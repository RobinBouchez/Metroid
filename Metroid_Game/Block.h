#pragma once
class Block final
{
public:
	enum class Type : int
	{
		Crawler = 0,
		Skrull = 1,
		RedCraler = 2,
	};

	Block(const int& rows, const int& columns);
	~Block() = default;

	void Draw() const;
	void Update(float elapsedSec);

	//static float GetBlockSize();

private:
	int m_Row;
	int m_Column;
	//static float m_BlockSize;
};

