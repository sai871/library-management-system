#pragma once
//
// msg.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MSG_HPP
#define MSG_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
//struct S
//{
//	int a;
//	std::string b;
//	// etc.
//};
enum MessageType {
	book = 1,
	user =2
};
class Msg
{
public:
	char s;
	//MessageType  messageType;
	enum { header_length = 4 };
	enum { max_body_length = 512 };
	

	Msg()
		: body_length_(0), s('s')
	{
	}

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}
	void setMessageType(MessageType mt) {
		//messageType = mt;
	}
	size_t length() const
	{
		return header_length + body_length_;
	}

	const char* body() const
	{
		return data_ + header_length;
	}

	char* body()
	{
		return data_ + header_length;
	}

	size_t body_length() const
	{
		return body_length_;
	}

	void body_length(size_t new_length)
	{
		body_length_ = new_length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}

	bool decode_header()
	{
		using namespace std; // For strncat and atoi.
		char header[header_length + 1] = "";
		strncat_s(header, data_, header_length);
		body_length_ = atoi(header);
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		
		
		return true;
	}
	void SetStructure(int s1)
	{
		this->s = s1;
	}

	void encode_header()
	{
		using namespace std; // For sprintf and memcpy.
		//messageType = book;
		char header[header_length + 1] = "";
		sprintf_s(header, "%4d", body_length_);
		memcpy(data_, header, header_length);
	}
	

private:
	char data_[header_length + max_body_length];
	size_t body_length_;
	size_t test;
	

};

#endif // CHAT_MESSAGE_HPP