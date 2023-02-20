#pragma once
#include "GameObject.h"
#include "CModel.h"
class TestMonster :
    public GameObject
{
   public:
     // �I�u�W�F�N�g��
     enum MONSTERPARTS {
      HIP, // ��
      BODY, // ����
      HEAD, // ��
      ARMR0, // �E��r
      ARML0, // ����r
      LEGR0, // ��������
      LEGL0, // ��������
      ARMR1, // �E��r
      ARML1, // ����r
      LEGR1, // �E����
      LEGL1, // ������
      WINGR0, // �E���O
      WINGL0, // �����O
      WINGR1, // �E���P
      WINGL1, // �����P
      TAIL0, // �K��
      NONE, // �Ȃ�
      END, // �I��
      PARTSMAX
      };
  
  // �\���̌^�^�O(�e�q�֌W�Ə����z�u�f�[�^)
  struct MonsterInitData {
      TestMonster::MONSTERPARTS ParentObjectNo; // �e�I�u�W�F�N�g�m��
      TestMonster::MONSTERPARTS ModelNo; // ���f���ԍ�
      DirectX::XMFLOAT3 FirstPosition; // �ŏ��̈ʒu
      DirectX::XMFLOAT3 FirstAngle; // �ŏ��̊p�x
  };
  
  // �����X�^�[�̃��f�������X�g
  struct MonsterModelData {
      TestMonster::MONSTERPARTS ModelNo; // ���f���ԍ�
  const char* XfileName; // �w�t�@�C����
  };
  
  // �����z�u�f�[�^
  static MonsterInitData ObjectInitData[];
  
  // ���f���t�@�C�������X�g
  static MonsterModelData XFileData[];
  
  // ���f���Z�b�g
  void SetModel(CModel* p,int idx) {
  m_models[idx] = p;
  }
  
  bool Init();
  void Draw();
  void Update();
  void Finalize();
  
  private:
  void UpdateLocalpose(); // ���[�J���|�[�Y���X�V����
  void CaliculateParentChildMtx(); // �e�q�֌W���l�������s����쐬
  static bool m_modelloadflag; // ���f����ǂݍ��񂾂��ǂ���
  CModel* m_models[MONSTERPARTS::PARTSMAX];
  DirectX::XMFLOAT4X4 m_mtxlocalpose[MONSTERPARTS::PARTSMAX]; 
  // �����̂��Ƃ������l�����s��
  DirectX::XMFLOAT4X4 m_mtxParentChild[MONSTERPARTS::PARTSMAX]; 
  // �e�q�֌W���l�������s��
  
  float m_speed = 0.0f; // �X�s�[�h
  DirectX::XMFLOAT3 m_angle; // ��]�p
  
};

