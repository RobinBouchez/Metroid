#include "pch.h"
#include "Screen.h"
#include "Texture.h"

Screen::~Screen()
{
	delete m_pTexure;
	m_pTexure = nullptr;
}
