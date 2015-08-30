#ifndef BASE_H_
#define BASE_H_

class Base
{
 public:
  virtual ~Base(){};
  enum SeqTrig {STARTKEY = 0,
		CLEAR,
		FAILURE,
		EXIT,
		NONE
  };
  virtual Base* update() = 0;
  virtual void keybord_handler(unsigned char key) = 0;
  virtual void draw() = 0;
  virtual void timer() = 0;
  SeqTrig seq_trig_;
  int is_winner_;
};

#endif
