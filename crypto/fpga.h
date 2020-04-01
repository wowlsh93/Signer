//
// Created by hama on 20. 4. 1..
//

#ifndef SIGNER_FPGA_H
#define SIGNER_FPGA_H

//
//#pragma once
//
//#include <mutex>
//#include <queue>
//#include <functional>
//
//#include <silexpk/sxbufop.h>
//#include <silexpk/core.h>
//#include <silexpk/ed25519.h>
//#include <silexpk/ec_curves.h>
//#include <silexpk/statuscodes.h>
//#include <silexpk/sxops/montgommery.h>
//#include <silexpk/sxops/rsa.h>
//#include <silexpk/sxops/eccweierstrass.h>
//
//#include <common/crypto/signer.h>
//#include <common/define/data.h>
//#include <common/interprocess/shared_memory_parent.h>
//
//#define BATCH_VERIFY_COUNT 2
//#define MAXPENDING         (126 / BATCH_VERIFY_COUNT)
//
//#define STEP_STATUS_DONE        -1
//#define STEP_STATUS_PENDING     1
//#define STEP_STATUS_EOF         -3
//#define STEP_STATUS_ERROR       -4
//#define STEP_STATUS_FATAL_ERROR -5
//
//#define ELEMENT_SIZE_32 32
//
//#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))
//
//using namespace med::interprocess;
//using namespace med::crypto;
//
//namespace med::accelerator {
//
//    struct ResultData {
//        int _index;
//        int _result; // 0 : insert error, result error , 1 : ok
//    };
//
//    struct IncommingData {
//        int _index;
//        unsigned char _sign[4][64];
//        unsigned char _pkey[4][64];
//        unsigned char _hash[4][32];
//
//        std::shared_ptr<ResultData> _resultData;
//    };
//
//    struct Job {
//        enum Arg {qx, qy, r, s, h};
//
//        int           _index;
//        int           _rid;
//        struct Job*   _next;
//        std::function<int(sx_pk_accel *req, struct Job *job)> _step;
//        struct sx_buf _ops[BATCH_VERIFY_COUNT][5];
//        int           _remaining;
//        int           _good;
//
//        std::shared_ptr<IncommingData>  _incommingData;
//    };
//
//    struct sx_pk_user_context {
//        struct Job job;
//    };
//
//    class Silexpk {
//
//    public:
//        enum Who {creator, endorsor1, endorsor2, endorsor3};
//
//        Silexpk(int boardIndex);
//        virtual ~Silexpk();
//
//        void init();
//
//        void add(VerifyData& t);
//        void addTest(VerifyData& t);
//
//        int execute();
//
//        // for test
//        bool verifySync(Signer& signer, unsigned char* sign, unsigned char* pkey, unsigned char* hash);
//        void preprocessingTest();
//        void resultPrint();
//
//        std::vector<std::shared_ptr<ResultData>> & result() {
//            return _results;
//        }
//
//    private:
//        int finishJob(sx_pk_accel *req, struct Job *job);
//        int verifyJob(Signer& signer, struct Job *job, std::queue<std::shared_ptr<IncommingData>>& datas);
//
//        Signer     _signer;
//        std::mutex _mtx;
//        std::queue<std::shared_ptr<IncommingData>> _datas;
//        std::vector<std::shared_ptr<ResultData>>   _results;
//
//        int _boardIndex;
//    };
//}


#endif //SIGNER_FPGA_H
