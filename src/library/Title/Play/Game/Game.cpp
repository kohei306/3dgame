#include <fstream>
#include <iostream>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glui.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <assert.h>
#include <time.h>
//#include "bmp.h"
#include "Game.h"
#include "Play.h"
#include "Pause.h"
#include "Clear.h"
#include "Failure.h"

using namespace std;

pthread_mutex_t mutex_for_states_ = PTHREAD_MUTEX_INITIALIZER;

//update function for Play class
Base *Game::update() {

  Base *temp_base = this;
  if (seq_trig_ == STARTKEY)
    temp_base = new Pause;
  else if (seq_trig_ == CLEAR) {
    temp_base = new Clear;
    Game::destroy();
  }
  else if(seq_trig_ == FAILURE) {
    temp_base = new Failure;
    int is_player1;
    int is_player2;
    get_player_position(PLAYER1, is_player1, is_player1);
    get_player_position(PLAYER2, is_player2, is_player2);    
    if (is_player1 == 0) 
      temp_base->is_winner_ = 2;  
    else
      temp_base->is_winner_ = 1;
    Game::destroy();
  }
  else if (seq_trig_ == EXIT)
    exit(0);
  else temp_base = this;

  seq_trig_ = NONE;
  return temp_base;
}

//keybord handler
void Game::keybord_handler(unsigned char key) {
  
  int player1_x, player1_y, player2_x, player2_y;
  get_player_position(PLAYER1, player1_x, player1_y);
  get_player_position(PLAYER2, player2_x, player2_y);
  Bombs bomb;
  vector<Bombs>::reverse_iterator bmit;
  switch(key) {
  case 't':
    seq_trig_ = Base::STARTKEY;
    break;
  case 'q': 
  case 'Q':
  case '\033':  // '\033' は ESC の ASCII コード 
    seq_trig_ = Base::EXIT;
    break;    
 case 'a':
   if (player1_x > 0) {
     if (get_state(player1_x - 1, player1_y) == FLOOR) {
       set_state(PLAYER1, player1_x - 1, player1_y);
       set_state(FLOOR, player1_x, player1_y);
     }
     if (get_state(player1_x - 1, player1_y) == FIRE_UP) {
       player1_state_.fire_level_++;
       set_state(PLAYER1, player1_x - 1, player1_y);
       set_state(FLOOR, player1_x, player1_y);
     }
     if (get_state(player1_x - 1, player1_y) == BOMB_UP) {
       player1_state_.num_bombs_++;
       set_state(PLAYER1, player1_x - 1, player1_y);
       set_state(FLOOR, player1_x, player1_y);
     }
   }
    else {
      bmit = bombs_.rbegin();
      while(bmit != bombs_.rend()) {
	if (bmit->player_id_ == 1) {
	  int x = bmit->x_ - 1;
	  int y = bmit->y_;
	  if (get_state(x, y) == FLOOR) {
	    set_state(PLAYER1, x, y);
	  }
	  if (get_state(x, y) == FIRE_UP) {
	    player1_state_.fire_level_++;
	    set_state(PLAYER1, x, y);
	  }
	  if (get_state(x, y) == BOMB_UP) {
	    player1_state_.num_bombs_++;
	    set_state(PLAYER1, x, y);
	  }
	  break;
	}
	++bmit;
      }
    }
   break;
  case 'd':
    if (player1_x > 0) {
      if (get_state(player1_x + 1, player1_y) == FLOOR) {
	set_state(PLAYER1, player1_x + 1, player1_y);
	set_state(FLOOR, player1_x, player1_y);
      }
     if (get_state(player1_x + 1, player1_y) == FIRE_UP) {
       player1_state_.fire_level_++;
       set_state(PLAYER1, player1_x + 1, player1_y);
       set_state(FLOOR, player1_x, player1_y);
     }
     if (get_state(player1_x + 1, player1_y) == BOMB_UP) {
       player1_state_.num_bombs_++;
       set_state(PLAYER1, player1_x + 1, player1_y);
       set_state(FLOOR, player1_x, player1_y);
     }

    }
    else {
      bmit = bombs_.rbegin();
      while(bmit != bombs_.rend()) {
	if (bmit->player_id_ == 1) {
	  int x = bmit->x_ + 1;
	  int y = bmit->y_;
	  if (get_state(x, y) == FLOOR) {
	    set_state(PLAYER1, x, y);
	  }
	  if (get_state(x, y) == FIRE_UP) {
	    player1_state_.fire_level_++;
	    set_state(PLAYER1, x, y);
	  }
	  if (get_state(x, y) == BOMB_UP) {
	    player1_state_.num_bombs_++;
	    set_state(PLAYER1, x, y);
	  }
	  break;
	}
	++bmit;
      }
    }
    break;
  case 'w':
    if (player1_x > 0) {
      if (get_state(player1_x, player1_y + 1) == FLOOR) {
	set_state(PLAYER1, player1_x, player1_y + 1);
	set_state(FLOOR, player1_x, player1_y);
      } 
     if (get_state(player1_x, player1_y + 1) == FIRE_UP) {
       player1_state_.fire_level_++;
       set_state(PLAYER1, player1_x, player1_y + 1);
       set_state(FLOOR, player1_x, player1_y);
     }
     if (get_state(player1_x, player1_y + 1) == BOMB_UP) {
       player1_state_.num_bombs_++;
       set_state(PLAYER1, player1_x, player1_y + 1);
       set_state(FLOOR, player1_x, player1_y);
     }
    }
    else {
      bmit = bombs_.rbegin();
      while(bmit != bombs_.rend()) {
	if (bmit->player_id_ == 1) {
	  int x = bmit->x_;
	  int y = bmit->y_ + 1;
	  if (get_state(x, y) == FLOOR) {
	    set_state(PLAYER1, x, y);
	  }
	  if (get_state(x, y) == FIRE_UP) {
	    player1_state_.fire_level_++;
	    set_state(PLAYER1, x, y);
	  }
	  if (get_state(x, y) == BOMB_UP) {
	    player1_state_.num_bombs_++;
	    set_state(PLAYER1, x, y);
	  }
	  break;
	}
	++bmit;
      }
    }
    break;
  case 'x':
    if (player1_x > 0) {
      if (get_state(player1_x, player1_y - 1) == FLOOR) {
	set_state(PLAYER1, player1_x, player1_y - 1);
	set_state(FLOOR, player1_x, player1_y);
      }
     if (get_state(player1_x, player1_y - 1) == FIRE_UP) {
       player1_state_.fire_level_++;
       set_state(PLAYER1, player1_x, player1_y - 1);
       set_state(FLOOR, player1_x, player1_y);
     }
     if (get_state(player1_x, player1_y - 1) == BOMB_UP) {
       player1_state_.num_bombs_++;
       set_state(PLAYER1, player1_x, player1_y - 1);
       set_state(FLOOR, player1_x, player1_y);
     }

    }
    else {
      bmit = bombs_.rbegin();
      while(bmit != bombs_.rend()) {
	if (bmit->player_id_ == 1) {
	  int x = bmit->x_;
	  int y = bmit->y_ - 1;
	  if (get_state(x, y) == FLOOR) {
	    set_state(PLAYER1, x, y);
	  }
	  if (get_state(x, y) == FIRE_UP) {
	    player1_state_.fire_level_++;
	    set_state(PLAYER1, x, y);
	  }
	  if (get_state(x, y) == BOMB_UP) {
	    player1_state_.num_bombs_++;
	    set_state(PLAYER1, x, y);
	  }
	  break;
	}
	++bmit;
      }
    }
    break;
  case 's':
    if (player1_state_.num_bombs_ > player1_state_.current_bombs_) {
      player1_state_.current_bombs_++;
      set_state(BOMB, player1_x, player1_y);
      bomb.x_ = player1_x;
      bomb.y_ = player1_y;
      bomb.player_id_ = 1;
      bomb.set_time_ = time(NULL);
      bomb.fire_level_ = player1_state_.fire_level_;
      bombs_.push_back(bomb);
    }
    break;
  case 'j':
   if (player2_x > 0) {
     if (get_state(player2_x - 1, player2_y) == FLOOR) {
       set_state(PLAYER2, player2_x - 1, player2_y);
       set_state(FLOOR, player2_x, player2_y);
     }
     if (get_state(player2_x - 1, player2_y) == FIRE_UP) {
       player2_state_.fire_level_++;
       set_state(PLAYER2, player2_x - 1, player2_y);
       set_state(FLOOR, player2_x, player2_y);
     }
     if (get_state(player2_x - 1, player2_y) == BOMB_UP) {
       player2_state_.num_bombs_++;
       set_state(PLAYER2, player2_x - 1, player2_y);
       set_state(FLOOR, player2_x, player2_y);
     }
   }
    else {
      bmit = bombs_.rbegin();
      while(bmit != bombs_.rend()) {
	if (bmit->player_id_ == 2) {
	  int x = bmit->x_ - 1;
	  int y = bmit->y_;
	  if (get_state(x, y) == FLOOR) {
	    set_state(PLAYER2, x, y);
	  }
	  if (get_state(x, y) == FIRE_UP) {
	    player2_state_.fire_level_++;
	    set_state(PLAYER2, x, y);
	  }
	  if (get_state(x, y) == BOMB_UP) {
	    player2_state_.num_bombs_++;
	    set_state(PLAYER2, x, y);
	  }
	  break;
	}
	++bmit;
      }
    }
    break;
  case 'l':
    if (player2_x > 0) {
      if (get_state(player2_x + 1, player2_y) == FLOOR) {
	set_state(PLAYER2, player2_x + 1, player2_y);
	set_state(FLOOR, player2_x, player2_y);
      }
     if (get_state(player2_x + 1, player2_y) == FIRE_UP) {
       player2_state_.fire_level_++;
       set_state(PLAYER2, player2_x + 1, player2_y);
       set_state(FLOOR, player2_x, player2_y);
     }
     if (get_state(player2_x + 1, player2_y) == BOMB_UP) {
       player2_state_.num_bombs_++;
       set_state(PLAYER2, player2_x + 1, player2_y);
       set_state(FLOOR, player2_x, player2_y);
     }

    }
    else {
      bmit = bombs_.rbegin();
      while(bmit != bombs_.rend()) {
	if (bmit->player_id_ == 2) {
	  int x = bmit->x_ + 1;
	  int y = bmit->y_;
	  if (get_state(x, y) == FLOOR) {
	    set_state(PLAYER2, x, y);
	  }
	  if (get_state(x, y) == FIRE_UP) {
	    player2_state_.fire_level_++;
	    set_state(PLAYER2, x, y);
	  }
	  if (get_state(x, y) == BOMB_UP) {
	    player2_state_.num_bombs_++;
	    set_state(PLAYER2, x, y);
	  }
	  break;
	}
	++bmit;
      }
    }
  break;
  case 'i':
    if (player2_x > 0) {
      if (get_state(player2_x, player2_y + 1) == FLOOR) {
	set_state(PLAYER2, player2_x, player2_y + 1);
	set_state(FLOOR, player2_x, player2_y);
      } 
     if (get_state(player2_x, player2_y + 1) == FIRE_UP) {
       player2_state_.fire_level_++;
       set_state(PLAYER2, player2_x, player2_y + 1);
       set_state(FLOOR, player2_x, player2_y);
     }
     if (get_state(player2_x, player2_y + 1) == BOMB_UP) {
       player2_state_.num_bombs_++;
       set_state(PLAYER2, player2_x, player2_y + 1);
       set_state(FLOOR, player2_x, player2_y);
     }
    }
    else {
      bmit = bombs_.rbegin();
      while(bmit != bombs_.rend()) {
	if (bmit->player_id_ == 2) {
	  int x = bmit->x_;
	  int y = bmit->y_ + 1;
	  if (get_state(x, y) == FLOOR) {
	    set_state(PLAYER2, x, y);
	  }
	  if (get_state(x, y) == FIRE_UP) {
	    player2_state_.fire_level_++;
	    set_state(PLAYER2, x, y);
	  }
	  if (get_state(x, y) == BOMB_UP) {
	    player2_state_.num_bombs_++;
	    set_state(PLAYER2, x, y);
	  }
	  break;
	}
	++bmit;
      }
    }
    break;
  case 'm':
    if (player2_x > 0) {
      if (get_state(player2_x, player2_y - 1) == FLOOR) {
	set_state(PLAYER2, player2_x, player2_y - 1);
	set_state(FLOOR, player2_x, player2_y);
      }
     if (get_state(player2_x, player2_y - 1) == FIRE_UP) {
       player2_state_.fire_level_++;
       set_state(PLAYER2, player2_x, player2_y - 1);
       set_state(FLOOR, player2_x, player2_y);
     }
     if (get_state(player2_x, player2_y - 1) == BOMB_UP) {
       player2_state_.num_bombs_++;
       set_state(PLAYER2, player2_x, player2_y - 1);
       set_state(FLOOR, player2_x, player2_y);
     }

    }
    else {
      bmit = bombs_.rbegin();
      while(bmit != bombs_.rend()) {
	if (bmit->player_id_ == 2) {
	  int x = bmit->x_;
	  int y = bmit->y_ - 1;
	  if (get_state(x, y) == FLOOR) {
	    set_state(PLAYER2, x, y);
	  }
	  if (get_state(x, y) == FIRE_UP) {
	    player2_state_.fire_level_++;
	    set_state(PLAYER2, x, y);
	  }
	  if (get_state(x, y) == BOMB_UP) {
	    player2_state_.num_bombs_++;
	    set_state(PLAYER2, x, y);
	  }
	  break;
	}
	++bmit;
      }
    }
    break;
  case 'k':
    if (player2_state_.num_bombs_ > player2_state_.current_bombs_) {
      player2_state_.current_bombs_++;
      set_state(BOMB, player2_x, player2_y);
      bomb.x_ = player2_x;
      bomb.y_ = player2_y;
      bomb.player_id_ = 2;
      bomb.set_time_ = time(NULL);
      bomb.fire_level_ = player2_state_.fire_level_;
      bombs_.push_back(bomb);
    }
    break;
  default:
    break;
  }
}

