#pragma once
#include "chComponent.h"

namespace ch
{
	using namespace math;
	class Camera : public Component
	{
	public:
		enum eProjectionType
		{
			Perspective,//원근
			Orthographic,//직교 투영
		};

		__forceinline static Matrix& GetGpuViewMatrix() { return View; }
		__forceinline static Matrix& GetGpuProjectionMatrix() { return Projection; }
		__forceinline static void SetGpuViewMatrix(Matrix view) { View = view; }
		__forceinline static void SetGpuProjectionMatrix(Matrix projection) { Projection = projection; }

		Camera();
		virtual ~Camera();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void CreateViewMatrix();
		void CreateProjectionMatrix();
		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType layer, bool enable = true);
		void EnableLayerMasks() { mLayerMasks.set(); }
		void DisableLayerMasks() { mLayerMasks.reset(); }

		void SetProjectionType(eProjectionType type) { mType = type; }
		float GetScale() { return mScale; }
		Matrix& GetViewMatrix() { return mView; }
		Matrix& GetProjectionMatrix() { return mProjection; }

		void SetTarget(GameObject* _Target) { mTargetOJ = _Target; }
		GameObject* GetTarget() const { return mTargetOJ; }

	

	private:
		void sortGameObjects();
		void renderOpaque();
		void renderCutout();
		void renderTransparent();
		void renderPostProcess();
		void pushGameObjectToRenderingModes(GameObject* gameObj);

	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;

		float mNear;
		float mFar;
		float mScale;

		std::bitset<(UINT)eLayerType::End> mLayerMasks;
		std::vector<GameObject*> mOpaqueGameObjects; //불투명
		std::vector<GameObject*> mCutoutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;
		std::vector<GameObject*> mPostProcessGameObjects;
		
	public:
		GameObject* mTargetOJ;//
		Vector3		mCamDir;

		float		mFarDist;

		float		mCamSpeed;
		float		mTime;

		bool		mSmooth;

		
	};
}
