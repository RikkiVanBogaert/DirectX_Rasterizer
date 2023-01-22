#include "pch.h"
#include "ShadedEffect.h"
#include "Texture.h"

ShadedEffect::ShadedEffect(ID3D11Device* pDevice, const std::wstring& assetFile)
	:Effect(pDevice, assetFile)
{
	m_pNormalMap = m_pEffect->GetVariableByName("gNormalMap")->AsShaderResource();
	if (!m_pNormalMap->IsValid())
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

ShadedEffect::~ShadedEffect()
{
	if (m_pEffect)
	{
		m_pEffect->Release();
		m_pEffect = nullptr;
	}
	/*m_pNormalMapVariable->Release();
	m_pSpecularMapVariable->Release();
	m_pGlossinessMapVariable->Release();*/
}

void ShadedEffect::SetNormalMap(Texture* pNormalTexture)
{
	if (m_pNormalMap)
	{
		m_pNormalMap->SetResource(pNormalTexture->GetSRV());
	}
}

void ShadedEffect::SetSpecularMap(Texture* pSpecularTexture)
{
	if (m_pSpecularMapVariable)
	{
		m_pSpecularMapVariable->SetResource(pSpecularTexture->GetSRV());
	}
}

void ShadedEffect::SetGlossinessMap(Texture* pGlossinessTexture)
{
	if (m_pGlossinessMapVariable)
	{
		m_pGlossinessMapVariable->SetResource(pGlossinessTexture->GetSRV());
	}
}

//void ShadedEffect::SetWorldMatrix(const Matrix& matrix)
//{
//	m_pWorldVariable->SetMatrix(reinterpret_cast<const float*>(&matrix));
//}
//
//void ShadedEffect::SetViewInvertMatrix(const Matrix& matrix)
//{
//	m_pViewInverseVariable->SetMatrix(reinterpret_cast<const float*>(&matrix));
//}
