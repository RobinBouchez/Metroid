#include "pch.h"
#include "Block.h"

Block::Block(const int& rows, const int& columns)
	: m_Row{rows}
	, m_Column{columns}
{
}

void Block::Draw() const
{
}

void Block::Update(float elapsedSec)
{
}

//float Block::GetBlockSize()
//{
//    return m_BlockSize;
//}
