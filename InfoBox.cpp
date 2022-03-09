#include "InfoBox.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string>::iterator it;



void InfoBox::setMessage(char a)
{
	message = { "Player Score is :  " };
	it = message.begin();
	it = message.insert(it, a);

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
	//cout << "score: " << score << endl;

	for (it=message.begin(); it < message.end(); it++)
	{
		cout << {*it}->
	}

}