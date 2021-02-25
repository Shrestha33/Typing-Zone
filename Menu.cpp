#include "Menu.h"
#include "Game.h"
#include <iostream>
Menu::Menu()
{
    first.loadFromFile("first.jpg");
    bomb.loadFromFile("bombrot.png");
    font.loadFromFile("cambria.ttc");
    lead.loadFromFile("lead.png");
    t = 1;
	h = 1;
	retGame = 1;

}

void Menu::Texts()//to set the background image and the text of the main menu
{
    firstBack.setTexture(first);
    secBack.setTexture(first);


    bomb.setSmooth(true);
    shape.setSize(sf::Vector2f(40.0f, 40.0f));
    shape.setTexture(&bomb);


    t0.setFont(font);
    t0.setPosition(255, 30);
    t0.setCharacterSize(42);
    t0.setStyle(sf::Text::Bold);
    t0.setFillColor(sf::Color(20, 100, 150));
    t0.setString("Welcome to Typing Zone");

    h0.setFont(font);
    h0.setPosition(255, 30);
    h0.setCharacterSize(42);
    h0.setStyle(sf::Text::Bold);
    h0.setFillColor(sf::Color(20, 100, 150));
    h0.setString("Difficulty Level");

    t1.setFont(font);
    t1.setPosition(302, 90);
    t1.setString("   Enter  the  Zone");

    t2.setFont(font);
    t2.setPosition(302, 130);
    t2.setString("   LeaderBoard");

    t3.setFont(font);
    t3.setPosition(302, 170);
    t3.setString("   About");

    t4.setFont(font);
    t4.setPosition(302, 210);
    t4.setString("   Exit");

    h1.setFont(font);
    h1.setPosition(302, 90);
    h1.setString("   Hard");

    h2.setFont(font);
    h2.setPosition(302, 130);
    h2.setString("   Medium");

    h3.setFont(font);
    h3.setPosition(302, 170);
    h3.setString("   Easy");
}

void Menu::DefaultText()    //to set the color and size of the texts for the main menu and the difficulty level
{
    t1.setFillColor(sf::Color::Magenta);
    t1.setCharacterSize(30);

    t2.setFillColor(sf::Color::Magenta);
    t2.setCharacterSize(30);

    t3.setFillColor(sf::Color::Magenta);
    t3.setCharacterSize(30);

    t4.setFillColor(sf::Color::Magenta);
    t4.setCharacterSize(30);

    h1.setFillColor(sf::Color::Magenta);
    h1.setCharacterSize(30);

    h2.setFillColor(sf::Color::Magenta);
    h2.setCharacterSize(30);

    h3.setFillColor(sf::Color::Magenta);
    h3.setCharacterSize(30);
}

void Menu::Display1()//displays the contents in the main menu
{
    window1.clear();

    window1.draw(firstBack);
    window1.draw(t0);
    window1.draw(t1);
    window1.draw(t2);
    window1.draw(t3);
    window1.draw(t4);
    window1.draw(shape);

    window1.display();
}

void Menu::MainMenu1()//related with the  main menu  contents and the choice of the user
{
    Texts();
    window1.create(sf::VideoMode(900,670), "Typing Zone");

    while (window1.isOpen())
    {
        DefaultText();
        shape.setPosition(sf::Vector2f(276, 52 + 40*t));//Position for the bomb present in main menu

        while (window1.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window1.close();
        }
        //for the choice through the keyboard following codes
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (t < 4)
                t++;
            Sleep(150);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (t > 1)
                t--;
            Sleep(150);
        }

        switch (t)//for change in color and increase in size
        {
        case 1:
            t1.setFillColor(sf::Color(244, 42, 11));
            t1.setCharacterSize(34);
            break;

        case 2:
            t2.setFillColor(sf::Color(244, 42, 11));
            t2.setCharacterSize(34);
            break;

        case 3:
            t3.setFillColor(sf::Color(244, 42, 11));
            t3.setCharacterSize(34);
            break;

        case 4:
            t4.setFillColor(sf::Color(244, 42, 11));
            t4.setCharacterSize(34);
            break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))//if user hits enter then selection based on t value
        {
            Sleep(150);
            switch (t)
            {
            case 1:
                MainMenu2();
                Sleep(100);
                break;

            case 2:
                LeaderBoard();
                Sleep(100);
                break;

            case 3:
                About();
                break;

            case 4:
                window1.close();
                break;

            }
        }
        Display1();//to display the contentes of the main menu
    }
}

