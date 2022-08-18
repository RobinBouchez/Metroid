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

	const float GetHealth() const;
	void SetHealth(const float& value);

private:
	State m_State;

	float m_Health;
};

