#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include "Book.h"
class User {
	friend class boost::serialization::access;
public:
	callType_enum callType;
	User()
		: userName()
		, userId(0)
		, callType()
		,password()
	{};
	User(std::string const &name)
		:userName(name)
		, userId(0)
		, callType()
		, password()
	{};

	void setUserId(int id) { userId= id; };
	void setUserName(std::string _userName) { userName = _userName; };
	void setCalltype(callType_enum c_type) { callType = c_type; };
	callType_enum getCallType() const {
		return callType;
	}
	void setPassword(std::string pass) { password = pass; };
	std::string getUserName() const { return userName; };
	std::string getPassword() const { return password; };
	int getId() const { return userId; };
	void printUser() {
		std::cout << " ----------------------------------------------" << "\n";
		std::cout << "User Id  :" << userId << "\n";
		std::cout << "User user name:" << userName<< "\n";
		std::cout << "Call type:" << callType << "\n\n\n";
	}
	template <class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & userId;
		ar & userName;
		ar & password;
		ar & callType;
	}

protected:
	std::string userName;
	int userId;
	std::string password;
};