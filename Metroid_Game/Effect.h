#pragma once
#include "Component.h"
#include "Animation.h"

class GameObject;
class Texture;

class Effect final
{
public:
	Effect(GameObject* object);
	virtual ~Effect();

	virtual void Draw() const;
	virtual void Update(float elapsedSec);

private:
	Texture* m_pTexture;	
	GameObject* m_Object;

};

