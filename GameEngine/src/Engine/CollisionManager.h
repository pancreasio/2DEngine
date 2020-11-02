#ifndef COLISIONMANAGER_H
#define COLISIONMANAGER_H

class Shape;

#define EXPORTDLL _declspec(dllexport)

class EXPORTDLL CollisionManager
{
public:
	CollisionManager() {};
	~CollisionManager() {};
	bool CheckCollision(Shape shape1, Shape shape2);
};

#endif
