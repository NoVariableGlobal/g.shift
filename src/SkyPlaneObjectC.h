#pragma once

#include "Component.h"
#include "Factory.h"

#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SkyPlaneObjectC);

class SkyPlaneObjectC : public Component {

  public:
    SkyPlaneObjectC() = default;
    virtual ~SkyPlaneObjectC() = default;

    virtual void destroy();

    // Sets a given material to the object
    void CreateSkyPlane(std::string normal, float distance, float bow,
                        std::string material);
};
