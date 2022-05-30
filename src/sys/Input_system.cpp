#include "Input_system.hpp"
#include "../engine/teosinteEngine.hpp"
#include "../man/SoundManager.hpp"
#include <GLFW/glfw3.h>

struct SoundManager; 
InputSystem::InputSystem(){
    key_tab = click_left = 0;
}


void InputSystem::update(GLFWwindow* window, Manentity_type& EM, EngineGL& GL) {
    auto update_one_entity = [&](Entity& e, CInput& cinp, CPhysics& phy, CRenderGL& rend){
        processMovement(window, EM, GL, phy, rend);
    };
	EM.foreach<SYSCMPs, SYSTAGs>(update_one_entity);
    check_pressed(window, GL);
};

void InputSystem::check_pressed(GLFWwindow* window, EngineGL& GL){

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        click_left = 1;
    }else{
        click_left = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS){
        key_tab = 1;
    }else{
        key_tab = 0;
    }

    if (GL.camera.last_q == 1){     //last 0 1 0    lastlast 0 1
        GL.camera.last_last_q = 1;
    }else{
        GL.camera.last_last_q = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        GL.camera.last_q = 1; 
    }else{
        GL.camera.last_q = 0;
    }

    GL.camera.pressed_q = 0;




    if (GL.camera.pressed_space == 1){     //last 0 1 0    lastlast 0 1
        GL.camera.last_pressed_space= 1;
    }else{
        GL.camera.last_pressed_space= 0;
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        GL.camera.pressed_space = 1;
    }else{
        GL.camera.pressed_space = 0;
    }
}

void InputSystem::processMovement(GLFWwindow *window, Manentity_type& man_e, EngineGL& GL, CPhysics& phy, CRenderGL& rend){
    auto& candil_light_physics = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[2]);
    auto& coll                 = man_e.getEntityCMP<CCollision>(man_e.getEntityArray()[0]); 
    //auto& stamina              = man_e.getEntityCMP<CStamina>(man_e.getEntityArray()[0]); 
    auto& steps                = man_e.getEntityCMP<CSound>(man_e.getEntityArray()[0]);
    auto& lights               = man_e.getEntityCMP<CSound>(man_e.getEntityArray()[2]);
    //bool doublee = false;
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        GL.camera.ProcessKeyboardDouble(FORWARD,LEFT, GL.deltaTime, phy, coll, candil_light_physics);
        //steps.s_mgr->walking(true, 1);

    }else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        GL.camera.ProcessKeyboardDouble(FORWARD,RIGHT, GL.deltaTime, phy, coll, candil_light_physics);
       // steps.s_mgr->walking(true, 1);
    }else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        GL.camera.ProcessKeyboardDouble(BACKWARD,LEFT, GL.deltaTime, phy, coll, candil_light_physics);
        //steps.s_mgr->walking(true, 1);
    }else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        GL.camera.ProcessKeyboardDouble(BACKWARD,RIGHT, GL.deltaTime, phy, coll, candil_light_physics);
    }else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        GL.camera.ProcessKeyboard(FORWARD, GL.deltaTime, phy, coll, candil_light_physics);
    }else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        GL.camera.ProcessKeyboard(BACKWARD, GL.deltaTime, phy, coll, candil_light_physics);
    }else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        GL.camera.ProcessKeyboard(LEFT, GL.deltaTime, phy, coll, candil_light_physics);
    }else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        GL.camera.ProcessKeyboard(RIGHT, GL.deltaTime, phy, coll, candil_light_physics);  
    }
    //if(stamina.stamina <= 100)
    //    stamina.stamina += 0.2;
    //if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    //    
    //    if(stamina.stamina > 0){
    //        GL.camera.ProcessKeyboardDouble(FORWARD, FORWARD, GL.deltaTime, phy, coll, candil_light_physics);
    //        stamina.stamina -= 1;
    //    }
    //    
    //}

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE){
        steps.s_mgr->walking(true, 1);
    }
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        
        if (click_left == 0 && GL.camera.LanternIsHeld){
            auto& ent = man_e.getEntityArray()[2];
            auto& light = man_e.getEntityCMP<CPointLight>(ent);
            
            if (light.isOn){
                light.setOff();
                lights.s_mgr->setParameter("event:/Character/Fire (Oil)", "Progreso", 10 );
            }else{
                if(man_e.getEntityCMP<CHealth>(man_e.getEntityArray()[2]).health > 0) {

                    light.setOnLamp();
                    lights.s_mgr->playSound("event:/Character/Fire (Oil)");
                    lights.s_mgr->setParameter("event:/Character/Fire (Oil)", "Progreso", 0 );
                }
            }
        }
    }
    
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        if (GL.camera.last_last_q == 0 && GL.camera.last_q == 1 && GL.camera.pressed_q == 0){
             //std::cout << "LAST: "<< GL.camera.last_q << "LASTLAST: " << GL.camera.last_last_q << " input system \n";
            if(GL.camera.LanternIsHeld){
                GL.camera.pressed_q = 1;
                man_e.getEntityArray()[2].eraseTag<TPlayer>();
                man_e.getEntityArray()[2].addTag<Tpickable>();
                man_e.getEntityArray()[1].addTag<TNotRenderizable>();
                man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[2]).y = 0;
                
                GL.camera.LanternIsHeld=false;
            }
        }
    }

    
    
    //glm::mat4 MVP4 = ProjectionMatrix * ViewMatrix * (ModelMatrix4 * glm::inverse(ViewMatrix));
    //rend.modelMatrix.nodeMatrix = rend.modelMatrix.nodeMatrix * GL.camera.GetViewMatrix() ; 
    
    //rend.modelMatrix.nodeMatrix *= GL.camera.GetViewMatrix();
    //rend.modelMatrix.Rotate(1, 1, 1, 1);
}
    

void InputSystem::resetPlayerVelocity(Manentity_type& EM){
    auto&   e = EM.getEntityArray()[0];
    auto& cmp = EM.getEntityCMP<CPhysics>(e);

    cmp.vx = 0; cmp.vy = 0; cmp.vz = 0;
}

void InputSystem::MoveCamera(Manentity_type& man_e, EngineGL& GL){
    //auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
	//GL.camera.Position = glm::vec3(GL., player_phy.y, player_phy.z);
    GL.camera.movement = false;
}

void InputSystem::checkCharge(GLFWwindow* window, EngineGL& GL){
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        GL.camera.charge_plane = 0;
    }
}