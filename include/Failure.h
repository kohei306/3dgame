#ifndef FAILURE_H_
#define FAILURE_H_

#include "Base.h"

class Failure : public Base
{
 public:
  //update function for Play class
  Base *update();

  //keybord handler
  void keybord_handler(unsigned char key);
  //draw function
  void draw();
  //timer function
  void timer();
 
};

#endif
