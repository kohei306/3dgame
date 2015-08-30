#ifndef OBJECT_DRAW_H_
#define OBJECT_DRAW_H_

#include "ObjectState.h"

class ObjectDraw : public ObjectState
{
 public:
  ObjectDraw(){};
  ~ObjectDraw(){};
  
  void set_texture_id(GLuint t_id);
  GLuint get_texture_id();
  void draw_object();
  void set_image_id(ImageID img_id);
  ImageID get_image_id();
  void set_vertex_x(int x);
  void set_vertex_y(int y);
  int get_vertex_x();
  int get_vertex_y();
  void set_size(int size);
  int get_size();
  void init_object(GLuint t_id, ImageID img_id, int x, int y, int size);
  void set_object(ImageID img_id, int x, int y);

 private:
  GLuint texture_id_;
  ImageID image_id_;
  int vertex_x_;
  int vertex_y_;
  int size_;

};

#endif
