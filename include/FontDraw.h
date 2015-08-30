#ifndef FONT_DRAW_H_
#define FONT_DRAW_H_

class FontDraw

{
 public:
  static FontDraw *instance();
  static void create();
  static void destroy();
  void set_texture_id(GLuint t_id);
  GLuint get_texture_id();
  void draw_font();
  void draw_bg();
  void set_str(char *str);
  char *get_str();
  void set_vertex_x(int x);
  void set_vertex_y(int y);
  int get_vertex_x();
  int get_vertex_y();
  void set_size(double size);
  double get_size();
  void init_font(GLuint t_id, char* str, int x, int y, int size);
  void set_font(char* str, int x, int y);

 private:
  FontDraw(){};
  ~FontDraw(){};

  static FontDraw* font_draw_;
  GLuint texture_id_;
  char *str_;
  int vertex_x_;
  int vertex_y_;
  double size_;

};

#endif
