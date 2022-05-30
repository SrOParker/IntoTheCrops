/*************************************************
**************** INPUT SYSTEM ********************
**************************************************/


#pragma once
#include "../man/utils/types.hpp"

struct EngineGL;
struct GLFWwindow;
struct InputSystem {
    using SYSCMPs   = Typelist<CInput, CPhysics, CRenderGL>;
	using SYSTAGs   = Typelist<TPlayer>;
    using SYSTAGsIA = Typelist<TEnemy>;

    int click_left;// 0 dont pressed
    int key_tab;


    InputSystem();
    void update(GLFWwindow* window, Manentity_type& EM, EngineGL& GL);
    void processMovement(GLFWwindow *window, Manentity_type& man_e, EngineGL& GL, CPhysics& phy, CRenderGL& rend);
    void resetPlayerVelocity(Manentity_type& EM);
    void check_pressed(GLFWwindow* window, EngineGL& GL);
    void checkCharge(GLFWwindow* window, EngineGL& GL);
    
    void MoveCamera(Manentity_type& man_e, EngineGL& GL);

};