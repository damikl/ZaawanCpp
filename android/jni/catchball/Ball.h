#ifndef _BALL_H_
#define _BALL_H_

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Box2D.h"
#include "world.h"


struct Line { 
	float a; 
	float b;
	Line(float x1, float y1, float x2, float y2)
	{
		a = (y2-y1)/(x2 - x1);
		b = y1 - x1*a;
	}

	float getAngle(const Line& otherLine) const
	{
		return (a-otherLine.a)/(1+a*otherLine.a);
	}
};

class Ball {
private:
  GLfloat pos_x;
  GLfloat pos_y;
  b2Body* ball;
  b2RevoluteJoint* m_joint;
  GLfloat health;
  int texture;
  
public:
  Ball() {
  }
  Ball(const World& myworld) {
	b2World* world = myworld.getWorld();
	pos_x = 400.0f;
	pos_y = 200.0f;
	// Define another box shape for our dynamic body.
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(pos_x, pos_y);
	bd.allowSleep = false;
	ball = world->CreateBody(&bd);

	b2CircleShape shape;
	shape.m_radius = 70.0f;

	ball->CreateFixture(&shape, 1.0f);

	health = 255.0f;


	b2RevoluteJointDef jd;
	jd.Initialize(ball,myworld.getGround(),ball->GetWorldCenter());
//	jd.bodyA = myworld.getGround();
//	jd.bodyB = ball;
//	jd.localAnchorA.Set(0.0f, 10.0f);
//	jd.localAnchorB.Set(0.0f, 0.0f);
	jd.referenceAngle = 0.0f;
	jd.motorSpeed = 1.05f * b2_pi;
	jd.maxMotorTorque = 1e8f;
	jd.enableMotor = true;
	m_joint = (b2RevoluteJoint*)world->CreateJoint(&jd);
	
  }
  void setTexture(int tex);
  void draw();
  float degreesToRadian(float d);
  const b2RevoluteJoint* getJoint() const { return m_joint; }
  void draw_square(GLfloat vertex[4][2], GLfloat colors[3][4]);
  void drawTexture();
  void stopRotating() { m_joint->EnableMotor(false); }
  GLfloat getHealth();
  void rotate(float x1, float y1, float x2, float y2);
  void decreaseHealth(GLfloat h);
  float radianToDegrees(float d) {
    return (d*180)/3.14159;
  }
};

#endif
