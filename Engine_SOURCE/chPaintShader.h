#pragma once
#include "chComputeShader.h"
#include "chTexture.h"

namespace ch::graphics
{
	class PaintShader : public ComputeShader
	{
	public:
		PaintShader();
		~PaintShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetTarget(std::shared_ptr<Texture> texture) { mTarget = texture; }

	private:
		std::shared_ptr<Texture> mTarget;
	};
}
