#pragma once
#include <vector>
class TrafficLight
{
	
	enum class State
	{
		green,
		orange,
		red,
		off
	};


public:

	TrafficLight(const Point2f& pos);
	
	void DoHitTest(const Point2f& point);

	void Update(float elapsedSec);

	void Draw() const;

	float GetWidth();

	float GetHeight();




private:
	State m_State;
	Point2f m_Position;
	float m_AccumulatedSec;


	const float m_Width;
	const float m_Height;
	std::vector<Ellipsef> m_Lights;


	void MakeLights();
};

