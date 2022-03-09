#include "InfoBox.h"
#include <iostream>
using namespace std;
using std::to_string;
vector<string>::iterator it;
//vector<string> Message;



void InfoBox::setMessage(string n)
{
	message = { "Player Score is :  " };
	it = message.begin();
	//it = message.insert(it, n);
	message.push_back(n);
}

int InfoBox::getScore() const
{
	return score;
}
void InfoBox::setScore(int a)
{
	score += a;
}

void InfoBox::printInfo()
{
	setMessage(to_string(score));
	for (it= message.begin(); it < message.end(); it++)
	{
		cout << *it;
		cout << '-';

	}

}