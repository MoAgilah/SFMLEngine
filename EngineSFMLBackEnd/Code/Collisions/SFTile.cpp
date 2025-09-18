#include "SFTile.h"

#include "../Drawables/SFText.h"
#include "../Drawables/SFShape.h"
#include <Engine/Collisions/BoundingBox.h>
#include <Engine/Collisions/BoundingCircle.h>
#include <Engine/Collisions/BoundingCapsule.h>

SFTile::SFTile()
	: ITile(std::make_shared<BoundingBox<SFRect>>(), nullptr, nullptr)
{}

SFTile::SFTile(int gX, int gY, const std::string& fontName)
	: ITile(std::make_shared<BoundingBox<SFRect>>(), std::make_shared<SFText>(TextConfig(fontName)), nullptr)
{}

void SFTile::Render(IRenderer* renderer)
{
#if defined _DEBUG
	if (m_type == Types::DIAGU || m_type == Types::DIAGD)
	{
		if (m_slope)
		{
			auto triangle = dynamic_cast<SFTriangle*>(m_slope.get());
			if (triangle)
			{
				triangle->Render(renderer);
			}
		}
	}

	if (m_type == Types::LCRN || m_type == Types::RCRN)
	{
		auto* sfRenderer = dynamic_cast<SFRenderer*>(renderer);
		if (!sfRenderer)
			return;

		sf::RenderWindow* window = static_cast<sf::RenderWindow*>(sfRenderer->GetWindow()->GetNativeHandle());
		if (window)
		{
			sf::Vertex line[2];
			line[0].position = m_edge.start;
			line[0].color = Colour::Red;
			line[1].position = m_edge.end;
			line[1].color = Colour::Red;

			window->draw(line, 2, sf::PrimitiveType::Lines);
		}
	}

	m_aabb->Render(renderer);

	if (m_text)
		m_text->Render(renderer);
#endif
}

void SFTile::ResolveCollision(IDynamicGameObject* obj)
{
	Direction dir = obj->GetFacingDirection();
	Line tileTopEdge = m_aabb->GetSide(Side::Top);
	Vector2f objBottomPoint = obj->GetVolume()->GetPoint(Side::Bottom);

	switch (GetType())
	{
	case Types::OWAY:
	{
		if (dir == Direction::DDIR || dir == Direction::LDIR || dir == Direction::RDIR)
		{
			BoundingCapsule<SFCapsule> capsule(6, tileTopEdge);
			BoundingCircle<SFCircle> circle(4, obj->GetVolume()->GetPoint(Side::Bottom));
			if (static_cast<IBoundingVolume*>(&capsule)->Intersects(static_cast<IBoundingVolume*>(&circle)))
			{
				if (tileTopEdge.IsPointAboveLine(objBottomPoint))
					ResolveObjectToBoxTop(obj);
			}
		}
		return;
	}
	case Types::GRND:
		if (dir == Direction::DDIR || dir == Direction::LDIR || dir == Direction::RDIR)
		{
			if (tileTopEdge.IsPointAboveLine(objBottomPoint))
				ResolveObjectToBoxTop(obj);
		}
		return;
	case Types::LCRN:
		[[fallthrough]];
	case Types::RCRN:
	{
		Vector2f seperationVector = obj->GetVolume()->GetSeparationVector(static_cast<IBoundingVolume*>(m_aabb.get()));
		Direction colDir = Direction::LDIR; /*GetCollisionDirection(seperationVector, obj->GetVelocity(), Vector2f())*/;

		if (dir == Direction::DDIR)
		{
			// the collision came from a vertical direction
			if (colDir == Direction::DDIR)
			{
				if (tileTopEdge.IsPointAboveLine(objBottomPoint))
				{
					ResolveObjectToBoxTop(obj);
					return;
				}
			}
		}

		// the collision came from a horizontal direction
		if (colDir == Direction::LDIR || colDir == Direction::RDIR)
		{
			ResolveObjectToBoxHorizontally(obj);
		}
		else
		{
			if (dir == Direction::LDIR || dir == Direction::RDIR)
			{
				if (tileTopEdge.IsPointAboveLine(objBottomPoint))
				{
					ResolveObjectToBoxTop(obj);
				}

				ResolveObjectToEdgeBounds(obj);
			}
		}
		return;
	}
	case Types::WALL:
		ResolveObjectToBoxHorizontally(obj);
		return;
	case Types::DIAGU:
	{
		switch (dir)
		{
		case Direction::DDIR:
			if (ResolveObjectToSlopeTop(obj))
			{
				if (!obj->GetShouldSlideLeft())
					obj->SetShouldSlideLeft(true);
			}
			break;
		case Direction::RDIR:
			if (ResolveObjectToSlopeIncline(obj, 0, 1))
			{
				if (!obj->GetShouldSlideLeft())
					obj->SetShouldSlideLeft(true);
			}
			break;
		case Direction::LDIR:
			if (ResolveObjectToSlopeDecline(obj, 1, 0))
			{
				if (!obj->GetShouldSlideLeft())
					obj->SetShouldSlideLeft(true);
			}
			break;
		}
		return;
	}
	case Types::DIAGD:
	{
		switch (dir)
		{
		case Direction::DDIR:
			if (ResolveObjectToSlopeTop(obj))
			{
				if (!obj->GetShouldSlideRight())
					obj->SetShouldSlideRight(true);
			}
			break;
		case Direction::LDIR:
			if (ResolveObjectToSlopeIncline(obj, 1, 0))
			{
				if (!obj->GetShouldSlideRight())
					obj->SetShouldSlideRight(true);
			}
			break;
		case Direction::RDIR:
			if (ResolveObjectToSlopeDecline(obj, 0, 1))
			{
				if (!obj->GetShouldSlideRight())
					obj->SetShouldSlideRight(true);
			}
			break;
		}
		return;
	}
	}
}

