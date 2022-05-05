#pragma once


class Texture;

class Sprite final
{
public:
	Sprite();
	Sprite(Texture* texture, int nrCols, int nrRows, float frameSec, float scale, int nrFrames = 0);

	Sprite(const Sprite& rhs);
	Sprite(Sprite && rhs) = default;
	Sprite& operator=(const Sprite & rhs);
	Sprite& operator=(Sprite && rhs) = default;
	~Sprite();

	void Update(float elapsedSec);
	void Draw(const Point2f& pos, const Point2f& srcBottomLeft = Point2f{ 0,0 }) const;
	void Draw(const Rectf& dstRect, const Point2f& srcBottomLeft = Point2f{ 0,0 }) const;

	float GetFrameWidth() const;
	float GetFrameHeight() const;
	int GetNrFrames() const;

	void SetActFrame(int actFrame);
	void SetAccuSec(float accuSec);

	float GetTotalLoopTime();

private:

	Texture* m_pSpriteSheet;

	int m_Frames;
	int m_Cols;
	int m_Rows;
	float m_FrameSec;
	int m_ActFrame;
	float m_AccuSec;

	float m_Scale;
};

