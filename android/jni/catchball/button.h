#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class Button {
private:    
  GLfloat point[1][2];
  GLfloat blue[1][4];
  GLfloat red[1][4];
  GLfloat size;
  int bblue, bred;
  bool active;
  
public:
  Button(GLfloat x, GLfloat y) {
    point[0][0] = x;
    point[0][1] = y;
    blue[0][0] = 0.0f;
    blue[0][1] = 0.0f;
    blue[0][2] = 1.0f;
    blue[0][3] = 1.0f;
    red[0][0] = 1.0f;
    red[0][1] = 0.0f;
    red[0][2] = 0.0f;
    red[0][3] = 1.0f;
    size = 60.0f;
    active = false;
  }
  Button() {
    size = 60.0f;
    active = false;
  }
  void draw();
  void drawTexture();
  void makeActive();
  void deActive();
  bool isActive();
  bool isPressed(int x, int y);
  void setTexture(int blue, int red);
};

#endif