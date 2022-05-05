#pragma once
class Camera final
{
public:
	Camera(float width, float height);


	void SetLevelBoundaries(const Rectf& levelBoundaries);
	void Transform(const Point2f& targetCenter) const;

	Rectf GetCameraView(const Point2f& targetCenter) const;
private:
	float m_Width;
	float m_Height;

	Rectf m_LevelBoundaries;

	void Clamp(Point2f& centerPos) const;
};

