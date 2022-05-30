#pragma once

#include <iostream>
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
//	       				stand by    in range?
//	       									
//	       						(Attack)		Chase
//
//


struct Node_Attack : Node{
	Node_Attack() noexcept{};
	
	void run(Manentity_type& EM, Entity& e, EngineGL& GL) noexcept override{
		//std::cout << "I'm Node_Attack! (leaf)\n";
		//std::cout << "I ATTACK!!\n";
		EM.getEntityCMP<CPhysics>(e).vx = 0;
		EM.getEntityCMP<CPhysics>(e).vz = 0;
		auto& player = EM.getEntityArray()[0];
		auto& salute = EM.getEntityCMP<CHealth>(player);
		auto& cphyplayer = EM.getEntityCMP<CPhysics>(player);
		salute.health -= 0.7;
		//std::cout << EM.getEntityCMP<CRenderGL>(e).modelMatrix.modelname << "\n";

		if(EM.getEntityCMP<CRenderGL>(e).modelMatrix.modelname.compare("attack.dae")!=0)
		{
			EM.getEntityCMP<CRenderGL>(e).modelMatrix = Model("assets/animaciones/attack.dae", glm::vec3(0, 0, 0));
			EM.getEntityCMP<CAnimation>(e).animation = Animation("assets/animaciones/attack.dae", &EM.getEntityCMP<CRenderGL>(e).modelMatrix);
			EM.getEntityCMP<CAnimation>(e).animator = Animator(&EM.getEntityCMP<CAnimation>(e).animation);
			rotateModel(EM, e, {cphyplayer.x, cphyplayer.z});				
		}
	}
};