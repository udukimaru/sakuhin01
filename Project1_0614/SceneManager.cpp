#include	"SceneManager.h"

// �ЂƂ̑J�ڕ��@�ōX�V
void SceneManager::updateSingle()
{
	// �o�ߎ��Ԃ��擾
	double elapsed = m_stopwatch.msF();

	// �t�F�[�h�A�E�g�J�ځ@and �o�ߎ��Ԃ��J�ڎ��Ԃ��I�[�o�[�����Ƃ�
	if (m_transitionState == TransitionState::FadeOut
		&& elapsed >= m_transitionTimeMillisec)
	{
		// ���̃V�[���̍X�V���������s
		m_scenefactories[m_nextscenekey]->Update();

		// �J�����g�V�[�������̃V�[���ɂ���
		m_currentscenekey = m_nextscenekey;

		// �J�ڃX�e�[�g���t�F�[�h�C���ɂ���
		m_transitionState = TransitionState::FadeIn;

		// �X�g�b�v�E�H�b�`���ăX�^�[�g
		m_stopwatch.restart();

		// �o�ߎ��Ԃ��O�ɂ��ǂ�
		elapsed = 0.0;
	}

	// �t�F�[�h�C���J�ځ@and �o�ߎ��Ԃ��J�ڎ��Ԃ��I�[�o�[�����Ƃ�
	if (m_transitionState == TransitionState::FadeIn &&
		elapsed >= m_transitionTimeMillisec)
	{
		// �X�g�b�v�E�H�b�`�����Z�b�g
		m_stopwatch.reset();

		// �J�ڎ��Ԃ��`�b�s�h�u�d�ɂ���
		m_transitionState = TransitionState::Active;
	}

	switch (m_transitionState)
	{
		case TransitionState::FadeIn:
			assert(m_transitionTimeMillisec);
			m_scenefactories[m_currentscenekey]->updateFadeIn(elapsed / m_transitionTimeMillisec);
			return;
		case TransitionState::Active:
			m_scenefactories[m_currentscenekey]->Update();
			return;
		case TransitionState::FadeOut:
			assert(m_transitionTimeMillisec);
			m_scenefactories[m_currentscenekey]->updateFadeOut(elapsed / m_transitionTimeMillisec);
			return;
		default:
			return;
	}
}

void SceneManager::updateCross()
{
	// �o�ߎ��Ԃ��擾
	const double elapsed = m_stopwatch.msF();

	// �J�ڕ��@���N���X�t�F�[�h�̏ꍇ
	if (m_transitionState == TransitionState::FadeInOut)
	{
		if (elapsed >= m_transitionTimeMillisec)
		{
			m_currentscenekey = m_nextscenekey;

			m_stopwatch.reset();

			m_transitionState = TransitionState::Active;
		}
	}

	if (m_transitionState == TransitionState::Active)
	{
		m_scenefactories[m_currentscenekey]->Update();

		return;
	}
	else
	{
		const double t = elapsed / m_transitionTimeMillisec;

		m_scenefactories[m_currentscenekey]->updateFadeOut(t);

		m_scenefactories[m_nextscenekey]->updateFadeIn(t);

		return;
	}
}


// �J�����g�V�[�����Z�b�g����
void SceneManager::setCurrentScene(std::string key) {

	m_currentscenekey = key;
}

void SceneManager::Update() {

	if (m_crossFade)
	{
		return updateCross();
	}
	else
	{
		return updateSingle();
	}
}

void SceneManager::Draw() {

	drawScene();

	// �J�����g�V�[���`��
//		m_scenefactories[m_currentscenekey]->Draw();
}



void SceneManager::drawScene()
{
	// �J�����g�V�[���L�[����Ȃ牽�����Ȃ�
	if (m_currentscenekey.empty())
	{
		return;
	}

	// �A�N�e�B�u���J�ڎ��Ԃ��O�Ȃ猻�݃V�[����`��
	if (m_transitionState == TransitionState::Active ||
		!m_transitionTimeMillisec)
	{
		m_scenefactories[m_currentscenekey]->Draw();
	}

	// �o�ߎ��Ԃ��擾
	const double elapsed = m_stopwatch.msF();
		// �J�ڃt�F�[�h�C���Ȃ�
	if (m_transitionState == TransitionState::FadeIn)
	{
		// �t�F�[�h�C���`��

//		TurnOffZbuffer();
		m_scenefactories[m_currentscenekey]->drawFadeIn(elapsed / m_transitionTimeMillisec);
//		TurnOnZbuffer();
	}
	// �J�ڃt�F�[�h�A�E�g�Ȃ�
	else if (m_transitionState == TransitionState::FadeOut)
	{
		// �t�F�[�h�A�E�g�`��
//		TurnOffZbuffer();
		m_scenefactories[m_currentscenekey]->drawFadeOut(elapsed / m_transitionTimeMillisec);
//		TurnOnZbuffer();
	}
	// �J�ڃN���X�t�F�[�h�Ȃ�
	else if (m_transitionState == TransitionState::FadeInOut)
	{
		// �t�F�[�h�A�E�g�`��
//		TurnOffZbuffer();
		m_scenefactories[m_currentscenekey]->drawFadeOut(elapsed / m_transitionTimeMillisec);
			// ���̃V�[�����ݒ肳��Ă����
		if (!m_nextscenekey.empty())
		{
			// �t�F�[�h�C���`��
			m_scenefactories[m_nextscenekey]->drawFadeIn(elapsed / m_transitionTimeMillisec);
		}
//		TurnOnZbuffer();
	}
}

void SceneManager::SetTransitionState(SceneManager::TransitionState ts) {
	m_transitionState = ts;
}


std::string SceneManager::GetCurrentSceneKey() {
	return m_currentscenekey;
}

DirectX::XMFLOAT4 SceneManager::GetFadeColor() {
	return m_fadeColor;
}

void SceneManager::SetFadeColor(DirectX::XMFLOAT4 color) {
	m_fadeColor = color;
}
