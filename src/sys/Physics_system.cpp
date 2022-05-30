#include "Physics_system.hpp"
#include "../man/SoundManager.hpp"

//struct SoundManager; 

PhysicsSystem::PhysicsSystem(){}

void PhysicsSystem::update(Manentity_type& EM) {

    auto update_one_entity = [&](Entity& e, CPhysics& phy){
        
        phy.x += phy.vx;
        phy.y += phy.vy;
        phy.z += phy.vz;
        
        if (e.hasTag<TEnemy>() && !e.hasTag<TDummy>()){
            auto& sound = EM.getEntityCMP<CSound>(e);
            sound.s_mgr->set3DProp("event:/Character/creepy", phy.x, phy.y, phy.z);
        }
        
        //if(e.hasTag<TPlayer>())
        //    std::cout << phy.x << ":" << phy.z << "\n";
    };
    EM.foreach<SYSCMPs, SYSTAGs>(update_one_entity);

};

