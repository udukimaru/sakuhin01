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
////// ���`���
////float lerp(float startPos, float endPos, float t)
////{
////	float val;
////	val = startPos + t * (endPos - startPos);
////	return val;
////}
////
////// �C�[�Y�C��
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
	//// Effekseer�̃I�u�W�F�N�g�̓X�}�[�g�|�C���^�ŊǗ������B�ϐ����Ȃ��Ȃ�Ǝ����I�ɍ폜�����B

	//DeviceDX11 device;
	//auto efkRenderer = device.GetEffekseerRenderer();
	//// Create a manager of effects
	//// �G�t�F�N�g�̃}�l�[�W���[�̍쐬
	//auto efkManager = ::Effekseer::Manager::Create(8000);

	//// Setup effekseer modules
	//// Effekseer�̃��W���[�����Z�b�g�A�b�v����
	//device.SetupEffekseerModules(efkManager);

	//// Specify a position of view
	//// ���_�ʒu���m��
	//auto viewerPosition = ::Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

	//// Specify a projection matrix
	//// ���e�s���ݒ�
	//::Effekseer::Matrix44 projectionMatrix;
	//projectionMatrix.PerspectiveFovRH(90.0f / 180.0f * 3.14f, (float)device.GetWindowSize().X / (float)device.GetWindowSize().Y, 1.0f, 500.0f);

	//// Specify a camera matrix
	//// �J�����s���ݒ�
	//::Effekseer::Matrix44 cameraMatrix;
	//cameraMatrix.LookAtRH(viewerPosition, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f));

	//// Load an effect
	//// �G�t�F�N�g�̓Ǎ�
	//auto effect = Effekseer::Effect::Create(efkManager, u"Dark.efkefc");

	//int32_t time = 0;
	//Effekseer::Handle efkHandle = 0;

	//while (device.NewFrame())
	//{
	//	if (time % 120 == 0)
	//	{
	//		// Play an effect
	//		// �G�t�F�N�g�̍Đ�
	//		efkHandle = efkManager->Play(effect, 0, 0, 0);
	//	}

	//	if (time % 120 == 119)
	//	{
	//		// Stop effects
	//		// �G�t�F�N�g�̒�~
	//		efkManager->StopEffect(efkHandle);
	//	}

	//	// Move the effect
	//	// �G�t�F�N�g�̈ړ�
	//	efkManager->AddLocation(efkHandle, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f));

	//	// Set layer parameters
	//	// ���C���[�p�����[�^�̐ݒ�
	//	Effekseer::Manager::LayerParameter layerParameter;
	//	layerParameter.ViewerPosition = viewerPosition;
	//	efkManager->SetLayerParameter(0, layerParameter);

	//	// Update the manager
	//	// �}�l�[�W���[�̍X�V
	//	Effekseer::Manager::UpdateParameter updateParameter;
	//	efkManager->Update(updateParameter);

	//	// Execute functions about DirectX
	//	// DirectX�̏���
	//	device.ClearScreen();

	//	// Update a time
	//	// ���Ԃ��X�V����
	//	efkRenderer->SetTime(time);

	//	// Specify a projection matrix
	//	// ���e�s���ݒ�
	//	efkRenderer->SetProjectionMatrix(projectionMatrix);

	//	// Specify a camera matrix
	//	// �J�����s���ݒ�
	//	efkRenderer->SetCameraMatrix(cameraMatrix);

	//	//// Begin to rendering effects
	//	//// �G�t�F�N�g�̕`��J�n�������s���B
	//	efkRenderer->BeginRendering();

	//	//// Render effects
	//	//// �G�t�F�N�g�̕`����s���B
	//	Effekseer::Manager::DrawParameter drawParameter;
	//	drawParameter.ZNear = 0.0f;
	//	drawParameter.ZFar = 1.0f;
	//	drawParameter.ViewProjectionMatrix = efkRenderer->GetCameraProjectionMatrix();
	//	efkManager->Draw(drawParameter);

	//	//// Finish to rendering effects
	//	//// �G�t�F�N�g�̕`��I���������s���B
	//	efkRenderer->EndRendering();

	//	// Execute functions about DirectX
	//	// DirectX�̏���
	//	device.PresentDevice();

	//	time++;
	//}
}
//
void Test::Draw()
{
	float col[4] = { 0,0,1,1 };

	// �`��O����
	DX11BeforeRender(col);

	XMFLOAT4X4 mtx;
/*	for (int i = 0; i < ui1.g_buttunlist.size(); i++)
	{
		ui1.updateVertex(ui1.g_buttunlist[i].width, ui1.g_buttunlist[i].height, XMFLOAT4(1, 1, 1, 1), ui1.g_buttunlist[i].uv);
		ui1.updateVbuffer();
		ui1.SetPosition(posx[i], ui1.g_buttunlist[i].y, 0);
		ui1.Draw();
	}*/

	// �G�t�F�N�g�̕`��J�n�������s���B
	//efkRenderer->BeginRendering();

	//// Render effects
	//// �G�t�F�N�g�̕`����s���B
	//Effekseer::Manager::DrawParameter drawParameter;
	//drawParameter.ZNear = 0.0f;
	//drawParameter.ZFar = 1.0f;
	//drawParameter.ViewProjectionMatrix = efkRenderer->GetCameraProjectionMatrix();
	//efkManager->Draw(drawParameter);

	//// Finish to rendering effects
	//// �G�t�F�N�g�̕`��I���������s���B
	//efkRenderer->EndRendering();

	// �v���W�F�N�V�����ϊ��s��擾
	mtx = CCamera::GetInstance()->GetProjectionMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, mtx);

	// �r���[�ϊ��s����擾
	mtx = CCamera::GetInstance()->GetCameraMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, mtx);

	// �`��㏈��
	DX11AfterRender();
//
}
