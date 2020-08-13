#pragma implementation "canvas.hpp"
#include "canvas.hpp"

unsigned char  Canvas::zone[640][40];
graphics * Canvas::device;

pthread_mutex_t Canvas::zone_mut = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

const int Canvas::virtX = 320;
const int Canvas::virtY = 640;
const double RADPERDEG = 3.1415926/180;

bool Canvas::SetSize( int left, int right, int top, int bottom )
{
  if ( left > right || top > bottom ) {
    _left = _right = _top = _bottom = 0;
  }

  _left = left  - ( left & 0x07 );
  _right = right;
  _top = top;
  _bottom = bottom;

  xchars = ( _right - _left ) >> 3;
  chars = xchars * ( _bottom - _top );

  orig.x  = _left;
  orig.y  = _top;
  windowOrig.x = 0;
  windowOrig.y = 0;
  SetWindowSize( 160, 104 );

  return true;
}

bool Canvas::SetWindowSize( int xlen, int ylen )
{
  windowX = min( min( actX, xlen ), _right - _left ) ;
  windowX = windowX - ( windowX & 0x07 );
  windowY = min( min( actY, ylen ), _bottom - _top );

  return true;
}


bool Canvas::SetOrig( int x, int y )
{
/*   if ( x > _right || y > _bottom ) {*/
/*     return false;*/
/*   }*/

  orig.x = x - ( x & 0x07 );
  orig.y = y;

  /*SetWindowOrig( orig.x, orig.y );*/

  return true;
}

bool Canvas::clear( bool isBlack )
{

  if ( isBlack ) {
    memset( zone, 0xff, sizeof( zone ) );
  }
  else {
    memset( zone, 0, sizeof( zone ) );
  }

  return true;
}

bool Canvas::Reverse( )
{
/*   if ( !zone ) {*/
/*     return false;*/
/*   }*/

  unsigned char * p = &(zone[0][0]);
  for ( int i = 0; i < chars; i ++ ) {
    p[i] ^= 0xff;
  }

  return true;
}

bool Canvas::Reverse(  struct Point lefttop, struct Point rightbtm )
{
  /* to get the valid rectangle region*/

   if ( !isPointInZone( lefttop ) || !isPointInZone( rightbtm ) ) {
     return false;
  }

  for ( int y = lefttop.y; y < rightbtm.y; y ++ ) {
    for ( int x = lefttop.x >> 3; x < ( rightbtm.x + 7 ) >> 3; x ++ ) {
      /*zone[y * ( virtX >> 3 ) + x] ^= 0xff;*/
      zone[y][x] ^= 0xff;
    }
  }

  return true;

}

bool Canvas::SetWindowOrig( int x, int y )
{

  if ( x + windowX > _right ) {
    windowOrig.x = _right - windowX;
    windowOrig.x = windowOrig.x - ( windowOrig.x & 0x07 );
  }
  else {
    windowOrig.x = x;
  }

  if ( y + windowY > _bottom ) {
    windowOrig.y = _bottom - windowY;
  }
  else {
    windowOrig.y = y;
  }

  return true;
}

bool Canvas::isPointInZone( struct Point pnt )
{
  return ( pnt.x <= ( _right - _left ) && pnt.y <= ( _bottom - _top  ));
}

bool Canvas::isPointInWindow( struct Point pnt )
{
  return ( pnt.x >= windowOrig.x && pnt.x <= windowOrig.x + windowX &&
	   pnt.y >= windowOrig.y && pnt.y <= windowOrig.y + windowY );
}

bool Canvas::Sync()
{
  int y1, y2, x1, x2;

  int virty =  min( windowOrig.y + windowY, virtY );
   for ( y1 = windowOrig.y, y2 = orig.y; ( y1 < virty ) && ( y2 < actY ); y1 ++, y2 ++ ) {
     int virtx = ( min( windowOrig.x + windowX, virtX ) >> 3 );
     for ( x1 = windowOrig.x >> 3, x2 = orig.x >> 3; ( x1 < virtx ) && ( x2 < actX );
	   x1 ++, x2 ++ ) {
       *( device->bufmap[y2][x2] ) = zone[y1][x1];
     }
   }

   device->sync( device->bufmap[0][0], DISP_BUFF_SIZE );
  return true;
}

