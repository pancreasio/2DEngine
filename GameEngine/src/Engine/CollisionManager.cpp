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
	for(int i=0; i< tilemap.GetTileCount(); i++)
	{
		if (tilemap.GetTile(i)->isSolid && CheckCollision(shape, (Shape)*tilemap.GetTile(i)))
		{
			return true;
		}
	}
	return  false;
}
