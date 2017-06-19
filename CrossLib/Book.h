#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
enum callType_enum {
	create = 0, 
	read = 1, 
	del = 2,
	print = 3,
	exist = 4,
	not_exist =5,
	added = 6,
	deleted = 7,
	update=8,
	searchforupdate = 9,
	issueBook = 10,
	issueBookFound = 11,
	issued = 12

};

class Book {
	friend class boost::serialization::access;
public:
	callType_enum callType;
	Book()
		: bookName()
		, isbn(0)
		, auther()
		, issueStatus()
		, callType()
		
	{};
	Book(std::string const &name)
		:bookName(name)
		, isbn(0)
		, auther()
		, issueStatus()
		, callType()
		
	{};

	void setISBN(int _isbn) { isbn = _isbn; };
void setIssueStatus(int s) { issueStatus = s; };
	void setAuther(std::string _auther) { auther = _auther; };
	void setCalltype(callType_enum c_type) { callType = c_type; };
	callType_enum getCallType() const {
		return callType;
	}
	void setName(std::string name) { bookName = name; };
	std::string getName() const { return bookName; };
	int getIssueStatus() const { return issueStatus; };

	std::string getAuther() const { return auther; };
	int getISBN() const { return isbn; };
	void printBook() {
		std::cout << " ----------------------------------------------" << "\n";
		std::cout << "Book ISBN  :" << isbn << "\n";
		std::cout << "Book name:"   << bookName << "\n";
		std::cout << "Book auther:" << auther<< "\n";
		if (issueStatus) {
			std::cout << "Book Status: not available\n";
		}
		else
		{
			std::cout << "Book Status: Available  \n";
		}
		//std::cout << "Call type:"   << callType << "\n\n\n";
	}
	template <class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & isbn;
		ar & bookName;
		ar & auther;
		ar & callType;
		ar & issueStatus;
	}

protected:
	std::string bookName;
	int isbn;
	std::string auther;
	int issueStatus;
	
	
};


//std::string serializeToString(Book const &p)
//{
//	std::stringstream str;
//	boost::archive::text_oarchive oa(str);
//	oa << p;
//	return str.str();
//}

//
//int main() {
//	std::cout << "Serialization Four." << std::endl;
//
//	//Book a("Homer Simpson");
//	//Book b("Marge Simpson");
//	//b.setId(42);
//	//b.setMoney(13.37);
//	//b.setValid(false);
//
//	std::cout << "serialized a: " << serializeToString(a) << std::endl;
//	std::cout << "serialized b: " << serializeToString(b) << std::endl;
//
//	std::string serializedB = serializeToString(b);
//
//	Book c("unnamed");
//	{
//		std::stringstream str(serializedB);
//		boost::archive::text_iarchive ia(str);
//		ia >> c;
//	}
//
//	std::cout << "name of c: " << c.getName() << std::endl;
//	std::cout << "id of c: " << c.getId() << std::endl;
//	std::cout << "money of c: " << c.getMoney() << std::endl;
//	std::cout << "serialized c: " << serializeToString(c) << std::endl;
//
//	return 0;
//}
