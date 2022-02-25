// -- Smiley.cpp file --
// Decide yourself about the necessary include directives
#include "pch.h"
#include "Smiley.h"
#include "Texture.h"
#include "utils.h"

// Static Texture data
Texture* Smiley::m_pSmileyTexture{ nullptr };
int Smiley::m_InstanceCounter{ 0 };
float Smiley::m_TextureWidth{ 0 };
float Smiley::m_TextureHeight{ 0 };

// Constructor
// Initializes the object, among others:
//	- Initializes the data members, the velocity gets a random value within the inclusive range[60, 180] and [-180, -60]
//	- Creates a texture object to load the image, only if it hasn’t been created before( !)
//  - Adapts the instance counter
Smiley::Smiley(const Point2f& position)
	: m_Position{ position }
	, m_Velocity{ float(rand() % 51 - 25), float(rand() % 51 - 25) }
	, m_IsHighest{ false }
	, m_IsSleeping{ false }
	, m_IsInSafeArea{ false }
{
	m_InstanceCounter++;
	if (m_pSmileyTexture == nullptr)
	{
		m_pSmileyTexture = new Texture{ "Resources/Smileys.png" };
		m_TextureWidth = m_pSmileyTexture->GetWidth() / 4.0f;
		m_TextureHeight = m_pSmileyTexture->GetHeight();
	}
}

// Destructor
// Deletes the Texture object when this is the last Smiley that is being destroyed.
Smiley::~Smiley()
{
	m_InstanceCounter--;
	if (m_InstanceCounter == 0)
	{
		delete m_pSmileyTexture;
		m_pSmileyTexture = nullptr;
	}
}

// Draw
// Draws a part of the image on the window, which part depends on the state of the smiley:
// - If the smiley is sleeping then the sleeping smiley is drawn.
// - If the smiley is at the highest position, then the happy smiley is drawn.
// - If the smiley is not in the safe area, the scary smiley is drawn.
// - If none of the above conditions is met, the neutral smiley should be drawn.
void Smiley::Draw() const
{
	if (m_IsSleeping)
		m_pSmileyTexture->Draw(m_Position, Rectf{ 3 * m_TextureWidth, 0, m_TextureWidth, m_TextureHeight });
	else if (m_IsHighest)
		m_pSmileyTexture->Draw(m_Position, Rectf{ 0, 0, m_TextureWidth, m_TextureHeight });
	else if (m_IsInSafeArea)
		m_pSmileyTexture->Draw(m_Position, Rectf{ m_TextureWidth, 0, m_TextureWidth, m_TextureHeight });
	else
		m_pSmileyTexture->Draw(m_Position, Rectf{ 2 * m_TextureWidth, 0, m_TextureWidth, m_TextureHeight });
}

// Update
// - When the smiley is not sleeping, the new position - using the velocity and elapsed seconds - is calculated.
// - The velocity changes sign when at this new position the smiley is outside the bounding rectangle (boundingRect)
// - Checks whether at this new position, it is located in the safe area and updates m_IsInSafeArea accordingly.
void Smiley::Update(float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect)
{
	if (!m_IsSleeping)
	{
		m_Position.x += m_Velocity.x * elapsedSec;
		m_Position.y += m_Velocity.y * elapsedSec;

		if (m_Position.x + m_TextureWidth > boundingRect.left + boundingRect.width ||
			m_Position.x < boundingRect.left)
			m_Velocity.x = -m_Velocity.x;
		if (m_Position.y + m_TextureHeight > boundingRect.bottom + boundingRect.height ||
			m_Position.y < boundingRect.bottom)
			m_Velocity.y = -m_Velocity.y;

		IsInSafeArea(safeRect) ? m_IsInSafeArea = true : m_IsInSafeArea = false;
	}

}

// HitTest
// If the value of the parameter pos is within the boundaries of the smiley’s circle,
// then the sleeping state of the smiley changes.
void Smiley::HitTest(const Point2f& pos)
{
	if (utils::IsPointInCircle(pos, Circlef(m_Position.x + m_TextureWidth / 2.0f, m_Position.y + m_TextureHeight / 2.0f, m_TextureWidth)))
	{
		m_IsSleeping ? m_IsSleeping = false : m_IsSleeping = true;
	}
}

// IsSleeping
// Getter of the m_IsSleeping data member
bool Smiley::IsSleeping() const
{
	return m_IsSleeping;
}

// GetPosition
// Getter of the m_Position data member
Point2f Smiley::GetPosition() const
{
	return m_Position;
}

// SetHighest
// Setter of the m_IsHighest data member
void Smiley::SetHighest(bool isHighest)
{
	m_IsHighest = isHighest;
}

// IncreaseSpeed
// Changes the speed 5% up
void Smiley::IncreaseSpeed()
{
	m_Velocity.x *= 1.5;
	m_Velocity.y *= 1.5;
}

// DecreaseSpeed
// Changes the speed 5% down
void Smiley::DecreaseSpeed()
{
	m_Velocity.x /= 1.5;
	m_Velocity.y /= 1.5;
}

// IsInSafeArea
// Returns true when the smiley is completely inside the safe area as indicated by safeRect
bool Smiley::IsInSafeArea(const Rectf& safeRect)
{
	return (m_Position.x + m_TextureWidth <= safeRect.left + safeRect.width
		&& m_Position.x >= safeRect.left)
		&& (m_Position.y + m_TextureHeight <= safeRect.bottom + safeRect.height
			&& m_Position.y >= safeRect.bottom);
}



