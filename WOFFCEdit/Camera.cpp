#include "Camera.h"

void Camera::Initialise()
{
	m_camRotRate = 3.0;

	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;
}
