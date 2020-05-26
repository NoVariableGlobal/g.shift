#pragma once

#include "Factory.h"
#include "InputComponent.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(EscapePressIC);

class EscapePressIC : public InputComponent {
    bool pressing_ = false;
    bool up_ = false;

  public:
    void handleInput(const SDL_Event& _event) override;
};
