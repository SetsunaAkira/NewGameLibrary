#pragma once
#include "scene.h"
#include "entity.h"
class EnemyExplosion : public Entity
{
public:
	EnemyExplosion(Scene* scene, const ID id) : Entity(scene, id){}
	~EnemyExplosion(){}

	void Create(const Vector2D & postion);
	void Update();

};

