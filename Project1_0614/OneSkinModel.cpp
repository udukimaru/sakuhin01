//#include "OneSkinModel.h"
//#include "Assimpscene.h"
//#include "Skeleton.h"
//#include "AnimationClip.h"
//#include "Animation.h"
//#include "BlendAnimation.h"
//#include "MeshData.h"
//#include "Material.h"
//#include "Texture.h"
//#include "dx11mathutil.h"
//#include "CDirectInput.h"
//#include "CCamera.h"
//#include <memory>
//
//XMFLOAT4X4		g_mtxplayer;		// ��l���̍s��
//
////CLight			g_directionallight;	// ���s����
//
//MeshData		g_meshData;			// ���b�V���̃f�[�^
//Skeleton		g_skeleton;			// ���f���̃X�P���g��
//std::vector<std::unique_ptr<AnimationClip>> g_animationClips; // �ǂݍ��񂾃A�j���[�V�����N���b�v�̔z��
//Animation		g_animation;		// �A�j���[�V����������@�\
//Material_OneSkin		g_material;			// �}�e���A��
//Texture_OneSkin			g_texture;			// �e�N�X�`���[
//BlendAnimation		g_blendAnimation;
//
//
//XMFLOAT3 operator+(XMFLOAT3 left, XMFLOAT3 right)
//{
//	XMFLOAT3 temp;
//	temp.x = left.x + right.x;
//	temp.y = left.y + right.y;
//	temp.z = left.z + right.z;
//
//	return temp;
//}
//XMFLOAT3 operator-(XMFLOAT3 left, XMFLOAT3 right)
//{
//	XMFLOAT3 temp;
//	temp.x = left.x - right.x;
//	temp.y = left.y - right.y;
//	temp.z = left.z - right.z;
//
//	return temp;
//}
//
//
//bool OneSkinModel::Init()
//{
//	// ���p�̒萔�o�b�t�@������
//	Skeleton::InitConstantBufferBoneMatrix(
//		CDirectXGraphics::GetInstance()->GetDXDevice());
//
//	AssimpScene assimpScene;
//
//	// �f�[�^�ǂݍ���
//	assimpScene.Init("assets/ThirdPerson.fbx");
//
//	// ���b�V���f�[�^�ǂݍ���
//	g_meshData.Load(&assimpScene);
//
//	// �f�[�^����X�P���g���ǂݍ���
//	g_skeleton.Load(&assimpScene);
//
//	g_animation.SetSkeleton(&g_skeleton);
//
//	//// �f�[�^����A�j���[�V�����ǂݍ���
//	//const int animNum = assimpScene.GetAnimationsNum();
//	//for (int i = 0; i < animNum; i++)
//	//{
//	//	std::unique_ptr<AnimationClip> ptr;
//	//	ptr = std::make_unique<AnimationClip>();
//	//	ptr.get()->Load(&assimpScene, i);
//	//	g_animationClips.emplace_back(std::move(ptr));
//	//}
//
//	assimpScene.Exit();
//
//	const char* animNames[3] =
//	{
//		"assets/ThirdPersonIdle.fbx",
//		"assets/ThirdPersonWalk.fbx",
//		"assets/ThirdPersonRun.fbx"
//	};
//	for (int i = 0; i < 3; i++)
//	{
//		assimpScene.Init(animNames[i]);
//		std::unique_ptr<AnimationClip> ptr;
//		ptr = std::make_unique<AnimationClip>();
//		ptr.get()->Load(&assimpScene, 0);
//		g_animationClips.emplace_back(std::move(ptr));
//		assimpScene.Exit();
//	}
//
//	//// �u�����h�A�j���[�V�����쐬
//	g_blendAnimation.AddBlendSample(g_animationClips[0].get(), 0.0f);
//	g_blendAnimation.AddBlendSample(g_animationClips[1].get(), 0.5f);
//	g_blendAnimation.AddBlendSample(g_animationClips[2].get(), 1.0f);
//	g_animation.AddAnimationClips(&g_blendAnimation);
//
//	// �A�j���[�V�����ɒǉ�
//	const int animClipNum = g_animationClips.size();
//	for (int i = 0; i < animClipNum; i++)
//	{
//		g_animation.AddAnimationClips(g_animationClips[i].get());
//	}
//
//
//
//	// �V�F�[�_�ǂݍ���
//	g_material.LoadShader("shader/vsoneskin.fx", "shader/graymanps.fx");
//
//	// �e�N�X�`���[�ǂݍ���
//	g_texture.Load("GraymanMaskTex.png", "assets");
//
//	// �P�ʍs��ɂ���
//	DX11MtxIdentity(g_mtxplayer);
//    return false;
//}
//
//void OneSkinModel::Draw()
//{
//}
//
//POINT oldos{};
//
//void OneSkinModel::Update()
//{
//	// �A�j���[�V�����u�����h
//	static float blendParam = 0.0f;
//
//	auto camera = CCamera::GetInstance();
//	CDirectInput& input = CDirectInput::GetInstance();
//
//
//	bool keyinput = false;
//
//	XMFLOAT3 axis(0, 0, 0);
//
//	XMFLOAT4X4 CameraMtx = camera->GetCameraMatrix();
//
//	//float speed = 0.3f;
//
//	//
//	if (input.CheckKeyBuffer(DIK_W)) {
//		keyinput = true;
//		axis.x -= CameraMtx._31;
//		axis.y -= CameraMtx._32;
//		axis.z += CameraMtx._33;
//		blendParam += 0.01f;
//	}
//	else if (input.CheckKeyBuffer(DIK_S)) {
//		keyinput = true;
//		axis.x += CameraMtx._31;
//		axis.y += CameraMtx._32;
//		axis.z -= CameraMtx._33;
//	}
//	else if (input.CheckKeyBuffer(DIK_D))
//	{
//		keyinput = true;
//		axis.x += CameraMtx._11;
//		axis.y += CameraMtx._12;
//		axis.z -= CameraMtx._13;
//	}
//	else if (input.CheckKeyBuffer(DIK_A))
//	{
//		keyinput = true;
//		axis.x -= CameraMtx._11;
//		axis.y -= CameraMtx._12;
//		axis.z += CameraMtx._13;
//	}
//
//	g_animation.SetBlendParameter(blendParam);
//	blendParam = g_animation.GetBlendParameter();
//
//	// �A�j���[�V�����؂�ւ�
//	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE)) {
//		int animno = g_animation.GetMotionIndex();
//		animno++;
//		unsigned int animnummax = g_animation.GetMotionNum();
//		if (animno >= animnummax) {
//			animno = 0;
//		}
//		g_animation.Play(animno);
//		g_animation.SetBlendParameter(0.0f);
//	}
//
//	// �A�j���[�V�����X�s�[�h����
//	static float animSpeed = 1.0f;
//	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_Q)) {
//		animSpeed -= 0.01f;
//	}
//	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_E)) {
//		animSpeed += 0.01f;
//	}
//	g_animation.SetMotionSpeed(animSpeed);
//
//	// ������
//	// 60fps�Ɖ��肵�čX�V
//	float fps = 30;
//	g_animation.UpdateAnimation(1.0f / fps);
//
//	// �L�[���͂��������Ƃ������ړ�����
//	if (keyinput)
//	{
//		axis.y = 0;
//		DX11Vec3Normalize(axis, axis);
//		m_pos.x += axis.x * 0.2f;
//		m_pos.y += axis.y * 0.2f;
//		m_pos.z += axis.z * 0.2f;
//		SetPos(m_pos);
//	}
//
//	// �}�E�X�̏���
//	XMFLOAT3 lookat = camera->GetLookat();
//	XMFLOAT3 eye = camera->GetEye();
//
//	XMFLOAT3 distance;
//
//	auto pos = GetPos();
//
//	distance = lookat - pos;
//	lookat = lookat - distance;
//	eye = eye - distance;
//
//	POINT currentpos{};
//	if (input.GetMouseLButtonCheck())
//	{
//		// ��x�������Ƃ������}�E�X�ʒu��O��̂��̂ɂ���
//		if (input.GetMouseLButtonTrigger())
//		{
//			oldpos.x = input.GetMousePosX();
//			oldpos.y = input.GetMousePosY();
//		}
//		//���݂̃}�E�X�ʒu
//		currentpos.x = input.GetMousePosX();
//		currentpos.y = input.GetMousePosY();
//
//		// �O��ƌ��݂̃}�E�X�ʒu�̋��������߂�
//		distance.x = currentpos.x - oldpos.x;
//		distance.y = currentpos.y - oldpos.y;
//
//		// 
//		float angleY = 1.0f * (static_cast<float>(distance.x) / 5.0f);
//		float angleX = 1.0f * (static_cast<float>(distance.y) / 5.0f);
//		auto dis = eye;
//
//		dis.x -= lookat.x;
//		dis.y -= lookat.y;
//		dis.z -= lookat.z;
//
//		XMFLOAT4X4 mtxX;
//		XMFLOAT4X4 mtxY;
//
//		DX11MtxRotationX(angleX, mtxX);
//		DX11MtxRotationY(angleY, mtxY);
//
//		DX11MtxMultiply(mtxY, mtxY, mtxX);
//
//		DX11Vec3MulMatrix(dis, dis, mtxY);
//
//		dis.x += lookat.x;
//		dis.y += lookat.y;
//		dis.z += lookat.z;
//
//		eye = dis;
//		oldpos = currentpos;
//
//
//	}
//	camera->SetEye(eye);
//	camera->SetLookat(lookat);
//	camera->CreateCameraMatrix();
//	camera->CreateProjectionMatrix();
//}
//
//void OneSkinModel::Finalize()
//{
//}
