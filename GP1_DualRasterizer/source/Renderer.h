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
		void SwitchFPSPrinting(bool& printFPS);

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

		void RenderHardware() const;
		void UpdateHardware(const Timer* pTimer);

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

		void RenderSoftware(); 
		void UpdateSoftware(const Timer* pTimer);

		ColorRGB PixelShading(const Vertex_Out& v) const;
		void VertexTransformationFunctionW4(std::vector<MeshRast>& meshes) const;

		//Switch States
		bool m_UsingHardware = true;
		bool m_IsRotating = true;
		bool m_UsingFireMesh = true;
		bool m_UsingNormalMap = true;
		bool m_DepthBufferVisualization = false;
		bool m_BoundingBoxVisualization = false;
		bool m_UniformClearColor = false;

		//TextColors
		const int m_WhiteText{ 15 };
		const int m_YellowText{ 6 };
		const int m_GreenText{ 10 };
		const int m_MagentaText{ 13 };
	};
