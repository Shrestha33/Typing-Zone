#include "Animation.h"
#include "Game.h"
#include<windows.h>
Game::Game(sf::RenderWindow& window1)
{

    if(!buffer.loadFromFile("Explosion.wav"))
                cout<<"Error"<<endl;
    sound.setBuffer(buffer);
    if(!buffer2.loadFromFile("Bloop.wav"))
               cout<<"Error"<<endl;
    sound2.setBuffer(buffer2);
    font.loadFromFile("cambria.ttc");

    third.loadFromFile("third.jpg");
    fourth.loadFromFile("fourth.jpg");
    thirdBack.setTexture(third);
    fourthBack.setTexture(fourth);

    blast.loadFromFile("blast.png");
    bomb.loadFromFile("bombdrop.png");
    bomb.setSmooth(true);
    peng.loadFromFile("peng.png");
    peng.setSmooth(true);
    smoke.loadFromFile("smoke.png");
    window=&window1;
}

void Game::GameValue()
{
    character.setSize(sf::Vector2f(50.0f, 51.0f)); //Sets the length and width of rectangular entity on which texture is to be shown and it must cover
    drop.setSize(sf::Vector2f(64.0f, 64.0f));
    detonate.setSize(sf::Vector2f(640.0f, 464.0f));//depends whether y is 735 or not
    diffuse.setSize(sf::Vector2f(128.0f, 107.0f));

    character.setPosition(425.0f, 600.0f);//Position on screen for penguin
    character.setTexture(&peng);

    detonate.setPosition(164.0f, 185.0f);//Position for blast
    detonate.setTexture(&blast);

    drop.setTexture(&bomb);
    diffuse.setTexture(&smoke);

    Cor = {250.0,0.0};//Position for bomb from where it starts to fall

    clock.restart();

    userInput.clear();
    initialGivenWords.clear();

    timeCalc = true;
    diffuseTrigger = false;
    bDrop = true;

    deltaTime = 0.0f;
    subTime = 0;
    finalTime = 0.0;

    point = 0;
    wordNo = 0;
    tempNo = 0;
    backSpace = 0;
    tempBack = 0;
    totalLetters = 0;
}

void Game::GameTexts()//For points and its value
{
    points.setFont(font);
    points.setCharacterSize(24);
    points.setPosition(770.0f, 20.0f);
    points.setString("Points");

    secured.setFont(font);
    secured.setCharacterSize(24);
    secured.setPosition(790.0f, 45.0f);
    secured.setString("0");

    type.setFont(font);
    type.setCharacterSize(24);
    type.setFillColor(sf::Color::Magenta);
    type.setPosition(390.0f, 90.0f);

    usertype.setFont(font);
    usertype.setCharacterSize(24);
    usertype.setFillColor(sf::Color::Magenta);
    usertype.setPosition(390.0f, 120.0f);
}

void Game::File(string filename)//opening the file based upon the players choice and displaying words randomly
{
    string temp = "Random";
    infile.open(filename);
    while (infile)   //checking if file is opened or not
    {
        while (!infile.eof())
        {
            infile >> word;
            if (temp != word) //done to avoid repetition of words
            {
                temp = word;
                initialGivenWords.push_back(word);
            }
        }
        infile.close();

        unsigned seed = std::chrono::system_clock::now()//shuffle the words
            .time_since_epoch()
            .count();
        shuffle(initialGivenWords.begin(), initialGivenWords.end(), std::default_random_engine(seed));
    }
}

