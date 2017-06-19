#include "stdafx.h"
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "message.h"
#include "Book.h"
//#include <unistd.h>
#include <chrono>
#include <thread>
#include "User.h"
#include "BookUser.h"

using boost::asio::ip::tcp;
Book forUpdate;
BookUser bookUserForUpdate;
bool updateFlag = false;
bool issueFlag = false;
typedef std::deque<Msg> chat_message_queue;
int  menuDisplay();
class chat_client
{
public:
	chat_client(boost::asio::io_service& io_service,
		tcp::resolver::iterator endpoint_iterator)
		: io_service_(io_service),
		socket_(io_service)
	{
		boost::asio::async_connect(socket_, endpoint_iterator,
			boost::bind(&chat_client::handle_connect, this,
				boost::asio::placeholders::error));
	}

	void write(const Msg& msg)
	{
		io_service_.post(boost::bind(&chat_client::do_write, this, msg));
	}

	void close()
	{
		io_service_.post(boost::bind(&chat_client::do_close, this));
	}

private:

	void handle_connect(const boost::system::error_code& error)
	{
		if (!error)
		{
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), Msg::header_length),
				boost::bind(&chat_client::handle_read_header, this,
					boost::asio::placeholders::error));
		}
	}

	void handle_read_header(const boost::system::error_code& error)
	{
		if (!error && read_msg_.decode_header())
		{
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				boost::bind(&chat_client::handle_read_body, this,
					boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void handle_read_body(const boost::system::error_code& error)
	{
		try {
			if (!error)
			{


				//std::cout << "\nClient received\n";
				{
					Book c("unnamed");
					{
						std::stringstream str(read_msg_.body());
						boost::archive::text_iarchive ia(str);
						ia >> c;
					}
					
					switch (c.getCallType())
					{
					case added:
						std::cout <<c.getName() << "  book added successfully \n";
						break;
					case exist:
						updateFlag = true;
						std::cout << " book found reply \n";
						c.printBook();
						forUpdate = c;
						break;

					case issueBookFound:
						issueFlag = true;
						std::cout << " book issue reply \n";
						//c.printBook();
						forUpdate = c;
						break;
					case print:
						c.printBook();
						break;
					case deleted:
						std::cout << " book deleted \n";
						break;
					case issued:
						std::cout << " book issued \n";
						break;
					default:
						break;
					}
				}
				//std::cout.write(read_msg_.body(), read_msg_.body_length());
				//std::cout << "\n";
				boost::asio::async_read(socket_,
					boost::asio::buffer(read_msg_.data(), Msg::header_length),
					boost::bind(&chat_client::handle_read_header, this,
						boost::asio::placeholders::error));
			}
			else
			{
				do_close();
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}
	}

	void do_write(Msg msg)
	{
		//std::cout << msg.body();
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress)
		{
			///boost::asio::async_write(socket_, boost::asio::buffer(msg.data, msg.data.length()), handler);
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()),
				boost::bind(&chat_client::handle_write, this,
					boost::asio::placeholders::error));
		}
	}
	void my_habler() {

	}
	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			write_msgs_.pop_front();
			if (!write_msgs_.empty())
			{
				/*
				boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().data(),
						write_msgs_.front().length()),
					boost::bind(&chat_client::handle_write, this,
						boost::asio::placeholders::error));
						*/
			}
		}
		else
		{
			do_close();
		}
	}

	void do_close()
	{
		socket_.close();
	}

private:
	boost::asio::io_service& io_service_;
	tcp::socket socket_;
	Msg read_msg_;
	chat_message_queue write_msgs_;
};
 struct S
{
	int a;
	//std::string b;
	// etc.
};
 int  mainMenuDisplay() {
	 int option;
	 std::cout << "*******************Select Option*******************\n";
	 std::cout << "1 - Admin\n";
	 std::cout << "2 - Normal user\n";
	 std::cout << "0 - Exit\n";
	 std::cout << "\n\n\n*****Please Select any option*****\n";
	 std::cin >> option;
	 //system("cls");

	 return option;

 }

int  menuDisplay() {
//	usleep(3000);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	if (updateFlag) {
		//std::cout << "update\n";
		//forUpdate.printBook();
		updateFlag = false;
		return 9;
	}
	else if (issueFlag)
	{
		issueFlag = false;
		return 10;
	}
	int option;
	std::cout << "*******************Select Option*******************\n";
	std::cout << "1 - Add A new book to a Library\n";
	std::cout << "2 - Search for books\n";
	std::cout << "3 - delete book\n";
	std::cout << "4 - Print all\n";
	std::cout << "5 - Update book\n";
	std::cout << "6 - Show borrowed Books\n";
	std::cout << "7 - Add User\n";
	std::cout << "8 - Issue book to user\n";
	
	std::cout << "0 - Exit\n";
	std::cout << "\n\n\n*****Please Select any option*****\n";
	std::cin >> option;
	system("cls");

	 return option;

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
std::string serializeBookUserToString(BookUser const &p)
{
	std::stringstream str;
	{
		boost::archive::text_oarchive oa(str);
		oa << p;
	}
	return str.str();
}

