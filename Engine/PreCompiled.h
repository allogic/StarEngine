#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <cstring>
#include <cassert>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>
#include <limits>
#include <functional>
#include <bitset>
#include <regex>

namespace fs = std::filesystem;

#define GLM_ENABLE_EXPERIMENTAL

	#include <Engine/GLM/glm.hpp>
	#include <Engine/GLM/ext.hpp>
	#include <Engine/GLM/gtc/matrix_transform.hpp>
	#include <Engine/GLM/gtc/quaternion.hpp>

#undef GLM_ENABLE_EXPERIMENTAL

#include <Engine/Types.h>
#include <Engine/Memory.h>
#include <Engine/Forward.h>
#include <Engine/Constants.h>
#include <Engine/SystemTime.h>
#include <Engine/Event.h>

#include <Engine/EnTT/EnTT.h>

#include <Engine/EnTT/Components/CameraComponents.h>
#include <Engine/EnTT/Components/ControllerComponents.h>
#include <Engine/EnTT/Components/LightComponents.h>
#include <Engine/EnTT/Components/PhysicsComponents.h>
#include <Engine/EnTT/Components/RenderComponents.h>
#include <Engine/EnTT/Components/TransformComponents.h>

#include <Engine/EnTT/Systems/TransformSystem.h>
#include <Engine/EnTT/Systems/ControllerSystem.h>
#include <Engine/EnTT/Systems/PhysicsSystem.h>

#include <Engine/AssetLoader/AssetLoader.h>

#include <Engine/AssetLoader/AssetReference/AssetReference.h>
#include <Engine/AssetLoader/AssetReference/MaterialReference.h>
#include <Engine/AssetLoader/AssetReference/ModelReference.h>
#include <Engine/AssetLoader/AssetReference/ShaderReference.h>
#include <Engine/AssetLoader/AssetReference/SkyBoxReference.h>
#include <Engine/AssetLoader/AssetReference/Texture2DReference.h>