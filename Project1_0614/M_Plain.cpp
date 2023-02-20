#include "M_Plain.h"
#include "drawaxis.h"
#include	"ModelMgr.h"
#include	"CDirectInput.h"

M_Plain::InitData M_Plain::ObjectInitData[] = {
    // �e
    {M_No1_PARTS::NONE, M_No1_PARTS::FACE,{0.0f,0.0f,10.0f},{ 0,0,0 }},
    {M_No1_PARTS::FACE, M_No1_PARTS::COVER,{0.0f,0.0f,0.0f},{ 0,0,0 }},
    {M_No1_PARTS::FACE, M_No1_PARTS::CORE,{0.0f,0.0f,0.0f},{ 0,0,0 }},
    {M_No1_PARTS::FACE, M_No1_PARTS::L_ARM,{0.0f,0.0f,0.0f},{ 0,0,0 }},
    {M_No1_PARTS::FACE, M_No1_PARTS::R_ARM,{0.0f,0.0f,0.0f},{ 0,0,0 }},
    {M_No1_PARTS::END, M_No1_PARTS::END,{0.0f,0.0f,0.0f},{ 0,0,0 }},

};


// ���f���t�@�C�������X�g
M_Plain::M_No1_ModelData  M_Plain::FileData[] = {
    {M_No1_PARTS::FACE,"assets/plain/face.obj"},
    {M_No1_PARTS::COVER,"assets/plain/cover.obj"},
    {M_No1_PARTS::CORE,"assets/plain/core.obj"},
    {M_No1_PARTS::L_ARM,"assets/plain/left_arm.obj"},
    {M_No1_PARTS::R_ARM,"assets/plain/right_arm.obj"},
    {M_No1_PARTS::END,nullptr},
};

// ���f����ǂݍ��񂾂��ǂ���
bool M_Plain::m_modelloadflag = false;

bool M_Plain::Init()
{
    //bool sts = true;
	// �s�񏉊���
	DX11MtxIdentity(m_mtx);


    //// �ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
    //if (M_Plain::m_modelloadflag == false) {
    //    // ���f���ǂݍ��݁iHERO�p�j
    //    for (int i = 0; i < static_cast<int>(M_Plain::PARTSMAX) - 2; i++) {
    //        sts = ModelMgr::GetInstance().LoadModel(
    //            M_Plain::FileData[i].filename,	// �t�@�C���� 
    //            "shader/vs.hlsl",				// ���_�V�F�[�_�[
    //            "shader/ps.hlsl",				// �s�N�Z���V�F�[�_�[
    //            "assets/plain/");				// �e�N�X�`���̊i�[�t�H���_
    //        if (!sts) {
    //            char str[128];
    //            sprintf_s<128>(str, "%s", M_Plain::FileData[i].filename);
    //            MessageBox(nullptr, str, "load error", MB_OK);
    //        }
    //    }
    //    M_Plain::m_modelloadflag = true;
    //}

    //// ���f���|�C���^�[���Z�b�g
    //for (int i = 0; i < static_cast<int>(M_Plain::PARTSMAX) - 2; i++) {
    //    SetModel(ModelMgr::GetInstance().GetModelPtr(FileData[i].filename), i);
    //}

    //// �v���C���s�񏉊���(�����ʒu)�i�����̂��Ƃ������l�����s����쐬�j
    //for (int i = 0; i < static_cast<int>(M_Plain::PARTSMAX) - 2; i++) {
    //    DX11MakeWorldMatrix(m_mtxlocalpose[i], ObjectInitData[i].FirstAngle, ObjectInitData[i].FirstPosition);
    //}

    //// �e�q�֌W���l�������s����v�Z����
    //CaliculateParentChildMtx();

    m_actionKeepTime = 100;

	// ���f���̓ǂݍ���
	bool sts = m_model[0].Init(
		"assets/plain/cover.obj",	// �t�@�C���� 
		"shader/vs.hlsl",			// ���_�V�F�[�_�[
		"shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
		"assets/plain/");	// �e�N�X�`���̊i�[�t�H���_

	// ���f���̓ǂݍ���
	 sts = m_model[1].Init(
		"assets/plain/face.obj",	// �t�@�C���� 
		"shader/vs.hlsl",			// ���_�V�F�[�_�[
		"shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
		"assets/plain/");	// �e�N�X�`���̊i�[�t�H���_

     // ���f���̓ǂݍ���
     sts = m_model[2].Init(
         "assets/plain/core.obj",	// �t�@�C���� 
         "shader/vs.hlsl",			// ���_�V�F�[�_�[
         "shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
         "assets/plain/");	// �e�N�X�`���̊i�[�t�H���_

     // ���f���̓ǂݍ���
     sts = m_model[3].Init(
         "assets/plain/left_arm.obj",	// �t�@�C���� 
         "shader/vs.hlsl",			// ���_�V�F�[�_�[
         "shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
         "assets/plain/");	// �e�N�X�`���̊i�[�t�H���_

      // ���f���̓ǂݍ���
     sts = m_model[4].Init(
         "assets/plain/right_arm.obj",	// �t�@�C���� 
         "shader/vs.hlsl",			// ���_�V�F�[�_�[
         "shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
         "assets/plain/");	// �e�N�X�`���̊i�[�t�H���_


	// �����ʒu
	m_pos.x = 5;
	m_pos.y = 0;
	m_pos.z = 10;

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;

	isActive = true;
    // �V�[�h�l����p����
    std::random_device rand_dev;
    // �V�[�h�l�Z�b�g
    m_mt.seed(rand_dev());
    m_mt2.seed(rand_dev());

	return sts;
}