//draw function
void Game::draw() {
  set_texture_id(object::tx_id);
  draw_all_objects();
}


void Game::enemy_move() {
  save_enemy_position();
  ENEMY_MOVE enemy_move;
  vector<int>::iterator it;
  vector<int> floor_dires; 
  bool flag = false;
  for (it = enemy_points_.begin(); it != enemy_points_.end(); ++it) {
   
    floor_dires.clear();
    int x = *it % 21;
    int y = *it / 21;
    
    if (get_state(x, y + 1) == Game::FLOOR)
      floor_dires.push_back(0);
    if (get_state(x, y - 1) == Game::FLOOR)
      floor_dires.push_back(1);
    if (get_state(x - 1, y) == Game::FLOOR)
      floor_dires.push_back(2);
    if (get_state(x + 1, y) == Game::FLOOR)
      floor_dires.push_back(3);
   
    int sum_of_weights = 0;
    int weight = 50 * (4 - floor_dires.size());
    int weights[4] = {10, 10, 10, 10};

    for (int i = 0; i < floor_dires.size(); i++) {

      switch (static_cast<Game::ENEMY_MOVE>(floor_dires[i])) {
      case Game::UP:
	weights[Game::UP] = weight;
	break;
      case Game::DOWN:
	weights[Game::DOWN] = weight;
	break;
      case Game::LEFT:
	weights[Game::LEFT] = weight;
	break;
      case Game::RIGHT:
	weights[Game::RIGHT] = weight;
	break;
      }

    }
    

    for (int j = 0; j < 4; j++) {
      sum_of_weights += weights[j];
    }
    //   fprintf(stderr, "sum_of_weights:%d\n", sum_of_weights);   
    int idx = rand() % (sum_of_weights + 1);
    for (int k = 0; k < 4; k++) {
      if (idx < weights[k]) {
	idx = k;
	//	fprintf(stderr, "BREAK!!\n");
	break;
      }
      idx -= weights[k];
    }
    //    fprintf(stderr, "sum_of_weights:%d idx:%d\n", sum_of_weights, idx);   
    enemy_move = static_cast<Game::ENEMY_MOVE>(idx);

    switch (enemy_move) {
    case Game::UP:
      y++;
      break;
    case Game::DOWN:
      y--;
      break;
    case Game::LEFT:
      x--;
      break;
    case Game::RIGHT:
      x++;
      break;
    default :
      break;
    }
    //    fprintf(stderr, "x:%d y:%d\n", x, y);      
    if (get_state(x, y) == Game::FLOOR) {
   
      set_state(ENEMY, x, y);
      int tmp_x = (int)*it % 21;
      int tmp_y = (int)*it / 21;
      set_state(FLOOR, tmp_x, tmp_y);
    } 
    if (get_state(x, y) ==Game::PLAYER1) {
      set_state(ENEMY, x, y);
      int player1_is_alive;
      get_player_position(Game::PLAYER1, player1_is_alive, player1_is_alive);
      if (!player1_is_alive)
	seq_trig_ = FAILURE;
      int tmp_x = (int)*it % 21;
      int tmp_y = (int)*it / 21;
      set_state(FLOOR, tmp_x, tmp_y);      
    }
    if (get_state(x, y) == Game::PLAYER2) {
      set_state(ENEMY, x, y);
      int player2_is_alive;
      get_player_position(Game::PLAYER2, player2_is_alive, player2_is_alive);
      if (!player2_is_alive)
      seq_trig_ = FAILURE;
      int tmp_x = (int)*it % 21;
      int tmp_y = (int)*it / 21;
      set_state(FLOOR, tmp_x, tmp_y);
    }
    
    
  }

}

