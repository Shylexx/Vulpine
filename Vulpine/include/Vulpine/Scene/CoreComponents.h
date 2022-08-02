#ifndef __VP_CORE_COMPONENTS_H__
#define __VP_CORE_COMPONENTS_H__

#include <glm/glm.hpp>

namespace Vulpine
{

  struct TransformComponent
  {
    glm::vec3 Translation = {0.0f, 0.0f, 0.0f};
    glm::vec3 Rotation = {0.0f,0.0f,0.0f};
    glm::vec3 Scale = {0.0f, 0.0f, 0.0f};
  };

}

#endif
