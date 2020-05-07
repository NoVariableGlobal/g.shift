#pragma once

#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(SpikeEC);

class SpikeEC : public EventComponent {
  private:
    bool collisioned = false;

  public:
    SpikeEC() = default;
    ~SpikeEC() = default;

	virtual void destroy();
    virtual void checkEvent();
};