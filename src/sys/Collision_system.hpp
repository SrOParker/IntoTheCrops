/*************************************************
************* COLLISION SYSTEM *****************
**************************************************/
#pragma once
#include "../man/utils/types.hpp"
struct EngineGL;
struct GLFWwindow;

enum Camera_Movementt {
    FORWARDD,
    BACKWARDD,
    LEFTT,
    RIGHTT
};

struct Collision_System {
	using SYSCMPs = Typelist<CCollision, CRenderGL, CPhysics>;
	using SYSTAGs = Typelist<TCollider>; // si hay algo que no se renderice podemos meter un tag para ello
    using STSTAGsCOLLISIONABLES = Typelist<TCollisionable>;
    using SYSTAG_ALL = Typelist<>;
    
    
    long unsigned int dialogo = 0;
    
    
    void initCollisions(Manentity_type& EM);
	void update(Manentity_type& EM, EngineGL& GL, GLFWwindow* window);
    void resetVariablesCollSys();

    
    private:
    void updateBoundingBoxes(Manentity_type& EM, EngineGL& GL);
    int  collisionAABB(CCollision& c, CCollision& c2);
    bool PressEToOpenDoor(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e, CRenderGL& r);
    bool PressEToBurn(GLFWwindow* window, Manentity_type& EM,EngineGL& GL, Entity& e);
    void CollisionWithWalls(EngineGL& GL, GLFWwindow* window, Manentity_type& EM, Entity& e);
    void CollisionWithPickable(GLFWwindow* window, Manentity_type& EM, Entity& object,EngineGL& GL);
    void CollisionWithSoundEvent(Manentity_type& EM, Entity& e2);
    void CollisionWithDoor(GLFWwindow* window, EngineGL& GL, Manentity_type& EM, Entity& e, Entity& e2, CRenderGL& r2);
    void CollisionWithBurnable(GLFWwindow* window, EngineGL& GL, Manentity_type& EM, Entity& e, Entity& e2, CRenderGL& r2);
    void CollisionWithReposition(Manentity_type& EM, EngineGL& GL, Entity& e, Entity& e2);
    void CollisionWithTransition(Manentity_type& EM, EngineGL& GL, Entity& e2);
    void CollisionWithDescription(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2);
    void CollisionWithWindowMailBox(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2);
    void CollisionWithMailBox(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2);
    void CollisionWithFuseBox(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2);
    void CollisionWithPhone(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2);
    void CollisionWithHouseInteractuable(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& object);
    void CollisionWithTombEvent(Manentity_type& EM, EngineGL& GL, Entity& e2);    
    void CollisionWithEnemyEvent(Manentity_type& EM, EngineGL& GL, Entity& e2);
    void CollisionWithTransitionY(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2);    
    void CollisionWithCodeLock(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2);
    void CollisionWithHatch(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2);
    void CollisionWithCar(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2);
    
    void DoAfterFarmerConversation(Manentity_type& EM, EngineGL& GL, Entity& farmer);
    void DoAfterTombEvent(Manentity_type& EM, EngineGL& GL, Entity& e2);    


    long unsigned int stop_E_pulsation{0};
    long unsigned int farmer_action{0};
    long unsigned int tomb_event{0};
    long unsigned int trampilla_abierta{0};
    long unsigned int puerta_principal{0};
};