#pragma once
class Square
{
public:
	Square(float size);
	Square(float size, float left, float bottom);
	~Square();

	// Member functions
	void Print();
	void Translate(float deltaLeft, float deltaBottom);
	void SetSize(float newSize);

private:
	// Data members
	float m_Left;
	float m_Bottom;
	float m_Size;

	// Helper functions
	float GetArea();
	float GetPerimeter();

};
