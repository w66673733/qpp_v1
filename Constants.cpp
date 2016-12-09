#include "Constants.h"

CConstants::CConstants(void)
{}

void CConstants::setConstant(unsigned char num, unsigned int value)
{
    switch(num)
    {
        case CHN_H:
            chn_A = value;
            break;
    }
}


unsigned char CConstants::chn_H = 0x00;
unsigned char CConstants::chn_V = 0x01;
unsigned char CConstants::chn_A = 0x02;
unsigned char CConstants::chn_D = 0x03;
unsigned char CConstants::chn_GPS = 0x04;
unsigned char CConstants::chn_SYN = 0x05;

unsigned int CConstants::rnd_len = 0;
unsigned int CConstants::block_size = 0;


__int64 CConstants::tdc_OF = 0;
__int64 CConstants::GPS_offset = 0;


CConstants CS;