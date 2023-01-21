#pragma once
class Texture;

class Effect final
{
public:
	Effect(ID3D11Device* pDevice, const std::wstring& assetFile);
	~Effect();

	Effect(const Effect&) = delete;
	Effect(Effect&&) noexcept = delete;
	Effect& operator=(const Effect&) = delete;
	Effect& operator=(Effect&&) noexcept = delete;

	void ToggleTechniques();
	//Matrices transformations
	void SetProjectionMatrix(const dae::Matrix& matrix);
	void SetViewInvertMatrix(const dae::Matrix& matrix);
	void SetWorldMatrix(const dae::Matrix& matrix);
	//Shading
	void SetDiffuseMap(Texture* pDiffuseTexture);
	void SetNormalMap(Texture* pNormalTexture);
	void SetSpecularMap(Texture* pSpecularTexture);
	void SetGlossinessMap(Texture* pGlossinessTexture);

	ID3DX11Effect* GetEffect();
	ID3DX11EffectTechnique* GetTechnique();
	ID3D11InputLayout* GetInputLayout();

private:
	enum class FilteringMethod
	{
		Point, 
		Linear,
		Anisotropic
	};
	FilteringMethod m_FilteringMethod;


	ID3DX11Effect* m_pEffect;
	ID3DX11EffectTechnique* m_pTechnique;
	ID3D11InputLayout* m_pInputLayout;

	//Transform Matrices
	ID3DX11EffectMatrixVariable* m_pMatWorldViewProjVariable{};
	ID3DX11EffectMatrixVariable* m_pMatWorldViewInvertVariable{};
	ID3DX11EffectMatrixVariable* m_pMatWorldVariable{};

	//Shading
	ID3DX11EffectShaderResourceVariable* m_pDiffuseMapVariable{};
	ID3DX11EffectShaderResourceVariable* m_pNormalMapVariable{};
	ID3DX11EffectShaderResourceVariable* m_pSpecularMapVariable{};
	ID3DX11EffectShaderResourceVariable* m_pGlossinessMapVariable{};

	bool m_IsButtonDown = false;

	static ID3DX11Effect* LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile);
};

