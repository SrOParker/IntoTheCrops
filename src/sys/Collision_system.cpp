#include "Collision_system.hpp"
#include "../engine/teosinteEngine.hpp"
#include "../man/SoundManager.hpp"
#include "../Levels.hpp"
#include "../man/St_Manager/St_Manager.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void Collision_System::initCollisions(Manentity_type& EM){
    Point bb_helper_min{};
    Point bb_helper_max{};
    Point bb_helper_init_min{};
    Point bb_helper_init_max{};
    auto update_one_entity = [&](Entity& e, CCollision& c, CRenderGL& r, CPhysics& phy){
        //std::cout << "Entidad iniciada : " << e.getID() << "\n"; 
        for (int i = 0; i < (int)r.modelMatrix.meshes.size(); ++i){
            for (int j= 1; j < (int)r.modelMatrix.meshes[i].vertices.size(); ++j){
                auto& V = r.modelMatrix.meshes[i].vertices[j].Position;
                if(V.x < c.min.x) c.min.x = V.x;
                if(V.y < c.min.y) c.min.y = V.y;
                if(V.z < c.min.z) c.min.z = V.z;
                if(V.x > c.max.x) c.max.x = V.x;
                if(V.y > c.max.y) c.max.y = V.y;
                if(V.z > c.max.z) c.max.z = V.z;
            }
        }

        if(e.hasTag<TScaleBoundingBox>()){
            c.min.x -= 1; c.min.y -= 1; c.min.z -= 1;
            c.max.x += 1; c.max.y += 1; c.max.z += 1;

            c.minInit.x = c.min.x; c.minInit.y = c.min.y; c.minInit.z = c.min.z;
            c.maxInit.x = c.max.x; c.maxInit.y = c.max.y; c.maxInit.z = c.max.z;
            c.min.x += phy.x; 
            c.min.y += phy.y;
            c.min.z += phy.z;
            c.max.x += phy.x;
            c.max.y += phy.y;
            c.max.z += phy.z;

        }else if(e.hasTag<TEnemy>()){
            c.min.x += 0.85; c.min.y += 0.85; c.min.z += 0.85;
            c.max.x -= 0.85; c.max.y -= 0.85; c.max.z -= 0.85;

            c.minInit.x = c.min.x; c.minInit.y = c.min.y; c.minInit.z = c.min.z;
            c.maxInit.x = c.max.x; c.maxInit.y = c.max.y; c.maxInit.z = c.max.z;
            c.min.x += phy.x; 
            c.min.y += phy.y;
            c.min.z += phy.z;
            c.max.x += phy.x;
            c.max.y += phy.y;
            c.max.z += phy.z;
        }else{
            c.minInit.x = c.min.x; c.minInit.y = c.min.y; c.minInit.z = c.min.z;
            c.maxInit.x = c.max.x; c.maxInit.y = c.max.y; c.maxInit.z = c.max.z;
            c.min.x += phy.x; 
            c.min.y += phy.y;
            c.min.z += phy.z;
            c.max.x += phy.x;
            c.max.y += phy.y;
            c.max.z += phy.z;
        }

        if (e.hasTag<TBoundingBoxHelp>()){
            bb_helper_min = c.min; 
            bb_helper_max = c.max; 
            bb_helper_init_min = c.minInit;
            bb_helper_init_max = c.maxInit;

        }

    };
	EM.foreach<SYSCMPs, SYSTAG_ALL>(update_one_entity);
}

void Collision_System::update(Manentity_type& EM, EngineGL& GL, GLFWwindow* window){
    updateBoundingBoxes(EM, GL);

    auto update_one_entity = [&](Entity& e, CCollision& c,  CRenderGL& r, CPhysics& phy){
        auto catch_entity = [&](Entity& e2, CCollision& c2, CRenderGL& r2, CPhysics& phy2){

            if (collisionAABB(c, c2) == 1){ //hay colision
                if (e2.hasTag<TWall>() && !e2.hasTag<TDoor>()){           
                    CollisionWithWalls(GL, window, EM, e);
                    GL.camera.colision = true;
                }else if (e2.hasTag<Tpickable>()) {
                    CollisionWithPickable(window, EM, e2, GL);
                }else if (e2.hasTag<TSEvent>()) {
                    CollisionWithSoundEvent(EM, e2);
                }else if (e2.hasTag<TDoor>()){
                    CollisionWithDoor(window,GL, EM, e, e2, r2);
                }else if (e2.hasTag<TBurnable>()){
                    CollisionWithBurnable(window,GL, EM, e, e2, r2);
                }else if (e2.hasTag<TTransition>()){
                    CollisionWithTransition(EM, GL, e2);
                }else if (e2.hasTag<TObjectInteractuable>()){
                    CollisionWithHouseInteractuable(window, EM, GL, e2);
                }else if (e2.hasTag<TReposition>()){
                    CollisionWithReposition(EM, GL, e, e2);
                }else if (e2.hasTag<TWindowMailBox>()){
                    CollisionWithWindowMailBox(window, EM, GL, e2);
                }else if (e2.hasTag<TMailBox>()){
                    CollisionWithMailBox(window, EM, GL, e2);
                }else if (e2.hasTag<TFuseBox>()){
                    CollisionWithFuseBox(window, EM, GL, e2);
                }else if (e2.hasTag<TPhone>()){
                    CollisionWithPhone(window, EM, GL, e2);
                }else if (e2.hasTag<TTombEvent>()){
                    CollisionWithTombEvent(EM,GL,e2);
                }else if (e2.hasTag<TEnemyEvent>()){
                    CollisionWithEnemyEvent(EM,GL,e2);
                }else if (e2.hasTag<TTransitionY>()){
                    CollisionWithTransitionY(window, EM,GL,e2);
                }else if (e2.hasTag<TCodeLock>()){
                    CollisionWithCodeLock(window, EM,GL,e2);
                }else if (e2.hasTag<THatch>()){
                    CollisionWithHatch(window, EM,GL,e2);
                }else if (e2.hasTag<TCarEventFinal>()){
                    CollisionWithCar(window, EM,GL,e2);
                }

                if(e2.hasTag<TDescription>()){
                    CollisionWithDescription(window,EM,GL, e2);
                } 
                
            }else{
                GL.camera.colision = false;
            }

        };
        EM.foreach<SYSCMPs,STSTAGsCOLLISIONABLES>(catch_entity);
    };
	EM.foreach<SYSCMPs, SYSTAGs>(update_one_entity);


    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE){
        stop_E_pulsation = 0;
    }
}

