#pragma once

class Level 
{
public:
	Level() = default;
	Level(const float LevelHeight, const float Levelwidth);
	virtual ~Level() = default;

	virtual void Draw() const;
	virtual void Update(float elapsedSec);

private:


};

