#include "pch.h"
#include "Boss.h"

Boss::Boss(Point2f centerPoint, float damage, float speed, float health)
	:Enemy{ centerPoint, damage, speed, health }
{
}
