#include "Doc_Info.h"






int Doc_Info::getDocID() const
{
	return DocID;
}

int Doc_Info::getFrequency() const
{
	return frequency;
}

bool Doc_Info::checkDocID(int id)
{
	return DocID==id;
}

void Doc_Info::incrementFrequencyByOne()
{
	frequency++;
}

bool Doc_Info::operator==(const Doc_Info& obj)
{
	if (DocID == obj.DocID && frequency == obj.frequency)
		return true;
	return false;
}

void Doc_Info::printDocID() const
{
	cout << "Doc" << DocID;
}







Doc_Info::Doc_Info()
{
	DocID = -1;
	frequency = -1;

}

Doc_Info::Doc_Info(int doc_id, int frequency)
	:DocID(doc_id),frequency(frequency)
{
}

Doc_Info::Doc_Info(const Doc_Info& obj)
{
	this->DocID = obj.DocID;
	this->frequency = obj.frequency;
}

Doc_Info::~Doc_Info()
{
	//destructor
}

ostream& operator<<(ostream& _cout, const Doc_Info& obj)
{
	_cout << "ID=" << obj.DocID<<",Freq="<<obj.frequency;
	return _cout;
	// TODO: insert return statement here
}
