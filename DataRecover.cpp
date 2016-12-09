#include "DataRecover.h"
#include <string.h>
CDataRecover::CDataRecover()
{   
    m_lastGPS = 0;
    m_c_pChannel = new unsigned char[CS.block_size + 1];
    m_i64_pTime = new __int64[CS.block_size + 1];
	memset(m_i_chnCnt, 0, 10*sizeof(int));
}

CDataRecover::~CDataRecover()
{
	deletMemory();
}

void CDataRecover::deletMemory()
{
	if (m_c_pChannel)
	{
		delete[] m_c_pChannel;
	}
	if (m_i64_pTime)
	{
		delete[] m_i64_pTime;
	}
}

unsigned int CDataRecover::getCoarse()
{
    return 0;
}

unsigned int CDataRecover::getFine()
{
    return 0;
}

unsigned char CDataRecover::getChannelNum()
{
    return 0xFF;
}

__int64 CDataRecover::data2Time(unsigned char minFine, unsigned char maxFine, int coarseStep)
{
    return 0;
}

int CDataRecover::logChnNum(unsigned int* chnCnt, int& GPSCnt, FILE* fpLogNum)
{
	GPSCnt++;
	fprintf(fpLogNum,"%d\t%6d\t%6d\t%6d\t%6d\t%6d\t\n", GPSCnt,chnCnt[CS.chn_H],\
			  chnCnt[CS.chn_V], chnCnt[CS.chn_A], chnCnt[CS.chn_D], chnCnt[CS.chn_SYN]);
	 return 0;
}

int CDataRecover::singleSecRecover(char* dataPath, char* logChnPath, int &GPSCnt)
{
    unsigned char channel;
    __int64 time;
    int i = 0;

    FILE* fpData = fileStore.getFile(dataPath, "rb");
    FILE* fpLogChn = fileStore.getFile(logChnPath, "w");
    
    while(fread(m_c_pdata,1,8,fpData))
    {
        channel = getChannelNum();
        m_i_chnCnt[channel]++;
        if(channel == 0xFF){
			time = data2Time(0,0,0);
		}
		else{
			time = data2Time(0,0,0);
		}
        if(i >= CS.block_size)
        {
			while(fread(m_c_pdata,1,8,fpData))
			{
				channel = getChannelNum();
				if(channel == CS.chn_GPS)
				{   
					m_c_pChannel[i] = channel;
				    m_i64_pTime[i] = time;
					logChnNum(m_i_chnCnt, GPSCnt, fpLogChn);
					LOG("warning : memery out when recover time at GPS:", GPSCnt);
					return i;
				}
			}
        }
        m_c_pChannel[i] = channel;
        m_i64_pTime[i] = time;

        if(channel == CS.chn_GPS)
        {   
            logChnNum(m_i_chnCnt, GPSCnt, fpLogChn);
            return i;
        }
		i++;
    }
    fileStore.close(dataPath);
    fileStore.close(logChnPaht);
    return i;
}

int CDataRecover::dataRecover(char* dataPath, char* dir)
{
    FILE *fpData, *fpLogChn;
    FILE* fpRecoverData[4];

    char path[256];
	int cnt = 0;
    fpData = fopen(dataPath, "rb");
    strcpy(path,dir);
    strcat(path,"chn.dat");
    fpRecoverData[0] = fopen(path, "wb");
    strcpy(path,dir);
    strcat(path,"rawTime.dat");
    fpRecoverData[1] = fopen(path, "wb");
    strcpy(path,dir);
    strcat(path,"GPSTime.dat");
    fpRecoverData[2] = fopen(path, "wb");
    strcpy(path,dir);
    strcat(path,"chnNum.txt");
    fpRecoverData[3] = fopen(path, "w");
	int GPSCnt = 0;
    while(!feof(fpData))
    {
        cnt = singleSecRecover(fpData, fpLogChn, GPSCnt);
		fwrite(m_c_pChannel, 1, cnt, fpRecoverData[0]);
        fwrite(m_i64_pTime, 8, cnt, fpRecoverData[1]);
		fwrite(&m_i64_pTime[cnt],8,1,fpRecoverData[2]);
            
    }
    for (int i = 0; i < 3; i++)
    {
		fclose(fpRecoverData[i]);
    }
    
    fclose(fpData); 
    return 0;
}

