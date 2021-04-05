#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct account
{
	string password;
	int id;
	
};
string password(int a, ifstream& in)
{
	int n;
	account x;
	in >> n;
	for (int i = 1; i <= n; i++)
	{
		in >> x.id;
		in >> x.password;
		if (x.id == a)
		{
			return x.password;
		}
	}
	return "can not find";
}

void changePassword(account a,string oldPass,string  newPass,ifstream& in) {
	ofstream out;
	int m;
	in.open("Text.txt");
	if (in) {
		in >> m;
		out.open("output.txt");
		out << m << endl;
		for(int i=1;i<=m;i++) {
			in >> a.id;
			in >> a.password;
			if (a.password==oldPass) {
				a.password.replace(a.password.find(oldPass), a.password.find(oldPass)+a.password.size(), newPass);
			}
			out << a.id << " " << a.password;
			out << endl;
		}
		out.close();
		in.close();
				remove ("Text.txt");
				rename("output.txt", "Text.txt");
	}
}