void Game::bombs_blast() {
  vector<Bombs>::iterator it;
  for (it = bombs_.begin(); it != bombs_.end(); ++it) {
    if ((time(NULL) - it->set_time_) > 5) {
      int x = it->x_;
      int y = it->y_;
      int fire = it->fire_level_;
      if (fire > 19)
	fire = 19;

      for ( int i = 1; i <= fire; i++) {
	switch (get_state(x - i, y)) {
	case BRICK :
	case FLOOR :
	case ENEMY :
	  set_state(HORI_FIRE, x - i, y);
	  break;
	case BRICK_FIRE_UP :
	  set_state(FIRE_UP, x - i, y);
	  break;
	case BRICK_BOMB_UP :
	  set_state(BOMB_UP, x - i, y);
	  break;
	case PLAYER1 : 
	  set_state(HORI_FIRE, x - i, y);
	  seq_trig_ = FAILURE;
	  break;
	case PLAYER2 : 
	  set_state(HORI_FIRE, x - i, y);
	  seq_trig_ = FAILURE;
	  break;
	}
	switch (get_state(x, y + i)) {
	case BRICK :
	case FLOOR :
	case ENEMY :
	  set_state(VER_FIRE, x, y + i);
	  break;
	case BRICK_FIRE_UP :
	  set_state(FIRE_UP, x, y + i);
	  break;
	case BRICK_BOMB_UP :
	  set_state(BOMB_UP, x, y + i);
	  break;
	case PLAYER1 : 
	  set_state(VER_FIRE, x, y + i);
	  seq_trig_ = FAILURE;
	  break;
	case PLAYER2 : 
	  set_state(VER_FIRE, x, y + i); 
	  seq_trig_ = FAILURE;
	  break;
	}
	switch (get_state(x + i, y)) {
	case BRICK :
	case FLOOR :
	case ENEMY :
	  set_state(HORI_FIRE, x + i, y);
	  break;
	case BRICK_FIRE_UP :
	  set_state(FIRE_UP, x + i, y);
	  break;
	case BRICK_BOMB_UP :
	  set_state(BOMB_UP, x + i, y);
	  break;
	case PLAYER1 : 
	  set_state(HORI_FIRE, x + i, y);
	  seq_trig_ = FAILURE;
	  break;
	case PLAYER2 : 
	  set_state(HORI_FIRE, x + i, y);
	  seq_trig_ = FAILURE;
	  break;
	}
	switch (get_state(x, y - i)) {
	case BRICK :
	case FLOOR :
	case ENEMY :
	  set_state(VER_FIRE, x, y - i);
	  break;
	case BRICK_FIRE_UP :
	  set_state(FIRE_UP, x, y - i);
	  break;
	case BRICK_BOMB_UP :
	  set_state(BOMB_UP, x, y - i);
	  break;
	case PLAYER1 : 
	  set_state(VER_FIRE, x, y - i);
	  seq_trig_ = FAILURE;
	  break;
	case PLAYER2 : 
	  set_state(VER_FIRE, x, y - i);
	  seq_trig_ = FAILURE;
	  break;
	}
      }
      switch (it->player_id_) {
      case 1:
	player1_state_.current_bombs_--;
	break;
      case 2:
	player2_state_.current_bombs_--;
	break;	
      }
      set_state(CROSS_FIRE, x, y);
      bomb_blasted_ = true; 
      it = bombs_.erase(it);
      if (it == bombs_.end())
	break;
    }
  }
}

