#include "9XXDataRecover.h"

unsigned int C9XXDataRecover::getCoarse()
{
    /*
    int Coarse;
	
	Coarse = *(unsigned char *)(m_c_pdata+3);
	Coarse = (Coarse << 8) | *(unsigned char *)(m_c_pdata + 4);
	Coarse = (Coarse << 8) | *(unsigned char *)(m_c_pdata + 5);
	*/
	return  (8 << ((8<< *(unsigned char *)(m_c_pdata+3)) \
                | *(unsigned char *)(m_c_pdata + 4))) \
                | *(unsigned char *)(m_c_pdata + 5);
}

unsigned int C9XXDataRecover::getFine()
{
    return *(unsigned char*)(m_c_pdata + 6);
}

unsigned char C9XXDataRecover::getChannelNum()
{
    switch(*(unsigned char*)(m_c_pdata + 7))
    {
       	case 0xF1://新旧版本
	    case 0xF2://新旧版本
    	case 0xF3://新旧版本
	    case 0xF4://新旧版本
	        return 4;
    	case 0xFE://新旧版本
	    case 0xC1://新版本
    	case 0xC2://新版本
	    case 0xC3://新版本
    	case 0xC5://新版本
	    case 0xC6://新版本
    	case 0xC7://新版本
    		return 5;
    	case 0xD1://新旧版本
	    	return 0;
    	case 0xD2://新旧版本
	    	return 1;
    	case 0xD4://新旧版本
	    	return 2;
    	case 0xD8://新旧版本
	    	return 3;
    	case 0xCE://新版本
    		return 6;
	    case 0xFA://新旧版本
    	case 0xCA://新旧版本
	    	return 7;
    	case 0xA1://新旧版本
	    	return 8;
    
	    default:
		    break;  
    }
    return 0xFF;
}

__int64 C9XXDataRecover::data2Time(unsigned char minFine, unsigned char maxFine, int coarseStep)
{
    __int64 tm;
	
	double fine_step;
	__int64 mask;
	unsigned char fine;

	unsigned char channel;
	
	if(!coarseStep || (maxFine <= minFine)){
		minFine = 8;
		maxFine = 120;
		coarseStep = 40000;
		//max_fine = coarse_step/345 - 1;
	}
	
	mask = CS.tdc_OV/coarseStep - 1;
	
	fine_step = coarseStep*1.0/(maxFine - minFine + 1);
	
	channel = getChannelNum(m_c_pdata);
	
	if(channel == CS.chn_OF){
		tm = Q4GetCoarse(m_c_pdata);	//溢出计数
		tm *= 1024*1024;
		tm *= 40000;
//		tm += Q4GetFine(m_c_pdata);		//GPS计数
		tm %= CS.chn_OF;
		return tm;
	}

	if(channel == CS.chn_GPS){
		tm = getCoarse(m_c_pdata);	//粗计数
		tm &= mask;
		tm *= coarse_step;
	//	tm += Q4GetFine(m_c_pdata);		//GPS计数
		return tm;
	}
	if(channel == CS.chn_PPC){
		tm = getCoarse(m_c_pdata);	//PPC给出的GPS时间秒
		tm *= 10000;
		tm += getFine(m_c_pdata);		//GPS计数
		return tm;
	}

	tm = getCoarse(m_c_pdata);
	tm &= mask;
	tm *= coarseStep;
	
	fine = getFine(m_c_pdata);
	if(fine > maxFine){
		fine = maxFine;
	}
	tm -= (int)((fine - minFine) * fine_step);
	return tm;
}
