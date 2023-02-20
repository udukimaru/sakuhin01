#include "Stage.h"
#include "CModel.h"
#include "Shader1.h"

void Stage::ChipDraw(int z, int x) {

    ID3D11DeviceContext* devcontext;

    devcontext = GetDX11DeviceContext();

    DirectX::XMFLOAT4X4 mtx;
    DirectX::XMFLOAT3 trans = { MAPCHIPWIDTH * x,0,-MAPCHIPWIDTH * z };

    DX11MtxTranslation(trans, mtx);

    // ���[���h�ϊ��s��Z�b�g
    DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, mtx);

    // �e�N�X�`���Z�b�g
    devcontext->PSSetShaderResources(0, 1, m_srv.GetAddressOf());

    devcontext->Draw(4,   //�`�悷�钸�_��
        0);               //���_�o�b�t�@�̍ŏ�����g��
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

    // ���_�f�[�^�̒�`
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
    };
    unsigned int numElements = ARRAYSIZE(layout);

    // ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
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

    // �s�N�Z���V�F�[�_�[�𐶐�
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

    // ���_�o�b�t�@���Z�b�g����
    unsigned int stride = sizeof(Vertex);
    unsigned offset = 0;
    devcontext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

    devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);  // �g�|���W�[���Z�b�g�i���v���~�e�B�u�^�C�v�j

    devcontext->IASetInputLayout(m_pVertexLayout.Get());                         // ���_���C�A�E�g���Z�b�g

    devcontext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);   //���_�V�F�[�_�[���Z�b�g
    devcontext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);    //�s�N�Z���V�F�[�_�[���Z�b�g

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

// �T�C�R����X���W��Z���W�������œn���@�߂�l�ł��̉��̃}�b�v�`�b�v�ԍ���Ԃ�
//int Stage::GetMapChipNo