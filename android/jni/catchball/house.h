#ifndef _HOUSE_H_
#define _HOUSE_H_

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Box2D.h"

class House {
private:
  b2Body* house;
  b2Body* roof;
  GLfloat health;
  int texture;
  
public:
  House() {
	health = 255.0f;
  }
  House(b2World *world) {
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(240.0f, 50.0f);
	house = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(100.0f, 50.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	house->CreateFixture(&fixtureDef);
	
	//dach
	b2PolygonShape r;
	b2Vec2 vertices[3];
	vertices[0].Set(-120.0f, 0.0f);
	vertices[1].Set(120.0f, 0.0f);
	vertices[2].Set(0.0f, 50.0f);
	r.Set(vertices, 3);
	
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(240.0f, 100.0f);
	roof = world->CreateBody(&bd);
	roof->CreateFixture(&r, 1.0f);
	
	health = 255.0f;
  }
  void setTexture(int tex);
  void draw();
  void draw_square(GLfloat vertex[4][2], GLfloat colors[3][4]);
  void drawTexture();
  GLfloat getHealth();
  void decreaseHealth(GLfloat h);
};

#endif