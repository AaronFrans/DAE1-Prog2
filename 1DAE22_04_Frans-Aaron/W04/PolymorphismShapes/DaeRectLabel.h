#pragma once
#include "Vector2f.h"
#include "Texture.h"
#include "DaeRectangle.h"

class DaeRectLabel final : public DaeRectangle
{
public:
	DaeRectLabel( const Point2f& center, float width, float height, const Color4f& color, const std::string& label, const Color4f& textColor, TTF_Font* pFont );
	~DaeRectLabel( );


	void virtual Draw() const override;
private: 
	Texture* m_pLabelText;
	float m_MarginX;
	float m_MarginY;
};

 
