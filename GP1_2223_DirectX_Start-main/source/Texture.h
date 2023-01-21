#pragma once
#include <SDL_surface.h>

class Texture final
{
public:
	Texture(ID3D11Device* pDevice, const std::string& path);
	~Texture();

	ID3D11ShaderResourceView* GetSRV() const;

private:
	ID3D11Texture2D* m_pResource{};
	ID3D11ShaderResourceView* m_pShaderResourceView{};
};

