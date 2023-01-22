#include "pch.h"
#include "Texture.h"
#include "Vector2.h"
#include <assert.h>


using namespace dae;


Texture::Texture(ID3D11Device* pDevice, const std::string& path)
{
	m_pSurface = IMG_Load(path.c_str());

	const DXGI_FORMAT format{ DXGI_FORMAT_R8G8B8A8_UNORM };
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = m_pSurface->w;
	desc.Height = m_pSurface->h;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = m_pSurface->pixels;
	initData.SysMemPitch = static_cast<UINT>(m_pSurface->pitch);
	initData.SysMemSlicePitch = static_cast<UINT>(m_pSurface->h * m_pSurface->pitch);

	HRESULT hr = pDevice->CreateTexture2D(&desc, &initData, &m_pResource);


	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc{};
	SRVDesc.Format = format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	hr = pDevice->CreateShaderResourceView(m_pResource, &SRVDesc, &m_pSRV);


	m_pSurfacePixels = (uint32_t*)m_pSurface->pixels;

}
Texture::~Texture()
{
	if(m_pResource)
	{
		m_pResource->Release();
		m_pResource = nullptr;
	}
	if(m_pSRV)
	{
		m_pSRV->Release();
		m_pSRV = nullptr;
	}
	if(m_pSurface)
	{
		SDL_FreeSurface(m_pSurface);
		m_pSurface = nullptr;
	}
}

ID3D11ShaderResourceView* Texture::GetSRV() const
{
	return m_pSRV;
}


//RASTERIZER
Texture::Texture(SDL_Surface* pSurface) :
	m_pSurface{ pSurface },
	m_pSurfacePixels{ (uint32_t*)pSurface->pixels }
{
}

Texture* Texture::LoadFromFile(const std::string& path)
{
	//TODO
	//Load SDL_Surface using IMG_LOAD
	//Create & Return a new Texture Object (using SDL_Surface)

	const auto loadedImage{ IMG_Load(path.c_str()) };
	assert(loadedImage != nullptr && "There was no file found");

	Texture* imageTexture = new Texture{ loadedImage };
	return imageTexture;
}


ColorRGB Texture::Sample(const dae::Vector2& uv) const
{
	Uint8 r, g, b;

	const size_t x{ static_cast<size_t>(uv.x * m_pSurface->w) };
	const size_t y{ static_cast<size_t>(uv.y * m_pSurface->h) };

	const Uint32 pixel{ m_pSurfacePixels[x + y * m_pSurface->w] };

	SDL_GetRGB(pixel, m_pSurface->format, &r, &g, &b);

	return { r / 255.f, g / 255.f, b / 255.f };
}
