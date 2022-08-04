#ifndef __VP_SCENE_H__
#define __VP_SCENE_H__

#include <string>

namespace Vulpine {

  class Entity;

	class Scene {
	public:
    Scene();
    ~Scene();

    Entity CreateEntity(const std::string& name = std::string());
    void DestroyEntity(Entity entity);

    void Start();
    void Stop();

    void Update(float deltaTime);
  private:
    template<typename T>
    void OnComponentAdded(Entity entity, T& component);

    void RenderScene();
	private:
    int m_Registry;
	};
}

#endif
