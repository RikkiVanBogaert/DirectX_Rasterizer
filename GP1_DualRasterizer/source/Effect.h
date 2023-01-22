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
	void ToggleTechniques();
	void ToggleCullMode();

	ID3DX11Effect* GetEffect() const;
	ID3DX11EffectTechnique* GetTechnique() const;
	ID3D11InputLayout* GetInputLayout() const;

	enum class FilteringMethod
	{
		Point,
		Linear,
		Anisotropic
	};
	FilteringMethod GetSampleState() const;

	enum class CullMode
	{
		None,
		Front,
		Back
	};
	CullMode GetCullMode() const;

protected:
	FilteringMethod m_FilteringMethod;

	ID3DX11Effect* m_pEffect{};
	ID3DX11EffectTechnique* m_pTechnique{};
	ID3D11InputLayout* m_pInputLayout{};

	//Transform Matrices
	ID3DX11EffectMatrixVariable* m_pMatWorldViewProjVariable{};
	ID3DX11EffectMatrixVariable* m_pViewInverseVariable{};
	ID3DX11EffectMatrixVariable* m_pWorldVariable{};

	//Shading
	ID3DX11EffectShaderResourceVariable* m_pDiffuseMapVariable{};

	//Cullmode
	ID3D11Device* m_pDevice{};
	CullMode m_CullMode{};
	ID3D11RasterizerState* m_pRasterizerState{};
	ID3DX11EffectRasterizerVariable* m_pRasterizerStateVariable{};

	static ID3DX11Effect* LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile);
};

