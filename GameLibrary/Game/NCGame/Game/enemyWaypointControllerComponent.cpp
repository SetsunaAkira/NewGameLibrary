#include "enemyWaypointControllerComponent.h"
#include "timer.h"
#include "kinematicComponent.h"
#include "waypoint.h"
#include "debugdraw.h"

void EnemyWaypointControllerComponent::Create(float speed, const std::vector<Vector2D>& points)
{
	m_speed = speed;
	m_timer = Math::GetRandomRange(1.0f, 3.0f);

	for (Vector2D point : points)
	{
		Waypoint* waypoint = m_sensei->Getscene()->addEntity<Waypoint>();
		waypoint->Create(point, Vector2D(10.0f, 10.0f), m_sensei);
		m_waypoints.push_back(waypoint);
	}

	m_waypointIndex = 0;
	m_waypoint = m_waypoints[m_waypointIndex];
}

void EnemyWaypointControllerComponent::Destroy()
{
	for (Waypoint* waypoint : m_waypoints)
	{
		waypoint;
		m_waypoint->SetState(Entity::DESTROY);
	}
}

void EnemyWaypointControllerComponent::Update()
{
	if (m_sensei->Intersects(m_waypoint))
	{
		SetNextWaypoint();
	}

	DEBUG_DRAW_LINE(m_sensei->GetTransform().position, m_waypoint->GetTransform().position, Color::white);

	float dt = Timer::Instance()->DeltaTimer();

	Vector2D force = m_waypoint->GetTransform().position - m_sensei->GetTransform().position;
	force.Normalize();

	kinematicComponent* kinematic = m_sensei->GetComponent<kinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, kinematicComponent::VELOCITY);
	}

	float rotation = Vector2D::GetAngle(force) * Math::RadiansToDegrees - 90.0f;
	m_sensei->GetTransform().rotation = Math::Lerp(m_sensei->GetTransform().rotation, rotation, 5.0f * dt);

	
	/*m_timer = m_timer - dt;
	if (m_timer <= 0.0f)
	{
		m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);

		Missile* missile = new Missile(m_sensei->Getscene());
		missile->Create("enemymissile", m_sensei->GetTransform().position, Vector2D::up, 800.0f);
		m_sensei->Getscene()->addEntity(missile);
	}*/
}

void EnemyWaypointControllerComponent::SetNextWaypoint()
{
	m_waypointIndex++;
	if (m_waypointIndex < m_waypoints.size())
	{
		m_waypoint = m_waypoints[m_waypointIndex];
	}
	else
	{
		m_sensei->SetState(Entity::DESTROY);
	}
}
