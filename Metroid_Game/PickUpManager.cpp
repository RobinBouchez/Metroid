#include "pch.h"
#include "PickUpManager.h"
#include "PickUp.h"
#include "utils.h"
#include "GameObject.h"
#include "HUD.h"


void PickUpManager::Draw() const
{
	for (auto e : m_pPickUpVector)
	{
		e->Draw();
	}
}

void PickUpManager::IsPlayerOverlapping(const Rectf& player)
{
	for (auto e : m_pPickUpVector)
	{
		if (!e->GetIsActive())
		{
			continue;
		}
		if (utils::IsOverlapping(player, e->GetBoundaries()))
		{
			HUD::GetInstance().UpdateScore(10);
			e->SetIsActive(false);
		}
	}
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

std::vector<PickUp*>& PickUpManager::GetPickUps()
{
	return m_pPickUpVector;
}


