#pragma once
#include <SFML\Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture *texture,sf::Vector2u imageCount, float switchTime);
	void Update(int row, float deltaTime, sf::Vector2f* Cord, bool *drop);//last ko cordinate ho bomb khasna ko laagi
	void SpeedChange(float switchTime);

public:
	sf::IntRect uvRect;
	sf::Vector2u deto;
	sf::Vector2u currentImage;

private:
	sf::Vector2u imageCount;

	float totalTime;
	float switchTime;

};


