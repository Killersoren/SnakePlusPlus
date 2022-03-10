#include "InfoBox.h"
#include <iostream>
using namespace std;
using std::to_string;
vector<string>::iterator it;
//vector<string> Message;



void InfoBox::setMessage(string a, string b)
{
	message = { "Player Score   :  "+ a };
	it = message.begin();
	//it = message.insert(it, n);
	message.push_back("Player Health  :  " + b);
	
	if (score == 1)
	{
		message.push_back("Picked up   :    food");
		//message.push_back("Status  :   Ate a * and score was increased to */Got hurt by * and life decreased to *");

	}
	/*else
	{
		message.pop_back();

	}*/
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
	setMessage(to_string(score), to_string(health));
	for (it= message.begin(); it < message.end(); it++)
	{
		cout << *it;
		cout << '|';
		cout << endl;

	}

}