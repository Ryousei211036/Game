//==============================================================================================
//
// 経験値ゲージ　　　expgage.cpp
// 土田凌聖
//
//==============================================================================================

//**********************************************************************************************
// インクルード
//**********************************************************************************************
#include"expgage.h"
#include"renderer.h"
#include"player.h"

//==============================================================================================
// コンストラクタ
//==============================================================================================
CExpgage::CExpgage() : CObject2D(4)
{
	m_fExpWidth = 0.0f;
	m_fTotalExp = 0.0f;
	m_LevelUpCount = 0;
}

//==============================================================================================
// デストラクタ
//==============================================================================================
CExpgage::~CExpgage()
{
}

//==============================================================================================
// 初期化処理
//==============================================================================================
HRESULT CExpgage::Init(D3DXVECTOR3 pos)
{
	CObject2D::Init(pos);
	m_fExpWidth = EXPGAGE_WIDTH;
	m_LevelUpCount = 1;

	return S_OK;
}

//==============================================================================================
// 終了処理
//==============================================================================================
void CExpgage::Uninit()
{
	CObject2D::Uninit();
}

//==============================================================================================
// 更新処理
//==============================================================================================
void CExpgage::Update()
{
	CObject2D::Update();
}

//==============================================================================================
// 描画処理
//==============================================================================================
void CExpgage::Draw()
{
	CObject2D::Draw();

#ifdef _DEBUG
	LPD3DXFONT m_Font;
	m_Font = CRenderer::GetFont();

	//ExpGage(m_Font);
#endif // _DEBUG
}

//==============================================================================================
// 生成処理
//==============================================================================================
CExpgage *CExpgage::Create(D3DXVECTOR3 pos, float width, float width2, float height, D3DXCOLOR col)
{
	CExpgage *pExpgage = nullptr;

	pExpgage = new CExpgage;

	if (pExpgage != nullptr)
	{
		pExpgage->Init(pos);				// 初期化
		pExpgage->SetGagelength(width, width2, height);	// サイズの設定
		pExpgage->SetCol(col);						// 色の設定
	}

	return pExpgage;
}

//==============================================================================================
// 経験値ゲージを増やす
//==============================================================================================
bool CExpgage::AddExpgage(float Exp)
{
	if (m_LevelUpCount < PLAYER_MAXLEVEL)
	{
		// 経験値の増加量の算出
		float fAddExp = (m_fExpWidth) * (Exp / 100);
		m_fTotalExp += fAddExp + m_fExtraExp;		// 経験値の合計

		if (m_fTotalExp < EXPGAGE_WIDTH
			&& m_LevelUpCount < PLAYER_MAXLEVEL)
		{
			// 経験値ゲージの設定
			CObject2D::SetGageSize(m_fTotalExp);

			m_fExtraExp = 0.0f;
		}
		else
		{
			m_fExtraExp = m_fTotalExp - EXPGAGE_WIDTH;	// ゲージからはみ出た分

			// 経験値ゲージの設定
			CObject2D::SetGageSize(m_fExtraExp);

			m_fTotalExp = 0.0f;
			m_LevelUpCount++;

			if (m_LevelUpCount >= PLAYER_MAXLEVEL)
			{
				// 経験値ゲージの設定
				CObject2D::SetGageSize(EXPGAGE_WIDTH);
			}

			return true;
		}
	}

	return false;
}