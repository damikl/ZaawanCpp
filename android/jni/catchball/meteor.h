#ifndef _METEOR_H_
#define _METEOR_H_

#include <time.h>
#include <stdlib.h>

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Box2D.h"

typedef enum {
	LEFT,
	RIGHT
} Side;

typedef enum {
	BLUE,
	GREEN,
	BRONZE,
	RED,
	YELLOW
} Color;

class Texture {
	private:
		Color color;
		int tex;
	public:
		Texture(Color c, int t)
		{
			color = c;
			tex = t;
		}
		Color getColor() const { return color;}
		int getTex() const { return tex; }
};

class SideSettings {
	private:
		Side side;
		GLfloat x;
		char sign;
		static SideSettings* tab[2];
		SideSettings(Side _side) {
			side = _side;
			switch(side)
			{
			case LEFT:
				x = 10.0;
				sign = 1;
				break;
			case RIGHT:
				x = 500.0;
				sign = -1;
				break;
			}
		}
	public:
		Side getSide() const { return side; }
		char getSign() const { return sign; }
		GLfloat getX() const { return x; }
		static const SideSettings* getSS(const Side& side){
			switch(side)
			{
			case LEFT:
				if(tab[0]== NULL)
					tab[0] = new SideSettings(LEFT);
				return tab[0];
				break;
			case RIGHT:
				if(tab[1]== NULL)
					tab[1] = new SideSettings(RIGHT);
				return tab[1];
				break;
			}
		}
		
};

class Meteor {
private:
  b2Body* body;
  b2BodyDef bodyDef;
  b2CircleShape dynamicBox;
  b2FixtureDef fixtureDef;
  Texture tex;
  
public:
  Meteor(b2World *world, Side side, Texture _tex) : tex(_tex) {
	const SideSettings* s = SideSettings::getSS(side);
    // Define the dynamic body. We set its position and call the body factory.
    bodyDef.type = b2_dynamicBody;
    srand ( time(NULL) );
    bodyDef.position.Set(s->getX(), rand() % 240 + 40 );
    body = world->CreateBody(&bodyDef);
    // Define another box shape for our dynamic body.
    dynamicBox.m_radius = 10.0f;
    // Define the dynamic body fixture.
    fixtureDef.shape = &dynamicBox;
    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;
    // Override the default friction.
    fixtureDef.friction = 0.3f;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    b2Vec2 force(200.0f*s->getSign(), 0.0f);
    body->SetLinearVelocity(force);
  }
  float degreesToRadian(float d);
  void drawTexture();
  void setTexture(Texture _tex) {tex = _tex;}
  void draw();
  b2Body* getBody();
};

#endif
