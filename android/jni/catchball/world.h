#ifndef _WORLD_H_
#define _WORLD_H_

#include "Box2D.h"

class World {
private:
  b2World *world;
  b2Body *groundBody;
public:
  World() {
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);	

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity, true);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(40.0f, 20.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(40.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);
  }
  b2World* getWorld() const;
  b2Body* getGround() const;
};

#endif
