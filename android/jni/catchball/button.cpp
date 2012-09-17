#include "button.h"

void Button::draw() { 
  glPointSize(size);
  if(active) {
    glColorPointer(4, GL_FLOAT, 0, red);
  } else {
    glColorPointer(4, GL_FLOAT, 0, blue);
  }
  glVertexPointer(2, GL_FLOAT, 0, point);    
  glDrawArrays(GL_POINTS, 0, 1);
  
}

void Button::drawTexture()
{
  #define fX(x) ((int)(x * (1  << 16)))
  int square[12] = {
    fX(-0.5), fX(-0.5), 0,
    fX(0.5), fX(-0.5), 0,
    fX(-0.5), fX(0.5), 0,
    fX(0.5), fX(0.5), 0
  };

  int texCoords[8] = {
      0, fX(1),
      fX(1), fX(1),
      0,0,
      fX(1),0
  };
  glPushMatrix();
  if(active) {
    glBindTexture( GL_TEXTURE_2D, bred );
  } else {
    glBindTexture( GL_TEXTURE_2D, bblue );
  }
  glTranslatef(point[0][0], point[0][1], 0);
  glScalef(50,50,0);
  glVertexPointer(3, GL_FIXED, 0, square);
  glTexCoordPointer(2, GL_FIXED, 0, texCoords);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glPopMatrix();
}

void Button::makeActive() {
  active = true;
}

void Button::deActive() {
  active = false;
}

bool Button::isActive() {
  return active;
}

bool Button::isPressed(int x, int y) {
  if(x>point[0][0]-30 && x<point[0][0]+30 && y>point[0][1]-30 && y<point[0][1]+30) {
    return true;
  } else {
    return false;
  }
}

void Button::setTexture(int blue, int red) {
  bblue = blue;
  bred = red;
}