int main(int argc, char* argv[])
{
	try
	{
		
		if (argc != 3)
		{
			std::cerr << "Usage: client <server IP> <port>\n";
			return 1;
		}
		
		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(argv[1], argv[2]);
		tcp::resolver::iterator iterator = resolver.resolve(query);

		chat_client c(io_service, iterator);

		boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

		char line[Msg::max_body_length + 1];
		int option = menuDisplay();
		char messagetype = 'b';
		std::string name;
		int isbn;
		int id = 0;

		while (option != 0 )//std::cin.getline(line, msg::max_body_length + 1))
		{
			messagetype = 'b';
			
			updateFlag = false;
			Book b("empty");
			User u("empty");
			BookUser bu(1);
	
			using namespace std; // For strlen and memcpy.
			Msg msg;
			//===========================================================//
			switch (option)
			{
			case 0:
				exit(0);
				break;

			case 1: //Add new book
				std::cout << "Book name: ";
				std::cin >> name;
				b.setName(name);
				std::cout << "Book Id: ";
				cin >> id;
				b.setISBN(id);
				b.setCalltype(create);
				break;
			case 2: //Search for book
				std::cout << " option 2" << endl;
				std::cout << "please enter any part of your book name: ";
				cin >> name;
				b.setName(name);
				b.setCalltype(read);
				break;

			case 3: //Search for book
				std::cout << " option 3" << endl;
				std::cout << "please enter ISBN of your book: ";
				cin >> isbn;
				b.setISBN(isbn);
				b.setCalltype(del);
				break;


			case 4: //Search for book
				std::cout << " option 4" << endl;
				b.setCalltype(print);
				break;
			case 5: //update book
				updateFlag = true;
				std::cout << " option 5" << endl;
				b.setCalltype(searchforupdate);
				std::cout << "please enter your book name to modify: ";
				cin >> name;
				b.setName(name);
				if (updateFlag) {
					std::cout << " book found \n";
				}
				else
				{
					std::cout << " book not found \n";
				}
				break;


			case 7: //add user
				messagetype = 'u';
				std::cout << "please enter user name: ";
				cin >> name;
				u.setUserName(name);
				std::cout << "please enter user id: ";
				cin >> isbn;
				u.setUserId(isbn);
				u.setCalltype(create);
				break;
			case 8: //issue book
				issueFlag = true;
				std::cout << " option 8" << endl;
				b.setCalltype(issueBook);
				std::cout << "please enter your book name to issue: ";
				cin >> name;
				b.setName(name);
				if (updateFlag) {
					//std::cout << " book found \n";
				}
				else
				{
					//std::cout << " book not found \n";
				}

				
				
				
				break;

			case 9: 
				std::cout << "please enter book name: ";
				cin >> name;
				b.setName(name);
				b.setISBN(forUpdate.getISBN());
				b.setCalltype(update);
				break;
			case 10:
				
				std::cout << "please enter user id: ";
				cin >> isbn;
				bu.setBookID(forUpdate.getISBN());
				bu.setUserId(isbn);
				bu.setCalltype(create);
				messagetype = 'i';
				break;
			default:
				std::cout << " no suitable option";
				break;
			}

			/*b.setName(name);
			b.setISBN(id);
			b.setAuther("auther");*/
			std::string serializedBook;
			char bookBody[3072];
			switch (messagetype)
			{
			case 'b':
				serializedBook = serializeToString(b);
				strcpy(bookBody, "b");
				break;
			case 'u':
				serializedBook = serializeUserToString(u);
				strcpy(bookBody, "u");
				break;
			case 'i':
				serializedBook = serializeBookUserToString(bu);
				strcpy(bookBody, "i");
				break;
			default:
				break;
			}
			
			//std::string prefix("s");
			//serializedBook = prefix + serializedBook;
			
			
			strcat(bookBody, serializedBook.c_str());// , sizeof(bookBody));
			bookBody[sizeof(bookBody) - 1] = 0;
			//===========================================================//
			
			
			msg.body_length(strlen(bookBody));
			memcpy(msg.body(), bookBody, msg.body_length());
			msg.encode_header();
			
			c.write(msg);

			option = menuDisplay();
		}

		c.close();
		t.join();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}