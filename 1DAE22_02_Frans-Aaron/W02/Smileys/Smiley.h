// The query type (const) methods are not indicated as such, 
// but we expect you to indicate these using const.
#include "structs.h"
#include "Vector2f.h"


// -- Smiley.h file --
#pragma once
class  Texture; // class forward declaration

class Smiley
{
public:
	Smiley( const Point2f& position );
	~Smiley( );

	void Draw( ) const;
	void Update( float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect );
	void HitTest( const Point2f& pos );
	bool IsSleeping( ) const;
	Point2f GetPosition( ) const;
	void SetHighest( bool isHighest );
	void IncreaseSpeed( );
	void DecreaseSpeed( );

private:
	// DATA MEMBERS
	static Texture* m_pSmileyTexture;
	static int m_InstanceCounter;
	static float m_TextureWidth;
	static float m_TextureHeight;


	Point2f m_Position;
	Vector2f m_Velocity;
	bool m_IsHighest;
	bool m_IsSleeping;
	bool m_IsInSafeArea;

	// FUNCTIONS
	bool IsInSafeArea( const Rectf& safeRect );
};



