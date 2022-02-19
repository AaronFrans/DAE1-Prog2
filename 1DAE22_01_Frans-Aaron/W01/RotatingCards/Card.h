#pragma once
class Texture;

class Card final
{
public:

	enum class Suit
	{
		clubs = 1,
		diamonds = 2,
		hearts = 3,
		spades = 4,
		count 
	};

	explicit Card( Suit suit, int rank, float angle, Circlef circle );
	~Card();
	void Draw( const Rectf& destRect ) const; // const member functions is new, will be explained in the theory
	void Update(float elapsedSec);

	const static int m_MinRank {1};
	const static int m_MaxRank {13};
	float GetWidth()const ;// const member functions is new, will be explained in the theory
	float GetHeight()const ;// const member functions is new, will be explained in the theory
	std::string GetImagePath(Suit suit, int rank) const;// const member functions is new, will be explained in the theory

private:
	float m_Width;
	float m_Height;
	const Texture *m_pTexture;
	const Suit m_Suit;
	const int m_Rank;
	float m_AngleDegree;
	Circlef m_Circle;
	
};