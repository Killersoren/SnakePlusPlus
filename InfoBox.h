#pragma once
#include <vector>
#include <string>
using namespace std;

class InfoBox
{

private:
	int score;
	vector<string> message;
	int health;

public:
	int getScore() const;
	void setScore(int a);
	int getHealth() const;
	void setHealth(int b);
	//vector<string> getMessage();
	void setMessage(string a, string b);

	virtual void printInfo();

};

