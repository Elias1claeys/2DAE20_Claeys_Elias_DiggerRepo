#include "SoundSystem.h"

namespace dae
{
	std::unique_ptr<SoundSystem> ServiceLocator::m_Instance = std::make_unique<NullSoundSystem>();
}