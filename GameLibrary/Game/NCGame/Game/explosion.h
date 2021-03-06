#pragma once
#include "scene.h"
#include "entity.h"
class Explosion : public Entity
{
public:
	enum eType
	{
	ENEMY,
	PLAYER
	};
public:
	Explosion(Scene* scene, const ID id) : Entity(scene, id){}
	~Explosion(){}

	void Create(const Vector2D & postion);
	void Update();

};

