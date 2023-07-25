#include "chRenderer.h"
#include "chTime.h"
#include "chResources.h"
#include "chMaterial.h"
#include "chSceneManager.h"
#include "chPaintShader.h"
#include "chParticleShader.h"


namespace ch::renderer
{
	Vertex vertexes[4] = {};
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	Camera* mainCamera = nullptr;
	std::vector<Camera*> cameras[(UINT)eSceneType::End];
	std::vector<DebugMesh> debugMeshes;
	std::vector<LightAttribute> lights;
	StructedBuffer* lightsBuffer = nullptr;

	std::shared_ptr<Texture> postProcessTexture = nullptr;

	void LoadMesh()
	{
#pragma region POINT MESH
		Vertex v = {};
		std::shared_ptr<Mesh> pointMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"PointMesh", pointMesh);
		pointMesh->CreateVertexBuffer(&v, 1);
		UINT pointIndex = 0;
		pointMesh->CreateIndexBuffer(&pointIndex, 1);
#pragma endregion
#pragma region RECT MESH
		//RECT
		vertexes[0].pos = Vector4(-0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Mesh
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);

		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
#pragma endregion
#pragma region DEBUG RECTMESH
		vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.1f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, -0.1f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, -0.1f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.1f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Mesh
		std::shared_ptr<Mesh> debugmesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugRectMesh", debugmesh);
		debugmesh->CreateVertexBuffer(vertexes, 4);
		debugmesh->CreateIndexBuffer(indexes.data(), indexes.size());
#pragma endregion
#pragma region CIRCLE MESH
		std::vector<Vertex> circleVtxes;
		Vertex center = {};
		center.pos = Vector4(0.0f, 0.0f, -0.00001f, 1.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		center.uv = Vector2::Zero;

		circleVtxes.push_back(center);

		int iSlice = 80;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;


		for (size_t i = 0; i < iSlice; i++)
		{
			Vertex vtx = {};
			vtx.pos = Vector4
			(
				fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, -0.00001f, 1.0f
			);
			vtx.color = center.color;

			circleVtxes.push_back(vtx);
		}
		indexes.clear();
		for (size_t i = 0; i < iSlice - 2; i++)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		// Crate Mesh
		std::shared_ptr<Mesh> cirlceMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"CircleMesh", cirlceMesh);
		cirlceMesh->CreateVertexBuffer(circleVtxes.data(), circleVtxes.size());
		cirlceMesh->CreateIndexBuffer(indexes.data(), indexes.size());
#pragma endregion
	}

	void LoadShader()
	{
#pragma region DEFAULT TRIANGLE SHADER
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");

		Resources::Insert<Shader>(L"RectShader", shader);
#pragma endregion
#pragma region SPRITE SHADER
		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		spriteShader->SetRSState(eRSType::SolidNone);
		Resources::Insert<Shader>(L"SpriteShader", spriteShader);
#pragma endregion
#pragma region UI SHADER
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"UIShader", uiShader);
#pragma endregion
#pragma region GRID SHADER
		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		gridShader->SetRSState(eRSType::SolidNone);
		gridShader->SetDSState(eDSType::NoWrite);
		gridShader->SetBSState(eBSType::AlphaBlend);

		Resources::Insert<Shader>(L"GridShader", gridShader);
#pragma endregion
#pragma region DEBUG SHADER
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetRSState(eRSType::SolidNone);
		debugShader->SetDSState(eDSType::NoWrite);
		debugShader->SetBSState(eBSType::AlphaBlend);
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		Resources::Insert<Shader>(L"DebugShader", debugShader);
#pragma endregion
#pragma region PAINT SHADER
		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		Resources::Insert<PaintShader>(L"PaintShader", paintShader);
