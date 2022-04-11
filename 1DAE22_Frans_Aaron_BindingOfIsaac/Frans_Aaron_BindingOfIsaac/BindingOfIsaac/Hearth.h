#pragma once
class Texture;
class Hearth final
{
public:
	enum class HearthState
	{
		full = 0,
		half = 1,
		empty = 2
	};

	Hearth(Texture* heartSheet, HearthState state, float dstHeartSize);

	void Draw(const Point2f& centerPos) const;
	HearthState GetState() const;

	void TakeDamage(float damage);

private:
	Texture* m_pHeartSheet;

	Point2f m_CenterPos;
	HearthState m_State;

	const float m_DstHeartSize;
	float m_SrcHeartSize;


};