void M_Plain::AIaction()
{
    // AI�̓����쐬

    switch (state)
    {
    case AI_MOVE::AI_INIT: // ����
        // �v���C���s�񏉊���(�����ʒu)�i�����̂��Ƃ������l�����s����쐬�j
        for (int i = 0; i < static_cast<int>(M_Plain::PARTSMAX) - 2; i++) {
            DX11MakeWorldMatrix(m_mtxlocalpose[i], ObjectInitData[i].FirstAngle, ObjectInitData[i].FirstPosition);
        }
        state = AI_MOVE::AI_IDLE;// �ҋ@�Ɉڂ�
        break;

    case AI_MOVE::AI_IDLE:// �ҋ@
        // �s���͈͓��ł��낤�낷�� 20x20
        //UpdateLocalpose();
            break;
    case AI_MOVE::AI_APPROACH:// �ڋ�
        // ���E�͈͂ɓ���Ƌ߂Â�

        break;
    }

   // // ��������
   // std::uniform_int_distribution<int32_t> rand4(0, static_cast<int>(M_Plain::ACTION::MAX_ACTION) - 1);
   // std::uniform_int_distribution<int32_t> rand10(10, 50);

   // // ��]�p���������񃊃Z�b�g
   // m_angle.x = m_angle.y = m_angle.z = 0.0f;

   // // �A�N�V�����ɂ���]�p���Z�b�g
   // switch (m_action)
   // {
   // case M_Plain::ACTION::ACT_STRAIGHT:
   //     m_angle.x = m_angle.y = m_angle.z = 0.0f;
   //     break;
   // case M_Plain::ACTION::ACT_LEFT:
   //     m_angle.x = 0.01f;
   //     break;
   // case M_Plain::ACTION::ACT_RIGHT:
   //     m_angle.x = -0.01f;
   //     break;
   ///* case Enemy::ACTION::ACT_UP:
   //     m_angle.x = 1.0f;
   //     break;
   // case Enemy::ACTION::ACT_DOWN:
   //     m_angle.x = -1.0f;
   //     break;*/
   // case M_Plain::ACTION::ACT_ROLLP:
   //     m_angle.z = -0.01f;
   //     break;
   // case M_Plain::ACTION::ACT_ROLLM:
   //     m_angle.z = 0.01f;
   //     break;
   // }

   // // �J�E���^�[���Z
   // if (--m_actionKeepTime <= 0) {
   //     // �����ɂ�莟�̃A�N�V�����Ǝ������Ԃ�ݒ�
   //     m_action = static_cast<ACTION>(rand4(m_mt));
   //     m_actionKeepTime = rand10(m_mt2);
   // }
}

