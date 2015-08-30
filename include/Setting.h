#ifndef SETTING_H_
#define SETTING_H_

#include "Base.h"
class GLUI;
namespace ForSet{
  GLUI *glui;
}

class Setting : public Base
{
 public:
  Setting();
  ~Setting();

  //update function for Base class
  Base *update();

  //keybord handler
  void keybord_handler(unsigned char key);

  //draw function
  void draw();

  //timer function
  void timer();

 private:
  
};

#endif
