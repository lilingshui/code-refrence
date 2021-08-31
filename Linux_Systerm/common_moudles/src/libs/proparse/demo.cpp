#include <iostream>
#include <stdio.h>
#include "proparseexport.h"

bool HandleFrameA(FrameStruct* frame)
{
    /*
    *
    *   handler the frame here
    */
    for(int i = 0; i < frame->FrameLen; i++)
    {
        printf("frame->Framedata[%d] is %02x\n", i, frame->Framedata[i]);
    }

    printf("HandleFrameA\n");
    return true;
}

int main(int argc, char** argv)
{
    printf("====11111====\n");
    PP_RegisterFrameHandler(CT_WRITE_PARAM, HandleFrameA);
    BYTE recvData[] = {0x68,0x00,0x00,0x00,0x00,0x00,0x00,0x68,0x14,0x12,0x34,0x33,0x33,0x32,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x34,0x33,0x33,0x33,0x33,0x8D,0x16};
    PP_InputBuffer(recvData, sizeof(recvData));
	return 0;
}
