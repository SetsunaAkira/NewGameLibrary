#include "WaypointControllerComponent.h"
#include "timer.h"
#include "kinematicComponent.h"
#include "waypoint.h"
#include "debugdraw.h"

void WaypointControllerComponent::Create(float speed, const std::vector<Vector2D>& points)
{
	m_speed = speed;
	m_timer = Math::GetRandomRange(1.0f, 3.0f);

	for (Vector2D point : points)
	{
		Waypoint* waypoint = m_sensei->Getscene()->addEntity<Waypoint>();
		waypoint->Create(point, Vector2D(30.0f, 30.0f), m_sensei);
		m_waypoints.push_back(waypoint);
	}

	m_waypointIndex = 0;
	m_waypoint = m_waypoints[m_waypointIndex];
}

void WaypointControllerComponent::Destroy()
{
	for (Waypoint* waypoint : m_waypoints)
	{
		waypoint;
		m_waypoint->SetState(Entity::DESTROY);
	}
}

void WaypointControllerComponent::Update()
{
	if (m_sensei->Intersects(m_waypoint))
	{
		SetNextWaypoint();
	}

	DEBUG_DRAW_LINE(m_sensei->GetTransform().position, m_waypoint->GetTransform().position, Color::white);

	float dt = Timer::Instance()->DeltaTimer();
	Vector2D direction = m_waypoint->GetTransform().position - m_sensei->GetTransform().position;
	float rotation = (Vector2D::GetAngle(direction) * Math::RadiansToDegrees + 90.0f);
	m_sensei->GetTransform().rotation = Math::LerpDegrees(m_sensei->GetTransform().rotation, rotation, 5.0f * dt);

	Vector2D force = Vector2D::Rotate(Vector2D::up, m_sensei->GetTransform().rotation * Math::DegreesToRadians + Math::PI);

	kinematicComponent* kinematic = m_sensei->GetComponent<kinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, kinematicComponent::VELOCITY);
	}
}

void WaypointControllerComponent::SetNextWaypoint()
{
	m_waypointIndex++;
	if (m_waypointIndex < m_waypoints.size())
	{
		m_waypoint = m_waypoints[m_waypointIndex];
	}
	else
	{
		m_isComplete = true;
		m_waypointIndex = 0;
		m_waypoint = m_waypoints[m_waypointIndex];
	}
}
