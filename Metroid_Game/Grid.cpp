#include "pch.h"
#include "Grid.h"
#include "Block.h"

#include <string>
#include <fstream>

Grid::Grid(const std::string& filepath, const int& rows, const int& colums)
	: m_Rows{ rows }
	, m_Colums{ colums }
{
	LoadGrid(filepath);
	LoadBlocks(rows, colums);
}

void Grid::LoadGrid(const std::string& filepath)
{
	std::ifstream file{ filepath };

	GetRowsFromFile(file);
	GetColumnsFromFile(file);


	for (int r = m_Rows - 1; r >= 0; r--)
	{
		std::vector<Block*> tempVector{};
		for (int c = 0; c < m_Colums; c++)
		{
			std::string typeBlock{};
			std::getline(file, typeBlock, (c < m_Colums - 1) ? ' ' : '\n');
	/*		if (true)
			{
				int blockType = std::stoi(typeBlock);
				switch (Block::BlockType(blockType))
				{
				case Block::BlockType::dirt:
					tempVector.push_back(new Block(r, c));
					break;
				case Block::BlockType::coin:
					tempVector.push_back(new Coin(r, c));
					break;
				default:
				case Block::BlockType::air:
					tempVector.push_back(nullptr);
					break;
				}
			}*/
		}
		m_Blocks.push_back(tempVector);
	}
}

void Grid::LoadBlocks(const int& rows, const int& colums)
{
	for (int r = 0; r < rows; r++)
	{
		std::vector<Block*> temp{};

		for (int c = 0; c < colums; c++)
		{
			temp.push_back(new Block(r, c));
		}
		m_Blocks.push_back(temp);
	}
}

const int Grid::GetRowsFromFile(std::ifstream& file)
{
	std::string amountOfRows{};
	std::getline(file, amountOfRows);
	m_Rows = std::stoi(amountOfRows);
	return m_Rows;
}

const int Grid::GetColumnsFromFile(std::ifstream& file)
{
	std::string amountOfColums{};
	std::getline(file, amountOfColums);
	m_Colums = std::stoi(amountOfColums);
	return m_Colums;
}
//
//Point2f Grid::PointOfCoordinate(const int& column, const int& row)
//{
//	return Point2f(column * Block::GetBlockSize(), row * Block::GetBlockSize());
//}
