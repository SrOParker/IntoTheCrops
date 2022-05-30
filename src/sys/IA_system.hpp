/*************************************************
************* INFORMATION SYSTEM *****************
**************************************************/
#pragma once

#include "../engine/teosinteEngine.hpp"
#include "../man/utils/types.hpp"

struct IASystem {
	using SYSCMPs = Typelist<CIA>;
	using SYSTAGs = Typelist<>;
	IASystem();
	void update(Manentity_type& EM, EngineGL& GL);
};