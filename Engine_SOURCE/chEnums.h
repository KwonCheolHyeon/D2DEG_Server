#pragma once

namespace ch::enums
{
	enum class eSceneType
	{
		Tilte,
		Main,
		Play,
		Test,
		Server,
		End,
	};

	enum class eLayerType //더이상 못늘림
	{
		None = 0,
		Camera,
		Grid,
		BackGround,
		Object,
		Hand,
		Weapone,
		Monster,
		MonsterBullet,
		Player,
		Dummy,
		Particle,
		PostProcess,
		UI,
		Wall,
		MonsterCollider,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // 위치 데이터 수정하는 컴포넌트
		Camera,
		Mesh,
		Collider,
		Rigidbody,
		//Collider2,
		MeshRenerer,
		SpriteRenderer,
		Animator,
		ParticleSystem,
		AudioListener,
		AudioSource,
		Light,
		UI,
		//FadeOut,FadeIn
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		/*Font,*/
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		AudioClip,
		Script,
		End,
	};

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};

	//struct Ray
	//{
	//	Vector3 origin;
	//	Vector3 dest;
	//};

}