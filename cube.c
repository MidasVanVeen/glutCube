#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Author: Midas van Veen
 *
 * glut test
 */

static int win_id;
static int win_x, win_y;
static int rotate_y, lastrotate_y;
static int rotate_x, lastrotate_x;
static int omx, omy, mx, my;
static int mouse_down[3], mouse_up[3];
static int keystates[256];

static void post_display(void);
static void pre_display(void);
static void display_func(void);
static void idle_func(void);
static void reshape_func(int width, int height);
static void key_func(unsigned char key, int x, int y);
static void mouse_func(int button, int state, int x, int y);
static void motion_func(int x, int y);
static void open_glut_window(void);

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  win_x = 512;
  win_y = 512;
  open_glut_window();

  glutMainLoop();

  return 0;
}

static void motion_func(int x, int y) {
  mx = x;
  my = y;
}

static void mouse_func(int button, int state, int x, int y) {
  omx = mx = x;
  omy = my = y;

  mouse_down[button] = state == GLUT_DOWN;
  mouse_up[button] = state == GLUT_UP;
}

static void key_func(unsigned char key, int x, int y) { keystates[key] = 1; }

static void keyUp_func(unsigned char key, int x, int y) { keystates[key] = 0; }

static void post_display(void) {
  glFlush();
  glutSwapBuffers();
}

static void pre_display(void) {
  glViewport(0, 0, win_x, win_y);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 1.0, 0.0, 1.0);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void display_func(void) {
  pre_display();
  glLoadIdentity();

  glRotatef(rotate_y, 1.0, 0.0, 0.0);
  glRotatef(rotate_x, 0.0, 1.0, 0.0);

  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.5, -0.5, -0.5);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.5, 0.5, -0.5);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(-0.5, 0.5, -0.5);
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(-0.5, -0.5, -0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(0.5, -0.5, 0.5);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.5, 0.5, 0.5);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(-0.5, 0.5, 0.5);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-0.5, -0.5, 0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.5, -0.5, -0.5);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.5, 0.5, -0.5);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.5, 0.5, 0.5);
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(0.5, -0.5, 0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-0.5, -0.5, 0.5);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(-0.5, 0.5, 0.5);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(-0.5, 0.5, -0.5);
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(-0.5, -0.5, -0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.5, 0.5, 0.5);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.5, 0.5, -0.5);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(-0.5, 0.5, -0.5);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(-0.5, 0.5, 0.5);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.5, -0.5, -0.5);
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(0.5, -0.5, 0.5);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-0.5, -0.5, 0.5);
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(-0.5, -0.5, -0.5);
  glEnd();

  post_display();
}

static void idle_func(void) {
  // update objects

  if (mouse_up[0] == 1) {
    lastrotate_y = rotate_y;
    lastrotate_x = rotate_x;
  }

  if (mouse_down[0] == 1) {
    rotate_y = lastrotate_y - (my - omy) / 2;
    rotate_x = lastrotate_x - (mx - omx) / 2;
  }

  if (keystates['w']) {
    rotate_y += 1;
  }
  if (keystates['s']) {
    rotate_y -= 1;
  }
  if (keystates['a']) {
    rotate_x += 1;
  }
  if (keystates['d']) {
    rotate_x -= 1;
  }

  glutSetWindow(win_id);
  glutPostRedisplay();
}

static void reshape_func(int width, int height) {
  glutSetWindow(win_id);
  glutReshapeWindow(width, height);
  win_x = width;
  win_y = height;
}

static void open_glut_window(void) {
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(win_x, win_y);
  win_id = glutCreateWindow("Alias | wavefront");

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glutSwapBuffers();

  pre_display();

  glutKeyboardFunc(key_func);
  glutKeyboardUpFunc(keyUp_func);
  glutMouseFunc(mouse_func);
  glutMotionFunc(motion_func);
  glutReshapeFunc(reshape_func);
  glutIdleFunc(idle_func);
  glutDisplayFunc(display_func);
}