void SFTile::SetPosition(const Vector2f& pos)
{
	m_aabb->Update(pos);

	switch (m_type)
	{
	case Types::DIAGU:
	{
		auto slope = std::make_shared<SFTriangle>();
		std::array<Vector2f, 3> points;
		points[0] = m_aabb->GetPosition() + Vector2f(-m_aabb->GetExtents().x, m_aabb->GetExtents().y);
		points[1] = m_aabb->GetPosition() + Vector2f(m_aabb->GetExtents().x, -m_aabb->GetExtents().y);
		points[2] = m_aabb->GetPosition() + m_aabb->GetExtents();
		slope->SetFillColour(Colour::Yellow);
		SetSlope(slope);
	}
		break;
	case Types::DIAGD:
	{
		auto slope = std::make_shared<SFTriangle>();
		std::array<Vector2f, 3> points;
		points[0] = m_aabb->GetPosition() - m_aabb->GetExtents();
		points[1] = m_aabb->GetPosition() + m_aabb->GetExtents();
		points[2] = m_aabb->GetPosition() - Vector2f(m_aabb->GetExtents().x, -m_aabb->GetExtents().y);
		slope->SetFillColour(Colour::Yellow);
		SetSlope(slope);
	}
		break;
	case Types::LCRN:
		m_edge.start = m_aabb->GetMin() + Vector2f(m_aabb->GetExtents().x * 2, 0);
		m_edge.end = m_edge.start - Vector2f(0, GetTileHeight());
		break;
	case Types::RCRN:
		m_edge.start = m_aabb->GetMin();
		m_edge.end = m_edge.start - Vector2f(0, GetTileHeight());
		break;
	}
}

void SFTile::SetFillColour(Colour col)
{
	auto sfAABB = dynamic_cast<BoundingBox<SFRect>*>(m_aabb.get());
	if (sfAABB)
	{
		sfAABB->GetShape()->SetFillColour(col);
	}
}

void SFTile::SetOutlineColour(Colour col)
{
	auto sfAABB = dynamic_cast<BoundingBox<SFRect>*>(m_aabb.get());
	if (sfAABB)
	{
		sfAABB->GetShape()->SetOutlineColour(col);
	}
}

