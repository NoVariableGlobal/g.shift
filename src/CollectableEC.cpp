#include "CollectableEC.h"
#include "AnimationLC.h"
#include "CoinCounterC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SoundComponent.h"

#include <json.h>

void CollectableEC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseEC(this);
}

void CollectableEC::checkEvent() {
    if (reinterpret_cast<RigidbodyPC*>(father_->getComponent("RigidbodyPC"))
            ->collidesWith("Player")) {
        reinterpret_cast<CoinCounterC*>(
            scene_->getEntityById("CoinManager")->getComponent("CoinCounterC"))
            ->pickCoin();
        SoundComponent* soundManager =
            dynamic_cast<SoundComponent*>(scene_->getEntityById("MusicManager")
                                              ->getComponent("SoundComponent"));
        soundManager->playSound("coinSound");
        scene_->deleteEntity(father_);
    }
}

int CollectableEC::getValue() { return value_; }

void CollectableEC::setValue(int value) { value_ = value; }

void CollectableEC::setAnimations() {
    animations_ =
        reinterpret_cast<AnimationLC*>(father_->getComponent("AnimationLC"));
}

void CollectableEC::playAnimation() { animations_->startAnimation("idle"); }

// FACTORY INFRASTRUCTURE
CollectableECFactory::CollectableECFactory() = default;

Component* CollectableECFactory::create(Entity* _father, Json::Value& _data,
                                        Scene* _scene) {
    CollectableEC* collectable = new CollectableEC();
    _scene->getComponentsManager()->addEC(collectable);

    collectable->setFather(_father);
    collectable->setScene(_scene);

    if (!_data["value"].asInt())
        throw std::exception("CollectableEC: value is not an int");
    collectable->setValue(_data["value"].asInt());

    collectable->setActive(true);

    collectable->setAnimations();
    collectable->playAnimation();

    return collectable;
};

DEFINE_FACTORY(CollectableEC)