int Game::GamePlay(int diff)
{
    GameValue();
    GameTexts();

    if (diff == 1)
    {
        File("Hard.txt");
        changetimeanimation = 0.4;
        changetimediffusion =0.2;
        rateOfChange = 0.07;
        Poinc = 8;
    }
    else if (diff == 2)
    {
        File("Medium.txt");
        changetimeanimation = 0.5;
        changetimediffusion =0.3;
        rateOfChange = 0.05;
        Poinc = 6;
    }
    else
    {
        File("Easy.txt");
        changetimeanimation = 0.7;
        changetimediffusion =0.4;
        rateOfChange = 0.04;
        Poinc = 5;
    }

    Animation animation(&peng, sf::Vector2u(8, 8), changetimeanimation);
    Animation diffusion(&smoke, sf::Vector2u(8, 1), changetimediffusion);//each coordinate changes in switch seconds
    Animation detonation(&blast, sf::Vector2u(5, 5), 0.025f);//switchtime is for the time for each texture to switch

    detonation.deto.x = 0, detonation.deto.y = 0; //for bomb detonation,must be after detonation object declaration

    auto start = chrono::steady_clock::now();
    while (window->isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        while (window->pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                auto end = chrono::steady_clock::now();
                window->close();
                auto diff = end - start;         // Store the time difference between start and end
                finalTime = (chrono::duration <double, milli>(diff).count()) / 1000;
            }

            if (event.type == sf::Event::TextEntered && Cor.y < 540)//to input the strings typed during the string
            {
                if (event.text.unicode == 27)
                    return 1;

                else if (event.text.unicode == 8)//if backspace removes last letter
                {
                    if (userInput.size() > 0)
                    {
                        userInput.pop_back();
                        tempBack++;
                    }

                }

               else if(event.text.unicode == 13 || event.text.unicode == 9 )
                {
                    //for enter and tab and escape do nothing
                }

                else if (userInput.size() < initialGivenWords[wordNo].size())
                {
                    userInput += static_cast<char>(event.text.unicode); //converts the unicode into the typed character as input is in the form of unicode
                }

                if (userInput.size() == initialGivenWords[wordNo].size())
                {
                    if (userInput == initialGivenWords[wordNo])
                    {
                        diffuseTrigger = true;
                        changetimeanimation -= rateOfChange * changetimeanimation;
                        changetimediffusion-= rateOfChange * changetimediffusion;
                        animation.SpeedChange(changetimeanimation);//increases the speed of bomb drop,changetimeanimation=droptime
                        diffusion.SpeedChange(changetimediffusion);
                        point += Poinc;
                        secured.setString(to_string(point));
                    }
                }

            }
        }

        window->clear();
        type.setString(initialGivenWords[wordNo]);//setting the string-words to be typed in the window
        usertype.setString(userInput);

        animation.Update(0 + animation.deto.y, deltaTime, &Cor, &bDrop);//cor is cordinate for the bomb which must change
        character.setTextureRect(animation.uvRect);

        window->draw(thirdBack);
        window->draw(points);
        window->draw(secured);
        window->draw(type);
        window->draw(usertype);

        drop.setPosition(Cor.x, Cor.y); //position for bomb, in every loop position must change
        if (Cor.y < 540) //if bomb hits the penguin, doesn't draw penguin and bomb
        {
            window->draw(character);
            if (diffuseTrigger == true)//starts process of diffusing but not what to do
            {
                bDrop = false; //stops changing of cordinate
                diffuse.setPosition(Cor.x - 30, Cor.y);//position for the diffuse texture
                diffusion.Update(0, deltaTime, &Cor, &bDrop);//animation
                diffuse.setTextureRect(diffusion.uvRect);
                window->draw(diffuse);
                if (sound2.getStatus() != sf::Sound::Playing)
                        sound2.play();

            }

            else
                window->draw(drop);//if <736 and no diffuseTrigger bomb keeps on falling
        }
        else //to blast the bomb once penguin is hit
        {
           if (sound.getStatus() != sf::Sound::Playing)//explosion sound
                    sound.play();
           if (timeCalc == true)//ends time for wpm and does calculation only once
            {
                auto end = chrono::steady_clock::now();
                auto diff = end - start;         // Store the time difference between start and end
                finalTime = (chrono::duration <double, milli>(diff).count()) / 1000 - changetimeanimation * 11; //excluding last time for bomb drop
                timeCalc = false;
            }

            detonation.Update(0 + detonation.deto.y, deltaTime, &Cor, &bDrop);
            detonate.setTextureRect(detonation.uvRect);
            window->draw(detonate);

            if (detonation.deto.x > 4)//to change the row of blast texture image
            {
                detonation.deto.x = 0;
                detonation.deto.y++;
            }
        }


        if (animation.deto.x > 7)//to change the row of blast texture image
        {
            animation.deto.x = 0;
            animation.deto.y++;
        }

        if (animation.deto.y > 7)
            animation.deto.y = 0;

        if (diffusion.currentImage.x == 6)//to restart the process after bomb diffuses
        {
            Cor.x = 250.0; //resetting bomb poisition
            Cor.y = 0.0;

            bDrop = true; //changing the value of drop in Animation,starts dropping
            diffuseTrigger = false; //to stop triggering diffuse

            userInput.clear();//clears the string

            subTime += changetimediffusion * 6; //adds the time for bomb diffuse,*6 because 6 images

            totalLetters += initialGivenWords[wordNo].size();
            tempNo++;
            wordNo++; //to change the words,next word
            backSpace += tempBack;
            tempBack = 0;

            diffusion.currentImage.x = 0; //resetting diffusion value in sprite sheet,initial position
        }

        if (detonation.deto.y == 6)
        {
            return 0;
        }
        window->display();
    }
    return 0;
}

