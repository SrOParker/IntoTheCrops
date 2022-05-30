#include "Sound_system.hpp"
#include "../man/SoundManager.hpp"
#include "../engine/teosinteEngine.hpp"
#include <glm/glm.hpp>
#include <iostream>

void Sound_system::update(Manentity_type& EM, EngineGL& GL){

    auto update_one_entity = [&](Entity& e, CSound& csound){
        
        csound.s_mgr->update(GL.camera.Position.x, GL.camera.Position.y, GL.camera.Position.z, GL.camera.Front , GL.camera.Up ); 
        
    };
    EM.foreach<SYSCMPs, SYSTAGs>(update_one_entity);
};
