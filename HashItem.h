#pragma once
#include "Doc_Info.h"
#include "Term_Info.h"
using namespace std;

template<typename T>
class HashItem
{
private:
	int key;
	T  value;
	short status;
	//friend class HashMap<T>;
	friend ostream& operator<<<T>(ostream& _cout,  HashItem<T>& obj);
public:
	HashItem(T value, int key)
	{
		this->value = value;
		this->key = key;
	}
	HashItem(int key)
	{
		this->key = key;
		status = 0;
	}
	HashItem()
		:HashItem(-1)
	{
	}
	bool operator==(const HashItem<T>& obj)
	{
		return this->key == obj.key;
	}
	void setStatus(short Status)
	{
		this->status = Status;
	}
	T& getValue()
	{
		return value;
	}
	int getKey()const
	{
		return this->key;
	}
};

template<typename T>
ostream& operator<<(ostream& _cout,  HashItem<T>& obj)
{
	_cout << " ";
	_cout << obj.getValue();
	return _cout;
}