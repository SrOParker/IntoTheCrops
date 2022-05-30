/*************************************************
************* INFORMATION SYSTEM *****************
**************************************************/
#pragma once
#include "../man/utils/types.hpp"

struct InformationSystem {
	using SYSCMPs = Typelist<CInformation>;
	using SYSTAGs = Typelist<>;

	void update(Manentity_type& EM);
};