#pragma endregion
#pragma region PARTICLE SHADER
		std::shared_ptr<Shader> particleShader = std::make_shared<Shader>();
		particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		particleShader->SetRSState(eRSType::SolidNone);
		particleShader->SetDSState(eDSType::NoWrite);
		particleShader->SetBSState(eBSType::AlphaBlend);
		particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		Resources::Insert<Shader>(L"ParticleShader", particleShader);

		std::shared_ptr<ParticleShader> particleCS = std::make_shared<ParticleShader>();
		Resources::Insert<ParticleShader>(L"ParticleCS", particleCS);
		particleCS->Create(L"ParticleCS.hlsl", "main");
#pragma endregion

#pragma region POST PROCESS SHADER
		std::shared_ptr<Shader> postProcessShader = std::make_shared<Shader>();
		postProcessShader->Create(eShaderStage::VS, L"PostProcessVS.hlsl", "main");
		postProcessShader->Create(eShaderStage::PS, L"PostProcessPS.hlsl", "main");
		postProcessShader->SetDSState(eDSType::NoWrite);
		Resources::Insert<Shader>(L"PostProcessShader", postProcessShader);
#pragma endregion
	}

	void SetUpState()
	{
#pragma region Input layout
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 16;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 32;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;


		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, shader->GetVSBlobBufferPointer()
			, shader->GetVSBlobBufferSize()
			, shader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, spriteShader->GetVSBlobBufferPointer()
			, spriteShader->GetVSBlobBufferSize()
			, spriteShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, uiShader->GetVSBlobBufferPointer()
			, uiShader->GetVSBlobBufferSize()
			, uiShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, gridShader->GetVSBlobBufferPointer()
			, gridShader->GetVSBlobBufferSize()
			, gridShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, debugShader->GetVSBlobBufferPointer()
			, debugShader->GetVSBlobBufferSize()
			, debugShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, particleShader->GetVSBlobBufferPointer()
			, particleShader->GetVSBlobBufferSize()
			, particleShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> postProcessShader = Resources::Find<Shader>(L"PostProcessShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, postProcessShader->GetVSBlobBufferPointer()
			, postProcessShader->GetVSBlobBufferSize()
			, postProcessShader->GetInputLayoutAddressOf());

#pragma endregion
#pragma region sampler state
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;

		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Point].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf()
		);

		GetDevice()->BindsSamplers((UINT)eSamplerType::Point
			, 1, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Linear
			, 1, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic
			, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer state
		D3D11_RASTERIZER_DESC rsDesc = {};
		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Less].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Greater].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		//None
		blendStates[(UINT)eBSType::Default] = nullptr;

		D3D11_BLEND_DESC bsDesc = {};
		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;

		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion

	}

	void LoadBuffer()
	{
#pragma region CONSTANT BUFFER
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::Animation] = new ConstantBuffer(eCBType::Animation);
		constantBuffers[(UINT)eCBType::Animation]->Create(sizeof(AnimationCB));

		constantBuffers[(UINT)eCBType::Light] = new ConstantBuffer(eCBType::Light);
		constantBuffers[(UINT)eCBType::Light]->Create(sizeof(LightCB));

		constantBuffers[(UINT)eCBType::ParticleSystem] = new ConstantBuffer(eCBType::ParticleSystem);
		constantBuffers[(UINT)eCBType::ParticleSystem]->Create(sizeof(ParticleSystemCB));

		constantBuffers[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffers[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

#pragma endregion
#pragma region STRUCTED BUFFER
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 128, eSRVType::SRV, nullptr, true);
#pragma endregion
	}

	void LoadTexture()
	{
#pragma region STATIC TEXTURE
		Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		Resources::Load<Texture>(L"DefaultSprite", L"Light.png");
		Resources::Load<Texture>(L"HPBarTexture", L"HPBar.png");
		Resources::Load<Texture>(L"CartoonSmoke", L"particle\\CartoonSmoke.png");
		Resources::Load<Texture>(L"noise_01", L"noise\\noise_01.png");
		Resources::Load<Texture>(L"noise_02", L"noise\\noise_02.png");
		Resources::Load<Texture>(L"noise_03", L"noise\\noise_03.jpg");

#pragma endregion
#pragma region DYNAMIC TEXTURE
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE
			| D3D11_BIND_UNORDERED_ACCESS);
		Resources::Insert<Texture>(L"PaintTexture", uavTexture);
