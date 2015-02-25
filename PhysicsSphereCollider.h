#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Physics.h"
#include "PhysicsCollider.h"
#include <memory>

class PhysicsSphereCollider : public PhysicsCollider {
  
  btCollisionShape* collisionShape;
  btDefaultMotionState* motionState;
  btRigidBody* rigidBody;
  std::shared_ptr<GameObject> gameObject;
  bool isDynamic;
 
public: 
  PhysicsSphereCollider(std::shared_ptr<GameObject> go, Physics& physics, float radius, float mass);
  ~PhysicsSphereCollider();
  void update(float deltaTime) const override;

};
