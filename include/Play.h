#ifndef PLAY_H_
#define PLAY_H_


class Play: public Base
{
 public:
  Play();
  ~Play();
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
