#pragma once
#include <vector>
#include "Vector2f.h"

class Texture;

class Level
{
public:
	Level();
	~Level();

	void DrawBackground() const;
	void DrawForeground() const;

	void HandleCollision(Rectf& actorShape, Vector2f& angularVelocity) const;
	bool IsOnGround(const Rectf& actorShape) const;

private:

	Texture* m_pBackgroundTexture;
	Texture* m_pFenceTexture;


	std::vector<Point2f> m_Vertices;
	Point2f m_fenceBottomLeft;
};

