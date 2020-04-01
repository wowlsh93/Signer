//
// Created by hama on 20. 4. 1..
//

#include "fpga.h"

//
//#include <accelerator/silexpk.h>
//
//#include <cstring>
//#include <iostream>
//#include <memory>
//
//namespace med::accelerator {
//
//    Silexpk::Silexpk(int boardIndex) {
//
//        _boardIndex = boardIndex;
//        struct sx_pk_config cfg = { .maxpending = MAXPENDING};
//        const struct sx_pk_capabilities *caps;
//        caps = sx_pk_fetch_capabilities(_boardIndex);
//
//        int status = sx_pk_initialize(&cfg);
//        std::cout << "silexpk init [board : " << boardIndex << "] [ status: " <<  status << "]" << std::endl;
//        //[info level] logging status
//    }
//
//    Silexpk::~Silexpk() {
//        sx_pk_finalize();
//    }
//
//    bool Silexpk::verifySync(Signer& signer, unsigned char* sign, unsigned char* pkey, unsigned char* hash) {
//
//        std::lock_guard<std::mutex> lg(_mtx);
//
//        unsigned char compactedSign[64];
//        signer.compact(sign, compactedSign);
//
//        unsigned char serializedkey[65];
//        signer.serialize(pkey, serializedkey);
//
//        const struct sx_buf h = { 32, (char*)hash };
//        const struct sx_buf qx = { 32, (char*) &serializedkey[1] };
//        const struct sx_buf qy = { 32, (char*) &serializedkey[33] };
//        const struct sx_buf r = { 32, (char*) &compactedSign[0] };
//        const struct sx_buf s = { 32, (char*) &compactedSign[32] };
//
//        int status = sx_ecdsa_verify(sx_pk_get_curve_secp256k1(), &qx, &qy, &r, &s, &h); // status 0 : ok
//        return status == 0;
//    }
//
//    void Silexpk::init() {
//
//        _results.clear();
//    }
//
//    void Silexpk::add(VerifyData& t) {
//
//        std::shared_ptr<ResultData> result = std::make_shared<ResultData>();
//
//        result->_index = t._index;
//        result->_result = 0;
//        _results.push_back(result);
//
//        std::shared_ptr<IncommingData> incommingData = std::make_shared<IncommingData>();
//
//        incommingData->_index = t._index;
//        memcpy(incommingData->_sign[Who::creator], t._sign_c, 64);
//        memcpy(incommingData->_pkey[Who::creator], t._pkey_c, 64);
//        memcpy(incommingData->_hash[Who::creator], t._hash_c, 32);
//
//        memcpy(incommingData->_sign[Who::endorsor1], t._sign_e1, 64);
//        memcpy(incommingData->_pkey[Who::endorsor1], t._pkey_e1, 64);
//        memcpy(incommingData->_hash[Who::endorsor1], t._hash1_e1, 32);
//
//        //memcpy(incommingData->_sign[Who::endorsor2], t._sign_e2, 64);
//        //memcpy(incommingData->_pkey[Who::endorsor2], t._pkey_e2, 64);
//        //memcpy(incommingData->_hash[Who::endorsor2], t._hash1_e2, 32);
//
//        //memcpy(incommingData->_sign[Who::endorsor3], t._sign_e3, 64);
//        //memcpy(incommingData->_pkey[Who::endorsor3], t._pkey_e3, 64);
//        //memcpy(incommingData->_hash[Who::endorsor3], t._hash1_e3, 32);
//
//        incommingData->_resultData = result;
//        _datas.push(incommingData);
//    }
//
//    int Silexpk::finishJob(sx_pk_accel *req, struct Job *job) {
//
//        int r;
//        r = sx_pk_has_finished(req);
//        sx_pk_release_accel(req);
//
//        if (r == SX_OK) {
//            job->_good++;
//        }
//
//        job->_remaining--;
//        if (job->_remaining > 0) {
//            return STEP_STATUS_PENDING;
//        }
//
//        if (job->_good == BATCH_VERIFY_COUNT) {
//            job->_incommingData->_resultData->_result = 1;
//        }
//        else {
//            job->_incommingData->_resultData->_result = 0;
//        }
//
//        return STEP_STATUS_DONE;
//    }
//
//    int Silexpk::verifyJob(Signer& signer, struct Job *job, std::queue<std::shared_ptr<IncommingData>>& datas) {
//
//        if (datas.empty())
//            return STEP_STATUS_EOF;
//
//        std::shared_ptr<IncommingData> data = datas.front();
//        datas.pop();
//
//        const struct sx_pk_ecurve *curve = sx_pk_get_curve_secp256k1();
//        job->_step = std::bind(&Silexpk::finishJob, this, std::placeholders::_1, std::placeholders::_2);
//        job->_remaining = BATCH_VERIFY_COUNT;
//        job->_good = 0;
//        job->_index = data->_index;
//        job->_incommingData = data;
//
//        struct sx_pk_dreq pkreq = {};
//
//        for (int i = 0; i < BATCH_VERIFY_COUNT; i++) {
//            unsigned char compacted_sign[64];
//            signer.compact(data->_sign[i], compacted_sign);
//
//            unsigned char serialized_key[65];
//            signer.serialize(data->_pkey[i], serialized_key);
//
//            job->_ops[i][Job::Arg::qx] = { ELEMENT_SIZE_32, (char*)&serialized_key[1] };
//            job->_ops[i][Job::Arg::qy] = { ELEMENT_SIZE_32, (char*)&serialized_key[33] };
//            job->_ops[i][Job::Arg::r]  = { ELEMENT_SIZE_32, (char*)&compacted_sign[0] };
//            job->_ops[i][Job::Arg::s]  = { ELEMENT_SIZE_32, (char*)&compacted_sign[32] };
//            job->_ops[i][Job::Arg::h]  = { ELEMENT_SIZE_32, (char*)data->_hash[i] };
//
//            pkreq = sx_async_ecdsa_verify_go(curve,
//                                             &job->_ops[i][Job::Arg::qx],
//                                             &job->_ops[i][Job::Arg::qy],
//                                             &job->_ops[i][Job::Arg::r],
//                                             &job->_ops[i][Job::Arg::s],
//                                             &job->_ops[i][Job::Arg::h]);
//
//            if (pkreq.status != 0) {
//                //[debug level] logging
//                data->_resultData->_result = 0;
//                return STEP_STATUS_ERROR;
//            }
//
//            sx_pk_set_user_context(pkreq.req, job);
//        }
//
//        return STEP_STATUS_PENDING;
//    }
//
//    void Silexpk::preprocessingTest() {
//
//        int idx = 0;
//        while (!_datas.empty()) {
//            std::shared_ptr<IncommingData> data = _datas.front();
//            _datas.pop();
//
//            for (int i = 0; i < BATCH_VERIFY_COUNT; i++) {
//                unsigned char compacted_sign[64];
//                _signer.compact(data->_sign[i], compacted_sign);
//
//                unsigned char serialized_key[65];
//                _signer.serialize(data->_pkey[i], serialized_key);
//
//                idx++;
//            }
//        }
//    }
//
//    int Silexpk::execute() {
//
//        struct Job jobs[MAXPENDING] = {};
//
//        struct Job *available = jobs;
//        int pending = 0;
//        int status = 1;
//
//        for (int i = 0; i < ARRAY_SIZE(jobs); i++) {
//            jobs[i]._next = &jobs[i + 1];
//        }
//
//        jobs[MAXPENDING - 1]._next = NULL;
//
//        while (!_datas.empty() || pending) {
//            while (!_datas.empty() && available) {
//                int rid;
//                rid = verifyJob(_signer, available, _datas);
//
//                if (rid == STEP_STATUS_EOF) {
//                    break;
//                }
//
//                if (rid == STEP_STATUS_PENDING) {
//                    pending++;
//                    available = available->_next;
//                }
//                else if (rid == STEP_STATUS_ERROR) {
//                    continue;
//                }
//            }
//
//            sx_pk_accel *req;
//            if (!pending)
//                continue;
//
//            while ((req = sx_pk_pop_finished_req()) == NULL) {
//                /* busy wait for now */
//            }
//
//            struct Job *job = (struct Job*)sx_pk_get_user_context(req);
//            int r = job->_step(req, job);
//            if (r != STEP_STATUS_PENDING) {
//                job->_next = available;
//                available = job;
//                pending--;
//            }
//        } // end of while
//
//        return status;
//    }
//
//    void Silexpk::resultPrint() {
//        int count = 0;
//        int result0 = 0;
//        int result1 = 0;
//        int result2 = 0;
//
//        for (std::vector<std::shared_ptr<ResultData>>::iterator iter = _results.begin(); iter != _results.end(); iter++) {
//
//            std::shared_ptr<ResultData> result = *iter;
//
//            if (result->_result == 2) {
//                result2++;
//            }
//            else if (result->_result == 1) {
//                result1++;
//            }
//            else {
//                result0++;
//            }
//
//            count++;
//        }
//
//        std::cout << "=======================================" << std::endl;
//
//        std::cout << "count : " << count << std::endl;
//        std::cout << "result0 : " << result0 << std::endl;
//        std::cout << "result1 : " << result1 << std::endl;
//        std::cout << "result2 : " << result2 << std::endl;
//    }
//}
