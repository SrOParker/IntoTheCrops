
#pragma once

#include <iostream>


#include "Node.hpp"
#include "Node_Attack.hpp"
#include "Node_Chase.hpp"
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
//	       				stand by    (in range?)
//	       									
//	       						Attack		Chase
//
//

struct Node_InRange : Node{
	Node_InRange(Node_Attack& at, Node_Chase& c) noexcept : attack{at}, chase{c}{};


	void run(Manentity_type& EM, Entity& e, EngineGL& GL) noexcept override{
		//std::cout << "I'm Node_InRange!\n";
		//std::cout << "Calling Node_Candil children!\n"; 
		
		Entity const player = EM.getEntityArray()[0];

		float dist = distance(EM.getEntityCMP<CPhysics>(e).x, EM.getEntityCMP<CPhysics>(e).z, EM.getEntityCMP<CPhysics>(player).x, EM.getEntityCMP<CPhysics>(player).z);

		if(dist < 1.5)
			attack.run(EM, e, GL); 
		else	
			chase.run(EM, e, GL); 
	}

	Node& attack; 
	Node& chase;
};