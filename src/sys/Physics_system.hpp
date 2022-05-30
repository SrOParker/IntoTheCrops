#pragma once
#include "../man/utils/types.hpp"

struct PhysicsSystem {
	using SYSCMPs = Typelist<CPhysics>;
	using SYSTAGs = Typelist<>;
	
    PhysicsSystem();
    void update(Manentity_type& EM);
};