void Game::flush_fire() {
  vector<ImageID>::iterator it;
  pthread_mutex_lock(&mutex_for_states_);
  for (it = states_.begin(); it != states_.end(); ++it) {
    if (*it == Game::HORI_FIRE || *it == VER_FIRE || *it == CROSS_FIRE) {
      *it = Game::FLOOR;
    }
  }
  pthread_mutex_unlock(&mutex_for_states_);
}

bool Game::cleared() {
 vector<ImageID>::iterator it;
  for (it = states_.begin(); it != states_.end(); ++it) {
    if (*it == Game::ENEMY && game_init::player_mode == game_init::ONE_PLAYER) {
      return 0;
    }
  }
  return 1;
}

//timer function
void Game::timer() {

  enemy_move();
  bombs_blast();
  if (bomb_blasted_)
    flush_cnt_++;
  if (flush_cnt_ == 2) {
  flush_fire();
  flush_cnt_ = 0;
  bomb_blasted_ = false;
  }
  glutPostRedisplay();
  
  if (cleared())
  seq_trig_ = CLEAR;
}

void Game::set_texture_id(GLuint t_id) {
  texture_id_ = t_id; 
}

GLuint Game::get_texture_id() { 
  return texture_id_;
}

void Game::draw_object() {
  // glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, get_texture_id());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 105, 0, 105);
  

  double x;
  double y;
  double size = 0.25;
  switch (get_image_id()) {
  case PLAYER1: { 
    x = 0;
    y = 0.75;
    break;
  }
  case PLAYER2:
    x = 0.25;
    y = 0.75;
    break;
  case BOMB_UP:
    x = 0.50;
    y = 0.75;
    break;
  case FIRE_UP:
    x = 0.75;
    y = 0.75;
    break;
  case HORI_FIRE:
    x = 0;
    y = 0.50;
    break;
  case VER_FIRE:
    x = 0.25;
    y = 0.50;
    break;
  case ENEMY:
    x = 0.50;
    y = 0.50;
    break;
  case WALL:
    x = 0.75;
    y = 0.50;
    break;
  case BRICK:
    x = 0;
    y = 0.25;
    break;
  case FLOOR:
    x = 0.25;
    y = 0.25;
    break;
  case BOMB:
    x = 0.50;
    y = 0.25;
    break;
  case CROSS_FIRE:
    x = 0.75;
    y = 0.25;
    break;
  default:
    fprintf(stderr, "there is no such a object\n");
    break;
  }
  glBegin(GL_QUADS);
  glTexCoord2f(x, y); glVertex2i(get_vertex_x(), get_vertex_y());
  glTexCoord2f(x, y + size); glVertex2i(get_vertex_x(), get_vertex_y() + get_size());
  glTexCoord2f(x + size, y + size); glVertex2i(get_vertex_x() + get_size(), get_vertex_y() + get_size());
  glTexCoord2f(x + size, y); glVertex2i(get_vertex_x() + get_size(), get_vertex_y());
  glEnd();
 
  glDisable(GL_TEXTURE_2D);
   glFlush();
  //glutSwapBuffers();
}