#pragma endregion
#pragma region NOISE
		//noise
		postProcessTexture = std::make_shared<Texture>();
		postProcessTexture->Create(1600, 900, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE);
		postProcessTexture->BindShaderResource(eShaderStage::PS, 60);
#pragma endregion
		Resources::Load<Texture>(L"FadeEffectTexture", L"black.jpg");
		Resources::Load<Texture>(L"EmptyTexture", L"empty.png");
		//main menu
		Resources::Load<Texture>(L"mainBG", L"enterthe\\mainmenu\\BackGround.png");
		Resources::Load<Texture>(L"mainMenu", L"enterthe\\mainmenu\\main_menu.png");

		//UI
		Resources::Load<Texture>(L"Fullheart", L"enterthe\\UI\\hp\\FullHeart.png");
		Resources::Load<Texture>(L"HalfHeart", L"enterthe\\UI\\hp\\HalfHeart.png");
		Resources::Load<Texture>(L"NoHeart", L"enterthe\\UI\\hp\\NoHeart.png");

		// UI\\CrossHead
		Resources::Load<Texture>(L"Crosshead", L"enterthe\\UI\\crossHead\\crosshair.png");

		//player
		Resources::Load<Texture>(L"PlayerIdle", L"idle01.png");
		Resources::Load<Texture>(L"PlayerIdleRight", L"idleR01.png");
		Resources::Load<Texture>(L"PlayerIdleLeft", L"idleL01.png");

		//playerHand
		Resources::Load<Texture>(L"PlayerHand", L"enterthe\\character\\hand.png");

#pragma region ¸ó½ºÅÍ
		Resources::Load<Texture>(L"BulletKinIdle", L"enterthe\\enemy\\bullet_Kin\\idle\\idle_02.png");

#pragma endregion

#pragma region ¸Ê
		Resources::Load<Texture>(L"Map_01_Texture", L"enterthe\\Map\\map\\map01.png");
		Resources::Load<Texture>(L"Map_02_Texture", L"enterthe\\Map\\map\\map02.png");
		Resources::Load<Texture>(L"Map_03_Texture", L"enterthe\\Map\\map\\map03.png");
		Resources::Load<Texture>(L"Map_04_Texture", L"enterthe\\Map\\map\\map04.png");
		Resources::Load<Texture>(L"Map_05_Texture", L"enterthe\\Map\\map\\map05.png");
		Resources::Load<Texture>(L"Map_06_Texture", L"enterthe\\Map\\map\\map06.png");
		Resources::Load<Texture>(L"Map_07_Texture", L"enterthe\\Map\\map\\map07.png");
		Resources::Load<Texture>(L"Map_08_Texture", L"enterthe\\Map\\map\\map08.png");
		Resources::Load<Texture>(L"Map_09_Texture", L"enterthe\\Map\\map\\map09.png");
		Resources::Load<Texture>(L"Map_10_Texture", L"enterthe\\Map\\map\\map10.png");
		Resources::Load<Texture>(L"Map_11_Texture", L"enterthe\\Map\\map\\map11.png");
		Resources::Load<Texture>(L"Map_vertical_Texture", L"enterthe\\Map\\map\\vertical_map.png");
		Resources::Load<Texture>(L"Map_horizontal_Texture", L"enterthe\\Map\\map\\horizontal_map.png");
		Resources::Load<Texture>(L"Map_sample_Texture", L"enterthe\\Map\\map\\map_sample.png");
		Resources::Load<Texture>(L"Map_sample_Texture2", L"enterthe\\Map\\map\\map_sample2.png");
		Resources::Load<Texture>(L"Black_Texture", L"black.jpg");
