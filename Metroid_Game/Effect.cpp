#include "pch.h"
#include "Effect.h"
#include "Animation.h"

Effect::Effect()
	: m_pAnimation{ nullptr }
{
}

Effect::~Effect()
{
	delete  m_pAnimation;
	m_pAnimation = nullptr;
}
