#pragma implementation "viewcomponent.hpp"
#include "viewcomponent.hpp"

ViewComponent::ViewComponent(int x, int y, bool enabled, bool visible)
{
  pst.x = x;
  pst.y = y;
  isenabled = enabled;
  isvisible = visible;
  /*owner = sender;*/
}

ViewComponent::~ViewComponent()
{

}

void ViewComponent::enable()
{
  isenabled = true;
}

void ViewComponent::disable()
{
  isenabled = false;
}

void ViewComponent::setvisible(bool visible)
{
  isvisible = visible;
}

bool ViewComponent::visible()
{
  return isvisible;
}


void ViewComponent::click()
{

}

void ViewComponent::show ()
{

}

void ViewComponent::setcanvas( Canvas * sender )
{
  if ( sender != NULL ) {
    canv = sender ;
  }
}

void ViewComponent::setfocus(bool state)
{

}

void ViewComponent::setposition( struct Position pst )
{

}

int ViewComponent::GetHight()
{
  return 0;
}
