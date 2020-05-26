#pragma once

#include "Component.h"
#include "Factory.h"

DECLARE_FACTORY(DeathControllerC)

class DeathControllerC final : public Component {
    bool activated_ = false;

  public:
    DeathControllerC() = default;
    ~DeathControllerC() = default;

    void destroy() override;

    void playerDeath();
};