void M_Plain::Update()
{    
    //// ���[�J���|�[�Y���X�V����
    //UpdateLocalpose();
    ////AIaction();
    //// �e�q�֌W���l�������s����v�Z����
    //CaliculateParentChildMtx();

	// AI�̓����̏�����...
	XMFLOAT3 pos = {};
    XMFLOAT4 axisX;
    XMFLOAT4 axisY;
    XMFLOAT4 axisZ;

    //AIaction();
    test();

    // X�������o��
    axisX.x = m_mtx._11;
    axisX.y = m_mtx._12;
    axisX.z = m_mtx._13;
    axisX.w = 0.0f;

    // Y�������o��
    axisY.x = m_mtx._21;
    axisY.y = m_mtx._22;
    axisY.z = m_mtx._23;
    axisY.w = 0.0f;

    // Z�������o��
    axisZ.x = m_mtx._31;
    axisZ.y = m_mtx._32;
    axisZ.z = m_mtx._33;
    axisZ.w = 0.0f;

    XMFLOAT4 qt;

    // �s�񂩂�N�I�[�^�j�I���쐬
    DX11GetQtfromMatrix(m_mtx, qt);

    XMFLOAT4 qtx, qty, qtz;

    // �w�莲��]�̃N�I�[�^�j�I���쐬
    DX11QtRotationAxis(qtx, axisX, m_angle.x);
    DX11QtRotationAxis(qty, axisY, m_angle.y);
    DX11QtRotationAxis(qtz, axisZ, m_angle.z);
    // �N�I�[�^�j�I������
    XMFLOAT4 tempqt1;
    DX11QtMul(tempqt1, qt, qtx);

    XMFLOAT4 tempqt2;
    DX11QtMul(tempqt2, qty, qtz);

    XMFLOAT4 tempqt3;
    DX11QtMul(tempqt3, tempqt1, tempqt2);

    // �N�I�[�^�j�I�����m�[�}���C�Y
    DX11QtNormalize(tempqt3, tempqt3);
    // �N�I�[�^�j�I������s����쐬
    DX11MtxFromQt(m_mtx, tempqt3);

    // Z�������o��
    axisZ.x = m_mtx._31;
    axisZ.y = m_mtx._32;
    axisZ.z = m_mtx._33;
    axisZ.w = 0.0f;

    m_pos.x -= axisZ.x * m_speed;
    m_pos.y -= axisZ.y * m_speed;
    m_pos.z -= axisZ.z * m_speed;

    m_mtx._41 = m_pos.x;
    m_mtx._42 = m_pos.y;
    m_mtx._43 = m_pos.z;


    //keyinput = false;
}