void CDataRecover::TimeDump(char *datafile, char *outputfile)
{ 
	FILE *fp1,*fp2; 
	unsigned char buffer[9];
	
	__int64 time;
	
	fp1 = fopen(datafile,"rb");
	fp2 = fopen(outputfile,"wt");
	while(fread(buffer,1,9,fp1) == 9)
	{
		time = *(__int64 *)(buffer+1);
		fprintf(fp2,"%d\t%15I64d\t",buffer[0],time);
		fprintf(fp2,"%15I64d\n",time % CS.tdc_OF);
	}
	fclose(fp1);
	fclose(fp2);
}

__int64 CDataRecover::fixGPS(__int64 lastGPS, __int64 currentGPS)
{
    int i = 0;
    __int64 crtGPS = currentGPS;
    __int64 GPSGap = 0;
    __int64 rem = 0;
    int sec = 400*PS_PER_SEC/CS.tdc_OF;
    for(i = 0; i < sec; i++)
    {   
        GPSGap = crtGPS - lastGPS;
        if(GPSGap > 0)
        {
            rem = GPSGap % PS_PER_SEC;
			if (rem > PS_PER_SEC/2)
				rem = rem - PS_PER_SEC;
			
            if (rem > -CS.GPS_offset && rem < CS.tdc_OF)
                return crtGPS;
        }
        crtGPS = currentGPS + CS.tdc_OF*i;
    }
}

__int64 CDataRecover::rectifyGPS(__int64 fixedGPS, __int64 fixedTime, int num)
{
    __int64 offset;
    if (num < 10)
    {
        return fixedGPS;
    }
    else
    {
        offset = fixedGPS - fixedTime;
        return fixedGPS;
    }
}

__int64 CDataRecover::singleSecFix(unsigned char* pchannel, __int64* pTime,\
        int num, __int64 lastGPS)
{
   int i = 0;
   __int64 timeAddon = 0, lastTime = lastGPS % CS.tdc_OF;
   __int64 fixedGPS = lastGPS;
   for(i = 0; i < num; i++) 
   {
       if(pTime[i] < lastTime) // if current time < last time need carry
       {
	     timeAddon += CS.tdc_OF;
	   }
	   lastTime = pTime[i];
	   pTime[i] += timeAddon;
	   
   }
   if(pchannel[--i] == CS.chn_GPS)
    {
        fixedGPS = fixGPS(lastGPS, lastTime);
        return rectifyGPS(fixedGPS, pTime[i], num);
    }
   else
   {
	   return -1;
   }
}

__int64 CDataRecover::singleSecFix(char* dataPath, char* logChnPath,\ 
        char* chnPath, char* timePath, __int64 lastGPS, int *cnt)
{
	int GPSCnt = 0;
    
    FILE* fpChn = fileStore.getFile(chnPath, "wb");
    FILE* fpTime = fileStore.getFile(timePaht, "wb");

    *cnt = singleSecRecover(dataPath, logChnPath, GPSCnt);  
	__int64 gps = singleSecFix(m_c_pChannel, m_i64_pTime, cnt, lastGPS);
    fwrite(m_c_pChannel, cnt, 1, fpChn);
    fwrite(m_i64_pTime, cnt, 8, fpTime);
    if(fileStore.fileIsExist(dataPath))
    {
        fileStore.closeFile(fpChn);
        fileStore.closeFile(fpTime);
    }
    return gps;
}

__int64 CDataRecover::singleSecFix(char* dataPath, char* logChnPath,\ 
        char* chnPath, char* timePath, int *cnt)
{   
    m_lastGPS = singleSecFix(dataPath, logChnPath, chnPath, timePath, m_lastGPS, &cnt);
    return m_lastGPS;
}

int CDataRecover::readRnd(char* rndFilePaht, char* pRnd)
{
    FILE* fpRnd;
    fpRnd = fopen(rndFilePaht, "rb");

    if(fpRnd == NULL)
    {
        printf("rnd file open error");
    }
   fread(pRnd, 1, CS.rnd_len/2, fpRnd);
   fclose(fpRnd);
   return 0;
}
