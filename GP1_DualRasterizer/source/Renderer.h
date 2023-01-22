#pragma once
#include "Camera.h"

struct SDL_Window;
struct SDL_Surface;
class MeshRepresentation;
class Texture;
struct Vertex_Out;
struct MeshRast;

using namespace dae;

	class Renderer final
	{
	public:
		Renderer(SDL_Window* pWindow);
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void Update(const Timer* pTimer);
		void Render();

		//Switch States
		void SwitchState();
		void SwitchRotating();
		void SwitchUsingFire();
		void SwitchTechniques() const;
		void SwitchShadingMode();
		void SwitchNormalMap();
		void SwitchDepthBufferVisualization();
		void SwitchBoundingBoxVisualization();
		void ToggleUniformClearColor();
		void ToggleCullMode();

	private:
		//SHARED
		SDL_Window* m_pWindow{};

		int m_Width{};
		int m_Height{};

		bool m_IsInitialized{ false };

		Camera m_Camera{};
		float m_Angle{};
		Vector3 m_Translation{};

		//DIRECTX
		HRESULT InitializeDirectX();
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
		IDXGISwapChain* m_pSwapChain;
		ID3D11Texture2D* m_pDepthStencilBuffer;
		ID3D11DepthStencilView* m_pDepthStencilView;
		ID3D11Resource* m_pRenderTargetBuffer;
		ID3D11RenderTargetView* m_pRenderTargetView;
		std::vector<MeshRepresentation*> m_pMeshes;
		MeshRepresentation* m_pFireMesh;

		void RenderDirectX() const;
		void UpdateDirectX(const Timer* pTimer);

		//Rasterizer
		SDL_Surface* m_pFrontBuffer{ nullptr };
		SDL_Surface* m_pBackBuffer{ nullptr };
		uint32_t* m_pBackBufferPixels{ nullptr };
		std::vector<MeshRast> m_pMeshesRast;

		float* m_pDepthBufferPixels{};

		Texture* m_pDiffuseTxt;
		Texture* m_pNormalTxt;
		Texture* m_pSpecularTxt;
		Texture* m_pGlossTxt;

		enum class LightMode
		{
			ObservedArea,
			Diffuse,
			Specular,
			Combined
		};
		LightMode m_LightMode{ LightMode::Combined };

		void RenderRasterizer(); 
		void UpdateRasterizer(const Timer* pTimer);

		ColorRGB PixelShading(const Vertex_Out& v) const;
		void VertexTransformationFunctionW4(std::vector<MeshRast>& meshes) const;

		//Switch States
		bool m_UsingDirectX = true;
		bool m_IsRotating = true;
		bool m_UsingFireMesh = true;
		bool m_UsingNormalMap = true;
		bool m_DepthBufferVisualization = false;
		bool m_BoundingBoxVisualization = false;
		bool m_UniformClearColor = false;

		//Color
		const int m_Yellow{ 14 };
		const int m_Green{ 10 };
		const int m_Magenta{ 13 };
		const int m_Red{ 12 };
		const int m_White{ 15 };
	};
