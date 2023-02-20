#pragma once
#include	<string>
#include	<unordered_map>
#include	<functional>
#include	<iostream>
#include	<memory>
#include	<directxmath.h>
#include	<chrono>
#include	<thread>
#include	"Application.h"
#include	"uncopyable.h"
#include	"StopWatch.h"
#include	"quad2d.h"
#include	"IScene.h"

class IScene;

class SceneManager {
private:
	// �J�ڕ��@��`�񋓃N���X
	enum class TransitionState
	{
		None,
		FadeIn,
		Active,
		FadeOut,
		FadeInOut,
	};

	// �V�[���ۊ�
	std::unordered_map<std::string, std::unique_ptr<IScene>>	m_scenefactories;
	std::string m_currentscenekey;			// �J�����g�V�[���̃L�[
	std::string m_nextscenekey;				// ���V�[��

	// ��ʑJ�ږ@
	TransitionState m_transitionState = TransitionState::None;

	int32_t	m_transitionTimeMillisec = 1000;	// �J�ڎ��ԁi�f�t�H���g�F�P�O�O�O�~���b�j

	Stopwatch m_stopwatch;						// �X�g�b�v�E�I�b�`

	DirectX::XMFLOAT4 m_fadeColor = DirectX::XMFLOAT4(0, 0, 0, 1);		// �t�F�[�h�J���[

	bool m_crossFade = false;

	void updateSingle();					// �ЂƂ̑J�ڕ��@�ōX�V
	void updateCross();						// �N���X�t�F�[�h�ōX�V
	void drawScene();						// �J�����g�V�[���`��
	void SetTransitionState(SceneManager::TransitionState ts);	// �J�ڕ��@�Z�b�g
public:
	template <class sceneclass>
	void add(std::string key);
	// �V�[����ύX����1
	template <class sceneclass>
	void changeScene(std::string key);

	// �V�[����ύX����2
	template <class sceneclass>
	bool changeScene(std::string key, int32_t transitionTimeMillisec, bool crossFade);

	// �J�����g�V�[�����Z�b�g����
	void setCurrentScene(std::string key);
	void Update();
	void Draw();

	std::string GetCurrentSceneKey();
	DirectX::XMFLOAT4 GetFadeColor();
	void SetFadeColor(DirectX::XMFLOAT4 color);
	
	//bool E_Bchange = false;
};

template <class sceneclass>
void SceneManager::add(std::string key) {
	m_scenefactories[key] = std::move(std::make_unique<sceneclass>());
	m_scenefactories[key].get()->Init();
	m_scenefactories[key].get()->SetSceneManager(this);

	SetTransitionState(SceneManager::TransitionState::Active);
}

// �V�[����ύX����
template <class sceneclass>
void SceneManager::changeScene(std::string key) {

	// �w�肳�ꂽ�L�[�����݂��Ă��邩
	auto it = m_scenefactories.find(key);
	if (it != m_scenefactories.end()) {
		// ���݂��Ă����ꍇ
	}
	else {
		// ���݂��Ă��Ȃ������ꍇ����

		m_scenefactories[key] = std::move(std::make_unique<sceneclass>());
		m_scenefactories[key].get()->Init(this);
		m_scenefactories[key].get()->SetSceneManager(this);
	}

	// �J�����g�V�[���Z�b�g	
	setCurrentScene(key);
}

template <class sceneclass>
bool SceneManager::changeScene(std::string key, int32_t transitionTimeMillisec, bool crossFade) {
	// ���݂̃V�[���ƕύX��̃V�[���������ł���΃N���X�t�F�[�h�s��Ȃ�
	if (key == m_currentscenekey)
	{
		crossFade = false;
	}
	// �w�肳�ꂽ�L�[�����݂��Ă��邩
	auto it = m_scenefactories.find(key);
	if (it != m_scenefactories.end()) {
		// ���݂��Ă����ꍇ
	}
	else {
		// ���݂��Ă��Ȃ������ꍇ����
		m_scenefactories[key] = std::move(std::make_unique<sceneclass>());
		// �V�[��������
		m_scenefactories[key].get()->Init();
		// �V�[���}�l�[�W���̃|�C���^���Z�b�g
		m_scenefactories[key].get()->SetSceneManager(this);
	}
	m_nextscenekey = key;
	m_crossFade = crossFade;
	// �N���X�t�F�[�h���s��
	if (crossFade)
	{
		// �J�ڎ��Ԃ������o�ϐ��ɃZ�b�g
		m_transitionTimeMillisec = transitionTimeMillisec;
		m_transitionState = TransitionState::FadeInOut;
		m_stopwatch.restart();
	}
	else
	{
		//�@�t�F�[�h�A�E�g��Ƀt�F�[�h�C���Ȃ̂őJ�ڎ��Ԃ�2�Ŋ���
		m_transitionTimeMillisec = (transitionTimeMillisec / 2);
		m_transitionState = TransitionState::FadeOut;

		m_stopwatch.restart();
	}

	return true;
}