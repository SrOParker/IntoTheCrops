#pragma once

#include <iostream>
#include "Node.hpp"
#include "Node_StandBy.hpp"
#include "Node_InRange.hpp"
//								TREE STRUCTURE v2.0
//					Left branches = Yes |  Right branches = No
//                      
//                        (    The node you're in    )
//                                  
//                                                  
//	       							See Player
//	       									
//	       					(candil on?)		Wander 
//	       					       
//	       				stand by    in range?
//	       									
//	       						Attack		Chase
//
//


struct Node_Candil : Node{
	Node_Candil(Node_StandBy& st, Node_InRange& r) noexcept : stby{st}, range{r}{};
	
	void run(Manentity_type& EM, Entity& e, EngineGL& GL) noexcept override{
		//std::cout << "I'm Node_Candil!\n";
		//std::cout << "Calling Node_Candil children!\n";

		Entity& light = EM.getEntityArray()[2];
		bool isOn = EM.getEntityCMP<CPointLight>(light).isOn; 

		float dist = distance(EM.getEntityCMP<CPhysics>(e).x, EM.getEntityCMP<CPhysics>(e).z, EM.getEntityCMP<CPhysics>(light).x, EM.getEntityCMP<CPhysics>(light).z);
		
		auto& cphyia = EM.getEntityCMP<CPhysics>(e); 

		bool frustum = GL.camera.isOnFrustum({cphyia.x, cphyia.y, cphyia.z});

		if((frustum && !isOn) || (!frustum && !isOn) || (dist < 5 && !isOn) || (isOn && !frustum && dist > 5)){
			range.run(EM, e, GL);
		}else{
			stby.run(EM, e, GL); 
		}
	}
	
	Node& stby; 
	Node& range; 
};