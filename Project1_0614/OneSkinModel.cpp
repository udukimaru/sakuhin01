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
//XMFLOAT4X4		g_mtxplayer;		// 主人公の行列
//
////CLight			g_directionallight;	// 平行光源
//
//MeshData		g_meshData;			// メッシュのデータ
//Skeleton		g_skeleton;			// モデルのスケルトン
//std::vector<std::unique_ptr<AnimationClip>> g_animationClips; // 読み込んだアニメーションクリップの配列
//Animation		g_animation;		// アニメーションさせる機能
//Material_OneSkin		g_material;			// マテリアル
//Texture_OneSkin			g_texture;			// テクスチャー
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
//	// 骨用の定数バッファ初期化
//	Skeleton::InitConstantBufferBoneMatrix(
//		CDirectXGraphics::GetInstance()->GetDXDevice());
//
//	AssimpScene assimpScene;
//
//	// データ読み込み
//	assimpScene.Init("assets/ThirdPerson.fbx");
//
//	// メッシュデータ読み込み
//	g_meshData.Load(&assimpScene);
//
//	// データからスケルトン読み込み
//	g_skeleton.Load(&assimpScene);
//
//	g_animation.SetSkeleton(&g_skeleton);
//
//	//// データからアニメーション読み込み
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
//	//// ブレンドアニメーション作成
//	g_blendAnimation.AddBlendSample(g_animationClips[0].get(), 0.0f);
//	g_blendAnimation.AddBlendSample(g_animationClips[1].get(), 0.5f);
//	g_blendAnimation.AddBlendSample(g_animationClips[2].get(), 1.0f);
//	g_animation.AddAnimationClips(&g_blendAnimation);
//
//	// アニメーションに追加
//	const int animClipNum = g_animationClips.size();
//	for (int i = 0; i < animClipNum; i++)
//	{
//		g_animation.AddAnimationClips(g_animationClips[i].get());
//	}
//
//
//
//	// シェーダ読み込み
//	g_material.LoadShader("shader/vsoneskin.fx", "shader/graymanps.fx");
//
//	// テクスチャー読み込み
//	g_texture.Load("GraymanMaskTex.png", "assets");
//
//	// 単位行列にする
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
//	// アニメーションブレンド
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
//	// アニメーション切り替え
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
//	// アニメーションスピード制御
//	static float animSpeed = 1.0f;
//	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_Q)) {
//		animSpeed -= 0.01f;
//	}
//	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_E)) {
//		animSpeed += 0.01f;
//	}
//	g_animation.SetMotionSpeed(animSpeed);
//
//	// 仮処理
//	// 60fpsと仮定して更新
//	float fps = 30;
//	g_animation.UpdateAnimation(1.0f / fps);
//
//	// キー入力があったときだけ移動する
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
//	// マウスの処理
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
//		// 一度押したときだけマウス位置を前回のものにする
//		if (input.GetMouseLButtonTrigger())
//		{
//			oldpos.x = input.GetMousePosX();
//			oldpos.y = input.GetMousePosY();
//		}
//		//現在のマウス位置
//		currentpos.x = input.GetMousePosX();
//		currentpos.y = input.GetMousePosY();
//
//		// 前回と現在のマウス位置の距離を求める
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
