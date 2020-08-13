#ifndef _MATRIXBIT_HPP_
#define _MATRIXBIT_HPP_

#pragma interface

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "canvas.hpp"

class MatrixBit {
public:
  MatrixBit( int X, int Y ) {
    SetXYBits( X, Y );
    canvas = NULL;
  }
  ~MatrixBit( );
  void SetXYBits( int X, int Y );
  bool SetFile( char * filename );
  void SetOffset( int offset );
  void SetCanvas( Canvas * canv )
  {
    canvas = canv;
  };
  int GetChars( ) {
    return ichars;
  };
  int GetX () {
    return iXbits;
  };
  int GetY() {
    return iYbits;
  };
  bool Draw( int x, int y, bool isBlack );
private:
  int iXbits;
  int iYbits;
  int iXchars;
  int ichars;

  int ioffset;
  char * _filename;

  unsigned char * matrix;
  Canvas * canvas;
  bool isload;

  bool GetMatrix();
};

#endif /* _MATRIXBIT_HPP_*/
