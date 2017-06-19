#pragma once
#include <iostream>
#include<vector>
#include "stdafx.h"
#include <string>
#include <tuple>
class first
{
public:
	first();
	~first();
	std::vector<int>bisbn;
	std::vector<std::string>bname;
	std::vector<std::string>aname;
	std::vector<int>idate;
	std::vector<std::string>sname;
	std::vector<int>uid;
	std::vector<int>ucno;
	std::vector<int>bbisbn;
	std::vector<int>bdate;
	std::vector<int>ddate;
	std::vector<int>sbbooks;
	std::vector<int>bidate;
	std::tuple<int,std::string,std::string,int> addbookdetails(int ais,std::string abn,std::string aan,int aid);
	int issuebook();
	std::tuple<int,std::string, int,int> editbookdetails(int val,std::string change,int id,int i);
	std::tuple<int,int>searchbook(int);
	int deletebook();
	int showbooks();
	std::tuple<int,std::string,int>adduser(int ui,std::string un,int cno);
	std::tuple<int, int>searchuser(int ui);
	std::tuple<int,std::string,int>edituser(int t,int c,std::string un,int cno);
	int showusers();
	int viewbbooks();
};

