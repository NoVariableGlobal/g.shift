#include "CoinCounterC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "RigidbodyPC.h"
#include "Scene.h"

#include <json.h>

#include <iostream> // PROVISIONAL

void CoinCounterC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

int CoinCounterC::getTotalCoins() { return totalCoins_; }

void CoinCounterC::setTotalCoins(int total) { totalCoins_ = total; }

void CoinCounterC::pickCoin() {
    coinsPicked_++;
    std::cout << "\nCOIN PICKED      " << coinsPicked_ << " de " << totalCoins_
              << "\n"; // PROVISIONAL
}

int CoinCounterC::getCoinsPicked() { return coinsPicked_; }

// FACTORY INFRASTRUCTURE
CoinCounterCFactory::CoinCounterCFactory() = default;

Component* CoinCounterCFactory::create(Entity* _father, Json::Value& _data,
                                       Scene* _scene) {
    CoinCounterC* counter = new CoinCounterC();
    _scene->getComponentsManager()->addDC(counter);

    counter->setFather(_father);
    counter->setScene(_scene);

    if (!_data["totalCoins"].asInt())
        throw std::exception("CollectableEC: totalCoins is not an int");
    counter->setTotalCoins(_data["totalCoins"].asInt());

    counter->setActive(true);

    return counter;
};

DEFINE_FACTORY(CoinCounterC);