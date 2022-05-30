#pragma once

#include <iostream>
#include "../../man/SoundManager.hpp"
#include "Node.hpp"

//								TREE STRUCTURE v2.0
//					Left branches = Yes |  Right branches = No
//                      
//                        (    The node you're in    )
//                                  
//                                                  
//	       							See Player
//	       									
//	       					candil on?		Wander 
//	       					       
//	       				(stand by)    in range?
//	       									
//	       						Attack		Chase
//
//

struct Node_StandBy : Node{
	Node_StandBy() noexcept{};

	void run(Manentity_type& EM, Entity& e, EngineGL& GL) noexcept override{
		//std::cout << "I'm Node_StandBy! (leaf)\n";
		//The enemy stops moving afraid by the light
		// Aqui se debería congelar la animación de movimiento del enemigo
		// Para hacer steering behaviour debería haber una deceleración
		//vf = v0 + at
		//vf = 0
		//a  = -v0/t
		auto& player = EM.getEntityArray()[0];
		auto& phy 	 = EM.getEntityCMP<CPhysics>(e);
		auto& csound = EM.getEntityCMP<CSound>(e);
		auto const velx  = (EM.getEntityCMP<CPhysics>(player).x - EM.getEntityCMP<CPhysics>(e).x)*0.005;
		auto const velz  = (EM.getEntityCMP<CPhysics>(player).z - EM.getEntityCMP<CPhysics>(e).z)*0.005;
		auto& cphyplayer = EM.getEntityCMP<CPhysics>(player); 
	
		csound.s_mgr->setParameter("event:/Character/creepy", "close", 0 );

		if(length(phy.vx, phy.vx, phy.vz, phy.vz) != 0 ){
			phy.vx = velx/5;
			phy.vz = velz/5;

		}else{
			phy.vx = 0;
			phy.vz = 0;
			if(EM.getEntityCMP<CRenderGL>(e).modelMatrix.modelname.compare("idle.dae")!=0)
			{
				EM.getEntityCMP<CRenderGL>(e).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
				rotateModel(EM, e, {cphyplayer.x, cphyplayer.z});
				EM.getEntityCMP<CAnimation>(e).animation = Animation("assets/animaciones/idle.dae", &EM.getEntityCMP<CRenderGL>(e).modelMatrix);
				EM.getEntityCMP<CAnimation>(e).animator = Animator(&EM.getEntityCMP<CAnimation>(e).animation);
				
			}
		}
	}
};