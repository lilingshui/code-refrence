#ifndef _FONT_HPP_
#define _FONT_HPP_

#pragma interface

#include "matrixbit.hpp"

enum  FONTTYPE{
  FONT16 = 0, FONT12 = 1, FONT8 = 2,
};

struct FontAttr {
  int hight;
  int hz_width;
  int ascii_width;
  char * const hz_filename;
  char * const ascii_filename;
};

/*****************************************************
*字体类: 默认12点阵的字体(12x12汉字, 12x8 ASCII字符
*	  目前只支持12点阵和16点阵字体,支持8x8点阵ASCII码字符
******************************************************/
class Font {
public:
  Font( enum FONTTYPE type = FONT16 );
  bool TextOut( int x, int y, char * ptext, bool isBlack );
  bool SetFile( char * ascii_filename, char * hz_filename );
  bool SetType( enum FONTTYPE type );
  void SetCanvas( Canvas * canv )
  {
    asciibit.SetCanvas( canv );
    hzbit.SetCanvas( canv );
  };
  enum FONTTYPE GetType( ) { return _type; };
  int GetHight()
  {
    return y;
  };
  int GetHZWidth()
  {
    return hz_x;
  };
  int CharWidth()		/* 返回单个字符宽(X向点数)*/
  {
    return ascii_x;
  };
private:
  int hz_x, ascii_x, y; 			/* 汉字点阵在X向的点数*/
  enum FONTTYPE _type;
  MatrixBit asciibit, hzbit;

  static struct FontAttr attrib[];
};

extern Font Font16, Font12;


#endif /* _FONT_HPP_*/
