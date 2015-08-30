#ifndef OBJECT_STATE_H_
#define OBJECT_STATE_H_

class ObjectState
{
 public:
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
  
  ObjectState(){};
  ~ObjectState(){};
  
  void load_stage(char* filename);
  void set_state(ImageID img_id, int x, int y);
  ImageID get_state(int x, int y);
  void init_states(double enemy_percent,
		   double brick_percent,
		   double fire_up_percent,
		   double bomb_up_percent,
		   int num_players);
  
  ImageID *states_;
  std::vector<int> floor_points_;
  std::vector<int> brick_points_;
  int stage_size_;
};

#endif