void SFTile::ResolveObjectToBoxTop(IDynamicGameObject* obj)
{
	Vector2f seperationVector = GetSeperationVector(obj);

	obj->Move(0, -seperationVector.y);
	obj->SetOnGround(true);
	obj->SetOnSlope(false);
}

void SFTile::ResolveObjectToBoxBottom(IDynamicGameObject* obj)
{
	Vector2f seperationVector = GetSeperationVector(obj);

	obj->Move(0, seperationVector.y);
}

void SFTile::ResolveObjectToBoxHorizontally(IDynamicGameObject* obj)
{
	Vector2f seperationVector = GetSeperationVector(obj);

	obj->Move((obj->GetDirection() ? -1 : 1) * seperationVector.x, 0);
}

bool SFTile::ResolveObjectToSlopeTop(IDynamicGameObject* obj)
{
	/*Line line = GetSlope(0, 1);
	BoundingCircle circle(4, obj->GetColVolume()->GetPoint(Side::Bottom));

	if (line.IsPointAboveLine(circle.GetCenter()))
	{
		BoundingCapsule capsule(6, line);
		if (capsule.Intersects(static_cast<BoundingVolume*>(&circle)))
		{
			obj->SetOnSlope(true);
			return true;
		}
	}*/

	return false;
}

static float GetYOffSet(float pDistX, float lDistY, float slopeY, float currY, float tileHeight)
{
	auto percent = pDistX / lDistY;
	auto colHeight = lDistY * percent + slopeY;
	return ((currY - colHeight) / tileHeight);
}

bool SFTile::ResolveObjectToSlopeIncline(IDynamicGameObject* obj, int start, int end)
{
	/*Line line = GetSlope(start, end);
	BoundingCircle circle(4, obj->GetColVolume()->GetPoint(Side::Bottom));
	BoundingCapsule capsule(6, line);
	if (capsule.Intersects(static_cast<BoundingVolume*>(&circle)))
	{
		auto yOffset = GetYOffSet(start ? GetXDist(circle.GetCenter(), line.start) : GetXDist(line.start, circle.GetCenter()),
			line.DistY(),
			line.start.y,
			obj->GetBoundingBox()->GetPosition().y,
			GetTileHeight());

		obj->Move(0, yOffset);
		obj->SetOnSlope(true);

		return true;
	}*/

	return false;
}

bool SFTile::ResolveObjectToSlopeDecline(IDynamicGameObject* obj, int start, int end)
{
	/*Line line = GetSlope(start, end);
	BoundingCircle circle(4, obj->GetColVolume()->GetPoint(Side::Bottom));
	BoundingCapsule capsule(6, line);
	if (capsule.Intersects(static_cast<BoundingVolume*>(&circle)))
	{
		auto yOffset = GetYOffSet(start ? GetXDist(circle.GetCenter(), line.start) : GetXDist(line.start, circle.GetCenter()),
			line.DistY(),
			line.start.y,
			obj->GetBoundingBox()->GetPosition().y,
			GetTileHeight());

		obj->Move(0, -yOffset);
		obj->SetOnSlope(true);

		return true;
	}*/

	return false;
}

void SFTile::ResolveObjectToEdgeBounds(IDynamicGameObject* obj)
{
	/*if (IsPlayerObject(obj->GetID()))
		return;

	Vector2f side;
	if (m_type == Types::LCRN)
		side = obj->GetBoundingBox()->GetPoint(Side::Right);
	else
		side = obj->GetBoundingBox()->GetPoint(Side::Left);

	Line edge = GetEdge();

	if (pnt::IsMovingTowards(edge.start, side, Vector2f(0, 0), obj->GetVelocity()))
	{
		BoundingCircle circle(4, side);
		BoundingCapsule capsule(4, edge);
		if (capsule.Intersects(static_cast<BoundingVolume*>(&circle)))
			obj->SetDirection(!obj->GetDirection());
	}*/
}