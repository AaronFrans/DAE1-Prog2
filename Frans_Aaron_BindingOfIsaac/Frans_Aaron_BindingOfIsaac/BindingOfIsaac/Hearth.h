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

	Hearth(const Hearth& rhs);
	Hearth(Hearth && rhs) = default;
	Hearth& operator=(const Hearth & rhs);
	Hearth& operator=(Hearth && rhs) = default;
	virtual ~Hearth() = default;


	void Draw(const Point2f& centerPos) const;
	HearthState GetState() const;

	void TakeDamage(float damage);

private:
	Texture* m_pHeartSheet;

	Point2f m_CenterPos;
	HearthState m_State;

	float m_DstHeartSize;
	float m_SrcHeartSize;
};

