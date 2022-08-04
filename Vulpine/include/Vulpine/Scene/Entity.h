#ifndef __VP_ENTITY_H__
#define __VP_ENTITY_H__

#include <Vulpine/Scene/Scene.h>

class Entity
{
public:
  Entity(Scene* scene);

  template<typename Comp>
  void AddComponent() {
    m_Scene->registry.AddComponent<Comp>(m_EntityID);
  }

private:
  Scene* m_Scene;
  int m_EntityID;

};

#endif
