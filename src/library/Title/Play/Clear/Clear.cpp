#include <fstream>
#include <iostream>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <assert.h>

//#include "bmp.h"
#include "Game.h"
#include "Play.h"
#include "Pause.h"
#include "Clear.h"
#include "Failure.h"
#include "Title.h"
#include "FontDraw.h"

using namespace std;

//update function for Play class
Base *Clear::update() {
    Base *temp_base = this;
    if (seq_trig_ == STARTKEY) 
      temp_base = Title::instance();
  return temp_base;
  
}

//keybord handler
void Clear::keybord_handler(unsigned char key) {
  switch(key) {
  case 't':
    seq_trig_ = Base::STARTKEY;
    break;
  case 'q': 
  case 'Q':
  case '\033':  // '\033' は ESC の ASCII コード 
    seq_trig_ = Base::EXIT;
    break;    
  default:
    break;
  }
  
}

//draw function
void Clear::draw() {
 FontDraw::create();
  FontDraw *font_draw = FontDraw::instance();
  font_draw->set_texture_id(font::tx_id);
  font_draw->draw_bg();
  font_draw->set_size(5);
  font_draw->set_font("Clear!\nPush t go to TITLE", 0, 60);
  font_draw->draw_font();
  font_draw->destroy();
}

//timer function
void Clear::timer() {
}
