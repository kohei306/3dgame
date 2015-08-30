#include <fstream>
#include <iostream>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <stdio.h>
#include <vector>
#include <pthread.h>
#include "bmp.h"
#include "Game.h"
#include "Clear.h"
#include "Failure.h"
#include "Pause.h"
#include "FontDraw.h"
#include "Base.h"
#include "Play.h"
#include "Title.h"
#include "Setting.h"


Title* Title::title_;
Game* Game::game_;
FontDraw* FontDraw::font_draw_;
Base *base;
GLUI_RadioGroup *group1;
int main_window;
GLUI_Listbox *listbox;
extern pthread_mutex_t mutex_for_states_ = PTHREAD_MUTEX_INITIALIZER;
void draw_walls(void) {
  Game *game;
  game->set_object(Game::WALL, 50, 50);
}

void disp(void) {
  pthread_mutex_lock(&mutex_for_states_);
  base->draw();
  pthread_mutex_unlock(&mutex_for_states_);
  // sleep(1.5);
  
}

void keyboard(unsigned char key, int x, int y) {

  base->keybord_handler(key);
  base = base->update();
  glutPostRedisplay();
}

void timer(int value) {

  base->timer();
  base = base->update();
  //  fprintf(stderr, "main er!!\n");
  /* static int x = 0;
  x++;
  game->set_state(Game::PLAYER1, x, 5);
  glutPostRedisplay();
 //   game->set_object(Game::PLAYER1, 0, 0);
  // game->set_vertex_x(x);
  // glRotatef(55 , 0.5 , 50 , 0.25);
  // game->draw_object();
  glutTimerFunc(1 , timer , 0);
  */
  glutTimerFunc(1, timer , 5);
  //  glutPostRedisplay();  
}


void cb_for_radiobutton(int id){
   int num_player = group1->get_int_val();
  game_init::player_mode = static_cast<game_init::PLAYER_MODE>(num_player);
};

void cb_for_listbox(int id){
   int level = listbox->get_int_val();
  game_init::game_level = static_cast<game_init::GAME_LEVEL>(level);
};

void set() {
  delete base;
  base = Title::instance();
  glutPostRedisplay();
} 

void setting_glui() {
  int obj;
  ForSet::glui = GLUI_Master.create_glui_subwindow( main_window, 
						   GLUI_SUBWINDOW_TOP );
  ForSet:: glui->add_statictext( "Setting" );
  ForSet:: glui->add_separator();

  /* * a vertical bar should be drawn **/
  GLUI_Panel *obj_panel = ForSet::glui->add_panel ( "Select Player mode" );

 /* GLUI_RadioGroup*/ 
  group1 = ForSet::glui->add_radiogroup_to_panel(obj_panel, &obj, 3, cb_for_radiobutton);
  ForSet::glui->add_radiobutton_to_group( group1, "1 player mode" );
  ForSet::glui->add_radiobutton_to_group( group1, "2 player mode" );
  ForSet::glui->add_button( "Set", 0,(GLUI_Update_CB)set );
  listbox = ForSet::glui->add_listbox_to_panel(obj_panel, "Level ", &obj, 1, cb_for_listbox);

  listbox->add_item(0, "Beginer");
  listbox->add_item(1, "Intermediate");
  listbox->add_item(2, "Advanced");
 /** Register the Idle callback with GLUI (instead of with GLUT) **/
 ForSet::glui->hide();
 GLUI_Master.set_glutIdleFunc(NULL);
}

void *redraw(void *arg) {
  
  // while (1) {
  //   flush_fire();
  //    sleep(1);
  // }
  // return 0;
  
}




int main(int argc , char ** argv){
 
  Title::create();
  base = Title::instance();

  glutInit(&argc , argv);
  glutInitWindowSize(1000 , 900);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  main_window =  glutCreateWindow("Kitty on your lap");
  setting_glui();
  object::tx_id = LoadBMP("../data/image/objects.bmp");
  font::tx_id = LoadBMP("../data/image/font.bmp");

  pthread_t t1;

  int create_t1 = pthread_create(&t1, NULL, redraw, NULL);
  
  glutDisplayFunc(disp);
  glutTimerFunc(1 , timer , 5);
  glutKeyboardFunc(keyboard);
  
  glutMainLoop();
  return 0;
  }



