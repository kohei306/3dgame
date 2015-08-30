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
#include "Title.h"
#include "Game.h"
#include "Play.h"
#include "Pause.h"
#include "Clear.h"
#include "Failure.h"
#include "FontDraw.h"
#include "Setting.h"

using namespace std;

Title::Title(){
   seq_trig_ = NONE;
}
Title::~Title(){}

//update function for Play class
Base *Title::update() {
  Base *temp_base = this;
  if (title_disp_ == PLAY && seq_trig_ == STARTKEY) {
    Game::create();
    temp_base = Game::instance();
  }
  else if (title_disp_ == SETTING && seq_trig_ == STARTKEY) {
    temp_base = new Setting;
  }
  else {
    temp_base = this;
  }
  seq_trig_ = NONE;
  return temp_base;
}

//keybord handler
void Title::keybord_handler(unsigned char key) {
 
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
    title_disp_ = PLAY;
    break;
  case 'x':
    title_disp_ = SETTING;
    break;
  default : 
    break;
  }
}

//draw function
void Title::draw() {
  FontDraw::create();
  FontDraw *font_draw = FontDraw::instance();
  font_draw->set_texture_id(font::tx_id);
  font_draw->draw_bg();
  font_draw->set_size(5);
  if (title_disp_ == PLAY)
    font_draw->set_font("!PLAY\n Setting", 0, 60);
  if(title_disp_ == SETTING)
    font_draw->set_font(" PLAY\n!Setting", 0, 60);
 
  font_draw->draw_font();
  font_draw->destroy();

}

//timer function
void Title:: timer() {
}
 
Title *Title::instance() {
  return Title::title_;
}

void Title::create() {
  assert(!title_ && "object Title exists already!!\n");
  title_ = new Title();
}

void Title::destroy() {
  delete title_;
  title_ = NULL;
}

