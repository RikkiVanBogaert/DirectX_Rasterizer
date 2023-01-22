#pragma once
#include "DataTypes.h"
#include "Effect.h"

struct MeshRast final
{
	std::vector<Vertex> vertices{};
	std::vector<uint32_t> indices{};
	PrimitiveTopology primitiveTopology{ PrimitiveTopology::TriangleStrip };

	std::vector<Vertex_Out> vertices_out{};
	Matrix worldMatrix{};
};


class MeshRepresentation final
{
public:
	MeshRepresentation(ID3D11Device* pDevice, const std::string& objFilePath, Effect* pEffect);
	~MeshRepresentation();

	void Render(ID3D11DeviceContext* pDeviceContext);
	void Update(const dae::Matrix& viewProjMatrix, const dae::Matrix& viewInvertMatrix, float angle, Vector3 translation);
	void ToggleTechniques() const;

	int GetSampleState() const;

private:
	ID3D11Buffer* m_pVertexBuffer{nullptr};
	ID3D11Buffer* m_pIndexBuffer{ nullptr };
	ID3D11InputLayout* m_pInputLayout{ nullptr };
	Effect* m_pEffect{ nullptr };
	uint32_t m_NumIndices{};

	Matrix m_TranslationMatrix{ Vector3::UnitX, Vector3::UnitY, Vector3::UnitZ, Vector3::Zero };
	Matrix m_RotationMatrix{ Vector3::UnitX, Vector3::UnitY, Vector3::UnitZ, Vector3::Zero };
	Matrix m_ScaleMatrix{ Vector3::UnitX, Vector3::UnitY, Vector3::UnitZ, Vector3::Zero };

};