void Game::draw_all_objects() {
  //  pthread_mutex_lock(&mutex_for_states_);
  for (int i = 0; i < stage_size_; i++) {
    switch (states_[i]) {
    case Game::WALL:
      set_object(Game::WALL, (i%21)*5, (i/21)*5); 
      draw_object();    
      break;
    case Game::FLOOR:
      set_object(Game::FLOOR, (i%21)*5, (i/21)*5);
      draw_object();
      break;
    case Game::PLAYER1:
      set_object(Game::PLAYER1, (i%21)*5, (i/21)*5);
      draw_object();
      break;
    case Game::PLAYER2:
      set_object(Game::PLAYER2, (i%21)*5, (i/21)*5);
      draw_object();
      break;
    case Game::BRICK:
    case Game::BRICK_FIRE_UP:
    case Game::BRICK_BOMB_UP:
      set_object(Game::BRICK, (i%21)*5, (i/21)*5);
      draw_object();
      break;
    case Game::ENEMY:
      set_object(Game::ENEMY, (i%21)*5, (i/21)*5);
      draw_object();
      break;
    case Game::FIRE_UP:
      set_object(Game::FIRE_UP, (i%21)*5, (i/21)*5);
      draw_object();
      break;
    case Game::BOMB_UP:
      set_object(Game::BOMB_UP, (i%21)*5, (i/21)*5);
      draw_object();
      break;
    case Game::BOMB:
      set_object(Game::BOMB, (i%21)*5, (i/21)*5);
      draw_object();
      break;
    case Game::HORI_FIRE:
      set_object(Game::HORI_FIRE, (i%21)*5, (i/21)*5);
      draw_object();
      break;
    case Game::VER_FIRE:
      set_object(Game::VER_FIRE, (i%21)*5, (i/21)*5);
      draw_object();
      break;
    case Game::CROSS_FIRE:
      set_object(Game::CROSS_FIRE, (i%21)*5, (i/21)*5);
      draw_object();
      break;

    }
  }
 
}

