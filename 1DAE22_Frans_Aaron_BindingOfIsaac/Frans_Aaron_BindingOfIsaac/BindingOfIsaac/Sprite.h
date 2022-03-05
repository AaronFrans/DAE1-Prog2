#pragma once

class Texture;

class Sprite
{
public:
	Sprite();
	Sprite(Texture* texture, int nrCols, int nrRows, float frameSec, float scale, int nrFrames = 0);
	~Sprite();

	void Update(float elapsedSec);
	void Draw(const Point2f& pos, const Point2f& srcBottomLeft = Point2f{ 0,0 }) const;

	float GetFrameWidth() const;
	float GetFrameHeight() const;

	void SetActFrame(int actFrame);
	void SetAccuSec(float accuSec);

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

