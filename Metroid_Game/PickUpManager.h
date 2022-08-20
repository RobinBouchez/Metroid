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

    template<typename T>
    std::enable_if_t<std::is_base_of_v<PickUp, T>, T*> Create(T* newPickUp);
    void IsPlayerOverlapping(const Rectf& player);
    void Update(float elapsedSec);
    void Cleanup();

    std::vector<PickUp*>& GetPickUps();

private:
    std::vector<PickUp*> m_pPickUpVector;
};

template<typename T>
inline std::enable_if_t<std::is_base_of_v<PickUp, T>, T*> PickUpManager::Create(T* newPickUp)
{
    m_pPickUpVector.push_back(newPickUp);
    return newPickUp;
}
