#include "Physics.h"
#include "PhysicsCollider.h"
#include <iostream>

Physics::Physics(float gravity)
  : broadphase(new btDbvtBroadphase()),
    collisionConfiguration(new btDefaultCollisionConfiguration()),
    dispatcher(new btCollisionDispatcher(collisionConfiguration)),
    solver(new btSequentialImpulseConstraintSolver()),
    dynamicsWorld(new btDiscreteDynamicsWorld(
      dispatcher, broadphase, solver, collisionConfiguration
    ))
{ 
  dynamicsWorld->setGravity(btVector3(0, -gravity, 0));
}

Physics::~Physics() {
  delete dynamicsWorld;
  delete solver;
  delete dispatcher;
  delete collisionConfiguration;
  delete broadphase;
}

void Physics::stepSimulation(float timestep) {
  dynamicsWorld->stepSimulation(timestep, 10);
  
  // Handle collisions.
  int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
  //std::cout << "manifolds" << numManifolds <<  "\n";
  for (int i = 0; i < numManifolds; i++)
  {
      btPersistentManifold* contactManifold =
        dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
      const btCollisionObject* obA =
        static_cast<const btCollisionObject*>(contactManifold->getBody0());
      const btCollisionObject* obB =
        static_cast<const btCollisionObject*>(contactManifold->getBody1());

      PhysicsCollider* colliderA =
        static_cast<PhysicsCollider*>(obA->getUserPointer());
      PhysicsCollider* colliderB =
        static_cast<PhysicsCollider*>(obB->getUserPointer());

      colliderA->reportCollision(*colliderB);
      colliderB->reportCollision(*colliderA);
  }
}

btDynamicsWorld* Physics::getDynamicsWorld() {
  return dynamicsWorld;
}

PhysicsCollider* Physics::rayCast(const Ogre::Vector3& start,
                                  const Ogre::Vector3& direction,
                                  float maxDist) const
{
  Ogre::Vector3 end = start + direction * maxDist;
  btVector3 btStart(start.x, start.y, start.z);
  btVector3 btEnd(end.x, end.y, end.z);
  btCollisionWorld::ClosestRayResultCallback rayCallback(btStart, btEnd);

  dynamicsWorld->rayTest(btStart, btEnd, rayCallback);

  if (rayCallback.hasHit()) {
    const btCollisionObject* collObj = rayCallback.m_collisionObject;
    if (collObj != nullptr) {
      return static_cast<PhysicsCollider*>(collObj->getUserPointer());
    }
  }

  return nullptr;
}

const std::vector<PhysicsCollider*>
Physics::rayCastAll(const Ogre::Vector3& start,
                 const Ogre::Vector3& direction,
                 float maxDist) const {
  Ogre::Vector3 end = start + direction * maxDist;
  btVector3 btStart(start.x, start.y, start.z);
  btVector3 btEnd(end.x, end.y, end.z);
  btCollisionWorld::AllHitsRayResultCallback rayCallback(btStart, btEnd);

  dynamicsWorld->rayTest(btStart, btEnd, rayCallback);

  std::vector<PhysicsCollider*>
  colliders(rayCallback.m_collisionObjects.size());
  
  for (int i = 0; i < rayCallback.m_collisionObjects.size(); ++i) {
    const btCollisionObject* collObj = rayCallback.m_collisionObjects[i];
    if (collObj != nullptr) {
      colliders[i] = static_cast<PhysicsCollider*>(collObj->getUserPointer());
    }
  }

  return colliders;
}

