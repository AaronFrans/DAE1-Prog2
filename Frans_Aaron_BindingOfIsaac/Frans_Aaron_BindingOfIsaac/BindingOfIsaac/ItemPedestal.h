#pragma once
#include "GameObject.h"
#include "TextureManager.h"

class Item;
class ItemPedestal final
{
public:

	ItemPedestal(Texture* pedestalTexture, Point2f center, float size);

    ItemPedestal(const ItemPedestal& rhs);
    ItemPedestal(ItemPedestal && rhs) = default;
    ItemPedestal& operator=(const ItemPedestal & rhs);
    ItemPedestal& operator=(ItemPedestal && rhs) = default;
    ~ItemPedestal();

    ItemPedestal* Clone() const;


    void Draw() const;

    void PlaceItem(Item* item);
    void TakeItem();

    Circlef GetShape() const;
    Point2f GetCenter() const;
    Item* GetItem();

    bool IsItemTaken();



private:


	Item* m_pItem;


    Texture* m_pTexture;
    Rectf m_DrawShape;
    Point2f m_Center;


    bool m_IsItemTaken;

};

