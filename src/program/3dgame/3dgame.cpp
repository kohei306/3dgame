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
#include "Game3d.h"


Game3d* Game3d::game3d_;

Base *base;
GLUI_RadioGroup *group1;
int main_window;
GLUI_Listbox *listbox;
extern pthread_mutex_t mutex_for_states_ = PTHREAD_MUTEX_INITIALIZER;

void disp(void) { 

  base->draw();
  
}

void keyboard(unsigned char key, int x, int y) {
  base->keybord_handler(key);
  // base = base->update();
  glutPostRedisplay();
}

void timer(int value) {

  // x += 10.0;
  // fprintf(stderr, "timer!\n");
    base->timer();
  //  base = base->update();
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
    glutPostRedisplay();  
}


void cb_for_radiobutton(int id){
   int num_player = group1->get_int_val();
  game3d_init::player_mode = static_cast<game3d_init::PLAYER_MODE>(num_player);
};

void cb_for_listbox(int id){
   int level = listbox->get_int_val();
  game3d_init::game3d_level = static_cast<game3d_init::GAME_LEVEL>(level);
};

void set() {
  delete base;
  //base = Title::instance();
  glutPostRedisplay();
} 

// void setting_glui() {
//   int obj;
//   ForSet::glui = GLUI_Master.create_glui_subwindow( main_window, 
// 						   GLUI_SUBWINDOW_TOP );
//   ForSet:: glui->add_statictext( "Setting" );
//   ForSet:: glui->add_separator();

//   /* * a vertical bar should be drawn **/
//   GLUI_Panel *obj_panel = ForSet::glui->add_panel ( "Select Player mode" );

//  /* GLUI_RadioGroup*/ 
//   group1 = ForSet::glui->add_radiogroup_to_panel(obj_panel, &obj, 3, cb_for_radiobutton);
//   ForSet::glui->add_radiobutton_to_group( group1, "1 player mode" );
//   ForSet::glui->add_radiobutton_to_group( group1, "2 player mode" );
//   ForSet::glui->add_button( "Set", 0,(GLUI_Update_CB)set );
//   listbox = ForSet::glui->add_listbox_to_panel(obj_panel, "Level ", &obj, 1, cb_for_listbox);

//   listbox->add_item(0, "Beginer");
//   listbox->add_item(1, "Intermediate");
//   listbox->add_item(2, "Advanced");
//  /** Register the Idle callback with GLUI (instead of with GLUT) **/
//  ForSet::glui->hide();
//  GLUI_Master.set_glutIdleFunc(NULL);
// }

void *redraw(void *arg) {
  
  // while (1) {
  //   flush_fire();
  //    sleep(1);
  // }
  // return 0;
  
}

void init(void)
{

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glMatrixMode(GL_PROJECTION);
  //  glEnable(GL_LIGHT1);
  //  glLightfv(GL_LIGHT0, GL_AMBIENT, draw_stuff::red);
  //glLightfv(GL_LIGHT1, GL_SPECULAR, draw_stuff::green);
 static GLfloat lightpos[] = { -3.0, 4.0, 5.0, 0.0 }; /* 光源の位置 */

/* 光源の位置を設定 */
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

}
void resize(int w, int h)
{

  glViewport(0, 0, w, h);
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1, 2000.0);
  //glTranslated(0.0, 0.0, -5.0);
  //    gluLookAt(0.0, 500.0, -50.0, 0.0, 0.0, -50, 0.0, 0.0, -1.0);
  // gluLookAt(lx, ly, lz, lx, ly, -200, 0.0, 1.0, 0.0);
  // glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
  /* 光源の位置設定 */
  // glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}


int main(int argc , char ** argv){

  //this has to be done before create Game3d
  game3d_init::num_blocks = 1;
  game3d_init::num_obstacles_in_block = 300;
  game3d_init::num_enemies = 1;
  
  Game3d::create();
  base = Game3d::instance();


  glutInit(&argc , argv);
  glutInitWindowSize(1000 , 900);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  main_window =  glutCreateWindow("Kitty on your lap");
  //  setting_glui();

  // pthread_t t1;
   // int create_t1 = pthread_create(&t1, NULL, redraw, NULL);
   /* 緑の箱 */
  
  glutDisplayFunc(disp);
  glutTimerFunc(1 , timer , 5);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
  return 0;
  }