void M_Plain::Update_test()
{
    XMFLOAT4 axisX;
    XMFLOAT4 axisY;
    XMFLOAT4 axisZ;

    static bool keyinput = true;

    //�@�{�̂̈ړ�����
    //  X�������o��
    axisX.x = m_mtx._11;
    axisX.y = m_mtx._12;
    axisX.z = m_mtx._13;
    axisX.w = 0.0f;

    // Y�������o��
    axisY.x = m_mtx._21;
    axisY.y = m_mtx._22;
    axisY.z = m_mtx._23;
    axisY.w = 0.0f;

    // Z�������o��
    axisZ.x = m_mtx._31;
    axisZ.y = m_mtx._32;
    axisZ.z = m_mtx._33;
    axisZ.w = 0.0f;

    // �ړ��ʋy�ъp�x���O�ɂ���
    m_speed = 0.0f;
    m_angle.x = m_angle.y = m_angle.z = 0.0f;

    if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LEFT)) {
        m_angle.y -= 1.0f;
        keyinput = true;
    }

    if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_RIGHT)) {
        m_angle.y += 1.0f;
        keyinput = true;
    }
    if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_UP)) {
        m_speed = 1.0f;
        keyinput = true;
    }

    if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_DOWN)) {
        m_speed = -1.0f;
        keyinput = true;
    }

    // �L�[���͂��������ꍇ
    if (keyinput) {
        XMFLOAT4 qt;	// �N�I�[�^�j�I��

        // �s�񂩂�N�I�[�^�j�I���𐶐�
        DX11GetQtfromMatrix(m_mtx, qt);

        XMFLOAT4 qtx, qty, qtz;		// �N�I�[�^�j�I��

        // �w�莲��]�̃N�I�[�^�j�I���𐶐�
        DX11QtRotationAxis(qtx, axisX, m_angle.x);
        DX11QtRotationAxis(qty, axisY, m_angle.y);
        DX11QtRotationAxis(qtz, axisZ, m_angle.z);

        // �N�I�[�^�j�I��������
        XMFLOAT4 tempqt1;
        DX11QtMul(tempqt1, qt, qtx);

        XMFLOAT4 tempqt2;
        DX11QtMul(tempqt2, qty, qtz);

        XMFLOAT4 tempqt3;
        DX11QtMul(tempqt3, tempqt1, tempqt2);

        // �N�I�[�^�j�I�����m�[�}���C�Y
        DX11QtNormalize(tempqt3, tempqt3);

        // �N�I�[�^�j�I������s����쐬
        DX11MtxFromQt(m_mtx, tempqt3);
    }
    // Z�������o��
    axisZ.x = m_mtx._31;
    axisZ.y = m_mtx._32;
    axisZ.z = m_mtx._33;
    axisZ.w = 0.0f;

    // �ʒu���X�V
    m_pos.x += axisZ.x * m_speed;
    m_pos.y += axisZ.y * m_speed;
    m_pos.z += axisZ.z * m_speed;

    m_mtx._41 = m_pos.x;
    m_mtx._42 = m_pos.y;
    m_mtx._43 = m_pos.z;

    // ���[�J���|�[�Y���X�V����
    UpdateLocalpose();

    // �e�q�֌W���l�������s����v�Z����
    CaliculateParentChildMtx();

    keyinput = false;
}

void M_Plain::MosionUpdate()
{ 
    // �o�����̃��[�V�����쐬

}

void M_Plain::BattleUpdate()
{
   
    m_pos.z -= 0.3f;
    //if (m_pos.z >= 5) m_pos.z = 5.0f;

    m_mtx._41 = m_pos.x;
    m_mtx._42 = m_pos.y;
    m_mtx._43 = m_pos.z;
}

