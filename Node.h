#pragma once
#include"List.h"

template<typename T>
class List;

template<typename T>
class Node
{
public:
	Node<T>*next,*prev;
	T data;
public:

	
	friend class List<T>;
	Node()
	{
		next = prev = nullptr;
	}
	Node(T data, Node<T>*prev=nullptr, Node<T>*next=nullptr )
	{
		this->prev=prev;
		this->next=next;
		this->data=data;
	}
	~Node()
	{

	}
};