#pragma once
#include <vector>
#include <string>
using namespace std;

class InfoBox
{

private:
	int score;
	vector<string> message;

public:
	int getScore() const;
	void setScore(int a);
	//vector<string> getMessage();
	void setMessage(string a);

	virtual void printInfo();

};

