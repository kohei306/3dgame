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

#include "FontDraw.h"
#include "Game.h"
#include "Play.h"
#include "Pause.h"
#include "Clear.h"
#include "Failure.h"
#include "bmp.h"
#include "Title.h"

using namespace std;

Pause::~Pause() {
FontDraw *font_draw = FontDraw::instance();
 font_draw->destroy();
}

Pause::Pause() {
  seq_trig_ = NONE;
 
}

//update function for Play class
Base *Pause::update() {
    Base *temp_base;
   
    if (pause_disp_ == RESTART && seq_trig_ == STARTKEY) {
    temp_base = Game::instance();
    }
    else if (pause_disp_ == TITLE && seq_trig_ == STARTKEY) {
      Game::destroy();
      temp_base = Title::instance();
    }
  else if (seq_trig_ == EXIT)
    exit(0);
  else temp_base = this;

    seq_trig_ = NONE;

  return temp_base;
  
}

//keybord handler
void Pause::keybord_handler(unsigned char key) {

  switch(key) {
  case 't':
    seq_trig_ = Base::STARTKEY;
    break;
  case 'q': 
  case 'Q':
  case '\033':  // '\033' は ESC の ASCII コード 
    seq_trig_ = Base::EXIT;
    break;    
 case 'w':
   pause_disp_ = RESTART;
    break;
  case 'x':
    pause_disp_ = TITLE;
    break;

  default:
    break;
  }

}

//draw function
void Pause::draw() {
  FontDraw::create();
  FontDraw *font_draw = FontDraw::instance();
  font_draw->set_texture_id(font::tx_id);
  font_draw->draw_bg();
  font_draw->set_size(5);
  if (pause_disp_ == RESTART)
    font_draw->set_font("!RESTART\n TITLE", 0, 60);
  if(pause_disp_ == TITLE)
    font_draw->set_font(" RESTART\n!TITLE", 0, 60);
 
  font_draw->draw_font();
  font_draw->destroy();
}

//timer function
void Pause::timer() {
}
