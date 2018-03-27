#pragma once

class CharacterFactory
{

};

struct FrameData
{
	Vector2 idleFrames;
	Vector2 leftFrames;
	Vector2 rightFrames;
	Vector2 downFrames;
	Vector2 upFrames;
	Vector2 deathFrames;
};

class character
{
public:
	character(SpriteSheet* sprite, FrameData frameInfo)
	{
		this->sprite = sprite;
		this->frameInfo = frameInfo;
		bool alive = true;
	}
	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void ChangeFrames(int32) = 0;

private:
	SpriteSheet* sprite;
	FrameData frameInfo;
	bool alive;
};

class NPCharacter : public character
{
public:
	virtual void Move() = 0;
	virtual void Attack() = 0;

};