bool Canvas::DrawBit( int x, int y, bool isBlack )
{
 /*  if ( !zone ) {*/
/*     return false;*/
/*   }*/

  if (( x  >= _right - _left ) ||( y  >=  _bottom - _top )) {
    return false;
  }

  unsigned char value =  0x01 << ( 7 - ( x & 0x07 ) );
  /*unsigned char value = 0x01 << ( (31-(x%32))% 8 );*/

  if ( isBlack ) {
    zone[y][x >> 3] |= value;
    /**(device->bufmap[ y][ x >> 3]) |= value;*/
  }
  else {
    zone[y][x >> 3] &= ~value;
    /**( device->bufmap[y][x >> 3] ) &= ~value;*/
  }

  return true;
}

bool Canvas::DrawLine( int x1, int y1, int x2, int y2, bool isBlack )
{
  int dx,dy,e;
  dx=x2-x1;
  dy=y2-y1;

  if(dx>=0)
    {
      if(dy>=0)
	{
	  if(dx>=dy)
	    {
	      e=dy-dx/2;
	      while(x1<=x2)
		{
		  DrawBit( x1 ,y1, isBlack );
		  if(e>0){y1+=1;e-=dx;}
		  x1+=1;
		  e+=dy;
		}
	    }
	  else
	    {
	      e=dx-dy/2;
	      while(y1<=y2)
		{
		  DrawBit(x1,y1,isBlack);
		  if(e>0){x1+=1;e-=dy;}
		  y1+=1;
		  e+=dx;
		}
	    }
	}
      else /*dy<0 dx>=0;*/
	{
	  dy=-dy;   /* dy=abs(dy)*/

	  if(dx>=dy) /* 8/8 octant*/
	    {
	      e=dy-dx/2;
	      while(x1<=x2)
		{
		  DrawBit(x1,y1,isBlack);
		  if(e>0){y1-=1;e-=dx;}
		  x1+=1;
		  e+=dy;
		}
	    }
	  else            /* 7/8 octant*/
	    {
	      e=dx-dy/2;
	      while(y1>=y2)
		{
		  DrawBit(x1,y1,isBlack);
		  if(e>0){x1+=1;e-=dy;}
		  y1-=1;
		  e+=dx;
		}
	    }
	}
    }
  else /*dx<0*/
    {
      dx=-dx;         /*dx=abs(dx)*/
      if(dy >= 0) /* dy>=0*/
	{
	  if(dx>=dy) /* 4/8 octant*/
	    {
	      e=dy-dx/2;
	      while(x1>=x2)
		{
		  DrawBit(x1,y1,isBlack);
		  if(e>0){y1+=1;e-=dx;}
		  x1-=1;
		  e+=dy;
		}
	    }
	  else            /* 3/8 octant*/
	    {
	      e=dx-dy/2;
	      while(y1<=y2)
		{
		  DrawBit(x1,y1,isBlack);
		  if(e>0){x1-=1;e-=dy;}
		  y1+=1;
		  e+=dx;
		}
	    }
	}
      else               /* dy<0*/
	{
	  dy=-dy;   /* dy=abs(dy)*/
	  if(dx>=dy) /* 5/8 octant*/
	    {
	      e=dy-dx/2;
	      while(x1>=x2)
		{
		  DrawBit(x1,y1,isBlack);
		  if(e>0){y1-=1;e-=dx;}
		  x1-=1;
		  e+=dy;
		}
	    }
	  else            /* 6/8 octant*/
	    {
	      e=dx-dy/2;
	      while(y1>=y2)
		{
		  DrawBit( x1, y1, isBlack );
		  if(e>0){x1-=1;e-=dy;}
		  y1-=1;
		  e+=dx;
		}
	    }
	}
    }
  return true;
}


bool Canvas::DrawRectangle( int x1, int y1, int x2, int y2, bool isBlack )
{
  if ( x1 > x2 || y1 > y2 ) {
    return false;
  }

  DrawLine( x1, y1, x2, y1, true );
  DrawLine( x2, y1, x2, y2, true );
  DrawLine( x1, y2, x2, y2, true );
  DrawLine( x1, y1, x1, y2, true );

  return true;
}

void Canvas::lock( )
{
  pthread_mutex_lock( &zone_mut );
}

void Canvas::unlock()
{
  pthread_mutex_unlock( &zone_mut );
}

void Canvas::Init(  )
{
  device = InitGUIDevice( );
  if ( !device )
    {
      printf( "graphic device is null\n" );
      exit( -1 );
    }

}

