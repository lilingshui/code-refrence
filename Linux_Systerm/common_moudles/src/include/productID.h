#ifndef _PRODUCT_ID_H_
#define _PRODUCT_ID_H_

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "wfos_ioctl.h"

#define NEWGWII         0x200
#define NEWGWIII        0x400
/*#define NEWGW_ZB      0x400*/     /*新国网专变*/
#define NEWGWJS         0x800
#define NEWGWI_JZQ      0x40000
#define NEWGWSHI_JZQ    0x1000000
#define NEWGWSHIII      0x2000000
#define NW_FK           0x80000     /*新南网负控*/
#define NW_JZQ          0x100000    /*新南网集中器*/
#define NW_PB           0x80        /*新南网配变*/

/*9G25 CSG terminals*/
#define CSG_9G25_PB     0x3

/*
int GetProductID()
{
    int fd;
    int product_id = 0;
    for( int i = 0; i < 3; i++ )
    {
        if( ( fd = open("/dev/productinfo", O_RDWR)) >= 0 )
        {
            if( ( product_id = ioctl(fd, IOC_PRODUCT_ID, 0)) >= 0 )
            {
                close( fd );
                break;
            }
        }
        else
        {
            usleep( 200000 );
        }
    }
    return product_id;
}
*/

#endif /*_PRODUCT_ID_H_*/

