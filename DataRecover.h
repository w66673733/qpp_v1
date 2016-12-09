#ifndef _DATARECOVER_H_
#define _DATARECOVER_H_
#include <stdio.h>
#include "Log.h"
#include "Constants.h"
#include "FileMap.h"
class CDataRecover
{
    public:
        CDataRecover();
        ~CDataRecover();
		void deletMemory();

        virtual unsigned int getCoarse();
        virtual unsigned int getFine();
        virtual unsigned char getChannelNum();
        virtual __int64 data2Time(unsigned char minFine, unsigned char maxFine, int coarseStep);
        virtual int logChnNum(unsigned int* chnNum, int& GPSCnt, FILE* fpLogNum);
        virtual int singleSecRecover(char* dataPath, char* logChnPath, int& GPSCnt);
        virtual int dataRecover(char* dataPath, char* dir);
        virtual void TimeDump(char *datafile, char *outputfile);

        virtual __int64 rectifyGPS(__int64 fixedGPS, __int64 fixedTime, int num);
        virtual __int64 fixGPS(__int64 lastGPS, __int64 currentGPS);
		virtual __int64 singleSecFix(unsigned char* pchannel, __int64* pTime, int num, __int64 lastGPS);
		virtual __int64 singleSecFix(char* dataPath, char* logChnPath,\ 
                char* chnPath, char* timePath, __int64 lastGPS, int *cnt);
        virtual __int64 singleSecFix(char* dataPath, char* logChnPath,\ 
                char* chnPath, char* timePath, int* cnt);


        virtual int readrnd(char* rndFilePaht, char* pRnd);
    private:
        unsigned char* m_c_pChannel;
        __int64* m_i64_pTime;
        __int64 m_lastGPS;
        unsigned char m_c_pdata[8];
		unsigned int m_i_chnCnt[10];

        CFileMap fileStore;

        
};
#endif

