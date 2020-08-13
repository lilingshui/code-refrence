#ifndef _CANVAS_HPP_
#define _CANVAS_HPP_
#pragma interface
#include <pthread.h>

#include "graphics.hpp"
#include "types.hpp"
#include "public.h"
#include  <math.h>

/************************************
* 画布对象: 提供虚拟的屏幕,
************************************/
class Canvas {
public:
  /* */
  Canvas()
  {
    SetSize( 0, 160, 0, 104 );
  };

  ~Canvas()
  {
/*     if ( zone ) {*/
/*       free( zone );*/
/*     }*/
  };

  bool SetOrig( int x, int y );
  struct Point GetOrig( ) { return orig; };
  bool SetSize( int left , int right, int top, int bottom );
  bool SetWindowSize( int xlen, int ylen );
  bool SetWindowOrig( int x, int y );
  bool isPointInWindow( struct Point pnt );
  bool isPointInZone( struct Point pnt );
  bool clear( bool isBlack = false );
  bool Reverse();
  bool Reverse( struct Point lefttop, struct Point rightbtm ); /* 反白显示矩形区域*/
  /*void clear( );*/
  bool Sync(); 			/* to cope image in zone to graphic driver buffer*/

  bool DrawBit( int x, int y, bool isBlack );
  bool DrawLine( int x1, int y1, int x2, int y2, bool isBlack );
  /*  bool DrawBox( int x1, int y1, int x2, int y2, bool isBlack );*/
  bool DrawRectangle( int x1, int y1, int x2, int y2, bool isBlack );
  bool DrawPhasic( int x0, int y0, float length, float angle, bool isBlack, int &x2,int &y2 );
  bool DrawCircle( int x0, int y0, int radius, bool isBlack );
  static void Init(  );
  /*保护全局变量--zone 的互斥锁机制*/
  static void lock();
  static void unlock();
  static const int virtX;
  static const int virtY;

private:
  int _left;
  int _right;
  int _top;
  int _bottom;

  int xchars;
  int windowX;
  int windowY;

  int chars;
  struct Point orig;
  struct Point windowOrig;

  static unsigned char zone[640][40];

  static pthread_mutex_t zone_mut;

  static graphics * device;

};

#endif /* _CANVAS_HPP_*/
