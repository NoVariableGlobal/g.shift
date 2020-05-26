#pragma once

#include "Factory.h"
#include "GuiLabelC.h"

namespace CEGUI {
    class Window;
}

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(GuiCoinsPickedLabelC);

class GuiCoinsPickedLabelC final : public GuiLabelComponent {
  private:
  public:
    GuiCoinsPickedLabelC() = default;
    ~GuiCoinsPickedLabelC() = default;

    void createText();
};