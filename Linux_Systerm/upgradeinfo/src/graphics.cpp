#pragma implementation "graphics.hpp"

#include "graphics.hpp"

graphics::~graphics()
{
  memset( bufmap, 0, sizeof( bufmap ));
}

TAB_graphics::~TAB_graphics()
{
  closeDev();
}


TAB_graphics::TAB_graphics()
{
  isOpen = false;
  fbDevBuffer = 0;
  memset( bufmap, 0, sizeof( bufmap ));
  openDev( TAB_DEVICE_NAME );
}



bool TAB_graphics::openDev( const char * pDevName )
{
  isOpen = false;
  fbDev = open( pDevName, O_RDWR);

  if( fbDev < 0 ) {
    perror( "open( framebuffer )" );
    return false;
  }
  puts( "frambuffer device has opened." );

  fbDevBuffer = ( char * )mmap( NULL, 160 * 80,
				PROT_READ|PROT_WRITE,MAP_SHARED, fbDev, 0 );

  if( !fbDevBuffer )
    {
      close( fbDev );
      return false;
    }

  int offset = 0;
  char * fb = fbDevBuffer;

  for (int y = 0; y < actY; y ++)
    {
      offset = y * 80; /* 80 is the virual screen chars in X axle*/
      for (int x = 0; x < actX >> 3; x ++, offset ++)
	{
	  int tmp = x + 3 - 2 * ( x & 0x03);
	  bufmap[y][tmp] = fb + offset;
	}
    }

  isOpen = true;
  return true;
}

void TAB_graphics::sync( char * buf, int bufsize )
{

}

bool TAB_graphics::closeDev()
{
  if( isOpen )
    {
      munmap( fbDevBuffer, 160 * 20 );
      close( fbDev );
      isOpen = false;
      return true;
    }
  else
    {
      return false;
    }
}

COG_graphics::COG_graphics()
{
  isOpen = false;
  memset( bufmap, 0, sizeof( bufmap ));
  openDev( COG_DEVICE_NAME );
}

COG_graphics::~COG_graphics()
{
  closeDev();
}


bool COG_graphics::openDev( const char *pDevName )
{
  isOpen = false;
  fbDevBuffer = (char * )malloc( DISP_BUFF_SIZE );
  if ( fbDevBuffer == 0 )
    {
      perror( "can not get free memory \n" );
      exit( -1 );
    }

  int offset = 0;
  for (int y = 0; y < actY; y ++)
    {
      for (int x = 0; x < actX * BITS_PER_PIXER / BITS_PER_BYTE; x ++, offset ++)
	{
	  bufmap[y][x] = fbDevBuffer + offset;
	}
    }

  isOpen = true;
  return true;
}

/******************************************************************************
* ���ڲ���COG��Chip On Glass����ʾ���������ں˽�ڲ���֧��mmap��ʽ������ֻ֧����
* write��ʽ��Ϊ�˾���ʹ�Ķ���С�������˴˺�����ֱ�Ӳ����豸
* ʹ��˵����������ʾ��������ָ�루buf) �ͻ�������С��bufsize�����ɹ��򷵻�true��
* ���򷵻�false
******************************************************************************/
void COG_graphics::sync( char * buf, int bufsize )
{
  int fd = open( "/dev/fb0", O_RDWR );
  if( fd < 0 )
    {
      return;
    }

  int real_size = ( bufsize < DISP_BUFF_SIZE )? bufsize : DISP_BUFF_SIZE;
  write( fd, buf, real_size );
  close( fd );

  return ;
}


bool COG_graphics::closeDev()
{
  free( bufmap[0][0] );
  memset( bufmap, 0, sizeof( bufmap ));
  return true;
}



/********************************************************************
* Ŀǰͼ���豸�ӿ������֣�һ����ͨ��mmap��ʽ��ֱ��д�ڴ棨TAB��ʽ����
* ����һ������write��ʽ��COG��ʽ�������ߵ����ַ�ʽĿǰ��ͨ���ļ������ֵ�
* ���ַ�ʽ��̫�ã�����и��õ����ַ�ʽ����Ҫ�޸�
********************************************************************/
class graphics * InitGUIDevice( )
{
  class graphics * device = 0;

  if ( access( COG_DEVICE_NAME, R_OK | W_OK ) == 0 )
    {
      device = new COG_graphics;
    }
  else if ( access( TAB_DEVICE_NAME, R_OK | W_OK ) == 0 )
    {
      device = new TAB_graphics;
    }
  else
    {
      /* û���κ�һ���豸���쳣*/
      printf( "can not find %s or %s device\n", COG_DEVICE_NAME, TAB_DEVICE_NAME );
    }

  if ( device == 0 )
    {
      /* �Ƿ�Ӧ�ü�¼*/
      printf( "can not init device!!!!\n" );
    }

  return device;
}