void M_Plain::test()
{
    // ��������
    std::uniform_int_distribution<int32_t> rand4(0, static_cast<int>(M_Plain::ACTION::MAX_ACTION) - 1);
    std::uniform_int_distribution<int32_t> rand10(10, 50);

    // ��]�p���������񃊃Z�b�g
    m_angle.x = m_angle.y = m_angle.z = 0.0f;

    // �A�N�V�����ɂ���]�p���Z�b�g
    switch (m_action)
    {
    case M_Plain::ACTION::ACT_STRAIGHT:
        m_angle.x = m_angle.y = m_angle.z = 0.0f;
        break;
    case M_Plain::ACTION::ACT_LEFT:
        m_angle.y = 1.1f;

        break;
    case M_Plain::ACTION::ACT_RIGHT:
        m_angle.y = -1.1f;
        //partsangle[idx].y += 1.0f;
        break;
    case M_Plain::ACTION::ACT_ROLLP:
        m_angle.y = -1.1f;
        // partsangle[idx].y -= 1.0f;
        break;
    case M_Plain::ACTION::ACT_ROLLM:
        m_angle.y = 1.1f;
        //partsangle[idx].y += 1.0f;
        break;
    }
    // m_action = M_Plain::ACTION::ACT_LEFT;
      //�J�E���^�[���Z
    if (--m_actionKeepTime <= 0) {
        // �����ɂ�莟�̃A�N�V�����Ǝ������Ԃ�ݒ�
        m_action = static_cast<ACTION>(rand4(m_mt));
        m_actionKeepTime = rand10(m_mt2);
    }
    //AIaction();

    //// X�������o��
    //axisX.x = m_mtx._11;
    //axisX.y = m_mtx._12;
    //axisX.z = m_mtx._13;
    //axisX.w = 0.0f;

    //// Y�������o��
    //axisY.x = m_mtx._21;
    //axisY.y = m_mtx._22;
    //axisY.z = m_mtx._23;
    //axisY.w = 0.0f;

    //// Z�������o��
    //axisZ.x = m_mtx._31;
    //axisZ.y = m_mtx._32;
    //axisZ.z = m_mtx._33;
    //axisZ.w = 0.0f;

    //XMFLOAT4 qt;

    //// �s�񂩂�N�I�[�^�j�I���쐬
    //DX11GetQtfromMatrix(m_mtx, qt);

    //XMFLOAT4 qtx, qty, qtz;

    //// �w�莲��]�̃N�I�[�^�j�I���쐬
    //DX11QtRotationAxis(qtx, axisX, m_pos.x);
    //DX11QtRotationAxis(qty, axisY, m_pos.y);
    //DX11QtRotationAxis(qtz, axisZ, m_pos.z);
    //// �N�I�[�^�j�I������
    //XMFLOAT4 tempqt1;
    //DX11QtMul(tempqt1, qt, qtx);

    //XMFLOAT4 tempqt2;
    //DX11QtMul(tempqt2, qty, qtz);

    //XMFLOAT4 tempqt3;
    //DX11QtMul(tempqt3, tempqt1, tempqt2);

    //// �N�I�[�^�j�I�����m�[�}���C�Y
    //DX11QtNormalize(tempqt3, tempqt3);
    //// �N�I�[�^�j�I������s����쐬
    //DX11MtxFromQt(m_mtx, tempqt3);

    //// Z�������o��
    //axisZ.x = m_mtx._31;
    //axisZ.y = m_mtx._32;
    //axisZ.z = m_mtx._33;
    //axisZ.w = 0.0f;

    //m_pos.x -= axisZ.x * m_speed;
    //m_pos.y -= axisZ.y * m_speed;
    //m_pos.z -= axisZ.z * m_speed;

    //m_mtx._41 = m_pos.x;
    //m_mtx._42 = m_pos.y;
    //m_mtx._43 = m_pos.z;

  /*  XMFLOAT4X4 partsmtx;
    DX11MakeWorldMatrix(partsmtx, m_angle, m_pos);
    DX11MtxMultiply(m_mtx, partsmtx, m_mtx);*/
}

void M_Plain::Draw()
{
	// ���f���`��
	m_model[1].Draw(m_mtx);
	m_model[0].Draw(m_mtx);
    m_model[2].Draw(m_mtx);
    m_model[3].Draw(m_mtx);
    m_model[4].Draw(m_mtx);
    /*for (int i = 0; i < static_cast<int>(M_Plain::PARTSMAX) - 2; i++) {
        m_models[i]->Draw(m_mtxParentChild[i]);
    }*/
}

void M_Plain::DrawWithAxis()
{
}
void M_Plain::Finalize()
{
   /* for (int i = 0; i < static_cast<int>(M_Plain::PARTSMAX) - 2; i++) {
        m_models[i]->Uninit();
    }*/
   
    m_model->Uninit();
}

