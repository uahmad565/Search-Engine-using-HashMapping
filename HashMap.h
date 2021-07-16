#pragma once
#include<iostream>
#include<string>
#include "List.h"
#include "HashItem.h"
using namespace std;


class Hash
{
public:
	size_t operator()(int key, int tablesize)
	{
		return key % tablesize;
	}

};

template<typename T>
class HashMap
{
	List<HashItem<T>>** hashItemLists;
	int currentHashItems;
	int capacity;
public:
	HashMap();
	HashMap(int capacity);
	void Initialize2Darray(List<HashItem<T>>** hashLists, int CapacityOfList);
	void deleteHashLists();
	List<HashItem<T>>* insert(const T& obj, int key);
	typename List<HashItem<T>>::Iterator search(int key);
	int getCapacity()const;
	void deleteKey(int key);
	void print()const;
	float loadFactor();
	void doubleCapacity();
};

template<typename T>
inline HashMap<T>::HashMap()
	:HashMap(10)
{
}

template<typename T>
inline HashMap<T>::HashMap(int capacity)
	:capacity(capacity),currentHashItems(0)
{
	hashItemLists = new List<HashItem<T>>* [capacity];
	Initialize2Darray(this->hashItemLists, this->capacity);
}

template<typename T>
inline void HashMap<T>::Initialize2Darray(List<HashItem<T>>** hashLists, int CapacityOfList)
{
	for (int i = 0; i < CapacityOfList; i++)
	{
		hashLists[i] = nullptr;
	}
}

template<typename T>
inline void HashMap<T>::deleteHashLists()
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (hashItemLists[i])
		{
			delete hashItemLists[i];
		}
	}
	delete[] hashItemLists;
	hashItemLists = nullptr;
}

template<typename T>
inline List<HashItem<T>>* HashMap<T>::insert(const T& obj, int key)
{
	if (loadFactor() >= 0.75)
		doubleCapacity();
	HashItem<T> hashItem(obj, key);
	Hash hash;
	int index=hash(key, capacity);
	if (hashItemLists[index] == nullptr)
	{
		hashItemLists[index] = new List<HashItem<T>>;
	}
	hashItemLists[index]->insertAtEnd(hashItem);
	currentHashItems++;
	return hashItemLists[index];
}

template<typename T>
inline typename List<HashItem<T>>::Iterator HashMap<T>::search(int key)
{
	HashItem<T> dummy(key);
	Hash hash;
	int index = hash(key, capacity);
	typename List<HashItem<T>>::Iterator iter;
	if (hashItemLists[index])
	{
		iter = hashItemLists[index]->find(key);
	}
	return iter;
}

template<typename T>
inline int HashMap<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
inline void HashMap<T>::deleteKey(int key)
{
	typename List<HashItem<T>>::Iterator iter =search(key);
	Hash hash;
	int index=hash(key, capacity);
	if (iter != nullptr)
	{
		hashItemLists[index]->remove(iter);
		//return true;
	}
	//return false;
}

template<typename T>
inline void HashMap<T>::print() const
{
	int i = 0;
	while (i < capacity)
	{
		cout << i<<" ";
		if (hashItemLists[i])
		{
			hashItemLists[i]->print();
		}
		else
			cout << "Empty\n";
		i++;
	}

}

template<typename T>
inline float HashMap<T>::loadFactor()
{
	float x = currentHashItems;
	x=x/ capacity;
	return x;
}

template<typename T>
inline void HashMap<T>::doubleCapacity()
{
	List<HashItem<T>>** newHashItemLists=new List<HashItem<T>>*[capacity*2];
	Initialize2Darray(newHashItemLists, capacity*2);
	int i = 0;
	while (i < capacity)
	{
		if (hashItemLists[i])
		{
			if (hashItemLists[i])
			{
				typename List<HashItem<T>>::Iterator iter = hashItemLists[i]->begin();
				for (; iter != hashItemLists[i]->end(); iter++)
				{
					int Key = iter->data.getKey();
					Hash hash;
					int index = hash(Key, capacity * 2);
					if (newHashItemLists[index]==nullptr)
					{
						newHashItemLists[index] = new List<HashItem<T>>();
					}
					newHashItemLists[index]->insertAtEnd(iter->data);
				}
			}
			
		}
		i++;
	}
	deleteHashLists();
	capacity *= 2;
	hashItemLists = newHashItemLists;
}


