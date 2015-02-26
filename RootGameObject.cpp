#include "RootGameObject.h"

RootGameObject::RootGameObject(Ogre::SceneManager* sceneMgr, const std::string name){
	node = sceneMgr->getRootSceneNode()->createChildSceneNode(name + "node");
}

void RootGameObject::translate(const Ogre::Vector3& trans){
	node->translate(trans);
}

void RootGameObject::translate(float x, float y, float z) {
	node->translate(x, y, z);
}

void RootGameObject::setPosition(const Ogre::Vector3& position){
	node->setPosition(position);
}

const Ogre::Vector3 RootGameObject::getPosition() const {
	return node->getPosition();
}

void RootGameObject::setWorldPosition(const Ogre::Vector3& position) {
	node->_setDerivedPosition(position);
}

const Ogre::Vector3 RootGameObject::getWorldPosition() const {
	return node->_getDerivedPosition();
}

void RootGameObject::rotate(const Ogre::Vector3& axis, const Ogre::Radian& rads){
	node->rotate(axis, rads);
}

void RootGameObject::scale(const Ogre::Vector3& scale){
	node->scale(scale);
}

void RootGameObject::setScale(const Ogre::Vector3& scale){
	node->setScale(scale);
}
