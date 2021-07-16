#include "Search_Engine.h"
#include"HashMap.h"
#include<string.h>
#include<string>
#include<fstream>
#include<conio.h>
#include<vector>
#include<iostream>
using namespace std;


Search_Engine::Search_Engine()
{
	HashMapOfTerms = new HashMap<Term_Info<Doc_Info>>();
}

void Search_Engine::UserInput_QueryWords()
{
	string input;
	cout << "Enter Query Words. \n";
	getline(cin, input, '\n');
		input.append(" ");
		tokenize_QueryWords(input);
}

void Search_Engine::tokenize_QueryWords(string input)
{
	vector<string> listQueryWords;
	string str;
	int i =0;
	bool flag=false;
	while (i<input.length())
	{
		if (input[i] == ' '&& input.length()!=1)
		{
			if (!flag)
			{
				if(str.length()!=0)
				listQueryWords.push_back(str);
			}
			str.clear();
			flag = true;
			
		}
		else if((input[i] >= 'a' &&input[i]<='z')|| (input[i] >= 'A' && input[i] <= 'Z'))
		{
			flag = false;
			str += input[i];
		}
		i++;
	}
	Search_Documents(listQueryWords);
}

int Search_Engine::GenerateHashValue(const string& keyTermName)
{
	int hashVal=0;
	for (char ch : keyTermName)
	{
		hashVal = hashVal + ch;
	}
	return hashVal;
}


void Search_Engine::Create_Index(vector<string> NameList_Docs)
{
	int i = 0;
	while (i < NameList_Docs.size())
	{
		Add_Doc_to_Index(NameList_Docs[i],i+1);
		i++;
	}
	//HashMapOfTerms->print();
}

void Search_Engine::print() const
{
	HashMapOfTerms->print();
}

void Search_Engine::Add_Doc_to_Index(const string& DocName, int id)
{
	ifstream fin(DocName);
	while (!fin.eof())
	{
		string word;
		fin >> word;
		int hashValue=GenerateHashValue(word);
		typename List<HashItem<Term_Info<Doc_Info>>>::Iterator iter=HashMapOfTerms->search(hashValue);
		if (iter == nullptr)
		{
			Term_Info<Doc_Info> term_info(word);
			term_info.insertDoc(id);
			HashMapOfTerms->insert(term_info, hashValue);
		}
		else
		{
			(*iter).getValue().insertDoc(id);
			//cout << (*iter).getValue();
		}	
	}
}

void Search_Engine::Search_Documents(vector<string> Tokenized_qWords)
{
	if (Tokenized_qWords.size() == 0)
	{
		cout << "Please Enter Some Query Words.\n";
		UserInput_QueryWords();
	}
	List<Doc_Info>* rankDocList = new List<Doc_Info>();   //delete it
	 QueryWordsAndCollectiveFreq(rankDocList, Tokenized_qWords); //Apply Rule1 And Rule2
	if (rankDocList->getNoOfNodes() == 0)
	{
		system("cls");
		cout << "\n These Kinds Of Query Words Doesn't Exist in Our Search Engine!!!\n";
		cout << "Please Make Sure that Your have Create Indexing Function Call Before Searching Query Words.\n\n";
		delete rankDocList;
		rankDocList = nullptr;
		return;
	}
	ArrangeDocListByFrequency(rankDocList);	
	ArrangeDocListByID(rankDocList);  //Apply Rule 3
	cout << endl;
	cout << "Founded KeyTerms:\n";
	print_IndexedTerms(Tokenized_qWords); //Print Indexed KeyTerms With Doc List
	printDocsList(rankDocList);            //Print Doc WIth Names
	return;
}


List<Doc_Info>::Iterator Search_Engine::find(List<Doc_Info> * listDoc, int id)
{
		List<Doc_Info>::Iterator iter = listDoc->begin();
		while (iter != listDoc->end())
		{
			if (iter->data.getDocID() == id)
			{
				return iter;
			}
			iter++;
		}
		List<Doc_Info>::Iterator temp;
		return temp;
}


void  Search_Engine::print_IndexedTerms(vector<string> querywords)
{
	for (int i = 0; i < querywords.size(); i++)
	{
		int hashVal = GenerateHashValue(querywords[i]);
		List<HashItem<Term_Info<Doc_Info>>>::Iterator iter=HashMapOfTerms->search(hashVal);
		if(iter!=nullptr)
		cout << iter->data.getValue() << endl;
	}
}



void Search_Engine::QueryWordsAndCollectiveFreq(List<Doc_Info>*& RankdocList, vector<string> queryWOrds_Token)
{
	int i = 0;
	while (i < queryWOrds_Token.size())
	{
		int hashVal = GenerateHashValue(queryWOrds_Token[i]);
		List<HashItem<Term_Info<Doc_Info>>>::Iterator iter = HashMapOfTerms->search(hashVal); //Give Here A List
		if (iter != nullptr)
		{
			List<Doc_Info>* docList = iter->data.getValue().getListOfDoc_s();
			List<Doc_Info>::Iterator iterDocList = docList->begin();
			while (iterDocList != docList->end())
			{
				List<Doc_Info>::Iterator rankDoc = find(RankdocList,iterDocList->data.DocID); //if true
				if (rankDoc == nullptr) //no found, Unique Case
				{
					RankdocList->insertAtEnd(*iterDocList);
				}
				else //rank Doc Exist 
				{
					rankDoc->data.frequency+=iterDocList->data.frequency;
				}
				iterDocList++;
			}
		}
			i++;
	}
}





void Search_Engine::ArrangeDocListByFrequency(List<Doc_Info>*& doc_List)
{
	List<Doc_Info>::Iterator iterDocList=doc_List->begin();
	while (iterDocList != doc_List->end())
	{
		Doc_Info max(*iterDocList);
		List<Doc_Info>::Iterator maxIter = iterDocList;
		for (List<Doc_Info>::Iterator  i = iterDocList;i!= doc_List->end(); i++)
		{
			if (i->data.frequency > max.frequency)
			{
				max = i->data;
				maxIter = i;
			}
		}
		swap(*iterDocList, *maxIter);
		iterDocList++;
	}
}

void Search_Engine::ArrangeDocListByID(List<Doc_Info>*& rankDocList)
{
	{
		List<Doc_Info>::Iterator start = rankDocList->begin();
		List<Doc_Info>::Iterator end = rankDocList->begin();
		int freq = end->data.frequency;
		for (; end != rankDocList->end(); end++)
		{
			if (end->data.frequency != freq)
			{
				SelectionSortByID(rankDocList, start, end);
				start = end;
			}
		}
		 SelectionSortByID(rankDocList, start, end);
	}
}

void Search_Engine::SelectionSortByID(List<Doc_Info>*& doc_List,List<Doc_Info>::Iterator start, List<Doc_Info>::Iterator end)
{
	while (start != end)
	{
		Doc_Info max(*start);
		List<Doc_Info>::Iterator maxIter = start;
		for (List<Doc_Info>::Iterator i = start; i != end; i++)
		{
			if (i->data.DocID < max.DocID)
			{
				max = i->data;
				maxIter = i;
			}
		}
		swap(*start, *maxIter);
		start++;
	}
}

void Search_Engine::printDocsList(List<Doc_Info>*& doc_List) const
{
	List<Doc_Info>::Iterator iter=doc_List->begin();
	cout << endl;
	for ( ; iter != doc_List->end() ; iter++)
	{
		iter->data.printDocID();
		cout << endl;
	}
}



Search_Engine::~Search_Engine()
{
	if (HashMapOfTerms != nullptr)
		delete HashMapOfTerms;
}
