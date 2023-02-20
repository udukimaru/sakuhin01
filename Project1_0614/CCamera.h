#include	<directxmath.h>
#include	"Memory.h"
#include    "CDirectInput.h"
#include <random> 

using namespace DirectX;

class CCamera {
	CCamera() {
	}
public:
	CCamera(const CCamera&) = delete;
	CCamera& operator=(const CCamera&) = delete;
	CCamera(CCamera&&) = delete;
	CCamera& operator=(CCamera&&) = delete;

	static CCamera* GetInstance() {
		static CCamera instance;
		return &instance;
	}

	void Init(float nearclip, float farclip, float fov,
		float width, float height,
		XMFLOAT3 eye, XMFLOAT3 lookat, XMFLOAT3 up) {

		SetProjection(nearclip, farclip, fov, width, height);
		SetCamera(eye, lookat, up);
	}

	void SetNear(float nearclip) {
		m_near = nearclip;
	}

	void SetFar(float farclip) {
		m_far = farclip;
	}

	void SetFov(float fov) {
		m_Fov = fov;
	}

	void SetAspect(float width, float height) {
		m_Aspect = width / height;
	}

	void SetProjection(float nearclip, float farclip, float fov, float width, float height) {
		SetNear(nearclip);
		SetFar(farclip);
		SetFov(fov);
		SetAspect(width, height);
		CreateProjectionMatrix();
	}

	void SetCamera(const XMFLOAT3& eye, const XMFLOAT3& lookat, const XMFLOAT3& up) {

		SetEye(eye);
		SetLookat(lookat);
		SetUp(up);
		CreateCameraMatrix();
	}

	void SetEye(const XMFLOAT3& eye) {
		m_Eye = eye;
	}

	void SetLookat(const XMFLOAT3& lookat) {
		m_Lookat = lookat;
	}

	void SetUp(const XMFLOAT3& up) {
		m_Up = up;
	}

	void CreateCameraMatrix() {

		ALIGN16 XMVECTOR Eye = XMVectorSet(m_Eye.x, m_Eye.y, m_Eye.z, 0.0f);
		ALIGN16 XMVECTOR At = XMVectorSet(m_Lookat.x, m_Lookat.y, m_Lookat.z, 0.0f);
		ALIGN16 XMVECTOR Up = XMVectorSet(m_Up.x, m_Up.y, m_Up.z, 0.0f);

		ALIGN16 XMMATRIX camera;
		camera = XMMatrixLookAtLH(Eye, At, Up);

		XMStoreFloat4x4(&m_Camera, camera);
	}

	void CreateProjectionMatrix() {

		ALIGN16 XMMATRIX projection;

		projection = XMMatrixPerspectiveFovLH(m_Fov, m_Aspect, m_near, m_far);

		XMStoreFloat4x4(&m_Projection, projection);

	}

	const XMFLOAT4X4& GetCameraMatrix() {
		return m_Camera;
	}

	const XMFLOAT4X4& GetProjectionMatrix() {
		return m_Projection;
	}

	float GetFov() const {
		return m_Fov;
	}

	const XMFLOAT3& GetEye() const {
		return m_Eye;
	}

	const XMFLOAT3& GetLookat() const {
		return m_Lookat;
	}

	const XMFLOAT3& GetUp() const {
		return m_Up;
	}

	void CameraMoveUpdate() {

		if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_UP)) {
			m_Eye.z += 1.0f;
		}
		if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_DOWN)) {
			m_Eye.z -= 1.0f;
		}
		if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_RIGHT)) {
			m_Eye.x += 1.0f;
		}
		if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LEFT)) {
			m_Eye.x -= 1.0f;
		}

		CreateProjectionMatrix();
		CreateCameraMatrix();

	}

private:
	XMFLOAT4X4		m_Projection;

	XMFLOAT4X4		m_Camera;

	XMFLOAT3		m_Eye;				// �J�����ʒu
	XMFLOAT3		m_Lookat;			// �����_
	XMFLOAT3		m_Up;				// ������x�N�g��

	float			m_near;
	float			m_Aspect;
	float			m_Fov;
	float			m_far;


	XMFLOAT3 lightpos = GetEye();

	enum class ACTION {
		ACT_ZERO = 0,
		ACT_ENEMY,
		ACT_MY_MONSTER,
		ACT_MOVE_1,
		ACT_MOVE_2,

		MAX_ACTION
	};
	ACTION m_action = ACTION::ACT_ZERO;
	unsigned int m_actionKeepTime = 20;

	std::mt19937 m_mt;
	std::mt19937 m_mt2;

	XMFLOAT3		m_EyeTargetPos = { 0,0,0 };
	bool			m_updateflag = false;

public:
	void UpdateCamera();
	void AutoCamera();
	void AutoCameraUpdate();
	void SetEyeTargetPos(XMFLOAT3& eye) {
		if (m_updateflag == false) {
			m_EyeTargetPos = eye;
			m_updateflag = true;
		}
	}
};