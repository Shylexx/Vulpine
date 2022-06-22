#include "Vulpine/Scene/Scene.h"

namespace Vulpine {
	void Scene::Update(float deltaTime) {
		for (Layer* layer : m_Layers)
			layer->Update(deltaTime);
	}
}