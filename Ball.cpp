#include "Ball.h"
#include <OgreSubMesh.h>
#include <OgreMeshManager.h>

Ball::Ball(Ogre::SceneManager* mgr,
           const std::string& name,
           float r,
           const Ogre::Vector3& position)
  : GameObject(mgr, mgr->createEntity(name + "_sphere", Ogre::SceneManager::PT_SPHERE), name, position), radius(r)
{
  float scale = r / 50.0f;  // Default sphere radius = 50.
  setScale(Ogre::Vector3(scale, scale, scale));
}
