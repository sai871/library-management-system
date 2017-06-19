
#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include "Book.h"
#include "User.h"

#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include "Book.h"
class BookUser {
	friend class boost::serialization::access;
public:
	callType_enum callType;
	BookUser()
		: userId()
		, DOI()
		, callType()
		, bookID()
	{};
	BookUser(int id)
		: userId()
		, DOI()
		, callType()
		, bookID()
	{};
	

	void setUserId(int id) { userId = id; };
	void setCalltype(callType_enum c_type) { callType = c_type; };
	void setDOI(std::string DOI) { DOI = DOI; };
	//void setCalltype(callType_enum c_type) { callType = c_type; };
	callType_enum getCallType() const {
		return callType;
	}
	void setUserId(std::string userId) { userId = userId; };
	int getUserID() const { return userId; };
	void setBookID(int bId) { bookID = bId; };
	int getBookID() const { return bookID; };
	std::string getDOI()const { return DOI; }
	template <class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & userId;
		ar & DOI;
		ar & bookID;
		ar & callType;
	}

protected:
	int userId;
	std::string DOI;
	int bookID;
};