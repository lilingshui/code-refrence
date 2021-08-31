#pragma implementation "screen.hpp"
#include "screen.hpp"

void Screen::JudgeAndSetWindow()
{
	if(!isSetParam)
	{
		static char flag = 1;
		canvas.SetWindowOrig( 0, 104*flag );
		flag = 1-flag;
		show();
		return;
	}
	ViewComponent * tmp = getfocusObj();
	struct Point top = tmp->getposition();
	struct Point bottom;
	bottom.x = top.x = 0;
	bottom.y =  top.y + tmp->GetHight() + 2;

	if ( !canvas.isPointInWindow( top ) || !canvas.isPointInWindow( bottom ) )
	{
		if ( top.y < 104 )
		{
			canvas.SetWindowOrig( 0, 0 );
		}
		else
		{
		canvas.SetWindowOrig( 0, 104 );
		}
		show();
	}
}



void Screen::enable()
{
  Form::enable();
}


void Screen::disable()
{
  Form::disable();
}


void Screen::key_down()
{
  Form::key_down();
}
