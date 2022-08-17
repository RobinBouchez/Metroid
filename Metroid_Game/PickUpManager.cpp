#include "pch.h"
#include "PickUpManager.h"
#include "PickUp.h"

void PickUpManager::Draw() const
{
	for (auto e : m_pPickUpVector)
	{
		e->Draw();
	}
}

void PickUpManager::Create(PickUp* PickUp)
{
	m_pPickUpVector.push_back(PickUp);
}

void PickUpManager::Update(float elapsedSec)
{
	for (auto e : m_pPickUpVector)
	{
		e->Update(elapsedSec);
	}
}

void PickUpManager::Cleanup()
{
	for (auto e : m_pPickUpVector)
	{
		delete e;
		e = nullptr;
	}
	m_pPickUpVector.clear();
}

std::vector<PickUp*>& PickUpManager::GetBullets()
{
	return m_pPickUpVector;
}
