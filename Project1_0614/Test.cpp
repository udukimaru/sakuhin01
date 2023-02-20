#include "Test.h"
#include "dx11util.h"
#include "CModel.h"
#include "CCamera.h"
#include "DX11Settransform.h"
#include "dx11mathutil.h"
#include "Application.h"
#include "CDirectInput.h"


#include <stdio.h>
#include <string>
#include <windows.h>

//#include "DeviceDX11.h"
//#include "src/EffectSorce/Effekseer/Effekseer.h"

//#include "M_Dog.h"
//#include "M_Plain.h"
//#include "CCommand.h"
////#include <cmath>
////#include <numbers>
//#include "Easing.h"
//M_Dog dog;
//M_Plain plain;
//
//CCommand ui1;
//float posx[] = { 0,0,0,0 };
//float t[] = { 0.0f,0.0f,0.0f,0.0f };
////
////// 線形補間
////float lerp(float startPos, float endPos, float t)
////{
////	float val;
////	val = startPos + t * (endPos - startPos);
////	return val;
////}
////
////// イーズイン
////float easeIn(float x)
////{
////	return x * x * x;
////}
////
////float easeOut(float x)
////{
////	return 1 + (x - 1) * (x - 1) * (x - 1);
////}
////
////float easeOutBack(float x) {
////	return 1 - (x - 1) * (x - 1) * (-2.70158 * (x - 1) - 1.70158);
////}
////
////float easeOutElastic(float x)
////{
////	float amplitude = 1.0f;
////	float period = 0.01f;
////	float val = amplitude * std::pow(2, -3 * x) * std::sinf((x - (period / (2 * 3.14) * std::asin(1 / amplitude))) * (2 * 3.14) / period) + 1;
////
//// //(ELASTIC_AMPLITUDE * math.pow(2, -10 * t) * math.sin((t - (ELASTIC_PERIOD / (2 * math.pi) * math.asin(1 / ELASTIC_AMPLITUDE))) * (2 * math.pi) / ELASTIC_PERIOD) + 1)
////	return val;
////}
////
////float backOut(float x) 
////{
////	return 1 - (x - 1) * (x - 1) * (-2.70158 * (x - 1) - 1.70158);
////}
////
////float easeOutExpo(float t) {
////	float val= -std::pow(2, -10 * t) + 1;
////	return val;
////}
void Test::Init()
{

}
//
void Test::Input()
{

}