#pragma endregion
#pragma region ¿ÀºêÁ§Æ®
		Resources::Load<Texture>(L"Table_Default", L"enterthe\\object\\table\\table_default.png"); //±âº» Ã¥»ó

		Resources::Load<Texture>(L"Table_Front_01", L"enterthe\\object\\table\\front\\table_front_01.png"); //
		Resources::Load<Texture>(L"Table_Front_02", L"enterthe\\object\\table\\front\\table_front_02.png"); //
		
		Resources::Load<Texture>(L"Table_Back_01", L"enterthe\\object\\table\\back\\table_back_01.png"); //
		Resources::Load<Texture>(L"Table_Back_02", L"enterthe\\object\\table\\back\\table_back_02.png"); //

		Resources::Load<Texture>(L"Table_Left_01", L"enterthe\\object\\table\\left\\table_left_01.png");
		Resources::Load<Texture>(L"Table_Left_02", L"enterthe\\object\\table\\left\\table_left_02.png");

		Resources::Load<Texture>(L"Table_Right_01", L"enterthe\\object\\table\\right\\table_right_01.png");
		Resources::Load<Texture>(L"Table_Right_02", L"enterthe\\object\\table\\right\\table_right_02.png");
#pragma endregion
		//¹«±â
		Resources::Load<Texture>(L"W_pistol", L"enterthe\\Waepone\\PistolFolder\\pistol_Idle.png");
		Resources::Load<Texture>(L"W_fightsabreSprite", L"enterthe\\Waepone\\FightSabre\\Item.png");
		//ÃÑ¾Ë
		Resources::Load<Texture>(L"W_Bullet", L"enterthe\\Waepone\\Bullet\\bulit.png");
		Resources::Load<Texture>(L"W_Bullet_02", L"enterthe\\Waepone\\FightSabre\\bullet\\bullet01.png");

		//Àû ÃÑ¾Ë
		Resources::Load<Texture>(L"Enemy_Bullet", L"enterthe\\enemy\\enemy_bullet.png");
		//bg
		Resources::Load<Texture>(L"FloatSprite", L"battleField.png");

		//zelda
		Resources::Load<Texture>(L"ZeldaSprite", L"Zelda.png");

		//UI
#pragma region UI
		Resources::Load<Texture>(L"CrossHairSprite", L"enterthe\\UI\\crossHair\\crosshair.png");
		#pragma region UI_Heart
		Resources::Load<Texture>(L"FullHeartSprite", L"enterthe\\UI\\hp\\FullHeart.png");
		Resources::Load<Texture>(L"HalfHeartSprite", L"enterthe\\UI\\hp\\HalfHeart.png");
		Resources::Load<Texture>(L"NoHeartSprite", L"enterthe\\UI\\hp\\NoHeart.png");
		#pragma endregion

		#pragma region KEY + BLANK_BULLET + MONEY (etc)
		Resources::Load<Texture>(L"Blank_bulletsSprite", L"enterthe\\UI\\blank_bullets\\blank_bullets.png");
		Resources::Load<Texture>(L"KeySprite", L"enterthe\\UI\\key\\key.png");
		Resources::Load<Texture>(L"MoneySprite", L"enterthe\\UI\\money\\money.png");
		#pragma endregion

		#pragma region ³²ÀºÃÑ¾Ë 
		Resources::Load<Texture>(L"bulletZeroSprite", L"enterthe\\UI\\bullet\\zero.png");
		Resources::Load<Texture>(L"bulletOneSprite", L"enterthe\\UI\\bullet\\one.png");
		Resources::Load<Texture>(L"bulletTwoSprite", L"enterthe\\UI\\bullet\\two.png");
		Resources::Load<Texture>(L"bulletThreeSprite", L"enterthe\\UI\\bullet\\three.png");
		Resources::Load<Texture>(L"bulletFourSprite", L"enterthe\\UI\\bullet\\four.png");
		Resources::Load<Texture>(L"bulletFiveSprite", L"enterthe\\UI\\bullet\\five.png");
		#pragma endregion

		#pragma region ¹Ì´Ï¸Ê °ü·Ã
		Resources::Load<Texture>(L"bulletZeroSprite", L"enterthe\\UI\\MiniMapBase\\MiniMap.png");

		#pragma endregion
