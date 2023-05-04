#pragma once
//#include "DeviceResources.h"
#include "pch.h"
#include "InputCommands.h"


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

	void ArcballCamera();
	//void PosCamera();
	//void MoveCamera();
	void Update(InputCommands* input);
	


private:
	DirectX::SimpleMath::Vector3 m_camPosition;
	DirectX::SimpleMath::Vector3 m_camOrientation;
	DirectX::SimpleMath::Vector3 m_camLookAt;
	DirectX::SimpleMath::Vector3 m_camLookDirection;
	DirectX::SimpleMath::Vector3 m_camRight;
	
	float m_camRotRate;
	DirectX::SimpleMath::Matrix                                             m_world;
	DirectX::SimpleMath::Matrix                                             m_view;
	DirectX::SimpleMath::Matrix                                             m_projection;

	//width and height on screen 
	float m_width;
	float m_height;
	
	
};

