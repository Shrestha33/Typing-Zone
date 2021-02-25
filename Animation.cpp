#include "Animation.h"
#include <iostream>
Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime)
{
	this-> imageCount = imageCount;
	this-> switchTime = switchTime;

	totalTime = 0.0f;
	currentImage.x = 0; //texture ko x ko position

	uvRect.width = texture->getSize().x / float(imageCount.x); //width and height of single texture
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::Update(int row, float deltaTime, sf::Vector2f* Cord, bool *drop)
{
	currentImage.y = row; // texture ko y ko value ma input wala row ko value haleko
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
			currentImage.x = 0;
		deto.x++; //for changing row in blast texture image. changes is made directly in main function

		if (Cord->y < 736 && *drop==true)//to drop the bomb(movement), valid until hits the penguin
		{
			Cord->x += 15.0;
			Cord->y += 49.0;
		}

	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

void Animation::SpeedChange(float switchtime)
{
	this->switchTime = switchtime;
}