#pragma endregion
		Resources::Load<Texture>(L"ReloadBarSprite", L"enterthe\\UI\\Reload\\ReloadBar.png");
		Resources::Load<Texture>(L"ReloadButtonSprite", L"enterthe\\UI\\Reload\\ReloadButton.png");

		//UITest
		Resources::Load<Texture>(L"CircleSprite", L"enterthe\\circle.png");
	}

	void LoadMaterial()
	{
		
		{//mainmenu
			{//background
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"mainBG");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"mainBgMaterial", material);

			}

			{//mainmenu 
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"mainMenu");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"mainMenuMaterial", material);
			}
		}
		

		{// player

			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"PlayerIdle");
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetRenderingMode(eRenderingMode::Opaque);
			material->SetShader(shader);
			material->SetTexture(eTextureSlot::T0, texture);
			Resources::Insert<Material>(L"pIdleMaterial", material);
			
		}

		{
			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"BulletKinIdle");
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetRenderingMode(eRenderingMode::Transparent);
			material->SetShader(shader);
			material->SetTexture(eTextureSlot::T0, texture);
			Resources::Insert<Material>(L"BulletKinMaterial", material);
		}

		{//playerHand

			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"PlayerHand");
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetRenderingMode(eRenderingMode::Transparent);
			material->SetShader(shader);
			material->SetTexture(eTextureSlot::T0, texture);
			Resources::Insert<Material>(L"pHandMaterial", material);

		}
		{ //¹«±â
			{
				{
					std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"W_pistol");
					std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
					std::shared_ptr<Material> material = std::make_shared<Material>();
					material->SetRenderingMode(eRenderingMode::Transparent);
					material->SetShader(shader);
					material->SetTexture(eTextureSlot::T0, texture);
					Resources::Insert<Material>(L"W_pistol_Material", material);
				}
				{
					std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"W_fightsabreSprite");
					std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
					std::shared_ptr<Material> material = std::make_shared<Material>();
					material->SetRenderingMode(eRenderingMode::Transparent);
					material->SetShader(shader);
					material->SetTexture(eTextureSlot::T0, texture);
					Resources::Insert<Material>(L"W_FightSabre_Material", material);
				}


			}


			{//ÃÑ¾Ë
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"W_Bullet");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"W_BulletMaterial", material);
			
			}

			{//ÃÑ¾Ë2
				std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"W_Bullet_02");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"W_BulletMaterial2", material);

			}
		}

		{//battleScenen
			std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"FloatSprite");
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetRenderingMode(eRenderingMode::Transparent);
			material->SetShader(shader);
			material->SetTexture(eTextureSlot::T0, texture);
			Resources::Insert<Material>(L"floatMaterial", material);
		}

		{//UI	
		#pragma region UI

		#pragma region ¹Ì´Ï¸Ê 
			{//¹Ì´Ï¸Ê
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"FullHeartSprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"FullHeartMaterial", uiMaterial);
			}
		#pragma endregion
			#pragma region UI_HEART
			{//FHeart
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"FullHeartSprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"FullHeartMaterial", uiMaterial);
			}

			{//HHeart
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"HalfHeartSprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"HalfHeartMaterial", uiMaterial);
			}

			{//NHeart
			std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"NoHeartSprite");
			std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
			uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
			uiMaterial->SetShader(uiShader);
			uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
			Resources::Insert<Material>(L"NoHeartMaterial", uiMaterial);
			}
#pragma endregion
			{//key
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"KeySprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"KeyMaterial", uiMaterial);
			}
			{//money
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"MoneySprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"MoneyMaterial", uiMaterial);
			}
			{//blankbullet (°øÆ÷Åº)
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"Blank_bulletsSprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"Blank_bulletsMaterial", uiMaterial);
			}
			{//ReloadBar
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"ReloadBarSprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"ReloadBarMaterial", uiMaterial);
			}

			{//ReloadButton
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"ReloadButtonSprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"ReloadButtonMaterial", uiMaterial);
			}
