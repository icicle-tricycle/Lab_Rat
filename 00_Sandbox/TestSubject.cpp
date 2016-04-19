#include "TestSubject.h"

TestSubject::TestSubject(matrix4 posi)
{
	position = posi;
	velocity = vector3(1.0f, 0.0f, 0.0f);
	acceleration = vector3(0.0f, 0.0f, 0.0f);
}
TestSubject::TestSubject(TestSubject const & other) { }
TestSubject & TestSubject::operator=(TestSubject const & other) { return *this; }
TestSubject::~TestSubject() { }

void TestSubject::Update()
{
	position += glm::translate(velocity);
}
