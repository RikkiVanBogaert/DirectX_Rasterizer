#pragma once

using namespace dae;

class Camera final
{
public:
	Camera() = default;
	Camera(Vector3 _origin, float _fovAngle);

	void Initialize(float _fovAngle = 90.f, Vector3 _origin = { 0.f,0.f,0.f }, float ratio = 1);
	void Update(const Timer* pTimer);
	const Matrix& GetViewMatrix() const;
	const Matrix& GetViewInvertMatrix() const;
	const Matrix& GetProjectionMatrix() const;
	const Matrix& GetViewProjectionMatrix() const;
	void CalculateViewMatrix();
	void CalculateProjectionMatrix();

	Vector3 origin{};
	float fovAngle{ 90.f };
	float fov{ tanf((fovAngle * TO_RADIANS) / 2.f) };
	float aspectRatio{ 1.f };

	Vector3 forward{ Vector3::UnitZ };
	Vector3 up{ Vector3::UnitY };
	Vector3 right{ Vector3::UnitX };

	float totalPitch{};
	float totalYaw{};

	Matrix invViewMatrix{};
	Matrix viewMatrix{};
	Matrix projectionMatrix{};

	const float nearPlane{ 0.1f };
	const float farPlane{ 100.f };
};

