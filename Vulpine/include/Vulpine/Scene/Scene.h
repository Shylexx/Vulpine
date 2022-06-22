#ifndef __VP_SCENE_H__
#define __VP_SCENE_H__

#include <vector>
#include "Vulpine/Scene/Layer.h"


namespace Vulpine {
	class Scene {
	public:
		virtual void Update(float deltaTime);
	private:
		std::vector<Layer*> m_Layers;
	};
}

#endif