Game::~Game()
{
    if (totalLetters == 0)
    {
        Accuracy = 0;
        NWPM = 0;
        return;
    }
    else
    {
        Accuracy = (float(totalLetters - backSpace) / totalLetters) * 100;
        NWPM = (totalLetters / 5) / ((finalTime - subTime) / 60);
    }

    sswpm << std::fixed << std::setprecision(2) << NWPM;
    ssacc << std::fixed << std::setprecision(2) << Accuracy;
    wpmstr = sswpm.str();
    accstr = ssacc.str();

    EndTexts();

    while (window->isOpen())
    {
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::TextEntered)//to input the strings typed during the string
            {
                if (event.text.unicode == 27)
                    return;

                else if (event.text.unicode == 13 || event.text.unicode == 9)
                {
                    //for enter and tab and escape do nothing
                }

                else if (event.text.unicode == 8)//if backspace removes last letter
                {
                    if (userName.size() > 0)
                        userName.pop_back();
                }

                else
                    userName += static_cast<char>(event.text.unicode);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            ofstream outfile;
            outfile.open("LeaderBoard.txt", ios::app);//append mode to add the value in the data
            while (outfile)
            {
                outfile << userName << "\t" << NWPM << "\t" << Accuracy << endl;//this also introduces the tab in the file
                break;//otherwise the loop iterates infinitely;
            }
            outfile.close();
            return;
        }

        username.setString(userName);

        window->clear();

        window->draw(fourthBack);
        window->draw(display);
        window->draw(poin);
        window->draw(accuracy);
        window->draw(per);
        window->draw(name);
        window->draw(username);
        window->draw(wpm);

        window->display();
    }
}


void Game::EndTexts()
{
    name.setFont(font);
    name.setCharacterSize(24);
    name.setPosition(420,200);
    name.setString("Enter your name");

    username.setFont(font);
    username.setCharacterSize(24);
    username.setPosition(600, 200);

    display.setFont(font);
    display.setCharacterSize(24);
    display.setPosition(450, 230);
    display.setString("Points:- \nAccuracy:- \nAvg. WPM:-");

    poin.setFont(font);
    poin.setCharacterSize(25);
    poin.setPosition(550, 230);
    poin.setString(to_string(point));


    accuracy.setFont(font);
    accuracy.setCharacterSize(25);
    accuracy.setPosition(572, 258);
    accuracy.setString(accstr);

    wpm.setFont(font);
    wpm.setCharacterSize(25);
    wpm.setPosition(584, 286);
    wpm.setString(wpmstr);

    per.setFont(font);
    per.setCharacterSize(25);
    per.setPosition(649, 258);
    per.setString("%");

}
