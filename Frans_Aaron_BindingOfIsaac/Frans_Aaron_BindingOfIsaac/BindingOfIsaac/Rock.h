#pragma once
#include "GameObject.h"

class Rock final : public GameObject
{
public:

    Rock(Texture* objectTexture, Point2f center, float size);

    Rock(const Rock& rhs);
    Rock(Rock && rhs) = default;
    Rock& operator=(const Rock & rhs);
    Rock& operator=(Rock && rhs) = default;
    ~Rock();


    virtual void Draw() const override;
    virtual bool IsNotDestroyed() const override;

    virtual GameObject* Clone() const override;

private:
    bool m_IsBroken;
    int m_RockType;
};

