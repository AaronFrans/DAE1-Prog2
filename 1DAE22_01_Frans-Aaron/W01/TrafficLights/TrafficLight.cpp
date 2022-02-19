#include "pch.h"
#include "TrafficLight.h"
#include "utils.h"
#include <iostream>
TrafficLight::TrafficLight(const Point2f& pos)
	:m_Position{ pos }
	, m_Width{ 50 }
	, m_Height{ 150 }
	, m_State{ State::off }
	, m_AccumulatedSec{ 0 }
	, m_Lights{}
{
	MakeLights();
}

void TrafficLight::DoHitTest(const Point2f& point)
{
	if (utils::IsPointInRect(point, Rectf{
		m_Position.x,
		m_Position.y,
		m_Width,
		m_Height
		}))
	{
		switch (m_State)
		{
		case State::green:
			m_State = State::off;
			break;
		case State::orange:
			m_State = State::off;
			break;
		case State::red:
			m_State = State::off;
			break;
		case State::off:
			for (Ellipsef light : m_Lights)
			{
				if (utils::IsPointInCircle(point, Circlef{
					light.center,
					light.radiusY
					}))
					m_AccumulatedSec = 0;
				else {
					m_State = State::red;

				}
			}
			break;
		}

	}

}

void TrafficLight::Update(float elapsedSec)
{
	switch (m_State)
	{
	case State::green:
		if (m_AccumulatedSec >= 4)
		{
			m_State = State::orange;
			m_AccumulatedSec -= 4;
		}
		m_AccumulatedSec += elapsedSec;
		break;
	case State::orange:
		if (m_AccumulatedSec >= 1)
		{
			m_State = State::red;
			m_AccumulatedSec -= 1;
		}
		m_AccumulatedSec += elapsedSec;
		break;
	case State::red:
		m_AccumulatedSec += elapsedSec;
		if (m_AccumulatedSec >= 4)
		{
			m_State = State::green;
			m_AccumulatedSec -= 4;
		}
		break;
	case State::off:

		break;
	}

}

void TrafficLight::Draw() const
{
	Color4f green{ 0,1,0,1 };
	Color4f orange{ 1,0.6f,0,1 };
	Color4f red{ 1,0,0,1 };
	Color4f lightOff{ 0.5f,0.5f,0.5f,1 };
	Color4f LightFrame{ 0.2f,0.2f,0.2f,1 };

	utils::SetColor(LightFrame);
	utils::FillRect(m_Position, m_Width, m_Height);

	switch (m_State)
	{
	case State::green:
		utils::SetColor(lightOff);
		utils::FillEllipse(m_Lights[0]);

		utils::SetColor(lightOff);
		utils::FillEllipse(m_Lights[1]);

		utils::SetColor(green);
		utils::FillEllipse(m_Lights[2]);
		break;
	case State::orange:
		utils::SetColor(lightOff);
		utils::FillEllipse(m_Lights[0]);

		utils::SetColor(orange);
		utils::FillEllipse(m_Lights[1]);

		utils::SetColor(lightOff);
		utils::FillEllipse(m_Lights[2]);

		break;
	case State::red:
		utils::SetColor(red);
		utils::FillEllipse(m_Lights[0]);

		utils::SetColor(lightOff);
		utils::FillEllipse(m_Lights[1]);

		utils::SetColor(lightOff);
		utils::FillEllipse(m_Lights[2]);
		break;
	case State::off:
		utils::SetColor(lightOff);
		utils::FillEllipse(m_Lights[0]);

		utils::SetColor(lightOff);
		utils::FillEllipse(m_Lights[1]);

		utils::SetColor(lightOff);
		utils::FillEllipse(m_Lights[2]);
		break;
	}
}

float TrafficLight::GetWidth()
{
	return m_Width;
}

float TrafficLight::GetHeight()
{
	return m_Height;
}

void TrafficLight::MakeLights()
{
	m_Lights.push_back(
		Ellipsef{
			m_Position.x + m_Width / 2,
			m_Position.y + (m_Height / 6 * 1),
			m_Width / 2 - 5,
			m_Width / 2 - 5,
		}
	);
	m_Lights.push_back(
		Ellipsef{
			m_Position.x + m_Width / 2,
			m_Position.y + (m_Height / 6 * 3),
			m_Width / 2 - 5,
			m_Width / 2 - 5,
		}
	);
	m_Lights.push_back(
		Ellipsef{
			m_Position.x + m_Width / 2,
			m_Position.y + (m_Height / 6 * 5),
			m_Width / 2 - 5,
			m_Width / 2 - 5,
		}
	);
}
