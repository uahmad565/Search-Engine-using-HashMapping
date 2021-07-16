#pragma once
#include<iostream>
using namespace std;

template<typename T> class List;
class Doc_Info;

template<typename T>
class Term_Info
{
private:
	string keyTerm;
	List<T>* listOfDoc_s;
	friend ostream& operator<<<T>(ostream& _cout, const Term_Info<T>& obj);
public:
	Term_Info();
	Term_Info(string keyTerm); //parametrized constructor
	Term_Info(const Term_Info& obj);
	void insertDoc(int DocId); // insert id in iteself
	string getKeyTerm()const;
	List<T>* getListOfDoc_s() const;
	Term_Info<T>& operator=(const Term_Info<T>& obj);
	~Term_Info();
};

template<typename T>
string Term_Info<T>::getKeyTerm() const
{
	return keyTerm;
}
template<typename T>
List<T>* Term_Info<T>::getListOfDoc_s()const
{
	return listOfDoc_s;
}

template<typename T>
inline Term_Info<T>& Term_Info<T>::operator=(const Term_Info<T>& obj)
{
	delete listOfDoc_s;
	this->keyTerm = obj.keyTerm;
	this->listOfDoc_s=new List<Doc_Info>(*obj.getListOfDoc_s());
	return *this;
}

template<typename T>
Term_Info<T>::Term_Info()
{
	listOfDoc_s = new List<T>();
}

template<typename T>
Term_Info<T>::Term_Info(string keyTerm)
{
	listOfDoc_s = new List<Doc_Info>();
	if (keyTerm.length() != 0)
	{
		this->keyTerm = keyTerm;
	}
	

}

template<typename T>
Term_Info<T>::Term_Info(const Term_Info& obj)
{
	this->keyTerm = obj.keyTerm;
	List<Doc_Info>* listDocPtr=obj.getListOfDoc_s();
	this->listOfDoc_s = new List<Doc_Info>(*listDocPtr);
}

template<typename T>
inline void Term_Info<T>::insertDoc( int DocId)
{
	typename List<Doc_Info>::Iterator iter= listOfDoc_s->begin();
	bool flag = false;
	while (iter != nullptr && !flag)
	{
		if ((*iter).getDocID() == DocId)
		{
			(*iter).incrementFrequencyByOne();
			flag = true;
		}
		iter++;
	}
	if (!flag)
	{
		Doc_Info doc_Info(DocId,1);
		listOfDoc_s->insertAtEnd(doc_Info);
	}
}

template<typename T>
Term_Info<T>::~Term_Info()
{
	if (listOfDoc_s != nullptr)
		delete listOfDoc_s;
}



template<typename T>
ostream& operator<<( ostream & _cout,  const Term_Info<T> & obj)
{
	_cout << obj.keyTerm <<" ";
typename	List<Doc_Info>::Iterator iter = obj.listOfDoc_s->begin();
	while (iter != obj.listOfDoc_s->end())
	{
		_cout << "ID=" << iter->data.getDocID() << ",Freq=" << iter->data.getFrequency() <<" ";
		iter++;
	}
	cout << endl;
	return _cout;
}