void Game::set_image_id(ImageID img_id) {
  image_id_ = img_id;
}

Game::ImageID Game::get_image_id() { 
  return image_id_;
}

void Game::set_vertex_x(int x) {
  vertex_x_ = x;
}

void Game::set_vertex_y(int y) {
  vertex_y_ = y;
}

int Game::get_vertex_x() {
  return vertex_x_;
}

int Game::get_vertex_y() {
  return vertex_y_;
}

void Game::set_size(int size) {
  size_ = size;
}

int Game::get_size() {
  return size_;
}

void Game::init_object(GLuint t_id, ImageID img_id, int x, int y, int size) {
  texture_id_ = t_id; 
  image_id_ = img_id;
  vertex_x_ = x;
  vertex_y_ = y;
  size_ = size;
}

void Game::set_object(ImageID img_id, int x, int y) {
  image_id_ = img_id;
  vertex_x_ = x;
  vertex_y_ = y;
}


 //stage data handle function
void Game::load_stage(char *filename) {

  ifstream inputFile(filename, ifstream::binary);
  inputFile.seekg(0, ifstream::end);

  int file_size = static_cast<int>(inputFile.tellg());
  inputFile.seekg(0, ifstream::beg);

  char* file_image = new char[file_size];
  inputFile.read(file_image, file_size);
  cout.write(file_image, file_size);
   
  int i = 0;
  int stage_size = 0;
     while(file_image[i] != '\0') {
       switch (file_image[i]) {
       case '#' :
	 states_.push_back(WALL);
	 stage_size++;
	 break;
       case ' ':
	 states_.push_back(FLOOR);
	 floor_points_.push_back(stage_size);
	 stage_size++;
	 break;
       }
       i++;
     }
     stage_size_ =  stage_size;
}

