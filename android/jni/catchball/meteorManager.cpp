#include "meteorManager.h"
#include <iostream>
 
using namespace std;
//void meteorManager::setTexture(int texture) {
//  meteorTexture = texture;
//}

void meteorManager::drawTexture() {
//  LOGI("rysuje textury dla %i meteorow", meteors.size() );
  for(it=meteors.begin();it<meteors.end();it++) {
    (*it)->drawTexture();
  }
}

void meteorManager::addTexture(const Texture& tex){
	LOGI("Dodaje texture");
//	LOGI("Dodaje texture: %s \n", tex.getColor() );
	textures.push_back(tex);
}

void meteorManager::draw() {
  for(it=meteors.begin();it<meteors.end();it++) {
    (*it)->draw();
  }
}

void meteorManager::create() {
	vector<Texture>::iterator cor_it;
//	LOGI("Ilosc tekstur: %i \n", textures.size());
	cor_it = random_element(textures.begin(),textures.end());
//	LOGI("Wskaznik na: %i \n", distance(textures.begin(),cor_it));
	Meteor *tmp = new Meteor(world, LEFT, *cor_it);
	meteors.push_back(tmp);
//	LOGI("Stworzono meteor");
}

void meteorManager::destroy() {
  if((int) meteors.size() > 0) {
    world->DestroyBody((*meteors.begin())->getBody());
    meteors.erase(meteors.begin());
  }
}

int meteorManager::collision() {
	int health = 0;
	for(it=meteors.begin();it<meteors.end();it++) {
		if((*it)->getBody()->GetAngularVelocity()>0.0f || (*it)->getBody()->GetLinearVelocity().x>0.0f || (*it)->getBody()->GetWorldCenter().y<100) {
			world->DestroyBody((*it)->getBody());
			meteors.erase(it);
			health += 10;
		}
	}
	return health;
}
