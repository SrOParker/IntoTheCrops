#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include "Node.hpp"
#include "../../man/SoundManager.hpp"
#include "../PathA/PathA.hpp"

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
//	       						Attack		(Chase)
//
//

struct Node_Chase : Node{
	Node_Chase() noexcept{};


	void run(Manentity_type& EM, Entity& e, EngineGL& GL) noexcept override{
		PathA solver;

		auto& player  	 	= EM.getEntityArray()[0];
		auto& cphyplayer 	= EM.getEntityCMP<CPhysics>(player);
		auto& cia 	   	 	= EM.getEntityCMP<CIA>(e);
		auto& patrol 	 	= cia.targets[cia.current];
		auto& cphyia   	 	= EM.getEntityCMP<CPhysics>(e);

		float distpatrol =  distance(cphyia.x, cphyia.z,  patrol.x,  patrol.z);
		float dist = distance(cphyia.x, cphyia.z,  cphyplayer.x,  cphyplayer.z);

		if(distpatrol > 15 && dist > cia.max_range ){
			cphyia.vx = (patrol.x - cphyia.x) * cia.max_vel;
			cphyia.vz = (patrol.z - cphyia.z) * cia.max_vel;
		}else{

			//velocidad máxima a la que va a llegar el enemigo:
			//se calcula la velocidad a la que se quiere llegar 
			//se resta la velocidad deseada a la velocidad actual

			float velocidad_deseadax = (cphyplayer.x - cphyia.x);
			float velocidad_deseadaz = (cphyplayer.z - cphyia.z);

			glm::vec3 dvel = glm::normalize( glm::vec3{ velocidad_deseadax, 0 , velocidad_deseadaz} ) ;

			dvel *= cia.max_vel;

			glm::vec3 steer { dvel.x - cphyia.vx,  0, dvel.z - cphyia.vz };

			cphyia.vx += steer.x*cia.max_vel;
			cphyia.vz += steer.z*cia.max_vel;

			//Steer calculates the movement forces isntead of flat velocity
		
			if( dist < 7 ){
				cphyia.vx += steer.x*0.05;
				cphyia.vz += steer.z*0.05;

				if(EM.getEntityCMP<CRenderGL>(e).modelMatrix.modelname.compare("run.dae")!=0)
				{
					EM.getEntityCMP<CRenderGL>(e).modelMatrix = Model("assets/animaciones/run.dae", glm::vec3(0, 0, 0));
					//EM.getEntityCMP<CRenderGL>(e).modelMatrix.Rotate(180,0,1,0);
					EM.getEntityCMP<CAnimation>(e).animation = Animation("assets/animaciones/run.dae", &EM.getEntityCMP<CRenderGL>(e).modelMatrix);
					EM.getEntityCMP<CAnimation>(e).animator = Animator(&EM.getEntityCMP<CAnimation>(e).animation);
 					rotateModel(EM, e, {cphyplayer.x, cphyplayer.z});
					//EM.getEntityCMP<CRenderGL>(e).modelMatrix.Rotate(180,0,1,0);

				}
				
				auto& csound = EM.getEntityCMP<CSound>(e);
				csound.eventvalue = 0.11;

				if(csound.eventvalue != 0.11)
					csound.s_mgr->setParameter("event:/Character/creepy", "close", csound.eventvalue );
		
			}

			//Calculo de la rotación del enemigo
			//vector al player
			//Node::rotateModel
			rotateModel(EM, e, {cphyplayer.x, cphyplayer.z});

			//Calcular la distancia a la que me encuentro de currenttarget, si me encuentro más lejos de x distancia volver a la patrulla. 
/*
	pathfinding
			std::vector< PathNode >*vec{};
			glm::vec2 vel_path; 
			if(EM.getLevelsStatus().actual == 3 || EM.getLevelsStatus().actual == 8 ){
				auto update_one_entity = [&](Entity& e, CMap& cmap){
					
					vec = &cmap.map;
				
				};
				EM.foreach<Typelist<CMap>,Typelist<>>(update_one_entity);
				solver.solve(*vec, {cphyia.x, cphyia.z}, {cphyplayer.x, cphyplayer. z});

			}
*/		
			//sacar el mapa de la entidad map y pasarla al solve
			
		}
	}
};