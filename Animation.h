#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Animation
{
	Vector2u ImgCount;
	Vector2u CurrImg;
	float totalTime = 0.0f;
	float switchTime = 0.0f;
public:
	IntRect uvRect;//use to display animation
public:
	void setAnimation(Texture*texture,Vector2u ImgCount,float switchTime);
	void Update(int row, float deltaTime);
};
//row la dong cua bo animation selected
//faceRight dung de xac dinh huong cua nhan vat va lat hinh

