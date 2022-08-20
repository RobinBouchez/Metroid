#pragma once
#include <vector>

class Block;
class Grid final
{
public:
	Grid() = default;
	Grid(const std::string& filepath,const int& rows, const int& colums);
	~Grid() = default;

	void Draw() const;
	void Update(float elapsedSec);
	//void Collision(Mario* marioCollision);
	//bool IsOnGround(Mario* mario);
	Point2f PointOfCoordinate(const int& column, const int& row);

private:
	void LoadGrid(const std::string& filepath);
	void LoadBlocks(const int& rows, const int& colums);
	const int GetRowsFromFile(std::ifstream& file);
	const int GetColumnsFromFile(std::ifstream& file);


private:
	std::vector<std::vector<Block* >> m_Blocks;

	int m_Colums;
	int m_Rows;
};


