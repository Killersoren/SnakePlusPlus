//#include "InfoBox.h"
//#include <iostream>
//using namespace std;
//using std::to_string;
//vector<string>::iterator it;
////vector<string> Message;
//
//
//
//int InfoBox::getScore() const
//{
//	return score;
//}
//void InfoBox::setScore(int a)
//{
//	score += a;
//}
//int InfoBox::getHealth() const
//{
//	return health;
//}
//void InfoBox::setHealth(int b)
//{
//	health += b;
//}
//InfoBox::~InfoBox()
//{
//	std::cout << "Destructor called";
//	delete score;
//	delete score;
//
//}
//void InfoBox::setMessage(string a, string b)
//{
//	message = { "Player Score   :  " + a };
//	it = message.begin();
//	//it = message.insert(it, n);
//	message.push_back("Player Health  :  " + b);
//
//	if (score == 1)
//	{
//		message.push_back("Picked up   :    food");
//		//message.push_back("Status  :   Ate a * and score was increased to */Got hurt by * and life decreased to *");
//
//	}
//	/*else
//	{
//		message.pop_back();
//
//	}*/
//}
//
//void InfoBox::printInfo()
//{
//	setMessage(to_string(getScore()), to_string(getHealth()));
//	for (it = message.begin(); it < message.end(); it++)
//	{
//		cout << *it;
//		cout << '|';
//		cout << endl;
//
//	}
//
//}