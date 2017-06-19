#pragma warning(disable:4996) 
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
#include "Service.h"


using boost::asio::ip::tcp;

//----------------------------------------------------------------------

typedef std::deque<Msg> chat_message_queue;

//----------------------------------------------------------------------
struct S
{
	int a;/*
	std::string b;*/
	// etc.
};

class chat_participant
{
public:
	virtual ~chat_participant() {}
	virtual void deliver(const Msg& msg) = 0;
};

typedef boost::shared_ptr<chat_participant> chat_participant_ptr;

//----------------------------------------------------------------------

class chat_room
{
public:
	void join(chat_participant_ptr participant)
	{
		participants_.insert(participant);
		std::for_each(recent_msgs_.begin(), recent_msgs_.end(),
			boost::bind(&chat_participant::deliver, participant, _1));
	}

	void leave(chat_participant_ptr participant)
	{
		participants_.erase(participant);
	}

	void deliver(const Msg& msg)
	{
		recent_msgs_.push_back(msg);
		while (recent_msgs_.size() > max_recent_msgs)
			recent_msgs_.pop_front();

		std::for_each(participants_.begin(), participants_.end(),
			boost::bind(&chat_participant::deliver, _1, boost::ref(msg)));
	}

private:
	std::set<chat_participant_ptr> participants_;
	enum { max_recent_msgs = 100 };
	chat_message_queue recent_msgs_;
};

//----------------------------------------------------------------------

class chat_session
	: public chat_participant,
	public boost::enable_shared_from_this<chat_session>
{
public:
	chat_session(boost::asio::io_service& io_service, chat_room& room)
		: socket_(io_service),
		room_(room), service()
	{
	}

	tcp::socket& socket()
	{
		return socket_;
	}
	
	void start()
	{
		room_.join(shared_from_this());
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), Msg::header_length),
			boost::bind(
				&chat_session::handle_read_header, shared_from_this(),
				boost::asio::placeholders::error));
	}
	char* subString(const char *s, int index, int n) {
		char *res = new char[n + 1];
		sprintf(res, "%.*s", n, s + index);
		return res;
	}
	void deliver(const Msg& msg)
	{
		Book c("unnamed");
		User u("unnamed");
		BookUser bu(0);
		//BookUserDB bu("unnamed");
		int bookIndex = -1;
		Msg msg2;
		Book b2;
		User u2;
		BookUser bu2;
		//BookUserDB bu2;
		/*S *tmp_pckt = (S *)msg.body()[0];
		std::cout << tmp_pckt-> << "\n";*/
		//std::cout << msg. << "\n";
		//msg.body();
		std::cout << msg.body()[0] << "\n";
		char messageType = msg.body()[0];
		bool iterate = false;
		int size = strlen(msg.body());
		char otherString[3072];
		char* body = subString(msg.body(), 1, size);
		switch (messageType)
		{
		case 'b'://Book
			std::cout << "Book call\n";
			{
				std::stringstream str(body);// msg.body());
				boost::archive::text_iarchive ia(str);
				ia >> c;
			}
			c.printBook();
			switch (c.getCallType()) {
			
			case create:
				//bookVector.push_back(c);
				service.AddBook(c);
				b2.setCalltype(added);
				b2.setName("book added");
				break;
			case read:
				std::cout << "\n-----------------------------------";
				std::cout << "\n Search\n";
				bookIndex = service.searchBookByName(c.getName());
				if (bookIndex == -1) {
					std::cout << "not found\n";
					b2.setName("not found");
					b2.setCalltype(not_exist);

				}
				else
				{
					std::cout << "\n found\n";

					b2.setName(service.bookVector.at(bookIndex).getName());
					b2.setISBN(service.bookVector.at(bookIndex).getISBN());
					b2.setAuther(service.bookVector.at(bookIndex).getAuther());
					b2.setCalltype(exist);
				}
				break;
			case issueBook:
				std::cout << "\n-----------------------------------";
				std::cout << "\n Search\n";
				bookIndex = service.searchBookByName(c.getName());
				if (bookIndex == -1) {
					std::cout << "not found\n";
					b2.setName("not found");
					b2.setCalltype(not_exist);

				}
				else
				{
					std::cout << "\n found\n";

					b2.setName(service.bookVector.at(bookIndex).getName());
					b2.setISBN(service.bookVector.at(bookIndex).getISBN());
					b2.setAuther(service.bookVector.at(bookIndex).getAuther());
					b2.setCalltype(issueBookFound);
				}
				break;
			case print:
				std::cout << "\n-----------------------------------";
				std::cout << "\n Printing all books\n";
				for (Book b : service.bookVector) {
					b.printBook();
				}
				std::cout << "Total\n" << service.bookVector.size() << " of books are there\n";
				iterate = true;
				break;

			case del:
				std::cout << "\n-----------------------------------";
				bookIndex = service.deleteBook(c.getISBN());
				if (bookIndex == -1) {
					std::cout << "not Delete\n";
					b2.setName("not Delete");
					b2.setCalltype(not_exist);

				}
				else
				{
					std::cout << "\n Delete\n";
					b2.setName("Deleted");
					b2.setCalltype(deleted);
				}
				break;

			case searchforupdate:
				std::cout << "\n-----------------------------------";
				bookIndex = service.searchBookByName(c.getName());
				if (bookIndex == -1) {
					std::cout << "not found\n";
					b2.setName("not found");
					b2.setCalltype(not_exist);
				}
				else
				{
					std::cout << "\n found\n";

					b2.setName(service.bookVector.at(bookIndex).getName());
					b2.setISBN(service.bookVector.at(bookIndex).getISBN());
					b2.setAuther(service.bookVector.at(bookIndex).getAuther());
					b2.setCalltype(exist);
				}

			case update:
				bookIndex = service.updatebook(c);
				std::cout << "index " << bookIndex << " \n";
				if (bookIndex == -1) {
					std::cout << "updated\n";
				}
				else
				{
					std::cout << "not updated\n";
				}
				break;
			default:
				std::cout << "no option\n";
				break;
			}

			if (iterate) {
				int st = 0;
				for (Book b : service.bookVector) {
					st = b.getIssueStatus();
					b.setCalltype(print);
					send(b, msg2);
				}
			}
			send(b2, msg2);
			break;

		case 'u': //user
			std::cout << "User call\n";
			{
				std::stringstream str(body);// msg.body());
				boost::archive::text_iarchive ia(str);
				ia >> u;
			}
			u.printUser();

			switch (u.getCallType()) {
			case create:
				service.userVector.push_back(u);
				u2.setCalltype(added);
				u2.setUserName("user added");
				break;

			default:

				break;
			}
			break;

		case 'i':
			std::cout << "Issue Book call\n";
			{
				std::stringstream str(body);// msg.body());
				boost::archive::text_iarchive ia(str);
				ia >> bu;
			}
			//c.printBook();
			switch (bu.getCallType()) {
			case create:
				service.bookUserVector.push_back(bu);
				service.issue_Book(bu.getUserID(), bu.getBookID());
				b2.setCalltype(issued);
				b2.setName("book issued");
				break;
			case read:
				std::cout << "\n-----------------------------------";
				std::cout << "\n Search\n";
				bookIndex = service.searchBookByISBN(bu.getBookID());
				if (bookIndex == -1) {
					std::cout << "not found\n";
					//bu2.setName("not found");
					bu2.setCalltype(not_exist);

				}
				else
				{
					std::cout << "\n found\n";

					bu2.setBookID(service.bookVector.at(bookIndex).getISBN());
					//b2.setISBN(bookVector.at(bookIndex).getISBN());
					//b2.setAuther(bookVector.at(bookIndex).getAuther());
					bu2.setCalltype(issueBookFound);
				}
			}
			send(b2, msg2);
			break;
		default:
			break;
		}
		
		
	}
	std::string serializeToString(Book const &p)
	{
		std::stringstream str;
		{
			boost::archive::text_oarchive oa(str);
			oa << p;
		}
		return str.str();
	}
	std::string serializeUserToString(User const &p)
	{
		std::stringstream str;
		{
			boost::archive::text_oarchive oa(str);
			oa << p;
		}
		return str.str();
	}
	void send(Book b2, Msg msg2) {


		std::string serializedBook = serializeToString(b2);
		char bookBody[3072];
		strncpy(bookBody, serializedBook.c_str(), sizeof(bookBody));
		bookBody[sizeof(bookBody) - 1] = 0;
		msg2.body_length(strlen(bookBody));
		memcpy(msg2.body(), bookBody, msg2.body_length());
		msg2.encode_header();
		//b2.write(msg2);
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg2);
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()),
				boost::bind(&chat_session::handle_write, shared_from_this(),
					boost::asio::placeholders::error));
		}
	}
	void handle_read_header(const boost::system::error_code& error)
	{
		if (!error && read_msg_.decode_header())
		{
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				boost::bind(&chat_session::handle_read_body, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}

	void handle_read_body(const boost::system::error_code& error)
	{
		if (!error)
		{
			room_.deliver(read_msg_);
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), Msg::header_length),
				boost::bind(&chat_session::handle_read_header, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}

	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			write_msgs_.pop_front();
			if (!write_msgs_.empty())
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().data(),
						write_msgs_.front().length()),
					boost::bind(&chat_session::handle_write, shared_from_this(),
						boost::asio::placeholders::error));
			}
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}

