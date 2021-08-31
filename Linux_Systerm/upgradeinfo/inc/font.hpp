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
*������: Ĭ��12���������(12x12����, 12x8 ASCII�ַ�
*	  Ŀǰֻ֧��12�����16��������,֧��8x8����ASCII���ַ�
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
  int CharWidth()		/* ���ص����ַ���(X�����)*/
  {
    return ascii_x;
  };
private:
  int hz_x, ascii_x, y; 			/* ���ֵ�����X��ĵ���*/
  enum FONTTYPE _type;
  MatrixBit asciibit, hzbit;

  static struct FontAttr attrib[];
};

extern Font Font16, Font12;


#endif /* _FONT_HPP_*/
