#include "CTDCBlock.h"


CTDCBlock::CTDCBlock()
{
    m_p_syn = new __int64[2];//CS.syn_num_per_sec
//    m_pp_apdTime = new __int64[2];//CS.apd_channel_num

}

STDCBlock CTDCBlock::getTDCBlock(int apdChn = 4, int apdNum = 100, int synNum = 10000, int blockLen =1)
{
    STDCBlock block;
    block.p_syn = new __int64[synNum];
    memset(block.p_syn, 0, synNum*sizeof(block.p_syn));
    block.p2_apdTime = newArray.newArrayN(apdChn,apdNum);
    block.gpsStart = 0;
    block.gpsEnd = 0;
    block.syn_cnt = 0;
    return block;
}

void CTDCBlock::setBlockValue(STDCBlock &block, unsigned char channel, __int64 time, int* apdCnt, int &synCnt)
{
    switch(channel)
    {
        case 0:
            block->p2_apdTime[0][apdCnt[0]] = time;
            apdCnt[0]++;
            break;
        case 1:
            block->p2_apdTime[1][apdCnt[1]] = time;
            apdCnt[1]++;
            break;
        case 2:
            block->p2_apdTime[2][apdCnt[2]] = time;
            apdCnt[2]++;
            break;
        case 3:
            block->p2_apdTime[3][apdCnt[3]] = time;
            apdCnt[3]++;
            break;
        case 4:
            block->p_syn[synCnt] = time;
            synCnt++;
            break;
        case 5:
            break;
        case 6:
            break;
    } 
}

void CTDCBlock::setTDCBlockByFix(CDataRecover* pdataRecover, char* path, STDCBlcok &block)
{
    char dataPath[256];
    char logChnPath[256];
    char chnPath[256];
    char timePath[256];
    __int64 lastGps = 0;

    int j,i;
    int cnt = 0;
    int apdCnt[4] = {0,0,0,0};
    int synCnt = 0;

    for(i = 0; i < m_blockSize; i++)
    {   
        pdataRecover->singleSecFix(dataPath, logChnPath, chnPaht, timePath, &cnt);
        for(j = 0; j < cnt; j++)
        {
            setBlockValue(block, pdataRecover->m_c_pChannel[j], \
                    pdataRecover->m_i64_pTime, apdCnt, synCnt);        
        }

    }
}

void CTDCBlock::setTDCBlockByfile(char* path, STDCBlcok &block)
{
    char filePaht[256];
    strcpy(filePaht, path);

}

CTDCBlock::setTDCBlockByFile()
