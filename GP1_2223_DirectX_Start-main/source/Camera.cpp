#include "pch.h"
#include "Camera.h"
#include "Timer.h"

using namespace dae;

Camera::Camera(Vector3 _origin, float _fovAngle):
	origin{_origin},
	fovAngle{_fovAngle}
{}

void Camera::Initialize(float _fovAngle , Vector3 _origin , float ratio )
{
	fovAngle = _fovAngle;
	fov = tanf((fovAngle * TO_RADIANS) / 2.f);
	aspectRatio = ratio;

	origin = _origin;

	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

void Camera::Update(const Timer* pTimer)
{
	const float deltaTime = pTimer->GetElapsed();

	//Camera Update Logic
	const float movementSpeed{ 10 * deltaTime };
	//Keyboard Input
	//const uint8_t* pKeyboardState = SDL_GetKeyboardState(nullptr);
	const Uint8* pStates{ SDL_GetKeyboardState(nullptr) };
	if (pStates[SDL_SCANCODE_W] || pStates[SDL_SCANCODE_UP])
	{
		origin.z += movementSpeed;
	}
	else if (pStates[SDL_SCANCODE_S] || pStates[SDL_SCANCODE_DOWN])
	{
		origin.z -= movementSpeed;
	}
	else if (pStates[SDL_SCANCODE_D] || pStates[SDL_SCANCODE_RIGHT])
	{
		origin.x += movementSpeed;
	}
	else if (pStates[SDL_SCANCODE_A] || pStates[SDL_SCANCODE_LEFT])
	{
		origin.x -= movementSpeed;
	}

	//Mouse Input
	int mouseX{}, mouseY{};
	const uint32_t mouseState = SDL_GetRelativeMouseState(&mouseX, &mouseY);

	const float rotationSpeed{ 0.1f * deltaTime };

	if ((mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)))
	{
		origin.y += -mouseY * movementSpeed;
	}
	else if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		totalPitch += -mouseY * rotationSpeed;
		totalYaw += mouseX * rotationSpeed;
	}
	else if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		totalYaw += mouseX * rotationSpeed;

		origin.z += -mouseY * movementSpeed;
	}

	const Matrix finalRotation{ Matrix::CreateRotationX(totalPitch) * Matrix::CreateRotationY(totalYaw) };
	forward = finalRotation.TransformVector(Vector3::UnitZ);
	forward.Normalize();

	//Update Matrices
	CalculateViewMatrix();
	CalculateProjectionMatrix(); //Try to optimize this - should only be called once or when fov/aspectRatio changes
}

void Camera::CalculateViewMatrix()
{
	viewMatrix = Matrix::CreateLookAtLH(origin, forward, up);
	invViewMatrix = Matrix::Inverse(viewMatrix);
	//DirectX Implementation => https://learn.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixlookatlh
}

void Camera::CalculateProjectionMatrix()
{
	projectionMatrix = Matrix::CreatePerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane);
	//DirectX Implementation => https://learn.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectivefovlh
}

const Matrix& Camera::GetViewMatrix() const
{
	return viewMatrix;
}

const Matrix& Camera::GetViewInvertMatrix() const
{
	return invViewMatrix;
}

const Matrix& Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}

const Matrix& Camera::GetViewProjectionMatrix() const
{
	Matrix result{ viewMatrix * projectionMatrix };
	return result;
}