#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#pragma interface

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

const int actX = 160;
const int actY = 104;
const int DISP_Y_SIZE = 104;
const int DISP_X_SIZE = 160;
const int BITS_PER_PIXER = 1;
const int BITS_PER_BYTE = 8;
const int DISP_BUFF_SIZE = DISP_Y_SIZE * DISP_X_SIZE * BITS_PER_PIXER / BITS_PER_BYTE;
const int BYTES_PER_LINE = DISP_X_SIZE * BITS_PER_PIXER / BITS_PER_BYTE;

#define TAB_DEVICE_NAME "/dev/fb/0"
#define COG_DEVICE_NAME "/dev/fb0"

class graphics{
public:
  /*  graphics( );*/
  virtual ~graphics( );

/*   virtual void dump( void );*/
/*   virtual void undump( void );*/

  virtual void sync( char * buf, int bufsize ) = 0; /* ����������buf���е�����ͬ������ʾ�豸����ʾ����*/
  /*  virtual char * GetFrameBuff();*/                /* ���֡�������ָ��                 */
  char * bufmap[actY][actX >> 3];

protected:
  virtual bool openDev( const char *pDevName ) = 0;
  virtual bool closeDev() = 0;
};


/**************************************************
* COGLCD�豸�ӿ���
***************************************************/
class COG_graphics : public graphics
{
public:
  COG_graphics();
  ~COG_graphics();
  void sync( char * buf, int bufsize );

private:
  bool openDev( const char * pDevName );
  bool closeDev( );

  bool isOpen;

  char *fbDevBuffer;
};

/**************************************************
* TAB LCD�豸�ӿ�
***************************************************/
class TAB_graphics : public graphics
{
public:
  TAB_graphics();
  ~TAB_graphics();

  void sync( char * buf, int bufsize );

private:
  bool openDev( const char * pDevName );
  bool closeDev( );

  int  fbDev;
  bool isOpen;

  char *fbDevBuffer;
};

/***********************************************************
* ��ʼ���豸�ӿڣ������豸�ӿ�
* ע�⣺�豸��������new��ʽ���ɵģ�����ʱ����Ҫ��delete�ͷ�
************************************************************/
class graphics * InitGUIDevice( );

#endif
