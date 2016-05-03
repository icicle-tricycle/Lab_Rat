#include "Trap.h"

Trap::Trap(String m_sMeshName) : GameObject(m_sMeshName)
{
	b_isEnabled = true;
}

Trap::Trap(Trap const& other) : GameObject(other)
{
}

Trap & Trap::operator=(Trap const & other)
{

}

Trap::~Trap()
{

}

void Trap::Swap(Trap& other)
{

}

void SetEnabled(bool setTo) { b_isEnabled = setTo; }
bool GetEnabled() { return b_isEnabled; }
