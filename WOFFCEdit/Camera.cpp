#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
Camera::Camera()
{
}
Camera::~Camera()
{
}
void Camera::Initialise(float width, float Height)
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
	m_width = width;
	m_height = Height;
}

void Camera::ArcballCamera()
{
}

void Camera::Update(InputCommands* m_InputCommands)
{

	if (m_InputCommands->rotRight)
	{
		m_camOrientation.x -= m_camRotRate;
	}
	if (m_InputCommands->rotLeft)
	{
		m_camOrientation.x += m_camRotRate;
	}

	float test = m_InputCommands->mouse_x - m_InputCommands->mouse_old_x;
	float tper = test * ((2 * 3.1415) / m_width);//position in width of screen space
	float testy = m_InputCommands->mouse_y - m_InputCommands->mouse_old_y;
	float tpery = testy * (3.1415 / m_height);
	if (m_InputCommands->mouse_lb_down && m_InputCommands->testcamera)
	{

		if (test > 1)
		{
			m_camOrientation.y += m_camRotRate * tper * 25.0f;
		}
		else if (test < -1)
		{
			m_camOrientation.y += m_camRotRate * tper * 25.0f;
		}
		if (testy > 1)
		{

			m_camOrientation.x -= m_camRotRate * tpery * 25.0f;
		}
		else if (testy < -1)
		{

			m_camOrientation.x -= m_camRotRate * tpery * 25.0f;
		}
		m_InputCommands->testcamera = false;
	}
	if (m_camOrientation.x >= 90)
	{
		m_camOrientation.x = 89;
	}
	else if (m_camOrientation.x <= -90)
	{
		m_camOrientation.x = -89;

	}

	//create look direction from Euler angles in m_camOrientation
	m_camLookDirection.x = cos((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);
	//m_camLookDirection.x = sin((m_camOrientation.y)*3.1415 / 180); 
	m_camLookDirection.y = sin((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.z = sin((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);
	//m_camLookDirection.z = cos((m_camOrientation.y) * 3.1415 / 180);
	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);

	//arcBall
	//m_camPosition = m_camLookDirection * m_movespeed + m_camLookAt; //rotation * speed + distance + m_camlookat
	//None ArcBall
	m_camLookAt = m_camPosition + m_camLookDirection;

	m_view = Matrix::CreateLookAt(m_camPosition, m_camLookAt, Vector3::UnitY);
}
