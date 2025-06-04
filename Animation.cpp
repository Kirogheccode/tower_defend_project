#include "Animation.h"

void Animation::setAnimation(Texture* texture, Vector2u ImgCount, float switchTime)
{
	this->ImgCount = ImgCount;
	this->switchTime = switchTime;

	totalTime = 0.0f;
	CurrImg.x = 0;

	//Kich thuoc cua tung mot animation
	uvRect.width = texture->getSize().x / float(ImgCount.x);
	uvRect.height = texture->getSize().y / float(ImgCount.y);
}

void Animation::Update(int row, float deltaTime)
{
	//In this img the row is 0 (index)
	CurrImg.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;//smoother instead of equal to 0.0
		CurrImg.x++;//XChuyen sang animation ke tiep, Index cua tung buoc anh chu khong phai toa do

		if (CurrImg.x >= ImgCount.x) // ImgCount.x - 1 is index of the last img
			CurrImg.x = 0;
	}

	uvRect.top = CurrImg.y * uvRect.height;
	uvRect.left = CurrImg.x * uvRect.width;
	//if (faceRight)
	//{
	//	uvRect.left = CurrImg.x * uvRect.width;
	//}
	//else
	//{
	//	uvRect.left = (CurrImg.x + 1) * abs(uvRect.width);//abs: dam bao chieu dai tinh toan la duong
	//	uvRect.width = -abs(uvRect.width);//abs: giu cho chieu dai luon am every loop
	//}
}
