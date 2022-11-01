#ifndef __VP_ENTITY_H__
#define __VP_ENTITY_H__

#include <Vulpine/Scene/Scene.h>
#include <utility>

namespace Vulpine {

    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);

        template<typename Comp, typename... Args>
        Comp& AddComponent(Args&&... args) {
            Comp& component = m_Scene->m_Registry.emplace<Comp>(m_EntityHandle, std::forward<Args>(args)...);
            m_Scene->OnComponentAdded<Comp>(*this, component);
            return component
        }

        template<typename Comp, typename... Args>
        Comp& AddOrReplaceComponent(Args&&... args) {
            Comp& component = m_Scene->m_Registry.emplace_or_replace<Comp>(m_EntityHandle, std::forward<Args>(args)...);
            m_Scene->OnComponentAdded<Comp>(*this, component);
            return component
        }

        template<typename Comp>
        Comp& GetComponent()
        {
            return m_Scene->m_Registry.get<Comp>(m_EntityHandle);
        }

        template<typename Comp>
        bool HasComponent()
        {
            m_Scene->m_Registry.
            return m_Scene->m_Registry.all_of<Comp>(m_EntityHandle);
        }

        template<typename Comp>
        void RemoveComponent()
        {
            m_Scene->m_Registry.remove<Comp>(m_EntityHandle);
        }

        entt::entity m_EntityHandle{ entt::null };
    private:
        Scene* m_Scene = nullptr;
    };

}
#endif
