#include	"IScene.h"
#include	"SceneManager.h"

Quad2D		g_quadfadein;
Quad2D		g_quadfadeout;

Quad2D      g_maru;

float pos_y;

IScene::IScene() {
}

void IScene::updateFadeIn(double t) {
	std::cout << "updateFadeIn:" << t << std::endl;

	pos_y -= 1.1f;
	Update();
}

void IScene::updateFadeOut(double t) {
	std::cout << "updateFadeOut:" << t << std::endl;
	Update();
}

void IScene::drawFadeIn(double t)
{
	static bool first = true;
	// ここで真っ黒から透明へアルファ値を変化させながら画面サイズの矩形を描画する
	DirectX::XMFLOAT4 fadecolor = { 0,0,0,1 };

	DirectX::XMFLOAT2 size = { 10,10 };

	DirectX::XMFLOAT2 uv[4] = {
		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f}
	};

	if (first) {
		g_quadfadein.Init(Application::CLIENT_WIDTH,
			Application::CLIENT_HEIGHT,
			DirectX::XMFLOAT4(fadecolor.x, fadecolor.y, fadecolor.z, fadecolor.w), uv);
		g_quadfadein.LoadTexture("assets/white.bmp");

		/*g_maru.Init(Application::CLIENT_WIDTH,
			Application::CLIENT_HEIGHT,
			DirectX::XMFLOAT4(0, 0, 0, 0), uv);
		g_maru.LoadTexture("assets/UI/maru.png");*/
		first = false;
	}

	std::cout << "DrawFadeIn:" << t << std::endl;

	Draw();

	fadecolor = m_manager->GetFadeColor();

	fadecolor.w = fadecolor.w * (1.0 - t);
	size.x = size.x * (1.0 - t);
	size.y = size.y * (1.0 - t);

	TurnOffZbuffer();

	g_quadfadein.SetPosition(
		Application::CLIENT_WIDTH / 2,
		Application::CLIENT_HEIGHT / 2, 0);

	g_quadfadein.updateVertex(
		Application::CLIENT_WIDTH,
		Application::CLIENT_HEIGHT,
		DirectX::XMFLOAT4(fadecolor.x, fadecolor.y, fadecolor.z, fadecolor.w), uv);

	g_quadfadein.updateVbuffer();
	g_quadfadein.Draw();

	/*g_maru.SetPosition(
		Application::CLIENT_WIDTH / 2,
		Application::CLIENT_HEIGHT / 2, 0);
	g_maru.SetScale(size.x, size.y, 0);
	g_maru.updateVertex(
		Application::CLIENT_WIDTH,
		Application::CLIENT_HEIGHT,
		DirectX::XMFLOAT4(1, 1, 1, 1), uv);

	g_maru.updateVbuffer();
	g_maru.Draw();*/

	TurnOnZbuffer();
}

void IScene::drawFadeOut(double t)
{
	static bool first = true;
	// ここで真っ黒から透明へアルファ値を変化させながら画面サイズの矩形を描画する
	DirectX::XMFLOAT4 fadecolor = { 0,0,0,1 };
	DirectX::XMFLOAT2 uv[4] = {
		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f}
	};

	if (first) {
		g_quadfadeout.Init(Application::CLIENT_WIDTH,
			Application::CLIENT_HEIGHT,
			DirectX::XMFLOAT4(fadecolor.x, fadecolor.y, fadecolor.z, fadecolor.w), uv);
		g_quadfadeout.LoadTexture("assets/white.bmp");
		first = false;
	}
	std::cout << "DrawFadeOut:" << t << std::endl;

	TurnOnZbuffer();
	Draw();
	TurnOffZbuffer();

	// ここで透明から真っ黒へアルファ値を変化させながら画面サイズの矩形を描画する
	fadecolor = m_manager->GetFadeColor();

	fadecolor.w = t;

	g_quadfadeout.updateVertex(
		Application::CLIENT_WIDTH,
		Application::CLIENT_HEIGHT,
		DirectX::XMFLOAT4(fadecolor.x, fadecolor.y, fadecolor.z, fadecolor.w), uv);

	g_quadfadeout.updateVbuffer();

	g_quadfadeout.SetPosition(
		Application::CLIENT_WIDTH / 2,
		Application::CLIENT_HEIGHT / 2, 0);

	g_quadfadeout.Draw();

	TurnOnZbuffer();
}