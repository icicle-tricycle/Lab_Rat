#include "Trap.h"

Trap::Trap(String m_sMeshName) : GameObject(m_sMeshName)
{
	GameObject::Init(m_sMeshName);
	b_isEnabled = true;
}

Trap::Trap(Trap const& other) : GameObject(other)
{
}

Trap & Trap::operator=(Trap const & other)
{
	if (this != &other)
	{
		Release();
		Init(other.m_sMeshName);
		Trap temp(other);
		Swap(temp);
	}
	return *this;
}

Trap::~Trap()
{

}

void Trap::Swap(Trap& other)
{

}

void Trap::SetEnabled(bool setTo) { b_isEnabled = setTo; }
bool Trap::GetEnabled() { return b_isEnabled; }
