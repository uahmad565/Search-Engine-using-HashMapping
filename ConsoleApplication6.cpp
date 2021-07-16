#include <iostream>
#include<vector>
#include "Term_Info.h"
#include "HashItem.h"
#include"Search_Engine.h"
#include "Doc_Info.h"
#include "Term_Info.h"
#include"HashMap.h"
#include"List.h"
using namespace std;



void push_DocList(vector<string>& listOfNames)
{
	listOfNames.push_back("Doc1.txt");
	listOfNames.push_back("Doc2.txt");
	listOfNames.push_back("Doc3.txt");
	listOfNames.push_back("Doc4.txt");
	listOfNames.push_back("Doc5.txt");
}
int main()
{
	Search_Engine searchEngine;
	vector<string> listOfNames;
	push_DocList(listOfNames);
	searchEngine.Create_Index(listOfNames);
	searchEngine.UserInput_QueryWords();

	cout << "\n\n";
	system("pause");
	return 0;
}


void Test()
{
	Term_Info<int> tPtr;
}

void populateDocs(Term_Info<Doc_Info>& obj1, Term_Info<Doc_Info>& obj2)
{
	obj1.insertDoc(1);
	obj1.insertDoc(2);
	obj2.insertDoc(3);
	obj2.insertDoc(4);
}
