#pragma once


typedef struct tagVector3
{
	float x, y, z;

	tagVector3() : x(0), y(0), z(0) { };

	tagVector3(float _x, float _y)
		: x(_x), y(_y), z(0) { };

	tagVector3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z) { };

}Vector3;


typedef struct tagUser
{
	char* Name;
	Vector3 Position;

}User;