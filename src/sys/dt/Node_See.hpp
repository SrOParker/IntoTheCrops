#pragma once

#include <iostream>

#include "Node.hpp"
#include "Node_Candil.hpp"
#include "Node_Wander.hpp"

//								TREE STRUCTURE v2.0
//					Left branches = Yes |  Right branches = No
//                      
//                        (    The node you're in    )
//                                  
//                                                  
//	       							(See Player)
//	       									
//	       					candil on?		Wander 
//	       					       
//	       				stand by    in range?
//	       									
//	       						Attack		Chase
//
//

struct Node_See : Node{
	
	Node_See(Node_Candil &c, Node_Wander &w) noexcept : candil{c}, wander{w}{};
	//Node used to decide if enemy is in range to see the player

	void run(Manentity_type& EM, Entity& e, EngineGL& GL) noexcept override{
		//std::cout << "I'm Node_See!\n"; 
		//std::cout << "Calling Node_See children!\n"; 
		Entity& player = EM.getEntityArray()[0];
		auto& cia = EM.getEntityCMP<CIA>(e); 
		float xp = EM.getEntityCMP<CPhysics>(player).x;
		float zp = EM.getEntityCMP<CPhysics>(player).z;

		float xe = EM.getEntityCMP<CPhysics>(e).x;
		float ze = EM.getEntityCMP<CPhysics>(e).z;

		float dist = distance(xe, ze, xp, zp);

		//LOD
		if(dist > 20){
			EM.setIATime(1/5);
		}else{
			EM.setIATime(1/10);
		}

		if(dist < cia.max_range)
			candil.run(EM, e, GL);
		else
			wander.run(EM, e, GL);
		
	}
	private:
		Node& candil;
		Node& wander;
	
};
