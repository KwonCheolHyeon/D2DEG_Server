#pragma once
#define _WINSOCKAPI_

#include <WinSock2.h>
#include "CommonInclude.h"
#include "chMath.h"
#include "chGraphicDevice_DX11.h"
		  
#include "chMesh.h"
#include "chShader.h"
#include "chConstantBuffer.h"
#include "chCamera.h"
#include "chLight.h"
#include "chStructedBuffer.h"

using namespace ch::math;
using namespace ch::graphics;

namespace ch::renderer
{
	struct Vertex
	{
		Vector4 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;
		Vector2 xy;
		Vector3 xyz;
		Vector4 xyzw;
		Matrix matrix;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
	};

	CBUFFER(AnimationCB, CBSLOT_ANIMATION)
	{
		Vector2 leftTop;
		Vector2 size;
		Vector2 offset;
		Vector2 atlasSize;

		UINT type;
	};

	//CBSLOT_NUMBEROFLIGHT
	CBUFFER(LightCB, CBSLOT_NUMBEROFLIGHT)
	{
		UINT numberOfLight;
	};

	CBUFFER(ParticleSystemCB, CBSLOT_PARTICLESYSTEM) 
	{
		Vector4 worldPosition;
		Vector4 startColor;
		Vector4 startSize;

		UINT maxParticles;
		UINT simulationSpace;
		float radius;
		float startSpeed;

		float startLifeTime;
		float deltaTime;
		float elapsedTime; //누적시간
		int padding;
	};

	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 noiseSize;
		float noiseTime;
	};

	extern Vertex vertexes[4];
	extern Camera* mainCamera;
	extern ConstantBuffer* constantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<Camera*> cameras[];
	extern std::vector<DebugMesh> debugMeshes;
	extern std::vector<LightAttribute> lights;
	extern StructedBuffer* lightsBuffer;

	void Initialize();
	void Render();
	void Release();

	//Renderer
	void PushLightAttribute(LightAttribute lightAttribute);
	void BindLights();
	void BindNoiseTexture();
	void CopyRenderTarget();

}

