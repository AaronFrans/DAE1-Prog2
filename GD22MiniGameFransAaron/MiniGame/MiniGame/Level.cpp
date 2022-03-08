#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "utils.h"
#include "SVGParser.h"

Level::Level()
	: m_fenceBottomLeft{ 200, 190 }

{
	m_pBackgroundTexture = new Texture{ "Resources/Images/background.png" };
	m_pFenceTexture = new Texture{ "Resources/Images/fence.png" };

	SVGParser::GetVerticesFromSvgFile("Resources/Images/background.svg", m_Vertices);
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	m_pBackgroundTexture = nullptr;
	delete m_pFenceTexture;
	m_pFenceTexture = nullptr;
}

void Level::DrawBackground() const
{
	m_pBackgroundTexture->Draw(Point2f{ 0, 0 });
}

void Level::DrawForeground() const
{
	m_pFenceTexture->Draw(m_fenceBottomLeft);
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& angularVelocity) const
{
	utils::HitInfo hitInfo;
	Point2f actorTop{ actorShape.left + actorShape.width / 2.0f,
	actorShape.bottom + actorShape.height };
	Point2f actorBottom{ actorShape.left + actorShape.width / 2.0f,
	actorShape.bottom - 1};
	if (utils::Raycast(m_Vertices[0], actorTop, actorBottom, hitInfo))
	{
		actorShape.bottom = hitInfo.intersectPoint.y;
		angularVelocity.y = 0;
	}
}

bool Level::IsOnGround(const Rectf& actorShape) const
{
	utils::HitInfo hitInfo;
	Point2f actorTop{ actorShape.left + actorShape.width / 2.0f,
	actorShape.bottom + actorShape.height };
	Point2f actorBottom{ actorShape.left + actorShape.width / 2.0f,
	actorShape.bottom - 1 };

	return utils::Raycast(m_Vertices[0], actorTop, actorBottom, hitInfo);
}
