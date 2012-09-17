#include "world.h"

b2World* World::getWorld() const {
  return world;
}

b2Body* World::getGround() const {
  return groundBody;
}
