#pragma once
#include "Math.h"

using namespace dae;

struct Vertex
{
	Vector3 position;
	dae::Vector2 uv;
	Vector3 normal;
	Vector3 tangent;
};

struct Vertex_Out
{
	Vector4 position{};
	ColorRGB color{};
	dae::Vector2 uv{};
	Vector3 normal{};
	Vector3 tangent{};
	Vector3 viewDirection{};
};

enum class PrimitiveTopology
{
	TriangleList,
	TriangleStrip
};

struct Mesh
{
	std::vector<Vertex> vertices{};
	std::vector<uint32_t> indices{};
	PrimitiveTopology primitiveTopology{ PrimitiveTopology::TriangleStrip };

	std::vector<Vertex_Out> vertices_out{};
	Matrix worldMatrix{};
};