void Menu::About()
{
    text1.setCharacterSize(20);
    text1.setPosition(45, 40);
    text1.setFont(font);
    text1.setString(" Hello Learner, \n\n\t\tWelcome to Typing Zone, a project on object oriented programming in C++. This game is\n designed in such a way that the user can master their typing skill in a fun way.");

    text2.setCharacterSize(20);
    text2.setPosition(45, 150);
    text2.setFont(font);
    text2.setString(" Game concept: \n\t\tThis is a game based on typing. We have a baby Penguin having fun in the Antartica. We\n have to save it from a nuclear bomb that is approaching to it. It is in the hand of the user to\n save the baby penguin.");

    text3.setCharacterSize(20);
    text3.setPosition(45, 260);
    text3.setFont(font);
    text3.setString(" How to Play: \n\t\t  A bomb is falling from the sky which is targeted at the young Penguin. A word is shown\n near the  top of the window, which depends on the  difficulty level that user  selected. If you \ncomplete typing the word provided before it hits the penguin, the bomb will diffuse and you\n save the penguin.");

    text4.setCharacterSize(20);
    text4.setPosition(45, 380);
    text4.setFont(font);
    text4.setString("\t\t Game End ? Happy Ending? Not quite yet.  Another bomb appears and after you complete\n diffusing it, then another and another, till you diffuse every last one of them  while the time\n keeps on decreasing. Number of Bombs you may ask which in your horror is infinite");

    text5.setCharacterSize(20);
    text5.setPosition(545, 475);
    text5.setFont(font);
    text5.setString("Developed By: \nMilan Shrestha (PUL 075 BCT 050) \nPrabin Paudel    (PUL 075 BCT 060)");

    while (window1.isOpen())
    {
        while (window1.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window1.close();

            if (event.type == sf::Event::TextEntered && event.text.unicode == 27)//to input the strings typed during the string
                return;
        }
        window1.clear();

        window1.draw(text1);
        window1.draw(text2);
        window1.draw(text3);
        window1.draw(text4);
        window1.draw(text5);

        window1.display();
    }
}

void Menu::Display2()//for displaying the contents in the difficulty section
{
    window1.clear();

    window1.draw(secBack);
    window1.draw(shape);
    window1.draw(h0);
    window1.draw(h1);
    window1.draw(h2);
    window1.draw(h3);

    window1.display();
}

void Menu::MainMenu2()//related with the contents of the difficulty section
{
    Game Game(window1);//passing the window to display the contents in the same window

    while (window1.isOpen())
    {
        DefaultText();
        shape.setPosition(sf::Vector2f(276, 52 + 40 * h));

        while (window1.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window1.close();

            if (event.type == sf::Event::TextEntered && event.text.unicode == 27)//to input the strings typed during the string
                {

                }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (h < 3)
                h++;
            Sleep(200);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (h > 1)
                h--;
            Sleep(200);
        }

        switch (h)//for change in color and increase in size
        {
        case 1:
            h1.setFillColor(sf::Color(244, 42, 11));
            h1.setCharacterSize(34);
            break;

        case 2:
            h2.setFillColor(sf::Color(244, 42, 11));
            h2.setCharacterSize(34);
            break;

        case 3:
            h3.setFillColor(sf::Color(244, 42, 11));
            h3.setCharacterSize(34);
            break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            retGame = Game.GamePlay(h);
            if (retGame == 0)
            {
                Sleep(200);
                return;
            }

        }
        Display2();//to display the contents of the difficulty section
    }

}

std::istream& operator>>(std::istream& is, Player& s)//overloading of stream extraction operator so line by line data of file is stored as the data members of the user defined data type
{
    return is >> s.Name >> s.wpm >> s.accuracy;//serial data of file is stored in the members of the user defind data type
}

void Menu::LeaderBoard()
{
    ifstream input("LeaderBoard.txt", ios::in);
    vector<Player> players;//vector of structures of type player

    Player s;
    while (input >> s)//stream extraction operator takes the input of one line of the file int the struct s
    {
        players.push_back(s);//after reading the data it is pushed into the vectors of players
    }
    input.close();

    sort(players.begin(), players.end(), [](const Player& s1, const Player& s2) {return s1.wpm * s1.accuracy > s2.wpm* s2.accuracy;});
    //algorithm to sort the vector of players based on the value obtained by the multiplication of wpm and accuracy in descending order

    while (players.size() > 10)//to display the contents of only ten players
        players.pop_back();//removes the last element of the vector corresponding to the lowest value of the players

    LeadText();//For the texts in the leader board

    window1.clear();
    while (window1.isOpen())
    {
        while (window1.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window1.close();
            if (event.type == sf::Event::TextEntered && event.text.unicode == 27)//to input the strings typed during the string
                return;
        }

        window1.draw(leadBack);
        window1.draw(firstLine);

        for (int i = 0; i < 10; i++)//for displaying the contents of the vectors and the numbers with precision of two
        {
            ssWpm << std::fixed << std::setprecision(2) << players[i].wpm;
            ssAcc << std::fixed << std::setprecision(2) << players[i].accuracy;
            Wpmstr = ssWpm.str();
            Accstr = ssAcc.str();

            naam.setPosition(150, 120 + 30 * i);
            naam.setString(players[i].Name);
            wpm.setPosition(435, 120 + 30 * i);
            wpm.setString(Wpmstr);
            acc.setPosition(617, 120 + 30 * i);
            acc.setString(Accstr);

            ssWpm.str("");
            ssAcc.str("");

            window1.draw(naam);
            window1.draw(wpm);
            window1.draw(acc);
        }
        window1.display();
    }
}

void Menu::LeadText()
{
    leadBack.setTexture(lead);

    firstLine.setString("Name \t\t\t\t\t\t\t\t WPM \t\t\t\t Accuracy");
    firstLine.setCharacterSize(28);
    firstLine.setFont(font);
    firstLine.setPosition(150, 80);

    naam.setCharacterSize(24);
    naam.setFont(font);

    wpm.setCharacterSize(24);
    wpm.setFont(font);

    acc.setCharacterSize(24);
    acc.setFont(font);
}


