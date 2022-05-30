#pragma once

#include <iostream>
#include <glm/vec3.hpp>
#include "Node.hpp"

//								TREE STRUCTURE v2.0
//					Left branches = Yes |  Right branches = No
//                      
//                        (    The node you're in    )
//                                  
//                                                  
//	       							See Player
//	       									
//	       					candil on?		(Wander) 
//	       					      
//	       				stand by    in range?
//	       									
//	       						Attack		Chase
//
//

struct Node_Wander : Node{
	Node_Wander() noexcept {};

	void runoent(Manentity_type &EM, Entity& e) noexcept {
		auto& phy	 = EM.getEntityCMP<CPhysics>(e);
		auto& cia	 = EM.getEntityCMP<CIA>(e);
 
 		if(cia.current >= cia.tot_patrol)
		 	cia.current = 0; 

		auto const& target = cia.targets[cia.current];
		if(target == cia.invalid){
			cia.current = 0; 
			return;
		}

		glm::vec3 const distance{ target.x - phy.x  , 0  ,  target.z - phy.z }; 
		float value = length(distance.x, distance.x, distance.z, distance.z);
		
		if(value < cia.arrival_radius)
			++cia.current; 
			
		phy.vx = glm::normalize(distance).x * 0.024;
		phy.vz = glm::normalize(distance).z * 0.024;
		if(EM.getEntityCMP<CRenderGL>(e).modelMatrix.modelname.compare("patrol.dae")!=0)
		{
			EM.getEntityCMP<CRenderGL>(e).modelMatrix = Model("assets/animaciones/patrol.dae", glm::vec3(0, 0, 0));
			rotateModel(EM, e, {cia.targets[cia.current].x, cia.targets[cia.current].z});
			EM.getEntityCMP<CAnimation>(e).animation = Animation("assets/animaciones/patrol.dae", &EM.getEntityCMP<CRenderGL>(e).modelMatrix);
			EM.getEntityCMP<CAnimation>(e).animator = Animator(&EM.getEntityCMP<CAnimation>(e).animation); 
		}

		rotateModel(EM, e, {cia.targets[cia.current].x,cia.targets[cia.current].z });
	}
	
	void run(Manentity_type& EM, Entity& e, EngineGL& GL) noexcept override{
		auto& phy = EM.getEntityCMP<CPhysics>(e);

		phy.vx = 0;
		phy.vz = 0;
		if(!e.hasTag<TNotPatrol>()){
			runoent(EM, e);
		}
		//por el momento el enemigo está estático
		//world->enemy->setPatrol();
	
	}
};