#include "Stage.h"
#include "CModel.h"
#include "Shader1.h"

void Stage::ChipDraw(int z, int x) {

    ID3D11DeviceContext* devcontext;

    devcontext = GetDX11DeviceContext();

    DirectX::XMFLOAT4X4 mtx;
    DirectX::XMFLOAT3 trans = { MAPCHIPWIDTH * x,0,-MAPCHIPWIDTH * z };

    DX11MtxTranslation(trans, mtx);

    // ワールド変換行列セット
    DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, mtx);

    // テクスチャセット
    devcontext->PSSetShaderResources(0, 1, m_srv.GetAddressOf());

    devcontext->Draw(4,   //描画する頂点数
        0);               //頂点バッファの最初から使う
}

bool Stage::Create()
{
    ID3D11Device* dev;
    ID3D11DeviceContext* devcontext;

    dev = GetDX11Device();
    devcontext = GetDX11DeviceContext();

   /* for (int i = 0; i < 4; i++)
    {*/
        bool sts;
        sts = CreateSRVfromFile(m_texfilename, dev, devcontext, &m_tex ,&m_srv);

        if (!sts) {
            MessageBox(nullptr, "load tex error (stage)", "error", MB_OK);
        }
    //}

        sts = CreateVertexBuffer(dev, sizeof(Vertex), 4, m_v, &m_pVertexBuffer);
    if (!sts) {
        MessageBox(nullptr, "CreateVertexBuffer erroe(stage)", "error", MB_OK);
    }

    // 頂点データの定義
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
    };
    unsigned int numElements = ARRAYSIZE(layout);

    // 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
    sts = CreateVertexShader(dev,
        "shader/vs.hlsl",
        "main",
        "vs_5_0",
        layout,
        numElements,
        &m_pVertexShader,
        &m_pVertexLayout);
    if (!sts) {
        MessageBox(nullptr, "CreateVertexShader error(stage)", "error", MB_OK);
    }

    // ピクセルシェーダーを生成
    sts = CreatePixelShader(
        dev,
        "shader/pstexcol.hlsl",
        "main",
        "ps_5_0",
        & m_pPixelShader);
    if (!sts) {
        MessageBox(nullptr, "CreatePixelShader error(stage)", "error", MB_OK);
    }

    return sts;
}

void Stage::Destroy()
{
}

bool Stage::Init()
{
    bool sts = Create();
    return sts;
}

void Stage::Update()
{
}

//int Stage::GetMapChipNo(int x, int y, int z )
//{
//    
//}
//
//int Stage::GetMapChipNo(int x, int y)
//{
//    //return 0;
//}

void Stage::Draw()
{
    ID3D11DeviceContext* devcontext;

    devcontext = GetDX11DeviceContext();

    // 頂点バッファをセットする
    unsigned int stride = sizeof(Vertex);
    unsigned offset = 0;
    devcontext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

    devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);  // トポロジーをセット（旧プリミティブタイプ）

    devcontext->IASetInputLayout(m_pVertexLayout.Get());                         // 頂点レイアウトをセット

    devcontext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);   //頂点シェーダーをセット
    devcontext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);    //ピクセルシェーダーをセット

    for (int z = -MAPSIZEZ / 2; z <= MAPSIZEZ / 2; z++)
    {
        for (int x = -MAPSIZEX / 2; x <= MAPSIZEX / 2; x++)
        {
            ChipDraw(z,x);
        }
    }

}

void Stage::Finalize()
{
    Destroy();
}

// サイコロのX座標とZ座標を引数で渡す　戻り値でその下のマップチップ番号を返す
//int Stage::GetMapChipNo