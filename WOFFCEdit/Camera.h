#pragma once
#include "DeviceResources.h"

#include "pch.h"
//#include "DisplayObject.h"
#include <vector>

class Camera: public DX::IDeviceNotify
{
public:
	void Initialise();
	void GetView();
	void GetWorld();
	void GetProjection();

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

	
	
};