int  Collision_System::collisionAABB(CCollision& c, CCollision& c2){
    // Exit with no intersection if separated along an axis
    if (c.max.x < c2.min.x || c.min.x > c2.max.x ) return 0;
    if (c.max.y < c2.min.y || c.min.y > c2.max.y ) return 0;
    if (c.max.z < c2.min.z || c.min.z > c2.max.z ) return 0;
    // Overlapping on all axes means AABBs are intersecting
    return 1;
}

void Collision_System::updateBoundingBoxes(Manentity_type& EM, EngineGL& GL){
    using rend= Typelist<CCollision, CRenderGL, CPhysics>;
	using tags = Typelist<>;
    auto updateBB = [&](Entity& e,CCollision& c, CRenderGL& r, CPhysics& phy){
        if (!e.hasTag<TPlayer>()){
            //para el enemigo, tag enemy
            if(e.hasTag<TEnemy>()){
                if(phy.vx != 0 || phy.vz != 0){
                    c.min.x = c.minInit.x + phy.x;
                    c.min.y = c.minInit.y + phy.y;
                    c.min.z = c.minInit.z + phy.z;
                    c.max.x = c.maxInit.x + phy.x;
                    c.max.y = c.maxInit.y + phy.y;
                    c.max.z = c.maxInit.z + phy.z;
                }
            }
        }else{
            if ((GL.camera.movement = true)){
                c.min.x = c.minInit.x + phy.x;
                c.min.y = c.minInit.y + phy.y;
                c.min.z = c.minInit.z + phy.z;
                c.max.x = c.maxInit.x + phy.x;
                c.max.y = c.maxInit.y + phy.y;
                c.max.z = c.maxInit.z + phy.z;
            }
        }
    };
    EM.foreach<rend, tags>(updateBB);

}

void Collision_System::CollisionWithWalls(EngineGL& GL, GLFWwindow* window,Manentity_type& EM ,Entity& e){
    //auto& enemy_p = EM.getEntityCMP<CPhysics>(e);
    
    if(e.hasTag<TPlayer>()){
        GL.camera.Position = GL.camera.LastPosition;
    }else{
        //enemy
    }   
}
 