private:
	tcp::socket socket_;
	chat_room& room_;
	Msg read_msg_;
	chat_message_queue write_msgs_;
	Service service;
};

//typedef boost::shared_ptr<chat_session> chat_session_ptr;

//----------------------------------------------------------------------

class chat_server
{
public:
	chat_server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint):
				io_service_(io_service), acceptor_(io_service, endpoint)
	{
		start_accept();
	}

	/*
	 This method will be called on server creation 
	*/
	void start_accept()
	{
		boost::shared_ptr<chat_session> socketservice(new chat_session(io_service_, room_));
		//Start an asynchronous accept
		acceptor_.async_accept(
								//Socket Service
								socketservice->socket(),
								//Accept Handler
								boost::bind(&chat_server::handle_accept, this, socketservice,	boost::asio::placeholders::error)
							  );
	}

	void handle_accept(boost::shared_ptr<chat_session> socketservice,	const boost::system::error_code& error)
	{
		if (!error)
		{
			socketservice->start();
		}

		start_accept();
	}

private:
	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
	chat_room room_;
};

typedef boost::shared_ptr<chat_server> chat_server_ptr;

///typedef std::list<chat_server_ptr> chat_server_list;

//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 2)
		{
			std::cerr << "Usage: server <port> [<port> ...]\n";
			std::cin.get();
			return 1;
		}

		boost::asio::io_service io_service;
		int server_port = atoi(argv[1]);
		using namespace std; // For atoi.
		tcp::endpoint endpoint(tcp::v4(), server_port);
		chat_server_ptr server(new chat_server(io_service, endpoint));
		std::cout << "Server started successfully  at port " << server_port << endl;
		io_service.run();
		
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}