#pragma once

class Vitals final
{
public:
	enum class State
	{
		alive,
		dead
	};

public:
	Vitals(const float& health);
	~Vitals();

	void Update(float elapsedSec);

	const float GetHealth() const;
	void SetHealth(const float& value);
	void TakeDamage(const float& damage);

	State m_State;

private:
	bool m_TakenDamage;
	float m_InvinsibleTimer;
	float m_InvinsibleDuration;
	float m_Health;
};

