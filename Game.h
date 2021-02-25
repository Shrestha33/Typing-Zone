#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

class Game
{
public:
    Game(sf::RenderWindow& window1);
    int GamePlay(int diff);
    ~Game();

private:
    void GameTexts();
    void GameValue();
    void File(string);
    void EndTexts();

private:
    sf::RenderWindow *window;
    sf::RectangleShape character, drop,  detonate, diffuse;
    sf::Texture blast, bomb, peng, smoke, third, fourth;
    sf::Sprite thirdBack, fourthBack;
    sf::Clock clock;
    sf::Font font;
    sf::Event event;
    sf::Text secured, points, type, usertype;//third wala ma
    sf::Text display, accuracy, wpm, poin, per, name, username;//last wala ma
    sf::Vector2f Cor;
    sf::SoundBuffer buffer,buffer2;
    sf::Sound sound,sound2;

    ifstream infile;

    bool timeCalc;
    bool diffuseTrigger;
    bool bDrop;

    float deltaTime;
    float changetimeanimation;
    float changetimediffusion;

    float rateOfChange;
    float subTime;
    float Accuracy;
    float NWPM;
    double finalTime;

    int point; //points dina
    int Poinc;
    int wordNo; //file wala word change garna
    int tempNo;
    int difficulty;
    unsigned int backSpace;//to find error
    unsigned int tempBack;
    unsigned int totalLetters;


    string word; //file dekhi vector ma haalna
    string userInput; //user le input gareko store garna
    string userName;
    string tempString;
    string wpmstr, accstr;
    vector<string> initialGivenWords; //file ko save garna
    stringstream sswpm, ssacc;
};

