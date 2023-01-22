#pragma once
class Texture;

using namespace dae;

class Effect
{
public:
	Effect(ID3D11Device* pDevice, const std::wstring& assetFile);
	virtual ~Effect();

	Effect(const Effect&) = delete;
	Effect(Effect&&) noexcept = delete;
	Effect& operator=(const Effect&) = delete;
	Effect& operator=(Effect&&) noexcept = delete;

	//Matrices transformations
	void SetProjectionMatrix(const dae::Matrix& matrix);
	void SetViewInvertMatrix(const dae::Matrix& matrix);
	void SetWorldMatrix(const dae::Matrix& matrix);
	//Shading
	void SetDiffuseMap(Texture* pDiffuseTexture);


	ID3DX11Effect* GetEffect();
	ID3DX11EffectTechnique* GetTechnique();
	ID3D11InputLayout* GetInputLayout();

	void ToggleTechniques();
	int GetSampleState() const;

protected:
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
	ID3DX11EffectMatrixVariable* m_pViewInverseVariable{};
	ID3DX11EffectMatrixVariable* m_pWorldVariable{};

	//Shading
	ID3DX11EffectShaderResourceVariable* m_pDiffuseMapVariable{};

	//Cullmode
	ID3DX11EffectRasterizerVariable* m_CullMode{};

	static ID3DX11Effect* LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile);
};

