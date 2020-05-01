#include "ChangeGravityIC.h"
#include "AmbientLightC.h"
#include "ComponentsManager.h"
#include "ConstantMovementC.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TridimensionalObjectRC.h"

#include <iostream>
#include <json.h>

ChangeGravityIC::ChangeGravityIC() {}

ChangeGravityIC::~ChangeGravityIC() {}

void ChangeGravityIC::handleInput(const SDL_Event& _event) {
    if (_event.type == SDL_KEYDOWN && _event.key.keysym.sym == SDLK_SPACE) {
        movingIzq = !movingIzq;

        RigidbodyPC* body =
            reinterpret_cast<RigidbodyPC*>(father_->getComponent("RigidbodyPC"));

        body->setGravity(!movingIzq ? Ogre::Vector3(speed, 0.0f, 0.0f)
                                    : Ogre::Vector3(-speed, 0.0f, 0.0f));

        Ogre::Vector3 velocity = body->getLinearVelocity();

        body->setLinearVelocity(Ogre::Vector3(0.0f, velocity.y, 0.0f));

        reinterpret_cast<AmbientLightC*>(
            scene->getEntitybyId("Light")->getComponent("AmbientLightC"))
            ->setColour(!movingIzq ? Ogre::Vector3(0.0f, 0.0f, 1.0f)
                                   : Ogre::Vector3(0.5f, 0.0f, 0.5f));
    }
}

void ChangeGravityIC::setSpeed(float _speed) { speed = _speed; }

// FACTORY INFRASTRUCTURE

ChangeGravityICFactory::ChangeGravityICFactory() = default;

Component* ChangeGravityICFactory::create(Entity* _father, Json::Value& _data,
                                          Scene* scene) {
    ChangeGravityIC* changeGravity = new ChangeGravityIC();
    scene->getComponentsManager()->addIC(changeGravity);

    changeGravity->setFather(_father);
    changeGravity->setScene(scene);

    if (!_data["speed"].isDouble())
        throw std::exception("ChangeGravityIC: speed is not a double");

    changeGravity->setSpeed(_data["speed"].asDouble());

    return changeGravity;
};

DEFINE_FACTORY(ChangeGravityIC);