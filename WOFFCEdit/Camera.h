#pragma once
//#include "DeviceResources.h"
#include "pch.h"
#include "InputCommands.h"
#include "StepTimer.h"

#include <SimpleMath.h>
//#include "DisplayObject.h"
#include <vector>

class Camera
{
public:
	Camera();
	~Camera();
	void Initialise(float width, float hieght);

	DirectX::SimpleMath::Matrix  GetView()
	{
		return m_view;
	}
	DirectX::SimpleMath::Matrix  GetWorld()
	{
		return m_world;
	}
	DirectX::SimpleMath::Matrix  GetProjection()
	{
		return m_projection;
	}
	void SetDistance(DirectX::SimpleMath::Vector3 position);
	void ArcballCamera();
	//void PosCamera();
	void MoveCamera(InputCommands* input);
	void CameraRotation(InputCommands* m_InputCommands);
	void PlayerMovement(InputCommands* m_InputCommands);
	void update(InputCommands* input, DX::StepTimer const& timer);
	void CreateDistance(DirectX::SimpleMath::Vector3 position,float f, float t);
	void Lerp(DX::StepTimer const& t);
	DirectX::SimpleMath::Vector3 m_camLookAt;
	DirectX::SimpleMath::Vector3 m_distance;
	DirectX::SimpleMath::Vector3 m_camLookDirection;
	DirectX::SimpleMath::Vector3 m_camPosition;

private:
	//DirectX::SimpleMath::Vector3 m_camPosition;
	DirectX::SimpleMath::Vector3 m_camOrientation;
	//DirectX::SimpleMath::Vector3 m_camLookAt;
	//DirectX::SimpleMath::Vector3 m_camLookDirection;
	DirectX::SimpleMath::Vector3 m_camRight;
	
	
	float m_camRotRate;
	DirectX::SimpleMath::Matrix                                             m_world;
	DirectX::SimpleMath::Matrix                                             m_view;
	DirectX::SimpleMath::Matrix                                             m_projection;

	//width and height on screen 
	float m_width;
	float m_height;
	DirectX::SimpleMath::Vector3   m_from;
	DirectX::SimpleMath::Vector3   m_towards;

	float lerp;
	float LerpRemaining;
	float m_movespeed;
	bool  rot_towards;
	bool distset;
};


