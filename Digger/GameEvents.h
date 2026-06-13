#include "Event/Event.h"
#include "Audio/SoundSystem.h"

namespace dae {
	constexpr EventId PLAYER_MOVED = make_sdbm_hash("PlayerMoved");
	constexpr EventId TOOK_DAMAGE = make_sdbm_hash("TookDamage");
	constexpr EventId ENEMY_KILLED = make_sdbm_hash("KilledEnemy");
	constexpr EventId EMERALD_COLLECTED = make_sdbm_hash("EmeraldCollected");
	constexpr EventId GOLD_COLLECTED = make_sdbm_hash("GoldCollected");
	constexpr EventId BAG_COLLISION = make_sdbm_hash("BagCollision");
	constexpr EventId EMERALD_SPAWNED = make_sdbm_hash("EmeraldSpawned");
	constexpr EventId LEVEL_COMPLETED = make_sdbm_hash("LevelCompleted");
	constexpr EventId GAME_STARTED = make_sdbm_hash("GameStarted");


}