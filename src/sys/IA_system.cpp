#include "IA_system.hpp"
#include "dt/dt.hpp"



IASystem::IASystem(){}

void IASystem::update(Manentity_type& EM, EngineGL& GL){
    
    auto update_one_entity = [&](Entity& e, CIA& cia){
        if (!e.hasTag<TDummy>()){
            cia.dt->run(EM, e, GL);
        } 
        
    };
    EM.foreach<SYSCMPs,SYSTAGs>(update_one_entity);
};