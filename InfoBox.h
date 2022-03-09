#pragma once
#include <vector>
#include <string>
class InfoBox
{

private:
	//int life;
	int score;
	vector<string> message;

public:
	int getScore() const;
	void setScore(int a);
	//vector<string> getMessage();
	void setMessage(char a);

	virtual void printInfo();

};

