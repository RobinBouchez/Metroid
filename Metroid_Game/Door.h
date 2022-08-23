#pragma once
#include "GameObject.h"

class Texture;

class Door final : public GameObject
{
public:
	Door();
	virtual ~Door() = default;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	bool Open();

private:
	Texture* m_pTexture;
	bool m_IsClosed;
};

