#include "Vulpine/Scene/Entity.h"
namespace Vulpine {
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}
}
