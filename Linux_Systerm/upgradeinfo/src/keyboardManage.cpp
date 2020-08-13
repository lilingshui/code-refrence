#include <time.h>

#include "keyboardManage.hpp"

enum KEYS FourKeyMap[9] =
  {
    KEY_NULL,	KEY_ENTER,
    KEY_DOWN,	KEY_NULL,
    KEY_CANCEL,	KEY_NULL,
    KEY_NULL,	KEY_NULL,
    KEY_UP,
  };

enum KEYS SixKeyMap[9] =
  {
    KEY_NULL,	KEY_ENTER,
    KEY_DOWN,	KEY_NULL,
    KEY_CANCEL,	KEY_LEFT,
    KEY_NULL,	KEY_RIGHT,
    KEY_UP,
  };


void keyBoard::ClearBuffer( void )
{
	 unsigned char cKeyBuf[ 2 ];
	 int count = 0;
	 for(count =0; count < 50; count++) {
		 read( fdKey, cKeyBuf, 2 );
	 }

}
keyBoard::keyBoard( bool isBlock )
{
  isBlockMode = isBlock;
  fdKey = -1;
  openDev( isBlock );
  islighton = false;
  Keys = FOUR_KEYS;
  _keymap = FourKeyMap;
  lighton();
  isLocked = false;
  ClearBuffer();
}

void keyBoard::SetKeyType( enum KEY_TYPE _type )
{
  Keys = _type;
  switch( Keys )
    {
    case SIX_KEYS:
      _keymap = SixKeyMap;
      break;
    default:
      _keymap = FourKeyMap;
      break;
    }
}

/************************************************
*设定键盘是否上锁, 当给键盘上锁时, 不响应按键操作
*当解锁时, 先清除掉键盘设备中的累积的按键值
************************************************/
void keyBoard::SetLock( bool tolock )
{
  if ( tolock )
    {
      isLocked = true;
    }
  else
    {
      isLocked = false;
      while( OnKeyDown() != KEY_NULL )
	;
    }
}

enum KEY_TYPE keyBoard::GetKeyType()
{
  return Keys;
}

double keyBoard::GetSysUpTime()
{
  FILE * fp;

  fp = fopen( "/proc/uptime", "r" );
  if ( fp == NULL )
    {
      exit( -1 );
    }

  double runtime;

  fscanf( fp, "%lf", &runtime );
  fclose( fp );

  return runtime;
}

enum KEYS keyBoard::OnKeyDown( void )
{
  unsigned int i=0;
  time_t now;

  if ( isLocked )
    {
      return KEY_NULL;
    }

  i = ReadKey();

  if ( i > 0 && i < 9 )
    {
      last = ( long ) GetSysUpTime();
      if ( !islighton )
	{
	  lighton();
	}

      return _keymap[i];
    }

  now = ( long ) GetSysUpTime();
  if ( islighton && abs( now - last ) > 60 )
    {
      lightoff();
    }

  return KEY_NULL;
}


int keyBoard::ReadKey()
{
  unsigned char cKeyBuf[ 2 ];

  for( ;; )
    {
      memset( cKeyBuf, 0x00, sizeof( cKeyBuf ));

      if( read( fdKey, cKeyBuf, 2 ) != sizeof( cKeyBuf ) )
	{
	  /*
	    signal ?
	  */
	  //perror( "read( keyboard )" );
	  return -1;
	}else
	  {
	    if( cKeyBuf[ 0 ] != 0xff )
	      {
		return cKeyBuf[ 0 ];
	      }
	    else
	      {
		if( !isBlockMode )
		  {
		    return 0;
		  }
	      }
	  }
      /*
	loop last key
      */
    }
  /*
    unreached...
  */
  return -1;
}

bool keyBoard::openDev( bool isBlock )
{
  if( fdKey != -1 )
    return false;

  if( isBlock )
    fdKey = open( "/dev/wfet1000kb", O_RDWR );
  else
    fdKey = open( "/dev/wfet1000kb", O_RDWR | O_NONBLOCK );

  if( fdKey != -1 )
    return true;
  else{
    perror( "open( keyboard )" );
    exit(-1);
  }
}

bool keyBoard::closeDev( void )
{
  if( fdKey != -1 )
    {
      close( fdKey );
      fdKey = -1;
      return true;
    }else
      return false;
};

int keyBoard::lighton( void )
{
  last = ( long ) GetSysUpTime();
  if ( islighton )
    {
      return 0;
    }

  char key_buf[] = { 0xff };
  int i;

  i = write( fdKey, key_buf, 1 );

  if ( i != 1 )
    {
      return -1;
    }
  else
    {
      islighton = true;
      return 0;
    }
}

int keyBoard::lightoff( void )
{
  if ( !islighton ) {
    return 0;
  }

  char key_buf[] = { 0x00 };
  int i;

  i = write( fdKey, key_buf, 1 );

  if ( i != 1 )
    {
      return -1;
    }
  else
    {
      islighton = false;
      return 0;
    }
}