void Collision_System::CollisionWithPickable(GLFWwindow* window, Manentity_type& EM, Entity& object, EngineGL &GL){
    //En este punto TPickable ya ha sido comprobado
    if(!object.hasTag<TLantern>()){    
        GL.renderText(EM.getEntityCMP<CInformation>(object).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
    }
    if (!object.hasTag<TNotRenderizable>()){ // si la entidad no tiene el tag norenderizable 
        if (stop_E_pulsation == 0 && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !object.hasTag<TLantern>()){
            if(!object.hasTag<TRueda>() && !object.hasTag<TMarco>() && !object.hasTag<TYesquero>() && !object.hasTag<TFuse>() && !object.hasTag<TRing>() && !object.hasTag<TShears>()){
                if (EM.getLevelsStatus().actual == 2){puerta_principal =1;}
                object.addTag<TNotRenderizable>(); // simulo recogida del objeto
                object.eraseTag<TDescription>();
                object.eraseTag<TCollisionable>();
                auto& inventory = EM.getInventory();
                inventory.push_back(&object);

                EM.getEntityCMP<CRenderGL>(object).modelMatrix.Scale(0.3,0.3,0.3);
                EM.getEntityCMP<CSound>(object).s_mgr->playSound("event:/HardFX/Llave");
                
                if(stop_E_pulsation == 0 && EM.getLevelsStatus().actual == 2){
                    auto& door = EM.getEntityByID(object.getID() - 4); 
                    auto& figura = EM.getEntityByID(object.getID() - 3); 
                    door.eraseTag<TDescription>();
                    figura.eraseTag<TDescription>();
                    figura.eraseTag<TWindowMailBox>();
                    EM.getEntityCMP<CInformation>(figura).description ="";
                }
                

            }else if (object.hasTag<TFuse>()){
                object.addTag<TNotRenderizable>(); // simulo recogida del objeto fusible
                object.eraseTag<TCollisionable>();
                object.eraseTag<TDescription>();
                auto& inventory = EM.getInventory();
                inventory.push_back(&object);
                auto& fuse_box = EM.getEntityByID(object.getID()-1);
                fuse_box.eraseTag<TDescription>();
                EM.getEntityCMP<CRenderGL>(object).modelMatrix.Scale(0.5,0.5,0.5);

            }else if (object.hasTag<TRing>()){
                GL.camera.anillo_rec = 1;
                auto& rendanillo = EM.getEntityCMP<CRenderGL>(object);
                rendanillo.modelMatrix.Rotate(45,0,0,1);
                object.addTag<TNotRenderizable>(); // simulo recogida del objeto fusible
                object.eraseTag<TCollisionable>();
                object.eraseTag<TDescription>();
                auto& inventory = EM.getInventory();
                inventory.push_back(&object);
                
            }else if(object.hasTag<TShears>()){

                object.addTag<TNotRenderizable>(); // simulo recogida del objeto fusible
                object.eraseTag<TCollisionable>();
                object.eraseTag<TDescription>();
                auto& inventory = EM.getInventory();
                EM.getEntityCMP<CRenderGL>(object).modelMatrix.Scale(0.05,0.05,0.05);

                inventory.push_back(&object);

            }else if(object.hasTag<TMarco>()){
                GL.camera.marco_lvl4 = 1;
                object.addTag<TNotRenderizable>(); // simulo recogida del objeto fusible
                object.eraseTag<TCollisionable>();
                object.eraseTag<TDescription>();
                auto& inventory = EM.getInventory();
                inventory.push_back(&object);
                EM.getEntityCMP<CRenderGL>(object).modelMatrix.Scale(0.15,0.15,0.15);
            }else if(object.hasTag<TRueda>()){
                EM.getLevelsStatus().lvl_Sotano_objects_status = object.getID();
                auto& rendrueda = EM.getEntityCMP<CRenderGL>(object);
                ///rendrueda.modelMatrix.Rotate(45,0,0,1);
                rendrueda.modelMatrix.Scale(0.15,0.15,0.15);
                object.addTag<TNotRenderizable>(); // simulo recogida del objeto fusible
                object.eraseTag<TCollisionable>();
                object.eraseTag<TDescription>();
                auto& inventory = EM.getInventory();
                inventory.push_back(&object);
                //spawn de enemigo en sotano
                auto dummy = [&](Entity& e){
                    e.eraseTag<TNotRenderAnim>();
                    e.eraseTag<TDummy>();
                };
                EM.foreach<Typelist<>, Typelist<TDummy>>(dummy);

                auto& csoundrueda = EM.getEntityCMP<CSound>(object);
                csoundrueda.s_mgr->playSound("event:/Music/End");
            }else{
                if(GL.camera.LanternIsHeld)
                {
                    object.addTag<TNotRenderizable>(); // simulo recogida del objeto
                    object.eraseTag<TDescription>();
                    object.eraseTag<TCollisionable>();
                    //cogemos la segunda entidad, que es la linterna, cambiar por tag de luz o algo así
                    EM.getEntityCMP<CHealth>(EM.getEntityArray()[2]).health = 100;
                }
                
            }
        }
        if(object.hasTag<TLantern>()){
            GL.renderText(EM.getEntityCMP<CInformation>(object).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.65, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
                if (GL.camera.last_last_q == 0 && GL.camera.last_q == 1 && GL.camera.pressed_q == 0){
                    
                    GL.camera.pressed_q = 1;
                    object.addTag<TPlayer>();
                    object.eraseTag<Tpickable>();
                    EM.getEntityArray()[1].eraseTag<TNotRenderizable>();
                    EM.getEntityCMP<CRenderGL>(object).modelMatrix.setPosition(0.8, -0.7, 0);
                    GL.camera.LanternIsHeld=true;
                    GL.firstLanternHeld=true;
                    
                }
            }
        }
    }
}

void Collision_System::CollisionWithSoundEvent(Manentity_type& EM, Entity& e2){

    auto& cmp = EM.getEntityCMP<CSound>(e2);
    cmp.s_mgr->setParameter("event:/Enviroment/Ambiente", "Ambiente", cmp.eventvalue); 
    e2.eraseTag<TSEvent>();

    if(e2.hasTag<TJumpscare>()){
        e2.eraseTag<TNotRenderizable>();

    }
}

void Collision_System::CollisionWithDoor(GLFWwindow* window, EngineGL& GL, Manentity_type& EM, Entity& e, Entity& e2, CRenderGL& r2){
    auto& cinf = EM.getEntityCMP<CInformation>(e2);

    if(EM.getLevelsStatus().actual == 1){
        //usar abajo los auto de arriba 
        if (EM.getInventory().size()>0){
            GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
        }
        if (e2.hasComponent<CReference>()){
            std::size_t reference_ID = EM.getEntityCMP<CReference>(e2).id_reference;
            auto& entity_door = EM.getEntityByID(reference_ID);
            auto& render_door = EM.getEntityCMP<CRenderGL>(entity_door);
            if (cinf.descriptionPickable != (const char*)""){
                if (PressEToOpenDoor(window, EM, GL, entity_door, render_door)){
                    e2.eraseTag<TCollisionable>();
                    e2.eraseTag<TDescription>();
                    EM.getEntityCMP<CSound>(e2).s_mgr->playSound("event:/HardFX/PuertaIglesia");
                };
            }

        }else{
            PressEToOpenDoor(window, EM, GL, e2, r2);
        }
    }else if (EM.getLevelsStatus().actual == 2){
        if (puerta_principal == 0){
            GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
            if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
                EM.addTagToEntity<TDescription>(e2);
                auto& sound_e2 = EM.getEntityCMP<CSound>(e2);
                sound_e2.s_mgr->playSound("event:/HardFX/LlamarPuerta");
                cinf.type_of_text=3;
                cinf.times_to_print_text=100;
                cinf.description="No answer... Maybe I can see something through the window";
                auto& enetity_figura = EM.getEntityByID(e2.getID()+1);
                //EM.addTagToEntity<TNotRenderizable>(enetity_figura);
                EM.addTagToEntity<TCollisionable>(enetity_figura);
                EM.addTagToEntity<TDescription>(enetity_figura);
                
            }
        }else{

            cinf.descriptionPickable = "[E] Try to open";
            cinf.description = "";
            GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
            if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
                e2.eraseTag<TDoor>();
                EM.defineCMP<CIDLvl>(e2, CIDLvl{.lvlid = 3});
                e2.addTag<TTransition>();
            }
        }

    }else if (EM.getLevelsStatus().actual == 3){
        if (e2.hasTag<TDoor>() && !e2.hasComponent<CIDLvl>() && !e2.hasTag<TBedRoom>()){
            GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
            if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
                auto& sound_door = EM.getEntityCMP<CSound>(e2);
                sound_door.s_mgr->playSound("event:/HardFX/Door");
                e2.eraseTag<TDoor>();
                auto& rend = EM.getEntityCMP<CRenderGL>(e2);
                rend.modelMatrix.Rotate(-80, 0,1,0);
                auto& e_wall = EM.getEntityByID(e2.getID()+1);
                e_wall.eraseTag<TWall>();
                e_wall.eraseTag<TCollisionable>();
            }
        }else if(e2.hasTag<TDoor>() && !e2.hasComponent<CIDLvl>() && e2.hasTag<TBedRoom>()){//closed door bedroom
            GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
            if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
                cinf.type_of_text = 3;
                cinf.times_to_print_text = 100;
                cinf.description = "us...they...are scared of the light, search for the light";
                e2.addTag<TDescription>();
            }
        }else{
            GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
            if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
                e2.eraseTag<TDoor>();
                EM.defineCMP<CIDLvl>(e2, CIDLvl{.lvlid = 2});
                e2.addTag<TTransition>();

            }
        }
    }else if (EM.getLevelsStatus().actual == 5){
        
        GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
        if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            if (!GL.camera.LanternIsHeld){
                e2.eraseTag<TCollisionable>();
                e2.eraseTag<TDoor>();

                auto& door1 = EM.getEntityByID(e2.getID()-2);
                auto& door2 = EM.getEntityByID(e2.getID()-1);
                auto& door1_phy = EM.getEntityCMP<CPhysics>(door1);
                auto& door2_phy = EM.getEntityCMP<CPhysics>(door2);

                door1_phy.x -= 2;
                door2_phy.x += 2;
                door1.eraseTag<TWall>();
                door2.eraseTag<TWall>();
                auto& sounddoor = EM.getEntityCMP<CSound>(e2);
                sounddoor.s_mgr->playSound("event:/HardFX/SlideDoor");

                auto despertar = [&](Entity& e){ e.eraseTag<TDummy>(); };
                EM.foreach<Typelist<>,Typelist<TEventDoorGranero>>(despertar);

            }else{
                auto& cinf = EM.getEntityCMP<CInformation>(e2);
                cinf.times_to_print_text = 70;
                e2.addTag<TDescription>();
            }


        }
    }


}

