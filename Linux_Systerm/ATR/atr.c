#include <stdio.h>
#include <stdbool.h>

#define TA_BIT          (1<<4)  /**< TAx presence bit (bit 4, 0x10) */
#define TB_BIT          (1<<5)  /**< TBx presence bit (bit 5, 0x20) */
#define TC_BIT          (1<<6)  /**< TCx presence bit (bit 6, 0x40) */
#define TD_BIT          (1<<7)  /**< TDx presence bit (bit 7, 0x80) */

void atr_TS(unsigned char ch)
{
    printf("TS: %02X\r\n", ch);
    if(ch == 0x3B) {
        printf("\t正向约定\r\n");
    } else if(ch == 0x3F) {
        printf("\t反向约定\r\n");
    } else {
        printf("\tATR 错误\r\n");
    }
}
void atr_T0(unsigned char ch)
{
    printf("T0: %02X\r\n", ch);

    if ((ch & TA_BIT) == TA_BIT) {
        printf("\tTA1 存在\r\n");
    }
    if ((ch & TB_BIT) == TB_BIT) {
        printf("\tTB1 存在\r\n");
    }
    if ((ch & TC_BIT) == TC_BIT) {
        printf("\tTC1 存在\r\n");
    }
    if ((ch & TD_BIT) == TD_BIT) {
        printf("\tTD1 存在\r\n");
    }
    printf("\t历史字符数: %d\r\n", ch & 0x0f);
}
void atr_TA1(unsigned char ch)
{
    int Di[16] = { 0, 1, 2, 4, 8, 16, 32, 64,
        12, 20, 0, 0, 0, 0, 0, 0 };
    int Fi[16] = { 372, 372, 558, 744, 1116, 1488, 1860, 0,
        0, 512, 768, 1024, 1536, 2048, 0, 0 };

    printf("TA1: %02X\r\n", ch);
    printf("\t时钟速率转换因子Fi: %d\r\n", (ch >> 4) & 0x0f);
    printf("\t位速率调节因子Di: %d\r\n", (ch & 0x0f));
    printf("\tFi/Di: %f\r\n",
        (Fi[(ch>>4)&0x0f]!=0 && Di[ch&0x0f]!=0) ? (float)Fi[(ch>>4)&0x0f]/(float)Di[ch&0x0f] : 0);
}
void atr_TB1(unsigned char ch)
{
    printf("TB1: %02X\r\n", ch);
    printf("\t编程电压 P 值: %d\r\n", ch & 0x1f);
    printf("\t最大编程电流 I 值: %d\r\n", (ch >> 5) & 0x03);
}
void atr_TC1(unsigned char ch)
{
    printf("TC1: %02X\r\n", ch);
    printf("\t额外保护时间: %d\r\n", ch);
}
void atr_TD1(unsigned char ch)
{
    printf("TD1: %02X\r\n", ch);

    if ((ch & TA_BIT) == TA_BIT) {
        printf("\tTA2 存在\r\n");
    }
    if ((ch & TB_BIT) == TB_BIT) {
        printf("\tTB2 存在\r\n");
    }
    if ((ch & TC_BIT) == TC_BIT) {
        printf("\tTC2 存在\r\n");
    }
    if ((ch & TD_BIT) == TD_BIT) {
        printf("\tTD2 存在\r\n");
    }
    printf("\t后续信息交换所使用的协议类型: %d\r\n", ch & 0x0f);
}
void atr_TA2(unsigned char ch)
{
    printf("TA2: %02X\r\n", ch);
    printf("\t是否有能力改变它的操作模式: %s\r\n",
        !!!(ch & 0x80) ? "是(0)" : "否(1)");
    printf("\t协商模式 or 特定模式: %s\r\n",
        !!!(ch & 0x80) ? "特定模式(0)" : "协商模式(1)");
    printf("\t后续信息交换所使用的协议类型: %d\r\n", ch & 0x0f);
}
void atr_TB2(unsigned char ch)
{
    printf("TB2: %02X\r\n", ch);
    printf("\tIC卡所需的编程电压P的值PI2: %d\r\n", ch);
}
void atr_TC2(unsigned char ch)
{
    printf("TC2: %02X\r\n", ch);
    printf("\tT=0, 传输工作等待时间整数WI: %d\r\n", ch);
}
void atr_TD2(unsigned char ch)
{
    printf("TD2: %02X\r\n", ch);

    if ((ch & TA_BIT) == TA_BIT) {
        printf("\tTA3 存在\r\n");
    }
    if ((ch & TB_BIT) == TB_BIT) {
        printf("\tTB3 存在\r\n");
    }
    if ((ch & TC_BIT) == TC_BIT) {
        printf("\tTC3 存在\r\n");
    }
    if ((ch & TD_BIT) == TD_BIT) {
        printf("\tTD3 存在\r\n");
    }
    printf("\t后续信息交换所使用的协议类型: %d\r\n", ch & 0x0f);
}
void atr_TA3(unsigned char ch)
{
    printf("TA3: %02X\r\n", ch);
    printf("\tT=1, IC卡的信息域大小整数IFSI: %d\r\n", ch);
}
void atr_TB3(unsigned char ch)
{
    printf("TB3: %02X\r\n", ch);
    printf("\tT=1, CWI: %d\r\n", ch & 0x0f);
    printf("\tT=1, BWI: %d\r\n", (ch >> 4) & 0x0f);
}
void atr_TC3(unsigned char ch)
{
    printf("TC3: %02X\r\n", ch);
    printf("\tT=1, 块错误校验码的类型: %d\r\n", ch & 0x01);
}
void atr_history(unsigned char *ch, int len)
{
    int i;
    printf("TKi:");
    for(i = 0; i < len; i++)
        printf(" %02X", ch[i]);
    printf("\r\n");
}
void atr_TCK(unsigned char ch)
{
    printf("TCK: %02X\r\n", ch);
}