void Game::set_state(ImageID img_id, int x, int y) {
  if (x + y*21 >= states_.size() || x + y*21 < 0)
    return;
  states_[x + y*21] = img_id;
}

Game::ImageID Game::get_state(int x, int y) {
  if (x + y*21 >= states_.size() || x + y*21 < 0)
    return Game::WALL;
  return states_[x + y*21];
}

void Game::get_player_position(Game::ImageID img_id, int& x, int&y) {
  int player_idx = 0;
  vector<Game::ImageID>::iterator it;
  if (img_id == Game::PLAYER1) { 
    it = find(states_.begin(), states_.end(), PLAYER1);
    if (it != states_.end()) player_idx = distance(states_.begin(), it);
    else player_idx = -1;
  }
  else if (img_id == Game::PLAYER2) { 
    it = find(states_.begin(), states_.end(), PLAYER2);
    if (it != states_.end()) player_idx = distance(states_.begin(), it);
    else player_idx = -1;
  }
  else {
    fprintf(stderr, "arg $1 is not PLAYER!!#\n");
    exit(0); 
  }
  x = player_idx % 21;
  y = player_idx / 21;
};

void Game::save_enemy_position() {
  enemy_points_.clear();
  vector<Game::ImageID>::iterator it;
  for (it = states_.begin(); it != states_.end(); ++it) {
    if (*it == Game::ENEMY)
      enemy_points_.push_back(distance(states_.begin(), it));
  }

};



