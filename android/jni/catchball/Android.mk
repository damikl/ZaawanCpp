LOCAL_PATH := $(call my-dir)

BOX2D_SOURCES := Box2D/Collision/b2BroadPhase.cpp
BOX2D_SOURCES += Box2D/Collision/b2CollideCircle.cpp
BOX2D_SOURCES += Box2D/Collision/b2CollideEdge.cpp
BOX2D_SOURCES += Box2D/Collision/b2CollidePolygon.cpp
BOX2D_SOURCES += Box2D/Collision/b2Collision.cpp
BOX2D_SOURCES += Box2D/Collision/b2Distance.cpp
BOX2D_SOURCES += Box2D/Collision/b2DynamicTree.cpp
BOX2D_SOURCES += Box2D/Collision/b2TimeOfImpact.cpp
BOX2D_SOURCES += Box2D/Collision/Shapes/b2CircleShape.cpp
BOX2D_SOURCES += Box2D/Collision/Shapes/b2EdgeShape.cpp
BOX2D_SOURCES += Box2D/Collision/Shapes/b2PolygonShape.cpp
BOX2D_SOURCES += Box2D/Common/b2BlockAllocator.cpp
BOX2D_SOURCES += Box2D/Common/b2Math.cpp
BOX2D_SOURCES += Box2D/Common/b2Settings.cpp
BOX2D_SOURCES += Box2D/Common/b2StackAllocator.cpp
BOX2D_SOURCES += Box2D/Dynamics/b2Body.cpp
BOX2D_SOURCES += Box2D/Dynamics/b2ContactManager.cpp
BOX2D_SOURCES += Box2D/Dynamics/b2Fixture.cpp
BOX2D_SOURCES += Box2D/Dynamics/b2Island.cpp
BOX2D_SOURCES += Box2D/Dynamics/b2World.cpp
BOX2D_SOURCES += Box2D/Dynamics/b2WorldCallbacks.cpp
BOX2D_SOURCES += Box2D/Dynamics/Contacts/b2CircleContact.cpp
BOX2D_SOURCES += Box2D/Dynamics/Contacts/b2Contact.cpp
BOX2D_SOURCES += Box2D/Dynamics/Contacts/b2ContactSolver.cpp
BOX2D_SOURCES += Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
BOX2D_SOURCES += Box2D/Dynamics/Contacts/b2PolygonContact.cpp
BOX2D_SOURCES += Box2D/Dynamics/Contacts/b2TOISolver.cpp
BOX2D_SOURCES += Box2D/Dynamics/Joints/b2DistanceJoint.cpp
BOX2D_SOURCES += Box2D/Dynamics/Joints/b2FrictionJoint.cpp
BOX2D_SOURCES += Box2D/Dynamics/Joints/b2GearJoint.cpp
BOX2D_SOURCES += Box2D/Dynamics/Joints/b2Joint.cpp
BOX2D_SOURCES += Box2D/Dynamics/Joints/b2LineJoint.cpp
BOX2D_SOURCES += Box2D/Dynamics/Joints/b2MouseJoint.cpp
BOX2D_SOURCES += Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
BOX2D_SOURCES += Box2D/Dynamics/Joints/b2PulleyJoint.cpp
BOX2D_SOURCES += Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
BOX2D_SOURCES += Box2D/Dynamics/Joints/b2WeldJoint.cpp

include $(CLEAR_VARS)

LOCAL_MODULE := catchball

LOCAL_ARM_MODE  := arm
LOCAL_C_INCLUDES := $(LOCAL_PATH)/Box2D $(LOCAL_PATH)/../libzip/ $(LOCAL_PATH)/../libpng/
LOCAL_SRC_FILES := $(BOX2D_SOURCES) meteor.cpp meteorManager.cpp house.cpp world.cpp app-android.cpp utils.cpp ball.cpp
LOCAL_STATIC_LIBRARIES := libzip libpng

#-Wno-psabi to remove warning about GCC 4.4 va_list warning
LOCAL_CFLAGS := -DANDROID_NDK -Wno-psabi

LOCAL_DEFAULT_CPP_EXTENSION := cpp 
   

LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog -lz

include $(BUILD_SHARED_LIBRARY)
