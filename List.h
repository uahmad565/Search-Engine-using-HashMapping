#pragma once
#include<iostream>
#include "Node.h"
#include "HashItem.h"
using namespace std;

class Doc_Info;
template <typename T> class Node;
template<typename T> class Term_Info;
template<typename T> class HashItem;

template<typename T>
class List //List Class Is Doubly Linked List Using dummy datas for Head And Tail
{
private:
	class ListIterator
	{
	private:
		Node<T>* ptr;
	public:
		friend class List<T>;
		ListIterator(Node<T>* ptr = nullptr)
		{
			this->ptr = ptr;
		}
		ListIterator operator++(int x)          //preIncrement
		{
			ListIterator oldIter(*this);
			if (this->ptr != nullptr)
			{
				ptr = ptr->next;
			}
			return oldIter;
		}
		T &operator*()
		{
			return ptr->data;
		}
		ListIterator& operator=(const ListIterator& obj)
		{
			this->ptr = obj.ptr;
			return *this;
		}
		bool operator==(const ListIterator& obj)
		{
			return ptr == obj.ptr;
		}
		bool operator!=(const ListIterator& obj)
		{
			return ptr != obj.ptr;
		}
		
		Node<T>*& operator->()
		{
			return ptr;
		}
	};

	Node<T>*head;
	Node<T>*tail;
	int noOfNodes;
public:
	typedef ListIterator Iterator;
	Iterator find(int key);

public:
	List();
	List(int noOfNodes);
	List(const List<T>& listOperand);
	void reverseList();
	int getNoOfNodes()const;
	bool remove(Iterator ptr);
	Iterator find(const T& val);
	void insertAtStart(const T data);
	Iterator insertAtEnd(const T data);
	bool insertBefore(const T insertedItem, const T keyData);
	void deleteAtStart();
	void deleteAtEnd();
	void print()const;
	bool insert(const T NewData, Node<T>* ptr);
	void clear();
	bool deleteNode(Iterator ptr);
	List<T>& operator=(const List& obj);
	Iterator begin();
	Iterator end();
	~List();
};



template<>
inline typename List<HashItem<Term_Info<Doc_Info>>>::Iterator List<HashItem<Term_Info<Doc_Info>>>::find(int key)
{
	for (Iterator iter = begin(); iter != end(); iter++)
	{
		if ((*iter).getKey() == key)
		{
			return iter;
		}
	}
	return Iterator();
}

template<typename T>
inline List<T>::List()
{
	head = new Node<T>();
	tail = new Node<T>();
	head->next = tail;
	tail->prev = head;
	noOfNodes = 0;
}

template<typename T>
inline List<T>::List(int noOfNodes)
	:List()
{
	for (int i = 0; i < noOfNodes; i++)
	{
		insertAtEnd(0);
	}
	this->noOfNodes = noOfNodes;

}

template<typename T>
inline List<T>::List(const List<T>& listOperand)
{
	head = new Node<T>();
	tail = new Node<T>();
	head->next = tail;
	tail->prev = head;
	noOfNodes = 0;

	if (listOperand.noOfNodes != 0)
	{
		Node<T>* temp = listOperand.head->next;
		while (temp != listOperand.tail)
		{
			insertAtEnd(temp->data);
			temp = temp->next;
		}
	}
	this->noOfNodes = listOperand.noOfNodes;
}

template<typename T>
inline void List<T>::reverseList()
{
	int i = 0;
	Node<T>* start = head->next;
	Node<T>* end = tail->prev;
	while (i < noOfNodes / 2)
	{
		swap(start->data, end->data);
		start = start->next;
		end = end->prev;
		i++;
	}
}





template<typename T>
inline int List<T>::getNoOfNodes() const
{
	return noOfNodes;
}

template<typename T>
inline bool List<T>::remove(Iterator ptr)
{
	if (ptr != nullptr)
	{
		Iterator found = find(ptr->data);
		if (found == nullptr)
			return false;
		deleteNode(found);
		return true;
	}
	return false;
}

template<typename T>
inline typename List<T>::Iterator List<T>::find(const T& data)
{
	Iterator iter;
	for (Node<T>* i = head->next; i != tail; i = i->next)
	{
		if (i->data == data)
		{
			iter.ptr = (i);
			return iter;
		}
	}
	return iter;
}

template<typename T>
inline void List<T>::insertAtStart(const T data)
{
	insert(data, head);
}

template<typename T>
inline typename List<T>::Iterator List<T>::insertAtEnd(const T data)
{
	insert(data, tail->prev);
	Iterator iter(tail->prev);
	return iter;
}

template<typename T>
inline bool List<T>::insertBefore(const T insertedItem, const T keyData)
{
	Node<T>* key = find(keyData);
	if (key != nullptr)
	{
		Node<T>* newNode = new Node<T>(insertedItem);
		key->prev->next = newNode;
		newNode->prev = key->prev;
		newNode->next = key;
		key->prev = newNode;
		noOfNodes++;
		return true;
	}
	return false;

}

template<typename T>
inline void List<T>::deleteAtStart()
{
	deleteNode(head->next);
}

template<typename T>
inline void List<T>::deleteAtEnd()
{
	deleteNode(tail->prev);
}

template<typename T>
inline void List<T>::print() const
{
	for (Node<T>* i = head->next; i != tail; i = i->next)
	{
		cout << i->data;
		i->next == tail ? cout << "" : cout << " ";
	}
	cout << endl;
}

template<typename T>
inline bool List<T>::insert(const T NewData, Node<T>* ptr)
{
	if (ptr != tail)
	{
		Node<T>* newNode = new Node<T>(NewData);
		newNode->prev = ptr;
		newNode->next = ptr->next;
		ptr->next = newNode;
		newNode->next->prev = newNode;
		noOfNodes++;
		return true;
	}
	else
		return false;

}

template<typename T>
inline void List<T>::clear()
{
	Iterator iter;
	iter.ptr = head;
	while (iter != nullptr)
	{
		head = head->next;
		if (head != nullptr)
			head->prev = nullptr;
		delete iter.ptr;
		iter.ptr = head;
	}
}



template<typename T>
inline bool List<T>::deleteNode(Iterator ptr)
{
	if (ptr != nullptr)
	{
		if (ptr != head && ptr != tail)
		{
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			delete ptr.operator->();
			noOfNodes--;
			return true;
		}
		return false;
	}
	return false;
}

template<typename T>
inline List<T>& List<T>::operator=(const List<T>& obj)
{
	Node<T>*temp=(obj.head)->next;
	while (temp !=obj.tail )
	{
		insertAtEnd(temp->data);
		temp = temp->next;
	}
	return *this;
}

template<typename T>
typename inline List<T>::Iterator List<T>::begin()
{
	Iterator iter;
	if (noOfNodes > 0)
	{
		iter.ptr = head->next;
	}
	return iter;
}

template<typename T>
typename inline List<T>::Iterator List<T>::end()
{
	Iterator iter;
	if (noOfNodes != 0)
	{
		iter.ptr = tail;
	}
	return iter;
}


template<typename T>
inline List<T>::~List()
{
	clear();
}
