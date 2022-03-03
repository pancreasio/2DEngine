#include "CollisionManager.h"

#include <iostream>


#include "Shape.h"
#include "Tilemap.h"

bool CollisionManager::CheckCollision(Shape shape1, Shape shape2)
{
	return (shape1.GetPosition().x - shape1.GetScale().x / 2 < shape2.GetPosition().x + shape2.GetScale().x / 2 &&
		shape1.GetPosition().x + shape1.GetScale().x / 2 > shape2.GetPosition().x - shape2.GetScale().x / 2 &&
		shape1.GetPosition().y - shape1.GetScale().y / 2 < shape2.GetPosition().y + shape2.GetScale().y / 2 &&
		shape1.GetPosition().y + shape1.GetScale().y / 2 > shape2.GetPosition().y - shape2.GetScale().y / 2);
}

bool CollisionManager::CheckCollision(Shape shape, Tilemap tilemap)
{
	for(int i=0; i< tilemap.GetSolidTileCount(); i++)
	{
		if (CheckCollision(shape, (Shape)*tilemap.GetSolidTile(i)))
		{
			return true;
		}
	}
	return  false;
}

bool CollisionManager::CheckCollisionOptimized(Shape shape, Tilemap tilemap)
{
	std::list<Tile*> tilesInRange = tilemap.GetSolidTilesOverlappingShape(shape);
	for (std::list<Tile*>::iterator it = tilesInRange.begin(); it != tilesInRange.end(); ++it)
	{
		if (CheckCollision(shape, (Shape)**it))
		{
			return true;
		}
	}
	return false;
}