#pragma region remain Bullet
			{//left bullet  5
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"bulletFiveSprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"bulletFiveMaterial", uiMaterial);
			}
			{//left bullet  4
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"bulletFourSprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"bulletFourMaterial", uiMaterial);
			}
			{//left bullet  3
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"bulletThreeSprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"bulletThreeMaterial", uiMaterial);
			}
			{//left bullet  2
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"bulletTwoSprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"bulletTwoMaterial", uiMaterial);
			}
			{//left bullet  1
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"bulletOneSprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"bulletOneMaterial", uiMaterial);
			}
			{//left bullet  0
				std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"bulletZeroSprite");
				std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
				std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
				uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
				uiMaterial->SetShader(uiShader);
				uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
				Resources::Insert<Material>(L"bulletZeroMaterial", uiMaterial);
			}
#pragma endregion
#pragma endregion
		}
		{//¸Ê
		#pragma region ¸Ê
			
			{//map ¼¼·Î
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Map_vertical_Texture");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Mapvertical_Material", material);
			}
			{//map °¡·Î
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Map_horizontal_Texture");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Maphorizontal_Material", material);
			}
			{//map »ùÇÃ
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Map_sample_Texture");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"MapSample_Material", material);
			}
			{//map »ùÇÃ
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Map_sample_Texture2");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"MapSample_Material2", material);
			}

			{//°ËÁ¤ È­¸é
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Black_Texture");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Black_Material", material);
			}



#pragma endregion
		}
#pragma region ¿ÀºêÁ§Æ®
		{
			{
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Table_Default");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Opaque);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Table_Material", material);
			}
			{//Å×ÀÌºí ÇÁ·ÎÆ®01
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Table_Front_01");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Table_Front_01_Material", material);
			}
			{
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Table_Front_02");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Table_Front_02_Material", material);
			}
			{ // back
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Table_Back_01");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Table_Back_01_Material", material);
			}
			{
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Table_Back_02");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Table_Back_02_Material", material);
			}
			{//left
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Table_Left_01");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Table_Left_01_Material", material);
			}
			{
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Table_Left_02");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Table_Left_02_Material", material);
			}
			{ // right
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Table_Right_01");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Table_Right_01_Material", material);
			}
			{
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Table_Right_02");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Table_Right_02_Material", material);
			}
			{//Àû ÃÑ¾Ë
				std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"Enemy_Bullet");
				std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
				std::shared_ptr<Material> material = std::make_shared<Material>();
				material->SetRenderingMode(eRenderingMode::Transparent);
				material->SetShader(shader);
				material->SetTexture(eTextureSlot::T0, texture);
				Resources::Insert<Material>(L"Enemy_Bullet_material", material);
			}

		}
