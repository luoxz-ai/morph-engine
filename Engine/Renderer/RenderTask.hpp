﻿#pragma once
#include "Engine/Core/common.hpp"
#include "Engine/Math/Primitives/mat44.hpp"
#include "Engine/Renderer/type.h"

class Camera;
class Mesh;
class Material;
class Transform;
class Program;
class RenderTask {
public:
  Camera* camera = nullptr;
	const Transform* transform = nullptr;
	const Mesh* mesh = nullptr;
	const Material* material = nullptr;
  const Program* program = nullptr;
	uint passIndex;
	uint lightIndices[NUM_MAX_LIGHTS];
	uint lightCount;

	uint layer;
	uint queue;

	static void sort(const Camera& cam, span<RenderTask> tasks);
};
