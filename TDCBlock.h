#ifndef _TDCBLOCK_H_
#define _TDCBLOCK_H_
#include "Constants.h"
#include "DataRecover.h"
#include "New2DArray.h"

struct STDCBlock
{
    __int64 gpsStart, gpsEnd;
	__int64 *p_syn;
	__int64	**p2_apdTime;
	int syn_cnt;
}

class CTDCBlock
{
    public:
        CTDCBlock();
        STDCBlock getTDCBlock(int apdChn = 4, int apdNum = 100, int synNum = 10000, int blockLen =1);
        void setBlockValue(STDCBlock &block, unsigned char channel, __int64 time, int* apdCnt, int &synCnt);
        __int64 setTDCBlockByFile(char* path, STDCBlock &block);
        __int64 setTDCBlockByFix(CDataRecover* pdataRecover, char* path,\
                __int64 lastGps, int blockLen, STDCBlock &block);
        __int64 setTDCBlock(CDataRecover* pdataRecover, char* path, STDCBlock &block, bool renew);
        ~CTDCBlock();
    public:
        CNew2DArray<__int64> newArray;
        int m_blockSize;
};
#endif
