#include "Vulpine/Scene/Scene.h"
#include "Vulpine/Scene/Entity.h"

namespace Vulpine {
	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity.m_EntityHandle);
	}
	void Scene::Update(float deltaTime) {
		//for (Layer* layer : m_Layers)
			//layer->Update(deltaTime);
  }
}