void M_Plain::UpdateLocalpose()
{
    // �e�p�[�c�̉�]�p�x(�O�t���[������̕ψʗ�)
    XMFLOAT3			partsangle[static_cast<int>(M_No1_PARTS::PARTSMAX)];
    XMFLOAT3			partstrans[static_cast<int>(M_No1_PARTS::PARTSMAX)];

    // �ǂ̃p�[�c�𓮂�����
    static int idx = 0;
    bool	initflag = false;

    // �p�x�ƈړ��ʂ�������
    for (int i = 0; i < static_cast<int>(M_No1_PARTS::PARTSMAX); i++) {
        partsangle[i].x = 0.0f;
        partsangle[i].y = 0.0f;
        partsangle[i].z = 0.0f;
        partstrans[i].x = 0.0f;
        partstrans[i].y = 0.0f;
        partstrans[i].z = 0.0f;
    }

    // ����p�[�c��؂�ւ�
    if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_TAB)) {
        idx++;
        if (idx > static_cast<int>(M_No1_PARTS::PARTSMAX) - 3) {
            idx = 0;
        }
    }

    //// �p�[�c�̃��[�J���|�[�Y�����߂�ׂ̃L�[����
    //if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_UP)) {
    //    partsangle[idx].x += 1.0f;
    //}

    //if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_DOWN)) {
    //    partsangle[idx].x -= 1.0f;
    //}

    //if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LEFT)) {
    //    partsangle[idx].y += 1.0f;
    //}

    //if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_RIGHT)) {
    //    partsangle[idx].y -= 1.0f;
    //}

    //if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_F1)) {
    //    partstrans[idx].z += 0.1f;
    //}

    //if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_F2)) {
    //    partstrans[idx].z -= 0.1f;
    //}

    //// ������Ԃɂ���
    //if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE)) {
    //    initflag = true;
    //    idx = 0;
    //}

    //// �����|�[�Y�ɖ߂�
    //if (initflag) {
    //    InitalPose();
    //}

    // ��������
    std::uniform_int_distribution<int32_t> rand4(0, static_cast<int>(M_Plain::ACTION::MAX_ACTION) - 1);
    std::uniform_int_distribution<int32_t> rand10(10, 50);

    // ��]�p���������񃊃Z�b�g
    m_angle.x = m_angle.y = m_angle.z = 0.0f;

    // �A�N�V�����ɂ���]�p���Z�b�g
    switch (m_action)
    {
    case M_Plain::ACTION::ACT_STRAIGHT:
        partstrans[idx].x = partstrans[idx].y = partstrans[idx].z = 0.0f;
        break;
    case M_Plain::ACTION::ACT_LEFT:
        partsangle[idx].y = 1.1f;
        
        break;
    case M_Plain::ACTION::ACT_RIGHT:
        partsangle[idx].y = -1.1f;
        //partsangle[idx].y += 1.0f;
        break;
    case M_Plain::ACTION::ACT_ROLLP:
        partsangle[idx].y = -1.1f;
       // partsangle[idx].y -= 1.0f;
        break;
    case M_Plain::ACTION::ACT_ROLLM:
        partsangle[idx].y = 1.1f;
        //partsangle[idx].y += 1.0f;
        break;
    }
   // m_action = M_Plain::ACTION::ACT_LEFT;
     //�J�E���^�[���Z
    if (--m_actionKeepTime <= 0) {
        // �����ɂ�莟�̃A�N�V�����Ǝ������Ԃ�ݒ�
        m_action = static_cast<ACTION>(rand4(m_mt));
        m_actionKeepTime = rand10(m_mt2);
    }
    XMFLOAT4 axisX;
    XMFLOAT4 axisY;
    XMFLOAT4 axisZ;

    //AIaction();

    // X�������o��
    axisX.x = m_mtx._11;
    axisX.y = m_mtx._12;
    axisX.z = m_mtx._13;
    axisX.w = 0.0f;

    // Y�������o��
    axisY.x = m_mtx._21;
    axisY.y = m_mtx._22;
    axisY.z = m_mtx._23;
    axisY.w = 0.0f;

    // Z�������o��
    axisZ.x = m_mtx._31;
    axisZ.y = m_mtx._32;
    axisZ.z = m_mtx._33;
    axisZ.w = 0.0f;

    XMFLOAT4 qt;

    // �s�񂩂�N�I�[�^�j�I���쐬
    DX11GetQtfromMatrix(m_mtx, qt);

    XMFLOAT4 qtx, qty, qtz;

    // �w�莲��]�̃N�I�[�^�j�I���쐬
    DX11QtRotationAxis(qtx, axisX, partstrans[idx].x);
    DX11QtRotationAxis(qty, axisY, partstrans[idx].y);
    DX11QtRotationAxis(qtz, axisZ, partstrans[idx].z);
    // �N�I�[�^�j�I������
    XMFLOAT4 tempqt1;
    DX11QtMul(tempqt1, qt, qtx);

    XMFLOAT4 tempqt2;
    DX11QtMul(tempqt2, qty, qtz);

    XMFLOAT4 tempqt3;
    DX11QtMul(tempqt3, tempqt1, tempqt2);

    // �N�I�[�^�j�I�����m�[�}���C�Y
    DX11QtNormalize(tempqt3, tempqt3);
    // �N�I�[�^�j�I������s����쐬
    DX11MtxFromQt(m_mtx, tempqt3);

    // Z�������o��
    axisZ.x = m_mtx._31;
    axisZ.y = m_mtx._32;
    axisZ.z = m_mtx._33;
    axisZ.w = 0.0f;

    partstrans[idx].x -= axisZ.x * m_speed;
    partstrans[idx].y -= axisZ.y * m_speed;
    partstrans[idx].z -= axisZ.z * m_speed;

    m_mtx._41 = partstrans[idx].x;
    m_mtx._42 = partstrans[idx].y;
    m_mtx._43 = partstrans[idx].z;
    //partstrans[idx].y += 0.05f;
    
   /* if (partstrans[idx].y < 5 && partstrans[idx].y >= 0)
    {
        partstrans[idx].y += 0.05f;
    }
    if (partstrans[idx].y > 5&& partstrans[idx].y >= 0)
    {
        partstrans[idx].y -= 0.05f;
    }*/

    // �p�[�c�̊p�x���[�J���|�[�Y��\���s����v�Z
    XMFLOAT4X4 partsmtx;
    DX11MakeWorldMatrix(partsmtx, partsangle[idx], partstrans[idx]);
    DX11MtxMultiply(m_mtxlocalpose[idx], partsmtx, m_mtxlocalpose[idx]);
}

