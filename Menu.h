#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>
#include<fstream>
#include<algorithm>
#include <iomanip>
#include <sstream>
#include <SFML/Audio.hpp>
using namespace std;
struct Player
{
    string Name;
    float wpm;
    float accuracy;
};
class Menu
{
public:
    Menu();
	void MainMenu1();
	void Display1();
	void DefaultText();
	void Texts();
	void MainMenu2();
	void Display2();
	void About();
	void LeaderBoard();
	void LeadText();

private:
	sf::RenderWindow window1;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text t0, t1, t2, t3, t4;//first main menu
	sf::Text h0, h1, h2, h3;//second main menu
	sf::Text text1, text2, text3, text4, text5;//about
	sf::Text firstLine, naam, wpm, acc;//leaderboard
	sf::Texture bomb, first, second, lead;
	sf::Sprite firstBack, secBack, leadBack;
	sf::Event event;

	int t;
	int	h;
	int retGame;

	string Wpmstr, Accstr;
	stringstream ssWpm, ssAcc;
};


