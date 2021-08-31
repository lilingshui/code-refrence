#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#pragma interface

#include "form.hpp"
#include "canvas.hpp"

class Screen : public Form
{
public:
	Screen( Form * p = NULL ):Form( p )
	{
		canvas.SetSize( 0, 160, 0, 104 );
		canvas.SetOrig( 0, 0 );
		isSetParam = true;
	};

	virtual void key_down();
	void enable();
	void disable();
	~Screen(){};

	void JudgeAndSetWindow(); 	/* 2005��6�����, Ϊ����ӵ���������ʾ�ؼ�����*/

  	bool isSetParam;

};


#endif /* _SCREEN_HPP_*/
