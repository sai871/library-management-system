// testing.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "Book.h"
#include "iostream"
#include"User.h"
#include"BookUser.h"
#include"Service.h"
#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
using namespace std;
BOOST_AUTO_TEST_SUITE(TestcasesForBookSetters)
BOOST_AUTO_TEST_CASE(bookisbnp)
{
	Book b("empty");
	b.setISBN(1);
	BOOST_TEST_MESSAGE("test passsed");
	
	BOOST_CHECK(b.getISBN() == 1);
	
	//BOOST_CHECK_MESSAGE(b.getISBN() != 1,"isbn "<<b.getISBN()<<"check passed");
}
BOOST_AUTO_TEST_CASE(bookanamep)
{
	BOOST_TEST_MESSAGE("test passsed");
	Book b("empty");
	std::string x = "name";
	b.setAuther(x);
	std::cout<<""<<std::endl;
	BOOST_CHECK(b.getAuther() == "name");
}
BOOST_AUTO_TEST_CASE(bookbnamep)
{
	BOOST_TEST_MESSAGE("test passsed");
	Book b("empty");
	std::string x = "name";
	b.setName(x);
	BOOST_CHECK(b.getName() == "name");
}
BOOST_AUTO_TEST_CASE(bookstatusp)
{
	Book b("empty");

	b.setIssueStatus(1);
	BOOST_CHECK(b.getIssueStatus() == 1);
}
BOOST_AUTO_TEST_CASE(usernamep)
{
	User b("empty");

	b.setUserName("name");
	BOOST_CHECK(b.getUserName() == "name");
}
BOOST_AUTO_TEST_CASE(useridp)
{
	User b("empty");

	b.setUserId(1);
	BOOST_CHECK(b.getId() == 1);
}
BOOST_AUTO_TEST_CASE(userpasswordp)
{
	User b("empty");

	b.setPassword("name");
	BOOST_CHECK(b.getPassword() == "name");
}


BOOST_AUTO_TEST_CASE(userborroweduidp)
{
	BookUser b(1);

	b.setUserId(1);
	BOOST_CHECK(b.getUserID() == 1);
}
/*
BOOST_AUTO_TEST_CASE(userborroweddoip)
{
	
	BookUser b(1);
	b.setDOI("name");
	BOOST_CHECK(b.getDOI() == "name");
}
*/
BOOST_AUTO_TEST_CASE(userborrowedbidp)
{
	BookUser b(1);

	b.setBookID(1);
	BOOST_CHECK(b.getBookID() == 1);
}

BOOST_AUTO_TEST_CASE(bookisbnf)
{
	Book b("empty");
	b.setISBN(1);
	BOOST_CHECK(b.getISBN() != 0);
}
BOOST_AUTO_TEST_CASE(bookanamef)
{
	Book b("empty");
	std::string x = "name";
	b.setAuther(x);
	BOOST_CHECK(b.getAuther() != "nam");
}
BOOST_AUTO_TEST_CASE(bookbnamef)
{
	Book b("empty");
	std::string x = "name";
	b.setName(x);
	BOOST_CHECK(b.getName() != "nam");
}
BOOST_AUTO_TEST_CASE(bookstatusf)
{
	Book b("empty");

	b.setIssueStatus(1);
	BOOST_CHECK(b.getIssueStatus() != 0);
}
BOOST_AUTO_TEST_CASE(usernamef)
{
	User b("empty");

	b.setUserName("name");
	BOOST_CHECK(b.getUserName() != "nam");
}
BOOST_AUTO_TEST_CASE(useridf)
{
	User b("empty");

	b.setUserId(1);
	BOOST_CHECK(b.getId() != 0);
}
BOOST_AUTO_TEST_CASE(userpasswordf)
{
	User b("empty");

	b.setPassword("name");
	BOOST_CHECK(b.getPassword() != "nam");
}