void Game::init_states(  double enemy_percent,
				double brick_percent,
				double fire_up_percent,
				double bomb_up_percent,
				int num_players) {

  assert((enemy_percent + brick_percent) < 1 && 
	 "enemy_percent + brick_percent should be < 1!!");

  int num_enemies = enemy_percent * floor_points_.size();
  int num_bricks = brick_percent * floor_points_.size();

  for(int i = 0; i < num_enemies; i++) {
    int idx = rand() % (floor_points_.size() - 1);
    states_[floor_points_[idx]] = ENEMY;
    floor_points_.erase(floor_points_.begin() + idx);
  }

  for(int i = 0; i < num_bricks; i++) {
    int idx = rand() % (floor_points_.size() - 1);
    states_[floor_points_[idx]] = BRICK;
    brick_points_.push_back(floor_points_[idx]);
    floor_points_.erase(floor_points_.begin() + idx);
 }
  int num_fire_up = fire_up_percent * brick_points_.size();
  int num_bomb_up = bomb_up_percent * brick_points_.size();

  for(int i = 0; i < num_fire_up; i++) {
    int idx = rand() % (brick_points_.size() - 1);
      states_[brick_points_[idx]] = BRICK_FIRE_UP;
      brick_points_.erase(brick_points_.begin() + idx);
  }

 for(int i = 0; i < num_bomb_up; i++) {
    int idx = rand() % (brick_points_.size() - 1);
    states_[brick_points_[idx]] = BRICK_BOMB_UP;
    brick_points_.erase(brick_points_.begin() + idx);
  }

 for (int i = 0; i < num_players; i++) {
   if (i == 0) {
     set_state(PLAYER1, 1, 19);
     set_state(FLOOR, 2, 19);
     set_state(FLOOR, 1, 18);
   }
   else if (i == 1){
     set_state(PLAYER2, 19, 1);
     set_state(FLOOR, 19, 2);
     set_state(FLOOR, 18, 1);
   }
 }
}

void Game::init_game(game_init::PLAYER_MODE player_mode, 
		     game_init::GAME_LEVEL game_level) {
  double enemy_ratio, brick_ratio, fireup_ratio, bombup_ratio;
  int num_player;
  switch (player_mode) {
  case game_init::ONE_PLAYER:
    num_player = 1;
    break;
  case game_init::TWO_PLAYER:
    num_player = 2;
    break;
  default:
    break;
  }
  switch (game_level) {
  case game_init::BEGGINER:
    enemy_ratio = 0.07;
    brick_ratio = 0.6;
    fireup_ratio = 0.3;
    bombup_ratio = 0.3;
    break;
  case game_init::INTERMEDIATE:
    enemy_ratio = 0.09;
    brick_ratio = 0.5;
    fireup_ratio = 0.3;
    bombup_ratio = 0.3;
    break;
  case game_init::ADVANCED:
    enemy_ratio = 0.7;
    brick_ratio = 0.2;
    fireup_ratio = 0.3;
    bombup_ratio = 0.3;
    break;
  default:
    break;
  }
  init_states(enemy_ratio, brick_ratio, fireup_ratio, bombup_ratio, num_player);
}

Game *Game::instance() {
  return Game::game_;
}

void Game::create() {
  assert(!game_ && "object Game exists already!!\n");
  game_ = new Game();
}

void Game::destroy() {
  delete game_;
  game_ = NULL;
}

Game::Game(){
  load_stage("../data/stage/stage1.txt");
  set_size(5);
  init_game(game_init::player_mode, game_init::game_level);
  seq_trig_ = NONE;
  player1_state_ = {1, 1, 0};
  player2_state_ = {1, 1, 0};
  bomb_blasted_ = false;
  flush_cnt_ = 0;
}
Game::~Game(){}