bool Collision_System::PressEToOpenDoor(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e, CRenderGL& r){
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        for(uint8_t i = 0 ; (uint8_t)i < EM.getInventory().size();++i){
            if (EM.getInventory()[i]->hasTag<TDoorKeyChurch>()){
                e.eraseTag<TWall>();
                e.eraseTag<TCollisionable>();
                r.modelMatrix.Rotate(80, 0,1,0);
                return true;
            }
        }
    }
    return false;
}

void Collision_System::CollisionWithBurnable(GLFWwindow* window, EngineGL& GL, Manentity_type& EM, Entity& e, Entity& e2, CRenderGL& r2){
    auto& ent= EM.getEntityArray()[2];
    auto& light= EM.getEntityCMP<CPointLight>(ent);
    if (light.isOn && GL.camera.LanternIsHeld){
        GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
        if (e2.hasComponent<CReference>()){
            std::size_t reference_ID = EM.getEntityCMP<CReference>(e2).id_reference;
            auto& ent_quemable = EM.getEntityByID(reference_ID);
            if (PressEToBurn(window, EM, GL,ent_quemable)){
                auto& sound_burnable = EM.getEntityCMP<CSound>(e2);
                sound_burnable.s_mgr->playSound("event:/HardFX/Quemar");
                e2.eraseTag<TCollisionable>();
                e2.eraseTag<TDescription>();
            }
        }else{
            PressEToBurn(window, EM,GL, e2);
        }

    }
}