void M_Plain::CaliculateParentChildMtx()
{
    // ��Ԃ̐e�̃L���^�s���ɍs����Z�b�g
//	m_mtxlocalpose[TANK_CATERPILLAR] = m_mtx;

    // �e�q�֌W���l�������s������
    for (int i = 0; i < static_cast<int>(M_No1_PARTS::PARTSMAX) - 2; i++) {
        m_mtxParentChild[i] = m_mtxlocalpose[i];
        for (int j = static_cast<int>(ObjectInitData[i].ParentObjectNo);
            j != static_cast<int>(M_No1_PARTS::NONE);
            j = static_cast<int>(ObjectInitData[j].ParentObjectNo)) {

            DX11MtxMultiply(m_mtxParentChild[i], m_mtxParentChild[i], m_mtxlocalpose[j]);
        }
    }
}

int M_Plain::AttackDamage()
{
    int damage;
    std::random_device rand_dev;
    std::mt19937 m_mt(rand_dev());
    std::uniform_int_distribution<> rand100(10, 15);
    damage = rand100(m_mt);
    printf("�G�U����%d\n", damage);

    return damage;
}

//void M_Plain::CheckInSight(XMFLOAT3 pos, XMFLOAT4 mtx)
//{
//    bool sts = IsInFrustum(pos, mtx);
//}


