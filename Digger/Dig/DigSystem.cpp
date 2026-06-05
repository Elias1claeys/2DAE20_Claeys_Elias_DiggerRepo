#include "DigSystem.h"

namespace dae
{
	std::unique_ptr<DigSystem> DigLocator::m_Instance = std::make_unique<NullDigSystem>();
}