/*************************************************
************* Sound SYSTEM ***********************
**************************************************/

#pragma once
#include "../man/utils/types.hpp"


struct EngineGL;
struct Sound_system {
	using SYSCMPs = Typelist<CSound>;
	using SYSTAGs = Typelist<>; // si hay algo que no se renderice podemos meter un tag para ello
      
	void update(Manentity_type& EM, EngineGL& GL);
    
};