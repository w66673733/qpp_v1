#ifndef _9XXDATARECOVER_H_
#define _9XXDATARECOVER_H_
#include "DataRecover.h"

class C9XXDataRecover : public CDataRecover
{
    public:
        C9XXDataRecover();
        unsigned int getCoarse();
        unsigned int getFine();
        unsigned char getChannelNum();
        __int64 data2Time(unsigned char minFine, unsigned char maxFine, int coarseStep);
        int dataRecover(char* dataFilePath, char* timeFilePath);
        int readRnd(char* rndFilePaht, char* pRnd);

};
#endif

