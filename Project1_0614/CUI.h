#pragma once
#include <vector>
/// <summary>
/// 
/// ������UI�������g���֐��܂Ƃ߂���
/// 
/// </summary>
class CUI
{
public:
	bool ChangeOnOff();// ���̃{�^�����I���Ȃ̂��@true �I�� , false �I�t

	template<typename T>
	bool IsActive(std::vector<T>& list, bool is)
	{
		for (int i = 0; i < list.size(); i++) {
			list[i].active = is;
		}
	}
};

