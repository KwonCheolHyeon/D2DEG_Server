#pragma once
#include "chResource.h"
#include "chShader.h"
#include "chTexture.h"
#include "chRenderer.h"
//#include "yaConstantBuffer.h"

using namespace ch::renderer;

namespace ch::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		Material(std::wstring _TextureName, std::wstring _ShaderName);
		virtual ~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGPUParam param, void* data);
		void Bind();
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		std::shared_ptr<Shader> GetShader() { return mShader; }

		void SetTexture(eTextureSlot slot, std::shared_ptr<Texture> texture) { mTexture[(UINT)slot] = texture; }
		std::shared_ptr<Texture> GetTexture(eTextureSlot slot) { return mTexture[(UINT)slot]; }

		eRenderingMode GetRenderingMode() { return mMode; }
		void SetRenderingMode(eRenderingMode mode) { mMode = mode; }

	private:
		std::shared_ptr<Shader>		mShader;
		std::shared_ptr<Texture>	mTexture[(UINT)eTextureSlot::End];
		MaterialCB					mCB;
		eRenderingMode				mMode;
	};
}

