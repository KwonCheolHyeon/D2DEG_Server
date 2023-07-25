#pragma once
#include "chComponent.h"
#include "chMesh.h"
#include "chMaterial.h"
#include "chBaseRenderer.h"

using namespace ch::graphics;
namespace ch
{
	class MeshRenderer : public BaseRenderer
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}