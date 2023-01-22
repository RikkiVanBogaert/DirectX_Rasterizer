#pragma once

#include <SDL_surface.h>
#include "ColorRGB.h"

using namespace dae;

class Vector2;

class Texture final
{
public:
	Texture(ID3D11Device* pDevice, const std::string& path);
	~Texture();

	//DirectX
	ID3D11ShaderResourceView* GetSRV() const;

	//Rasterizer
	Texture(SDL_Surface* pSurface);
	ColorRGB Sample(const dae::Vector2& uv) const;
	static Texture* LoadFromFile(const std::string& path);

private:
	ID3D11Texture2D* m_pResource{};
	ID3D11ShaderResourceView* m_pSRV{};

	SDL_Surface* m_pSurface{ nullptr };
	uint32_t* m_pSurfacePixels{ nullptr };
};

