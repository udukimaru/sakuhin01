#pragma once
#include <vector>
/// <summary>
/// 
/// ここにUIたちが使う関数まとめたい
/// 
/// </summary>
class CUI
{
public:
	bool ChangeOnOff();// このボタンがオンなのか　true オン , false オフ

	template<typename T>
	bool IsActive(std::vector<T>& list, bool is)
	{
		for (int i = 0; i < list.size(); i++) {
			list[i].active = is;
		}
	}
};

