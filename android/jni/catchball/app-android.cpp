#include "app-android.h"
#include <GLES/gl.h>
#include "def.h"
#include "utils.h"

#include <vector>

#include "meteor.h"
#include "meteorManager.h"
#include "house.h"
#include "Ball.h"
#include "world.h"

#include "Box2D.h"

zip* APKArchive;

//buttonManager buttons;
meteorManager meteors;
//House house;
Ball ball;
World world;

//int to fixed point
#define iX(x) (x<<16)
//float ti fixed point
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

GLuint texture;

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGE("after %s() glError (0x%x)\n", op, error);
    }
}

static void loadAPK (const char* apkPath) {
  LOGI("Loading APK %s", apkPath);
  APKArchive = zip_open(apkPath, 0, NULL);
  if (APKArchive == NULL) {
    LOGE("Error loading APK");
    return;
  }

  //Just for debug, print APK contents
  int numFiles = zip_get_num_files(APKArchive);
  for (int i=0; i<numFiles; i++) {
    const char* name = zip_get_name(APKArchive, i, 0);
    if (name == NULL) {
      LOGE("Error reading zip file name at index %i : %s", zip_strerror(APKArchive));
      return;
    }
    LOGI("File %i : %s\n", i, name);
  }
}

JNIEXPORT void JNICALL Java_net_catchball_CatchBallRenderer_nativeInit
  (JNIEnv * env, jclass cls, jstring apkPath) {
  const char* str;
  jboolean isCopy;
  str = env->GetStringUTFChars(apkPath, &isCopy);
  loadAPK(str);

  int width, height;
  texture = loadTextureFromPNG("assets/sprites/texture.png", width, height);
  int bblue = loadTextureFromPNG("assets/sprites/button blue.png", width, height);
  int bred = loadTextureFromPNG("assets/sprites/button red.png", width, height);
//  int houseTexture = loadTextureFromPNG("assets/sprites/house.png", width, height);
  int meteor_b = loadTextureFromPNG("assets/sprites/meteor.png", width, height);
  int meteor_y = loadTextureFromPNG("assets/sprites/meteor-y.png", width, height);
  int meteor_r = loadTextureFromPNG("assets/sprites/meteor-r.png", width, height);
  int meteor_g = loadTextureFromPNG("assets/sprites/meteor-g.png", width, height);
  int ballTexture = loadTextureFromPNG("assets/sprites/ball.png", width, height);

  printGLString("Version", GL_VERSION);
  printGLString("Vendor", GL_VENDOR);
  printGLString("Renderer", GL_RENDERER);
  printGLString("Extensions", GL_EXTENSIONS);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  glClearColor(0,0,0,0);
  glColor4f(1,1,1,1);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  
	Texture texr(RED,meteor_r);
	Texture texg(GREEN,meteor_g);
	Texture texy(YELLOW,meteor_y);
	Texture texb(BRONZE,meteor_b);

LOGI("textures created");
//  house = House(world.getWorld());
//  house.setTexture(houseTexture);
  ball = Ball(world);
  ball.setTexture(ballTexture);
LOGI("Ball created");
  meteors = meteorManager(world.getWorld());
LOGI("Meteors created");
//  meteors.setTexture(meteor);
  meteors.addTexture(texb);
  meteors.addTexture(texr);
  meteors.addTexture(texy);
  meteors.addTexture(texg);
//  buttons.setTextures(bblue, bred);
LOGI("Textures for meteors added");
}

JNIEXPORT void JNICALL Java_net_catchball_CatchBallRenderer_nativeResize
  (JNIEnv *, jclass, jint w, jint h) {
  LOGI("nativeResize (%i,%i)", w, h);
  if(h == 0)
    h = 1;
  glViewport(0, 0, w, h);
  checkGlError("glViewport");
  glMatrixMode(GL_PROJECTION);
  const float ratio=w/(float)h;
  glLoadIdentity();
  //glOrthof(0, 15, 15/ratio, 0, -1, 1);
  glOrthof(0, w, 0, h, 0, 1);
  checkGlError("glViewport");
  glMatrixMode(GL_MODELVIEW);
}

JNIEXPORT void JNICALL Java_net_catchball_CatchBallRenderer_nativeRender
  (JNIEnv *, jclass) {
    
    static int i=0;
    i++;
    if(i>100) {
//		LOGI("Started creating meteors");
		meteors.create();
		i=0;
//		LOGI("Finished creating meteors");
    }
    
  world.getWorld()->Step(1.0f / 60.0f, 6, 2);
//  house.decreaseHealth(meteors.collision());

  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

//  buttons.drawTexture();
//  house.drawTexture();
  ball.drawTexture();   
  meteors.drawTexture();
}

JNIEXPORT void JNICALL Java_net_catchball_CatchBallGLSurface_processTouch
  (JNIEnv *, jclass, jfloat x1, jfloat y1, jfloat x2, jfloat y2) {
	ball.rotate(x1,y1,x2,y2);
}

JNIEXPORT void JNICALL Java_net_catchball_CatchBallGLSurface_nativePause
  (JNIEnv *, jclass) {
  ball.stopRotating();
//  LOGI("Pause");
}

