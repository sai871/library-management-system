#include "stdafx.h"
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "Book.h"
#include "User.h"
#include "message.h"
#include "BookUser.h"
#define _ITERATOR_DEBUG_LEVEL 2 

class Service {
	
	
public:
	int deleteBook(int isbn) {
		int deleted = -1;
		int bookIndex = searchBookByISBN(isbn);
		if (bookIndex != -1) {
			bookVector.erase(bookVector.begin() + bookIndex);
			deleted = bookIndex;
		}


		return deleted;
	}
	int searchBookByName(std::string query) {
		int index = -1;
		std::vector<Book>::iterator it;
		int i = 0;
		for (it = bookVector.begin(); it < bookVector.end(); it++, i++) {
			// found nth element..print and break.
			std::string val1 = it->getName();
			if (strstr(val1.c_str(), query.c_str())) {
				std::cout << "found!!";
				index = i;
				break;
			}
		}
		return index;

	}
	int searchBookByISBN(int isbn) {
		int index = -1;
		std::vector<Book>::iterator it;
		int i = 0;
		for (it = bookVector.begin(); it < bookVector.end(); it++, i++) {
			// found nth element..print and break.
			int val1 = it->getISBN();
			if (val1 == isbn) {
				std::cout << "found!!";
				index = i;
				break;
			}
		}
		return index;

	}
	int updatebook(Book b) {
		int result = -1;
		std::vector<Book>::iterator it;
		int i = 0;
		for (it = bookVector.begin(); it < bookVector.end(); it++, i++) {
			// found nth element..print and break.
			int val1 = it->getISBN();
			if (val1 == b.getISBN()) {
				it->setName(b.getName());
				result = i;
				break;
			}
		}
		return result;
	}
	void issue_Book(int userId, int bookId) {
		//int result = -1;
		std::vector<Book>::iterator it;
		int i = 0;
		for (it = bookVector.begin(); it < bookVector.end(); it++, i++) {
			// found nth element..print and break.
			int val1 = it->getISBN();
			if (val1 == bookId) {
				it->setIssueStatus(1);
				//result = i;
				break;
			}
		}

	}
	void AddBook(Book b) {
		bookVector.push_back(b);
	}
	
	char* subString(const char *s, int index, int n) {
		char *res = new char[n + 1];
		sprintf(res, "%.*s", n, s + index);
		return res;
	}
//private:
	std::vector<Book> bookVector = {};
	std::vector<User> userVector = {};
	std::vector<BookUser> bookUserVector = {};
};
