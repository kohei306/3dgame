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

using namespace std;

 
Play::Play(){
   seq_trig_ = NONE;
}
Play::~Play(){}

//update function for Play class
Base *Play::update() {
  Base *temp_base = this;
  if (seq_trig_ == STARTKEY)
    temp_base = new Pause;
  else if (seq_trig_ == CLEAR)
    temp_base = new Clear;
  else if(seq_trig_ == FAILURE)
    temp_base = new Failure;
  else if (seq_trig_ == EXIT)
    exit(0);
  else temp_base = this;
  return temp_base;
}

//keybord handler
void Play::keybord_handler(unsigned char key) {
 
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
void Play::draw() {

}

//timer function
void Play::timer() {
}
