#pragma once

#include "chComponent.h"
#include "chMesh.h"
#include "chMaterial.h"
#include "chBaseRenderer.h"

using namespace ch::graphics;
namespace ch
{
	class SpriteRenderer : public BaseRenderer
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}
