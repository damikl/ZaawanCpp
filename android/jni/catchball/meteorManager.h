#ifndef _METEOR_MANAGER_H_
#define _METEOR_MANAGER_H_

#include <vector>

#include <time.h>
#include <stdlib.h>

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Box2D.h"
#include "def.h"
#include "meteor.h"

using namespace std;

template <typename I>
I random_element(I begin, I end)
{
    const unsigned long n = std::distance(begin, end);

    unsigned long k;
    k = std::rand() % n;

    std::advance(begin, k);
	return begin;
}


class meteorManager {
private:
  vector<Meteor*> meteors;
  vector<Meteor*>::iterator it;
  b2World *world;
//  int meteorTexture;
  vector<Texture> textures;
//  vector<Texture>::iterator tex_it;
  
public:
  meteorManager() {
  }
  meteorManager(b2World *w) {
    world = w;
  }
//  void setTexture(int texture);
  void addTexture(const Texture& tex);
  void drawTexture();
  void draw();
  void create();
  void destroy();
  int collision();
};

#endif
