#include "Ball.h"
#include "def.h"
#include <iostream>
#include <algorithm>

void Ball::setTexture(int tex)
{
	texture = tex;
}

void Ball::draw() {
    GLfloat colors[3][4] =
    {
	{1.0f - health/255.0f, health/255.0f, 0.0f, 1.0f},
	{1.0f - health/255.0f, health/255.0f, 0.0f, 1.0f},
	{1.0f - health/255.0f, health/255.0f, 0.0f, 1.0f}
    };

    b2Vec2 position = ball->GetPosition();
    
    GLfloat vertices[4][2] =
    {
	{position.x+100.0f, position.y+50.0f},
	{position.x-100.0f, position.y+50.0f},
	{position.x-100.0f, position.y-50.0f},
	{position.x+100.0f, position.y-50.0f}
    }; 
    
    draw_square(vertices, colors); 
    int i = 0;
    GLfloat roofColor[3][4] =
    {
	{1.0f - health/255.0f, health/255.0f, 0.0f, 1.0f},
	{1.0f - health/255.0f, health/255.0f, 0.0f, 1.0f},
	{1.0f - health/255.0f, health/255.0f, 0.0f, 1.0f}
    };
    
    GLfloat roofVertices[4][2] =
    {
	{240-120, 100},
	{240+120, 100},
	{240, 150},
    }; 
    
    glVertexPointer(2, GL_FLOAT, 0, roofVertices);
    glColorPointer(4, GL_FLOAT, 0, roofColor);

    // Draw the triangle (3 vertices)
    glDrawArrays(GL_TRIANGLES, 0, 3);  
}

void Ball::draw_square(GLfloat vertex[4][2], GLfloat colors[3][4]) {    
    GLfloat vertices[3][2] =
    {
	{vertex[0][0], vertex[0][1]},
	{vertex[1][0], vertex[1][1]},
	{vertex[2][0], vertex[2][1]},
    };
    
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glColorPointer(4, GL_FLOAT, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, 3); 
    
    GLfloat vertices1[3][2] =
    {
	{vertex[0][0], vertex[0][1]},
	{vertex[2][0], vertex[2][1]},
	{vertex[3][0], vertex[3][1]},
    };
    
    glVertexPointer(2, GL_FLOAT, 0, vertices1);
    glColorPointer(4, GL_FLOAT, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, 3); 
}

float Ball::degreesToRadian(float d) {
    return (d*3.14159)/180;
}

void Ball::drawTexture()
{
  b2Vec2 position = ball->GetPosition();

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
  glTranslatef(position.x, position.y, 0);
  glScalef(140,140,0);
	// m_joint->GetJointAngle()
  float angle = radianToDegrees( ball->GetAngle() );
  glRotatef(angle,0.0f,0.0f,1.0f);
//  LOGI("praktyczna rotacja o: %f \n", angle);
  glBindTexture( GL_TEXTURE_2D, texture );
  glVertexPointer(3, GL_FIXED, 0, square);
  glTexCoordPointer(2, GL_FIXED, 0, texCoords);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glPopMatrix();
}

void Ball::rotate(float x1, float y1, float x2, float y2) {
//	x1 = 800.0 - x1;
//	x2 = 800.0 - x2;
	//class member variable
	b2Vec2 clickedPoint;
	//in class constructor
	clickedPoint = b2Vec2(x2,y2);//initial starting point

	b2Vec2 position = ball->GetPosition();
	LOGI("punkty: %f %f %f %f %f %f\n", x1,y1,x2,y2,position.x,position.y);
	Line lineold = Line(x1,y1,position.x,position.y);
//	LOGI("stara: %f %f\n", lineold.a, lineold.b);
	Line linenew = Line(x2,y2,position.x,position.y);
//	LOGI("nowa: %f %f\n", linenew.a, linenew.b);

	float bodyAngle = ball->GetAngle();
    b2Vec2 toTarget = clickedPoint - ball->GetPosition();
    float desiredAngle = atan2f( -toTarget.x, toTarget.y );
//	float angle = lineold.getAngle(linenew);
	float totalRotation = desiredAngle - bodyAngle;
	while ( totalRotation < -degreesToRadian(180) ) totalRotation += degreesToRadian(180);
	while ( totalRotation > degreesToRadian(180)) totalRotation -= degreesToRadian(180);
	float change = degreesToRadian(1.0); //allow 1 degree rotation per time step
	float newAngle = bodyAngle + std::min( change, std::max(-change, totalRotation));
	ball->SetTransform( position, newAngle );
	LOGI("rotacja o: %f \n", newAngle);
}

GLfloat Ball::getHealth() {
  return health;
}

void Ball::decreaseHealth(GLfloat h) {
  health -= h;
}