#define STATE_PARSE_TS                            1
#define STATE_PARSE_T0                            2
#define STATE_PARSE_TA                            3
#define STATE_PARSE_TB                            4
#define STATE_PARSE_TC                            5
#define STATE_PARSE_TD                            6
#define STATE_PARSE_HIST_BYTES                    7
#define STATE_PARSE_TCK                            8
#define STATE_PARSE_END                            255

int atr_parse(unsigned char *atr, int len)
{
    unsigned char data;
    unsigned char TCK = 0;
    unsigned char K = 0;
    unsigned char Yi = 0;
    int k, state, index, length, protocol;
    unsigned char *ptr;
    unsigned char hist_bytes[16];


    length = len;
    ptr = atr;
    state = STATE_PARSE_TS;
    index = 0;
    k = 0;
    protocol = 0;

    while( ptr < (atr + length) ) {
        data = *ptr++;
        if ( state != STATE_PARSE_TS ) {
            TCK ^= data ;
        }

        switch( state ) {
            case STATE_PARSE_TS:
                atr_TS(data);
                state = STATE_PARSE_T0;
                break;
            case STATE_PARSE_T0:
                atr_T0(data);
                K = data & 0x0F;
                Yi = data;
                if ( data & 0x10 ) {
                    state = STATE_PARSE_TA;
                } else if ( data & 0x20 ) {
                    state = STATE_PARSE_TB;
                } else {
                    if ( data & 0x40 ){
                        state = STATE_PARSE_TC;
                    } else if ( data & 0x80 ) {
                        state = STATE_PARSE_TD;
                    } else {
                        state = STATE_PARSE_HIST_BYTES;
                    }
                }
                break;
            case STATE_PARSE_TA :
                switch( index ) {
                    case 0:            /* TA1 */
                        atr_TA1(data);
                        break;
                    case 1:
                        atr_TA2(data);
                        break;
                    case 2:
                        atr_TA3(data);
                        break;
                }
                if ( Yi & 0x20 ) {
                    state = STATE_PARSE_TB;
                } else if ( Yi & 0x40 ) {
                    state = STATE_PARSE_TC;
                } else if ( Yi & 0x80 ) {
                    state = STATE_PARSE_TD;
                } else {
                    state = STATE_PARSE_HIST_BYTES;
                }
                break;
            case STATE_PARSE_TB :
                switch( index ) {
                    case 0:            /* TB1 */
                        atr_TB1(data);
                        break ;
                    case 1:            /* TB2 */
                        atr_TB2(data);
                        break ;
                    case 2:            /* TB3 */
                        atr_TB3(data);
                        break;
                }

                if ( Yi & 0x40 ) {
                    state = STATE_PARSE_TC;
                } else if ( Yi & 0x80 ) {
                    state = STATE_PARSE_TD;
                } else{
                    state = STATE_PARSE_HIST_BYTES;
                }
                break;
            case STATE_PARSE_TC :
                switch( index ) {
                    case 0:            /* TC1 */
                        atr_TC1(data);
                        break;
                    case 1:            /* TC2 */
                        atr_TC2(data);
                        break ;
                    case 2:            /* TC3 */
                        atr_TC3(data);
                        break ;
                }
                if ( Yi & 0x80 ) {
                    state = STATE_PARSE_TD;
                } else {
                    state = STATE_PARSE_HIST_BYTES;
                }
                break ;
            case STATE_PARSE_TD :
                Yi = data ;
                switch( index++ ) {
                    case 0:
                        protocol = Yi & 0x0F;
                        atr_TD1(data);
                        break;
                    case 1:
                        atr_TD2(data);
                        break;
                }

                if ( Yi & 0xF0 ) {
                    if ( Yi & 0x10 ) {
                        /* TAx character present */
                        state = STATE_PARSE_TA;
                    } else if ( Yi & 0x20 ) {
                        /* TBx character present */
                        state = STATE_PARSE_TB;
                    } else if ( Yi & 0x40 ) {
                        /* TCx character present */
                        state = STATE_PARSE_TC;
                    } else if ( Yi & 0x80 ) {
                        /* TDx character present */
                        state = STATE_PARSE_TD;
                    } else {
                        state = STATE_PARSE_HIST_BYTES;
                    }
                } else {
                    state = STATE_PARSE_HIST_BYTES;
                }
                break ;
            case STATE_PARSE_HIST_BYTES:
                if( K ) {
                    if( k < K ) {
                        hist_bytes[k++] = data;
                        if(k == K) {
                            if(protocol > 0)
                                state = STATE_PARSE_TCK;
                            else
                                ptr = atr + length;
                            atr_history(hist_bytes, k);
                        }
                    }
                    break;
                }
            case STATE_PARSE_TCK:
                atr_TCK(data);
                if ( !TCK ){
                }
                atr_TCK(TCK);
                ptr = atr + length;
                break ;
        }
        if( state == STATE_PARSE_HIST_BYTES && K == 0 && protocol == 0)
            break;
    }

    return 0;
}

int read_frame_form_file(unsigned char buf[], int size)
{
    int len = 0;
	bool bResult = true;
	FILE * fp;
    char * line = NULL;
    size_t linelen = 0;
	ssize_t read;

	fp = fopen("frame.txt", "r");
	if (fp == NULL) {
		printf("open file error\n");
		return -1;
	}

	while ((read = getline(&line, &linelen, fp)) != -1) {
		len = 0;
		char* pstrLine = line;
		unsigned int nValue = 0;

		while (1) {
			int ret = sscanf(pstrLine, "%02X", &nValue);
			if (EOF == ret || 0 >= ret) {
				break;
			}

			buf[len] = nValue;
			len++;
			pstrLine += 3;
            if(len >= size) {
                break;
            }
		}
/*
		if (len > 0) {
			printf("Send Data => ");
			for(int j = 0; j < len; j++) {
				printf("%02X ", buf[j]);
			}
			printf("\n");
		}
*/        
     }

    return len;
}

int main(void)
{
    unsigned char atr[256] = {0};
    int len = read_frame_form_file(atr, sizeof(atr)/sizeof(atr[0]));
    atr_parse(atr, len);
    return 0;
}