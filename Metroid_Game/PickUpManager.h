#pragma once
#include "Manager.h"
#include <vector>

class PickUp;

class PickUpManager final : public Manager<PickUpManager>
{
public:
    PickUpManager() = default;
    ~PickUpManager() = default;
    PickUpManager(const PickUpManager& other) = delete;
    PickUpManager(PickUpManager&& other) = delete;
    PickUpManager& operator=(const PickUpManager& other) = delete;
    PickUpManager& operator=(PickUpManager&& other) = delete;

    void Draw() const;
    void Create(PickUp* PickUp);
    void Update(float elapsedSec);
    void Cleanup();

    std::vector<PickUp*>& GetBullets();

private:
    std::vector<PickUp*> m_pPickUpVector;
};