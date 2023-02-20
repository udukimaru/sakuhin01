#pragma once
#include	<directxmath.h>
#include "dx11mathutil.h"
class GameObject {

	uint64_t m_id = 0;

protected:
	DirectX::XMFLOAT3 m_pos{};				// ˆÊ’u
	DirectX::XMFLOAT4X4 m_mtx{};
	DirectX::XMFLOAT4X4 g_mtxtotal{};
public:
	GameObject() {};
	virtual ~GameObject() {};
	virtual bool Init() = 0;
	virtual void Finalize() = 0;

	// p¨‚ğæ“¾
	DirectX::XMFLOAT4X4 GetMtx() {
		return m_mtx;
	}

	void SetPos(DirectX::XMFLOAT3 pos) {
		m_mtx._41 = pos.x;
		m_mtx._42 = pos.y;
		m_mtx._43 = pos.z;
	}

	void SetDirection(float dir) {
		
		DX11MtxRotationY(dir, m_mtx);
	}

	// ˆÊ’u‚ğæ“¾
	DirectX::XMFLOAT3 GetPos() {
		return m_pos;
	}

	// ‚h‚c‚ğæ“¾
	uint64_t GetID() {
		return m_id;
	}
};