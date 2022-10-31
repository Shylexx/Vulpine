#ifndef __VP_ENTITY_H__
#define __VP_ENTITY_H__

#include <Vulpine/Scene/Scene.h>

namespace Vulpine {

    class Entity
    {
    public:
        Entity(Scene* scene);

        template<typename Comp>
        void AddComponent() {
            m_Scene->m_Registry.emplace<Comp>();
        }

    private:
        Scene* m_Scene;
        int m_EntityID;

    };

}
#endif