void Test::Finalize()
{

}
//
void Test::Update()
{
	////device.Initialize("DirectDX11", Utils::Vec2I{ 1280, 720 });

	//// Effekseer's objects are managed with smart pointers. When the variable runs out, it will be disposed automatically.
	//// Effekseerのオブジェクトはスマートポインタで管理される。変数がなくなると自動的に削除される。

	//DeviceDX11 device;
	//auto efkRenderer = device.GetEffekseerRenderer();
	//// Create a manager of effects
	//// エフェクトのマネージャーの作成
	//auto efkManager = ::Effekseer::Manager::Create(8000);

	//// Setup effekseer modules
	//// Effekseerのモジュールをセットアップする
	//device.SetupEffekseerModules(efkManager);

	//// Specify a position of view
	//// 視点位置を確定
	//auto viewerPosition = ::Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

	//// Specify a projection matrix
	//// 投影行列を設定
	//::Effekseer::Matrix44 projectionMatrix;
	//projectionMatrix.PerspectiveFovRH(90.0f / 180.0f * 3.14f, (float)device.GetWindowSize().X / (float)device.GetWindowSize().Y, 1.0f, 500.0f);

	//// Specify a camera matrix
	//// カメラ行列を設定
	//::Effekseer::Matrix44 cameraMatrix;
	//cameraMatrix.LookAtRH(viewerPosition, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f));

	//// Load an effect
	//// エフェクトの読込
	//auto effect = Effekseer::Effect::Create(efkManager, u"Dark.efkefc");

	//int32_t time = 0;
	//Effekseer::Handle efkHandle = 0;

	//while (device.NewFrame())
	//{
	//	if (time % 120 == 0)
	//	{
	//		// Play an effect
	//		// エフェクトの再生
	//		efkHandle = efkManager->Play(effect, 0, 0, 0);
	//	}

	//	if (time % 120 == 119)
	//	{
	//		// Stop effects
	//		// エフェクトの停止
	//		efkManager->StopEffect(efkHandle);
	//	}

	//	// Move the effect
	//	// エフェクトの移動
	//	efkManager->AddLocation(efkHandle, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f));

	//	// Set layer parameters
	//	// レイヤーパラメータの設定
	//	Effekseer::Manager::LayerParameter layerParameter;
	//	layerParameter.ViewerPosition = viewerPosition;
	//	efkManager->SetLayerParameter(0, layerParameter);

	//	// Update the manager
	//	// マネージャーの更新
	//	Effekseer::Manager::UpdateParameter updateParameter;
	//	efkManager->Update(updateParameter);

	//	// Execute functions about DirectX
	//	// DirectXの処理
	//	device.ClearScreen();

	//	// Update a time
	//	// 時間を更新する
	//	efkRenderer->SetTime(time);

	//	// Specify a projection matrix
	//	// 投影行列を設定
	//	efkRenderer->SetProjectionMatrix(projectionMatrix);

	//	// Specify a camera matrix
	//	// カメラ行列を設定
	//	efkRenderer->SetCameraMatrix(cameraMatrix);

	//	//// Begin to rendering effects
	//	//// エフェクトの描画開始処理を行う。
	//	efkRenderer->BeginRendering();

	//	//// Render effects
	//	//// エフェクトの描画を行う。
	//	Effekseer::Manager::DrawParameter drawParameter;
	//	drawParameter.ZNear = 0.0f;
	//	drawParameter.ZFar = 1.0f;
	//	drawParameter.ViewProjectionMatrix = efkRenderer->GetCameraProjectionMatrix();
	//	efkManager->Draw(drawParameter);

	//	//// Finish to rendering effects
	//	//// エフェクトの描画終了処理を行う。
	//	efkRenderer->EndRendering();

	//	// Execute functions about DirectX
	//	// DirectXの処理
	//	device.PresentDevice();

	//	time++;
	//}
}
//
void Test::Draw()
{
	float col[4] = { 0,0,1,1 };

	// 描画前処理
	DX11BeforeRender(col);

	XMFLOAT4X4 mtx;
/*	for (int i = 0; i < ui1.g_buttunlist.size(); i++)
	{
		ui1.updateVertex(ui1.g_buttunlist[i].width, ui1.g_buttunlist[i].height, XMFLOAT4(1, 1, 1, 1), ui1.g_buttunlist[i].uv);
		ui1.updateVbuffer();
		ui1.SetPosition(posx[i], ui1.g_buttunlist[i].y, 0);
		ui1.Draw();
	}*/

	// エフェクトの描画開始処理を行う。
	//efkRenderer->BeginRendering();

	//// Render effects
	//// エフェクトの描画を行う。
	//Effekseer::Manager::DrawParameter drawParameter;
	//drawParameter.ZNear = 0.0f;
	//drawParameter.ZFar = 1.0f;
	//drawParameter.ViewProjectionMatrix = efkRenderer->GetCameraProjectionMatrix();
	//efkManager->Draw(drawParameter);

	//// Finish to rendering effects
	//// エフェクトの描画終了処理を行う。
	//efkRenderer->EndRendering();

	// プロジェクション変換行列取得
	mtx = CCamera::GetInstance()->GetProjectionMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, mtx);

	// ビュー変換行列を取得
	mtx = CCamera::GetInstance()->GetCameraMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, mtx);

	// 描画後処理
	DX11AfterRender();
//
}