void Collision_System::CollisionWithTransition(Manentity_type& EM, EngineGL& GL, Entity& e2){
    //EM.getEntityCMP<CHealth>(e).health = 0 ;
    // Cambiamos el changed del componente del nivel para comprobar a posterior si está cambiado o no
    //std::cout << EM.getEntityCMP<CPhysics>(EM.getEntityArray()[0]).x << " " << EM.getEntityCMP<CPhysics>(EM.getEntityArray()[0]).z; 
    auto& cid   = EM.getEntityCMP<CIDLvl>(e2); 
    cid.changed = 1;
    GL.camera.charge_plane = 130;
    GL.camera.charge_status = 0;
    auto& player_model  = EM.getEntityArray()[1];
    auto& candil        = EM.getEntityArray()[2];
    player_model.addTag<TNotRenderizable>();
    candil.addTag<TNotRenderizable>();
    GL.transition.Draw(GL.Guishader);
    //save status
    if (EM.getLevelsStatus().actual ==1 && EM.getLevelsStatus().lvl_1_objects_status.size() == 0){
        auto one_time_descriptions= [&](Entity& e, CInformation& cinf){
        if (cinf.type_of_text == 3){ // only one time, next level without this text
            EM.getLevelsStatus().lvl_1_objects_status.push_back( e.getID() );
        }
        };
        EM.foreach<Typelist<CInformation>,Typelist<>>(one_time_descriptions);

        auto save_key_status= [&](Entity& e){
            EM.getLevelsStatus().lvl_1_objects_status.push_back( e.getID() );
        };
        EM.foreach<Typelist<>,Typelist<TDoorKeyChurch>>(save_key_status);

        auto save_door_status= [&](Entity& e){
            EM.getLevelsStatus().lvl_1_objects_status.push_back( e.getID() );
        };
        EM.foreach<Typelist<>,Typelist<TDoor>>(save_door_status);

        auto save_burnable_status= [&](Entity& e){
            EM.getLevelsStatus().lvl_1_objects_status.push_back( e.getID() );
        };
        EM.foreach<Typelist<>,Typelist<TBurnable>>(save_burnable_status);
        
        e2.eraseTag<TSaveStatus>();
        e2.eraseTag<TCollisionable>();
    }
    if (EM.getLevelsStatus().actual ==2 && EM.getLevelsStatus().lvl_2_objects_status.size() == 0 && EM.getInventory().size() == 1){
        int id{};
        auto saelvl2 = [&](Entity& e, CInformation& cinf){
            EM.getLevelsStatus().lvl_2_objects_status.push_back(e.getID()); //door
            id  = e.getID(); 
        };
        EM.foreach<Typelist<CInformation>, Typelist<TTransition>>(saelvl2);  
        EM.getLevelsStatus().lvl_2_objects_status.push_back(id+1);//figura
        EM.getLevelsStatus().lvl_2_objects_status.push_back(id+2);//mailbox
        EM.getLevelsStatus().lvl_2_objects_status.push_back(id+4);//key
        EM.getLevelsStatus().lvl_2_objects_status.push_back(id+5);//mailbox_rotate (boca)

    }
    if (EM.getLevelsStatus().actual ==2 && GL.camera.Position.x >= 30){
        GL.camera.reposition_lvl_camera = 1;
    }
    if (EM.getLevelsStatus().actual ==3 && GL.camera.Position.x >= 15) {
        GL.camera.reposition_lvl_camera = 2;
    }else if(EM.getLevelsStatus().actual ==3 && GL.camera.Position.x <= 15){
        GL.camera.reposition_lvl_camera = 1;
    }
    if (EM.getLevelsStatus().actual ==4){
        GL.camera.reposition_lvl_camera = 3;
    }
    if (EM.getLevelsStatus().actual ==6 || EM.getLevelsStatus().actual ==5 ){
        GL.camera.reposition_lvl_camera = 4;
    }
    if (EM.getLevelsStatus().actual ==8){
        GL.camera.reposition_lvl_camera = 10;
        //if (EM.getLevelsStatus()){
        //
        //}
    }
    if (EM.getLevelsStatus().actual ==7){
        GL.camera.reposition_lvl_camera = 3;
        //if (EM.getLevelsStatus()){
        //
        //}
    }
    if (EM.getLevelsStatus().actual ==2 && e2.hasTag<TBackDoor>()){
        GL.camera.reposition_lvl_camera = 11;
    }
    if (EM.getLevelsStatus().actual ==3 && EM.getLevelsStatus().lvl_3_objects_status.size() == 0 && farmer_action == 1){
        EM.getLevelsStatus().lvl_3_objects_status.push_back(7);//salon puerta
        EM.getLevelsStatus().lvl_3_objects_status.push_back(9);//habitacion p
        EM.getLevelsStatus().lvl_3_objects_status.push_back(11);//aseo p
        EM.getLevelsStatus().lvl_3_objects_status.push_back(13);//p trasera
        EM.getLevelsStatus().lvl_3_objects_status.push_back(16);//fusible
        EM.getLevelsStatus().lvl_3_objects_status.push_back(19);//tlf
        EM.getLevelsStatus().lvl_3_objects_status.push_back(22);//farmer
        EM.getLevelsStatus().lvl_3_objects_status.push_back(23);//quemable
        EM.getLevelsStatus().lvl_3_objects_status.push_back(25);//enemy 1
        EM.getLevelsStatus().lvl_3_objects_status.push_back(26);//enemy 2
        EM.getLevelsStatus().lvl_3_objects_status.push_back(27);//enemy 3
        EM.getLevelsStatus().lvl_3_objects_status.push_back(17);//cuadro

    }
    if (EM.getLevelsStatus().actual ==4 && EM.getLevelsStatus().lvl_4_objects_status.size() == 0 && tomb_event != 0){
        //checker lvl 4
        EM.getLevelsStatus().lvl_4_objects_status.push_back(9);
        EM.getLevelsStatus().lvl_4_objects_status.push_back(8);
        EM.getLevelsStatus().lvl_4_objects_status.push_back(6);
        EM.getLevelsStatus().lvl_4_objects_status.push_back(10);
    }
    if (EM.getLevelsStatus().actual ==5 && EM.getLevelsStatus().lvl_5_objects_status.size() == 0 && trampilla_abierta!=0){
        EM.getLevelsStatus().lvl_5_objects_status.push_back(7);
        EM.getLevelsStatus().lvl_5_objects_status.push_back(9);
        EM.getLevelsStatus().lvl_5_objects_status.push_back(15);
    }
}

bool Collision_System::PressEToBurn(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e){
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        e.eraseTag<TCollisionable>();
        e.eraseTag<TWall>();
        e.addTag<TNotRenderizable>();
        if (EM.getLevelsStatus().actual == 3 && EM.getLevelsStatus().lvl_Sotano_objects_status!=0){
                GL.camera.granjero_quemado = 1;
        }
        
        
        return true;
    }
    return false;
}

