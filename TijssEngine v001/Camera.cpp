#include "Camera.h"

namespace Tijss
{
	cCamera::cCamera()
	{
		m_Right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		m_Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		m_Forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		m_Position = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		m_Target = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

		m_MoveLR = 0.0f;
		m_MoveBF = 0.0f;
		m_MoveTD = 0.0f;
		
		m_Roll = 0.0f;
		m_Pitch = 0.0f;
		m_Yaw = 0.0f;

		m_DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		m_DefaultUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		m_DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

		UpdateViewMatrix();
	}


	float cCamera::GetRoll()
	{
		return m_Roll;
	}

	float cCamera::GetPitch()
	{
		return m_Pitch;
	}

	float cCamera::GetYaw()
	{
		return m_Yaw;
	}

	XMFLOAT3 cCamera::GetPosition()
	{
		XMFLOAT3 result;
		XMStoreFloat3(&result, m_Position);
		return result;
	}

	XMFLOAT3 cCamera::GetRotation()
	{
		return XMFLOAT3(m_Roll, m_Pitch, m_Yaw);
	}


	void cCamera::SetPosition(float pX, float pY, float pZ)
	{
		m_Position = XMVectorSet(pX, pY, pZ, 0.0f);
	}

	void cCamera::SetRotation(float pRoll, float pPitch, float pYaw)
	{
		m_Roll += pRoll;
		m_Pitch += pPitch;
		m_Yaw += pYaw;
	}

	void cCamera::SetOrthoProjection(float X1, float X2, float Y1, float Y2, float ZNear, float ZFar)
	{
		if (X2>X1 && Y2>Y1 && ZFar>ZNear)
			m_ProjMatrix = XMMatrixOrthographicOffCenterLH(X1, X2, Y2, Y1, ZNear, ZFar);
		//else
			//Log::Error("Camera::SetOrthoProjection: check parametr's");
	}

	void cCamera::SetPerspectiveProjection(float FovDEG, float pAspertRatio, float ZNear, float ZFar)
	{
		if (ZNear == 0.00f)
		{
			ZNear += 0.01f;
			//Log::Warning("Camera::SetPerspectiveProjection: ZNear=0 is bad idea");
		}

		if (FovDEG<1.0f)
			FovDEG = 1.0f;

		if (FovDEG>179.0f)
			FovDEG = 179.0f;

		m_ProjMatrix = XMMatrixPerspectiveFovLH(FovDEG*DEGREETORADIAN, pAspertRatio, ZNear, ZFar);
	}

	void cCamera::UpdateViewMatrix()
	{
		m_ViewMatrix = XMMatrixLookAtLH(m_Position, m_Target, m_Up);
	}

	XMMATRIX cCamera::GetFinalMatrix()
	{
		return m_ViewMatrix * m_ProjMatrix;
	}

	XMMATRIX cCamera::GetProjectionMatrix()
	{
		return m_ProjMatrix;
	}

	XMMATRIX cCamera::GetViewMatrix()
	{
		return m_ViewMatrix;
	}


	void cCamera::Move(float pX, float pY, float pZ)
	{
		m_MoveLR += pX;
		m_MoveTD += pY;
		m_MoveBF += pZ;
	}

	void cCamera::Turn(float pRoll, float pPitch, float pYaw)
	{
		m_Roll += pRoll;
		m_Pitch += pPitch;
		m_Yaw += pYaw;

		m_Roll = fmod(m_Roll, XM_2PI);

		if (m_Roll>XM_PI / 2.0f)
		{
			m_Roll = XM_PI / 2.0f;
		}

		if (m_Roll<-XM_PI / 2.0f)
		{
			m_Roll = -XM_PI / 2.0f;
		}
	}

	void cCamera::Update()
	{
		m_RotMatrix = XMMatrixRotationRollPitchYaw(m_Roll, m_Pitch, m_Yaw);
		m_Target = XMVector3TransformCoord(m_DefaultForward, m_RotMatrix);
		m_Target = XMVector3Normalize(m_Target);

		XMMATRIX RotateYTempMatrix;
		RotateYTempMatrix = XMMatrixRotationRollPitchYaw(m_Roll, m_Pitch, m_Yaw);

		m_Right = XMVector3TransformCoord(m_DefaultRight, RotateYTempMatrix);
		m_Up = XMVector3TransformCoord(m_DefaultUp, RotateYTempMatrix);
		m_Forward = XMVector3TransformCoord(m_DefaultForward, RotateYTempMatrix);

		m_Position += m_MoveLR * m_Right;
		m_Position += m_MoveTD * m_Up;
		m_Position += m_MoveBF * m_Forward;

		m_MoveLR = 0.0f;
		m_MoveTD = 0.0f;
		m_MoveBF = 0.0f;

		m_Target = m_Position + m_Target;

		UpdateViewMatrix();
	}
}