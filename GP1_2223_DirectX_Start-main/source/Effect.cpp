#include "pch.h"
#include "Effect.h"
#include "Texture.h"


Effect::Effect(ID3D11Device* pDevice, const std::wstring& assetFile):
	m_pEffect { LoadEffect(pDevice, assetFile) }
{

	m_pTechnique = m_pEffect->GetTechniqueByName("PointFilteringTechnique");
	if (!m_pTechnique->IsValid())
	{
		std::wcout << L"Technique not valid\n";
	}
	//Matrices
	m_pMatWorldViewProjVariable = m_pEffect->GetVariableByName("gWorldViewProj")->AsMatrix();
	if (!m_pMatWorldViewProjVariable->IsValid())
	{
		std::wcout << L"m_pMatWorldViewProjVariable not valid\n";
	}

	m_pMatWorldViewInvertVariable = m_pEffect->GetVariableByName("gViewInverseMatrix")->AsMatrix();
	if (!m_pMatWorldViewInvertVariable->IsValid())
	{
		std::wcout << L"m_pMatWorldViewInvertVariable not valid\n";
	}

	m_pMatWorldVariable = m_pEffect->GetVariableByName("gWorldMatrix")->AsMatrix();
	if (!m_pMatWorldVariable->IsValid())
	{
		std::wcout << L"m_pMatWorldVariable not valid\n";
	}

	//Shading
	m_pDiffuseMapVariable = m_pEffect->GetVariableByName("gDiffuseMap")->AsShaderResource();
	if (!m_pDiffuseMapVariable->IsValid())
	{
		std::wcout << L"m_pDiffuseMapVariable not valid!\n";
	}

	m_pNormalMapVariable = m_pEffect->GetVariableByName("gNormalMap")->AsShaderResource();
	if (!m_pNormalMapVariable->IsValid())
	{
		std::wcout << L"m_pNormalMapVariable not valid!\n";
	}

	m_pSpecularMapVariable = m_pEffect->GetVariableByName("gSpecularMap")->AsShaderResource();
	if (!m_pSpecularMapVariable->IsValid())
	{
		std::wcout << L"m_pSpecularMapVariable not valid!\n";
	}

	m_pGlossinessMapVariable = m_pEffect->GetVariableByName("gGlossinessMap")->AsShaderResource();
	if (!m_pGlossinessMapVariable->IsValid())
	{
		std::wcout << L"m_pGlossinessMapVariable not valid!\n";
	}


}

Effect::~Effect()
{
	m_pEffect->Release();
}


void Effect::ToggleTechniques()
{
	const Uint8* pStates{ SDL_GetKeyboardState(nullptr) };
	if (pStates[SDL_SCANCODE_F2] && !m_IsButtonDown)
	{
		if (int(m_FilteringMethod) < 2) // < amount FilteringMethods - 1
			m_FilteringMethod = FilteringMethod(int(m_FilteringMethod) + 1);
		else
			m_FilteringMethod = FilteringMethod(0);


		switch (m_FilteringMethod)
		{
		case Effect::FilteringMethod::Point:
			m_pTechnique = m_pEffect->GetTechniqueByName("PointFilteringTechnique");
			if (!m_pTechnique->IsValid())
				std::wcout << L"PointTechnique not valid\n";
			break;
		case FilteringMethod::Linear:
			m_pTechnique = m_pEffect->GetTechniqueByName("LinearFilteringTechnique");
			if (!m_pTechnique->IsValid())
				std::wcout << L"LinearTechnique not valid\n";
			break;
		case FilteringMethod::Anisotropic:
			m_pTechnique = m_pEffect->GetTechniqueByName("AnisotropicFilteringTechnique");
			if (!m_pTechnique->IsValid())
				std::wcout << L"AnisotropicTechnique not valid\n";
			break;
		default:
			break;
		}

		m_IsButtonDown = true;
	}
	else
	{
		m_IsButtonDown = false;
	}
}

void Effect::SetProjectionMatrix(const dae::Matrix& matrix)
{
	m_pMatWorldViewProjVariable->SetMatrix(reinterpret_cast<const float*>(&matrix));
}

void Effect::SetViewInvertMatrix(const dae::Matrix& matrix)
{
	m_pMatWorldViewInvertVariable->SetMatrix(reinterpret_cast<const float*>(&matrix));
}

void Effect::SetWorldMatrix(const dae::Matrix& matrix)
{
	m_pMatWorldVariable->SetMatrix(reinterpret_cast<const float*>(&matrix));
}

void Effect::SetDiffuseMap(Texture* pDiffuseTexture)
{
	if (m_pDiffuseMapVariable)
		m_pDiffuseMapVariable->SetResource(pDiffuseTexture->GetSRV());
}

void Effect::SetNormalMap(Texture* pNormalTexture)
{
	if (m_pNormalMapVariable)
	{
		m_pNormalMapVariable->SetResource(pNormalTexture->GetSRV());
	}
}

void Effect::SetSpecularMap(Texture* pSpecularTexture)
{
	if (m_pSpecularMapVariable)
	{
		m_pSpecularMapVariable->SetResource(pSpecularTexture->GetSRV());
	}
}

void Effect::SetGlossinessMap(Texture* pGlossinessTexture)
{
	if (m_pGlossinessMapVariable)
	{
		m_pGlossinessMapVariable->SetResource(pGlossinessTexture->GetSRV());
	}
}

ID3DX11Effect* Effect::GetEffect()
{
	return m_pEffect;
}

ID3DX11EffectTechnique* Effect::GetTechnique()
{
	return m_pTechnique;
}

ID3D11InputLayout* Effect::GetInputLayout()
{
	return m_pInputLayout;
}

ID3DX11Effect* Effect::LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile)
{
	HRESULT result;
	ID3D10Blob* pErrorBlob{ nullptr };
	ID3DX11Effect* pEffect;
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3DCOMPILE_DEBUG;
	shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	result = D3DX11CompileEffectFromFile(assetFile.c_str(),
		nullptr,
		nullptr,
		shaderFlags,
		0,
		pDevice,
		&pEffect,
		&pErrorBlob);
	if (FAILED(result))
	{
		if (pErrorBlob != nullptr)
		{
			const char* pErrors = static_cast<char*>(pErrorBlob->GetBufferPointer());

			std::wstringstream ss;
			for (unsigned int i = 0; i < pErrorBlob->GetBufferSize(); i++)
				ss << pErrors[i];

			OutputDebugStringW(ss.str().c_str());
			pErrorBlob->Release();
			pErrorBlob = nullptr;

			std::wcout << ss.str() << std::endl;
		}
		else
		{
			std::wstringstream ss;
			ss << "EffectLoader: Failed to CreateEffectFromFile!\nPath: " << assetFile;
			std::wcout << ss.str() << std::endl;
			return nullptr;
		}
	}
	return pEffect;
}

