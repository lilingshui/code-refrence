#pragma implementation "form.hpp"
#include "form.hpp"
#include <iostream>

Form::Form(Form*  p)
{
  taborder = 0;
  if (p) parent = p;
  else parent = this;
  isfromchild = false;
  succeeded = false;
  hint[0] = '\0';
}

Form::~Form()
{
  components.clear();
  tabcomponents.clear();
}


void Form::show()
{

  Canvas::lock();

  canvas.clear();

  std::vector< ViewComponent *  >::iterator curr;
  for ( curr = components.begin(); curr != components.end(); curr ++){
     if ((*curr)->visible()){
       (*curr)->show();
     }
  }
  canvas.Sync();

  Canvas::unlock();
}


Form* Form::current = NULL;
int Form::iKeyNullCount = 500000;


typedef void ( Form::*FormFunc)();

void Form::keydown(enum KEYS keystate)
{
  static FormFunc KeyFuncMap[] =
    {
      &Form::key_null,
      &Form::key_up,     &Form::key_down,
      &Form::key_cancel, &Form::key_enter,
      &Form::key_left,   &Form::key_right,
    };

  if ( keystate != KEY_NULL ) {
    iKeyNullCount  = 0;
  }
  else {
    iKeyNullCount ++;
  }

  (current->*KeyFuncMap[keystate])();

/*   switch (keystate) {*/
/*   case UPWARD :*/
/*     key_up();*/
/*     break;*/
/*   case DOWNWARD :*/
/*     key_down();*/
/*     break;*/
/*   case LEFTWARD :*/
/*     key_left();*/
/*     break;*/
/*   case RIGHTWARD :*/
/*     key_right();*/
/*     break;      */
/*   case CANCEL :*/
/*     key_cancel();*/
/*     break;*/
/*   case ENTER :*/
/*     key_enter();*/
/*     break;*/
/*   default:*/
/*     break;*/
/*   }*/
}

void Form::addcomponent( ViewComponent *  cmpnt, bool tab)
{
  if ( cmpnt )  {
    cmpnt->setcanvas( &canvas );
    components.push_back(cmpnt);
  }
  else {
    std::cout << "component is NULL!" << std::endl;
  }

  if (tab){
    tabcomponents.push_back(cmpnt);
  }

}

void Form::setparent(  Form  *  p )
{
  parent = p;
}

void Form::sethint( const char * txt )
{
  if ( txt == 0 )
    {
      return;
    }

  strncpy( hint, txt, MAX_HINT_LEN );
  hint[MAX_HINT_LEN - 1] = '\0';
}


void Form::settaborder(unsigned int order)
{
  if (order >= tabcomponents.size()) {
    /*should do something;   */
    return;
  }
  std::vector< ViewComponent *  >::iterator curr;
  for ( curr = tabcomponents.begin(); curr!= tabcomponents.end(); curr ++ ) {
    (*curr)->setfocus(false);
  }
  taborder = order;
  tabcomponents[order]->setfocus(true);
}

void Form::nofocus()
{
  tabcomponents[taborder]->setfocus(false);
}

void Form::delcomponent( ViewComponent *  cmpnt)
{
  if ( cmpnt )
    {
      std::vector< ViewComponent *  >::iterator curr;
      for ( curr = tabcomponents.begin(); curr!= tabcomponents.end(); curr ++ )
	{
	  if( ( *curr ) == cmpnt )
	    {
	      tabcomponents.erase( curr );
	      break;
	    }
	}
    }
}

unsigned int Form::gettaborder()
{
  return taborder;
}

ViewComponent * Form::getfocusObj()
{
  if( tabcomponents.size() == 0 ) {
    return NULL;
  }

  return tabcomponents[taborder];
}

bool Form::IsLastShow()
{
	if(tabcomponents.size()==0)
	{
		return true;
	}
	else if(++taborder>=tabcomponents.size())
	{
		taborder = tabcomponents.size()-1;
		settaborder(taborder);
		return true;
	}
	else
	{
		settaborder(taborder);
		return false;
	}
}

bool Form::IsFirstShow()
{
	if(tabcomponents.size()==0 )
	{
		return true;
	}
	else if(taborder<=0)
	{
		taborder = 0;
		settaborder(taborder);
		return true;
	}
	else
	{
		taborder--;
		settaborder(taborder);
		return false;
	}
}

void Form::key_enter()
{
   if (tabcomponents.size() > 0) {
      tabcomponents[taborder]->click();
    }
}

void Form::key_cancel()
{
  disable();
}



void Form::key_down ()
{
  if (tabcomponents.size() == 0){
    return;
  }

  tabcomponents[taborder]->disable() ;
  taborder++;
  if (taborder >= tabcomponents.size()){
    taborder = 0;
  }
  tabcomponents[taborder]->enable();

  /*  JudgeAndSetWindow();*/

  show ();
}

void Form::key_up ()
{
  if (tabcomponents.size() == 0){
    return;
  }

  tabcomponents[taborder]->disable();
  if (taborder > 0) {
    taborder--;
  }
  else {
    taborder = tabcomponents.size() - 1;
  }
  tabcomponents[taborder]->enable();

  /*  JudgeAndSetWindow();*/

  show();
}

void Form::key_left()
{
	key_up();
}

void Form::key_right()
{
	key_down();
}

void Form::enable()
{
  Form::current = this;
  show();
}

void Form::disable()
{
  Form::current = parent;
  /*close();*/
  Form::current->enable();
}

void Form::clearcomponents()
{
  components.clear();
  tabcomponents.clear();
}

/****************************************************
* 关闭窗体并将form 所占空间释放掉
* 注意: 此函数只能在顶层窗口退出后才能调用!!!!!!
****************************************************/
void Form::CloseForm( Form * form )
{
  delete form;
  form = 0;
}

