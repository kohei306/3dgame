#include <fstream>
#include <iostream>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <assert.h>
#include "bmp.h"
#include "FontDraw.h"


void FontDraw::set_texture_id(GLuint t_id) {
  texture_id_ = t_id; 
}

GLuint FontDraw::get_texture_id() { 
  return texture_id_;
}

void FontDraw::draw_font() {
  // glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, get_texture_id());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 100, 0, 100);
  

  double x;
  double y;
  double size_x = 0.07;
  double size_y = 0.17;
  char *fonts = get_str();
  int   i    = 0;
  int	posi = 0;
  while(fonts[i] != '\0') {
    if (fonts[i] == '\n') { 
      set_vertex_y(get_vertex_y() - get_size());
      posi   = 0;
      i++;
      continue;
    }
    x = (double)((int)fonts[i] % 16) * 0.0625;
    y = (double)(1.1666 - (((int)(fonts[i] / 16)) * (0.1666)));
    
    glBegin(GL_QUADS);
    glTexCoord2f(x, y); glVertex2f(get_vertex_x() + get_size() * posi, get_vertex_y());
    glTexCoord2f(x, y + size_y); glVertex2f(get_vertex_x() + get_size() * posi, get_vertex_y() + get_size());
    glTexCoord2f(x + size_x, y + size_y); glVertex2f(get_vertex_x() + get_size() + get_size() * posi, 
						     get_vertex_y() + get_size());
    glTexCoord2f(x + size_x, y); glVertex2f(get_vertex_x() + get_size() + get_size() * posi, get_vertex_y());
    glEnd();
    glFlush();
    i++;
    posi++;
  }
}
void FontDraw::draw_bg() {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, get_texture_id());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 100, 0, 100);

  double x;
  double y;
  double size_x = 0.07;
  double size_y = 0.17;
  set_str(" ");
  char *fonts = get_str();
  x = (double)((int)fonts[0] % 16) * 0.0625;
  y = (double)(1.1666 - (((int)(fonts[0] / 16)) * (0.1666)));
  set_size(5);
  for (int i = 0; i < 21; i++) {
    set_vertex_y(i*5);
    for (int j = 0; j < 21; j++) {
      set_vertex_x(j*5);
    
    glBegin(GL_QUADS);
    glTexCoord2f(x, y); glVertex2f(get_vertex_x(), get_vertex_y());
    glTexCoord2f(x, y + size_y); glVertex2f(get_vertex_x(), get_vertex_y() + get_size());
    glTexCoord2f(x + size_x, y + size_y); glVertex2f(get_vertex_x() + get_size(), 
						     get_vertex_y() + get_size());
    glTexCoord2f(x + size_x, y); glVertex2f(get_vertex_x() + get_size() + get_size(), get_vertex_y());
    glEnd();
    glFlush();
    }
  }
}

void FontDraw::set_str(char *str) {
  str_ = str;
}

char *FontDraw::get_str() { 
  return str_;
}

void FontDraw::set_vertex_x(int x) {
  vertex_x_ = x;
}

void FontDraw::set_vertex_y(int y) {
  vertex_y_ = y;
}

int FontDraw::get_vertex_x() {
  return vertex_x_;
}

int FontDraw::get_vertex_y() {
  return vertex_y_;
}

void FontDraw::set_size(double size) {
  size_ = size;
}

double FontDraw::get_size() {
  return size_;
}

void FontDraw::init_font(GLuint t_id, char *str, int x, int y, int size) {
  texture_id_ = t_id; 
  str_ = str;
  vertex_x_ = x;
  vertex_y_ = y;
  size_ = size;
}

void FontDraw::set_font(char* str, int x, int y) {
  str_ = str;
  vertex_x_ = x;
  vertex_y_ = y;
}

FontDraw *FontDraw::instance() {
  return FontDraw::font_draw_;
}

void FontDraw::create() {
  assert(!FontDraw::font_draw_ && "object FontDraw exists already!!\n");
  FontDraw::font_draw_ = new FontDraw();
}

void FontDraw::destroy() {
  delete FontDraw::font_draw_;
  FontDraw::font_draw_ = NULL;
}
