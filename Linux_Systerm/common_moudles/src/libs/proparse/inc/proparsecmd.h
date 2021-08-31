#ifndef _PROPARSE_CMD_H_
#define _PROPARSE_CMD_H_

/*������λ�����б���֡��������*/
enum PROPARSE_CMD_TYPE {
   CT_READ_PARAM = 0x11,
   CT_WRITE_PARAM = 0x14,
   CT_TEST_INFRARED = 0x16,
   CT_TEST_INFRARED_N = 0x91,
   CT_TEST_INFRARED_A = 0xD1,
   CT_ERROR = 0xFF,
};

#endif /*_PROPARSE_CMD_H_*/

