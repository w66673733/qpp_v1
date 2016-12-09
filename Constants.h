#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//typedef long long __int64;

#define TDC_LEN 8

#define CHN_H 0x00
#define CHN_V 0x01
#define CHN_A 0x02
#define CHN_D 0x03
#define CHN_SYN 0x04
#define CHN_GPS 0x05



#define PS_PER_SEC 1000000000000i64

class CConstants
{
    public:
    CConstants();
    static void setConstant(unsigned char name, unsigned int value);
    static void setConstant(unsigned char name, __int64 value);
    
    public:

    static unsigned char chn_H;
    static unsigned char chn_V;
    static unsigned char chn_A;
    static unsigned char chn_D;
    static unsigned char chn_SYN;
    static unsigned char chn_GPS;
    static unsigned char chn_OF; //channel overflow 
    static unsigned char chn_PPC;

    static unsigned int block_size;
    static unsigned int block_seconds;

    static unsigned int apd_channel_num;
    static unsigned int apd_num_per_sec;
    static unsigned int syn_num_per_sec;

    static unsigned int rnd_len;
    static __int64 tdc_OF;
    static __int64 GPS_offset;

};

extern CConstants CS;
#endif
