#pragma once
#include<map>

class Texture;
class Sprite;
class Costume;
class Item
{
public:
	enum class StatChanges
	{
		walkSpeed,
		tearHeight,
		tearSpeed,
		tearRange,
		damage,
		tearFireRate,
		healthCointainer,
	};

	enum class CostumeType
	{
		head,
		body
	};

	Item(std::string name, Texture* pickUpTexture, Sprite* costumeUD, Sprite* costumeLR,
		Point2f center, std::map<StatChanges, float> statChanges, CostumeType costumeType);

	Item(const Item& rhs) = default;
	Item(Item && rhs) = default;
	Item& operator=(const Item & rhs) = default;
	Item& operator=(Item && rhs) = default;
	~Item();

	void SetPosition(Point2f newPos);
	void Draw() const;

	Costume* GetCostume();
	std::string GetName();

	std::map<StatChanges, float> GetStatChanges();


private:


	std::string m_Name;

	Texture* m_pPickUpTexture;
	Costume* m_pCostume;

	Point2f m_CenterPosition;

	std::map<StatChanges, float> m_StatChanges;

	float m_Width;
	float m_Height;

};