void Collision_System::CollisionWithDescription(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2){
    auto& cinformation = EM.getEntityCMP<CInformation>(e2);
    if (cinformation.type_of_text == 0){
        GL.renderText(cinformation.description, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.2, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
        //if (cinformation.descriptionPickable != (const char*)"no-pickable"){
        //    GL.renderText(cinformation.descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
        //} HACER COLISION CON SILUETA
        if (e2.hasTag<TBackDoor>()){
            GL.renderText(cinformation.descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
                //e2.addTag<TDescription>();
                if (farmer_action == 0){
                    cinformation.type_of_text = 3;
                    cinformation.times_to_print_text =100;
                    cinformation.description = "It's closed from inside";
                }else{
                    e2.addTag<TDoor>();
                    e2.eraseTag<TDescription>();
                }
            }
        }
    }else if (cinformation.type_of_text == 1){
        double altura = 2.2;
        for (long unsigned int i = 0 ; i < cinformation.text_list.size() ; ++i){
            if (strcmp(cinformation.text_list[i], "")){ // cinformation.text_list[i] != (const char*)""
                GL.renderText(cinformation.text_list[i], GL.SRC_WIDTH/4, GL.SRC_HEIGHT/altura, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
                altura += 0.15;
            }else{
                break;
            }
        }
    }else if (cinformation.type_of_text == 2){
        if (strcmp(cinformation.text_list[dialogo], "")){
            if ((dialogo==0 || dialogo==2 || dialogo==4 || dialogo==5||dialogo==7||dialogo==9||dialogo==10||dialogo==11) && EM.getLevelsStatus().actual == 3){
                GL.renderText(cinformation.text_list[dialogo], GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.2, 0.7f, glm::vec3(1.0f, 0.0f, 0.0f));
            }else{
                GL.renderText(cinformation.text_list[dialogo], GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.2, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
            }
            if (cinformation.descriptionPickable != (const char*)"no-pickable"){
                GL.renderText(cinformation.descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
            }
        }else{
            dialogo = 0;
            cinformation.type_of_text = 0;
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            if ( GL.camera.last_pressed_space == 0 && GL.camera.pressed_space == 1){
                dialogo++;
                //cinformation.descriptionPickable = "no-pickable";
            } 
        }
    }else if (cinformation.type_of_text == 3){
        GL.renderText(cinformation.description, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.2, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
        
        if (cinformation.times_to_print_text == 0){
            e2.eraseTag<TDescription>();

            if(e2.hasTag<TBackDoor>()){
                cinformation.type_of_text = 0;
                e2.addTag<TDescription>();
                cinformation.description ="";
            }
        }
        
        cinformation.times_to_print_text--;
       
    }
}

void Collision_System::CollisionWithReposition(Manentity_type& EM, EngineGL& GL, Entity& e, Entity& e2){
    if (EM.getLevelsStatus().contador_Y < 5){
        auto& creposition = EM.getEntityCMP<CReposition>(e2);

        if(creposition.type == 1){
            EM.getLevelsStatus().contador_Y++;
            if (EM.getLevelsStatus().contador_Y == 1){ 
                creposition.type = 2; 
                auto& creposition_2 = EM.getEntityCMP<CReposition>(EM.getEntityByID(e2.getID()+1));
                creposition_2.type = 1;
            }else if (EM.getLevelsStatus().contador_Y == 3){
                creposition.type = 2; 
                auto& creposition_2 = EM.getEntityCMP<CReposition>(EM.getEntityByID(e2.getID()-1));
                creposition_2.type = 1;
            }
            if (EM.getLevelsStatus().contador_Y == 4){
                
                EM.defineCMP<CIDLvl>(e2, CIDLvl{.lvlid=5});
                e2.addTag<TTransition>();
            }
        }else{
            
            if (e2.getID() == 15){
                creposition.type =1;
                auto& creposition_2 = EM.getEntityCMP<CReposition>(EM.getEntityByID(e2.getID()+1));
                creposition_2.type=2;
            }else{
                creposition.type =2;
                auto& creposition_2 = EM.getEntityCMP<CReposition>(EM.getEntityByID(e2.getID()-1));
                creposition_2.type=1;
            }
            EM.getLevelsStatus().contador_Y = 0;
        }

        GL.camera.Position = {creposition.x, 1.5, creposition.z};
    }

}

void Collision_System::CollisionWithWindowMailBox(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2){
    auto& cinformation = EM.getEntityCMP<CInformation>(e2);
    GL.renderText(cinformation.descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        cinformation.type_of_text = 3;
        cinformation.times_to_print_text = 100;
        cinformation.description = "She used to leave a key in the mailbox";
        EM.addTagToEntity<TCollisionable>(e2);
        EM.addTagToEntity<TDescription>(e2);
        auto& mailbox = EM.getEntityByID(e2.getID()+1);
        mailbox.addTag<TDescription>();
        EM.addTagToEntity<TScaleBoundingBox>(mailbox);
	    EM.addTagToEntity<TCollisionable>(mailbox);
	    EM.addTagToEntity<TMailBox>(mailbox);
    }
}

void Collision_System::CollisionWithMailBox(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2){
    auto& cinformation = EM.getEntityCMP<CInformation>(e2);
    if (strcmp(cinformation.descriptionPickable, "")){
        cinformation.description="";
        GL.renderText(cinformation.descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
    }

    if (stop_E_pulsation == 0 && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        cinformation.descriptionPickable = "";
        auto& key = EM.getEntityByID(e2.getID()+2);
        key.eraseTag<TNotRenderizable>();
        key.addTag<TDescription>();
        auto& mailbox_rot = EM.getEntityByID(key.getID()+1);
        EM.getEntityCMP<CRenderGL>(mailbox_rot).modelMatrix.Rotate(90,1,0,0);
        
        e2.eraseTag<TCollisionable>();

        stop_E_pulsation++;
    }

}

void Collision_System::CollisionWithFuseBox(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2){
    bool haveFuse = false;
    unsigned long int pos = 0;
    for(unsigned long int i = 0; i < EM.getInventory().size();++i){
        if (EM.getInventory()[i]->hasTag<TFuse>()){
            haveFuse = true;
            pos = i;
        }
    }
    if (haveFuse){
        GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
        
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            auto& csound_fuse_box = EM.getEntityCMP<CSound>(e2);
            csound_fuse_box.s_mgr->playSound("event:/HardFX/PuertaBloqueada");
            auto& fuse = *EM.getInventory()[pos];
            EM.getEntityCMP<CRenderGL>(fuse).modelMatrix.nodeMatrix = glm::mat4(1.f);
            auto& fuse_phy = EM.getEntityCMP<CPhysics>(fuse);
            fuse.eraseTag<TNotRenderizable>();
            fuse_phy.x = -2.962; fuse_phy.y = 1.80; fuse_phy.z = -1.381;
            e2.eraseTag<TCollisionable>();

            auto look_for_bedroom_door= [&](Entity& e){
                e.eraseTag<TBedRoom>();
                auto& cinf = EM.getEntityCMP<CInformation>(e);
                cinf.type_of_text=0;
                cinf.description="";
                cinf.descriptionPickable = "[E] Open";
            };
            EM.foreach<Typelist<>,Typelist<TBedRoom>>(look_for_bedroom_door);


            auto lights= [&](Entity& e, CPointLight& cp){
                if(e.getID() != 3){
                    cp.houseLight();
                }
                
            };
            EM.foreach<Typelist<CPointLight>,Typelist<>>(lights);
            //ALGO VISUAL PARA HACER COMO QUE HE PUESTO EL FUSIBLE
            //A PARTE DE VEER EL FUSIBLE EN SU POSICION
        }
    }
}

void Collision_System::CollisionWithPhone(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& phone){
    GL.renderText(EM.getEntityCMP<CInformation>(phone).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        phone.eraseTag<TCollisionable>();
        auto& csound_phone = EM.getEntityCMP<CSound>(phone);
        csound_phone.s_mgr->setParameter("event:/HardFX/Telefono","Llamada",2);
    }
}//FALTA HACER MAKE ALL Y PROBAR COLLISION CON TELEFONO

void Collision_System::CollisionWithHouseInteractuable(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& object){
    if (object.hasTag<TPainting>()){
        GL.renderText(EM.getEntityCMP<CInformation>(object).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            EM.getEntityCMP<CPhysics>(object).x = -2.89;
            EM.getEntityCMP<CPhysics>(object).y = 0.6;
            EM.getEntityCMP<CRenderGL>(object).modelMatrix.Rotate(10, 0,0,1);

            object.eraseTag<TCollisionable>();
            object.eraseTag<TDescription>();

            auto save_b= [&](Entity& e){
                e.addTag<TDescription>();
                e.addTag<TSaveBox>();
                e.addTag<TCodeLock>();
            };
            EM.foreach<Typelist<>,Typelist<TSaveBox>>(save_b);
        }
    }else if(object.hasTag<TFarmer>()){
        auto& cinf_farmer = EM.getEntityCMP<CInformation>(object);
        if (cinf_farmer.type_of_text == 0){
            DoAfterFarmerConversation(EM,GL, object);
        }
    }
    
}

void Collision_System::CollisionWithTombEvent(Manentity_type& EM, EngineGL& GL, Entity& e2){
    auto& cinform = EM.getEntityCMP<CInformation>(e2);
    if (cinform.type_of_text == 0) {
        DoAfterTombEvent(EM,GL,e2);
    }
}

void Collision_System::CollisionWithEnemyEvent(Manentity_type& EM, EngineGL& GL, Entity& e2){
    e2.eraseTag<TEnemyEvent>();
    std::size_t id=0;
    for (unsigned long int i = 0; i < EM.getEntityArray().size(); ++i){
        if (EM.getEntityArray()[i].hasTag<TEnemy>()){
            id = EM.getEntityArray()[i].getID();
            break;
        }
    }
    
    auto& enemy1 = EM.getEntityByID(id);
    auto& enemy2 = EM.getEntityByID(id+1);
    enemy1.eraseTag<TDummy>();
    enemy2.eraseTag<TDummy>();

	EM.getEntityCMP<CRenderGL>(enemy1).modelMatrix.Rotate(180,0,1,0);
    
    srand(time(0));
    int rand_enemy = rand() % (6 - 2) + 2;
    auto& enemy3 = EM.getEntityByID(id+rand_enemy);
    enemy3.eraseTag<TDummy>();
    //EM.getEntityCMP<CRenderGL>(enemy3).modelMatrix = Model("assets/level1/enemigotext.obj", glm::vec3(0, 0, 0));

}

void Collision_System::DoAfterFarmerConversation(Manentity_type& EM, EngineGL& GL, Entity& farmer){
    farmer_action = 1;
    farmer.eraseTag<TFarmer>(); // para no repetir esta funcion

    //APAGADO DE LUCES Y SPAWN DE ENEMIGOS POR LA HABITACION/ CASA
    auto& p_habitacion = EM.getEntityByID(9);
    auto& p_habitacion_wall = EM.getEntityByID(9+1);
    auto& p_habitacion_rend = EM.getEntityCMP<CRenderGL>(p_habitacion);
    auto& p_habitacion_sound = EM.getEntityCMP<CSound>(p_habitacion);
        p_habitacion_rend.modelMatrix.Rotate(80, 0,1,0);
        p_habitacion_wall.addTag<TCollisionable>();
        p_habitacion_wall.addTag<TWall>();
        p_habitacion_sound.s_mgr->playSound("event:/HardFX/CerrarPuerta");
    auto& p_trasera = EM.getEntityByID(13);
        p_trasera.addTag<TDoor>();
        p_trasera.eraseTag<TDescription>();
    //Modelo de los enemigos tiene que ser el estatico. 
    //En el momento que se acabe la conversación con el granjero deben tener componente animator y ponerles a todos el 
    //modelo que corresponde de movimiento
    
    auto despertar= [&](Entity& e){
        e.eraseTag<TDummy>();
        //EM.getEntityCMP<CRenderGL>(e).modelMatrix = Model("assets/level1/enemigotext.obj", glm::vec3(0, 0, 0));
        EM.addTagToEntity<TNotRenderizable>(e);
        EM.addComponentToEntity<CAnimation>(e);
        EM.getEntityCMP<CAnimation>(e).animation = Animation("assets/animaciones/idle.dae", &EM.getEntityCMP<CRenderGL>(e).modelMatrix);
	    EM.getEntityCMP<CAnimation>(e).animator = Animator(&EM.getEntityCMP<CAnimation>(e).animation);

	
    };
    EM.foreach<Typelist<>,Typelist<TDummy>>(despertar);

    auto lights= [&](Entity& e, CPointLight& cp){
        cp.setOff();
    };
    EM.foreach<Typelist<CPointLight>,Typelist<>>(lights);
    
}

void Collision_System::DoAfterTombEvent(Manentity_type& EM, EngineGL& GL, Entity& e2){
    e2.eraseTag<TTombEvent>();
    std::size_t ref = EM.getEntityCMP<CReference>(e2).id_reference;
    auto& event = EM.getEntityByID(ref);
    event.addTag<TEnemyEvent>();
    tomb_event++;
}

void Collision_System::CollisionWithTransitionY(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2){
    GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        //EM.defineCMP<CIDLvl>(e2, CIDLvl{.lvlid = 6});
        e2.addTag<TTransition>();

    }
}

void Collision_System::CollisionWithCodeLock(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2){
    if (!GL.codelock_completed){
        GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            GL.incodelock = true;
        }
    }else{
        e2.eraseTag<TCodeLock>();
        e2.eraseTag<TSaveBox>();
        e2.eraseTag<TCollisionable>();

        auto& door_save_box = EM.getEntityByID(e2.getID()+1);
        auto& rend = EM.getEntityCMP<CRenderGL>(door_save_box);
        rend.modelMatrix.Rotate(80,0,1,0);
        auto& anillo = EM.getEntityByID(e2.getID()+2);

        anillo.addTag<TDescription>();
        anillo.addTag<Tpickable>();
    }

}

void Collision_System::CollisionWithHatch(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2){
    GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
    bool cizalla = false;
    auto& cinfo_trampilla = EM.getEntityCMP<CInformation>(e2);
    for(unsigned long int i = 0 ; i < EM.getInventory().size(); ++i){
        if (EM.getInventory()[i]->hasTag<TShears>()){
            cizalla = true;
        }
    }
    if (stop_E_pulsation == 0 && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        if (GL.camera.LanternIsHeld && cizalla && strcmp(cinfo_trampilla.descriptionPickable, "[E] Down stairs")!=0){
            cinfo_trampilla.description = "Needs two hands to use the shears";
            stop_E_pulsation++;
            
        }else if (!GL.camera.LanternIsHeld && cizalla && strcmp(cinfo_trampilla.descriptionPickable, "[E] Down stairs")!=0){
            auto& puerta_izq = EM.getEntityByID(e2.getID()+1);
            auto& puerta_drc = EM.getEntityByID(e2.getID()+2);
            auto& rend_pizq  = EM.getEntityCMP<CRenderGL>(puerta_izq);
            auto& rend_pdrc  = EM.getEntityCMP<CRenderGL>(puerta_drc);
            auto& sound_e2   = EM.getEntityCMP<CSound>(e2);

            sound_e2.s_mgr->playSound("event:/HardFX/cadenas");
            rend_pizq.modelMatrix.Rotate(120,0,0,1);
            rend_pdrc.modelMatrix.Rotate(-120,0,0,1);
            cinfo_trampilla.descriptionPickable = "[E] Down stairs";
            cinfo_trampilla.description = "";
            stop_E_pulsation++;
            trampilla_abierta++;
        }
        if (stop_E_pulsation == 0 && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && strcmp(cinfo_trampilla.descriptionPickable, "[E] Down stairs")==0){
            EM.defineCMP<CIDLvl>(e2, CIDLvl{.lvlid = 8});
            e2.addTag<TTransition>();
            stop_E_pulsation++;
        }
    }
}

void Collision_System::CollisionWithCar(GLFWwindow* window, Manentity_type& EM, EngineGL& GL, Entity& e2){
    if (EM.getLevelsStatus().lvl_Sotano_objects_status!=0){
        GL.renderText(EM.getEntityCMP<CInformation>(e2).descriptionPickable, GL.SRC_WIDTH/4, GL.SRC_HEIGHT/2.4, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            if(GL.camera.granjero_quemado ==0){
                //final malo
                //std::cout<<"final malo"<<"\n";
                GL.final_=1;
            }else{
                //final bueno
                //std::cout<<"final bueno"<<"\n";
                GL.final_=2;
            }
        }   

    }
}

void Collision_System::resetVariablesCollSys(){
    farmer_action=0;
    tomb_event=0;
    trampilla_abierta=0;
    puerta_principal=0;
    stop_E_pulsation=0;
    dialogo = 0;
}