BOOST_AUTO_TEST_CASE(userborroweduidf)
{
	BookUser b(1);

	b.setUserId(1);
	BOOST_CHECK(b.getUserID() != 0);
}
BOOST_AUTO_TEST_CASE(userborroweddoif)
{

	BookUser b(1);
	b.setDOI("name");
	BOOST_CHECK(b.getDOI() != "nam");
}
BOOST_AUTO_TEST_CASE(userborrowedbidf)
{
	BookUser b(1);

	b.setBookID(1);
	BOOST_CHECK(b.getBookID() != 0);
}

BOOST_AUTO_TEST_CASE(servicesearchbookISBNp)
{

	Service s;
	int x = s.searchBookByISBN(1);

	BOOST_CHECK(x == -1);
	std::cout << std::endl << "Book search test case Pass" << std::endl;
}
BOOST_AUTO_TEST_CASE(serviceAddbookp)
{
	Book b;
	Service s;
	b.setISBN(1);
	b.setName("cplusplus");
	b.setAuther("saikumar");
	s.AddBook(b);
	int x = s.searchBookByISBN(1);
	BOOST_CHECK(x == 0);
	std::cout << std::endl << "Book added test case Pass" << std::endl;
}
BOOST_AUTO_TEST_CASE(servicedeletebookp)
{
	Book b;
	Service s;
	b.setISBN(1);
	b.setName("cplusplus");
	b.setAuther("saikumar");
	s.AddBook(b);
	int x=s.searchBookByISBN(1);
	x = s.deleteBook(1);
	BOOST_CHECK(x == 0);
	std::cout << std::endl << "Book delete test case Pass" << std::endl;
}

BOOST_AUTO_TEST_CASE(serviceupdatebookp)
{
	Book b;
	Service s;
	b.setISBN(1);
	b.setName("cplusplus");
	b.setAuther("saikumar");
	s.AddBook(b);
	b.setName("sai");
	b.setISBN(1);
	int x=s.updatebook(b);
	BOOST_CHECK(x == 0);
	std::cout << std::endl << "Book update test case Pass" << std::endl;
}

BOOST_AUTO_TEST_CASE(serviceissuebookp)
{

	Book b;
	Service s;
	b.setISBN(1);
	b.setName("cplusplus");
	b.setAuther("saikumar");
	s.AddBook(b);
	s.issue_Book(1, 1);
	int x = b.getIssueStatus();
	BOOST_CHECK(x == 0);
	std::cout << std::endl << "Book Issued test case Pass" << std::endl;
}



BOOST_AUTO_TEST_CASE(servicesearchbookISBNf)
{

	Service s;
	int x = s.searchBookByISBN(1);

	BOOST_CHECK(x != 1);
	std::cout << std::endl<<"Book search test case fail" << std::endl;


}
BOOST_AUTO_TEST_CASE(serviceAddbookf)
{
	Book b;
	Service s;
	b.setISBN(1);
	b.setName("cplusplus");
	b.setAuther("saikumar");
	s.AddBook(b);

	int x = s.searchBookByISBN(1);
	BOOST_CHECK(x != -1);
	std::cout << std::endl<<"Book add test case fail" << std::endl;

}
BOOST_AUTO_TEST_CASE(servicedeletebookf)
{
	Book b;
	Service s;
	b.setISBN(1);
	b.setName("cplusplus");
	b.setAuther("saikumar");
	s.AddBook(b);
	int x = s.searchBookByISBN(1);
	x = s.deleteBook(1);
	BOOST_CHECK(x != 1);
	std::cout << std::endl << "Book delete test case fail" << std::endl;

}

BOOST_AUTO_TEST_CASE(serviceupdatebookf)
{
	Book b;
	Service s;
	b.setISBN(1);
	b.setName("cplusplus");
	b.setAuther("saikumar");
	s.AddBook(b);
	b.setName("sai");
	b.setISBN(1);
	int x = s.updatebook(b);
	BOOST_CHECK(x != 1);
	std::cout << std::endl << "Book update test case fail" << std::endl;

}
/*
BOOST_AUTO_TEST_CASE(serviceissuebookf)
{
	Book b;
	Service s;
	s.issue_Book(1, 1);
	int x = b.getIssueStatus();
	BOOST_CHECK(x != 0);
}
*/
BOOST_AUTO_TEST_SUITE_END()