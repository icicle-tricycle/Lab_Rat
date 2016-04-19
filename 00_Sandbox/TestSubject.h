#pragma once
#include "gameobject.h"
#include "RE\ReEng.h"

class TestSubject :
	public GameObject
{
public:
	//Rule of 3
	TestSubject(matrix4 posi);
	TestSubject(TestSubject const& other);
	TestSubject& operator=(TestSubject const& other);
	~TestSubject();

	void Update();
};

