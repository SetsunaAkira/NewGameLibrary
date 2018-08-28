#pragma once
#include "entity.h"
#include "controllerComponent.h"
#include <vector>
#include "_math.h"
#include "engine.h"

class Waypoint;

class ENGINE_API WaypointControllerComponent : public IControllerComponent
{
public:
	WaypointControllerComponent(Entity* sensei) : IControllerComponent(sensei) {}

	void Create(float speed, const std::vector<Vector2D>& points, float turnRate, bool setPositionAtStart);
	void Destroy();
	void Update();

	void SetNextWaypoint();
	bool isComplete() { return m_isComplete; }

protected:
	bool m_isComplete = false;
	float m_speed = 0.0f;
	float m_timer = 0.0f;
	float m_fireRateMin = 1.0f;
	float m_turnRate = 0.0f;


	Waypoint* m_waypoint = nullptr;

	size_t m_waypointIndex = 0;
	std::vector<Waypoint*> m_waypoints;
	float m_fireRateMax = 3.0f;
};