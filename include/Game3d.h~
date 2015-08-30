#ifndef GAME_H_
#define GAME_H_

#include "Base.h"

namespace game_init {
  enum PLAYER_MODE {
    ONE_PLAYER = 0,
    TWO_PLAYER
  };
  enum GAME_LEVEL {
    BEGGINER = 0,
    INTERMEDIATE,
    ADVANCED
  };
  PLAYER_MODE player_mode;
  GAME_LEVEL game_level;
}

namespace object {
  GLuint tx_id;
}

struct Bombs;
struct PlayerState
{
  int fire_level_;
  int num_bombs_;
  int current_bombs_;
};


class Game : public Base
{
 public:
  static Game *instance();
  static void create();
  static void destroy();
  enum ImageID{ PLAYER1= 0, 
		PLAYER2,
		BOMB_UP,
		FIRE_UP,
		HORI_FIRE,
		VER_FIRE,
		ENEMY,
		WALL,
		BRICK,
		FLOOR,
		BOMB,
		CROSS_FIRE,
		BRICK_FIRE_UP,
		BRICK_BOMB_UP
	};
  enum ENEMY_MOVE{ UP = 0,
		   DOWN,
		   LEFT,
		   RIGHT
  };
  //update function for Play class
  Base *update();

  //keybord handler
  void keybord_handler(unsigned char key);

  //draw function
  void draw();

  //timer function
  void timer();

  void enemy_move();
  void bombs_blast();
  void flush_fire();
  bool cleared();

  int get_num_bombs(ImageID Player_id);
  void set_texture_id(GLuint t_id);
  GLuint get_texture_id();
  void draw_object();
  void draw_all_objects();
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
  

  //stage data handle function
  void load_stage(char* filename);
  void set_state(ImageID img_id, int x, int y);
  ImageID get_state(int x, int y);
  void get_player_position(ImageID img_id, int& x, int&y);
  void save_enemy_position();
  void init_states(double enemy_percent,
		   double brick_percent,
		   double fire_up_percent,
		   double bomb_up_percent,
		   int num_players);
  void init_game(game_init::PLAYER_MODE player_mode, 
		 game_init::GAME_LEVEL game_level);

  // game satatus variables
  std::vector<ImageID> states_;
  std::vector<int> floor_points_;
  std::vector<int> brick_points_;
  std::vector<int> enemy_points_;
  std::vector<Bombs> bombs_;
  int stage_size_;
  PlayerState player1_state_;
  PlayerState player2_state_;
  bool bomb_blasted_;
  int flush_cnt_;
 private:
  Game();
  ~Game();

  //draw variables
  GLuint texture_id_;
  ImageID image_id_;
  int vertex_x_;
  int vertex_y_;
  int size_;
  

  static Game *game_;

};

struct Bombs 
{
  int x_;
  int y_;
  int player_id_;
  int set_time_;
  int fire_level_;

};


#endif
