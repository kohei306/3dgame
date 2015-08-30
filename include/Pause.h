#ifndef PAUSE_H_
#define PAUSE_H_

#include "Base.h"
class FontDraw;

namespace font {
  GLuint tx_id;
}

class Pause : public Base
{
 public:
  Pause();
  ~Pause();
  enum PAUSE_DISP {
    RESTART = 0,
    TITLE
  };

  //update function for Play class
  Base *update();

  //keybord handler
  void keybord_handler(unsigned char key);
  //draw function
  void draw();
  //timer function
  void timer();

  FontDraw *font_draw_;
  PAUSE_DISP pause_disp_;
 
};

#endif
