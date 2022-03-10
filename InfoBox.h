#pragma once
#include <vector>
#include <string>
using namespace std;

class InfoBox
{

private:
	int score;
	vector<string> message;
	int health = 3;

public:
	int getScore() const;
	void setScore(int a);
	//vector<string> getMessage();
	void setMessage(string a, string b);

	virtual void printInfo();

};

