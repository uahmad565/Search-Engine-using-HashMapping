#pragma once
#include<iostream>
using namespace std;

class Doc_Info
{
private:
	int DocID;
	int frequency;
	friend  ostream& operator<<(ostream& _cout, const Doc_Info& obj);
	friend class Search_Engine;
public:
	Doc_Info();
	Doc_Info(int doc_id, int frequency=1);
	Doc_Info(const Doc_Info& obj);
	int getDocID()const;
	int getFrequency()const;
	bool checkDocID(int id);
	void incrementFrequencyByOne();
	bool operator==(const Doc_Info& obj);
	void printDocID()const;
	~Doc_Info();
};

