#include "pch.h"

#if defined(_DEBUG)
#include "vld.h"
#endif

#undef main
#include "Renderer.h"

using namespace dae;

bool g_PrintPFS{ true };

void ShutDown(SDL_Window* pWindow)
{
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Unreferenced parameters
	(void)argc;
	(void)args;

	//Create window + surfaces
	SDL_Init(SDL_INIT_VIDEO);

	const uint32_t width = 640;
	const uint32_t height = 480;

	SDL_Window* pWindow = SDL_CreateWindow(
		"DirectX - ***Van Bogaert Rikki, 2DAE08***",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, 0);

	if (!pWindow)
		return 1;

	//Initialize "framework"
	const auto pTimer = new Timer();
	const auto pRenderer = new Renderer(pWindow);

	//Start loop
	pTimer->Start();
	float printTimer = 0.f;
	bool isLooping = true;
	while (isLooping)
	{
		//--------- Get input events ---------
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				isLooping = false;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_F1:
					pRenderer->SwitchState();
					break;
				case SDL_SCANCODE_F2:
					pRenderer->SwitchRotating();
					break;
				case SDL_SCANCODE_F3:
					pRenderer->SwitchUsingFire();
					break;
				case SDL_SCANCODE_F4:
					pRenderer->SwitchTechniques();
					break;
				case SDL_SCANCODE_F5:
					pRenderer->SwitchShadingMode();
					break;
				case SDL_SCANCODE_F6:
					pRenderer->SwitchNormalMap();
					break;
				case SDL_SCANCODE_F7:
					pRenderer->SwitchDepthBufferVisualization();
					break;
				case SDL_SCANCODE_F8:
					pRenderer->SwitchBoundingBoxVisualization();
					break;
				case SDL_SCANCODE_F9:
					pRenderer->ToggleCullMode();
					break;
				case SDL_SCANCODE_F10:
					pRenderer->ToggleUniformClearColor();
					break;
				case SDL_SCANCODE_F11:
					g_PrintPFS = !g_PrintPFS;
					break;
				}
				break;
			default: 
				break;
			}
		}

		//--------- Update ---------
		pRenderer->Update(pTimer);

		//--------- Render ---------
		pRenderer->Render();

		//--------- Timer ---------
		pTimer->Update();
		if(g_PrintPFS)
		{
			printTimer += pTimer->GetElapsed();
			if (printTimer >= 1.f)
			{
				printTimer = 0.f;
				std::cout << "dFPS: " << pTimer->GetdFPS() << std::endl;
			}
		}
	}
	pTimer->Stop();

	//Shutdown "framework"
	delete pRenderer;
	delete pTimer;

	ShutDown(pWindow);
	return 0;
}