#pragma endregion
		// Default
		std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"PaintTexture");
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(eTextureSlot::T0, texture);
		Resources::Insert<Material>(L"RectMaterial", material);

		// Sprite
		std::shared_ptr <Texture> spriteTexture = Resources::Find<Texture>(L"DefaultSprite");
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
		spriteMaterial->SetShader(spriteShader);
		spriteMaterial->SetTexture(eTextureSlot::T0, spriteTexture);
		Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);

		// UI
		std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"HPBarTexture");
		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();

		uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		uiMaterial->SetShader(uiShader);
		uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
		Resources::Insert<Material>(L"UIMaterial", uiMaterial);

		{
			// UI
			std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"CircleSprite");
			std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
			uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
			uiMaterial->SetShader(uiShader);
			uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
			Resources::Insert<Material>(L"CircleMaterial", uiMaterial);
		}

		// Grid
		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
		gridMaterial->SetShader(gridShader);
		Resources::Insert<Material>(L"GridMaterial", gridMaterial);

		//// Fade ÀÌÆåÆ®
		//std::shared_ptr <Texture> fadeTexture = Resources::Find<Texture>(L"FadeEffectTexture");
		//std::shared_ptr<Shader> fadeShader = Resources::Find<Shader>(L"FadeEffectShader");
		//std::shared_ptr<Material> fadeMaterial = std::make_shared<Material>();
		//fadeMaterial->SetRenderingMode(eRenderingMode::Transparent);
		//fadeMaterial->SetShader(fadeShader);
		//fadeMaterial->SetTexture(fadeTexture);
		//Resources::Insert<Material>(L"FadeEffectMaterial", fadeMaterial);
		
		{//Åõ¸í
			std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"EmptyTexture");
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetRenderingMode(eRenderingMode::Transparent);
			material->SetShader(shader);
			material->SetTexture(eTextureSlot::T0, texture);
			Resources::Insert<Material>(L"EmptyMaterial", material);
		}
		// Debug
		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
		debugMaterial->SetRenderingMode(eRenderingMode::Transparent);
		debugMaterial->SetShader(debugShader);
		Resources::Insert<Material>(L"DebugMaterial", debugMaterial);

		// Debug
		std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
		std::shared_ptr<Material> particleMaterial = std::make_shared<Material>();
		particleMaterial->SetRenderingMode(eRenderingMode::Transparent);
		particleMaterial->SetShader(particleShader);
		Resources::Insert<Material>(L"ParticleMaterial", particleMaterial);
#pragma region POSTPROCESS
		std::shared_ptr<Shader> postProcessShader = Resources::Find<Shader>(L"PostProcessShader");
		std::shared_ptr<Material> postProcessMaterial = std::make_shared<Material>();
		postProcessMaterial->SetRenderingMode(eRenderingMode::PostProcess);
		postProcessMaterial->SetShader(postProcessShader);
		Resources::Insert<Material>(L"PostProcessMaterial", postProcessMaterial);
#pragma endregion
	}

	void Initialize()
	{
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
	}

	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}

	

	void Render()
	{
		BindNoiseTexture();
		BindLights();

		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras[(UINT)type].clear();
		renderer::lights.clear();
	}

	void PushLightAttribute(LightAttribute lightAttribute)
	{
		lights.push_back(lightAttribute);
	}

	void BindLights()
	{
		lightsBuffer->SetData(lights.data(), lights.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);

		renderer::LightCB trCb = {};
		trCb.numberOfLight = lights.size();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Light];
		cb->SetData(&trCb);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
	float noiseTime = 10.0f;
	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> noise = Resources::Find<Texture>(L"noise_01");
		noise->BindShaderResource(eShaderStage::VS, 16);
		noise->BindShaderResource(eShaderStage::HS, 16);
		noise->BindShaderResource(eShaderStage::DS, 16);
		noise->BindShaderResource(eShaderStage::GS, 16);
		noise->BindShaderResource(eShaderStage::PS, 16);
		noise->BindShaderResource(eShaderStage::CS, 16);

		NoiseCB info = {};
		info.noiseSize.x = noise->GetWidth();
		info.noiseSize.y = noise->GetHeight();
		noiseTime -= Time::DeltaTime();
		info.noiseTime = noiseTime;

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Noise];
		cb->SetData(&info);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}

	void CopyRenderTarget()
	{
		std::shared_ptr<Texture> renderTarget = Resources::Find<Texture>(L"RenderTargetTexture");

		ID3D11ShaderResourceView* srv = nullptr;
		GetDevice()->BindShaderResource(eShaderStage::PS, 60, &srv);

		ID3D11Texture2D* dest = postProcessTexture->GetTexture().Get();
		ID3D11Texture2D* source = renderTarget->GetTexture().Get();

		GetDevice()->CopyResource(dest, source);

		postProcessTexture->BindShaderResource(eShaderStage::PS, 60);
	}
}
