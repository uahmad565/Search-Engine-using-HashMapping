#pragma once
#include<iostream>
#include<vector>
#include"List.h"
#include<iostream>
using namespace std;

class Doc_Info;
template<typename T> class List;
template <typename T> class Term_Info;
template<typename T> class HashMap;
template<typename T> class HashItem;

class Search_Engine   
{
private:
	HashMap<Term_Info<Doc_Info>>*HashMapOfTerms;
public:
	Search_Engine();                                  //Constructor
	void UserInput_QueryWords();                      //Get Sentence From User
	void tokenize_QueryWords(string input);          //Tokenize QueryWOrds into Vector
	int GenerateHashValue(const string& keyTermName);
	void Create_Index(vector<string> NameList_Docs); //Create all unique words from All DOcuments
	void print() const;
	void Add_Doc_to_Index(const string& DocName,int id);//Add DocInfo To KeyTerm
	void Search_Documents(vector<string> QueryWOrds);           //Search Documents Accordingly QueryWords and Print Docs
	List<Doc_Info>::Iterator find(List<Doc_Info>* listDoc, int id);
	void print_IndexedTerms(vector<string> QueryWOrds);
	void QueryWordsAndCollectiveFreq(List<Doc_Info>*& docList, vector<string> queryWOrds_Token); //Collects collective Frequency.
	//   Using RUle1 and Using Rule2
	void ArrangeDocListByFrequency(List<Doc_Info>*&doc_List);  //Arrange w.r.t DocInfo Frequency
	void ArrangeDocListByID(List<Doc_Info>*& doc_List);         //Arrange DocList w.r.t ID
	void SelectionSortByID(List<Doc_Info>*& doc_List, List<Doc_Info>::Iterator start, List<Doc_Info>::Iterator end);//Arrange List
	//By Selection SOrt From Start To End-1(Fails Condition on End)
	void printDocsList(List<Doc_Info>*& doc_List)const;  //Print DOcs By Name+ID
	~Search_Engine(); //Destructor
	
};