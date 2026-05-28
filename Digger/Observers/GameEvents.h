#include "Event/Event.h"

namespace dae {
	constexpr EventId PLAYER_MOVED = make_sdbm_hash("PlayerMoved");
	constexpr EventId TOOK_DAMAGE = make_sdbm_hash("TookDamage");
	constexpr EventId ENEMY_KILLED = make_sdbm_hash("KilledEnemy");
	constexpr EventId EMERALD_COLLECTED = make_sdbm_hash("EmeraldCollected");
	constexpr EventId GOLD_COLLECTED = make_sdbm_hash("GoldCollected");
}