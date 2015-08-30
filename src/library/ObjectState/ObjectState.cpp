#include <fstream>
#include <iostream>
#include <cstdlib>
//#include <GL/gl.h>
//#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <assert.h>

//#include "bmp.h"
#include "ObjectState.h"
using namespace std;
void ObjectState::load_stage(char *filename) {

  ifstream inputFile(filename, ifstream::binary);
  inputFile.seekg(0, ifstream::end);

  int file_size = static_cast<int>(inputFile.tellg());
  inputFile.seekg(0, ifstream::beg);

  char* file_image = new char[file_size];
  inputFile.read(file_image, file_size);
  cout.write(file_image, file_size);
   
  int i = 0;
  int stage_size = 0;
    ImageID *states = new ImageID[strlen(file_image)];
     while(file_image[i] != '\0') {
       switch (file_image[i]) {
       case '#' :
	 states[stage_size] = WALL;
	 stage_size++;
	 break;
       case ' ':
	 states[stage_size] = FLOOR;
	 floor_points_.push_back(stage_size);
	 stage_size++;
	 break;
       }
       i++;
     }
     stage_size_ =  stage_size;
     states_ = states;
}

void ObjectState::set_state(ImageID img_id, int x, int y) {
  states_[x + y*21] = img_id;
}

ObjectState::ImageID ObjectState::get_state(int x, int y) {
  return states_[x + y*21];
}

void ObjectState::init_states(  double enemy_percent,
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
