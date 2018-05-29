#ifndef DEXSYNCINFO_H
#define DEXSYNCINFO_H

#include "net.h"

namespace dex {

struct DexSyncInfo
{
    int checkSum;
    int count;
    uint64_t lastTimeMod;

    DexSyncInfo() {
        checkSum = 0;
        count = 0;
        lastTimeMod = 0;
    }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
        READWRITE(checkSum);
        READWRITE(count);
        READWRITE(lastTimeMod);
    }

    friend bool operator==(const DexSyncInfo &a, const DexSyncInfo &b) {
        if (a.checkSum != b.checkSum) {
            return false;
        }

        if (a.count != b.count) {
            return false;
        }

        if (a.lastTimeMod != b.lastTimeMod) {
            return false;
        }

        return true;
    }

    friend bool operator!=(const DexSyncInfo &a, const DexSyncInfo &b) {
        return !(a == b);
    }
};

}

#endif // DEXSYNCINFO_H
