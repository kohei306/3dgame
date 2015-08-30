#ifndef GAME3D_H_
#define GAME3D_H_

#include "Base.h"
#include "DrawData.h"
#include <list>
namespace game3d_init {
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
  GAME_LEVEL game3d_level;
  int num_blocks;
  int num_obstacles_in_block;
  int num_enemies;
}

namespace draw_stuff{
  GLuint tx_id;
  GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
  GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
  GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };
  GLfloat yellow[] = { 1, 1, 0, 1.0 };
  GLfloat ground[][4] = {
    { 0.6, 0.6, 0.6, 1.0 },
    { 0.3, 0.3, 0.3, 1.0 }
  };
}

enum ObstacleID {
  BRICK = 0,
  WALL,
  NUMOBSTACLEID};

class Target 
{
 public: 
  
  virtual ~Target(){};
  
};

class Obstacle : public Target
{
 public:

  int x_;
  int y_;
  int z_;
  ObstacleID id_;  
  double time_;
};

class Player;
class Missile 
{
 public :
 Missile() : v_(0, 0, 0) {};
  Vertex v_;
  Target *target_;
  double time_;
  double speed_;
  Player *whose_;
  double theta_;
  double phi_;
  void move();
};

class Player : public Target
{
 public:
  double x_;
  double y_;
  double z_;
  double theta_; //this means the front direction(x,z) of player 
  double phi_; // this means the front direction(x,y) of player
  double posture_theta_;
  double hp_;
  double time_;
  double v0_;
  double y_before_jump_;
  unsigned time_for_animation_;
  std::list<Missile*> missiles_;

  //these are to mimic enemy
  enum Input{
    FORWARD = 0,
    RIGHT,
    LEFT,
    BACK,
    JUMP,
    FIRE,
    NUMBER_OF_INPUTS
  };
  
  Input pre_action_;
  unsigned seed_for_action_;
  Input next_action(Input pre_action);
  void action(Input input);
  void face_to_player();

};

struct LookAtCordi {
  double posi_x_;
  double posi_y_;
  double posi_z_;
  double lookat_x_;
  double lookat_y_;
  double lookat_z_;
};

class Batch;
class GraphicDatabase;

class DrawTree {

 public:

  Node *root_;
  double time_[Node::NUMOFSTATES];
  void init_root();
  void set_root();
  
};


class Game3d : public Base
{
 public:
  enum ObType {
    NONE = -2,
    FLOOR = -1,
    PLAYER = 0,
    OBSTACLE
  };
  static Game3d *instance();
  static void create();
  static void destroy();
  //update function for Play class
  Base *update();

  //keybord handler
  void keybord_handler(unsigned char key);

  //draw function
  void draw();

  //timer function
  void timer();

  void init_stage();
  void set_lookat(LookAtCordi *lookat, const Player &player);
  void gravity();
  int collid_test(double now_x, double now_y,  double now_z,
  		   double next_x, double next_y, double next_z,
		  ObType objest, int idx = -1);
  void init_batch();
  void init_enemies();
  void load_graphic_database();
  Target *get_target();
  void erase_obstacle(int idx) {
    obstacles_.erase(obstacles_.begin() + idx);
  };
  void enemies_action();
  Player get_player1(){
    return player1_;
  };
  
 private:
  Game3d();
  ~Game3d();

  Player player1_,player2_;
  std::vector<Player*> enemies_;
  std::vector<Obstacle> obstacles_;
  GraphicDatabase *graphic_database_;
  //draw variables
  static Game3d *game3d_;
  DrawTree drawtree_;

};


#endif
