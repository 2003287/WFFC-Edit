#include "Camera.h"
#include <cmath>
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
	m_camRotRate = 3.0f;
	m_movespeed = 0.3f;
	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_distance.x = 0;
	m_distance.y = 0;
	m_distance.z = 5;

	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;
	distset = false;
	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;
	m_width = width;
	m_height = Height;
	rot_towards = false;

	lerp = 0;
	LerpRemaining = 0;
	m_from = Vector3();
	m_towards = Vector3();
}

void Camera::SetDistance(Vector3 position)
{
	//check you are not too close to the object
	float dist = Vector3::Distance(m_camPosition, position);
	if(dist<5)
	{
		return;
	}

	//get out the rotation angle
	Vector3 junk;
	Quaternion Rot;
	m_view.Decompose(junk, Rot, junk);
	Rot.Normalize();
	Vector3 eul = Rot.ToEuler();

	m_view = Matrix::CreateLookAt(m_camPosition,position,Vector3::UnitY);

	m_view.Decompose(junk, Rot, junk);
	Rot.Normalize();
	Vector3 eul2 = Rot.ToEuler();

	eul *= (180/3.1415);
	eul2 *= (180/3.1415);

	Vector3 Delta = eul2 - eul;
	Delta.x = 0;

	m_camOrientation.x -= Delta.z;
	m_camOrientation.y += Delta.y;

	if (m_camOrientation.x > 89.0f) {
		m_camOrientation.x = 89.0f;
	}
	if (m_camOrientation.x < -89.0f) {
		m_camOrientation.x = -89.0f;
	}

	if (m_camOrientation.y < 0.0f) {
		m_camOrientation.y += 360.0f;
	}
	if (m_camOrientation.y > 360.0f) {
		m_camOrientation.y -= 360.0f;
	}
}

void Camera::ArcballCamera()
{
	//m_camPosition = m_camLookDirection * m_movespeed + m_camLookAt; //rotation * speed + distance + m_camlookat

}

void Camera::MoveCamera(InputCommands* m_InputCommands)
{
	float x_direction = m_InputCommands->mouse_x - m_InputCommands->mouse_old_x;
	float x_screenpos = x_direction * ((2 * 3.1415) / m_width);//position in width of screen space
	float y_direction = m_InputCommands->mouse_y - m_InputCommands->mouse_old_y;
	float y_screenpos = y_direction * (3.1415 / m_height);
	if (m_InputCommands->mouse_lb_down && m_InputCommands->mouse_moving)
	{

		if (x_direction > 1)
		{
			m_camOrientation.y += m_camRotRate * x_screenpos * 25.0f;
		}
		else if (x_direction < -1)
		{
			m_camOrientation.y += m_camRotRate * x_screenpos * 25.0f;
		}
		if (y_direction > 1)
		{

			m_camOrientation.x -= m_camRotRate * y_screenpos * 25.0f;
		}
		else if (y_direction < -1)
		{

			m_camOrientation.x -= m_camRotRate * y_screenpos * 25.0f;
		}		
	}
	if (m_camOrientation.x >= 90)
	{
		m_camOrientation.x = 89;
	}
	else if (m_camOrientation.x <= -90)
	{
		m_camOrientation.x = -89;
	}
	if (m_camOrientation.y < 0.0f) {
		m_camOrientation.y += 360.0f;
	}
	else if (m_camOrientation.y > 360.0f) {
		m_camOrientation.y -= 360.0f;
	}

}

void Camera::CameraRotation(InputCommands* m_InputCommands)
{
	if(m_InputCommands->mouse_lb_down)
	{
		MoveCamera(m_InputCommands);
	}
	//create look direction if()from Euler angles in m_camOrientation
	m_camLookDirection.x = cos((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);
	//m_camLookDirection.x = sin((m_camOrientation.y)*3.1415 / 180); 
	m_camLookDirection.y = sin((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.z = sin((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);
	//m_camLookDirection.z = cos((m_camOrientation.y) * 3.1415 / 180);
	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);
}

void Camera::PlayerMovement(InputCommands* m_InputCommands)
{
	
	if (m_InputCommands->rotRight)
	{
		m_camOrientation.x -= m_camRotRate;
	}
	if (m_InputCommands->rotLeft)
	{
		m_camOrientation.x += m_camRotRate;
	}

	//if (m_InputCommands->game_mode != 2)
	{
		
			CameraRotation(m_InputCommands);
		
		
	}
	
	if (m_InputCommands->forward)
	{
		m_camPosition += m_camLookDirection * m_movespeed;
	}
	if (m_InputCommands->back)
	{
		m_camPosition -= m_camLookDirection * m_movespeed;
	}
	if (m_InputCommands->right)
	{
		m_camPosition += m_camRight * m_movespeed;
	}
	if (m_InputCommands->left)
	{
		m_camPosition -= m_camRight * m_movespeed;
	}
}

void Camera::update(InputCommands* m_InputCommands, DX::StepTimer const& timer)
{
	if(distset)
	{
		distset = false;
		return;
	}
	PlayerMovement(m_InputCommands);
	if(LerpRemaining >0.0f)
	{
		Lerp(timer);
	}
	
	if(m_InputCommands->cameraMode == 2)
	{
		Vector3 ts = m_camLookAt + m_distance;
		m_camPosition = (m_camLookDirection + m_camLookAt);
	}
	else if(m_InputCommands->cameraMode == 1)
	{
	
			m_camLookAt = m_camPosition + m_camLookDirection;
		
		//
	}
	

	m_view = Matrix::CreateLookAt(m_camPosition, m_camLookAt, Vector3::UnitY);
}


void Camera::CreateDistance(Vector3 position, float f, float t)
{
	distset = true;
	float dist = Vector3::Distance(m_camPosition, position);
	if (dist > f)
		dist -= f;
	else
	{
		lerp = 0;
		LerpRemaining = 0;
		m_from = Vector3();
		m_towards = Vector3();
		return;
	}

	lerp = t;
	LerpRemaining = t;
	m_from = m_camPosition;
	Vector3 ts = position - m_camPosition;	
	ts.Normalize();
	ts = m_camPosition + (dist*ts);
	m_towards = ts;
	m_distance = ts *dist;
	//m_towards 


}

void Camera::Lerp(DX::StepTimer const& t)
{
	LerpRemaining -= t.GetElapsedSeconds();
	float lerpFac = (lerp -LerpRemaining)/lerp;
	m_camPosition = Vector3::Lerp(m_from,m_towards,lerpFac);
}
