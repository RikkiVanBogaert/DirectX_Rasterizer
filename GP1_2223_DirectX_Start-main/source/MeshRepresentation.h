#pragma once
#include "DataTypes.h"
#include "Effect.h"

class MeshRepresentation final
{
public:
	MeshRepresentation(ID3D11Device* pDevice, const std::string& objFilePath, Effect* pEffect);
	~MeshRepresentation();

	void Render(ID3D11DeviceContext* pDeviceContext);
	void Update(const dae::Matrix& viewProjMatrix, const dae::Matrix& viewInvertMatrix);
	void ToggleTechniques();

private:
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11InputLayout* m_pInputLayout;
	Effect* m_pEffect;
	uint32_t m_NumIndices;

	Matrix m_TranslationMatrix{ Vector3::UnitX, Vector3::UnitY, Vector3::UnitZ, Vector3::Zero };
	Matrix m_RotationMatrix{ Vector3::UnitX, Vector3::UnitY, Vector3::UnitZ, Vector3::Zero };
	Matrix m_ScaleMatrix{ Vector3::UnitX, Vector3::UnitY, Vector3::UnitZ, Vector3::Zero };
};

