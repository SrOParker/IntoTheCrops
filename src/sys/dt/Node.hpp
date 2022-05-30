#pragma once

#include "../../man/utils/types.hpp"
#include "../../engine/teosinteEngine.hpp"
struct Node {  // This class represents each node in the decision tree.

	virtual void run(Manentity_type& EM, Entity& e, EngineGL& GL) noexcept = 0;

	virtual ~Node() noexcept = default;

	float distance(int x1, int y1, int x2, int y2) noexcept{ return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2) * 1.0);}
	float length(int x1, int z1, int x2, int z2) noexcept { return std::sqrt(x1*z1 + x2*z2); };

	float dotprod(glm::vec3 a, glm::vec3 b){ return (a.x* b.x) + (a.z*b.z);}

	void rotateModel(Manentity_type& EM, Entity& e, glm::vec2 targetpos) noexcept{

		auto& cia 	   	 	= EM.getEntityCMP<CIA>(e);
		auto& cphyia   	 	= EM.getEntityCMP<CPhysics>(e);
		auto& crenderEnemy  = EM.getEntityCMP<CRenderGL>(e);
		
		float velocidad_deseadax = (targetpos.x - cphyia.x);
		float velocidad_deseadaz = (targetpos.y - cphyia.z);

		glm::vec3 dir { velocidad_deseadax, 0 , velocidad_deseadaz };
		glm::vec3 act = cia.face;

		//  dot product
		double dot   = (dir.x * act.x) + (dir.z * act.z);
		//  cross product
		double cross = (dir.x * act.z) - (dir.z * act.x); 
		
		float angle = atan2( cross , dot );

		angle = angle * 180 / 3.14;
		crenderEnemy.modelMatrix.nodeMatrix = cia.origin;
		crenderEnemy.modelMatrix.Rotate(angle, 0, 1, 0);


	};
};