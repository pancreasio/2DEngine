#ifndef COLISIONMANAGER_H
#define COLISIONMANAGER_H

class Shape;
class Tilemap;
#define EXPORTDLL _declspec(dllexport)

class EXPORTDLL CollisionManager
{
public:
	CollisionManager() {};
	~CollisionManager() {};
	bool CheckCollision(Shape shape1, Shape shape2);
	bool CheckCollision(Shape shape, Tilemap tilemap);
	bool CheckCollisionOptimized(Shape shape, Tilemap tilemap);
};

#endif
