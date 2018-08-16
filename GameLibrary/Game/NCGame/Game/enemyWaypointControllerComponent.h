#pragma once
#include "entity.h"
#include "controllerComponent.h"
#include <vector>
#include "_math.h"

class Waypoint;

class EnemyWaypointControllerComponent : public IControllerComponent
{
public:
	EnemyWaypointControllerComponent(Entity* sensei) : IControllerComponent(sensei) {}

	void Create(float speed, const std::vector<Vector2D>& points);
	void Destroy();
	void Update();

	void SetNextWaypoint();

protected:
	float m_speed = 0.0f;
	float m_timer = 0.0f;
	float m_fireRateMin = 1.0f;


	Waypoint* m_waypoint = nullptr;

	size_t m_waypointIndex = 0;
	std::vector<Waypoint*> m_waypoints;
	float m_fireRateMax = 3.0f;
};