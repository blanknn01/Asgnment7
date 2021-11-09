#pragma once
#include<iostream>
#include<fstream>
#include <string>
#include <algorithm>
using namespace std;
class Text_Preprocessor
{
private:
	ifstream obj;
public:
	Text_Preprocessor(string const& openfile);
	virtual ~Text_Preprocessor();
	void preprocess_text();
	int search_word(const string& word);

};

