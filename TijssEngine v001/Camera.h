#pragma once
#include "_DllExport.h"
#include "TypeDefines.h"
#include <d3d11.h>
#include <xnamath.h>

namespace Tijss
{
	class TIJSSEN_DECLSPEC cCamera
	{
	public:
		cCamera();

		void SetOrthoProjection(float32 X1, float32 X2, float32 Y1, float32 Y2, float32 ZNear, float32 ZFar);
		void SetPerspectiveProjection(float32 FovDEG, float32 pAspectRatio, float32 ZNear, float32 ZFar);

		void Turn(float32 pRoll, float32 pPitch, float32 pYaw);
		void Move(float32 pX, float32 pY, float32 pZ);

		void SetPosition(float32 pX, float32 pY, float32 pZ);
		void SetRotation(float32 pRoll, float32 pPitch, float32 pYaw);

		void UpdateViewMatrix();
		void Update();

		float32 GetRoll();
		float32 GetPitch();
		float32 GetYaw();

		XMFLOAT3 GetPosition();
		XMFLOAT3 GetRotation();

		XMMATRIX GetFinalMatrix();
		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjectionMatrix();
	private:
		float32 m_MoveLR, m_MoveBF, m_MoveTD;
		float32 m_Roll, m_Pitch, m_Yaw;

		XMMATRIX m_ViewMatrix;
		XMMATRIX m_ProjMatrix;
		XMMATRIX m_RotMatrix;

		XMVECTOR m_Position;
		XMVECTOR m_Target;
		XMVECTOR m_Up;
		XMVECTOR m_Right;
		XMVECTOR m_Forward;

		XMVECTOR m_DefaultUp;
		XMVECTOR m_DefaultRight;
		XMVECTOR m_DefaultForward;

	};
}


//class Camera
//{
//public:
//	Camera(int width, int height, Vector3 scaleFactors);
//	~Camera();
//
//	// functions
//	void Update();
//	void Follow(SpriteSheet* following);
//	void Unfollow();
//	bool IsFollowing() const;
//	void SetTransform(Graphics* gfx) const;
//
//private:
//	Vector3 scaleFactors;
//	D2D1_MATRIX_3X2_F orthographicMatrix;
//	D2D1_MATRIX_3X2_F identityMatrix;
//	D2D1_MATRIX_3X2_F viewMatrix;
//
//	SpriteSheet* following;
//
//	int width;
//	int height;
//};