#ifndef _KEYBOARDMANAGE_HPP_
#define _KEYBOARDMANAGE_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*∞¥º¸¿‡–Õ*/
enum KEY_TYPE {
  FOUR_KEYS, SIX_KEYS,
};


enum KEYS {
  KEY_UP = 1,		KEY_DOWN = 2,
  KEY_CANCEL = 3,	KEY_ENTER = 4,
  KEY_LEFT = 5,		KEY_RIGHT = 6,
  KEY_NULL = 0,
};

/* #ifdef FOUR_KEYS
   const enum KEYS _keymap[9] =  {
   KEY_NULL,	KEY_ENTER,
   KEY_DOWN,	KEY_NULL,
   KEY_CANCEL,	KEY_NULL,
   KEY_NULL,	KEY_NULL,
   KEY_UP,
 };
 #else
 #endif*/

class keyBoard{
public:
  keyBoard( bool isBlock = false );
  ~keyBoard( ){
    closeDev( );
  };
  enum KEYS OnKeyDown( void );
  void SetKeyType( enum KEY_TYPE _type );
  enum KEY_TYPE GetKeyType() ;
  void SetLock( bool tolock );
  bool IsLocked();
  void ClearBuffer();
private:
  int fdKey;
  bool isBlockMode;
  bool islighton;
  bool isLocked;

  time_t last;
  enum KEY_TYPE Keys;
  enum KEYS * _keymap ;

  bool openDev( bool isBlock );
  bool closeDev( void );
  int ReadKey();
  int lightoff();
  int lighton();
  double GetSysUpTime();
};

extern keyBoard * keyboard;

#endif /* _KEYBOARDMANAGE_HPP_*/
