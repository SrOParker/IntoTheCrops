#include "Levels.hpp"
#include "Game.hpp"
#include "engine/teosinteEngine.hpp"

//perdón por esta monstruosidad fran
void Levels::reset_game_variables(Manentity_type& man_e,Sys& systems, EngineGL& GL){
	//Clear ManEntity && CLevels
	clearLevel(man_e,systems,GL);
	man_e.getInventory().clear();
	man_e.getLevelsStatus().contador_Y = 0;
	man_e.getLevelsStatus().lvl_1_objects_status.clear();
	man_e.getLevelsStatus().lvl_2_objects_status.clear();
	man_e.getLevelsStatus().lvl_3_objects_status.clear();
	man_e.getLevelsStatus().lvl_4_objects_status.clear();
	man_e.getLevelsStatus().lvl_5_objects_status.clear();
	man_e.getLevelsStatus().lvl_Sotano_objects_status = 0;
	//Clear Camera variables 
	GL.camera.marco_lvl4 = 0;
	GL.camera.anillo_rec = 0;
	GL.camera.reposition_lvl_camera = 0;
	GL.camera.granjero_quemado = 0;
	GL.camera.charge_plane = 0;
	GL.camera.charge_status = 1;
	GL.camera.LanternIsHeld = false;
	
	//Clear EngineGL
	GL.codelock_completed = 0;
	GL.final_ = 0;
	GL.firstLanternHeld = false;
	
	//Clear Systems
	systems.coll_sys.resetVariablesCollSys();
}

void Levels::save_inventory(Manentity_type& man_e,Sys& systems, EngineGL& GL){
	auto& inventory = man_e.getInventory();
	inventory.clear();
	if (man_e.getLevelsStatus().lvl_Sotano_objects_status != 0){
		auto& rueda = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CPng>();
		man_e.defineCMP<CPhysics>(rueda, CPhysics{.x =-19.88, .y=0.55 ,.z= -32.14});
		man_e.defineCMP<CPng>(rueda, CPng{.icono = Model("assets/Sotano/rueda.obj", glm::vec3(-0.70,0.42,0))});
		man_e.getEntityCMP<CPng>(rueda).icono.Rotate(90,1,1,1);
		man_e.getEntityCMP<CPng>(rueda).icono.Scale(0.35,0.35,0.35);
		man_e.getEntityCMP<CRenderGL>(rueda).modelMatrix.Rotate(90,0,0,1);
		man_e.defineCMP<CRenderGL>(rueda, CRenderGL{.modelMatrix = Model("assets/Sotano/rueda.obj", glm::vec3(0,0,0))});
		man_e.getEntityCMP<CRenderGL>(rueda).modelMatrix.Scale(0.15,0.15,0.15);
		rueda.addTag<TNotRenderizable>();
		man_e.defineCMP<CInformation>(rueda, CInformation{.type_of_text = 0, .description{"A wheel! My salvation!"}, .descriptionPickable{"[E] Grab"}});

		inventory.push_back(&rueda);
	}
	if (GL.camera.marco_lvl4 == 1){
		auto& marco_foto = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CPng>();
		man_e.defineCMP<CPhysics>(marco_foto , CPhysics{.x = 2.45, .y = 0, .z = -28});
		man_e.defineCMP<CPng>(marco_foto , CPng{.icono = Model("assets/level4/marco_Tumba.obj", glm::vec3(0,0,0))});
		man_e.defineCMP<CRenderGL>(marco_foto , CRenderGL{.modelMatrix = Model("assets/level4/marco_Tumba.obj", glm::vec3(0,0,0))});
		man_e.getEntityCMP<CRenderGL>(marco_foto).modelMatrix.Scale(0.15,0.15,0.15);
		man_e.defineCMP<CInformation>(marco_foto, CInformation{.type_of_text=0, .description{"There's something written behind"}, .descriptionPickable{"[E] Grab"}});
		marco_foto.addTag<TNotRenderizable>(); 
		inventory.push_back(&marco_foto);
	}
	if(GL.camera.anillo_rec == 1){
		auto& anillo = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CSound, CPng>();
		man_e.defineCMP<CPhysics>(anillo, CPhysics{.x =-3.57, .y=1.60 , .z= -5.07});
		man_e.defineCMP<CSound>(anillo, CSound{.s_mgr = &systems.soundito});
		man_e.defineCMP<CPng>(anillo, CPng{.icono = Model("assets/level3/anillo.obj", glm::vec3(0,0,0))});
		man_e.defineCMP<CRenderGL>(anillo, CRenderGL{.modelMatrix = Model("assets/level3/anillo.obj", glm::vec3(0,0,0))});
		man_e.getEntityCMP<CRenderGL>(anillo).modelMatrix.Rotate(90, 0,0,-1);
		man_e.getEntityCMP<CRenderGL>(anillo).modelMatrix.Rotate(45,0,0,1);
		anillo.addTag<TNotRenderizable>(); // simulo recogida del objeto fusible
		man_e.defineCMP<CInformation>(anillo,CInformation{.description="" ,.descriptionPickable="[E] Grab"});	

		inventory.push_back(&anillo);
	}
}

void Levels::clearLevel(Manentity_type& man_e, Sys& systems, EngineGL& GL){
	auto& cs = man_e.getComponentStorage();
	systems.soundito.stopAll();
    cs.clearCS();
	man_e.getEntityArray()[0].resetNextID();// da igual a la entidad que se le haga el reset, nextid es static
    man_e.resetEntityArray();
	GL.camera.LanternIsHeld = true;
	GL.nextIDLight = 0;
}

void Levels::emptyAll(Manentity_type& man_e, Sys& systems, EngineGL& GL){
	auto& cs = man_e.getComponentStorage();
	//systems.soundito.stopAll();
    cs.clearCS();
	man_e.getEntityArray()[0].resetNextID();// da igual a la entidad que se le haga el reset, nextid es static
    man_e.resetEntityArray();
}

void Levels::InitSoundsLvl_1(SoundManager& s_mgr){
	s_mgr.playSound("event:/Enviroment/Ambiente");
	s_mgr.setParameter("event:/Enviroment/Ambiente", "Ambiente", 2.5);
	//s_mgr.setParameter("event:/Character/creepy", "close", 0.06);
	//s_mgr.set3DProp("event:/Character/creepy", 20, 1, -50);
	//s_mgr.playSound("event:/Character/creepy");
	s_mgr.set3DProp("event:/HardFX/coche", 0, 0, 0);
	s_mgr.playSound("event:/HardFX/coche");
	s_mgr.setParameter("event:/Character/Pasos", "Suelo", 1);
}

void Levels::InitSoundsLvl_2(SoundManager& s_mgr){
	s_mgr.playSound("event:/Enviroment/Ambiente");
	s_mgr.setParameter("event:/Enviroment/Ambiente", "Ambiente", 2.5);
	s_mgr.setParameter("event:/Character/creepy", "close", 0.06);
	s_mgr.set3DProp("event:/Character/creepy", 20, 1, -50);
	s_mgr.playSound("event:/Character/creepy");
	s_mgr.setParameter("event:/Character/Pasos", "Suelo", 1);
}

void Levels::InitSoundsLvl_3(Manentity_type& man_e, SoundManager& s_mgr){
	s_mgr.playSound("event:/Enviroment/AmbienteInterior");
	s_mgr.setParameter("event:/Enviroment/AmbienteInterior", "AmbienteInterior", 2.5);
	s_mgr.set3DProp("event:/HardFX/TV", 0.07, 0, -12.87);
	s_mgr.playSound("event:/HardFX/TV");
	s_mgr.setParameter("event:/Character/Pasos", "Suelo", 6);
	if(man_e.getLevelsStatus().lvl_3_objects_status.size() == 0){
		s_mgr.playSound("event:/HardFX/Telefono");
		s_mgr.set3DProp("event:/HardFX/Telefono", 18.12, 0.76, 6.41);
	}
}

void Levels::InitSoundsLvl_4(SoundManager& s_mgr){
	s_mgr.playSound("event:/Enviroment/Ambiente");
	s_mgr.setParameter("event:/Enviroment/Ambiente", "Ambiente", 2.5);
	s_mgr.setParameter("event:/Character/creepy", "close", 0.06);
	s_mgr.set3DProp("event:/Character/creepy", 99, 1, 99);
	s_mgr.playSound("event:/Character/creepy");
	s_mgr.setParameter("event:/Character/Pasos", "Suelo", 1);

}

void Levels::InitSoundsLvl_5(SoundManager& s_mgr){
	s_mgr.playSound("event:/Enviroment/Ambiente");
	s_mgr.setParameter("event:/Enviroment/Ambiente", "Ambiente", 2.5);
	s_mgr.setParameter("event:/Character/creepy", "close", 0.06);
	s_mgr.setParameter("event:/Character/Pasos", "Suelo", 1);
	//ENEMIGO?
	//s_mgr.set3DProp("event:/Character/creepy", 20, 1, -50);
	//s_mgr.playSound("event:/Character/creepy");
}

void Levels::InitSoundsLvl_Y(SoundManager& s_mgr){
	s_mgr.playSound("event:/Enviroment/AmbienteInterior");
	s_mgr.setParameter("event:/Enviroment/AmbienteInterior", "AmbienteInterior", 2.5);
	s_mgr.setParameter("event:/Character/creepy", "close", 0.06);

	s_mgr.setParameter("event:/Character/Pasos", "Suelo", 1);
	//ENEMIGO?
	s_mgr.set3DProp("event:/Character/creepy", 20, 1, -50);
	s_mgr.playSound("event:/Character/creepy");
}

void Levels::InitSoundsLvl_Sotano(SoundManager& s_mgr){
	s_mgr.playSound("event:/Enviroment/AmbienteInterior");
	s_mgr.setParameter("event:/Enviroment/AmbienteInterior", "AmbienteInterior", 2.5);
	s_mgr.setParameter("event:/Character/creepy", "close", 0.06);

	s_mgr.setParameter("event:/Character/Pasos", "Suelo", 2.3);
	s_mgr.playSound("event:/Character/Pasos");
	//ENEMIGO?
	s_mgr.set3DProp("event:/Character/creepy", 20, 1, -50);
	s_mgr.playSound("event:/Character/creepy");
}

void Levels::InitSoundsLvl_maze(SoundManager& s_mgr){
	s_mgr.playSound("event:/Enviroment/Ambiente");
	s_mgr.setParameter("event:/Enviroment/Ambiente", "Ambiente", 2.5);
	s_mgr.setParameter("event:/Character/Pasos", "Suelo", 1);
}

void Levels::load_lv_1_lights(Manentity_type& man_e,EngineGL& GL)
{

	auto& light5 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.defineCMP<CPhysics>(light5,  CPhysics{.x=-19.9, .y=1, .z=-24});
	man_e.defineCMP<CPointLight>(light5, CPointLight{0.7,0.7,0.7,0.4,0.4,0.4,0.11,0.11,0.11,1,0.7,1.8,GL.nextIDLight++,true});
	//man_e.getEntityCMP<CPointLight>(light).setOff();
	man_e.getEntityCMP<CPointLight>(light5).smallLight();

	auto& light6 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.defineCMP<CPhysics>(light6,  CPhysics{.x=-21.9, .y=1, .z=-32});
	man_e.defineCMP<CPointLight>(light6, CPointLight{0.7,0.7,0.7,0.4,0.4,0.4,0.11,0.11,0.11,1,0.7,1.8,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(light6).debugLight();
	//man_e.getEntityCMP<CPointLight>(light).setOff();
	auto& light7 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.defineCMP<CPhysics>(light7,  CPhysics{.x=-15.9, .y=1, .z=-10.2});
	man_e.defineCMP<CPointLight>(light7, CPointLight{0.7,0.7,0.7,0.4,0.4,0.4,0.11,0.11,0.11,1,0.7,1.8,GL.nextIDLight++,true});
	//man_e.getEntityCMP<CPointLight>(light).setOff();
	auto& light8 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.defineCMP<CPhysics>(light8,  CPhysics{.x=-0, .y=1, .z=-2});
	man_e.defineCMP<CPointLight>(light8, CPointLight{0.7,0.7,0.7,0.4,0.4,0.4,0.11,0.11,0.11,1,0.7,1.8,GL.nextIDLight++,true});
		/*
	auto& light2 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.defineCMP<CPhysics>(light2,  CPhysics{.x=-1.41, .y=2.5, .z=-42.2});
	man_e.defineCMP<CPointLight>(light2, CPointLight{1.7,0.7,0.5,0.4,0.4,0.4,0.11,0.11,0.11,1,0.7,1.8,GL.nextIDLight++, true});
	man_e.getEntityCMP<CPointLight>(light2).bigLight();
	
	auto& light3 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.defineCMP<CPhysics>(light3,  CPhysics{.x=-1.41, .y=2.5, .z=-44.5});
	man_e.defineCMP<CPointLight>(light3, CPointLight{2.7,2.7,0.5,0.4,0.4,0.4,0.11,0.11,0.11,1,0.7,1.8,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(light3).debugLight();
//
	auto& light4 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.defineCMP<CPhysics>(light4,  CPhysics{.x=-2.24, .y=2, .z=-46});
	man_e.defineCMP<CPointLight>(light4, CPointLight{0.7,0.7,0.7,0.4,0.4,0.4,0.11,0.11,0.11,1,0.7,1.8,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(light4).bigLight();
*/

}

void Levels::checkStatus_lvl1(Manentity_type& man_e, EngineGL& GL){
	for (uint8_t i{} ; i < man_e.getLevelsStatus().lvl_1_objects_status.size() ; ++i){
		auto& ent = man_e.getEntityByID(man_e.getLevelsStatus().lvl_1_objects_status[i]);
		if (ent.hasComponent<CInformation>() && ent.hasTag<TDescription>()){
			ent.eraseTag<TDescription>();
			ent.eraseTag<TCollisionable>();
		}
		if (ent.hasTag<TDoorKeyChurch>()){
			ent.addTag<TNotRenderizable>();
			ent.eraseTag<TDescription>();
			man_e.getEntityCMP<CInformation>(ent).description="";
			ent.eraseTag<TCollisionable>();
			//man_e.getInventory().push_back(&ent);
		}
		if (ent.hasTag<TDoor>()){
			ent.eraseTag<TCollisionable>();
			auto& id  = man_e.getEntityCMP<CReference>(ent).id_reference;
			auto& ref = man_e.getEntityByID(id);
			man_e.getEntityCMP<CRenderGL>(ref).modelMatrix.Rotate(80, 0,1,0);
			ref.eraseTag<TWall>();
			man_e.getEntityCMP<CInformation>(ent).description="";
			man_e.getEntityCMP<CInformation>(ent).descriptionPickable="";
		}
		if(ent.hasTag<TBurnable>()){
			auto& id  = man_e.getEntityCMP<CReference>(ent).id_reference;
			auto& ref = man_e.getEntityByID(id);
			ent.eraseTag<TCollisionable>();
			ent.eraseTag<TBurnable>();
			ent.eraseTag<TDescription>();
			man_e.getEntityCMP<CInformation>(ent).description="";
			ref.eraseTag<TWall>();
			ref.eraseTag<TCollisionable>();
			ref.addTag<TNotRenderizable>();
		}
		if (i==0 && man_e.getLevelsStatus().lvl_Sotano_objects_status != 0){
			//spawn enemigos a la vuelta
			auto dummy_out = [&](Entity& e){
				//e.eraseTag<TNotRenderizable>();
				e.eraseTag<TDummy>();
				e.eraseTag<TNotRenderAnim>();
			};
			man_e.foreach<Typelist<>,Typelist<TDummy, TNotRenderizable>>(dummy_out);
		}
	}

	auto car = [&](Entity& e){
		auto& cinf = man_e.getEntityCMP<CInformation>(e);
		if (man_e.getLevelsStatus().lvl_Sotano_objects_status != 0){
			cinf.type_of_text = 0;
			cinf.descriptionPickable = "[E] Try to set the wheel and repaire the car";
		}else{
			cinf.descriptionPickable = "no pickable";
		}
	};
	
	man_e.foreach<Typelist<>,Typelist<TCarEventFinal>>(car);
	GL.camera.Position = glm::vec3(19,1.5,-42); //repos
	auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
	player_phy.x = 19; player_phy.y = 1.5; player_phy.z = -42;
	auto& candil = man_e.getEntityArray()[2];
	auto& model  = man_e.getEntityArray()[1];
	candil.addTag<TPlayer>();
	candil.eraseTag<Tpickable>();
	model.eraseTag<TNotRenderizable>();
	man_e.getEntityCMP<CRenderGL>(candil).modelMatrix.setPosition(0.8, -0.7, 0);
	GL.camera.LanternIsHeld=true;
}

void Levels::checkStatus_lvl2(Manentity_type& man_e,Sys& systems, EngineGL& GL){
	for(unsigned long int i=0; i < man_e.getLevelsStatus().lvl_2_objects_status.size(); ++i){
		auto& entity = man_e.getEntityByID(man_e.getLevelsStatus().lvl_2_objects_status[i]);
		if (i == 0){ //39 door
			entity.eraseTag<TDescription>();
		}
		if (i == 1){ //40 figura
            entity.eraseTag<TWindowMailBox>();
		}
		if (i == 2){ //41 mailbox part 1
			entity.eraseTag<TCollisionable>();
		}
		if (i == 3){ //43 key
			//man_e.getInventory().push_back(&entity);
			entity.eraseTag<Tpickable>();
			entity.eraseTag<TCollisionable>();
		}
		if (i == 4){ //44 mailbox part 2
			auto& crender = man_e.getEntityCMP<CRenderGL>(entity);
			crender.modelMatrix.Rotate(90,1,0,0);
		}

	}
	
	if (man_e.getLevelsStatus().lvl_Sotano_objects_status!=0){
		auto yesqueropermanente = [&](Entity& e){
			if (!e.hasTag<TYesqueroPermanente>()){
				e.eraseTag<TCollisionable>();
				e.eraseTag<TDescription>();
				e.eraseTag<Tpickable>();
				e.eraseTag<TNotRenderizable>();
			}
		};
		man_e.foreach<Typelist<>, Typelist<TYesquero>>(yesqueropermanente);
	
		auto despertar = [&](Entity& e){ 
			e.eraseTag<TDummy>();
			//e.eraseTag<TNotRenderizable>();
			e.eraseTag<TNotRenderAnim>();
		};
		man_e.foreach<Typelist<>,Typelist<TDummy>>(despertar);
		
		auto& maiz = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
		man_e.addTagToEntity<TInstance>(maiz);
		man_e.addTagToEntity<TNotRenderizable>(maiz);
		man_e.defineCMP<CRenderGL>(maiz, CRenderGL{.modelMatrix= Model("assets/level1/CornLP.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/level2/instances_maiz2persecucion.txt", .iscorn=true});
		systems.rend_sys.initinstances(man_e, GL);
		
	}

	if (GL.camera.reposition_lvl_camera == 1){
		GL.camera.Position = glm::vec3(33,1.5,1.14); //repos
		auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
		player_phy.x = 33; player_phy.y = 1.5; player_phy.z = 1.14;
		GL.camera.reposition_lvl_camera = 0;
	}else if(GL.camera.reposition_lvl_camera == 2){
		GL.camera.Position = glm::vec3(51,1.5,5); //repos
		auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
		player_phy.x = 51; player_phy.y = 1.5; player_phy.z = 5;
		GL.camera.reposition_lvl_camera = 0;
	}else if (GL.camera.reposition_lvl_camera == 3){
		GL.camera.Position = glm::vec3(62,1.5,45); //repos
		auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
		player_phy.x = 62; player_phy.y = 1.5; player_phy.z = 45;
		GL.camera.reposition_lvl_camera = 0;
	}else if (GL.camera.reposition_lvl_camera == 4){
		//.x = 58.88, .y = 1.25, .z = -26.72
		GL.camera.Position = glm::vec3(55.88,1.5,-26); //repos
		auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
		player_phy.x = 55.88; player_phy.y = 1.5; player_phy.z = -26;
		GL.camera.reposition_lvl_camera = 0;
	}
	auto& candil = man_e.getEntityArray()[2];
	candil.addTag<TPlayer>();
	man_e.getEntityCMP<CRenderGL>(candil).modelMatrix.setPosition(0.8, -0.7, 0);
}

void Levels::checkStatus_lvl3(Manentity_type& man_e, EngineGL& GL){

	for(unsigned long int i = 0 ; i < man_e.getLevelsStatus().lvl_3_objects_status.size(); ++i){
		auto& entity_to_check = man_e.getEntityByID(man_e.getLevelsStatus().lvl_3_objects_status[i]);
		if (i == 0 || i==1 || i==2){
            entity_to_check.eraseTag<TDoor>();
            auto& rend = man_e.getEntityCMP<CRenderGL>(entity_to_check);
            rend.modelMatrix.Rotate(-80, 0,1,0);
            auto& e_wall = man_e.getEntityByID(entity_to_check.getID()+1);
            e_wall.eraseTag<TWall>();
            e_wall.eraseTag<TCollisionable>();
			if (entity_to_check.hasTag<TBedRoom>()){
				entity_to_check.eraseTag<TBedRoom>();
			}
		}
		if (i == 3){
			entity_to_check.addTag<TDoor>();
        	entity_to_check.eraseTag<TDescription>();
		}
		if (i == 4){
			
			entity_to_check.eraseTag<TCollisionable>();
			entity_to_check.eraseTag<TDescription>();
			auto& fuse_box = man_e.getEntityByID(entity_to_check.getID()-1);
			fuse_box.eraseTag<TDescription>();

            auto& fuse_phy = man_e.getEntityCMP<CPhysics>(entity_to_check);
            fuse_phy.x = -2.962; fuse_phy.y = 1.80; fuse_phy.z = -1.381;
            fuse_box.eraseTag<TCollisionable>();

		}
		if (i == 5){
			entity_to_check.eraseTag<TCollisionable>();
		}
		if ( i == 6 ){
			entity_to_check.eraseTag<TFarmer>();
			auto& cinfo = man_e.getEntityCMP<CInformation>(entity_to_check);
			cinfo.type_of_text=0;
			if (man_e.getLevelsStatus().lvl_Sotano_objects_status != 0){
				entity_to_check.addTag<TCollisionable>();
				entity_to_check.addTag<TBurnable>();
				cinfo.descriptionPickable = "[E] Help";
				//cogi la rueda, supone haber recorrido toda la historia, puedes quemar al granjero y acabar con la maldicion
				//se activa aqui 
				
			}
		}
		if ( i == 7 ){
			auto& quemable_txt = man_e.getEntityByID(entity_to_check.getID()+1);
			quemable_txt.eraseTag<TCollisionable>();
			quemable_txt.eraseTag<TDescription>();
			quemable_txt.eraseTag<TBurnable>();
			entity_to_check.eraseTag<TCollisionable>();
			entity_to_check.eraseTag<TWall>();
			entity_to_check.addTag<TNotRenderizable>();		
		}
		if (i==8 || i==9 || i==10){ //ENEMIGOS
			//por ahora al volver no apareceran
			if (i!=9){
				entity_to_check.eraseTag<TEnemy>();
				entity_to_check.eraseTag<TCollider>();
				entity_to_check.addTag<TNotRenderizable>();
				//man_e.getEntityCMP<CRenderGL>(entity_to_check).modelMatrix = Model("assets/level1/enemigotext.obj", glm::vec3(0, 0, 0));
			}else{
				entity_to_check.eraseTag<TDummy>();
			}
		}
		if (i == 11 && GL.codelock_completed){
			//cuadro al suelo
			man_e.getEntityCMP<CPhysics>(entity_to_check).x = -2.89;
            man_e.getEntityCMP<CPhysics>(entity_to_check).y = 0.6;
            man_e.getEntityCMP<CRenderGL>(entity_to_check).modelMatrix.Rotate(10, 0,0,1);
            entity_to_check.eraseTag<TCollisionable>();
            entity_to_check.eraseTag<TDescription>();
			//cajafuerte abierta 
			auto& door_save_box = man_e.getEntityByID(entity_to_check.getID()+2);
			auto& rend = man_e.getEntityCMP<CRenderGL>(door_save_box);
			rend.modelMatrix.Rotate(80,0,1,0);
			//anillo no esta
			auto& anillo_rec = man_e.getEntityByID(entity_to_check.getID()+3);
			anillo_rec.addTag<TNotRenderizable>();
		}
	}

	if (man_e.getLevelsStatus().lvl_3_objects_status.size() != 0 ){
		auto yesqueropermanente = [&](Entity& e){
			if (!e.hasTag<TYesqueroPermanente>()){
				e.eraseTag<TCollisionable>();
				e.eraseTag<TDescription>();
				e.eraseTag<Tpickable>();
				e.eraseTag<TNotRenderizable>();
			}
		};
		man_e.foreach<Typelist<>, Typelist<TYesquero>>(yesqueropermanente);
	}


	if (GL.camera.reposition_lvl_camera == 11){ // entrada por puerta trasera .x =17.30, .y=0 , .z= -13.36
		GL.camera.Position = glm::vec3(17.30,1.5,-12.2); //repos
		auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
		player_phy.x = 17.30; player_phy.y = 1.5; player_phy.z = -12.2;
	}else{
		GL.camera.Position = glm::vec3(0,1.5,-0.5); //repos
		auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
		player_phy.x = 0; player_phy.y = 1.5; player_phy.z = -0.5;
	}

	auto& candil = man_e.getEntityArray()[2];
	auto& model  = man_e.getEntityArray()[1];
	candil.addTag<TPlayer>();
	candil.eraseTag<Tpickable>();
	model.eraseTag<TNotRenderizable>();
	man_e.getEntityCMP<CRenderGL>(candil).modelMatrix.setPosition(0.8, -0.7, 0);
	GL.camera.LanternIsHeld=true;
}

void Levels::checkStatus_lvl4(Manentity_type& man_e, EngineGL& GL){
	
	for (unsigned long int i=0 ; i < man_e.getLevelsStatus().lvl_4_objects_status.size();++i){
		auto& entity = man_e.getEntityByID(man_e.getLevelsStatus().lvl_4_objects_status[i]);
		if(i == 0){
			entity.addTag<TNotRenderizable>(); 
            entity.eraseTag<TCollisionable>();
            entity.eraseTag<TDescription>();
            //auto& inventory = man_e.getInventory();
            //inventory.push_back(&entity);
		}else if(i == 1){
			man_e.defineCMP<CInformation>(entity, CInformation{.type_of_text=0, .description{"She died in 1986..."}, .descriptionPickable{""}});
		}else if(i == 2){
			entity.eraseTag<TDescription>();
			entity.eraseTag<TCollisionable>();
			man_e.defineCMP<CInformation>(entity, CInformation{.type_of_text=0, .description="" });
		}else if (i == 3){
			for (unsigned long int j = 0; j < 6;j++ ){
				std::size_t id = entity.getID();
				auto& e = man_e.getEntityByID(id+j);
				e.addTag<TNotRenderizable>();
			}
		}
	}

	GL.camera.Position = glm::vec3(0,1.5,-0.5); //repos
	GL.camera.Front.z *= -1;
	auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
	player_phy.x = 0; player_phy.y = 1.5; player_phy.z = -0.5;
	auto& candil = man_e.getEntityArray()[2];
	auto& model  = man_e.getEntityArray()[1];
	candil.addTag<TPlayer>();
	candil.eraseTag<Tpickable>();
	model.eraseTag<TNotRenderizable>();
	man_e.getEntityCMP<CRenderGL>(candil).modelMatrix.setPosition(0.8, -0.7, 0);
	GL.camera.LanternIsHeld=true;
}

void Levels::checkStatus_lvl5(Manentity_type& man_e, EngineGL& GL){
	for (unsigned long int i=0;i<man_e.getLevelsStatus().lvl_5_objects_status.size();++i){
		auto& entity = man_e.getEntityByID(man_e.getLevelsStatus().lvl_5_objects_status[i]);
		if (i == 0){
			entity.eraseTag<TCollisionable>();
			entity.eraseTag<TDoor>();

			auto& door1 = man_e.getEntityByID(entity.getID()-2);
			auto& door2 = man_e.getEntityByID(entity.getID()-1);
			auto& door1_phy = man_e.getEntityCMP<CPhysics>(door1);
			auto& door2_phy = man_e.getEntityCMP<CPhysics>(door2);

			door1_phy.x -= 2;
			door2_phy.x += 2;
			door1.eraseTag<TWall>();
			door2.eraseTag<TWall>();
		}else if (i==1){
			auto& cinfo_trampilla = man_e.getEntityCMP<CInformation>(entity);
			auto& puerta_izq = man_e.getEntityByID(entity.getID()+1);
            auto& puerta_drc = man_e.getEntityByID(entity.getID()+2);
            auto& rend_pizq  = man_e.getEntityCMP<CRenderGL>(puerta_izq);
            auto& rend_pdrc  = man_e.getEntityCMP<CRenderGL>(puerta_drc);
			rend_pizq.modelMatrix.Rotate(120,0,0,1);
            rend_pdrc.modelMatrix.Rotate(-120,0,0,1);
            cinfo_trampilla.descriptionPickable = "[E] Down stairs";
            cinfo_trampilla.description = "";
		}else if (i==2){
			entity.addTag<TNotRenderizable>(); 
			entity.eraseTag<TCollisionable>();
			entity.eraseTag<TDescription>();

			if (man_e.getLevelsStatus().lvl_Sotano_objects_status!=0){
				//enemy spawn
				auto despertar = [&](Entity& enemy){
				if (enemy.hasTag<TDummy>()){
					enemy.eraseTag<TDummy>();
				}
				auto& rend = man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix;
				rend = Model("assets/level1/enemigotext.obj", glm::vec3(0,1.5,-3));
				};
				man_e.foreach<Typelist<>,Typelist<TEnemy>>(despertar);
			}


		}
	}

	if (GL.camera.reposition_lvl_camera == 10){//4.59, .y = 0.13, .z = -53.41
		GL.camera.Position = glm::vec3(4.59,1.5,-50.41); //repos
		GL.camera.Front.z *= -1;
		auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
		player_phy.x = 4.59; player_phy.y = 1.5; player_phy.z = -50.41;
		GL.camera.reposition_lvl_camera = 0;
	}else{
		GL.camera.Position = glm::vec3(0,1.5,-0.5); //repos
		GL.camera.Front.z *= -1;
		auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
		player_phy.x = 0; player_phy.y = 1.5; player_phy.z = -0.5;
		GL.camera.reposition_lvl_camera = 0;
	}

	auto& candil = man_e.getEntityArray()[2];
	auto& model  = man_e.getEntityArray()[1];
	candil.addTag<TPlayer>();
	candil.eraseTag<Tpickable>();
	model.eraseTag<TNotRenderizable>();
	man_e.getEntityCMP<CRenderGL>(candil).modelMatrix.setPosition(0.8, -0.7, 0);
	GL.camera.LanternIsHeld=true;
}

void Levels::checkStatus_lvlY(Manentity_type& man_e, EngineGL& GL){
	GL.camera.Position = glm::vec3(0,1.5,-0.5); //repos
	GL.camera.Front.z *= -1;
	auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
	player_phy.x = 0; player_phy.y = 1.5; player_phy.z = -0.5;
	auto& candil = man_e.getEntityArray()[2];
	auto& model  = man_e.getEntityArray()[1];
	candil.addTag<TPlayer>();
	candil.eraseTag<Tpickable>();
	model.eraseTag<TNotRenderizable>();
	man_e.getEntityCMP<CRenderGL>(candil).modelMatrix.setPosition(0.8, -0.7, 0);
	GL.camera.LanternIsHeld=true;
}

void Levels::checkStatus_lvl_Sotano(Manentity_type& man_e, EngineGL& GL){
	if (man_e.getLevelsStatus().lvl_Sotano_objects_status != 0){
		auto& rueda = man_e.getEntityByID(man_e.getLevelsStatus().lvl_Sotano_objects_status);
		auto& rendrueda = man_e.getEntityCMP<CRenderGL>(rueda);

		rendrueda.modelMatrix.Scale(0.15,0.15,0.15);
		rueda.addTag<TNotRenderizable>();
		rueda.eraseTag<TCollisionable>();
		rueda.eraseTag<TDescription>();
		//auto& inventory = man_e.getInventory();
		//inventory.push_back(&rueda);

		auto dummy = [&](Entity& e){
			e.eraseTag<TNotRenderizable>();
			e.eraseTag<TDummy>();
		};
		man_e.foreach<Typelist<>, Typelist<TDummy>>(dummy);
	}
	
	
	GL.camera.Position = glm::vec3(0,1.5,-0.5); //repos
	GL.camera.Front.z *= -1;
	auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
	player_phy.x = 0; player_phy.y = 1.5; player_phy.z = -0.5;
	auto& candil = man_e.getEntityArray()[2];
	auto& model  = man_e.getEntityArray()[1];
	candil.addTag<TPlayer>();
	candil.eraseTag<Tpickable>();
	model.eraseTag<TNotRenderizable>();
	man_e.getEntityCMP<CRenderGL>(candil).modelMatrix.setPosition(0.8, -0.7, 0);
	GL.camera.LanternIsHeld=true;
}

void Levels::checkStatus_lvl_Maze(Manentity_type& man_e, EngineGL& GL){

	GL.camera.Position = glm::vec3(0,1.5,-0.5); //repos
	auto& player_phy = man_e.getEntityCMP<CPhysics>(man_e.getEntityArray()[0]);
	player_phy.x = 0; player_phy.y = 1.5; player_phy.z = -0.5;
	GL.camera.Front.z *= -1;
	auto& candil = man_e.getEntityArray()[2];
	auto& model  = man_e.getEntityArray()[1];
	candil.addTag<TPlayer>();
	candil.eraseTag<Tpickable>();
	model.eraseTag<TNotRenderizable>();
	man_e.getEntityCMP<CRenderGL>(candil).modelMatrix.setPosition(0.8, -0.7, 0);
	GL.camera.LanternIsHeld=true;
}
///////////////////////////////////////////////////////////////////////////////////////////////
// TIPOS DE TEXTOS EN DESCRIPCIONES															 //
//	0 -> description      1 linea permanente												 //
//  1 -> text_list		  2 lineas permanentes												 //	
//  2 -> text_list	      DIÁLOGO															 //
//  3 -> description	  Texto único desaparece con el tiempo (times_to_print_text = 100)	 //
///////////////////////////////////////////////////////////////////////////////////////////////


void Levels::load_lvl_1(Manentity_type& man_e, Sys& systems, EngineGL& GL){

//	Todas las entidades tienen que tener fisicas para tener las posiciones y poder renderizar
	InitSoundsLvl_1(systems.soundito);
	
	man_e.getLevelsStatus().actual = 1;
	//--------------------------------PLAYER---------------------------------------------------//

	////////////// PLAYER -- Collision box
	//	CMPS :  CRenderGL, CPhysics, CInput, CCollision
	//	TAGS : 	TPlayer, TCollider, TNotRenderizable
	auto& player = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CInput, CCollision, CHealth, CStamina, CSound>();	
	man_e.addTagToEntity<TPlayer>(player);
	man_e.addTagToEntity<TCollider>(player);
	man_e.addTagToEntity<TNotRenderizable>(player); //HACER UN CUBE ACORDE AL PLAYER
	man_e.defineCMP<CPhysics>(player, CPhysics{.x=0, .y=1.5, .z=-4});
	man_e.defineCMP<CRenderGL>(player, CRenderGL{.modelMatrix= Model("assets/level1/cube.obj", glm::vec3(0,1.5,-3))});
	man_e.defineCMP<CSound>(player, CSound{.s_mgr = &systems.soundito, .name{"surface"}, .eventvalue = 0,});

	GL.camera.Position = { 0, 1.5, -4};
	////////////// PLAYER -- Model
	//	CMPS :  CRenderGL, CPhysics
	//	TAGS : 	TPlayer
	auto& player_model = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.addTagToEntity<TPlayer>(player_model);
	man_e.addTagToEntity<TNotRenderizable>(player_model);
	man_e.defineCMP<CPhysics>(player_model, CPhysics{.x=0.7, .y=-0.5, .z=-2});
	man_e.defineCMP<CRenderGL>(player_model, CRenderGL{.modelMatrix= Model("assets/level1/brazo.obj", glm::vec3(0.7, -0.5, -2))}); 
	man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Scale(1.6,2,2);
	//man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Rotate(0, 0,1,0);
	////////////// PLAYER -- Model Candil with light
	//	CMPS :  CRenderGL, CPhysics, CPointLight
	//	TAGS : 	TPlayer
	auto& light = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CPointLight, CHealth, CSound, CCollision>(); //MIRAR BIEN
	//man_e.addTagToEntity<TPlayer>(light);
	man_e.addTagToEntity<TLantern>(light);
	man_e.addTagToEntity<TCollisionable>(light);
	man_e.addTagToEntity<Tpickable>(light);
	man_e.addTagToEntity<TScaleBoundingBox>(light);
	//man_e.addTagToEntity<TNotRenderizable>(light);
	man_e.defineCMP<CPhysics>(light,  CPhysics{.x=0.8, .y=0, .z=-45.5});
	man_e.defineCMP<CRenderGL>(light, CRenderGL{.modelMatrix = Model("assets/level1/Candil.obj", glm::vec3(0.8, -0.7, 0))});
	man_e.defineCMP<CSound>(light, CSound{.s_mgr= &systems.soundito}); 
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Scale(5,6,5);
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Rotate(90, 0,1,0);
	man_e.defineCMP<CPointLight>(light, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(light).setOff();

	//--------------------------------ENEMY---------------------------------------------------//

	////////////// ENEMY -- Enemy 1 with IA 
	//	CMPS :  CRenderGL, CIA, CPhysics
	//	TAGS : 	TEnemy
	//auto& enemy = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound>();
	//man_e.addTagToEntity<TEnemy>(enemy);
	//man_e.defineCMP<CPhysics>(enemy, CPhysics{.x = 0, .y = 1, .z = 0 , .vx = 1});
	//man_e.defineCMP<CIA>(enemy, CIA{.dt = &systems.dtree, .targets{
	//	glm::vec3{50.f,1.f,0.f} ,
	//	glm::vec3{ 0.f,1.f,50.f},
	//	glm::vec3{50.f,1.f,50.f},
	//	glm::vec3{0.f, 0.f, 0.f},
	//	
	//	
	//	}, .current = 0});
	//man_e.defineCMP<CSound>(enemy, CSound{.s_mgr = &systems.soundito});
	//man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix = Model("assets/level1/enemigo_prov.obj", glm::vec3(0, 0, 0));

	//--------------------------------BOUNDING BOX HELPER FOR OBJECTS WITH SMALL BB--------------------------------------------//
	auto& boundingbox = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(boundingbox);
	man_e.addTagToEntity<TBoundingBoxHelp>(boundingbox);
	man_e.defineCMP<CRenderGL>(boundingbox, CRenderGL{.modelMatrix = Model("assets/level1/boundingbox_help.obj", glm::vec3(0,0,0))});
	//--------------------------------CHURCH OBJECTS--------------------------------------------//
	////////////// IGLESIA Y MAPA  -- Mapa visual de la iglesia y el world
	//	CMPS : CRenderGL, CPhysics   
	//	TAGS : 	
	auto& iglesia = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();	
	//man_e.defineCMP<CPhysics>(iglesia, CPhysics{.y =0.1});
	man_e.defineCMP<CRenderGL>(iglesia, CRenderGL{ .modelMatrix = Model("assets/level1/mapa.obj", glm::vec3(0,-1.5,0))});

	////////////// ALTAR  WITH COLISIONS
	//	CMPS :  CRenderGL, CCollision, CPhysics 
	//	TAGS : 	TCollisionable, TWall
	auto& altar = man_e.createEntity_withCMPS< CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(altar);
	man_e.addTagToEntity<TWall>(altar);
	man_e.defineCMP<CPhysics>(altar, CPhysics{.x=1.8 , .y = 0, .z = -47});
	man_e.defineCMP<CRenderGL>(altar, CRenderGL{.modelMatrix = Model("assets/level1/Altar_ConCosas.obj", glm::vec3(0,0,0))});

	auto& altar_izq_txt = man_e.createEntity_withCMPS< CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(altar_izq_txt);
	man_e.addTagToEntity<TDescription>(altar_izq_txt);
	man_e.addTagToEntity<TNotRenderizable>(altar_izq_txt);
	man_e.addTagToEntity<TScaleBoundingBox>(altar_izq_txt);
	man_e.defineCMP<CPhysics>(altar_izq_txt, CPhysics{.x=-2 , .y = 0, .z = -47});
	man_e.defineCMP<CRenderGL>(altar_izq_txt, CRenderGL{.modelMatrix = Model("assets/level1/Altar_ConCosas.obj", glm::vec3(0,0,0))});
	auto& altar_drc_txt = man_e.createEntity_withCMPS< CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(altar_drc_txt);
	man_e.addTagToEntity<TDescription>(altar_drc_txt);
	man_e.addTagToEntity<TScaleBoundingBox>(altar_drc_txt);
	man_e.addTagToEntity<TNotRenderizable>(altar_drc_txt);
	man_e.defineCMP<CPhysics>(altar_drc_txt, CPhysics{.x=4.3 , .y = 0, .z = -47});
	man_e.defineCMP<CRenderGL>(altar_drc_txt, CRenderGL{.modelMatrix = Model("assets/level1/Altar_ConCosas.obj", glm::vec3(0,0,0))});

	////////////// BANCS WITH COLISIONS
	//	CMPS :  CRenderGL, CCollision, CPhysics 
	//	TAGS : 	TCollisionable, TWall
	auto& banco1 = man_e.createEntity_withCMPS<CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(banco1);
	man_e.addTagToEntity<TWall>(banco1);
	man_e.defineCMP<CPhysics>(banco1, CPhysics{.x =2.70, .y=0.32 ,.z= -40.15});
	man_e.defineCMP<CRenderGL>(banco1, CRenderGL{.modelMatrix = Model("assets/level1/Banco.obj", glm::vec3(0,0,0))});
	auto& banco2 = man_e.createEntity_withCMPS<CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(banco2);
	man_e.addTagToEntity<TWall>(banco2);
	man_e.defineCMP<CPhysics>(banco2, CPhysics{.x =-0.51, .y=0.32 ,.z= -40.14});
	man_e.defineCMP<CRenderGL>(banco2, CRenderGL{.modelMatrix = Model("assets/level1/Banco.obj", glm::vec3(0,0,0))});
	auto& banco3 = man_e.createEntity_withCMPS<CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(banco3);
	man_e.addTagToEntity<TWall>(banco3);
	man_e.defineCMP<CPhysics>(banco3, CPhysics{.x =2.77, .y=0.32 ,.z= -43.05});
	man_e.defineCMP<CRenderGL>(banco3, CRenderGL{.modelMatrix = Model("assets/level1/Banco.obj", glm::vec3(0,0,0))});
	auto& banco4 = man_e.createEntity_withCMPS<CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(banco4);
	man_e.addTagToEntity<TWall>(banco4);
	man_e.defineCMP<CPhysics>(banco4, CPhysics{.x =-0.49, .y=0.32 ,.z= -43.04});
	man_e.defineCMP<CRenderGL>(banco4, CRenderGL{.modelMatrix = Model("assets/level1/Banco.obj", glm::vec3(0,0,0))});

	man_e.getEntityCMP<CRenderGL>(banco1).modelMatrix.Rotate(-17, 0, 1, 0);
	man_e.getEntityCMP<CRenderGL>(banco2).modelMatrix.Rotate(11, 0, 1, 0);
	man_e.getEntityCMP<CRenderGL>(banco3).modelMatrix.Rotate(20, 0, 1, 0);
	man_e.getEntityCMP<CRenderGL>(banco4).modelMatrix.Rotate(-14, 0, 1, 0);
	////////////// Bounding Boxes CHURCH
	//	CMPS :  CRenderGL, CCollision, CPhysics 
	//	TAGS : 	TCollisionable, TWall, TNotRenderizable
	auto& iglesia_Pared_1= man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(iglesia_Pared_1);
	man_e.addTagToEntity<TCollisionable>(iglesia_Pared_1);
	man_e.addTagToEntity<TWall>(iglesia_Pared_1);
	man_e.defineCMP<CPhysics>(iglesia_Pared_1, CPhysics{.x=-1.99, .y = 1, .z = -43.68});
	man_e.defineCMP<CRenderGL>(iglesia_Pared_1, CRenderGL{.modelMatrix = Model("assets/level1/Iglesia_Pared_1.obj", glm::vec3(0,0,0))});
	auto& iglesia_Pared_2= man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(iglesia_Pared_2);
	man_e.addTagToEntity<TCollisionable>(iglesia_Pared_2);
	man_e.addTagToEntity<TWall>(iglesia_Pared_2);
	man_e.defineCMP<CPhysics>(iglesia_Pared_2, CPhysics{.x=6.37 , .y = 1, .z = -46.65});
	man_e.defineCMP<CRenderGL>(iglesia_Pared_2, CRenderGL{.modelMatrix = Model("assets/level1/Iglesia_Pared_2.obj", glm::vec3(0,0,0))});
	auto& iglesia_Pared_3= man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(iglesia_Pared_3);
	man_e.addTagToEntity<TCollisionable>(iglesia_Pared_3);
	man_e.addTagToEntity<TWall>(iglesia_Pared_3);
	man_e.defineCMP<CPhysics>(iglesia_Pared_3, CPhysics{.x=-0.54 , .y = 1, .z = -36.60});
	man_e.defineCMP<CRenderGL>(iglesia_Pared_3, CRenderGL{.modelMatrix = Model("assets/level1/Iglesia_Pared_3.obj", glm::vec3(0,0,0))});
	auto& iglesia_Pared_4= man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(iglesia_Pared_4);
	man_e.addTagToEntity<TCollisionable>(iglesia_Pared_4);
	man_e.addTagToEntity<TWall>(iglesia_Pared_4);
	man_e.defineCMP<CPhysics>(iglesia_Pared_4, CPhysics{.x=2.41 , .y = 1, .z = -36.35});
	man_e.defineCMP<CRenderGL>(iglesia_Pared_4, CRenderGL{.modelMatrix = Model("assets/level1/Iglesia_Pared_4.obj", glm::vec3(0,0,0))});
	auto& iglesia_Pared_5= man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(iglesia_Pared_5);
	man_e.addTagToEntity<TCollisionable>(iglesia_Pared_5);
	man_e.addTagToEntity<TWall>(iglesia_Pared_5);
	man_e.defineCMP<CPhysics>(iglesia_Pared_5, CPhysics{.x=-1.44 , .y = 1, .z = -37.52});
	man_e.defineCMP<CRenderGL>(iglesia_Pared_5, CRenderGL{.modelMatrix = Model("assets/level1/Iglesia_Pared_5.obj", glm::vec3(0,0,0))});
	auto& iglesia_Pared_6= man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(iglesia_Pared_6);
	man_e.addTagToEntity<TCollisionable>(iglesia_Pared_6);
	man_e.addTagToEntity<TWall>(iglesia_Pared_6);
	man_e.defineCMP<CPhysics>(iglesia_Pared_6, CPhysics{.x=4.23, .y = 1, .z = -37.48});
	man_e.defineCMP<CRenderGL>(iglesia_Pared_6, CRenderGL{.modelMatrix = Model("assets/level1/Iglesia_Pared_6.obj", glm::vec3(0,0,0))});
	auto& iglesia_Pared_7= man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(iglesia_Pared_7);
	man_e.addTagToEntity<TCollisionable>(iglesia_Pared_7);
	man_e.addTagToEntity<TWall>(iglesia_Pared_7);
	man_e.defineCMP<CPhysics>(iglesia_Pared_7, CPhysics{.x=6.25 , .y = 1, .z = -39.13});
	man_e.defineCMP<CRenderGL>(iglesia_Pared_7, CRenderGL{.modelMatrix = Model("assets/level1/Iglesia_Pared_7.obj", glm::vec3(0,0,0))});
	auto& iglesia_Pared_8= man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(iglesia_Pared_8);
	man_e.addTagToEntity<TCollisionable>(iglesia_Pared_8);
	man_e.addTagToEntity<TWall>(iglesia_Pared_8);
	man_e.defineCMP<CPhysics>(iglesia_Pared_8, CPhysics{.x=2.20 , .y = 1, .z = -49.44});
	man_e.defineCMP<CRenderGL>(iglesia_Pared_8, CRenderGL{.modelMatrix = Model("assets/level1/Iglesia_Pared_8.obj", glm::vec3(0,0,0))});

	//--------------------------------FENCE COLLISION--------------------------------------------//

	auto& coll_valla_1 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_1 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_1 );
	man_e.addTagToEntity<TWall>(coll_valla_1 );
	man_e.defineCMP<CPhysics>(coll_valla_1 , CPhysics{.x= 0.25 , .y = 0.82, .z = 0.95 });
	man_e.defineCMP<CRenderGL>(coll_valla_1 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.obj", glm::vec3(0,0,0))});
	auto& coll_valla_2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_2 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_2 );
	man_e.addTagToEntity<TWall>(coll_valla_2 );
	man_e.defineCMP<CPhysics>(coll_valla_2 , CPhysics{.x= -1.65 , .y = 0.82, .z = -4.57 });
	man_e.defineCMP<CRenderGL>(coll_valla_2 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.001.obj", glm::vec3(0,0,0))});
	auto& coll_valla_3 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_3 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_3 );
	man_e.addTagToEntity<TWall>(coll_valla_3 );
	man_e.defineCMP<CPhysics>(coll_valla_3 , CPhysics{.x= -7.19 , .y = 0.82, .z = -9.62 });
	man_e.defineCMP<CRenderGL>(coll_valla_3 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.002.obj", glm::vec3(0,0,0))});
	auto& coll_valla_4 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_4 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_4 );
	man_e.addTagToEntity<TWall>(coll_valla_4 );
	man_e.defineCMP<CPhysics>(coll_valla_4 , CPhysics{.x= 0.17 , .y = 0.82, .z = -13.91 });
	man_e.defineCMP<CRenderGL>(coll_valla_4 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.003.obj", glm::vec3(0,0,0))});
	auto& coll_valla_5 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_5 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_5 );
	man_e.addTagToEntity<TWall>(coll_valla_5 );
	man_e.defineCMP<CPhysics>(coll_valla_5 , CPhysics{.x= 0.17 , .y = 0.82, .z = -30.88 });
	man_e.defineCMP<CRenderGL>(coll_valla_5 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.004.obj", glm::vec3(0,0,0))});
	auto& coll_valla_6 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_6 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_6 );
	man_e.addTagToEntity<TWall>(coll_valla_6 );
	man_e.defineCMP<CPhysics>(coll_valla_6 , CPhysics{.x= -12.14 , .y = 0.82, .z = -11.81 });
	man_e.defineCMP<CRenderGL>(coll_valla_6 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.005.obj", glm::vec3(0,0,0))});
	auto& coll_valla_7 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_7 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_7 );
	man_e.addTagToEntity<TWall>(coll_valla_7 );
	man_e.defineCMP<CPhysics>(coll_valla_7 , CPhysics{.x= 9.72 , .y = 0.82, .z = -9.69 });
	man_e.defineCMP<CRenderGL>(coll_valla_7 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.006.obj", glm::vec3(0,0,0))});
	auto& coll_valla_8 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_8 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_8 );
	man_e.addTagToEntity<TWall>(coll_valla_8 );
	man_e.defineCMP<CPhysics>(coll_valla_8 , CPhysics{.x= 2.4 , .y = 0.82, .z = -4.45 });
	man_e.defineCMP<CRenderGL>(coll_valla_8 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.007.obj", glm::vec3(0,0,0))});
	auto& coll_valla_9 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_9 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_9 );
	man_e.addTagToEntity<TWall>(coll_valla_9 );
	man_e.defineCMP<CPhysics>(coll_valla_9 , CPhysics{.x= 16.88 , .y = 0.82, .z = -22.31 });
	man_e.defineCMP<CRenderGL>(coll_valla_9 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.008.obj", glm::vec3(0,0,0))});
	auto& coll_valla_10 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_10 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_10 );
	man_e.addTagToEntity<TWall>(coll_valla_10 );
	man_e.defineCMP<CPhysics>(coll_valla_10 , CPhysics{.x= 12.33 , .y = 0.82, .z = -22.31 });
	man_e.defineCMP<CRenderGL>(coll_valla_10 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.009.obj", glm::vec3(0,0,0))});
	auto& coll_valla_11 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_11 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_11 );
	man_e.addTagToEntity<TWall>(coll_valla_11 );
	man_e.defineCMP<CPhysics>(coll_valla_11 , CPhysics{.x = 9.92 , .y = 0.82, .z = -35.07 });
	man_e.defineCMP<CRenderGL>(coll_valla_11 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.010.obj", glm::vec3(0,0,0))});
	auto& coll_valla_12 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_12 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_12 );
	man_e.addTagToEntity<TWall>(coll_valla_12 );
	man_e.defineCMP<CPhysics>(coll_valla_12 , CPhysics{.x= -6.23 , .y = 0.82, .z = -35.24 });
	man_e.defineCMP<CRenderGL>(coll_valla_12 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.011.obj", glm::vec3(0,0,0))});
	auto& coll_valla_13 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_13 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_13 );
	man_e.addTagToEntity<TWall>(coll_valla_13 );
	man_e.defineCMP<CPhysics>(coll_valla_13 , CPhysics{.x= -18.76 , .y = 0.82, .z = -38.66 });
	man_e.defineCMP<CRenderGL>(coll_valla_13 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.012.obj", glm::vec3(0,0,0))});
	auto& coll_valla_14 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_14 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_14 );
	man_e.addTagToEntity<TWall>(coll_valla_14 );
	man_e.defineCMP<CPhysics>(coll_valla_14 , CPhysics{.x= -19.05 , .y = 0.82, .z = -20.72 });
	man_e.defineCMP<CRenderGL>(coll_valla_14 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.013.obj", glm::vec3(0,0,0))});
	auto& coll_valla_15 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_15 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_15 );
	man_e.addTagToEntity<TWall>(coll_valla_15 );
	man_e.defineCMP<CPhysics>(coll_valla_15 , CPhysics{.x= -26.13, .y = 0.82, .z = -29.77 });
	man_e.defineCMP<CRenderGL>(coll_valla_15 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.014.obj", glm::vec3(0,0,0))});
	auto& coll_valla_16 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_16 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_16 );
	man_e.addTagToEntity<TWall>(coll_valla_16 );
	man_e.defineCMP<CPhysics>(coll_valla_16 , CPhysics{.x= -11.85 , .y = 0.82, .z = -25.77 });
	man_e.defineCMP<CRenderGL>(coll_valla_16 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.015.obj", glm::vec3(0,0,0))});
	auto& coll_valla_17 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_17 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_17 );
	man_e.addTagToEntity<TWall>(coll_valla_17 );
	man_e.defineCMP<CPhysics>(coll_valla_17 , CPhysics{.x= -11.36 , .y = 0.82, .z = -37.18 });
	man_e.defineCMP<CRenderGL>(coll_valla_17 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.016.obj", glm::vec3(0,0,0))});
	auto& coll_valla_18 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_18 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_18 );
	man_e.addTagToEntity<TWall>(coll_valla_18 );
	man_e.defineCMP<CPhysics>(coll_valla_18 , CPhysics{.x= 2.77 , .y = 0.82, .z = -36.02 });
	man_e.defineCMP<CRenderGL>(coll_valla_18 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.017.obj", glm::vec3(0,0,0))});
	auto& coll_valla_19 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_19 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_19 );
	man_e.addTagToEntity<TWall>(coll_valla_19 );
	man_e.defineCMP<CPhysics>(coll_valla_19 , CPhysics{.x= -1.21 , .y = 0.82, .z = -36.18 });
	man_e.defineCMP<CRenderGL>(coll_valla_19 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.018.obj", glm::vec3(0,0,0))});
	auto& coll_valla_20 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_20 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_20 );
	man_e.addTagToEntity<TWall>(coll_valla_20 );
	man_e.defineCMP<CPhysics>(coll_valla_20 , CPhysics{.x= 22.36 , .y = 0.82, .z = -39.33 });
	man_e.defineCMP<CRenderGL>(coll_valla_20 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.019.obj", glm::vec3(0,0,0))});
	auto& coll_valla_21 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_21 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_21 );
	man_e.addTagToEntity<TWall>(coll_valla_21 );
	man_e.defineCMP<CPhysics>(coll_valla_21 , CPhysics{.x= 22.36 , .y = 0.82, .z = -44.08 });
	man_e.defineCMP<CRenderGL>(coll_valla_21 , CRenderGL{.modelMatrix = Model("assets/level1/Colision_Valla.020.obj", glm::vec3(0,0,0))});


	//--------------------------------WORLD OBJECTS--------------------------------------------//

	////////////// COCHE  
	//	CMPS : CInformation, CRenderGL, CCollision, CPhysics   // falsta sound
	//	TAGS : 	TCollisionable, TWall
	auto& coche = man_e.createEntity_withCMPS< CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(coche);
	man_e.addTagToEntity<TWall>(coche);
	man_e.defineCMP<CRenderGL>(coche, CRenderGL{.modelMatrix = Model("assets/level1/coche.obj", glm::vec3(0,0,0))});
	man_e.getEntityCMP<CRenderGL>(coche).modelMatrix.Scale(1.2,1.2,1.2);
	man_e.getEntityCMP<CRenderGL>(coche).modelMatrix.Rotate(180, 0, 1, 0);

	auto& coche_txt = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(coche_txt);
	man_e.addTagToEntity<TDescription>(coche_txt);
	man_e.addTagToEntity<TNotRenderizable>(coche_txt);
	man_e.addTagToEntity<TCarEventFinal>(coche_txt);
	man_e.defineCMP<CPhysics>(coche_txt, CPhysics{.z = -3});
	man_e.defineCMP<CRenderGL>(coche_txt, CRenderGL{.modelMatrix = Model("assets/level1/boundingbox_help.obj", glm::vec3(0,0,0))});
/*
	auto& cuervo  = man_e.createEntity_withCMPS<CPhysics, CRenderGL, CAnimation>();
	man_e.addTagToEntity<TNotRenderizable>(cuervo);
	man_e.getEntityCMP<CRenderGL>(cuervo).modelMatrix = Model("assets/animaciones/animCuervo.dae", glm::vec3(0, 0, 0));
	//man_e.getEntityCMP<CRenderGL>(cuervo).modelMatrix.Rotate(180,0,1,0);
	man_e.getEntityCMP<CAnimation>(cuervo).animation = Animation("assets/animaciones/animCuervo.dae", &man_e.getEntityCMP<CRenderGL>(cuervo).modelMatrix);
	man_e.getEntityCMP<CAnimation>(cuervo).animator = Animator(&man_e.getEntityCMP<CAnimation>(cuervo).animation);
	man_e.defineCMP<CPhysics>(cuervo , CPhysics{.x= 0 , .y = 1.5, .z = 0 });
	man_e.getEntityCMP<CRenderGL>(cuervo).modelMatrix.Rotate(90, 0, 0, 1);
	man_e.getEntityCMP<CRenderGL>(cuervo).modelMatrix.Rotate(90, 1, 0, 0);
*/


	////////////// TOCON  
	//	CMPS : CRenderGL, CPhysics   // falsta sound
	//	TAGS : 
	auto& tocon = man_e.createEntity_withCMPS<CPhysics, CRenderGL>();
	man_e.defineCMP<CPhysics>(tocon, CPhysics{.x =-21.88, .y=0.18 ,.z= -32.14});
	man_e.defineCMP<CRenderGL>(tocon, CRenderGL{.modelMatrix = Model("assets/level1/Tocon.obj", glm::vec3(0,0,0))});
	////////////// TUMBAS  
	//	CMPS :  CRenderGL, CCollision, CPhysics   // falsta sound
	//	TAGS : 	TCollisionable, TWall
	auto& tumba1 = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(tumba1);
	man_e.addTagToEntity<TWall>(tumba1);
	man_e.defineCMP<CPhysics>(tumba1, CPhysics{.x =-16.59, .y=0.19 ,.z= -23.08});
	man_e.defineCMP<CRenderGL>(tumba1, CRenderGL{.modelMatrix = Model("assets/level1/Tumba1.obj", glm::vec3(0,0,0))});
	auto& tumba1_txt = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(tumba1_txt);
	man_e.addTagToEntity<TDescription>(tumba1_txt);
	man_e.addTagToEntity<TNotRenderizable>(tumba1_txt);
	man_e.defineCMP<CPhysics>(tumba1_txt, CPhysics{.x =-16.59, .y=0.19 ,.z= -25.98});
	man_e.defineCMP<CRenderGL>(tumba1_txt, CRenderGL{.modelMatrix = Model("assets/level1/boundingbox_help.obj", glm::vec3(0,0,0))});

	auto& tumba2 = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(tumba2);
	man_e.addTagToEntity<TWall>(tumba2);
	man_e.defineCMP<CPhysics>(tumba2, CPhysics{.x =-22.03, .y=0.12 ,.z= -23.63});
	man_e.defineCMP<CRenderGL>(tumba2, CRenderGL{.modelMatrix = Model("assets/level1/Tumba2.obj", glm::vec3(0,0,0))});
	auto& tumba2_txt = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(tumba2_txt);
	man_e.addTagToEntity<TDescription>(tumba2_txt);
	man_e.addTagToEntity<TNotRenderizable>(tumba2_txt);
	man_e.defineCMP<CPhysics>(tumba2_txt, CPhysics{.x =-22.03, .y=0.12 ,.z= -25.98});
	man_e.defineCMP<CRenderGL>(tumba2_txt, CRenderGL{.modelMatrix = Model("assets/level1/boundingbox_help.obj", glm::vec3(0,0,0))});

	auto& tumba3 = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(tumba3);
	man_e.addTagToEntity<TWall>(tumba3);
	man_e.defineCMP<CPhysics>(tumba3, CPhysics{.x =-23.61, .y=0.06 ,.z= -27.17});
	man_e.defineCMP<CRenderGL>(tumba3, CRenderGL{.modelMatrix = Model("assets/level1/Tumba3.obj", glm::vec3(0,0,0))});
	auto& tumba3_txt = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(tumba3_txt);
	man_e.addTagToEntity<TDescription>(tumba3_txt);
	man_e.addTagToEntity<TNotRenderizable>(tumba3_txt);
	man_e.defineCMP<CPhysics>(tumba3_txt, CPhysics{.x =-23.61, .y=0.06 ,.z= -27.98});
	man_e.defineCMP<CRenderGL>(tumba3_txt, CRenderGL{.modelMatrix = Model("assets/level1/boundingbox_help.obj", glm::vec3(0,0,0))});

	auto& tumba4 = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(tumba4);
	man_e.addTagToEntity<TWall>(tumba4);
	man_e.defineCMP<CPhysics>(tumba4, CPhysics{.x =-19.04, .y=0.05 ,.z= -22.88});
	man_e.defineCMP<CRenderGL>(tumba4, CRenderGL{.modelMatrix = Model("assets/level1/Tumba4.obj", glm::vec3(0,0,0))});
	auto& tumba4_txt = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(tumba4_txt);
	man_e.addTagToEntity<TDescription>(tumba4_txt);
	man_e.addTagToEntity<TNotRenderizable>(tumba4_txt);
	man_e.defineCMP<CPhysics>(tumba4_txt, CPhysics{.x =-19.04, .y=0.05 ,.z= -24.88});
	man_e.defineCMP<CRenderGL>(tumba4_txt, CRenderGL{.modelMatrix = Model("assets/level1/boundingbox_help.obj", glm::vec3(0,0,0))});

	//--------------------------------BURNABLE--------------------------------------------//
	////////////// BURNABLE -- SOLID -- FALTA HACER QUE SE QUEME   
	//	CMPS : CInformation, CRenderGL, CCollision, CPhysics   // falsta sound
	//	TAGS : 	TCollisionable, TWall
	auto& quemable_iglesia = man_e.createEntity_withCMPS< CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(quemable_iglesia);
	man_e.addTagToEntity<TWall>(quemable_iglesia);
	man_e.defineCMP<CPhysics>(quemable_iglesia, CPhysics{.x =6.51, .y=0.32 ,.z= -42.17});
	man_e.defineCMP<CRenderGL>(quemable_iglesia, CRenderGL{.modelMatrix = Model("assets/level1/Enredaderas.obj", glm::vec3(0,0,0))});

	auto& quemable_iglesia_txt = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CReference, CSound>();
	man_e.addTagToEntity<TCollisionable>(quemable_iglesia_txt);
	man_e.addTagToEntity<TBurnable>(quemable_iglesia_txt);
	man_e.addTagToEntity<TDescription>(quemable_iglesia_txt);
	man_e.addTagToEntity<TNotRenderizable>(quemable_iglesia_txt);
	man_e.defineCMP<CSound>(quemable_iglesia_txt, CSound{.s_mgr = &systems.soundito});
	man_e.defineCMP<CReference>(quemable_iglesia_txt, CReference{.id_reference = quemable_iglesia.getID()});
	man_e.defineCMP<CPhysics>(quemable_iglesia_txt, CPhysics{.x =4.51, .y=0.32 ,.z= -42.17});
	man_e.defineCMP<CRenderGL>(quemable_iglesia_txt, CRenderGL{.modelMatrix = Model("assets/level1/boundingbox_help.obj", glm::vec3(0,0,0))});

	//--------------------------------DOORS & KEYS--------------------------------------------//
	////////////// CHURCH KEY -- SOLID -- FALTA HACER QUE SE QUEME   
	//	CMPS : CInformation, CRenderGL, CCollision, CPhysics, CPng 
	//	TAGS : 	TCollisionable, TPickable
	auto& key_church = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CPng, CSound>();
	man_e.addTagToEntity<TCollisionable>(key_church);
	man_e.addTagToEntity<TScaleBoundingBox>(key_church);
	man_e.addTagToEntity<Tpickable>(key_church);
	man_e.addTagToEntity<TDoorKeyChurch>(key_church);
	man_e.addTagToEntity<TDescription>(key_church);
	man_e.defineCMP<CPhysics>(key_church, CPhysics{.x =-21.88, .y=0.55 ,.z= -32.14});
	man_e.defineCMP<CPng>(key_church, CPng{.icono = Model("assets/level1/icono_llave.obj", glm::vec3(-0.70,0.42,0))});
	man_e.getEntityCMP<CPng>(key_church).icono.Rotate(90,0,1,1);
	man_e.getEntityCMP<CRenderGL>(key_church).modelMatrix.Rotate(90,0,0,1);
	man_e.getEntityCMP<CPng>(key_church).icono.Scale(0.15,0.2,0.2);
	man_e.defineCMP<CRenderGL>(key_church, CRenderGL{.modelMatrix = Model("assets/level1/llave.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CSound>(key_church, CSound{.s_mgr = &systems.soundito});
	////////////// CHURCH DOOR -- SOLID -- AND LATER NOT WALL  
	//	CMPS : CInformation, CRenderGL, CCollision, CPhysics 
	//	TAGS : 	TCollisionable, TDoor, TWall, TDescription
	auto& church_door = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CSound>();
	man_e.addTagToEntity<TCollisionable>(church_door);
	man_e.addTagToEntity<TWall>(church_door);
	man_e.defineCMP<CPhysics>(church_door, CPhysics{.x = 0.29 , .y = 0, .z = -35.61});
	man_e.defineCMP<CRenderGL>(church_door, CRenderGL{.modelMatrix = Model("assets/level1/puerta.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CSound>(church_door, CSound{.s_mgr = &systems.soundito});

	auto& church_door_text = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CReference, CSound>();
	man_e.addTagToEntity<TCollisionable>(church_door_text);
	man_e.addTagToEntity<TDescription>(church_door_text);	
	man_e.addTagToEntity<TNotRenderizable>(church_door_text);
	man_e.addTagToEntity<TDoor>(church_door_text);
	man_e.defineCMP<CReference>(church_door_text, CReference{.id_reference = church_door.getID()});
	man_e.defineCMP<CPhysics>(church_door_text, CPhysics{.x = 0.49 , .y = 0.99, .z = -34.61});
	man_e.defineCMP<CRenderGL>(church_door_text, CRenderGL{.modelMatrix = Model("assets/level1/boundingbox_help.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CSound>(church_door_text, CSound{.s_mgr = &systems.soundito});
	//--------------------------------HOUSE--------------------------------------------//
	////////////// HAUSE -- SOLID -- AND TP 
	//	CMPS :  CRenderGL, CCollision, CPhysics 
	//	TAGS : 	TCollisionable, TTransition

	auto& casa_hub = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CIDLvl>();
	man_e.addTagToEntity<TCollisionable>(casa_hub);
	man_e.addTagToEntity<TTransition>(casa_hub);
	man_e.addTagToEntity<TNotRenderizable>(casa_hub);
	//man_e.addTagToEntity<TWall>(casa_hub); cambiar colision y modelo
	man_e.defineCMP<CPhysics>(casa_hub, CPhysics{.x = 36.5 , .y = -0.2 , .z = -42});
	man_e.defineCMP<CRenderGL>(casa_hub, CRenderGL{.modelMatrix = Model("assets/level1/caja1.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CIDLvl>(casa_hub, CIDLvl{.lvlid = 2});
	auto& casa_hub_visual = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();
	man_e.defineCMP<CPhysics>(casa_hub_visual, CPhysics{.x = 50 , .y = -0.2 , .z = -42});
	man_e.defineCMP<CRenderGL>(casa_hub_visual, CRenderGL{.modelMatrix = Model("assets/level2/casa.obj", glm::vec3(0,0,0))});


	//--------------------------------INSTANCES--------------------------------------------//

	////////////////INSTANCIA VALLA PALOS VERTICALES
	//	CMPS:  CRenderGL, CPhysics
	//  TAGS: TInstance, TNotRenderizable
	auto& valla_pico = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(valla_pico);
	man_e.addTagToEntity<TNotRenderizable>(valla_pico);
	man_e.defineCMP<CRenderGL>(valla_pico, CRenderGL{.modelMatrix= Model("assets/level1/Valla_pico.obj", glm::vec3(0,0,0)),.amount=0, .instancePath="assets/level1/instances_Valla_pico.txt"});
	////////////////INSTANCIA VALLA MADERAS HORIZONTALES
	//	CMPS:  CRenderGL, CPhysics
	//  TAGS: TInstance, TNotRenderizable
	auto& valla_tablones = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(valla_tablones);
	man_e.addTagToEntity<TNotRenderizable>(valla_tablones);
	man_e.defineCMP<CRenderGL>(valla_tablones, CRenderGL{.modelMatrix= Model("assets/level1/Valla_tablones.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/level1/instances_Valla_tablones.txt"});

	auto& maiz = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(maiz);
	man_e.addTagToEntity<TNotRenderizable>(maiz);
	man_e.defineCMP<CRenderGL>(maiz, CRenderGL{.modelMatrix= Model("assets/level1/CornLP.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/level1/maiz_instances.txt",.iscorn=true});

	// Prueba de sonidos

	auto& cuervos_sonido = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CSound>();
	man_e.addTagToEntity<TCollisionable>(cuervos_sonido);
	man_e.addTagToEntity<TSEvent>(cuervos_sonido);
	man_e.addTagToEntity<TJumpscare>(cuervos_sonido);
	man_e.addTagToEntity<TNotRenderizable>(cuervos_sonido);
	man_e.addTagToEntity<TDescription>(cuervos_sonido);
	man_e.defineCMP<CPhysics>(cuervos_sonido, CPhysics{.x = -13.5  , .y = 1, .z = -33});
	man_e.defineCMP<CRenderGL>(cuervos_sonido, CRenderGL{.modelMatrix = Model("assets/level1/try.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CSound>(cuervos_sonido, CSound{.s_mgr = &systems.soundito, .eventvalue = 4.15f});
	man_e.getEntityCMP<CRenderGL>(cuervos_sonido).modelMatrix.Scale(0.5,0.5,0.5);

	if (man_e.getLevelsStatus().lvl_1_objects_status.size() == 0 ){
		auto& iglesia_sonido = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CSound>();
		man_e.addTagToEntity<TNotRenderizable>(iglesia_sonido);
		man_e.addTagToEntity<TCollisionable>(iglesia_sonido);
		man_e.addTagToEntity<TSEvent>(iglesia_sonido);
		man_e.defineCMP<CPhysics>(iglesia_sonido, CPhysics{.x = 1  , .y = 1, .z = -36});
		man_e.defineCMP<CRenderGL>(iglesia_sonido, CRenderGL{.modelMatrix = Model("assets/level1/cube.obj", glm::vec3(0,0,0))});
		man_e.defineCMP<CSound>(iglesia_sonido, CSound{.s_mgr = &systems.soundito, .eventvalue = 0.58f});
	}else{
		auto& iglesia_sonido = man_e.createEntity_withCMPS<>();
		iglesia_sonido.addTag<TNotRenderizable>();
	}

	auto& yesquero = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CPng>();
	man_e.addTagToEntity<TCollisionable>(yesquero);
	man_e.addTagToEntity<TScaleBoundingBox>(yesquero);
	man_e.addTagToEntity<Tpickable>(yesquero);
	man_e.addTagToEntity<TYesquero>(yesquero);
	man_e.addTagToEntity<TDescription>(yesquero);
	man_e.defineCMP<CPhysics>(yesquero, CPhysics{.x =-0.51, .y=0.42 ,.z= -40.14});
	man_e.getEntityCMP<CRenderGL>(yesquero).modelMatrix.Rotate(90,0,0,1);
	man_e.defineCMP<CRenderGL>(yesquero, CRenderGL{.modelMatrix = Model("assets/level1/aceite.obj", glm::vec3(0,0,0))});

	auto& texto_1 = man_e.createEntity_withCMPS<CInformation ,CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TDescription>(texto_1);
	man_e.addTagToEntity<TCollisionable>(texto_1);
	man_e.addTagToEntity<TNotRenderizable>(texto_1);
	man_e.defineCMP<CPhysics>(texto_1, CPhysics{.x =7.80, .y=0 ,.z= -11.43});
	man_e.defineCMP<CRenderGL>(texto_1, CRenderGL{.modelMatrix = Model("assets/level1/caja1.obj", glm::vec3(0,0,0))});
	auto& texto_2 = man_e.createEntity_withCMPS<CInformation ,CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TDescription>(texto_2);
	man_e.addTagToEntity<TCollisionable>(texto_2);
	man_e.addTagToEntity<TNotRenderizable>(texto_2);
	man_e.defineCMP<CPhysics>(texto_2, CPhysics{.x =14, .y=0 ,.z= -21.29});
	man_e.defineCMP<CRenderGL>(texto_2, CRenderGL{.modelMatrix = Model("assets/level1/caja2.obj", glm::vec3(0,0,0))});

	auto& texto_cuadro = man_e.createEntity_withCMPS<CInformation ,CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TDescription>(texto_cuadro);
	man_e.addTagToEntity<TCollisionable>(texto_cuadro);
	man_e.addTagToEntity<TScaleBoundingBox>(texto_cuadro);
	man_e.addTagToEntity<TNotRenderizable>(texto_cuadro);
	man_e.defineCMP<CPhysics>(texto_cuadro, CPhysics{.x =4.75, .y=0 ,.z= -39});
	man_e.defineCMP<CRenderGL>(texto_cuadro, CRenderGL{.modelMatrix = Model("assets/level1/cube.obj", glm::vec3(0,0,0))});

	auto& texto_final1 = man_e.createEntity_withCMPS<CInformation ,CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TDescription>(texto_final1);
	man_e.addTagToEntity<TCollisionable>(texto_final1);
	man_e.addTagToEntity<TNotRenderizable>(texto_final1);
	man_e.defineCMP<CPhysics>(texto_final1, CPhysics{.x = 12 , .y = -0.2 , .z = -42});
	man_e.defineCMP<CRenderGL>(texto_final1, CRenderGL{.modelMatrix = Model("assets/level1/caja1.obj", glm::vec3(0,0,0))});
	auto& texto_final2 = man_e.createEntity_withCMPS<CInformation ,CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TDescription>(texto_final2);
	man_e.addTagToEntity<TCollisionable>(texto_final2);
	man_e.addTagToEntity<TScaleBoundingBox>(texto_final2);
	man_e.addTagToEntity<TNotRenderizable>(texto_final2);
	man_e.defineCMP<CPhysics>(texto_final2, CPhysics{.x =18, .y=0 ,.z= -42});
	man_e.defineCMP<CRenderGL>(texto_final2, CRenderGL{.modelMatrix = Model("assets/level1/cube.obj", glm::vec3(0,0,0))});

	auto& cartel_casa = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CInformation>();
	man_e.addTagToEntity<TCollisionable>(cartel_casa);
	man_e.addTagToEntity<TWall>(cartel_casa);
	man_e.addTagToEntity<TDescription>(cartel_casa);
	man_e.defineCMP<CPhysics>(cartel_casa, CPhysics{.x = 25, .y = 0 ,.z = -43.64});
	man_e.defineCMP<CRenderGL>(cartel_casa, CRenderGL{.modelMatrix = Model("assets/level1/Cartel_Der.obj", glm::vec3(0,0,0))});
	
	
	for (int j = 0;j<5;++j){
		auto& enemy = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound, CAnimation>();
		man_e.addTagToEntity<TEnemy>(enemy);
		man_e.addTagToEntity<TNotPatrol>(enemy);	
		man_e.addTagToEntity<TDummy>(enemy);
		man_e.addTagToEntity<TNotRenderizable>(enemy);
		man_e.addTagToEntity<TNotRenderAnim>(enemy);
		man_e.defineCMP<CIA>(enemy, CIA{.dt = &systems.dtree});
		man_e.defineCMP<CSound>(enemy, CSound{.s_mgr = &systems.soundito});
		man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
		man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(180,0,1,0);
		man_e.getEntityCMP<CAnimation>(enemy).animation = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix);
		man_e.getEntityCMP<CAnimation>(enemy).animator = Animator(&man_e.getEntityCMP<CAnimation>(enemy).animation);
		man_e.getEntityCMP<CIA>(enemy).origin = man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.nodeMatrix;
		auto& phy = man_e.getEntityCMP<CPhysics>(enemy);
		if (j==0){ phy.x = -7.62;  phy.y = 0;  phy.z = -11.47; } //enemy 1
		if (j==1){ phy.x =-11.94; phy.y = 0; phy.z = -31.90;}   //enemy 2
		if (j==2){ phy.x =-11.57; phy.y = 0; phy.z = -34.23;}   //enemy 3
		if (j==3){ phy.x = -0.51;  phy.y = 0;  phy.z = -45.67; } //enemy 4
		if (j==4){ phy.x = -0.63;  phy.y = 0;  phy.z = -38.99;} //enemy 5
	}

	auto& decoration = man_e.createEntity_withCMPS<CPhysics, CRenderGL>();
	man_e.defineCMP<CPhysics>(decoration, CPhysics{.x =0, .y = 0 ,.z = 0});
	man_e.defineCMP<CRenderGL>(decoration, CRenderGL{.modelMatrix = Model("assets/level1/deco1.obj", glm::vec3(0,0,0))});
	
	auto& colideco11 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(colideco11 );
	man_e.addTagToEntity<TCollisionable>(colideco11 );
	man_e.addTagToEntity<TWall>(colideco11 );
	man_e.defineCMP<CPhysics>(colideco11 , CPhysics{.x= -13.702020645141602 , .y = 0.5, .z = -36.53837966918945});
	man_e.defineCMP<CRenderGL>(colideco11 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	// DESCRIPTIONS
	man_e.defineCMP<CInformation>(light,CInformation{.description="My salvation" ,.descriptionPickable="[Q] Grab"});
	man_e.defineCMP<CInformation>(coche_txt, CInformation{.description = "I got a little bit more than a flat tire..."});
	man_e.defineCMP<CInformation>(church_door_text, CInformation{.description = "It's locked, needs something", .descriptionPickable="[E] Try to open"});
	man_e.defineCMP<CInformation>(quemable_iglesia_txt,CInformation{.description= "Maybe i can burn it", .descriptionPickable="[E] Burn"});
	man_e.defineCMP<CInformation>(key_church,CInformation{.description="This must be it" ,.descriptionPickable="[E] Grab"});
	man_e.defineCMP<CInformation>(yesquero,CInformation{.description="Refills fuel" ,.descriptionPickable="[E] Grab"});
	man_e.defineCMP<CInformation>(altar_izq_txt,CInformation{.type_of_text = 1 ,.text_list{"'You, LORD, keep my lamp burning;","my God turns my darkness into light. | Psalm 18:28'",""} });
	man_e.defineCMP<CInformation>(altar_drc_txt,CInformation{.description{"this stuff looks very old"} });
	man_e.defineCMP<CInformation>(tumba2_txt,CInformation{.type_of_text = 1 ,.text_list{"'Eleanor Elkins - The love of my life","1948 - 1986'",""} });
	man_e.defineCMP<CInformation>(tumba4_txt,CInformation{.type_of_text = 1 ,.text_list{"'Catherine Elkins - The light of our lives","1970 - 1986'",""} });
	man_e.defineCMP<CInformation>(tumba1_txt,CInformation{.type_of_text = 1 ,.text_list{"'Jacob Elkins","1940 - '",""} });
	man_e.defineCMP<CInformation>(tumba3_txt,CInformation{.type_of_text = 0 ,.description{"'Toby our beloved pet'"} });
	man_e.defineCMP<CInformation>(texto_1,CInformation{.type_of_text = 3 ,.description{"There's got to be someone arround here..."} });
	man_e.defineCMP<CInformation>(texto_2,CInformation{.type_of_text = 3 ,.description{"It's cold out here"}});
	man_e.defineCMP<CInformation>(cuervos_sonido,CInformation{.type_of_text = 3 ,.description{"Well, those look like tombs..."}, .times_to_print_text{150} });
	man_e.defineCMP<CInformation>(texto_cuadro,CInformation{.type_of_text = 1 ,.text_list{"'Lord have mercy'","An old painting signed by 'E.Elkins'",""} });
	man_e.defineCMP<CInformation>(texto_final1,CInformation{.type_of_text = 3 ,.description{"Okay, I can see a house"}, .times_to_print_text{120} });
	man_e.defineCMP<CInformation>(texto_final2,CInformation{.type_of_text = 3 ,.description{"Better be careful... just in case"}, .times_to_print_text{100} });
	man_e.defineCMP<CInformation>(cartel_casa,CInformation{.type_of_text  = 0 ,.description{"To the house"}});

	

	std::cout << "Entities level 1 : " << man_e.getEntityArray().size() <<"\n";
	//std::cout << "ID entity [0] :  " << man_e.getEntityArray()[0].getID() << "\n";
	//std::cout << "ARRAY DE ENTIDADES CON EL STATUS CAMBIADO DE LVL 1" << "\n";
	//for (long unsigned int i=0; i < man_e.getLevelsStatus().lvl_1_objects_status.size() ;++i){
	//	std::cout << "Status changed for id "<< man_e.getLevelsStatus().lvl_1_objects_status[i] << "\n";
	//}
	load_lv_1_lights(man_e, GL);
}

void Levels::load_lvl_2(Manentity_type& man_e, Sys& systems, EngineGL& GL){
	GL.camera.LanternIsHeld = true;
	//Descomentar para cuando tengamos que cambiar de lvl
	//	Todas las entidades tienen que tener fisicas para tener las posiciones y poder renderizar
	InitSoundsLvl_2(systems.soundito);

	man_e.getLevelsStatus().actual = 2;
	//--------------------------------PLAYER---------------------------------------------------//
		
	////////////// PLAYER -- Collision box
	//	CMPS :  CRenderGL, CPhysics, CInput, CCollision
	//	TAGS : 	TPlayer, TCollider, TNotRenderizable
	auto& player = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CInput, CCollision, CHealth, CStamina, CSound>();	
	man_e.addTagToEntity<TPlayer>(player);
	man_e.addTagToEntity<TCollider>(player);
	man_e.addTagToEntity<TNotRenderizable>(player); //HACER UN CUBE ACORDE AL PLAYER
	man_e.defineCMP<CPhysics>(player, CPhysics{.x=0, .y=1.5, .z=0});
	
	//man_e.defineCMP<CPhysics>(player, CPhysics{.x=50, .y=1.31, .z=-0.2});
	man_e.defineCMP<CRenderGL>(player, CRenderGL{.modelMatrix= Model("assets/level1/cube.obj", glm::vec3(0,1.5,-3))});
	man_e.defineCMP<CSound>(player, CSound{.s_mgr = &systems.soundito, .name{"surface"}, .eventvalue = 0,});
	man_e.getInventory().clear();
	//std::cout << man_e.getEntityCMP<CPhysics>(player).x << "  " << man_e.getEntityCMP<CPhysics>(player).z << "\n";

	////////////// PLAYER -- Model
	//	CMPS :  CRenderGL, CPhysics
	//	TAGS : 	TPlayer
	auto& player_model = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.addTagToEntity<TPlayer>(player_model);
	//man_e.defineCMP<CPhysics>(player_model, CPhysics{.x=4, .z= -4});
	man_e.defineCMP<CRenderGL>(player_model, CRenderGL{.modelMatrix= Model("assets/level1/brazo.obj", glm::vec3(0.7, -0.5, -2))}); 
	man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Scale(1.6,2,2);
	//man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Rotate(0, 0,1,0);
	////////////// PLAYER -- Model Candil with light
	//	CMPS :  CRenderGL, CPhysics, CPointLight
	//	TAGS : 	TPlayer

	auto& light = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CPointLight, CHealth, CSound, CCollision>(); //MIRAR BIEN
	man_e.addTagToEntity<TPlayer>(light);
	man_e.addTagToEntity<TLantern>(light);
	man_e.addTagToEntity<TCollisionable>(light);
	//man_e.addTagToEntity<Tpickable>(light);
	man_e.addTagToEntity<TScaleBoundingBox>(light);
	//man_e.addTagToEntity<TNotRenderizable>(light);
	man_e.defineCMP<CPhysics>(light,  CPhysics{.x=0.8, .y=0, .z=-1});
	man_e.defineCMP<CRenderGL>(light, CRenderGL{.modelMatrix = Model("assets/level1/Candil.obj", glm::vec3(0.8, -0.7, 0))});
	man_e.defineCMP<CSound>(light, CSound{.s_mgr= &systems.soundito}); 
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Scale(5,6,5);
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Rotate(90, 0,1,0);
	man_e.defineCMP<CPointLight>(light, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(light).setOnLamp();


	//--------------------------------ENEMY---------------------------------------------------//
	////////////// ENEMY -- Enemy 1 with IA 
	//	CMPS :  CRenderGL, CIA, CPhysics
	//	TAGS : 	TEnemy
	auto& enemy = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound, CAnimation>();
	man_e.addTagToEntity<TNotRenderizable>(enemy);
	man_e.addTagToEntity<TEnemy>(enemy);
	man_e.defineCMP<CPhysics>(enemy, CPhysics{.x = 30, .y = 0, .z = 10 , .vx = 0});
	man_e.defineCMP<CIA>(enemy, CIA{.dt = &systems.dtree, .targets{
		
		glm::vec3{55.00f,  1.f,  36.80f},
		glm::vec3{62.28f,  1.f,  23.66f},
		glm::vec3{50.86f,  1.f,  14.15f},
		glm::vec3{50.25f,  1.f, -13.65f},
		glm::vec3{33.97f,  1.f, -27.30f},
		glm::vec3{26.39f,  1.f, -27.60f},
		glm::vec3{26.39f,  1.f, -11.83f},
		glm::vec3{17.49f,  1.f, -11.83f},
		glm::vec3{13.24f,  1.f,   5.76f},
		glm::vec3{25.27 ,  1.f,   6.16f},
		glm::vec3{31.34f,  1.f,  15.97f},
		glm::vec3{31.85f,  1.f,  35.59f}
		}, .max_range{15}});
	man_e.defineCMP<CSound>(enemy, CSound{.s_mgr = &systems.soundito});
	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(180,0,1,0);
	man_e.getEntityCMP<CAnimation>(enemy).animation = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix);
	man_e.getEntityCMP<CAnimation>(enemy).animator = Animator(&man_e.getEntityCMP<CAnimation>(enemy).animation);
	man_e.getEntityCMP<CIA>(enemy).origin = man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.nodeMatrix;

	auto& escenario = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.defineCMP<CRenderGL>(escenario, CRenderGL{ .modelMatrix = Model("assets/level2/lvl2.obj", glm::vec3(0,0,0))});
	
	auto& iglesia = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.defineCMP<CRenderGL>(iglesia, CRenderGL{.modelMatrix = Model("assets/level2/iglesia.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CPhysics>(iglesia, CPhysics{.x = -18, .y = 0.66, .z = -5});

	auto& granero = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.defineCMP<CRenderGL>(granero, CRenderGL{.modelMatrix = Model("assets/level2/granero_solo.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CPhysics>(granero, CPhysics{.x = 130, .y = 0.66, .z = -35.32});
	man_e.getEntityCMP<CRenderGL>(granero).modelMatrix.Rotate(90, 0, 1, 0);

	//---------------------------DEFINICION DE LOS MODELOS EN LVL2--------------------------------//

	auto& balancin  = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(balancin);
	man_e.addTagToEntity<TWall>(balancin);
	man_e.defineCMP<CRenderGL>(balancin, CRenderGL{ .modelMatrix = Model("assets/level2/Balancin.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(balancin, CPhysics{.x = 25.53, .y = 0.66, .z = 19.23});

	auto& columpio  = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(columpio);
	man_e.addTagToEntity<TWall>(columpio);
	man_e.addTagToEntity<TDescription>(columpio);
	//man_e.addTagToEntity<TScaleBoundingBox>(columpio);
	man_e.defineCMP<CRenderGL>(columpio, CRenderGL{ .modelMatrix = Model("assets/level2/Columpios.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(columpio, CPhysics{.x = 16.13, .y = 1.65, .z = 20.82});
//Colisiones por pensar
	auto& arenero 	= man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(arenero);
	man_e.addTagToEntity<TWall>(arenero);
	man_e.addTagToEntity<TDescription>(arenero);
	//man_e.addTagToEntity<TScaleBoundingBox>(arenero);
	man_e.defineCMP<CRenderGL>(arenero, CRenderGL{ .modelMatrix = Model("assets/level2/Arenero.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(arenero, CPhysics{.x = 19.43, .y = 0.25, .z = 14.11});
	
	auto& pozo 		= man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics>();
	man_e.addTagToEntity<TDescription>(pozo);
	//man_e.addTagToEntity<TScaleBoundingBox>(pozo);
	man_e.defineCMP<CRenderGL>(pozo, CRenderGL{ .modelMatrix = Model("assets/level2/Pozonew.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(pozo, CPhysics{.x = 36.80, .y = 0, .z = 22.88});
	man_e.getEntityCMP<CRenderGL>(pozo).modelMatrix.Scale(0.6, 0.8, 0.6);
	
	auto& pozo_coli = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(pozo_coli);
	man_e.addTagToEntity<TWall>(pozo_coli);
	man_e.addTagToEntity<TNotRenderizable>(pozo_coli);
	man_e.defineCMP<CRenderGL>(pozo_coli, CRenderGL{ .modelMatrix = Model("assets/level2/Pozo_Coli.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(pozo_coli, CPhysics{.x = 36.80, .y = 0.85, .z = 22.88});

	//auto& caja1 = man_e.createEntity_withCMPS<CRenderGL, CPhysics>(); 
	//man_e.defineCMP<CRenderGL>(caja1, CRenderGL{ .modelMatrix = Model("assets/level1/cube.obj", glm::vec3(0,0,0))});
	//man_e.defineCMP<CPhysics>(caja1, CPhysics{.x = 35, .y = 0.66, .z = 9.63});

	auto& granjero =  man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.defineCMP<CRenderGL>(granjero, CRenderGL{ .modelMatrix = Model("assets/level2/persona.obj", glm::vec3(0, 0 , 0))});
	man_e.defineCMP<CPhysics>(granjero,CPhysics{.x = 35.70, .y = 0.02, .z = 5.55});
	man_e.getEntityCMP<CRenderGL>(granjero).modelMatrix.Rotate(180, 0, 1, 0); 

	auto& caperro 	= man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(caperro);
	man_e.addTagToEntity<TWall>(caperro);
	man_e.addTagToEntity<TDescription>(caperro);
	man_e.defineCMP<CRenderGL>(caperro, CRenderGL{ .modelMatrix = Model("assets/level2/Casita_Perro.obj", glm::vec3(0, 0 , 0))});
	man_e.defineCMP<CPhysics>(caperro, CPhysics{.x = 31.55, .y = 0.02, .z = -6.02});

	// PUERTA DE LAS VALLAS

	auto& pvalla 	= man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(pvalla);
	man_e.addTagToEntity<TWall>(pvalla);
	man_e.defineCMP<CRenderGL>(pvalla, CRenderGL{ .modelMatrix = Model("assets/level2/PValla1.obj", glm::vec3(0 , 0 , 0))});
	man_e.defineCMP<CPhysics>(pvalla, CPhysics{.x = 58.99, .y = 1.24, .z = -21.82});
	auto& pvalla2 	= man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(pvalla2);
	man_e.addTagToEntity<TWall>(pvalla2);
	man_e.defineCMP<CRenderGL>(pvalla2, CRenderGL{ .modelMatrix = Model("assets/level2/PValla2.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(pvalla2, CPhysics{.x = 58.97, .y = 0, .z = -26.76});
	auto& pvalla3 	= man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(pvalla3);
	man_e.addTagToEntity<TWall>(pvalla3);
	man_e.defineCMP<CRenderGL>(pvalla3, CRenderGL{ .modelMatrix = Model("assets/level2/PValla3.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(pvalla3, CPhysics{.x = 58.88, .y = 1.25, .z = -31.72});

	//CULTIVOS

	auto& cultivo 	= man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics>();
	man_e.defineCMP<CRenderGL>(cultivo, CRenderGL{ .modelMatrix = Model("assets/level2/Campo.obj", glm::vec3(0, 0 , 0))});
	man_e.defineCMP<CPhysics>(cultivo, CPhysics{.x = 13.56, .y = 0, .z = -23.0});

	auto& cultivo2 	= man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics>();
	man_e.defineCMP<CRenderGL>(cultivo2, CRenderGL{ .modelMatrix = Model("assets/level2/Campo.obj", glm::vec3(0, 0 , 0))});
	man_e.defineCMP<CPhysics>(cultivo2, CPhysics{.x = 25.39, .y = 0, .z = -23.0});

	//VALLAS

	////////////////INSTANCIA VALLA PALOS VERTICALES
	//	CMPS:  CRenderGL, CPhysics
	//  TAGS: TInstance, TNotRenderizable
	auto& valla_pico = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(valla_pico);
	man_e.addTagToEntity<TNotRenderizable>(valla_pico);
	man_e.defineCMP<CRenderGL>(valla_pico, CRenderGL{.modelMatrix= Model("assets/level1/Valla_pico.obj", glm::vec3(0,0,0)),.amount=0, .instancePath="assets/level2/Instancia_Valla_pico22.txt"});
	
	//OBJETOS INSTANCIAS
	////////////////INSTANCIA VALLA MADERAS HORIZONTALES
	//	CMPS:  CRenderGL, CPhysics
	//  TAGS: TInstance, TNotRenderizable
	auto& valla_tablones = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(valla_tablones);
	man_e.addTagToEntity<TNotRenderizable>(valla_tablones);
	man_e.defineCMP<CRenderGL>(valla_tablones, CRenderGL{.modelMatrix= Model("assets/level1/Valla_tablones.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/level2/Instancia_Valla_tablon22.txt"});

	auto& maiz = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(maiz);
	man_e.addTagToEntity<TNotRenderizable>(maiz);
	man_e.defineCMP<CRenderGL>(maiz, CRenderGL{.modelMatrix= Model("assets/level1/CornLP.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/level2/Instancia_corn222.txt", .iscorn=true});
	//añadir segundo script de instancias a la hora de volver al nivel 2 si tenemos la rueda en el inventario IMPORTANTE
	//auto& maiz = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	//man_e.addTagToEntity<TInstance>(maiz);
	//man_e.addTagToEntity<TNotRenderizable>(maiz);
	//man_e.defineCMP<CRenderGL>(maiz, CRenderGL{.modelMatrix= Model("assets/level1/CornLP.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/level2/instances_maiz2persecucion.txt", .iscorn=true});
		
	//POSTE DE DIRECCION

	auto& poste 	= man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics>();
	man_e.defineCMP<CRenderGL>(poste, CRenderGL{ .modelMatrix = Model("assets/level2/Direccion_Poste.obj", glm::vec3(0, 0 , 0))});
	man_e.defineCMP<CPhysics>(poste, CPhysics{.x = 15.08, .y = 1.94, .z = -1.76});

	// CASA

	auto& casa 		= man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics>();
	man_e.defineCMP<CRenderGL>(  casa, CRenderGL{ .modelMatrix = Model("assets/level2/casa.obj", glm::vec3(0, 0 , 0))});
	man_e.defineCMP<CPhysics>(   casa, CPhysics{.x = 36.45, .y = -0.07, .z = 1.14});

	auto& col_casa = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(col_casa );
	man_e.addTagToEntity<TCollisionable>(col_casa );
	man_e.addTagToEntity<TWall>(col_casa );
	man_e.defineCMP<CPhysics>(col_casa , CPhysics{.x= 36.49 , .y = 1.64, .z = -2.77 });
	man_e.defineCMP<CRenderGL>(col_casa , CRenderGL{.modelMatrix = Model("assets/level2/Casa_Coli1.obj", glm::vec3(0,0,0))});
	auto& col_casa2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(col_casa2 );
	man_e.addTagToEntity<TCollisionable>(col_casa2 );
	man_e.addTagToEntity<TWall>(col_casa2 );
	man_e.defineCMP<CPhysics>(col_casa2 , CPhysics{.x= 42.74 , .y = 1.64, .z = 2.25 });
	man_e.defineCMP<CRenderGL>(col_casa2 , CRenderGL{.modelMatrix = Model("assets/level2/Casa_Coli2.obj", glm::vec3(0,0,0))});
	auto& col_casa3 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(col_casa3 );
	man_e.addTagToEntity<TCollisionable>(col_casa3 );
	man_e.addTagToEntity<TWall>(col_casa3 );
	man_e.defineCMP<CPhysics>(col_casa3 , CPhysics{.x= 35.88 , .y = 1.64, .z = 5.43 });
	man_e.defineCMP<CRenderGL>(col_casa3 , CRenderGL{.modelMatrix = Model("assets/level2/Casa_Coli3.obj", glm::vec3(0,0,0))});
	auto& col_casa4 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(col_casa4 );
	man_e.addTagToEntity<TCollisionable>(col_casa4 );
	man_e.addTagToEntity<TWall>(col_casa4 );
	man_e.defineCMP<CPhysics>(col_casa4 , CPhysics{.x= 35.43 , .y = 1.64, .z = -1.11 });
	man_e.defineCMP<CRenderGL>(col_casa4 , CRenderGL{.modelMatrix = Model("assets/level2/Casa_Coli4.obj", glm::vec3(0,0,0))});

	//COLISIONES DE LAS VALLAS
	auto& coll_valla_0 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_0 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_0 );
	man_e.addTagToEntity<TWall>(coll_valla_0 );
	man_e.defineCMP<CPhysics>(coll_valla_0 , CPhysics{.x= -1.07 , .y = 0.9, .z = 1.90 });
	man_e.defineCMP<CRenderGL>(coll_valla_0 , CRenderGL{.modelMatrix = Model("assets/level2/Valla2_Coli.obj", glm::vec3(0,0,0))});
	auto& coll_valla_1 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_1 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_1 );
	man_e.addTagToEntity<TWall>(coll_valla_1 );
	man_e.defineCMP<CPhysics>(coll_valla_1 , CPhysics{.x= -1.07 , .y = 0.9, .z = -2.30 });
	man_e.defineCMP<CRenderGL>(coll_valla_1 , CRenderGL{.modelMatrix = Model("assets/level2/Valla2_Coli.001.obj", glm::vec3(0,0,0))});
	auto& coll_valla_2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_2 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_2 );
	man_e.addTagToEntity<TWall>(coll_valla_2 );
	man_e.defineCMP<CPhysics>(coll_valla_2 , CPhysics{.x= 9.03 , .y = 0.9, .z = -17.38 });
	man_e.defineCMP<CRenderGL>(coll_valla_2 , CRenderGL{.modelMatrix = Model("assets/level2/Valla2_Coli.002.obj", glm::vec3(0,0,0))});
	auto& coll_valla_3 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_3 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_3 );
	man_e.addTagToEntity<TWall>(coll_valla_3 );
	man_e.defineCMP<CPhysics>(coll_valla_3 , CPhysics{.x= 9.03 , .y = 0.9, .z = 14.38 });
	man_e.defineCMP<CRenderGL>(coll_valla_3 , CRenderGL{.modelMatrix = Model("assets/level2/Valla2_Coli.003.obj", glm::vec3(0,0,0))});
	auto& coll_valla_5 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_5 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_5 );
	man_e.addTagToEntity<TWall>(coll_valla_5 );
	man_e.defineCMP<CPhysics>(coll_valla_5 , CPhysics{.x= 42.81 , .y = 0.9, .z = 40.58 });
	man_e.defineCMP<CRenderGL>(coll_valla_5 , CRenderGL{.modelMatrix = Model("assets/level2/Valla2_Coli.005.obj", glm::vec3(0,0,0))});
	auto& coll_valla_6 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_6 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_6 );
	man_e.addTagToEntity<TWall>(coll_valla_6 );
	man_e.defineCMP<CPhysics>(coll_valla_6 , CPhysics{.x= 52.86 , .y = 0.9, .z = -5.3 });
	man_e.defineCMP<CRenderGL>(coll_valla_6 , CRenderGL{.modelMatrix = Model("assets/level2/Valla2_Coli.006.obj", glm::vec3(0,0,0))});
	auto& coll_valla_7 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_7 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_7 );
	man_e.addTagToEntity<TWall>(coll_valla_7 );
	man_e.defineCMP<CPhysics>(coll_valla_7 , CPhysics{.x= 66.57 , .y = 0.9, .z = 25.15 });
	man_e.defineCMP<CRenderGL>(coll_valla_7 , CRenderGL{.modelMatrix = Model("assets/level2/Valla2_Coli.007.obj", glm::vec3(0,0,0))});
	auto& coll_valla_7_1 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_7_1 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_7_1);
	man_e.addTagToEntity<TWall>(coll_valla_7_1 );
	man_e.defineCMP<CPhysics>(coll_valla_7_1 , CPhysics{.x= 66.57 , .y = 0.9, .z = 45.15 });
	man_e.defineCMP<CRenderGL>(coll_valla_7_1 , CRenderGL{.modelMatrix = Model("assets/level2/Valla2_Coli.007.obj", glm::vec3(0,0,0))});
	auto& coll_valla_7_2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_7_2 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_7_2 );
	man_e.addTagToEntity<TWall>(coll_valla_7_2 );
	man_e.defineCMP<CPhysics>(coll_valla_7_2 , CPhysics{.x= 56 , .y = 0.9, .z = 55.22 });
	man_e.defineCMP<CRenderGL>(coll_valla_7_2 , CRenderGL{.modelMatrix = Model("assets/level2/Valla2_Coli.007.obj", glm::vec3(0,0,0))});
	auto& coll_valla_8 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_8 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_8 );
	man_e.addTagToEntity<TWall>(coll_valla_8 );
	man_e.defineCMP<CPhysics>(coll_valla_8 , CPhysics{.x= 49.07 , .y = 0.9, .z = -32.06 });
	man_e.defineCMP<CRenderGL>(coll_valla_8 , CRenderGL{.modelMatrix = Model("assets/level2/Valla2_Coli.008.obj", glm::vec3(0,0,0))});
	auto& coll_valla_9 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_9 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_9 );
	man_e.addTagToEntity<TWall>(coll_valla_9 );
	man_e.defineCMP<CPhysics>(coll_valla_9 , CPhysics{.x= 72.73 , .y = 0.9, .z = -21.51 });
	man_e.defineCMP<CRenderGL>(coll_valla_9 , CRenderGL{.modelMatrix = Model("assets/level2/Valla2_Coli.009.obj", glm::vec3(0,0,0))});
	auto& coll_valla_10 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(coll_valla_10 );
	man_e.addTagToEntity<TCollisionable>(coll_valla_10 );
	man_e.addTagToEntity<TWall>(coll_valla_10 );
	man_e.defineCMP<CPhysics>(coll_valla_10 , CPhysics{.x= 59.87 , .y = 0.9, .z = 10.88 });
	man_e.defineCMP<CRenderGL>(coll_valla_10 , CRenderGL{.modelMatrix = Model("assets/level2/Valla2_Coli.010.obj", glm::vec3(0,0,0))});

	auto& yesquero = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CPng>();
	man_e.addTagToEntity<TCollisionable>(yesquero);
	man_e.addTagToEntity<TScaleBoundingBox>(yesquero);
	man_e.addTagToEntity<Tpickable>(yesquero);
	man_e.addTagToEntity<TYesquero>(yesquero);
	man_e.addTagToEntity<TDescription>(yesquero);
	man_e.defineCMP<CPhysics>(yesquero, CPhysics{.x =34.37, .y=0 ,.z= 24.03});
	man_e.getEntityCMP<CRenderGL>(yesquero).modelMatrix.Rotate(90,0,0,1);
	man_e.defineCMP<CRenderGL>(yesquero, CRenderGL{.modelMatrix = Model("assets/level1/aceite.obj", glm::vec3(0,0,0))});
	
	auto& yesquero2 = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(yesquero2);
	man_e.addTagToEntity<TScaleBoundingBox>(yesquero2);
	man_e.addTagToEntity<Tpickable>(yesquero2);
	man_e.addTagToEntity<TYesquero>(yesquero2);
	man_e.addTagToEntity<TDescription>(yesquero2);
	man_e.defineCMP<CPhysics>(yesquero2, CPhysics{.x =50.61, .y=0 ,.z= -0.6});
	man_e.getEntityCMP<CRenderGL>(yesquero2).modelMatrix.Rotate(90,0,0,1);
	man_e.defineCMP<CRenderGL>(yesquero2, CRenderGL{.modelMatrix = Model("assets/level1/aceite.obj", glm::vec3(0,0,0))});

	auto& puerta_trasera = man_e.createEntity_withCMPS<CCollision, CPhysics, CRenderGL, CInformation, CIDLvl>();
	man_e.addTagToEntity<TNotRenderizable>(puerta_trasera);
	man_e.addTagToEntity<TCollisionable>(puerta_trasera);
	man_e.addTagToEntity<TDescription>(puerta_trasera);
	man_e.addTagToEntity<TScaleBoundingBox>(puerta_trasera);
	man_e.addTagToEntity<TBackDoor>(puerta_trasera);
	man_e.defineCMP<CPhysics>(puerta_trasera, CPhysics{.x =49, .y=0 ,.z= 5});
	man_e.defineCMP<CRenderGL>(puerta_trasera, CRenderGL{.modelMatrix = Model("assets/level1/cube.obj", glm::vec3(0,0,0))});

	//NO SEPARAR//
	auto& housedoor = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CInformation, CIDLvl, CSound>();
	man_e.addTagToEntity<TCollisionable>(housedoor);
	man_e.addTagToEntity<TDescription>(housedoor);
	man_e.addTagToEntity<TNotRenderizable>(housedoor);
	man_e.addTagToEntity<TScaleBoundingBox>(housedoor);
	man_e.addTagToEntity<TDoor>(housedoor);
    man_e.defineCMP<CSound>(housedoor, CSound{.s_mgr = &systems.soundito});
	man_e.defineCMP<CPhysics>(housedoor, CPhysics{.x = 36.45,.y=0.5, .z = 1.14});
	man_e.defineCMP<CRenderGL>(housedoor, CRenderGL{.modelMatrix = Model("assets/level1/cube.obj", glm::vec3(0,0,0))});
	auto& figura = man_e.createEntity_withCMPS<CPhysics, CInformation, CRenderGL, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(figura);
	man_e.addTagToEntity<TWindowMailBox>(figura);
	man_e.addTagToEntity<TScaleBoundingBox>(figura);
	man_e.defineCMP<CPhysics>(figura, CPhysics{.x = 33.45,.y=0.5, .z = 5.14});
	man_e.defineCMP<CRenderGL>(figura, CRenderGL{.modelMatrix = Model("assets/level1/cube.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CInformation>(figura, CInformation{.type_of_text = 3});
	auto& mailbox = man_e.createEntity_withCMPS<CPhysics, CInformation, CRenderGL, CCollision>();
	man_e.addTagToEntity<TScaleBoundingBox>(mailbox);
	man_e.defineCMP<CPhysics>(mailbox, CPhysics{.x = 33.79,.y=0.0, .z = -1.020});
	man_e.defineCMP<CRenderGL>(mailbox, CRenderGL{.modelMatrix = Model("assets/level2/buzon.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CInformation>(mailbox, CInformation{.type_of_text = 3});
	auto& mailbox_wall = man_e.createEntity_withCMPS<CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TWall>(mailbox_wall);
	man_e.addTagToEntity<TCollisionable>(mailbox_wall);
	man_e.addTagToEntity<TNotRenderizable>(mailbox_wall);
	man_e.defineCMP<CPhysics>(mailbox_wall, CPhysics{.x = 33.79,.y=0.0, .z = -1.020});
	man_e.defineCMP<CRenderGL>(mailbox_wall, CRenderGL{.modelMatrix = Model("assets/level2/buzon.obj", glm::vec3(0,0,0))});
	auto& house_key = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CSound, CPng>();
	man_e.addTagToEntity<TNotRenderizable>(house_key);
	man_e.addTagToEntity<Tpickable>(house_key);
	man_e.addTagToEntity<TCollisionable>(house_key);
	man_e.addTagToEntity<TScaleBoundingBox>(house_key);
	man_e.defineCMP<CPhysics>(house_key, CPhysics{.x = 33.79,.y=1, .z = -1.020});
	man_e.defineCMP<CRenderGL>(house_key, CRenderGL{.modelMatrix = Model("assets/level1/llave.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CPng>(house_key, CPng{.icono = Model("assets/level1/icono_llave.obj", glm::vec3(-0.70,0.42,0))});
	man_e.defineCMP<CSound>(house_key, CSound{.s_mgr = &systems.soundito});
	man_e.getEntityCMP<CPng>(house_key).icono.Rotate(90,0,1,1);
	man_e.getEntityCMP<CRenderGL>(house_key).modelMatrix.Rotate(90,0,0,1);
	man_e.getEntityCMP<CPng>(house_key).icono.Scale(0.15,0.2,0.2);
	auto& mailbox_rotate = man_e.createEntity_withCMPS<CPhysics, CRenderGL>();
	man_e.defineCMP<CPhysics>(mailbox_rotate, CPhysics{.x = 33.79,.y=0.9495, .z = -0.75});
	man_e.defineCMP<CRenderGL>(mailbox_rotate, CRenderGL{.modelMatrix = Model("assets/level2/buzon_boca.obj", glm::vec3(0,0,0))});
	//NO SEPARAR//
	//Transition entity

	auto& transitionlvl2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CIDLvl>();
	man_e.addTagToEntity<TNotRenderizable>(transitionlvl2 );
	man_e.addTagToEntity<TCollisionable>(transitionlvl2);
	//man_e.addTagToEntity<TWall>(transitionlvl2 );
	man_e.addTagToEntity<TTransition>(transitionlvl2);
	man_e.defineCMP<CPhysics>(transitionlvl2, CPhysics{.x=-6.5, .y=1.31, .z=-0.2});
	man_e.defineCMP<CRenderGL>(transitionlvl2 , CRenderGL{.modelMatrix = Model("assets/level1/Transition_Colision.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CIDLvl>(transitionlvl2, CIDLvl{.lvlid = 1});

	auto& transitionlvl2_to_maze = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CIDLvl>();
	man_e.addTagToEntity<TNotRenderizable>(transitionlvl2_to_maze );
	man_e.addTagToEntity<TCollisionable>(transitionlvl2_to_maze);
	man_e.addTagToEntity<TTransition>(transitionlvl2_to_maze);
	man_e.defineCMP<CPhysics>(transitionlvl2_to_maze, CPhysics{.x=64, .y=1.31, .z=58});
	man_e.defineCMP<CRenderGL>(transitionlvl2_to_maze , CRenderGL{.modelMatrix = Model("assets/level2/transition.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CIDLvl>(transitionlvl2_to_maze, CIDLvl{.lvlid = 7});

	auto& tp_lvl_Y = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CIDLvl>();
	man_e.addTagToEntity<TCollisionable>(tp_lvl_Y);
	man_e.addTagToEntity<TNotRenderizable>(tp_lvl_Y);
	man_e.addTagToEntity<TTransitionY>(tp_lvl_Y);
	man_e.addTagToEntity<TDescription>(tp_lvl_Y);
	man_e.defineCMP<CRenderGL>(tp_lvl_Y, CRenderGL{ .modelMatrix = Model("assets/level1/caja2.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(tp_lvl_Y, CPhysics{.x = 58.88, .y = 1.25, .z = -26.72});
	man_e.defineCMP<CIDLvl>(tp_lvl_Y, CIDLvl{.lvlid = 6});

	GL.camera.Position = { 0, 1.5, 0 };

	auto& cartel_granero = man_e.createEntity_withCMPS< CRenderGL, CPhysics, CCollision, CInformation>();
	man_e.addTagToEntity<TCollisionable>(cartel_granero);
	man_e.addTagToEntity<TWall>(cartel_granero);
	man_e.addTagToEntity<TDescription>(cartel_granero);
	man_e.defineCMP<CRenderGL>(cartel_granero, CRenderGL{ .modelMatrix = Model("assets/level1/Cartel_Izq.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(cartel_granero, CPhysics{.x = 54.16, .y = 0, .z = -22});
	man_e.getEntityCMP<CRenderGL>(cartel_granero).modelMatrix.Rotate(-90, 0, 1, 0);

	auto& cartel_tumba = man_e.createEntity_withCMPS< CRenderGL, CPhysics, CCollision, CInformation>();
	man_e.addTagToEntity<TCollisionable>(cartel_tumba);
	man_e.addTagToEntity<TWall>(cartel_tumba);
	man_e.addTagToEntity<TDescription>(cartel_tumba);
	man_e.defineCMP<CRenderGL>(cartel_tumba, CRenderGL{ .modelMatrix = Model("assets/level1/Cartel_Der.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(cartel_tumba, CPhysics{.x = 64.81, .y = 0, .z = 39.55});
	man_e.getEntityCMP<CRenderGL>(cartel_tumba).modelMatrix.Rotate(270, 0, 1, 0);
//no va la descirpiton
	auto& cartel_iglesia = man_e.createEntity_withCMPS< CRenderGL, CPhysics, CCollision, CInformation>();
	man_e.addTagToEntity<TCollisionable>(cartel_iglesia);
	man_e.addTagToEntity<TWall>(cartel_iglesia);
	man_e.addTagToEntity<TDescription>(cartel_iglesia);
	man_e.defineCMP<CRenderGL>(cartel_iglesia, CRenderGL{ .modelMatrix = Model("assets/level1/Cartel_Izq.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(cartel_iglesia, CPhysics{.x = 1.30, .y = 0, .z = -1.8});
	
	auto& enemy2 = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound, CAnimation>();
	man_e.addTagToEntity<TDummy>(enemy2);
	man_e.addTagToEntity<TNotRenderizable>(enemy2);
	man_e.addTagToEntity<TEnemy>(enemy2);
	man_e.addTagToEntity<TNotRenderAnim>(enemy2);
	man_e.defineCMP<CPhysics>(enemy2, CPhysics{.x = 30, .y = 0, .z = -10 , .vx = 0});
	man_e.defineCMP<CIA>(enemy2, CIA{.dt = &systems.dtree});
	man_e.defineCMP<CSound>(enemy2, CSound{.s_mgr = &systems.soundito});
	man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
	man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix.Rotate(180,0,1,0);
	man_e.getEntityCMP<CAnimation>(enemy2).animation = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix);
	man_e.getEntityCMP<CAnimation>(enemy2).animator = Animator(&man_e.getEntityCMP<CAnimation>(enemy2).animation);
	man_e.getEntityCMP<CIA>(enemy2).origin = man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix.nodeMatrix;

	auto& enemy3 = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound, CAnimation>();
	man_e.addTagToEntity<TDummy>(enemy3);
	man_e.addTagToEntity<TNotRenderizable>(enemy3);
	man_e.addTagToEntity<TEnemy>(enemy3);
	man_e.addTagToEntity<TNotRenderAnim>(enemy3);
	man_e.defineCMP<CPhysics>(enemy3, CPhysics{.x = 20, .y = 0, .z = 15 , .vx = 0});
	man_e.defineCMP<CIA>(enemy3, CIA{.dt = &systems.dtree});
	man_e.defineCMP<CSound>(enemy3, CSound{.s_mgr = &systems.soundito});
	man_e.getEntityCMP<CRenderGL>(enemy3).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
	man_e.getEntityCMP<CRenderGL>(enemy3).modelMatrix.Rotate(180,0,1,0);
	man_e.getEntityCMP<CAnimation>(enemy3).animation = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy3).modelMatrix);
	man_e.getEntityCMP<CAnimation>(enemy3).animator = Animator(&man_e.getEntityCMP<CAnimation>(enemy3).animation);
	man_e.getEntityCMP<CIA>(enemy3).origin = man_e.getEntityCMP<CRenderGL>(enemy3).modelMatrix.nodeMatrix;

	auto& enemy4 = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound, CAnimation>();
	man_e.addTagToEntity<TDummy>(enemy4);
	man_e.addTagToEntity<TNotRenderizable>(enemy4);
	man_e.addTagToEntity<TEnemy>(enemy4);
	man_e.addTagToEntity<TNotRenderAnim>(enemy4);
	man_e.defineCMP<CPhysics>(enemy4, CPhysics{.x = 40, .y = 0, .z = 7 , .vx = 0});
	man_e.defineCMP<CIA>(enemy4, CIA{.dt = &systems.dtree});
	man_e.defineCMP<CSound>(enemy4, CSound{.s_mgr = &systems.soundito});
	man_e.getEntityCMP<CRenderGL>(enemy4).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
	man_e.getEntityCMP<CRenderGL>(enemy4).modelMatrix.Rotate(180,0,1,0);
	man_e.getEntityCMP<CAnimation>(enemy4).animation = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy4).modelMatrix);
	man_e.getEntityCMP<CAnimation>(enemy4).animator = Animator(&man_e.getEntityCMP<CAnimation>(enemy4).animation);
	man_e.getEntityCMP<CIA>(enemy4).origin = man_e.getEntityCMP<CRenderGL>(enemy4).modelMatrix.nodeMatrix;

	auto& yesquero3 = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(yesquero3);
	man_e.addTagToEntity<TScaleBoundingBox>(yesquero3);
	man_e.addTagToEntity<TYesqueroPermanente>(yesquero3);
	man_e.addTagToEntity<Tpickable>(yesquero3);
	man_e.addTagToEntity<TYesquero>(yesquero3);
	man_e.addTagToEntity<TDescription>(yesquero3);
	man_e.defineCMP<CPhysics>(yesquero3, CPhysics{.x =18.91, .y=0 ,.z= -18.65});
	man_e.getEntityCMP<CRenderGL>(yesquero3).modelMatrix.Rotate(90,0,0,1);
	man_e.defineCMP<CRenderGL>(yesquero3, CRenderGL{.modelMatrix = Model("assets/level1/aceite.obj", glm::vec3(0,0,0))});

	auto& decoracion = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();
	man_e.defineCMP<CPhysics>(decoracion, CPhysics{.x =0, .y=-0.02 ,.z=-0.75});
	man_e.defineCMP<CRenderGL>(decoracion, CRenderGL{.modelMatrix = Model("assets/level2/DecoLvl2.obj", glm::vec3(0,0,0))});
	auto& Colideco1_001 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Colideco1_001 );
	man_e.addTagToEntity<TCollisionable>(Colideco1_001 );
	man_e.addTagToEntity<TWall>(Colideco1_001 );
	man_e.defineCMP<CPhysics>(Colideco1_001 , CPhysics{.x= 63.46554946899414 , .y = 0.3412599563598633, .z = 14.586127281188965});
	man_e.defineCMP<CRenderGL>(Colideco1_001 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& Colideco1_002 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Colideco1_002 );
	man_e.addTagToEntity<TCollisionable>(Colideco1_002 );
	man_e.addTagToEntity<TWall>(Colideco1_002 );
	man_e.defineCMP<CPhysics>(Colideco1_002 , CPhysics{.x= 60.75733947753906 , .y = 0.3412599563598633, .z = 17.70261001586914});
	man_e.defineCMP<CRenderGL>(Colideco1_002 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& Colideco1_003 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Colideco1_003 );
	man_e.addTagToEntity<TCollisionable>(Colideco1_003 );
	man_e.addTagToEntity<TWall>(Colideco1_003 );
	man_e.defineCMP<CPhysics>(Colideco1_003 , CPhysics{.x= 60.19936752319336 , .y = 0.3412599563598633, .z = 18.614421844482422});
	man_e.defineCMP<CRenderGL>(Colideco1_003 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& Colideco1_004 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Colideco1_004 );
	man_e.addTagToEntity<TCollisionable>(Colideco1_004 );
	man_e.addTagToEntity<TWall>(Colideco1_004 );
	man_e.defineCMP<CPhysics>(Colideco1_004 , CPhysics{.x= 61.2880973815918 , .y = 0.3412599563598633, .z = 19.281265258789062});
	man_e.defineCMP<CRenderGL>(Colideco1_004 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& Colideco1 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Colideco1 );
	man_e.addTagToEntity<TCollisionable>(Colideco1 );
	man_e.addTagToEntity<TWall>(Colideco1 );
	man_e.defineCMP<CPhysics>(Colideco1 , CPhysics{.x= 61.2880973815918 , .y = 0.3412599563598633, .z = 18.48883056640625});
	man_e.defineCMP<CRenderGL>(Colideco1 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& Colideco1_005 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Colideco1_005 );
	man_e.addTagToEntity<TCollisionable>(Colideco1_005 );
	man_e.addTagToEntity<TWall>(Colideco1_005 );
	man_e.defineCMP<CPhysics>(Colideco1_005 , CPhysics{.x= 40.929176330566406 , .y = 0.3412599563598633, .z = 17.664592742919922});
	man_e.defineCMP<CRenderGL>(Colideco1_005 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& Colideco1_006 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Colideco1_006 );
	man_e.addTagToEntity<TCollisionable>(Colideco1_006 );
	man_e.addTagToEntity<TWall>(Colideco1_006 );
	man_e.defineCMP<CPhysics>(Colideco1_006 , CPhysics{.x= 41.027828216552734 , .y = 0.3412599563598633, .z = 34.20791244506836});
	man_e.defineCMP<CRenderGL>(Colideco1_006 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& Colideco1_007 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Colideco1_007 );
	man_e.addTagToEntity<TCollisionable>(Colideco1_007 );
	man_e.addTagToEntity<TWall>(Colideco1_007 );
	man_e.defineCMP<CPhysics>(Colideco1_007 , CPhysics{.x= 12.468941688537598 , .y = 0.2835584282875061, .z = -7.390594482421875});
	man_e.defineCMP<CRenderGL>(Colideco1_007 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& Colideco1_008 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Colideco1_008 );
	man_e.addTagToEntity<TCollisionable>(Colideco1_008 );
	man_e.addTagToEntity<TWall>(Colideco1_008 );
	man_e.defineCMP<CPhysics>(Colideco1_008 , CPhysics{.x= 44.6636962890625 , .y = 0.43684759736061096, .z = -14.88556957244873});
	man_e.defineCMP<CRenderGL>(Colideco1_008 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& molino = man_e.createEntity_withCMPS<CRenderGL,CPhysics>();
	man_e.defineCMP<CPhysics>(molino , CPhysics{.x = 41.59,.y=0.0, .z = 13});
	man_e.defineCMP<CRenderGL>(molino , CRenderGL{.modelMatrix = Model("assets/level2/molino.obj", glm::vec3(0,0,0))});
	man_e.getEntityCMP<CRenderGL>(molino).modelMatrix.Rotate(180,0,1,0);
	man_e.getEntityCMP<CRenderGL>(molino).modelMatrix.Scale(0.6,0.6,0.6);

// 	-----------------------------------------------------------------------------
	//descripciones jugabilidad
	man_e.defineCMP<CInformation>(light,CInformation{.description="My salvation" ,.descriptionPickable="[Q] Grab"});
	man_e.defineCMP<CInformation>(yesquero, CInformation{.description="Refills fuel" ,.descriptionPickable="[E] Grab"});
	man_e.defineCMP<CInformation>(yesquero2,CInformation{.description="Refills fuel" ,.descriptionPickable="[E] Grab"});
	man_e.defineCMP<CInformation>(yesquero3,CInformation{.description="Refills fuel" ,.descriptionPickable="[E] Grab"});
	man_e.defineCMP<CInformation>(housedoor, CInformation{.description="", .descriptionPickable="[E] Knock the door"});
	man_e.defineCMP<CInformation>(figura, CInformation{.description="", .descriptionPickable="[E] Interact"});
	man_e.defineCMP<CInformation>(mailbox, CInformation{.descriptionPickable="[E] Open"});
	man_e.defineCMP<CInformation>(mailbox, CInformation{.descriptionPickable="[E] Open"});
	man_e.defineCMP<CInformation>(house_key, CInformation{.description="There's a rusty key inside" ,.descriptionPickable="[E] Grab"});
	//descripciones mundo
	man_e.defineCMP<CInformation>(arenero, CInformation{.type_of_text = 0, .description = "Now it's devoid of life"});
	man_e.defineCMP<CInformation>(columpio, CInformation{.type_of_text = 0, .description = "It's rusty. Hasn't been used in a while."});
	man_e.defineCMP<CInformation>(caperro, CInformation{.type_of_text = 1, .text_list{"Probably a dog house. Though i'm not sure","since there is no dog around",""}});
	man_e.defineCMP<CInformation>(pozo, CInformation{.type_of_text=0, .description="Needs a crank to work"});
	man_e.defineCMP<CInformation>(puerta_trasera, CInformation{.type_of_text = 0,.description="", .descriptionPickable ="[E] Try to open"});
	man_e.defineCMP<CInformation>(tp_lvl_Y, CInformation{.type_of_text = 0,.description="Looks like an old road to a barn", .descriptionPickable ="[E] Go"});
	
	man_e.defineCMP<CInformation>(cartel_granero, CInformation{.description="To the barn"});
	man_e.defineCMP<CInformation>(cartel_tumba,CInformation{.description="To the tomb"});
	man_e.defineCMP<CInformation>(cartel_iglesia, CInformation{.description="To the Church"});
//al barn posi mal
	std::cout << "Entities level 2 : " << man_e.getEntityArray().size() <<"\n";
	//std::cout << "ID entity [0] :  " << man_e.getEntityArray()[0].getID() << "\n";

}

void Levels::load_lvl_3(Manentity_type& man_e, Sys& systems, EngineGL& GL){
	
	InitSoundsLvl_3(man_e,systems.soundito);
	man_e.getLevelsStatus().actual = 3;
	//createPlayer(man_e, systems, GL);
	
	auto& player = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CInput, CCollision, CHealth, CStamina, CSound>();	
	man_e.addTagToEntity<TPlayer>(player);
	man_e.addTagToEntity<TCollider>(player);
	man_e.addTagToEntity<TNotRenderizable>(player); //HACER UN CUBE ACORDE AL PLAYER
	man_e.defineCMP<CPhysics>(player, CPhysics{.x=0, .y=1.5, .z=-0.5});
	man_e.defineCMP<CRenderGL>(player, CRenderGL{.modelMatrix= Model("assets/level1/cube.obj", glm::vec3(0,1.5,-3))});
	man_e.defineCMP<CSound>(player, CSound{.s_mgr = &systems.soundito, .name{"surface"}, .eventvalue = 0,});

	GL.camera.Position = { 0, 1.5, -0.5};
	////////////// PLAYER -- Model
	//	CMPS :  CRenderGL, CPhysics
	//	TAGS : 	TPlayer
	auto& player_model = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.addTagToEntity<TPlayer>(player_model);
	man_e.addTagToEntity<TNotRenderizable>(player_model);
	//man_e.defineCMP<CPhysics>(player_model, CPhysics{.x=4, .z= -4});
	man_e.defineCMP<CRenderGL>(player_model, CRenderGL{.modelMatrix= Model("assets/level1/brazo.obj", glm::vec3(0.7, -0.5, -2))}); 
	man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Scale(1.6,2,2);
	//man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Rotate(0, 0,1,0);
	////////////// PLAYER -- Model Candil with light
	//	CMPS :  CRenderGL, CPhysics, CPointLight
	//	TAGS : 	TPlayer
	auto& light = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CPointLight, CHealth, CSound, CCollision>(); //MIRAR BIEN
	//man_e.addTagToEntity<TPlayer>(light);
	man_e.addTagToEntity<TLantern>(light);
	man_e.addTagToEntity<TCollisionable>(light);
	man_e.addTagToEntity<Tpickable>(light);
	man_e.addTagToEntity<TScaleBoundingBox>(light);
	//man_e.addTagToEntity<TNotRenderizable>(light);
	man_e.defineCMP<CPhysics>(light,  CPhysics{.x=0.8, .y=0, .z=-45.5});
	man_e.defineCMP<CRenderGL>(light, CRenderGL{.modelMatrix = Model("assets/level1/Candil.obj", glm::vec3(0.8, -0.7, 0))});
	man_e.defineCMP<CSound>(light, CSound{.s_mgr= &systems.soundito}); 
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Scale(5,6,5);
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Rotate(90, 0,1,0);
	man_e.defineCMP<CPointLight>(light, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(light).setOff();
	//ESCENARIO
	
	auto& escenario = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.defineCMP<CRenderGL>(escenario, CRenderGL{ .modelMatrix = Model("assets/level3/lvl3.obj", glm::vec3(0,0,0))});
	
	//PUERTAS DE LA CASA
	auto& puerta = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CIDLvl>();
	man_e.addTagToEntity<TCollisionable>(puerta);
	man_e.addTagToEntity<TDoor>(puerta);
	//man_e.addTagToEntity<TScaleBoundingBox>(puerta);
	man_e.defineCMP<CPhysics>(puerta, CPhysics{.x =0.56, .y=0 ,.z= 0.33});
	man_e.defineCMP<CRenderGL>(puerta, CRenderGL{.modelMatrix = Model("assets/level3/Puerta.obj", glm::vec3(0,0,0))});
	auto& wall_puerta = man_e.createEntity_withCMPS<CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(wall_puerta);
	man_e.addTagToEntity<TWall>(wall_puerta);
	man_e.addTagToEntity<TNotRenderizable>(wall_puerta);
	man_e.defineCMP<CPhysics>(wall_puerta, CPhysics{.x =0.56, .y=0 ,.z= 0.41});
	man_e.defineCMP<CRenderGL>(wall_puerta, CRenderGL{.modelMatrix = Model("assets/level3/Puerta.obj", glm::vec3(0,0,0))});
	auto& puerta_salon = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CSound>();
	man_e.addTagToEntity<TCollisionable>(puerta_salon);
	man_e.addTagToEntity<TScaleBoundingBox>(puerta_salon);
	man_e.addTagToEntity<TDoor>(puerta_salon);
	man_e.defineCMP<CSound>(puerta_salon, CSound{.s_mgr = &systems.soundito});
	man_e.defineCMP<CPhysics>(puerta_salon, CPhysics{.x = 0.42, .y=0 ,.z= -2.80});
	man_e.defineCMP<CRenderGL>(puerta_salon, CRenderGL{.modelMatrix = Model("assets/level3/Puerta.obj", glm::vec3(0,0,0))});
	auto& wall_salon = man_e.createEntity_withCMPS<CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(wall_salon);
	man_e.addTagToEntity<TWall>(wall_salon);
	man_e.addTagToEntity<TNotRenderizable>(wall_salon);
	man_e.defineCMP<CPhysics>(wall_salon, CPhysics{.x = 0.42, .y=0 ,.z= -2.80});
	man_e.defineCMP<CRenderGL>(wall_salon, CRenderGL{.modelMatrix = Model("assets/level3/Puerta.obj", glm::vec3(0,0,0))});

	auto& puerta_habitacion = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CSound>();
	man_e.addTagToEntity<TCollisionable>(puerta_habitacion);
	man_e.addTagToEntity<TScaleBoundingBox>(puerta_habitacion);
	man_e.addTagToEntity<TDoor>(puerta_habitacion);
	man_e.addTagToEntity<TBedRoom>(puerta_habitacion);
	man_e.defineCMP<CSound>(puerta_habitacion, CSound{.s_mgr = &systems.soundito});
	man_e.defineCMP<CPhysics>(puerta_habitacion, CPhysics{.x = 8.86, .y=0 , .z= -0.53});
	man_e.defineCMP<CRenderGL>(puerta_habitacion, CRenderGL{.modelMatrix = Model("assets/level3/Puerta_Rotada.obj", glm::vec3(0,0,0))});
	auto& wall_habitacion = man_e.createEntity_withCMPS<CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(wall_habitacion);
	man_e.addTagToEntity<TWall>(wall_habitacion);
	man_e.addTagToEntity<TNotRenderizable>(wall_habitacion);
	man_e.defineCMP<CPhysics>(wall_habitacion, CPhysics{.x = 8.86, .y=0 , .z= -0.53});
	man_e.defineCMP<CRenderGL>(wall_habitacion, CRenderGL{.modelMatrix = Model("assets/level3/Puerta_Rotada.obj", glm::vec3(0,0,0))});

	auto& puerta_aseo = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CSound>();
	man_e.addTagToEntity<TCollisionable>(puerta_aseo);
	man_e.addTagToEntity<TScaleBoundingBox>(puerta_aseo);
	man_e.addTagToEntity<TDoor>(puerta_aseo);
	man_e.defineCMP<CSound>(puerta_aseo, CSound{.s_mgr = &systems.soundito});
	man_e.defineCMP<CPhysics>(puerta_aseo, CPhysics{.x = 17.85, .y=0 , .z = 0.64});
	man_e.defineCMP<CRenderGL>(puerta_aseo, CRenderGL{.modelMatrix = Model("assets/level3/Puerta.obj", glm::vec3(0,0,0))});
	auto& wall_aseo = man_e.createEntity_withCMPS<CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(wall_aseo);
	man_e.addTagToEntity<TWall>(wall_aseo);
	man_e.addTagToEntity<TNotRenderizable>(wall_aseo);
	man_e.defineCMP<CPhysics>(wall_aseo, CPhysics{.x = 17.85, .y=0 , .z = 0.64});
	man_e.defineCMP<CRenderGL>(wall_aseo, CRenderGL{.modelMatrix = Model("assets/level3/Puerta.obj", glm::vec3(0,0,0))});

	auto& puerta_trasera = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CIDLvl>();
	man_e.addTagToEntity<TCollisionable>(puerta_trasera);
	man_e.addTagToEntity<TDescription>(puerta_trasera);
	man_e.addTagToEntity<TScaleBoundingBox>(puerta_trasera);
	man_e.defineCMP<CPhysics>(puerta_trasera, CPhysics{.x =17.30, .y=0 , .z= -13.36});
	man_e.defineCMP<CRenderGL>(puerta_trasera, CRenderGL{.modelMatrix = Model("assets/level3/Puerta.obj", glm::vec3(0,0,0))});
	auto& wall_puerta_trasera = man_e.createEntity_withCMPS<CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(wall_puerta_trasera);
	man_e.addTagToEntity<TWall>(wall_puerta_trasera);
	man_e.addTagToEntity<TNotRenderizable>(wall_puerta_trasera);
	man_e.defineCMP<CPhysics>(wall_puerta_trasera, CPhysics{.x =17.30, .y=0 , .z= -13.36});
	man_e.defineCMP<CRenderGL>(wall_puerta_trasera, CRenderGL{.modelMatrix = Model("assets/level3/Puerta.obj", glm::vec3(0,0,0))});
	auto& fusibles_caja = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CSound>();
	man_e.addTagToEntity<TCollisionable>(fusibles_caja);
	man_e.addTagToEntity<TFuseBox>(fusibles_caja);
	man_e.addTagToEntity<TDescription>(fusibles_caja);
	man_e.defineCMP<CSound>(fusibles_caja, CSound{.s_mgr= &systems.soundito}); 
	man_e.defineCMP<CPhysics>(fusibles_caja, CPhysics{.x =-3, .y=1.80 , .z= -1.31});
	man_e.defineCMP<CRenderGL>(fusibles_caja, CRenderGL{.modelMatrix = Model("assets/level3/Caja_Fusibles.obj", glm::vec3(0,0,0))});
	auto& fusible_recogible = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CPng>();
	man_e.addTagToEntity<TCollisionable>(fusible_recogible);
	man_e.addTagToEntity<Tpickable>(fusible_recogible);
	man_e.addTagToEntity<TFuse>(fusible_recogible);
	man_e.addTagToEntity<TScaleBoundingBox>(fusible_recogible);
	man_e.addTagToEntity<TDescription>(fusible_recogible);
	//man_e.defineCMP<CSound>(fusible_recogible, CSound{.s_mgr= &systems.soundito}); 
	man_e.defineCMP<CPhysics>(fusible_recogible, CPhysics{.x =15.88, .y=0.94 , .z= -9.46});
	man_e.defineCMP<CPng>(fusible_recogible, CPng{.icono = Model("assets/level3/Fusibles_Solo.obj", glm::vec3(-0.70,0.42,0))});
	man_e.defineCMP<CRenderGL>(fusible_recogible, CRenderGL{.modelMatrix = Model("assets/level3/Fusibles_Solo.obj", glm::vec3(0,0,0))});

	auto& cuadro = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(cuadro);
	man_e.addTagToEntity<TObjectInteractuable>(cuadro);
	man_e.addTagToEntity<TPainting>(cuadro);
	man_e.addTagToEntity<TScaleBoundingBox>(cuadro);
	man_e.addTagToEntity<TDescription>(cuadro);
	man_e.defineCMP<CPhysics>(cuadro, CPhysics{.x =-2.99, .y=1.85 , .z= -5.02});
	man_e.defineCMP<CRenderGL>(cuadro, CRenderGL{.modelMatrix = Model("assets/level3/Cuadro.obj", glm::vec3(0,0,0))});
	auto& caja_fuerte = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision>();
	man_e.addTagToEntity<TCollisionable>(caja_fuerte);
	man_e.addTagToEntity<TScaleBoundingBox>(caja_fuerte);
	man_e.addTagToEntity<TSaveBox>(caja_fuerte);
	man_e.defineCMP<CPhysics>(caja_fuerte, CPhysics{.x =-3.57, .y=1.47 , .z= -5.07});
	man_e.defineCMP<CRenderGL>(caja_fuerte, CRenderGL{.modelMatrix = Model("assets/level3/Caja_Fuerte.obj", glm::vec3(0,0,0))});
	auto& caja_fuerte_puerta = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision>();
	man_e.defineCMP<CPhysics>(caja_fuerte_puerta, CPhysics{.x =-3.428, .y=1.66 , .z= -5.22});
	man_e.defineCMP<CRenderGL>(caja_fuerte_puerta, CRenderGL{.modelMatrix = Model("assets/level3/Caja_Fuerte_Puerta.obj", glm::vec3(0,0,0))});
	auto& anillo = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CSound, CPng>();
	man_e.addTagToEntity<TCollisionable>(anillo);
	man_e.addTagToEntity<TScaleBoundingBox>(anillo);

	man_e.addTagToEntity<TRing>(anillo);
	//man_e.addTagToEntity<TDescription>(anillo);
	man_e.defineCMP<CPhysics>(anillo, CPhysics{.x =-3.57, .y=1.60 , .z= -5.07});
	man_e.defineCMP<CSound>(anillo, CSound{.s_mgr = &systems.soundito});
	man_e.defineCMP<CPng>(anillo, CPng{.icono = Model("assets/level3/anillo.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CRenderGL>(anillo, CRenderGL{.modelMatrix = Model("assets/level3/anillo.obj", glm::vec3(0,0,0))});
	man_e.getEntityCMP<CRenderGL>(anillo).modelMatrix.Rotate(90, 0,0,-1);
	//COGER


	auto& telefono = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CSound>();
	man_e.addTagToEntity<TCollisionable>(telefono);
	man_e.addTagToEntity<TScaleBoundingBox>(telefono);
	man_e.addTagToEntity<TDescription>(telefono);
	man_e.addTagToEntity<TPhone>(telefono);
	man_e.defineCMP<CSound>(telefono, CSound{.s_mgr = &systems.soundito});
	man_e.defineCMP<CPhysics>(telefono, CPhysics{.x =18.12, .y=0.76 , .z= 6.41});
	man_e.defineCMP<CRenderGL>(telefono, CRenderGL{.modelMatrix = Model("assets/level3/Telefono.obj", glm::vec3(0,0,0))});
	man_e.getEntityCMP<CRenderGL>(telefono).modelMatrix.Rotate(90, 0,1,0);
	

	auto& granjero = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CSound>();
	man_e.addTagToEntity<TCollisionable>(granjero);
	man_e.addTagToEntity<TScaleBoundingBox>(granjero);
	man_e.addTagToEntity<TDescription>(granjero);
	man_e.addTagToEntity<TFarmer>(granjero);
	man_e.addTagToEntity<TObjectInteractuable>(granjero);
	man_e.defineCMP<CSound>(granjero, CSound{.s_mgr = &systems.soundito});
	man_e.defineCMP<CPhysics>(granjero, CPhysics{.x=14.48, .y=0.0, .z=5.20});
	man_e.defineCMP<CRenderGL>(granjero, CRenderGL{.modelMatrix = Model("assets/level3/persona.obj", glm::vec3(0,0,0))});

	auto& quemable_casa = man_e.createEntity_withCMPS< CPhysics, CRenderGL, CCollision, CSound>();
	man_e.addTagToEntity<TCollisionable>(quemable_casa);
	man_e.addTagToEntity<TWall>(quemable_casa);
	man_e.defineCMP<CSound>(quemable_casa, CSound{.s_mgr = &systems.soundito});
	man_e.defineCMP<CPhysics>(quemable_casa, CPhysics{.x =16.63, .y=1.14 ,.z= -2.79});
	man_e.defineCMP<CRenderGL>(quemable_casa, CRenderGL{.modelMatrix = Model("assets/level3/Quemable_Casa.obj", glm::vec3(0,0,0))});
	auto& quemable_casa_txt = man_e.createEntity_withCMPS<CInformation, CPhysics, CRenderGL, CCollision, CReference, CSound>();
	man_e.addTagToEntity<TCollisionable>(quemable_casa_txt);
	man_e.addTagToEntity<TBurnable>(quemable_casa_txt);
	man_e.addTagToEntity<TDescription>(quemable_casa_txt);
	man_e.addTagToEntity<TNotRenderizable>(quemable_casa_txt);
	man_e.defineCMP<CSound>(quemable_casa_txt, CSound{.s_mgr = &systems.soundito});
	man_e.defineCMP<CReference>(quemable_casa_txt, CReference{.id_reference = quemable_casa.getID()});
	man_e.defineCMP<CPhysics>(quemable_casa_txt, CPhysics{.x =16.63, .y=0.6 ,.z= -1.99});
	man_e.defineCMP<CRenderGL>(quemable_casa_txt, CRenderGL{.modelMatrix = Model("assets/level1/cube.obj", glm::vec3(0,0,0))});
	// enemigo 1 
	auto& enemy = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CCollision, CSound ,CAnimation>();
	man_e.addTagToEntity<TEnemy>(enemy);
	man_e.addTagToEntity<TCollider>(enemy);
	man_e.addTagToEntity<TDummy>(enemy);
	man_e.addTagToEntity<TNotPatrol>(enemy);
	man_e.addTagToEntity<TNotRenderizable>(enemy);
	man_e.defineCMP<CPhysics>(enemy, CPhysics{.x = 12.5, .y = 0, .z = -1});
	man_e.defineCMP<CIA>(enemy, CIA{.dt = &systems.dtree});
	man_e.defineCMP<CSound>(enemy, CSound{.s_mgr = &systems.soundito});
	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
 	man_e.getEntityCMP<CAnimation>(enemy).animation = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix);
	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(180,0,1,0);
	man_e.getEntityCMP<CAnimation>(enemy).animator = Animator(&man_e.getEntityCMP<CAnimation>(enemy).animation);
	//man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Scale(0.5,0.5,0.5);
	man_e.getEntityCMP<CIA>(enemy).origin = man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.nodeMatrix;
	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(10,0,1,0);
	
	// enemigo 2
	auto& enemy2 = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound, CCollision, CAnimation>();
	man_e.addTagToEntity<TEnemy>(enemy2);
	man_e.addTagToEntity<TCollider>(enemy2);
	man_e.addTagToEntity<TDummy>(enemy2);
	man_e.addTagToEntity<TNotPatrol>(enemy2);
	man_e.addTagToEntity<TNotRenderizable>(enemy2);
	man_e.defineCMP<CPhysics>(enemy2, CPhysics{.x = 19, .y = 0, .z = 2.5});
	man_e.defineCMP<CIA>(enemy2, CIA{.dt = &systems.dtree});
	man_e.defineCMP<CSound>(enemy2, CSound{.s_mgr = &systems.soundito});
	man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
 	man_e.getEntityCMP<CAnimation>(enemy2).animation = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix);
	man_e.getEntityCMP<CAnimation>(enemy2).animator = Animator(&man_e.getEntityCMP<CAnimation>(enemy).animation);
	man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix.Rotate(180,0,1,0);
	//man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix.Scale(0.5,0.5,0.5);
	man_e.getEntityCMP<CIA>(enemy2).origin = man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix.nodeMatrix;
	man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix.Rotate(75,0,1,0);
	//man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix.Scale(1.3,1.3,1.3);
	// enemigo 3 
	auto& enemy3 = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound, CCollision, CAnimation>();
	man_e.addTagToEntity<TEnemy>(enemy3);
	man_e.addTagToEntity<TCollider>(enemy3);
	man_e.addTagToEntity<TDummy>(enemy3);
	man_e.addTagToEntity<TNotPatrol>(enemy3);
	man_e.addTagToEntity<TNotRenderizable>(enemy3);
	man_e.defineCMP<CPhysics>(enemy3, CPhysics{.x =10.5, .y = 0, .z = 3});
	man_e.defineCMP<CIA>(enemy3, CIA{.dt = &systems.dtree});
	man_e.defineCMP<CSound>(enemy3, CSound{.s_mgr = &systems.soundito});
	man_e.getEntityCMP<CRenderGL>(enemy3).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
 	man_e.getEntityCMP<CAnimation>(enemy3).animation = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy3).modelMatrix);
	man_e.getEntityCMP<CAnimation>(enemy3).animator = Animator(&man_e.getEntityCMP<CAnimation>(enemy3).animation);
    man_e.getEntityCMP<CRenderGL>(enemy3).modelMatrix.Rotate(180,0,1,0);
	//man_e.getEntityCMP<CRenderGL>(enemy3).modelMatrix.Scale(0.5,0.5,0.5);
	man_e.getEntityCMP<CIA>(enemy3).origin = man_e.getEntityCMP<CRenderGL>(enemy3).modelMatrix.nodeMatrix;
	man_e.getEntityCMP<CRenderGL>(enemy3).modelMatrix.Rotate(165,0,1,0);
	//COLISIONES INTERIOR CASA
	{
	auto& Col_Casa = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa );
	man_e.addTagToEntity<TCollisionable>(Col_Casa );
	man_e.addTagToEntity<TWall>(Col_Casa );
	man_e.defineCMP<CPhysics>(Col_Casa , CPhysics{.x= -3.1337459087371826 , .y = 0.0, .z = -6.496933937072754});
	man_e.defineCMP<CRenderGL>(Col_Casa , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_001 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_001 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_001 );
	man_e.addTagToEntity<TWall>(Col_Casa_001 );
	man_e.defineCMP<CPhysics>(Col_Casa_001 , CPhysics{.x= 6.478853225708008 , .y = 0.0, .z = -13.34577465057373});
	man_e.defineCMP<CRenderGL>(Col_Casa_001 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.001.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_002 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_002 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_002 );
	man_e.addTagToEntity<TWall>(Col_Casa_002 );
	man_e.defineCMP<CPhysics>(Col_Casa_002 , CPhysics{.x= 19.02652931213379 , .y = 0.0, .z = -13.360952377319336});
	man_e.defineCMP<CRenderGL>(Col_Casa_002 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.002.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_003 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_003 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_003 );
	man_e.addTagToEntity<TWall>(Col_Casa_003 );
	man_e.defineCMP<CPhysics>(Col_Casa_003 , CPhysics{.x= 20.227262496948242 , .y = 0.0, .z = -3.0306308269500732});
	man_e.defineCMP<CRenderGL>(Col_Casa_003 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.003.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_004 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_004 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_004 );
	man_e.addTagToEntity<TWall>(Col_Casa_004 );
	man_e.defineCMP<CPhysics>(Col_Casa_004 , CPhysics{.x= 14.563971519470215 , .y = 0.0, .z = 7.1281328201293945});
	man_e.defineCMP<CRenderGL>(Col_Casa_004 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.004.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_005 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_005 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_005 );
	man_e.addTagToEntity<TWall>(Col_Casa_005 );
	man_e.defineCMP<CPhysics>(Col_Casa_005 , CPhysics{.x= 8.86541748046875 , .y = 0.0, .z = 3.538287401199341});
	man_e.defineCMP<CRenderGL>(Col_Casa_005 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.005.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_006 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_006 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_006 );
	man_e.addTagToEntity<TWall>(Col_Casa_006 );
	man_e.defineCMP<CPhysics>(Col_Casa_006 , CPhysics{.x= 4.654849529266357 , .y = 0.0, .z = 0.40509656071662903});
	man_e.defineCMP<CRenderGL>(Col_Casa_006 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.006.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_007 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_007 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_007 );
	man_e.addTagToEntity<TWall>(Col_Casa_007 );
	man_e.defineCMP<CPhysics>(Col_Casa_007 , CPhysics{.x= -1.9785757064819336 , .y = 0.0, .z = 0.40509656071662903});
	man_e.defineCMP<CRenderGL>(Col_Casa_007 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.007.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_008 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_008 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_008 );
	man_e.addTagToEntity<TWall>(Col_Casa_008 );
	man_e.defineCMP<CPhysics>(Col_Casa_008 , CPhysics{.x= -2.06711745262146 , .y = 0.0, .z = -2.807798147201538});
	man_e.defineCMP<CRenderGL>(Col_Casa_008 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.008.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_009 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_009 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_009 );
	man_e.addTagToEntity<TWall>(Col_Casa_009 );
	man_e.defineCMP<CPhysics>(Col_Casa_009 , CPhysics{.x= 8.123549461364746 , .y = 0.0, .z = -2.807798147201538});
	man_e.defineCMP<CRenderGL>(Col_Casa_009 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.009.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_010 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_010 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_010 );
	man_e.addTagToEntity<TWall>(Col_Casa_010 );
	man_e.defineCMP<CPhysics>(Col_Casa_010 , CPhysics{.x= 18.793636322021484 , .y = 0.0, .z = -2.807795286178589});
	man_e.defineCMP<CRenderGL>(Col_Casa_010 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.010.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_011 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_011 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_011 );
	man_e.addTagToEntity<TWall>(Col_Casa_011 );
	man_e.defineCMP<CPhysics>(Col_Casa_011 , CPhysics{.x= 19.036062240600586 , .y = 0.0, .z = 0.6494321227073669});
	man_e.defineCMP<CRenderGL>(Col_Casa_011 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.011.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_012 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_012 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_012 );
	man_e.addTagToEntity<TWall>(Col_Casa_012 );
	man_e.defineCMP<CPhysics>(Col_Casa_012 , CPhysics{.x= 15.431270599365234 , .y = 0.0, .z = 0.6494321227073669});
	man_e.defineCMP<CRenderGL>(Col_Casa_012 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.012.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_013 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_013 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_013 );
	man_e.addTagToEntity<TWall>(Col_Casa_013 );
	man_e.defineCMP<CPhysics>(Col_Casa_013 , CPhysics{.x= 14.352018356323242 , .y = 0.0, .z = -1.0680561065673828});
	man_e.defineCMP<CRenderGL>(Col_Casa_013 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.013.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_014 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_014 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_014 );
	man_e.addTagToEntity<TWall>(Col_Casa_014 );
	man_e.defineCMP<CPhysics>(Col_Casa_014 , CPhysics{.x= 8.86595344543457 , .y = 0.0, .z = -2.3663337230682373});
	man_e.defineCMP<CRenderGL>(Col_Casa_014 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.014.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_015 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_015 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_015 );
	man_e.addTagToEntity<TWall>(Col_Casa_015 );
	man_e.defineCMP<CPhysics>(Col_Casa_015 , CPhysics{.x= 12.078847885131836 , .y = 0.0, .z = -12.251666069030762});
	man_e.defineCMP<CRenderGL>(Col_Casa_015 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.015.obj", glm::vec3(0,0,0))});

	auto& Col_Casa_016 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_Casa_016 );
	man_e.addTagToEntity<TCollisionable>(Col_Casa_016 );
	man_e.addTagToEntity<TWall>(Col_Casa_016 );
	man_e.defineCMP<CPhysics>(Col_Casa_016 , CPhysics{.x= 12.078847885131836 , .y = 4.81864432799739e-08, .z = -6.3638386726379395});
	man_e.defineCMP<CRenderGL>(Col_Casa_016 , CRenderGL{.modelMatrix = Model("assets/level3/Col_Casa.016.obj", glm::vec3(0,0,0))});

	//COLISIONES DE LOS MUEBLES
	
	auto& Col_CasaM = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM );
	man_e.addTagToEntity<TWall>(Col_CasaM );
	man_e.defineCMP<CPhysics>(Col_CasaM , CPhysics{.x= 4.5418782234191895 , .y = 1.1905637979507446, .z = -2.486508846282959});
	man_e.defineCMP<CRenderGL>(Col_CasaM , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_001 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_001 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_001 );
	man_e.addTagToEntity<TWall>(Col_CasaM_001 );
	man_e.defineCMP<CPhysics>(Col_CasaM_001 , CPhysics{.x= 13.228334426879883 , .y = 1.1905637979507446, .z = 0.6826737523078918});
	man_e.defineCMP<CRenderGL>(Col_CasaM_001 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.001.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_002 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_002 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_002 );
	man_e.addTagToEntity<TWall>(Col_CasaM_002 );
	man_e.defineCMP<CPhysics>(Col_CasaM_002 , CPhysics{.x= 11.334111213684082 , .y = 1.1905635595321655, .z = 5.655010223388672});
	man_e.defineCMP<CRenderGL>(Col_CasaM_002 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.002.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_003 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_003 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_003 );
	man_e.addTagToEntity<TWall>(Col_CasaM_003 );
	man_e.defineCMP<CPhysics>(Col_CasaM_003 , CPhysics{.x= 9.418591499328613 , .y = 1.1905635595321655, .z = 6.460563659667969});
	man_e.defineCMP<CRenderGL>(Col_CasaM_003 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.003.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_004 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_004 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_004 );
	man_e.addTagToEntity<TWall>(Col_CasaM_004 );
	man_e.defineCMP<CPhysics>(Col_CasaM_004 , CPhysics{.x= 17.7946720123291 , .y = 1.1905635595321655, .z = 6.456747722625732});
	man_e.defineCMP<CRenderGL>(Col_CasaM_004 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.004.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_005 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_005 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_005 );
	man_e.addTagToEntity<TWall>(Col_CasaM_005 );
	man_e.defineCMP<CPhysics>(Col_CasaM_005 , CPhysics{.x= 19.352590560913086 , .y = 1.057325005531311, .z = 0.12855558097362518});
	man_e.defineCMP<CRenderGL>(Col_CasaM_005 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.005.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_006 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_006 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_006 );
	man_e.addTagToEntity<TWall>(Col_CasaM_006 );
	man_e.defineCMP<CPhysics>(Col_CasaM_006 , CPhysics{.x= 19.106706619262695 , .y = 1.057325005531311, .z = -2.2392237186431885});
	man_e.defineCMP<CRenderGL>(Col_CasaM_006 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.006.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_007 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_007 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_007 );
	man_e.addTagToEntity<TWall>(Col_CasaM_007 );
	man_e.defineCMP<CPhysics>(Col_CasaM_007 , CPhysics{.x= 14.086084365844727 , .y = 1.057325005531311, .z = -0.9079595804214478});
	man_e.defineCMP<CRenderGL>(Col_CasaM_007 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.007.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_008 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_008 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_008 );
	man_e.addTagToEntity<TWall>(Col_CasaM_008 );
	man_e.defineCMP<CPhysics>(Col_CasaM_008 , CPhysics{.x= 4.523681163787842 , .y = 1.057325005531311, .z = -2.1542654037475586});
	man_e.defineCMP<CRenderGL>(Col_CasaM_008 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.008.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_009 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_009 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_009 );
	man_e.addTagToEntity<TWall>(Col_CasaM_009 );
	man_e.defineCMP<CPhysics>(Col_CasaM_009 , CPhysics{.x= 2.0586142539978027 , .y = 1.053159236907959, .z = -5.176635265350342});
	man_e.defineCMP<CRenderGL>(Col_CasaM_009 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.009.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_010 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_010 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_010 );
	man_e.addTagToEntity<TWall>(Col_CasaM_010 );
	man_e.defineCMP<CPhysics>(Col_CasaM_010 , CPhysics{.x= 5.241843223571777 , .y = 1.0047500133514404, .z = -10.175806045532227});
	man_e.defineCMP<CRenderGL>(Col_CasaM_010 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.010.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_011 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_011 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_011 );
	man_e.addTagToEntity<TWall>(Col_CasaM_011 );
	man_e.defineCMP<CPhysics>(Col_CasaM_011 , CPhysics{.x= -0.028349488973617554 , .y = 1.0047500133514404, .z = -8.645856857299805});
	man_e.defineCMP<CRenderGL>(Col_CasaM_011 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.011.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_012 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_012 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_012 );
	man_e.addTagToEntity<TWall>(Col_CasaM_012 );
	man_e.defineCMP<CPhysics>(Col_CasaM_012 , CPhysics{.x= 0.11085638403892517 , .y = 0.6356117725372314, .z = -10.963936805725098});
	man_e.defineCMP<CRenderGL>(Col_CasaM_012 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.012.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_013 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_013 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_013 );
	man_e.addTagToEntity<TWall>(Col_CasaM_013 );
	man_e.defineCMP<CPhysics>(Col_CasaM_013 , CPhysics{.x= 0.08703248202800751 , .y = 0.6356117725372314, .z = -12.894588470458984});
	man_e.defineCMP<CRenderGL>(Col_CasaM_013 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.013.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_014 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_014 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_014 );
	man_e.addTagToEntity<TWall>(Col_CasaM_014 );
	man_e.defineCMP<CPhysics>(Col_CasaM_014 , CPhysics{.x= 8.897323608398438 , .y = 0.6356117725372314, .z = -12.899188041687012});
	man_e.defineCMP<CRenderGL>(Col_CasaM_014 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.014.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_015 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_015 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_015 );
	man_e.addTagToEntity<TWall>(Col_CasaM_015 );
	man_e.defineCMP<CPhysics>(Col_CasaM_015 , CPhysics{.x= 8.02364730834961 , .y = 0.6356117725372314, .z = -6.186954021453857});
	man_e.defineCMP<CRenderGL>(Col_CasaM_015 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.015.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_016 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_016 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_016 );
	man_e.addTagToEntity<TWall>(Col_CasaM_016 );
	man_e.defineCMP<CPhysics>(Col_CasaM_016 , CPhysics{.x= 16.681171417236328 , .y = 0.6356117129325867, .z = -7.4765801429748535});
	man_e.defineCMP<CRenderGL>(Col_CasaM_016 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.016.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_017 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_017 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_017 );
	man_e.addTagToEntity<TWall>(Col_CasaM_017 );
	man_e.defineCMP<CPhysics>(Col_CasaM_017 , CPhysics{.x= 19.787002563476562 , .y = 0.6356118321418762, .z = -7.567648887634277});
	man_e.defineCMP<CRenderGL>(Col_CasaM_017 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.017.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_018 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_018 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_018 );
	man_e.addTagToEntity<TWall>(Col_CasaM_018 );
	man_e.defineCMP<CPhysics>(Col_CasaM_018 , CPhysics{.x= 12.461625099182129 , .y = 0.6356118321418762, .z = -3.6436760425567627});
	man_e.defineCMP<CRenderGL>(Col_CasaM_018 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.018.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_019 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_019 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_019 );
	man_e.addTagToEntity<TWall>(Col_CasaM_019 );
	man_e.defineCMP<CPhysics>(Col_CasaM_019 , CPhysics{.x= 12.461625099182129 , .y = 0.6356118321418762, .z = -12.255107879638672});
	man_e.defineCMP<CRenderGL>(Col_CasaM_019 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.019.obj", glm::vec3(0,0,0))});

	auto& Col_CasaM_020 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Col_CasaM_020 );
	man_e.addTagToEntity<TCollisionable>(Col_CasaM_020 );
	man_e.addTagToEntity<TWall>(Col_CasaM_020 );
	man_e.defineCMP<CPhysics>(Col_CasaM_020 , CPhysics{.x= 14.674601554870605 , .y = 0.6356118321418762, .z = -1.1484493017196655});
	man_e.defineCMP<CRenderGL>(Col_CasaM_020 , CRenderGL{.modelMatrix = Model("assets/level3/Col_CasaM.020.obj", glm::vec3(0,0,0))});
	
	//Mapa pathfinding
	auto& map = man_e.createEntity_withCMPS<CMap>();
	
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -1.98, -12.31 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  2.31, -11.99 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  5.11, -12.60 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  7.32, -11.89 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 10.78, -11.73 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 10.60, -10.22 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 11.11,  -8.56 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  6.76,  -8.87 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  3.54,  -7.82 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  0.18, -10.03 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -2.41,  -8.48 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -2.41,  -5.15 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -0.03,  -5.15 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  4.31,  -5.15 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,   8.2,  -3.89 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 11.09,  -3.89 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 11.19,  -6.22 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 12.06, -10.45 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 13.92, -12.02 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 16.20, -12.15 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 18.17, -12.41 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 14.45,  -9.42 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 14.45,  -6.38 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 14.45,  -4.07 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 16.94,  -3.99 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 16.54,   -1.9 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 17.33,   -0.4 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 17.31,  0.61);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 19.07,  2.09);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 18.91,  5.3 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 16.39,  5.36);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 15.92,  2.12);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 11.80,  1.96);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 13.56,  5.46);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 9.72 ,  1.46);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 12.68, -1.9 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 10.04, -1.8 );
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  8.84, -1.05);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  6.51, -0.76);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  2.64, -0.79);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -0.75, -1.05);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -0.22, -2.81);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 18.38, -9.54);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 18.31, -9.54);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, 18.47, -4.57);

//45

	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, -0.53, -11.28);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  0.84, -11.34);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, -0.62, -10.65);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  0.75, -10.65);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, -0.97, -8.73);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  0.97, -8.66);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  6.64, -6.96);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  9.44, -7.03);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  6.48, -5.23);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  9.41, -5.3);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  2.04, -5.2);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  5.28, -10.43);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 12.08, -12.37);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 12.08, -11.58);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 12.08, -9.32);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 12.08, -7.3);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 12.08, -4.81);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 12.08, -2.87);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 12.57, -3.82);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 13.41, -2.82);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 15.54, -2.77);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 18.19, -2.77);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 18.21, -1.88);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 20.02, -1.80);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 15.90, -5.13);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 15.88, -7.44);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 15.93, -9.77);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 17.43, -9.82);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 17.53, -7.41);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 17.50, -5.08);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 19.92,  0.61);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 18.45,  0.61);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 16.11,  0.63);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 14.38,  0.61);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 13.36,  0.66);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 12.29,  0.58);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 10.97, -2.79);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  7.30, -2.82);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  5.41, -2.79);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  3.55, -2.85);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  1.51, -2.79);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, -1.92, -2.82);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  8.82, -0.12);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 10.61,  4.41);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 12.10,  4.46);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 10.60,  6.88);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 12.11,  6.88);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 17.10,  6.62);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, 18.61,  6.54);

	man_e.getEntityCMP<CMap>(map).map[0].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[1]);
	man_e.getEntityCMP<CMap>(map).map[0].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[10]);
	man_e.getEntityCMP<CMap>(map).map[0].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[45]);
	
	man_e.getEntityCMP<CMap>(map).map[1].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[0]);
	man_e.getEntityCMP<CMap>(map).map[1].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[2]);
	man_e.getEntityCMP<CMap>(map).map[1].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[8]);
	
	man_e.getEntityCMP<CMap>(map).map[2].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[1]);
	man_e.getEntityCMP<CMap>(map).map[2].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[3]);
	man_e.getEntityCMP<CMap>(map).map[2].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[56]);
	
	man_e.getEntityCMP<CMap>(map).map[3].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[2]);
	man_e.getEntityCMP<CMap>(map).map[3].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[4]);
	man_e.getEntityCMP<CMap>(map).map[3].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[7]);
	man_e.getEntityCMP<CMap>(map).map[3].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[56]);

	man_e.getEntityCMP<CMap>(map).map[4].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[5]);
	man_e.getEntityCMP<CMap>(map).map[4].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[57]);

	man_e.getEntityCMP<CMap>(map).map[5].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[4]);
	man_e.getEntityCMP<CMap>(map).map[5].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[6]);
	man_e.getEntityCMP<CMap>(map).map[5].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[7]);
	man_e.getEntityCMP<CMap>(map).map[5].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[17]);

	man_e.getEntityCMP<CMap>(map).map[6].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[5]);
	man_e.getEntityCMP<CMap>(map).map[6].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[16]);
	man_e.getEntityCMP<CMap>(map).map[6].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[59]);
	man_e.getEntityCMP<CMap>(map).map[6].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[52]);

	man_e.getEntityCMP<CMap>(map).map[7].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[3]);
	man_e.getEntityCMP<CMap>(map).map[7].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[8]);
	man_e.getEntityCMP<CMap>(map).map[7].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[51]);
	man_e.getEntityCMP<CMap>(map).map[7].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[56]);

	man_e.getEntityCMP<CMap>(map).map[8].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[1]);
	man_e.getEntityCMP<CMap>(map).map[8].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[7]);
	man_e.getEntityCMP<CMap>(map).map[8].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[13]);
	man_e.getEntityCMP<CMap>(map).map[8].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[50]);
	man_e.getEntityCMP<CMap>(map).map[8].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[51]);
	man_e.getEntityCMP<CMap>(map).map[8].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[56]);

	man_e.getEntityCMP<CMap>(map).map[9].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[8]);
	man_e.getEntityCMP<CMap>(map).map[9].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[10]);
	man_e.getEntityCMP<CMap>(map).map[9].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[48]);
	man_e.getEntityCMP<CMap>(map).map[9].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[49]);
	man_e.getEntityCMP<CMap>(map).map[9].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[50]);
	
	man_e.getEntityCMP<CMap>(map).map[10].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[0]);
	man_e.getEntityCMP<CMap>(map).map[10].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[11]);
	man_e.getEntityCMP<CMap>(map).map[10].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[12]);
	man_e.getEntityCMP<CMap>(map).map[10].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[49]);

	man_e.getEntityCMP<CMap>(map).map[11].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[10]);
	man_e.getEntityCMP<CMap>(map).map[11].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[12]);
	man_e.getEntityCMP<CMap>(map).map[11].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[86]);

	man_e.getEntityCMP<CMap>(map).map[12].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[11]);
	man_e.getEntityCMP<CMap>(map).map[12].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[49]);
	man_e.getEntityCMP<CMap>(map).map[12].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[41]);
	man_e.getEntityCMP<CMap>(map).map[12].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[55]);

	man_e.getEntityCMP<CMap>(map).map[13].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[8]); 
	man_e.getEntityCMP<CMap>(map).map[13].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[14]);
	man_e.getEntityCMP<CMap>(map).map[13].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[53]);
	man_e.getEntityCMP<CMap>(map).map[13].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[84]);
	man_e.getEntityCMP<CMap>(map).map[13].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[83]);

	man_e.getEntityCMP<CMap>(map).map[14].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[13]);
	man_e.getEntityCMP<CMap>(map).map[14].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[15]);
	man_e.getEntityCMP<CMap>(map).map[14].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[53]);
	man_e.getEntityCMP<CMap>(map).map[14].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[54]);
	man_e.getEntityCMP<CMap>(map).map[14].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[82]);
	man_e.getEntityCMP<CMap>(map).map[14].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[81]);

	man_e.getEntityCMP<CMap>(map).map[15].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[14]);
	man_e.getEntityCMP<CMap>(map).map[15].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[16]);
	man_e.getEntityCMP<CMap>(map).map[15].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[81]);
	man_e.getEntityCMP<CMap>(map).map[15].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[63]);

	man_e.getEntityCMP<CMap>(map).map[16].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[6]);
	man_e.getEntityCMP<CMap>(map).map[16].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[15]);
	man_e.getEntityCMP<CMap>(map).map[16].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[54]);
	man_e.getEntityCMP<CMap>(map).map[16].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[61]);

	man_e.getEntityCMP<CMap>(map).map[17].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[4]);
	man_e.getEntityCMP<CMap>(map).map[17].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[5]);
	man_e.getEntityCMP<CMap>(map).map[17].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[18]);
	man_e.getEntityCMP<CMap>(map).map[17].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[21]);

	man_e.getEntityCMP<CMap>(map).map[18].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[17]);
	man_e.getEntityCMP<CMap>(map).map[18].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[19]);
	man_e.getEntityCMP<CMap>(map).map[18].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[57]);
	man_e.getEntityCMP<CMap>(map).map[18].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[21]);

	man_e.getEntityCMP<CMap>(map).map[19].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[18]);
	man_e.getEntityCMP<CMap>(map).map[19].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[20]);
	man_e.getEntityCMP<CMap>(map).map[19].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[71]);
	man_e.getEntityCMP<CMap>(map).map[19].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[72]);

	man_e.getEntityCMP<CMap>(map).map[20].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[19]);
	man_e.getEntityCMP<CMap>(map).map[20].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[42]);
	man_e.getEntityCMP<CMap>(map).map[20].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[72]);

	man_e.getEntityCMP<CMap>(map).map[21].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[17]);
	man_e.getEntityCMP<CMap>(map).map[21].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[18]);
	man_e.getEntityCMP<CMap>(map).map[21].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[22]);
	man_e.getEntityCMP<CMap>(map).map[21].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[71]);

	man_e.getEntityCMP<CMap>(map).map[22].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[21]);
	man_e.getEntityCMP<CMap>(map).map[22].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[23]);
	man_e.getEntityCMP<CMap>(map).map[22].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[60]);
	man_e.getEntityCMP<CMap>(map).map[22].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[61]);
	man_e.getEntityCMP<CMap>(map).map[22].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[69]);

	man_e.getEntityCMP<CMap>(map).map[23].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[22]);
	man_e.getEntityCMP<CMap>(map).map[23].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[24]);
	man_e.getEntityCMP<CMap>(map).map[23].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[69]);
	man_e.getEntityCMP<CMap>(map).map[23].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[63]);
	man_e.getEntityCMP<CMap>(map).map[23].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[64]);
	man_e.getEntityCMP<CMap>(map).map[23].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[65]);

	man_e.getEntityCMP<CMap>(map).map[24].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[23]);
	man_e.getEntityCMP<CMap>(map).map[24].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[25]);
	man_e.getEntityCMP<CMap>(map).map[24].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[61]);
	man_e.getEntityCMP<CMap>(map).map[24].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[65]);
	man_e.getEntityCMP<CMap>(map).map[24].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[74]);
	man_e.getEntityCMP<CMap>(map).map[24].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[44]);

	man_e.getEntityCMP<CMap>(map).map[25].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[24]);
	man_e.getEntityCMP<CMap>(map).map[25].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[26]);
	man_e.getEntityCMP<CMap>(map).map[25].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[67]);
	man_e.getEntityCMP<CMap>(map).map[25].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[78]);

	man_e.getEntityCMP<CMap>(map).map[26].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[25]);
	man_e.getEntityCMP<CMap>(map).map[26].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[27]);
	man_e.getEntityCMP<CMap>(map).map[26].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[67]);
	man_e.getEntityCMP<CMap>(map).map[26].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[76]);

	man_e.getEntityCMP<CMap>(map).map[27].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[31]);
	man_e.getEntityCMP<CMap>(map).map[27].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[28]);
	man_e.getEntityCMP<CMap>(map).map[27].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[76]);
	man_e.getEntityCMP<CMap>(map).map[27].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[77]);

	man_e.getEntityCMP<CMap>(map).map[28].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[29]);
	man_e.getEntityCMP<CMap>(map).map[28].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[31]);
	man_e.getEntityCMP<CMap>(map).map[28].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[27]);
	man_e.getEntityCMP<CMap>(map).map[28].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[76]);

	man_e.getEntityCMP<CMap>(map).map[29].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[93]);
	man_e.getEntityCMP<CMap>(map).map[29].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[30]);
	man_e.getEntityCMP<CMap>(map).map[29].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[28]);
	man_e.getEntityCMP<CMap>(map).map[29].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[31]);

	man_e.getEntityCMP<CMap>(map).map[30].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[28]);
	man_e.getEntityCMP<CMap>(map).map[30].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[29]);
	man_e.getEntityCMP<CMap>(map).map[30].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[33]);
	man_e.getEntityCMP<CMap>(map).map[30].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[31]);

	man_e.getEntityCMP<CMap>(map).map[31].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[27]);
	man_e.getEntityCMP<CMap>(map).map[31].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[28]);
	man_e.getEntityCMP<CMap>(map).map[31].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[29]);
	man_e.getEntityCMP<CMap>(map).map[31].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[33]);
	man_e.getEntityCMP<CMap>(map).map[31].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[32]);

	man_e.getEntityCMP<CMap>(map).map[32].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[31]);
	man_e.getEntityCMP<CMap>(map).map[32].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[34]);
	man_e.getEntityCMP<CMap>(map).map[32].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[89]);
	man_e.getEntityCMP<CMap>(map).map[32].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[88]);

	man_e.getEntityCMP<CMap>(map).map[33].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[30]);
	man_e.getEntityCMP<CMap>(map).map[33].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[31]);
	man_e.getEntityCMP<CMap>(map).map[33].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[32]);
	man_e.getEntityCMP<CMap>(map).map[33].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[91]);

	man_e.getEntityCMP<CMap>(map).map[34].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[32]);
	man_e.getEntityCMP<CMap>(map).map[34].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[37]);
	man_e.getEntityCMP<CMap>(map).map[34].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[36]);
	man_e.getEntityCMP<CMap>(map).map[34].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[87]);
	man_e.getEntityCMP<CMap>(map).map[34].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[88]);

	man_e.getEntityCMP<CMap>(map).map[35].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[36]);
	man_e.getEntityCMP<CMap>(map).map[35].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[79]);
	man_e.getEntityCMP<CMap>(map).map[35].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[80]);
	man_e.getEntityCMP<CMap>(map).map[35].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[62]);

	man_e.getEntityCMP<CMap>(map).map[36].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[35]);	
	man_e.getEntityCMP<CMap>(map).map[36].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[37]);
	man_e.getEntityCMP<CMap>(map).map[36].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[34]);
		
	man_e.getEntityCMP<CMap>(map).map[37].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[87]);
	man_e.getEntityCMP<CMap>(map).map[37].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[38]);
	man_e.getEntityCMP<CMap>(map).map[37].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[36]);
	man_e.getEntityCMP<CMap>(map).map[37].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[34]);

	man_e.getEntityCMP<CMap>(map).map[38].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[37]);
	man_e.getEntityCMP<CMap>(map).map[38].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[39]);
	man_e.getEntityCMP<CMap>(map).map[38].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[82]);
	man_e.getEntityCMP<CMap>(map).map[38].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[83]);

	man_e.getEntityCMP<CMap>(map).map[39].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[38]);
	man_e.getEntityCMP<CMap>(map).map[39].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[40]);
	man_e.getEntityCMP<CMap>(map).map[39].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[84]);
	man_e.getEntityCMP<CMap>(map).map[39].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[85]);

	man_e.getEntityCMP<CMap>(map).map[40].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[39]);
	man_e.getEntityCMP<CMap>(map).map[40].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[41]);
	man_e.getEntityCMP<CMap>(map).map[40].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[85]);
	man_e.getEntityCMP<CMap>(map).map[40].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[86]);

	man_e.getEntityCMP<CMap>(map).map[41].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[40]);
	man_e.getEntityCMP<CMap>(map).map[41].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[12]);
	man_e.getEntityCMP<CMap>(map).map[41].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[86]);
	man_e.getEntityCMP<CMap>(map).map[41].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[85]);

	man_e.getEntityCMP<CMap>(map).map[42].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[20]);
	man_e.getEntityCMP<CMap>(map).map[42].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[43]);
	man_e.getEntityCMP<CMap>(map).map[42].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[72]);

	man_e.getEntityCMP<CMap>(map).map[43].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[42]);
	man_e.getEntityCMP<CMap>(map).map[43].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[44]);
	man_e.getEntityCMP<CMap>(map).map[43].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[73]);

	man_e.getEntityCMP<CMap>(map).map[44].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[24]);
	man_e.getEntityCMP<CMap>(map).map[44].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[43]);
	man_e.getEntityCMP<CMap>(map).map[44].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[74]);
	man_e.getEntityCMP<CMap>(map).map[44].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[66]);
}
// 	LUCES

	auto& luz1 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.addTagToEntity<TLantern>(luz1);
	man_e.defineCMP<CPhysics>(luz1,  CPhysics{.x=-0.11, .y=2.42, .z=-1.24});
	man_e.defineCMP<CPointLight>(luz1, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(luz1).setOff();

	auto& luz2 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.addTagToEntity<TLantern>(luz2);
	man_e.defineCMP<CPhysics>(luz2,  CPhysics{.x=-0.11, .y=2.42, .z=-5.07});
	man_e.defineCMP<CPointLight>(luz2, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(luz2).setOff();

	auto& luz3 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.addTagToEntity<TLantern>(luz3);
	man_e.defineCMP<CPhysics>(luz3,  CPhysics{.x=16.28, .y=2.42, .z=-10.57});
	man_e.defineCMP<CPointLight>(luz3, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(luz3).setOff();

	auto& luz4 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.addTagToEntity<TLantern>(luz4);	
	man_e.defineCMP<CPhysics>(luz4,  CPhysics{.x=16.28, .y=2.42, .z=-1.18});
	man_e.defineCMP<CPointLight>(luz4, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(luz4).setOff();

	auto& luz5 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.addTagToEntity<TLantern>(luz5);	
	man_e.defineCMP<CPhysics>(luz5,  CPhysics{.x=18.36, .y=2.42, .z=3.59});
	man_e.defineCMP<CPointLight>(luz5, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(luz5).setOff();

	/*
	auto& luz6 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.addTagToEntity<TLantern>(luz6);	
	man_e.defineCMP<CPhysics>(luz6,  CPhysics{.x=48.36, .y=2.42, .z=3.59});
	man_e.defineCMP<CPointLight>(luz6, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(luz6).smallLight();

	auto& luz7 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.addTagToEntity<TLantern>(luz7);	
	man_e.defineCMP<CPhysics>(luz7,  CPhysics{.x=28.36, .y=2.42, .z=3.59});
	man_e.defineCMP<CPointLight>(luz7, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(luz7).debugLight();

	auto& luz8 = man_e.createEntity_withCMPS< CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.addTagToEntity<TLantern>(luz8);	
	man_e.defineCMP<CPhysics>(luz8,  CPhysics{.x=38.36, .y=2.42, .z=3.59});
	man_e.defineCMP<CPointLight>(luz8, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(luz8).debugLight();
	*/

	auto& tv = man_e.createEntity_withCMPS<CPhysics, CRenderGL>();
	man_e.defineCMP<CPhysics>(tv, CPhysics{.x =0.07, .y=0 , .z= -12.87});
	man_e.defineCMP<CRenderGL>(tv, CRenderGL{.modelMatrix = Model("assets/level3/tv.obj", glm::vec3(0,0,0))});
	man_e.getEntityCMP<CRenderGL>(tv).modelMatrix.Rotate(-90, 0, 1, 0);
	man_e.getEntityCMP<CRenderGL>(tv).modelMatrix.Scale(0.6, 0.6, 0.6);

	auto& yesquero = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(yesquero);
	man_e.addTagToEntity<TScaleBoundingBox>(yesquero);
	man_e.addTagToEntity<TYesqueroPermanente>(yesquero);
	man_e.addTagToEntity<Tpickable>(yesquero);
	man_e.addTagToEntity<TYesquero>(yesquero);
	man_e.addTagToEntity<TDescription>(yesquero);
	man_e.defineCMP<CPhysics>(yesquero, CPhysics{.x =15.38, .y=0 ,.z= -1.12});
	man_e.getEntityCMP<CRenderGL>(yesquero).modelMatrix.Rotate(90,0,0,1);
	man_e.defineCMP<CRenderGL>(yesquero, CRenderGL{.modelMatrix = Model("assets/level1/aceite.obj", glm::vec3(0,0,0))});
	auto& yesquero2 = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(yesquero2);
	man_e.addTagToEntity<TScaleBoundingBox>(yesquero2);
	man_e.addTagToEntity<Tpickable>(yesquero2);
	man_e.addTagToEntity<TYesquero>(yesquero2);
	man_e.addTagToEntity<TDescription>(yesquero2);
	man_e.defineCMP<CPhysics>(yesquero2, CPhysics{.x =16.28, .y=0.8 ,.z= -6.28});
	man_e.getEntityCMP<CRenderGL>(yesquero2).modelMatrix.Rotate(90,0,0,1);
	man_e.defineCMP<CRenderGL>(yesquero2, CRenderGL{.modelMatrix = Model("assets/level1/aceite.obj", glm::vec3(0,0,0))});
	auto& yesquero3 = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(yesquero3);
	man_e.addTagToEntity<TScaleBoundingBox>(yesquero3);
	man_e.addTagToEntity<Tpickable>(yesquero3);
	man_e.addTagToEntity<TYesquero>(yesquero3);
	man_e.addTagToEntity<TDescription>(yesquero3);
	man_e.defineCMP<CPhysics>(yesquero3, CPhysics{.x =0.61, .y=0.7 ,.z= -10.97});
	man_e.getEntityCMP<CRenderGL>(yesquero3).modelMatrix.Rotate(90,0,0,1);
	man_e.defineCMP<CRenderGL>(yesquero3, CRenderGL{.modelMatrix = Model("assets/level1/aceite.obj", glm::vec3(0,0,0))});

	man_e.defineCMP<CInformation>(yesquero, CInformation{.description="Refills fuel" ,.descriptionPickable="[E] Grab"});
	man_e.defineCMP<CInformation>(yesquero2,CInformation{.description="Refills fuel" ,.descriptionPickable="[E] Grab"});
	man_e.defineCMP<CInformation>(yesquero3,CInformation{.description="Refills fuel" ,.descriptionPickable="[E] Grab"});

	man_e.defineCMP<CInformation>(light,CInformation{.description="" ,.descriptionPickable="[Q] Grab"});
	man_e.defineCMP<CInformation>(anillo,CInformation{.description="" ,.descriptionPickable="[E] Grab"});
	man_e.defineCMP<CInformation>(puerta, CInformation{.descriptionPickable = "[E] Go back"});
	man_e.defineCMP<CInformation>(puerta_salon, CInformation{.descriptionPickable = "[E] Open"});
	man_e.defineCMP<CInformation>(puerta_habitacion, CInformation{.descriptionPickable = "[E] Try to open"});
	man_e.defineCMP<CInformation>(puerta_trasera, CInformation{.type_of_text = 0, .description = "I cant't open it yet", .descriptionPickable="[E] Try to open"});
	man_e.defineCMP<CInformation>(puerta_aseo, CInformation{.descriptionPickable = "[E] Open"});
	
	man_e.defineCMP<CInformation>(caja_fuerte, CInformation{.type_of_text=0, .description{"Needs a four digit password"}, .descriptionPickable{"[E] Insert code"}});
	man_e.defineCMP<CInformation>(fusible_recogible, CInformation{.type_of_text=0, .description="Looks like a fuse, could be useful", .descriptionPickable="[E] Grab"});
	man_e.defineCMP<CInformation>(fusibles_caja, CInformation{.type_of_text=0, .description="Something is missing", .descriptionPickable="[E] Insert fuse"});
	man_e.defineCMP<CInformation>(telefono, CInformation{.type_of_text=0, .description="", .descriptionPickable="[E] Pick up"});
	man_e.defineCMP<CInformation>(cuadro, CInformation{.description="Seems like something is hidden behind", .descriptionPickable="[E] Move"});
	man_e.defineCMP<CInformation>(quemable_casa_txt,CInformation{.description= "", .descriptionPickable="[E] Burn"});
	man_e.defineCMP<CInformation>(granjero, CInformation{
		.type_of_text=2, 
		.description{"Help me end this..."}, 
		.text_list{"History repeats itself... many come, but nobody leaves", 
					"I think I hit my head in the accident", 
					"It's the damn corn... It'll eat you alive", 
					"What do you mean by that ?",  
					"Just do yourself a favour... and kill yourself... before it's too late",
					"My family... I had to do it, I had no choice",
					"Look, I just want to leave this place, I don't know what you're talking about",
					"Then why are you still here ?",
					"My car is busted! What am I supposed to do ?",
					"There's stuff in the barn's basement, might serve you well",
					"Let me know when you leave",
					"Didn't help the others though...",
					"What others ?",
					""},
		.descriptionPickable{"[E] Interact"}
	});
	std::cout << "Entities level 3 : " << man_e.getEntityArray().size() <<"\n";
}

void Levels::load_lvl_4(Manentity_type& man_e, Sys& systems, EngineGL& GL){
	clearLevel(man_e, systems, GL);
	//TUMBA
//	Todas las entidades tienen que tener fisicas para tener las posiciones y poder renderizar
	InitSoundsLvl_4(systems.soundito);
	man_e.getLevelsStatus().actual = 4;
	//--------------------------------PLAYER---------------------------------------------------//

	////////////// PLAYER -- Collision box
	//	CMPS :  CRenderGL, CPhysics, CInput, CCollision
	//	TAGS : 	TPlayer, TCollider, TNotRenderizable
	auto& player = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CInput, CCollision, CHealth, CStamina, CSound>();	
	man_e.addTagToEntity<TPlayer>(player);
	man_e.addTagToEntity<TCollider>(player);
	man_e.addTagToEntity<TNotRenderizable>(player); //HACER UN CUBE ACORDE AL PLAYER
	man_e.defineCMP<CPhysics>(player, CPhysics{.x=0, .y=1.5, .z=-4});
	man_e.defineCMP<CRenderGL>(player, CRenderGL{.modelMatrix= Model("assets/level1/cube.obj", glm::vec3(0,1.5,-3))});
	man_e.defineCMP<CSound>(player, CSound{.s_mgr = &systems.soundito, .name{"surface"}, .eventvalue = 0,});

	GL.camera.Position = { 0, 1.5, -4};
	GL.camera.Front = {0,0,-1};
	////////////// PLAYER -- Model
	//	CMPS :  CRenderGL, CPhysics
	//	TAGS : 	TPlayer
	auto& player_model = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.addTagToEntity<TPlayer>(player_model);
	man_e.addTagToEntity<TNotRenderizable>(player_model);
	//man_e.defineCMP<CPhysics>(player_model, CPhysics{.x=4, .z= -4});
	man_e.defineCMP<CRenderGL>(player_model, CRenderGL{.modelMatrix= Model("assets/level1/brazo.obj", glm::vec3(0.7, -0.5, -2))}); 
	man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Scale(1.6,2,2);
	//man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Rotate(0, 0,1,0);
	////////////// PLAYER -- Model Candil with light
	//	CMPS :  CRenderGL, CPhysics, CPointLight
	//	TAGS : 	TPlayer
	auto& light = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CPointLight, CHealth, CSound, CCollision>(); //MIRAR BIEN
	//man_e.addTagToEntity<TPlayer>(light);
	man_e.addTagToEntity<TLantern>(light);
	man_e.addTagToEntity<TCollisionable>(light);
	man_e.addTagToEntity<Tpickable>(light);
	man_e.addTagToEntity<TScaleBoundingBox>(light);
	//man_e.addTagToEntity<TNotRenderizable>(light);
	man_e.defineCMP<CPhysics>(light,  CPhysics{.x=0.8, .y=0, .z=-45.5});
	man_e.defineCMP<CRenderGL>(light, CRenderGL{.modelMatrix = Model("assets/level1/Candil.obj", glm::vec3(0.8, -0.7, 0))});
	man_e.defineCMP<CSound>(light, CSound{.s_mgr= &systems.soundito}); 
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Scale(5,6,5);
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Rotate(90, 0,1,0);
	man_e.defineCMP<CPointLight>(light, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(light).setOff();

	auto& escenario = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.defineCMP<CRenderGL>(escenario, CRenderGL{ .modelMatrix = Model("assets/level4/level4.obj", glm::vec3(0,0,0))});

	auto& casa = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.defineCMP<CRenderGL>(casa, CRenderGL{ .modelMatrix = Model("assets/level2/casa.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CPhysics>(casa,  CPhysics{.x=5.25, .y=0, .z=62.07});
	
	auto& event = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(event);
	man_e.addTagToEntity<TDescription>(event);
	man_e.addTagToEntity<TCollisionable>(event);
	//man_e.addTagToEntity<TEnemyEvent>(event);
	man_e.defineCMP<CPhysics>(event, CPhysics{.x= 0 , .y =0, .z = -24});
	man_e.defineCMP<CRenderGL>(event, CRenderGL{.modelMatrix = Model("assets/level4/cajanueva.obj", glm::vec3(0,0,0))});

	auto& tumba = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(tumba );
	man_e.addTagToEntity<TWall>(tumba );
	man_e.defineCMP<CPhysics>(tumba , CPhysics{.x= -0.07 , .y = 0.42, .z = -30.89});
	man_e.defineCMP<CRenderGL>(tumba , CRenderGL{.modelMatrix = Model("assets/level4/Tombn.obj", glm::vec3(0,0,0))});
	auto& txt_tumba = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CReference>();
	man_e.addTagToEntity<TCollisionable>(txt_tumba );
	man_e.addTagToEntity<TNotRenderizable>(txt_tumba );
	man_e.addTagToEntity<TScaleBoundingBox>(txt_tumba);
	man_e.addTagToEntity<TTombEvent>(txt_tumba);
	man_e.addTagToEntity<TDescription>(txt_tumba );
	man_e.defineCMP<CReference>(txt_tumba, CReference{.id_reference = event.getID()});
	man_e.defineCMP<CPhysics>(txt_tumba , CPhysics{.x= -0.07 , .y = 0.42, .z = -29.89});
	man_e.defineCMP<CRenderGL>(txt_tumba , CRenderGL{.modelMatrix = Model("assets/level1/cube.obj", glm::vec3(0,0,0))});

	auto& marco_foto = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CPng>();
	man_e.addTagToEntity<TDescription>(marco_foto );
	man_e.addTagToEntity<TCollisionable>(marco_foto );
	man_e.addTagToEntity<TScaleBoundingBox>(marco_foto);
	man_e.addTagToEntity<Tpickable>(marco_foto);
	man_e.addTagToEntity<TMarco>(marco_foto);
	man_e.defineCMP<CPhysics>(marco_foto , CPhysics{.x = 2.45, .y = 0, .z = -28});
	man_e.defineCMP<CPng>(marco_foto , CPng{.icono = Model("assets/level4/marco_Tumba.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CRenderGL>(marco_foto , CRenderGL{.modelMatrix = Model("assets/level4/marco_Tumba.obj", glm::vec3(0,0,0))});
	man_e.getEntityCMP<CRenderGL>(marco_foto).modelMatrix.Scale(2,2,2);

	//ENEMIGOS
	for (uint8_t i = 0; i < 6; ++i){

		auto& enemy = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound, CAnimation>();
		man_e.addTagToEntity<TEnemy>(enemy);
		man_e.addTagToEntity<TDummy>(enemy);
		man_e.addTagToEntity<TNotPatrol>(enemy);
		man_e.addTagToEntity<TNotRenderizable>(enemy);
		man_e.defineCMP<CIA>(enemy, CIA{.dt = &systems.dtree});
		man_e.defineCMP<CSound>(enemy, CSound{.s_mgr = &systems.soundito});
		man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
		man_e.getEntityCMP<CAnimation>(enemy).animation  = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix);
		man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(180,0,1,0);
		man_e.getEntityCMP<CAnimation>(enemy).animator   = Animator(&man_e.getEntityCMP<CAnimation>(enemy).animation);
		man_e.getEntityCMP<CAnimation>(enemy).animator.setCurrentTime(man_e.getEntityCMP<CAnimation>(enemy).animation.GetDuration());
		
		//man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Scale(0.5,0.5,0.5);
		man_e.getEntityCMP<CIA>(enemy).origin = man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.nodeMatrix;
		if (i==0){
			man_e.defineCMP<CPhysics>(enemy, CPhysics{.x = 10, .y = 0, .z = -15});//derecha
			//man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(180,0,1,0);
		}else if (i==1){
			man_e.defineCMP<CPhysics>(enemy, CPhysics{.x = -10, .y = 0, .z = -15});//izquierda 
			man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(180,0,1,0);
		}else if (i==2){
			man_e.defineCMP<CPhysics>(enemy, CPhysics{.x = -5, .y = 0, .z = -30.89}); // primero izd
			man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(140,0,1,0);
		//	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(180,0,1,0);
		}else if (i==3){
			man_e.defineCMP<CPhysics>(enemy, CPhysics{.x = -2, .y = 0, .z = -32}); // segundo
			man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(110,0,1,0);

		//	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(90,0,1,0);
		//	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(180,0,1,0);
		}else if (i==4){
			man_e.defineCMP<CPhysics>(enemy, CPhysics{.x = 2, .y = 0, .z = -32}); //tercero
			man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(85,0,1,0);

		//	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(90,0,1,0);
		//	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(180,0,1,0);
		}else if (i==5){
			man_e.defineCMP<CPhysics>(enemy, CPhysics{.x = 5, .y = 0, .z = -30.89}); // cuarto
			man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(70,0,1,0);

		//	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(25,0,1,0);
		//	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(180,0,1,0);
		}
	}
	//man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(10,0,1,0);

	{//COLLISIONS LVL 4

		auto& Colilvl4_01 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_01 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_01 );
		man_e.addTagToEntity<TWall>(Colilvl4_01 );
		man_e.defineCMP<CPhysics>(Colilvl4_01 , CPhysics{.x= -3.3646833896636963 , .y = 0.005483582615852356, .z = 3.754791736602783});
		man_e.defineCMP<CRenderGL>(Colilvl4_01 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_01.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_18 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_18 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_18 );
		man_e.addTagToEntity<TWall>(Colilvl4_18 );
		man_e.defineCMP<CPhysics>(Colilvl4_18 , CPhysics{.x= 3.3646833896636963 , .y = 0.005483582615852356, .z = 3.754791736602783});
		man_e.defineCMP<CRenderGL>(Colilvl4_18 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_18.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_17 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_17 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_17 );
		man_e.addTagToEntity<TWall>(Colilvl4_17 );
		man_e.defineCMP<CPhysics>(Colilvl4_17 , CPhysics{.x= 10.581685066223145 , .y = 0.005483582615852356, .z = -7.168239116668701});
		man_e.defineCMP<CRenderGL>(Colilvl4_17 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_17.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_02 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_02 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_02 );
		man_e.addTagToEntity<TWall>(Colilvl4_02 );
		man_e.defineCMP<CPhysics>(Colilvl4_02 , CPhysics{.x= -10.679211616516113 , .y = 0.005483582615852356, .z = -7.168239116668701});
		man_e.defineCMP<CRenderGL>(Colilvl4_02 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_02.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_16 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_16 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_16 );
		man_e.addTagToEntity<TWall>(Colilvl4_16 );
		man_e.defineCMP<CPhysics>(Colilvl4_16 , CPhysics{.x= 18.237558364868164 , .y = 0.005483582615852356, .z = -13.758806228637695});
		man_e.defineCMP<CRenderGL>(Colilvl4_16 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_16.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_15 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_15 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_15 );
		man_e.addTagToEntity<TWall>(Colilvl4_15 );
		man_e.defineCMP<CPhysics>(Colilvl4_15 , CPhysics{.x= 15.753433227539062 , .y = 0.005483582615852356, .z = -20.236865997314453});
		man_e.defineCMP<CRenderGL>(Colilvl4_15 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_15.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_14 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_14 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_14 );
		man_e.addTagToEntity<TWall>(Colilvl4_14 );
		man_e.defineCMP<CPhysics>(Colilvl4_14 , CPhysics{.x= 13.263679504394531 , .y = 0.005483582615852356, .z = -23.79696273803711});
		man_e.defineCMP<CRenderGL>(Colilvl4_14 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_14.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_05 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_05 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_05 );
		man_e.addTagToEntity<TWall>(Colilvl4_05 );
		man_e.defineCMP<CPhysics>(Colilvl4_05 , CPhysics{.x= -13.214914321899414 , .y = 0.005483582615852356, .z = -23.79696273803711});
		man_e.defineCMP<CRenderGL>(Colilvl4_05 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_05.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_03 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_03 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_03 );
		man_e.addTagToEntity<TWall>(Colilvl4_03 );
		man_e.defineCMP<CPhysics>(Colilvl4_03 , CPhysics{.x= -18.18879508972168 , .y = 0.005483582615852356, .z = -13.758806228637695});
		man_e.defineCMP<CRenderGL>(Colilvl4_03 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_03.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_04 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_04 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_04 );
		man_e.addTagToEntity<TWall>(Colilvl4_04 );
		man_e.defineCMP<CPhysics>(Colilvl4_04 , CPhysics{.x= -15.796566009521484 , .y = 0.005483582615852356, .z = -20.236865997314453});
		man_e.defineCMP<CRenderGL>(Colilvl4_04 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_04.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_10 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_10 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_10 );
		man_e.addTagToEntity<TWall>(Colilvl4_10 );
		man_e.defineCMP<CPhysics>(Colilvl4_10 , CPhysics{.x= -0.04859352111816406 , .y = 0.005483582615852356, .z = -37.304100036621094});
		man_e.defineCMP<CRenderGL>(Colilvl4_10 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_10.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_12 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_12 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_12 );
		man_e.addTagToEntity<TWall>(Colilvl4_12 );
		man_e.defineCMP<CPhysics>(Colilvl4_12 , CPhysics{.x= 10.630449295043945 , .y = 0.005483582615852356, .z = -31.176849365234375});
		man_e.defineCMP<CRenderGL>(Colilvl4_12 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_12.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_07 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_07 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_07 );
		man_e.addTagToEntity<TWall>(Colilvl4_07 );
		man_e.defineCMP<CPhysics>(Colilvl4_07 , CPhysics{.x= -10.651857376098633 , .y = 0.005483582615852356, .z = -31.176849365234375});
		man_e.defineCMP<CRenderGL>(Colilvl4_07 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_07.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_13 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_13 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_13 );
		man_e.addTagToEntity<TWall>(Colilvl4_13 );
		man_e.defineCMP<CPhysics>(Colilvl4_13 , CPhysics{.x= 11.704373359680176 , .y = 0.005483582615852356, .z = -27.434362411499023});
		man_e.defineCMP<CRenderGL>(Colilvl4_13 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_13.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_06 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_06 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_06 );
		man_e.addTagToEntity<TWall>(Colilvl4_06 );
		man_e.defineCMP<CPhysics>(Colilvl4_06 , CPhysics{.x= -11.744196891784668 , .y = 0.005483582615852356, .z = -27.434362411499023});
		man_e.defineCMP<CRenderGL>(Colilvl4_06 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_06.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_11 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_11 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_11 );
		man_e.addTagToEntity<TWall>(Colilvl4_11 );
		man_e.defineCMP<CPhysics>(Colilvl4_11 , CPhysics{.x= 7.851934432983398 , .y = 0.005483582615852356, .z = -34.79819869995117});
		man_e.defineCMP<CRenderGL>(Colilvl4_11 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_11.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_08 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_08 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_08 );
		man_e.addTagToEntity<TWall>(Colilvl4_08 );
		man_e.defineCMP<CPhysics>(Colilvl4_08 , CPhysics{.x= -8.120380401611328 , .y = 0.005483582615852356, .z = -34.79819869995117});
		man_e.defineCMP<CRenderGL>(Colilvl4_08 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_08.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_09 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_09 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_09 );
		man_e.addTagToEntity<TWall>(Colilvl4_09 );
		man_e.defineCMP<CPhysics>(Colilvl4_09 , CPhysics{.x= -5.518178939819336 , .y = 0.005483582615852356, .z = -35.93540573120117});
		man_e.defineCMP<CRenderGL>(Colilvl4_09 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_09.obj", glm::vec3(0,0,0))});
		auto& Colilvl4_19 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl4_19 );
		man_e.addTagToEntity<TCollisionable>(Colilvl4_19 );
		man_e.addTagToEntity<TWall>(Colilvl4_19 );
		man_e.defineCMP<CPhysics>(Colilvl4_19 , CPhysics{.x= 5.318161964416504 , .y = 0.005483582615852356, .z = -35.93540573120117});
		man_e.defineCMP<CRenderGL>(Colilvl4_19 , CRenderGL{.modelMatrix = Model("assets/level4/Colilvl4_11.001.obj", glm::vec3(0,0,0))});
	}
	
	auto& Transitionlvl4toMaze = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CIDLvl>();
	man_e.addTagToEntity<TNotRenderizable>(Transitionlvl4toMaze );
	man_e.addTagToEntity<TCollisionable>(Transitionlvl4toMaze );
	man_e.addTagToEntity<TTransition>(Transitionlvl4toMaze);
	man_e.defineCMP<CPhysics>(Transitionlvl4toMaze , CPhysics{.x= 0.0 , .y = 0.04087495803833008, .z = 11.33956527709961});
	man_e.defineCMP<CRenderGL>(Transitionlvl4toMaze , CRenderGL{.modelMatrix = Model("assets/level4/Transitionlvl4to2.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CIDLvl>(Transitionlvl4toMaze , CIDLvl{.lvlid = 2});  

	auto& valla_pico = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(valla_pico);
	man_e.addTagToEntity<TNotRenderizable>(valla_pico);
	man_e.defineCMP<CRenderGL>(valla_pico, CRenderGL{.modelMatrix= Model("assets/level5/Valla_pico2.obj", glm::vec3(0,0,0)),.amount=0, .instancePath="assets/level4/Valla4_picos.txt"});
	////////////////INSTANCIA VALLA MADERAS HORIZONTALES
	//	CMPS:  CRenderGL, CPhysics
	//  TAGS: TInstance, TNotRenderizable
	auto& valla_tablones = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(valla_tablones);
	man_e.addTagToEntity<TNotRenderizable>(valla_tablones);
	man_e.defineCMP<CRenderGL>(valla_tablones, CRenderGL{.modelMatrix= Model("assets/level5/Valla_tablones2.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/level4/Valla4_tablones.txt"});
	
	auto& maiz = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(maiz);
	man_e.addTagToEntity<TNotRenderizable>(maiz);
	man_e.defineCMP<CRenderGL>(maiz, CRenderGL{.modelMatrix= Model("assets/level1/CornLP.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/level4/instances_maiz4.txt",.iscorn=true});
	
	auto& cartel_hub = man_e.createEntity_withCMPS< CRenderGL, CPhysics, CCollision, CInformation>();
	man_e.addTagToEntity<TCollisionable>(cartel_hub);
	man_e.addTagToEntity<TWall>(cartel_hub);
	man_e.addTagToEntity<TDescription>(cartel_hub);
	man_e.defineCMP<CRenderGL>(cartel_hub, CRenderGL{ .modelMatrix = Model("assets/level1/Cartel_Der.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(cartel_hub, CPhysics{.x = 2.82, .y = 0, .z = -5.03});
	man_e.getEntityCMP<CRenderGL>(cartel_hub).modelMatrix.Rotate(-90, 0, 1, 0);

	auto& Coli4_deco = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Coli4_deco );
	man_e.addTagToEntity<TCollisionable>(Coli4_deco );
	man_e.addTagToEntity<TWall>(Coli4_deco );
	man_e.defineCMP<CPhysics>(Coli4_deco , CPhysics{.x= -11.942499160766602 , .y = 0.49542978405952454, .z = -11.779029846191406});
	man_e.defineCMP<CRenderGL>(Coli4_deco , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& Coli4_deco2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Coli4_deco2 );
	man_e.addTagToEntity<TCollisionable>(Coli4_deco2 );
	man_e.addTagToEntity<TWall>(Coli4_deco2 );
	man_e.defineCMP<CPhysics>(Coli4_deco2 , CPhysics{.x= 5.535165786743164 , .y = 0.49542978405952454, .z = -21.550006866455078});
	man_e.defineCMP<CRenderGL>(Coli4_deco2 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& Coli4_deco3 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(Coli4_deco3 );
	man_e.addTagToEntity<TCollisionable>(Coli4_deco3 );
	man_e.addTagToEntity<TWall>(Coli4_deco3 );
	man_e.defineCMP<CPhysics>(Coli4_deco3 , CPhysics{.x= 15.050317764282227 , .y = 0.49542978405952454, .z = -11.773526191711426});
	man_e.defineCMP<CRenderGL>(Coli4_deco3 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	//DESCRIPTIONS
	man_e.defineCMP<CInformation>(light,CInformation{.description="" ,.descriptionPickable="[Q] Grab"});
	man_e.defineCMP<CInformation>(event,CInformation{.type_of_text=3, .description="Damn, they're everywhere", .times_to_print_text=80});
	man_e.defineCMP<CInformation>(txt_tumba, CInformation{.type_of_text=2, .description{"She died in 1986..."} ,.text_list{"So she died in 1986...", "it may be useful later","In 1986...",""}, .descriptionPickable{"[E] Next"}});
	man_e.defineCMP<CInformation>(marco_foto, CInformation{.type_of_text=0, .description{"There's something written behind"}, .descriptionPickable{"[E] Grab"}});
	man_e.defineCMP<CInformation>(cartel_hub, CInformation{.type_of_text=0, .description{"To the house"}});

	std::cout << "Entities level 4 : " << man_e.getEntityArray().size() <<"\n";
}

void Levels::load_lvl_5(Manentity_type& man_e, Sys& systems, EngineGL& GL){
	//GRANERO
//	Todas las entidades tienen que tener fisicas para tener las posiciones y poder renderizar
	InitSoundsLvl_5(systems.soundito);
	man_e.getLevelsStatus().actual = 5;
	//--------------------------------PLAYER---------------------------------------------------//

	////////////// PLAYER -- Collision box
	//	CMPS :  CRenderGL, CPhysics, CInput, CCollision
	//	TAGS : 	TPlayer, TCollider, TNotRenderizable
	auto& player = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CInput, CCollision, CHealth, CStamina, CSound>();	
	man_e.addTagToEntity<TPlayer>(player);
	man_e.addTagToEntity<TCollider>(player);
	man_e.addTagToEntity<TNotRenderizable>(player); //HACER UN CUBE ACORDE AL PLAYER
	man_e.defineCMP<CPhysics>(player, CPhysics{.x=0, .y=1.5, .z=-4});
	man_e.defineCMP<CRenderGL>(player, CRenderGL{.modelMatrix= Model("assets/level1/cube.obj", glm::vec3(0,1.5,-3))});
	man_e.defineCMP<CSound>(player, CSound{.s_mgr = &systems.soundito, .name{"surface"}, .eventvalue = 0,});

	GL.camera.Position = { 0, 1.5, -4};
	////////////// PLAYER -- Model
	//	CMPS :  CRenderGL, CPhysics
	//	TAGS : 	TPlayer
	auto& player_model = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.addTagToEntity<TPlayer>(player_model);
	man_e.addTagToEntity<TNotRenderizable>(player_model);
	//man_e.defineCMP<CPhysics>(player_model, CPhysics{.x=4, .z= -4});
	man_e.defineCMP<CRenderGL>(player_model, CRenderGL{.modelMatrix= Model("assets/level1/brazo.obj", glm::vec3(0.7, -0.5, -2))}); 
	man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Scale(1.6,2,2);
	//man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Rotate(0, 0,1,0);
	////////////// PLAYER -- Model Candil with light
	//	CMPS :  CRenderGL, CPhysics, CPointLight
	//	TAGS : 	TPlayer
	auto& light = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CPointLight, CHealth, CSound, CCollision>(); //MIRAR BIEN
	//man_e.addTagToEntity<TPlayer>(light);
	man_e.addTagToEntity<TLantern>(light);
	man_e.addTagToEntity<TCollisionable>(light);
	man_e.addTagToEntity<Tpickable>(light);
	man_e.addTagToEntity<TScaleBoundingBox>(light);
	//man_e.addTagToEntity<TNotRenderizable>(light);
	man_e.defineCMP<CPhysics>(light,  CPhysics{.x=0.8, .y=0, .z=-6.5});
	man_e.defineCMP<CRenderGL>(light, CRenderGL{.modelMatrix = Model("assets/level1/Candil.obj", glm::vec3(0.8, -0.7, 0))});
	man_e.defineCMP<CSound>(light, CSound{.s_mgr= &systems.soundito}); 
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Scale(5,6,5);
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Rotate(90, 0,1,0);
	man_e.defineCMP<CPointLight>(light, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(light).setOff();

	auto& escenario = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.defineCMP<CRenderGL>(escenario, CRenderGL{ .modelMatrix = Model("assets/level5/lv5.obj", glm::vec3(0,-1.5,0))});

	auto& puerta_granero1 = man_e.createEntity_withCMPS< CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(puerta_granero1); 
	man_e.addTagToEntity<TWall>(puerta_granero1);
	man_e.defineCMP<CPhysics>(puerta_granero1,  CPhysics{.x= 3, .y = 0, .z = -23.6});
	man_e.defineCMP<CRenderGL>(puerta_granero1, CRenderGL{ .modelMatrix = Model("assets/level5/Puerta_Granero.obj", glm::vec3(0,-1.5,0))});
	auto& puerta_granero2 = man_e.createEntity_withCMPS< CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(puerta_granero2); 
	man_e.addTagToEntity<TWall>(puerta_granero2);
	man_e.defineCMP<CPhysics>(puerta_granero2,  CPhysics{.x= 6.41, .y = 0, .z = -23.6});
	man_e.defineCMP<CRenderGL>(puerta_granero2, CRenderGL{ .modelMatrix = Model("assets/level5/Puerta_Granero.obj", glm::vec3(0,-1.5,0))});
	auto& puerta_collision = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CSound>();
	man_e.addTagToEntity<TDescription>(puerta_collision);
	man_e.addTagToEntity<TCollisionable>(puerta_collision);
	man_e.addTagToEntity<TDoor>(puerta_collision);
	man_e.addTagToEntity<TNotRenderizable>(puerta_collision);
	man_e.defineCMP<CPhysics>(puerta_collision,  CPhysics{.x= 5, .y = 0, .z = -23.6});
	man_e.defineCMP<CRenderGL>(puerta_collision, CRenderGL{ .modelMatrix = Model("assets/level1/caja1.obj", glm::vec3(0,-1.5,0))});
	man_e.defineCMP<CSound>(puerta_collision, CSound{.s_mgr= &systems.soundito});

	auto& Transitionlvl5to2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CIDLvl>();
	man_e.addTagToEntity<TNotRenderizable>(Transitionlvl5to2 );
	man_e.addTagToEntity<TCollisionable>(Transitionlvl5to2 );
	man_e.addTagToEntity<TTransition>(Transitionlvl5to2 );
	man_e.defineCMP<CPhysics>(Transitionlvl5to2 , CPhysics{.x= 0.42177677154541016 , .y = 0.6210246086120605, .z = 12.256818771362305});
	man_e.defineCMP<CRenderGL>(Transitionlvl5to2 , CRenderGL{.modelMatrix = Model("assets/level5/Transitionlvl5to2.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CIDLvl>(Transitionlvl5to2, CIDLvl{.lvlid = 2});

	auto& trampilla = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CIDLvl, CSound>();
	man_e.addTagToEntity<TDescription>(trampilla);
	man_e.addTagToEntity<TCollisionable>(trampilla);
	man_e.addTagToEntity<TScaleBoundingBox>(trampilla);
	man_e.addTagToEntity<THatch>(trampilla); 
	man_e.defineCMP<CSound>(trampilla, CSound{.s_mgr= &systems.soundito});
	man_e.defineCMP<CPhysics>(trampilla, CPhysics{.x = 4.59, .y = 0.13, .z = -53.41});
	man_e.defineCMP<CRenderGL>(trampilla , CRenderGL{.modelMatrix = Model("assets/level5/TrampillaMain.obj", glm::vec3(0,0,0))});
	auto& trampilla_izd = man_e.createEntity_withCMPS<CRenderGL, CPhysics>(); 
	man_e.defineCMP<CPhysics>(trampilla_izd, CPhysics{.x = 3.92, .y = 0.31, .z = -53.41});
	man_e.defineCMP<CRenderGL>(trampilla_izd , CRenderGL{.modelMatrix = Model("assets/level5/TrampillaPIzquierda.obj", glm::vec3(0,0,0))});
	auto& trampilla_der = man_e.createEntity_withCMPS<CRenderGL, CPhysics>(); 
	man_e.defineCMP<CPhysics>(trampilla_der, CPhysics{.x = 5.26, .y = 0.31, .z = -53.41});
	man_e.defineCMP<CRenderGL>(trampilla_der , CRenderGL{.modelMatrix = Model("assets/level5/TrampillaPDerecha.obj", glm::vec3(0,0,0))});
	auto& colchon = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();
	man_e.defineCMP<CPhysics>(colchon, CPhysics{.x = -5.30, .y = 0.12, .z = -35.56});
	man_e.defineCMP<CRenderGL>(colchon , CRenderGL{.modelMatrix = Model("assets/level5/colchon.obj", glm::vec3(0,0,0))});

	auto& libro = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();
	man_e.defineCMP<CPhysics>(libro, CPhysics{.x = -4.82, .y = 0.84, .z = -38.08});
	man_e.defineCMP<CRenderGL>(libro , CRenderGL{.modelMatrix = Model("assets/level5/libro.obj", glm::vec3(0,0,0))});
	
	auto& caja_granero = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(caja_granero);
	man_e.addTagToEntity<TWall>(caja_granero);
	man_e.defineCMP<CPhysics>(caja_granero, CPhysics{.x = -4.89, .y = 0.39, .z = -38.28});
	man_e.defineCMP<CRenderGL>(caja_granero , CRenderGL{.modelMatrix = Model("assets/Sotano/Caja.obj", glm::vec3(0,0,0))});
	
	auto& cizalla = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CPng>();
	man_e.addTagToEntity<TCollisionable>(cizalla);
	man_e.addTagToEntity<TDescription>(cizalla);
	man_e.addTagToEntity<TShears>(cizalla);
	man_e.addTagToEntity<Tpickable>(cizalla);
	man_e.addTagToEntity<TScaleBoundingBox>(cizalla);
	man_e.defineCMP<CPng>(cizalla, CPng{.icono = Model("assets/level5/Cizallas.obj", glm::vec3(0,0,0))});
	man_e.getEntityCMP<CPng>(cizalla).icono.Scale(0.5,0.5,0.5);
	man_e.getEntityCMP<CPng>(cizalla).icono.Rotate(90,1,0,1);
	man_e.defineCMP<CPhysics>(cizalla, CPhysics{.x = 15.03, .y = 1.13, .z = -41.06});
	man_e.defineCMP<CRenderGL>(cizalla , CRenderGL{.modelMatrix = Model("assets/level5/Cizallas.obj", glm::vec3(0,0,0))});
	auto& banco_trabajo = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(banco_trabajo);
	man_e.addTagToEntity<TWall>(banco_trabajo);
	man_e.defineCMP<CPhysics>(banco_trabajo, CPhysics{.x = 15.37, .y = 0.99, .z = -41.50});
	man_e.defineCMP<CRenderGL>(banco_trabajo , CRenderGL{.modelMatrix = Model("assets/level5/banco_trabajo.obj", glm::vec3(0,0,0))});
		
	{//COLISIONES DE LAS VALLAS

		auto& Colilvl5_1 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_1 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_1 );
		man_e.addTagToEntity<TWall>(Colilvl5_1 );
		man_e.defineCMP<CPhysics>(Colilvl5_1 , CPhysics{.x= -2.4831888675689697 , .y = -2.562999725341797e-06, .z = 3.8704166412353516});
		man_e.defineCMP<CRenderGL>(Colilvl5_1 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_1.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_7 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_7 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_7 );
		man_e.addTagToEntity<TWall>(Colilvl5_7 );
		man_e.defineCMP<CPhysics>(Colilvl5_7 , CPhysics{.x= 3.1837356090545654 , .y = -2.562999725341797e-06, .z = 1.9814417362213135});
		man_e.defineCMP<CRenderGL>(Colilvl5_7 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_7.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_2 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_2 );
		man_e.addTagToEntity<TWall>(Colilvl5_2 );
		man_e.defineCMP<CPhysics>(Colilvl5_2 , CPhysics{.x= -6.729178428649902 , .y = -2.562999725341797e-06, .z = -3.172745943069458});
		man_e.defineCMP<CRenderGL>(Colilvl5_2 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_2.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_3 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_3 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_3 );
		man_e.addTagToEntity<TWall>(Colilvl5_3 );
		man_e.defineCMP<CPhysics>(Colilvl5_3 , CPhysics{.x= -11.234623908996582 , .y = -2.562999725341797e-06, .z = -6.436895847320557});
		man_e.defineCMP<CRenderGL>(Colilvl5_3 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_3.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_4 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_4 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_4 );
		man_e.addTagToEntity<TWall>(Colilvl5_4 );
		man_e.defineCMP<CPhysics>(Colilvl5_4 , CPhysics{.x= -12.705789566040039 , .y = -2.562999725341797e-06, .z = -9.28727912902832});
		man_e.defineCMP<CRenderGL>(Colilvl5_4 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_4.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_5 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_5 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_5 );
		man_e.addTagToEntity<TWall>(Colilvl5_5 );
		man_e.defineCMP<CPhysics>(Colilvl5_5 , CPhysics{.x= -14.284517288208008 , .y = -2.562999725341797e-06, .z = -22.79578971862793});
		man_e.defineCMP<CRenderGL>(Colilvl5_5 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_5.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_6 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_6 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_6 );
		man_e.addTagToEntity<TWall>(Colilvl5_6 );
		man_e.defineCMP<CPhysics>(Colilvl5_6 , CPhysics{.x= -10.856833457946777 , .y = -2.562999725341797e-06, .z = -36.028785705566406});
		man_e.defineCMP<CRenderGL>(Colilvl5_6 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_6.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_10 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_10 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_10 );
		man_e.addTagToEntity<TWall>(Colilvl5_10 );
		man_e.defineCMP<CPhysics>(Colilvl5_10 , CPhysics{.x= 1.3446476459503174 , .y = -2.562999725341797e-06, .z = -9.345913887023926});
		man_e.defineCMP<CRenderGL>(Colilvl5_10 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_10.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_8 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_8 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_8 );
		man_e.addTagToEntity<TWall>(Colilvl5_8 );
		man_e.defineCMP<CPhysics>(Colilvl5_8 , CPhysics{.x= -1.4222840070724487 , .y = -2.562999725341797e-06, .z = -6.808659076690674});
		man_e.defineCMP<CRenderGL>(Colilvl5_8 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_8.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_11 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_11 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_11 );
		man_e.addTagToEntity<TWall>(Colilvl5_11 );
		man_e.defineCMP<CPhysics>(Colilvl5_11 , CPhysics{.x= 9.022424697875977 , .y = -2.562999725341797e-06, .z = -12.316452026367188});
		man_e.defineCMP<CRenderGL>(Colilvl5_11 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_11.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_9 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_9 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_9 );
		man_e.addTagToEntity<TWall>(Colilvl5_9 );
		man_e.defineCMP<CPhysics>(Colilvl5_9 , CPhysics{.x= -5.689233779907227 , .y = -2.562999725341797e-06, .z = -8.0868501663208});
		man_e.defineCMP<CRenderGL>(Colilvl5_9 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_9.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_12 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_12 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_12 );
		man_e.addTagToEntity<TWall>(Colilvl5_12 );
		man_e.defineCMP<CPhysics>(Colilvl5_12 , CPhysics{.x= 17.93233871459961 , .y = -2.562999725341797e-06, .z = -15.161138534545898});
		man_e.defineCMP<CRenderGL>(Colilvl5_12 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_12.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_13 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_13 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_13 );
		man_e.addTagToEntity<TWall>(Colilvl5_13 );
		man_e.defineCMP<CPhysics>(Colilvl5_13 , CPhysics{.x= 26.16339683532715 , .y = -2.562999725341797e-06, .z = -23.75623893737793});
		man_e.defineCMP<CRenderGL>(Colilvl5_13 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_13.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_14 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_14 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_14 );
		man_e.addTagToEntity<TWall>(Colilvl5_14 );
		man_e.defineCMP<CPhysics>(Colilvl5_14 , CPhysics{.x= -7.245948314666748 , .y = 0.6747881770133972, .z = -41.45564270019531});
		man_e.defineCMP<CRenderGL>(Colilvl5_14 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_14.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_16 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_16 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_16 );
		man_e.addTagToEntity<TWall>(Colilvl5_16 );
		man_e.defineCMP<CPhysics>(Colilvl5_16 , CPhysics{.x= 4.7269287109375 , .y = 0.6747881770133972, .z = -59.172977447509766});
		man_e.defineCMP<CRenderGL>(Colilvl5_16 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_16.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_19 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_19 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_19 );
		man_e.addTagToEntity<TWall>(Colilvl5_19 );
		man_e.defineCMP<CPhysics>(Colilvl5_19 , CPhysics{.x= 16.632465362548828 , .y = 0.6747881770133972, .z = -41.50042724609375});
		man_e.defineCMP<CRenderGL>(Colilvl5_19 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_19.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_17 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_17 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_17 );
		man_e.addTagToEntity<TWall>(Colilvl5_17 );
		man_e.defineCMP<CPhysics>(Colilvl5_17 , CPhysics{.x= 12.320261001586914 , .y = 0.6747881770133972, .z = -23.89010238647461});
		man_e.defineCMP<CRenderGL>(Colilvl5_17 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_17.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_18 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_18 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_18 );
		man_e.addTagToEntity<TWall>(Colilvl5_18 );
		man_e.defineCMP<CPhysics>(Colilvl5_18 , CPhysics{.x= -2.9750447273254395 , .y = 0.6747881770133972, .z = -23.89010238647461});
		man_e.defineCMP<CRenderGL>(Colilvl5_18 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_18.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_15 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_15 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_15 );
		man_e.addTagToEntity<TWall>(Colilvl5_15 );
		man_e.defineCMP<CPhysics>(Colilvl5_15 , CPhysics{.x= 21.46672248840332 , .y = -2.562999725341797e-06, .z = -31.112424850463867});
		man_e.defineCMP<CRenderGL>(Colilvl5_15 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_15.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_20 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_20 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_20 );
		man_e.addTagToEntity<TWall>(Colilvl5_20 );
		man_e.defineCMP<CPhysics>(Colilvl5_20 , CPhysics{.x= -3.314997911453247 , .y = -2.562999725341797e-06, .z = -34.16627502441406});
		man_e.defineCMP<CRenderGL>(Colilvl5_20 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_20.obj", glm::vec3(0,0,0))});

		auto& Colilvl5_21 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(Colilvl5_21 );
		man_e.addTagToEntity<TCollisionable>(Colilvl5_21 );
		man_e.addTagToEntity<TWall>(Colilvl5_21 );
		man_e.defineCMP<CPhysics>(Colilvl5_21 , CPhysics{.x= -0.0063014160841703415 , .y = -2.562999725341797e-06, .z = -28.93134117126465});
		man_e.defineCMP<CRenderGL>(Colilvl5_21 , CRenderGL{.modelMatrix = Model("assets/level5/Colilvl5_21.obj", glm::vec3(0,0,0))});
		
		auto& ColiNewGranero = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>(); 
		man_e.addTagToEntity<TNotRenderizable>(ColiNewGranero );
		man_e.addTagToEntity<TCollisionable>(ColiNewGranero ); 
		man_e.addTagToEntity<TWall>(ColiNewGranero ); 
		man_e.defineCMP<CPhysics>(ColiNewGranero , CPhysics{.x= 4.613853454589844 , .y = 0.0, .z = -40.52289962768555}); 
		man_e.defineCMP<CRenderGL>(ColiNewGranero , CRenderGL{.modelMatrix = Model("assets/level5/ColiNewGranero.obj", glm::vec3(0,0,0))}); 
		
		auto& ColiNewGranero_001 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>(); 
		man_e.addTagToEntity<TCollisionable>(ColiNewGranero_001 ); 
		man_e.addTagToEntity<TNotRenderizable>(ColiNewGranero_001 );
		man_e.addTagToEntity<TWall>(ColiNewGranero_001 ); 
		man_e.defineCMP<CPhysics>(ColiNewGranero_001 , CPhysics{.x= 13.421558380126953 , .y = 0.0, .z = -27.024133682250977}); 
		man_e.defineCMP<CRenderGL>(ColiNewGranero_001 , CRenderGL{.modelMatrix = Model("assets/level5/ColiNewGranero_001.obj", glm::vec3(0,0,0))});
		
	}

	
	//INSTANCIAS 

	auto& valla_pico = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(valla_pico);
	man_e.addTagToEntity<TNotRenderizable>(valla_pico);
	man_e.defineCMP<CRenderGL>(valla_pico, CRenderGL{.modelMatrix= Model("assets/level5/Valla_pico2.obj", glm::vec3(0,0,0)),.amount=0, .instancePath="assets/level5/vallas5_pico.txt"});

	auto& valla_tablones = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(valla_tablones);
	man_e.addTagToEntity<TNotRenderizable>(valla_tablones);
	man_e.defineCMP<CRenderGL>(valla_tablones, CRenderGL{.modelMatrix= Model("assets/level5/Valla_tablones2.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/level5/vallas5_tablones.txt"});
	
	auto& maiz = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(maiz);
	man_e.addTagToEntity<TNotRenderizable>(maiz);
	man_e.defineCMP<CRenderGL>(maiz, CRenderGL{.modelMatrix= Model("assets/level1/CornLP.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/level5/newmaiz2.txt", .iscorn = true});

	auto& cartel_granero = man_e.createEntity_withCMPS< CRenderGL, CPhysics, CCollision, CInformation>();
	man_e.addTagToEntity<TCollisionable>(cartel_granero);
	man_e.addTagToEntity<TWall>(cartel_granero);
	man_e.defineCMP<CRenderGL>(cartel_granero, CRenderGL{ .modelMatrix = Model("assets/level1/Cartel_Izq.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(cartel_granero, CPhysics{.x = 1, .y = 0, .z = -5.62});

	auto& cartel_casa = man_e.createEntity_withCMPS< CRenderGL, CPhysics, CCollision, CInformation>();
	man_e.addTagToEntity<TCollisionable>(cartel_casa);
	man_e.addTagToEntity<TWall>(cartel_casa);
	man_e.defineCMP<CRenderGL>(cartel_casa, CRenderGL{ .modelMatrix = Model("assets/level1/Cartel_Izq.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(cartel_casa, CPhysics{.x = -1.71, .y = 0, .z = 3.65});
	man_e.getEntityCMP<CRenderGL>(cartel_casa).modelMatrix.Rotate(90, 0, 1, 0);

	auto& enemy = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound, CAnimation>();
	man_e.addTagToEntity<TEnemy>(enemy);	
	man_e.addTagToEntity<TEventDoorGranero>(enemy);
	man_e.addTagToEntity<TDummy>(enemy);
	man_e.addTagToEntity<TNotPatrol>(enemy);
	man_e.addTagToEntity<TNotRenderizable>(enemy);
	//man_e.addTagToEntity<TNotRenderAnim>(enemy);
	man_e.defineCMP<CPhysics>(enemy, CPhysics{.x= 6, .y = 0, .z = -27.6 , .vx = 0});
	man_e.defineCMP<CIA>(enemy, CIA{.dt = &systems.dtree});
	man_e.defineCMP<CSound>(enemy, CSound{.s_mgr = &systems.soundito});
	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(180,0,1,0);
	man_e.getEntityCMP<CAnimation>(enemy).animation = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix);
	man_e.getEntityCMP<CAnimation>(enemy).animator = Animator(&man_e.getEntityCMP<CAnimation>(enemy).animation);
	man_e.getEntityCMP<CIA>(enemy).origin = man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.nodeMatrix;

	auto& enemy2 = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound, CAnimation>();
	man_e.addTagToEntity<TEnemy>(enemy2);
	man_e.addTagToEntity<TDummy>(enemy2);
	man_e.addTagToEntity<TNotPatrol>(enemy2);
	man_e.addTagToEntity<TNotRenderizable>(enemy2);
	man_e.defineCMP<CPhysics>(enemy2, CPhysics{.x = -4.30, .y = 0.12, .z = -36.56 , .vx = 0});
	man_e.defineCMP<CIA>(enemy2, CIA{.dt = &systems.dtree});
	man_e.defineCMP<CSound>(enemy2, CSound{.s_mgr = &systems.soundito});
	man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
	man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix.Rotate(180,0,1,0);
	man_e.getEntityCMP<CAnimation>(enemy2).animation = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix);
	man_e.getEntityCMP<CAnimation>(enemy2).animator = Animator(&man_e.getEntityCMP<CAnimation>(enemy2).animation);
	man_e.getEntityCMP<CIA>(enemy2).origin = man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix.nodeMatrix;

	auto& yesquero = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(yesquero);
	man_e.addTagToEntity<TScaleBoundingBox>(yesquero);
	man_e.addTagToEntity<Tpickable>(yesquero);
	man_e.addTagToEntity<TYesquero>(yesquero);
	man_e.addTagToEntity<TDescription>(yesquero);
	man_e.defineCMP<CPhysics>(yesquero, CPhysics{.x =21.72, .y=0 ,.z= -26.46});
	man_e.getEntityCMP<CRenderGL>(yesquero).modelMatrix.Rotate(90,0,0,1);
	man_e.defineCMP<CRenderGL>(yesquero, CRenderGL{.modelMatrix = Model("assets/level1/aceite.obj", glm::vec3(0,0,0))});

	auto& colideco2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(colideco2 );
	man_e.addTagToEntity<TCollisionable>(colideco2 );
	man_e.addTagToEntity<TWall>(colideco2 );
	man_e.defineCMP<CPhysics>(colideco2 , CPhysics{.x= -11.979042053222656 , .y = 0.5159505009651184, .z = -11.932887077331543});
	man_e.defineCMP<CRenderGL>(colideco2 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& colideco2_001 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(colideco2_001 );
	man_e.addTagToEntity<TCollisionable>(colideco2_001 );
	man_e.addTagToEntity<TWall>(colideco2_001 );
	man_e.defineCMP<CPhysics>(colideco2_001 , CPhysics{.x= 23.079357147216797 , .y = 0.5159505009651184, .z = -18.339757919311523});
	man_e.defineCMP<CRenderGL>(colideco2_001 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& colideco2_002 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(colideco2_002 );
	man_e.addTagToEntity<TCollisionable>(colideco2_002 );
	man_e.addTagToEntity<TWall>(colideco2_002 );
	man_e.defineCMP<CPhysics>(colideco2_002 , CPhysics{.x= -10.149248123168945 , .y = 0.5159505009651184, .z = -34.38595199584961});
	man_e.defineCMP<CRenderGL>(colideco2_002 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& colideco2_003 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(colideco2_003 );
	man_e.addTagToEntity<TCollisionable>(colideco2_003 );
	man_e.addTagToEntity<TWall>(colideco2_003 );
	man_e.defineCMP<CPhysics>(colideco2_003 , CPhysics{.x= -9.201729774475098 , .y = 0.5159505009651184, .z = -33.232452392578125});
	man_e.defineCMP<CRenderGL>(colideco2_003 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});

	auto& colideco2_004 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(colideco2_004 );
	man_e.addTagToEntity<TCollisionable>(colideco2_004 );
	man_e.addTagToEntity<TWall>(colideco2_004 );
	man_e.defineCMP<CPhysics>(colideco2_004 , CPhysics{.x= -9.078140258789062 , .y = 0.5159505009651184, .z = -34.38595199584961});
	man_e.defineCMP<CRenderGL>(colideco2_004 , CRenderGL{.modelMatrix = Model("assets/level2/Colideco1_001.obj", glm::vec3(0,0,0))});
	
	auto& fuente_agua = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.defineCMP<CPhysics>(fuente_agua, CPhysics{.x =21.72, .y=0 ,.z= -25.46});
	man_e.defineCMP<CRenderGL>(fuente_agua, CRenderGL{.modelMatrix = Model("assets/level5/torre_agua.obj", glm::vec3(0,0,0))});
	man_e.getEntityCMP<CRenderGL>(fuente_agua).modelMatrix.Scale(2.5,2.7,2.5);

	//DESCRIPTIONS
	man_e.defineCMP<CInformation>(yesquero,CInformation{.description="Refills fuel" ,.descriptionPickable="[E] Grab"});
	man_e.defineCMP<CInformation>(puerta_collision, CInformation{.type_of_text=3, .description{"I can open it, but I need two hands"}, .descriptionPickable{"[E] Open"}, .times_to_print_text=0});
	man_e.defineCMP<CInformation>(light, CInformation{.type_of_text=0, .description{""}, .descriptionPickable{"[Q] Grab"}});
	man_e.defineCMP<CInformation>(cizalla, CInformation{.type_of_text=0, .description{"This can break any lock"}, .descriptionPickable{"[E] Grab"}});
	man_e.defineCMP<CInformation>(trampilla, CInformation{.type_of_text=0, .description{"I can't open with my hands"}, .descriptionPickable{"[E] Try to open"}});

	std::cout << "Entities level 5 : " << man_e.getEntityArray().size() <<"\n";
}

void Levels::load_lvl_Y(Manentity_type& man_e, Sys& systems, EngineGL& GL){

	InitSoundsLvl_Y(systems.soundito);
	man_e.getLevelsStatus().actual = 6;
	
	auto& player = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CInput, CCollision, CHealth, CStamina, CSound>();	
	man_e.addTagToEntity<TPlayer>(player);
	man_e.addTagToEntity<TCollider>(player);
	man_e.addTagToEntity<TNotRenderizable>(player); //HACER UN CUBE ACORDE AL PLAYER
	man_e.defineCMP<CPhysics>(player, CPhysics{.x=0, .y=1.5, .z=-4});
	man_e.defineCMP<CRenderGL>(player, CRenderGL{.modelMatrix= Model("assets/level1/cube.obj", glm::vec3(0,1.5,-3))});
	man_e.defineCMP<CSound>(player, CSound{.s_mgr = &systems.soundito, .name{"surface"}, .eventvalue = 0,});

	GL.camera.Position = { 0, 1.5, -4};
	////////////// PLAYER -- Model
	//	CMPS :  CRenderGL, CPhysics
	//	TAGS : 	TPlayer
	auto& player_model = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.addTagToEntity<TPlayer>(player_model);
	man_e.addTagToEntity<TNotRenderizable>(player_model);
	//man_e.defineCMP<CPhysics>(player_model, CPhysics{.x=4, .z= -4});
	man_e.defineCMP<CRenderGL>(player_model, CRenderGL{.modelMatrix= Model("assets/level1/brazo.obj", glm::vec3(0.7, -0.5, -2))}); 
	man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Scale(1.6,2,2);
	//man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Rotate(0, 0,1,0);
	////////////// PLAYER -- Model Candil with light
	//	CMPS :  CRenderGL, CPhysics, CPointLight
	//	TAGS : 	TPlayer

	auto& light = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CPointLight, CHealth, CSound, CCollision>(); //MIRAR BIEN
	//man_e.addTagToEntity<TPlayer>(light);
	man_e.addTagToEntity<TLantern>(light);
	man_e.addTagToEntity<TCollisionable>(light);
	man_e.addTagToEntity<Tpickable>(light);
	man_e.addTagToEntity<TScaleBoundingBox>(light);
	//man_e.addTagToEntity<TNotRenderizable>(light);
	man_e.defineCMP<CPhysics>(light,  CPhysics{.x=0.8, .y=0, .z=-45.5});
	man_e.defineCMP<CRenderGL>(light, CRenderGL{.modelMatrix = Model("assets/level1/Candil.obj", glm::vec3(0.8, -0.7, 0))});
	man_e.defineCMP<CSound>(light, CSound{.s_mgr= &systems.soundito}); 
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Scale(5,6,5);
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Rotate(90, 0,1,0);
	man_e.defineCMP<CPointLight>(light, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(light).setOff();

	auto& escenario = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.defineCMP<CRenderGL>(escenario, CRenderGL{ .modelMatrix = Model("assets/levelY/LevelY.obj", glm::vec3(0,-1.5,0))});
	
	//COLISIONES VALLAS
	{
		auto& VallaY3 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(VallaY3 );
		man_e.addTagToEntity<TCollisionable>(VallaY3 );
		man_e.addTagToEntity<TWall>(VallaY3 );
		man_e.defineCMP<CPhysics>(VallaY3 , CPhysics{.x= -17.251535415649414 , .y = 0.5141037106513977, .z = -20.274301528930664});
		man_e.defineCMP<CRenderGL>(VallaY3 , CRenderGL{.modelMatrix = Model("assets/levelY/VallaY3.obj", glm::vec3(0,0,0))});
		auto& VallaY1 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(VallaY1 );
		man_e.addTagToEntity<TCollisionable>(VallaY1 );
		man_e.addTagToEntity<TWall>(VallaY1 );
		man_e.defineCMP<CPhysics>(VallaY1 , CPhysics{.x= -1.8420860767364502 , .y = 0.5141037106513977, .z = -7.77614164352417});
		man_e.defineCMP<CRenderGL>(VallaY1 , CRenderGL{.modelMatrix = Model("assets/levelY/VallaY1.obj", glm::vec3(0,0,0))});
		auto& VallaY2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(VallaY2 );
		man_e.addTagToEntity<TCollisionable>(VallaY2 );
		man_e.addTagToEntity<TWall>(VallaY2 );
		man_e.defineCMP<CPhysics>(VallaY2 , CPhysics{.x= 1.89097261428833 , .y = 0.5141037106513977, .z = -7.77614164352417});
		man_e.defineCMP<CRenderGL>(VallaY2 , CRenderGL{.modelMatrix = Model("assets/levelY/VallaY2.obj", glm::vec3(0,0,0))});
		auto& VallaY7 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(VallaY7 );
		man_e.addTagToEntity<TCollisionable>(VallaY7 );
		man_e.addTagToEntity<TWall>(VallaY7 );
		man_e.defineCMP<CPhysics>(VallaY7 , CPhysics{.x= -0.13 , .y = 0.51, .z = -25.31});
		man_e.defineCMP<CRenderGL>(VallaY7 , CRenderGL{.modelMatrix = Model("assets/levelY/VallaY7.obj", glm::vec3(0,0,0))});
		auto& VallaY4 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(VallaY4 );
		man_e.addTagToEntity<TCollisionable>(VallaY4 );
		man_e.addTagToEntity<TWall>(VallaY4 );
		man_e.defineCMP<CPhysics>(VallaY4 , CPhysics{.x= 16.567384719848633 , .y = 0.5141037106513977, .z = -20.274301528930664});
		man_e.defineCMP<CRenderGL>(VallaY4 , CRenderGL{.modelMatrix = Model("assets/levelY/VallaY4.obj", glm::vec3(0,0,0))});
		auto& VallaY6 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(VallaY6 );
		man_e.addTagToEntity<TCollisionable>(VallaY6 );
		man_e.addTagToEntity<TWall>(VallaY6 );
		man_e.defineCMP<CPhysics>(VallaY6 , CPhysics{.x= 14.26 , .y = 0.51, .z = -36.29});
		man_e.defineCMP<CRenderGL>(VallaY6 , CRenderGL{.modelMatrix = Model("assets/levelY/VallaY6.obj", glm::vec3(0,0,0))});
		auto& VallaY8 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(VallaY8 );
		man_e.addTagToEntity<TCollisionable>(VallaY8 );
		man_e.addTagToEntity<TWall>(VallaY8 );
		man_e.defineCMP<CPhysics>(VallaY8 , CPhysics{.x= -18.66 , .y = 0.51, .z = -33.49494552612305});
		man_e.defineCMP<CRenderGL>(VallaY8 , CRenderGL{.modelMatrix = Model("assets/levelY/VallaY8.obj", glm::vec3(0,0,0))});
		auto& VallaY9 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(VallaY9 );
		man_e.addTagToEntity<TCollisionable>(VallaY9 );
		man_e.addTagToEntity<TWall>(VallaY9 );
		man_e.defineCMP<CPhysics>(VallaY9 , CPhysics{.x= -14.58 , .y = 0.51, .z = -35.85});
		man_e.defineCMP<CRenderGL>(VallaY9 , CRenderGL{.modelMatrix = Model("assets/levelY/VallaY9.obj", glm::vec3(0,0,0))});
		auto& VallaY5 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(VallaY5 );
		man_e.addTagToEntity<TCollisionable>(VallaY5 );
		man_e.addTagToEntity<TWall>(VallaY5 );
		man_e.defineCMP<CPhysics>(VallaY5 , CPhysics{.x= 19.05 , .y = 0.51, .z = -33.40});
		man_e.defineCMP<CRenderGL>(VallaY5 , CRenderGL{.modelMatrix = Model("assets/levelY/VallaY5.obj", glm::vec3(0,0,0))});
	}
	
	auto& Corn_Start = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();
	man_e.defineCMP<CPhysics>(Corn_Start , CPhysics{.x= 0.0 , .y = 0.3, .z = -7.74});
	man_e.defineCMP<CRenderGL>(Corn_Start , CRenderGL{.modelMatrix = Model("assets/levelY/cornevent.obj", glm::vec3(0,0,0))});
	auto& Corn1 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision,CReposition, CIDLvl>();
	man_e.addTagToEntity<TCollisionable>(Corn1 );
	man_e.addTagToEntity<TReposition>(Corn1);
	man_e.defineCMP<CPhysics>(Corn1 , CPhysics{.x= -16.77 , .y = 0.3, .z = -34.77});
	man_e.defineCMP<CRenderGL>(Corn1 , CRenderGL{.modelMatrix = Model("assets/levelY/cornevent.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CReposition>(Corn1, CReposition{.x = 0.f, .z = -7.f, .type = 1});
	auto& Corn2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CReposition>();
	man_e.addTagToEntity<TCollisionable>(Corn2);
	man_e.addTagToEntity<TReposition>(Corn2);
	man_e.defineCMP<CPhysics>(Corn2 , CPhysics{.x= 16.80 , .y = 0.3, .z = -34.77});
	man_e.defineCMP<CRenderGL>(Corn2 , CRenderGL{.modelMatrix = Model("assets/levelY/cornevent.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CReposition>(Corn2, CReposition{.x = 0.f, .z = -7.f, .type = 2});

	auto& cartel_casa = man_e.createEntity_withCMPS< CRenderGL, CPhysics, CCollision, CInformation>();
	man_e.addTagToEntity<TCollisionable>(cartel_casa);
	man_e.addTagToEntity<TDescription>(cartel_casa);
	man_e.defineCMP<CRenderGL>(cartel_casa, CRenderGL{ .modelMatrix = Model("assets/level1/Cartel_Izq.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(cartel_casa, CPhysics{.x = -1.5, .y = 0, .z = -2.34});
	man_e.getEntityCMP<CRenderGL>(cartel_casa).modelMatrix.Rotate(90, 0, 1, 0);

	auto& cartel_doble = man_e.createEntity_withCMPS< CRenderGL, CPhysics, CCollision, CInformation>();
	man_e.addTagToEntity<TCollisionable>(cartel_doble);
	man_e.addTagToEntity<TDescription>(cartel_doble);
	//man_e.addTagToEntity<TWall>(cartel_doble);
	man_e.defineCMP<CRenderGL>(cartel_doble, CRenderGL{ .modelMatrix = Model("assets/level1/Cartel_doble.obj", glm::vec3(0, 0, 0))});
	man_e.defineCMP<CPhysics>(cartel_doble, CPhysics{.x = 0.28, .y = 0, .z = -23.98});
	
	//INSTANCIAS MAIZ

	auto& maiz = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(maiz);
	man_e.addTagToEntity<TNotRenderizable>(maiz);
	man_e.defineCMP<CRenderGL>(maiz, CRenderGL{.modelMatrix= Model("assets/level1/CornLP.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/levelY/instances_maizY.txt",.iscorn=true});

	auto& transitionlvlYtoGranero = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CIDLvl>();
	man_e.addTagToEntity<TNotRenderizable>(transitionlvlYtoGranero );
	man_e.addTagToEntity<TCollisionable>(transitionlvlYtoGranero );
	man_e.addTagToEntity<TTransition>(transitionlvlYtoGranero );
	man_e.defineCMP<CPhysics>(transitionlvlYtoGranero , CPhysics{.x= -30.09 , .y = 2.25, .z = -207.93});
	man_e.defineCMP<CRenderGL>(transitionlvlYtoGranero , CRenderGL{.modelMatrix = Model("assets/level5/Transitionlvl5to2.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CIDLvl>(transitionlvlYtoGranero, CIDLvl{.lvlid = 5});
	
	auto& TransitionY_To_Hub = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CIDLvl>();
	man_e.addTagToEntity<TNotRenderizable>(TransitionY_To_Hub );
	man_e.addTagToEntity<TCollisionable>(TransitionY_To_Hub );
	man_e.addTagToEntity<TTransition>(TransitionY_To_Hub );
	man_e.defineCMP<CPhysics>(TransitionY_To_Hub , CPhysics{.x= 0.01835775375366211 , .y = 1.1315714120864868, .z = 3.489880084991455});
	man_e.defineCMP<CRenderGL>(TransitionY_To_Hub , CRenderGL{.modelMatrix = Model("assets/levelY/TransitionY_To_Hub.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CIDLvl>(TransitionY_To_Hub, CIDLvl{.lvlid = 2});

	man_e.defineCMP<CInformation>(cartel_casa, CInformation{.type_of_text=0, .description{"To the house"}});
	man_e.defineCMP<CInformation>(cartel_doble, CInformation{.type_of_text=0, .description{"Choose wisely"}});


	std::cout<< "Entities lvl Y: " << man_e.getEntityArray().size() << "\n";
}

void Levels::load_lvl_Sotano(Manentity_type& man_e, Sys& systems, EngineGL& GL){
	man_e.getLevelsStatus().actual = 8;

	InitSoundsLvl_Sotano(systems.soundito);
	auto& player = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CInput, CCollision, CHealth, CStamina, CSound>();	
	man_e.addTagToEntity<TPlayer>(player);
	man_e.addTagToEntity<TCollider>(player);
	man_e.addTagToEntity<TNotRenderizable>(player); //HACER UN CUBE ACORDE AL PLAYER
	man_e.defineCMP<CPhysics>(player, CPhysics{.x=0, .y=1.5, .z=-4});
	man_e.defineCMP<CRenderGL>(player, CRenderGL{.modelMatrix= Model("assets/level1/cube.obj", glm::vec3(0,1.5,-3))});
	man_e.defineCMP<CSound>(player, CSound{.s_mgr = &systems.soundito, .name{"surface"}, .eventvalue = 0,});

	GL.camera.Position = { 0, 1.5, -4};
	////////////// PLAYER -- Model
	//	CMPS :  CRenderGL, CPhysics
	//	TAGS : 	TPlayer
	auto& player_model = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.addTagToEntity<TPlayer>(player_model);
	man_e.addTagToEntity<TNotRenderizable>(player_model);
	//man_e.defineCMP<CPhysics>(player_model, CPhysics{.x=4, .z= -4});
	man_e.defineCMP<CRenderGL>(player_model, CRenderGL{.modelMatrix= Model("assets/level1/brazo.obj", glm::vec3(0.7, -0.5, -2))}); 
	man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Scale(1.6,2,2);
	//man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Rotate(0, 0,1,0);
	////////////// PLAYER -- Model Candil with light
	//	CMPS :  CRenderGL, CPhysics, CPointLight
	//	TAGS : 	TPlayer
	auto& light = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CPointLight, CHealth, CSound, CCollision>(); //MIRAR BIEN
	//man_e.addTagToEntity<TPlayer>(light);
	man_e.addTagToEntity<TLantern>(light);
	man_e.addTagToEntity<TCollisionable>(light);
	man_e.addTagToEntity<Tpickable>(light);
	man_e.addTagToEntity<TScaleBoundingBox>(light);
	//man_e.addTagToEntity<TNotRenderizable>(light);
	man_e.defineCMP<CPhysics>(light,  CPhysics{.x=0.8, .y=0, .z=-45.5});
	man_e.defineCMP<CRenderGL>(light, CRenderGL{.modelMatrix = Model("assets/level1/Candil.obj", glm::vec3(0.8, -0.7, 0))});
	man_e.defineCMP<CSound>(light, CSound{.s_mgr= &systems.soundito}); 
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Scale(5,6,5);
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Rotate(90, 0,1,0);
	man_e.defineCMP<CPointLight>(light, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(light).setOff();

	auto& enemy = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound, CAnimation>();
	man_e.addTagToEntity<TEnemy>(enemy);
	man_e.addTagToEntity<TNotPatrol>(enemy);
	man_e.addTagToEntity<TNotRenderizable>(enemy);
	man_e.defineCMP<CPhysics>(enemy, CPhysics{.x = -18.02, .y = 0, .z = -32.99 , .vx = 0});
	man_e.defineCMP<CIA>(enemy, CIA{.dt = &systems.dtree});
	man_e.defineCMP<CSound>(enemy, CSound{.s_mgr = &systems.soundito});
	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
	man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.Rotate(180,0,1,0);
	man_e.getEntityCMP<CAnimation>(enemy).animation = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix);
	man_e.getEntityCMP<CAnimation>(enemy).animator = Animator(&man_e.getEntityCMP<CAnimation>(enemy).animation);
	man_e.getEntityCMP<CIA>(enemy).origin = man_e.getEntityCMP<CRenderGL>(enemy).modelMatrix.nodeMatrix;

	auto& enemy2 = man_e.createEntity_withCMPS<CRenderGL, CIA, CPhysics, CSound, CAnimation>();
	man_e.addTagToEntity<TEnemy>(enemy2);
	man_e.addTagToEntity<TNotPatrol>(enemy2);
	man_e.addTagToEntity<TNotRenderizable>(enemy2);
	man_e.addTagToEntity<TNotRenderAnim>(enemy2);
	man_e.addTagToEntity<TDummy>(enemy2);
	man_e.defineCMP<CPhysics>(enemy2, CPhysics{.x = 0, .y = 0, .z = -32.99 , .vx = 0});
	man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix = Model("assets/animaciones/idle.dae", glm::vec3(0, 0, 0));
	man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix.Rotate(180,0,1,0);
	man_e.getEntityCMP<CAnimation>(enemy2).animation = Animation("assets/animaciones/idle.dae", &man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix);
	man_e.getEntityCMP<CAnimation>(enemy2).animator  = Animator(&man_e.getEntityCMP<CAnimation>(enemy2).animation);
	man_e.defineCMP<CIA>(enemy2, CIA{.dt = &systems.dtree});
	man_e.defineCMP<CSound>(enemy2, CSound{.s_mgr = &systems.soundito});
	
	man_e.getEntityCMP<CIA>(enemy2).origin = man_e.getEntityCMP<CRenderGL>(enemy2).modelMatrix.nodeMatrix;
/*
	{ //MAP POSITIONS
	auto& map = man_e.createEntity_withCMPS<CMap>();

	man_e.getEntityCMP<CMap>(map).map.emplace_back(true, -10.58, -25.90);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  -8.44, -31.56);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  -8.44, -34.93);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  -7.30, -35.56);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  -3.11, -35.56);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,   1.64, -35.56);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,   3.36, -24.98);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  -1.59, -24.98);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(true,  -1.59, -20.94);
	
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -18.02, -32.99);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -13.98, -32.99);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -10.00, -32.99);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -13.98, -28.93);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -10.00, -28.93);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -13.98, -22.15);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false, -10.00, -22.15);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  -6.42, -28.93);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  -6.42, -22.15);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  -3.06, -28.93);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  -3.06, -22.15);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,   5.59, -28.93);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,   5.59, -22.15);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  -6.42, -33.89);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  -3.06, -33.89);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,   0.91, -28.93);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,   0.91, -22.15);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,   0.91, -33.89);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  -6.42, -37.90);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,  -3.06, -37.90);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,   0.91, -37.90);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,   5.59, -33.89);
	man_e.getEntityCMP<CMap>(map).map.emplace_back(false,   5.59, -37.90);

	//añadimos la vecindad de los puntos
	
	man_e.getEntityCMP<CMap>(map).map[0].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[13]);
	man_e.getEntityCMP<CMap>(map).map[0].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[15]);

	man_e.getEntityCMP<CMap>(map).map[1].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[11]);
	man_e.getEntityCMP<CMap>(map).map[1].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[12]);
	man_e.getEntityCMP<CMap>(map).map[1].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[13]);
	man_e.getEntityCMP<CMap>(map).map[1].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[16]);
	
	man_e.getEntityCMP<CMap>(map).map[2].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[1]);
	man_e.getEntityCMP<CMap>(map).map[2].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[3]);
	man_e.getEntityCMP<CMap>(map).map[2].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[22]);

	man_e.getEntityCMP<CMap>(map).map[3].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[4]);
	man_e.getEntityCMP<CMap>(map).map[3].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[22]);
	man_e.getEntityCMP<CMap>(map).map[3].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[27]);

	man_e.getEntityCMP<CMap>(map).map[4].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[3]);
	man_e.getEntityCMP<CMap>(map).map[4].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[5]);
	man_e.getEntityCMP<CMap>(map).map[4].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[23]);
	man_e.getEntityCMP<CMap>(map).map[4].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[28]);

	man_e.getEntityCMP<CMap>(map).map[5].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[3]);
	man_e.getEntityCMP<CMap>(map).map[5].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[4]);
	man_e.getEntityCMP<CMap>(map).map[5].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[26]);
	man_e.getEntityCMP<CMap>(map).map[5].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[29]);

	man_e.getEntityCMP<CMap>(map).map[9].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[10]);
	man_e.getEntityCMP<CMap>(map).map[10].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[9]);
	man_e.getEntityCMP<CMap>(map).map[10].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[11]);
	man_e.getEntityCMP<CMap>(map).map[10].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[12]);
	man_e.getEntityCMP<CMap>(map).map[11].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[10]);
	man_e.getEntityCMP<CMap>(map).map[11].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[13]);
	man_e.getEntityCMP<CMap>(map).map[11].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[1]);
	man_e.getEntityCMP<CMap>(map).map[11].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[2]);
	man_e.getEntityCMP<CMap>(map).map[12].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[10]);
	man_e.getEntityCMP<CMap>(map).map[12].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[13]);
	man_e.getEntityCMP<CMap>(map).map[12].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[14]);
	man_e.getEntityCMP<CMap>(map).map[13].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[0]);
	man_e.getEntityCMP<CMap>(map).map[13].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[11]);
	man_e.getEntityCMP<CMap>(map).map[13].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[12]);
	man_e.getEntityCMP<CMap>(map).map[13].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[16]);
	man_e.getEntityCMP<CMap>(map).map[14].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[0]);
	man_e.getEntityCMP<CMap>(map).map[14].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[12]);
	man_e.getEntityCMP<CMap>(map).map[14].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[15]);
	man_e.getEntityCMP<CMap>(map).map[14].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[0]);
	man_e.getEntityCMP<CMap>(map).map[15].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[14]);
	man_e.getEntityCMP<CMap>(map).map[15].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[17]);
	man_e.getEntityCMP<CMap>(map).map[16].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[1]);
	man_e.getEntityCMP<CMap>(map).map[16].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[13]);
	man_e.getEntityCMP<CMap>(map).map[16].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[17]);
	man_e.getEntityCMP<CMap>(map).map[16].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[18]);
	man_e.getEntityCMP<CMap>(map).map[16].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[22]);
	man_e.getEntityCMP<CMap>(map).map[17].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[14]);
	man_e.getEntityCMP<CMap>(map).map[17].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[15]);
	man_e.getEntityCMP<CMap>(map).map[17].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[16]);
	man_e.getEntityCMP<CMap>(map).map[18].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[6]);
	man_e.getEntityCMP<CMap>(map).map[18].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[16]);
	man_e.getEntityCMP<CMap>(map).map[18].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[23]);
	man_e.getEntityCMP<CMap>(map).map[18].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[24]);
	man_e.getEntityCMP<CMap>(map).map[19].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[6]);
	man_e.getEntityCMP<CMap>(map).map[19].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[8]);
	man_e.getEntityCMP<CMap>(map).map[19].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[17]);
	man_e.getEntityCMP<CMap>(map).map[20].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[21]);
	man_e.getEntityCMP<CMap>(map).map[20].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[24]);
	man_e.getEntityCMP<CMap>(map).map[20].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[30]);	
	man_e.getEntityCMP<CMap>(map).map[21].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[7]);
	man_e.getEntityCMP<CMap>(map).map[21].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[20]);
	man_e.getEntityCMP<CMap>(map).map[21].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[25]);
	man_e.getEntityCMP<CMap>(map).map[22].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[1]);
	man_e.getEntityCMP<CMap>(map).map[22].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[2]);
	man_e.getEntityCMP<CMap>(map).map[22].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[16]);
	man_e.getEntityCMP<CMap>(map).map[22].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[23]);
	man_e.getEntityCMP<CMap>(map).map[23].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[4]);
	man_e.getEntityCMP<CMap>(map).map[23].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[18]);
	man_e.getEntityCMP<CMap>(map).map[23].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[22]);
	man_e.getEntityCMP<CMap>(map).map[23].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[26]);
	man_e.getEntityCMP<CMap>(map).map[24].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[6]);
	man_e.getEntityCMP<CMap>(map).map[24].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[7]);
	man_e.getEntityCMP<CMap>(map).map[24].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[18]);
	man_e.getEntityCMP<CMap>(map).map[24].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[20]);
	man_e.getEntityCMP<CMap>(map).map[24].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[26]);
	man_e.getEntityCMP<CMap>(map).map[25].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[6]);
	man_e.getEntityCMP<CMap>(map).map[25].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[7]);
	man_e.getEntityCMP<CMap>(map).map[25].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[8]);
	man_e.getEntityCMP<CMap>(map).map[25].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[21]);
	man_e.getEntityCMP<CMap>(map).map[26].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[5]);
	man_e.getEntityCMP<CMap>(map).map[26].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[23]);
	man_e.getEntityCMP<CMap>(map).map[26].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[24]);
	man_e.getEntityCMP<CMap>(map).map[26].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[30]);
	man_e.getEntityCMP<CMap>(map).map[27].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[3]);
	man_e.getEntityCMP<CMap>(map).map[27].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[28]);
	man_e.getEntityCMP<CMap>(map).map[28].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[4]);
	man_e.getEntityCMP<CMap>(map).map[28].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[27]);
	man_e.getEntityCMP<CMap>(map).map[28].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[29]);
	man_e.getEntityCMP<CMap>(map).map[29].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[5]);
	man_e.getEntityCMP<CMap>(map).map[29].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[28]);
	man_e.getEntityCMP<CMap>(map).map[29].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[31]);
	man_e.getEntityCMP<CMap>(map).map[30].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[5]);
	man_e.getEntityCMP<CMap>(map).map[30].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[20]);
	man_e.getEntityCMP<CMap>(map).map[30].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[26]);
	man_e.getEntityCMP<CMap>(map).map[30].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[31]);
	man_e.getEntityCMP<CMap>(map).map[31].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[29]);
	man_e.getEntityCMP<CMap>(map).map[31].vecNeighbours.push_back(&man_e.getEntityCMP<CMap>(map).map[30]);
	}
	*/
	
	auto& escenario = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.defineCMP<CRenderGL>(escenario, CRenderGL{ .modelMatrix = Model("assets/Sotano/Sotano.obj", glm::vec3(0,-1.5,0))});

	auto& rueda = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision, CPng,CSound>();
	man_e.addTagToEntity<TCollisionable>(rueda);
	man_e.addTagToEntity<TScaleBoundingBox>(rueda);
	man_e.addTagToEntity<Tpickable>(rueda);
	man_e.addTagToEntity<TDescription>(rueda);
	man_e.addTagToEntity<TRueda>(rueda);
	man_e.defineCMP<CPhysics>(rueda, CPhysics{.x =-17.88, .y=0.26 ,.z= -32.14});
	man_e.defineCMP<CPng>(rueda, CPng{.icono = Model("assets/Sotano/rueda.obj", glm::vec3(-0.70,0.42,0))});
	man_e.getEntityCMP<CPng>(rueda).icono.Rotate(90,1,1,1);
	man_e.getEntityCMP<CPng>(rueda).icono.Scale(0.35,0.35,0.35);
	man_e.defineCMP<CSound>(rueda, CSound{.s_mgr = &systems.soundito});
	man_e.defineCMP<CRenderGL>(rueda, CRenderGL{.modelMatrix = Model("assets/Sotano/rueda.obj", glm::vec3(0,0,0))});
	man_e.getEntityCMP<CRenderGL>(rueda).modelMatrix.Scale(1.6,1.6,1.6);
	man_e.getEntityCMP<CRenderGL>(rueda).modelMatrix.Rotate(65,0,0,1);
	auto& caja_r = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();
	man_e.defineCMP<CPhysics>(caja_r, CPhysics{.x =-19.88, .y=0.25 ,.z= -32.14});
	man_e.defineCMP<CRenderGL>(caja_r, CRenderGL{.modelMatrix = Model("assets/Sotano/cajas.obj", glm::vec3(0,0,0))});
	man_e.getEntityCMP<CRenderGL>(caja_r).modelMatrix.Scale(1.2,1.2,1.2);
	
	//COLISIONES
	{
	auto& ColiS12 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS12 );
	man_e.addTagToEntity<TCollisionable>(ColiS12 );
	man_e.addTagToEntity<TWall>(ColiS12 );
	man_e.defineCMP<CPhysics>(ColiS12 , CPhysics{.x= -8.76849365234375 , .y = -0.04288250207901001, .z = -20.21274757385254});
	man_e.defineCMP<CRenderGL>(ColiS12 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS12.obj", glm::vec3(0,0,0))});

	auto& ColiS16 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS16 );
	man_e.addTagToEntity<TCollisionable>(ColiS16 );
	man_e.addTagToEntity<TWall>(ColiS16 );
	man_e.defineCMP<CPhysics>(ColiS16 , CPhysics{.x= -8.447691917419434 , .y = -0.02438175678253174, .z = -33.15758514404297});
	man_e.defineCMP<CRenderGL>(ColiS16 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS16.obj", glm::vec3(0,0,0))});

	auto& ColiS10 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS10 );
	man_e.addTagToEntity<TCollisionable>(ColiS10 );
	man_e.addTagToEntity<TWall>(ColiS10 );
	man_e.defineCMP<CPhysics>(ColiS10 , CPhysics{.x= -18.586105346679688 , .y = -0.04288250207901001, .z = -30.242158889770508});
	man_e.defineCMP<CRenderGL>(ColiS10 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS10.obj", glm::vec3(0,0,0))});

	auto& ColiS13 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS13 );
	man_e.addTagToEntity<TCollisionable>(ColiS13 );
	man_e.addTagToEntity<TWall>(ColiS13 );
	man_e.defineCMP<CPhysics>(ColiS13 , CPhysics{.x= -1.669561743736267 , .y = -0.02438175678253174, .z = -22.511762619018555});
	man_e.defineCMP<CRenderGL>(ColiS13 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS13.obj", glm::vec3(0,0,0))});

	auto& ColiS15 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS15 );
	man_e.addTagToEntity<TCollisionable>(ColiS15 );
	man_e.addTagToEntity<TWall>(ColiS15 );
	man_e.defineCMP<CPhysics>(ColiS15 , CPhysics{.x= 0.15, .y = 0.02438175678253174, .z = -35.55625534057617});
	man_e.defineCMP<CRenderGL>(ColiS15 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS15.obj", glm::vec3(0,0,0))});

	auto& ColiS14 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS14 );
	man_e.addTagToEntity<TCollisionable>(ColiS14 );
	man_e.addTagToEntity<TWall>(ColiS14 );
	man_e.defineCMP<CPhysics>(ColiS14 , CPhysics{.x= 1.63 , .y = 0.02438175678253174, .z = -24.974567413330078});
	man_e.defineCMP<CRenderGL>(ColiS14 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS14.obj", glm::vec3(0,0,0))});

	auto& ColiS1 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS1 );
	man_e.addTagToEntity<TCollisionable>(ColiS1 );
	man_e.addTagToEntity<TWall>(ColiS1 );
	man_e.defineCMP<CPhysics>(ColiS1 , CPhysics{.x= 0.3372687101364136 , .y = -0.02438175678253174, .z = 2.5});
	man_e.defineCMP<CRenderGL>(ColiS1 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS1.obj", glm::vec3(0,0,0))});

	auto& ColiS2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS2 );
	man_e.addTagToEntity<TCollisionable>(ColiS2 );
	man_e.addTagToEntity<TWall>(ColiS2 );
	man_e.defineCMP<CPhysics>(ColiS2 , CPhysics{.x= 1.3169159889221191 , .y = -0.04288250207901001, .z = -9.47962760925293});
	man_e.defineCMP<CRenderGL>(ColiS2 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS2.obj", glm::vec3(0,0,0))});

	auto& ColiS3 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS3 );
	man_e.addTagToEntity<TCollisionable>(ColiS3 );
	man_e.addTagToEntity<TWall>(ColiS3 );
	man_e.defineCMP<CPhysics>(ColiS3 , CPhysics{.x= -1.3404326438903809 , .y = -0.04288250207901001, .z = -9.47962760925293});
	man_e.defineCMP<CRenderGL>(ColiS3 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS3.obj", glm::vec3(0,0,0))});

	auto& ColiS4 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS4 );
	man_e.addTagToEntity<TCollisionable>(ColiS4 );
	man_e.addTagToEntity<TWall>(ColiS4 );
	man_e.defineCMP<CPhysics>(ColiS4 , CPhysics{.x= 4.201246738433838 , .y = -0.04288250207901001, .z = -20.246610641479492});
	man_e.defineCMP<CRenderGL>(ColiS4 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS4.obj", glm::vec3(0,0,0))});

	auto& ColiS5 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS5 );
	man_e.addTagToEntity<TCollisionable>(ColiS5 );
	man_e.addTagToEntity<TWall>(ColiS5 );
	man_e.defineCMP<CPhysics>(ColiS5 , CPhysics{.x= 7.58760404586792 , .y = -0.04288250207901001, .z = -30.051437377929688});
	man_e.defineCMP<CRenderGL>(ColiS5 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS5.obj", glm::vec3(0,0,0))});

	auto& ColiS6 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS6 );
	man_e.addTagToEntity<TCollisionable>(ColiS6 );
	man_e.addTagToEntity<TWall>(ColiS6 );
	man_e.defineCMP<CPhysics>(ColiS6 , CPhysics{.x= -0.41237643361091614 , .y = -0.04288250207901001, .z = -39.87419891357422});
	man_e.defineCMP<CRenderGL>(ColiS6 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS6.obj", glm::vec3(0,0,0))});

	auto& ColiS7 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS7 );
	man_e.addTagToEntity<TCollisionable>(ColiS7 );
	man_e.addTagToEntity<TWall>(ColiS7 );
	man_e.defineCMP<CPhysics>(ColiS7 , CPhysics{.x= -8.302586555480957 , .y = -0.04288250207901001, .z = -37.91709899902344});
	man_e.defineCMP<CRenderGL>(ColiS7 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS7.obj", glm::vec3(0,0,0))});

	auto& ColiS8 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS8 );
	man_e.addTagToEntity<TCollisionable>(ColiS8 );
	man_e.addTagToEntity<TWall>(ColiS8 );
	man_e.defineCMP<CPhysics>(ColiS8 , CPhysics{.x= -14.441207885742188 , .y = -0.04288250207901001, .z = -35.48423767089844});
	man_e.defineCMP<CRenderGL>(ColiS8 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS8.obj", glm::vec3(0,0,0))});

	auto& ColiS9 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS9 );
	man_e.addTagToEntity<TCollisionable>(ColiS9 );
	man_e.addTagToEntity<TWall>(ColiS9 );
	man_e.defineCMP<CPhysics>(ColiS9 , CPhysics{.x= -21.088054656982422 , .y = -0.04288250207901001, .z = -32.898033142089844});
	man_e.defineCMP<CRenderGL>(ColiS9 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS9.obj", glm::vec3(0,0,0))});

	auto& ColiS11 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiS11 );
	man_e.addTagToEntity<TCollisionable>(ColiS11 );
	man_e.addTagToEntity<TWall>(ColiS11 );
	man_e.defineCMP<CPhysics>(ColiS11 , CPhysics{.x= -16.658702850341797 , .y = -0.04288250207901001, .z = -24.95364761352539});
	man_e.defineCMP<CRenderGL>(ColiS11 , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiS11.obj", glm::vec3(0,0,0))});

	auto& ColiLoop = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TNotRenderizable>(ColiLoop );
	man_e.addTagToEntity<TCollisionable>(ColiLoop );
	man_e.addTagToEntity<TWall>(ColiLoop );
	man_e.defineCMP<CPhysics>(ColiLoop , CPhysics{.x= -10.565428733825684 , .y = 0.0, .z = -25.942880630493164});
	man_e.defineCMP<CRenderGL>(ColiLoop , CRenderGL{.modelMatrix = Model("assets/Sotano/ColiLoop.obj", glm::vec3(0,0,0))});
	}
	
	auto& luz1 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.addTagToEntity<TLantern>(luz1);
	man_e.defineCMP<CPhysics>(luz1,  CPhysics{.x=-0.11, .y=2.42, .z=-1.24});
	man_e.defineCMP<CPointLight>(luz1, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});

	auto& luz2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.addTagToEntity<TLantern>(luz2);
	man_e.defineCMP<CPhysics>(luz2,  CPhysics{.x=8.31, .y=2.42, .z=-10.57});
	man_e.defineCMP<CPointLight>(luz2, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});

	auto& luz3 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CPointLight>(); //MIRAR BIEN
	man_e.addTagToEntity<TLantern>(luz3);
	man_e.defineCMP<CPhysics>(luz3,  CPhysics{.x=-0.11, .y=2.42, .z=-5.07});
	man_e.defineCMP<CPointLight>(luz3, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
		
	auto& TransS_to_Granero = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CIDLvl>();
	man_e.addTagToEntity<TNotRenderizable>(TransS_to_Granero );
	man_e.addTagToEntity<TCollisionable>(TransS_to_Granero );
	man_e.addTagToEntity<TTransition>(TransS_to_Granero);
	man_e.defineCMP<CPhysics>(TransS_to_Granero , CPhysics{.x= 0.06502115726470947 , .y = 0.0, .z = 2.4250199794769287});
	man_e.defineCMP<CRenderGL>(TransS_to_Granero , CRenderGL{.modelMatrix = Model("assets/Sotano/TransS_to_Granero.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CIDLvl>(TransS_to_Granero, CIDLvl{.lvlid = 5});
	


	auto& yesquero = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CCollision>();
	man_e.addTagToEntity<TCollisionable>(yesquero);
	man_e.addTagToEntity<TScaleBoundingBox>(yesquero);
	man_e.addTagToEntity<Tpickable>(yesquero);
	man_e.addTagToEntity<TYesquero>(yesquero);
	man_e.addTagToEntity<TDescription>(yesquero);
	man_e.defineCMP<CPhysics>(yesquero, CPhysics{.x =-1.91, .y=0 ,.z= -38.21});
	man_e.getEntityCMP<CRenderGL>(yesquero).modelMatrix.Rotate(90,0,0,1);
	man_e.defineCMP<CRenderGL>(yesquero, CRenderGL{.modelMatrix = Model("assets/level1/aceite.obj", glm::vec3(0,0,0))});
	//DESCRIPTIONS
	man_e.defineCMP<CInformation>(yesquero,CInformation{.description="Refills fuel" ,.descriptionPickable="[E] Grab"});
	man_e.defineCMP<CInformation>(light, CInformation{.type_of_text = 0, .description{""}, .descriptionPickable{"[Q] Grab"}});
	man_e.defineCMP<CInformation>(rueda, CInformation{.type_of_text = 0, .description{"A wheel! My salvation!"}, .descriptionPickable{"[E] Grab"}});

	std::cout << "Entities level Sot : " << man_e.getEntityArray().size() << "\n";
}

void Levels::load_lvl_maze(Manentity_type& man_e, Sys& systems, EngineGL& GL){
	//--------------------------------PLAYER---------------------------------------------------//
	//man_e.getLevelsStatus().actual = 8;
	InitSoundsLvl_maze(systems.soundito);
	////////////// PLAYER -- Collision box
	//	CMPS :  CRenderGL, CPhysics, CInput, CCollision
	//	TAGS : 	TPlayer, TCollider, TNotRenderizable
	man_e.getLevelsStatus().actual = 7;
	auto& player = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CInput, CCollision, CHealth, CStamina, CSound>();	
	man_e.addTagToEntity<TPlayer>(player);
	man_e.addTagToEntity<TCollider>(player);
	man_e.addTagToEntity<TNotRenderizable>(player); //HACER UN CUBE ACORDE AL PLAYER
	man_e.defineCMP<CPhysics>(player, CPhysics{.x=0, .y=1.5, .z=-4});
	man_e.defineCMP<CRenderGL>(player, CRenderGL{.modelMatrix= Model("assets/level1/cube.obj", glm::vec3(0,1.5,-3))});
	man_e.defineCMP<CSound>(player, CSound{.s_mgr = &systems.soundito, .name{"surface"}, .eventvalue = 0,});

	//GL.camera.Position = { -1.20, 1.5, -58};
	////////////// PLAYER -- Model
	//	CMPS :  CRenderGL, CPhysics
	//	TAGS : 	TPlayer
	auto& player_model = man_e.createEntity_withCMPS<CRenderGL, CPhysics>();	
	man_e.addTagToEntity<TPlayer>(player_model);
	man_e.addTagToEntity<TNotRenderizable>(player_model);
	man_e.defineCMP<CPhysics>(player_model, CPhysics{.x=0.7, .y=-0.5, .z=-2});
	man_e.defineCMP<CRenderGL>(player_model, CRenderGL{.modelMatrix= Model("assets/level1/brazo.obj", glm::vec3(0.7, -0.5, -2))}); 
	man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Scale(1.6,2,2);
	//man_e.getEntityCMP<CRenderGL>(player_model).modelMatrix.Rotate(0, 0,1,0);
	////////////// PLAYER -- Model Candil with light
	//	CMPS :  CRenderGL, CPhysics, CPointLight
	//	TAGS : 	TPlayer
	auto& light = man_e.createEntity_withCMPS<CInformation, CRenderGL, CPhysics, CPointLight, CHealth, CSound, CCollision>(); //MIRAR BIEN
	//man_e.addTagToEntity<TPlayer>(light);
	man_e.addTagToEntity<TLantern>(light);
	man_e.addTagToEntity<TCollisionable>(light);
	man_e.addTagToEntity<Tpickable>(light);
	man_e.addTagToEntity<TScaleBoundingBox>(light);
	//man_e.addTagToEntity<TNotRenderizable>(light);
	man_e.defineCMP<CPhysics>(light,  CPhysics{.x=0.8, .y=0, .z=-45.5});
	man_e.defineCMP<CRenderGL>(light, CRenderGL{.modelMatrix = Model("assets/level1/Candil.obj", glm::vec3(0.8, -0.7, 0))});
	man_e.defineCMP<CSound>(light, CSound{.s_mgr= &systems.soundito}); 
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Scale(5,6,5);
	man_e.getEntityCMP<CRenderGL>(light).modelMatrix.Rotate(90, 0,1,0);
	man_e.defineCMP<CPointLight>(light, CPointLight{1.9,0.0,0.0,0.9,0.9,0.9,0.11,0.11,0.11,1,0.7,0.14,GL.nextIDLight++,true});
	man_e.getEntityCMP<CPointLight>(light).setOff();
	
	auto& escenario = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.defineCMP<CRenderGL>(escenario, CRenderGL{ .modelMatrix = Model("assets/levelmaze/laberinto.obj", glm::vec3(0,-1.5,0))});

	srand(time(0));

	int a = rand() % 4 + 1;
	//std::cout << "Spawn laberinto " <<a << "\n";
	//a = 4;
	//descomentar lo de encima para seleccionar nivel

	if(a == 1){
		//cargar laberinto1
		auto& maiz1 = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
		man_e.addTagToEntity<TInstance>(maiz1);
		man_e.addTagToEntity<TNotRenderizable>(maiz1);
		man_e.defineCMP<CRenderGL>(maiz1, CRenderGL{.modelMatrix= Model("assets/level1/CornLP.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/levelmaze/laberinto1/instances_lab.txt",.iscorn=true});
		auto& ColiLaberinto1 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1 , CPhysics{.x= -15.469999313354492 , .y = 0.0, .z = -3.8446156978607178});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_001 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_001 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_001 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_001 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_001 , CPhysics{.x= 15.012308120727539 , .y = 0.0, .z = -3.8446156978607178});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_001 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.001.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_002 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_002 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_002 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_002 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_002 , CPhysics{.x= 25.99692153930664 , .y = 0.0, .z = -30.848464965820312});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_002 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.002.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_003 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_003 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_003 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_003 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_003 , CPhysics{.x= -25.905384063720703 , .y = 0.0, .z = -30.848464965820312});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_003 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.003.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_004 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_004 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_004 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_004 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_004 , CPhysics{.x= -15.469999313354492 , .y = 0.0, .z = -56.04351043701172});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_004 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.004.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_005 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_005 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_005 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_005 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_005 , CPhysics{.x= 15.012308120727539 , .y = 0.0, .z = -56.04351043701172});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_005 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.005.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_006 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_006 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_006 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_006 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_006 , CPhysics{.x= -0.09416218101978302 , .y = 0.0, .z = 8.621926307678223});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_006 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.006.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_007 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_007 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_007 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_007 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_007 , CPhysics{.x= -3.399717330932617 , .y = 0.0, .z = 2.392226457595825});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_007 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.007.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_008 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_008 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_008 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_008 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_008 , CPhysics{.x= 3.020688056945801 , .y = 0.0, .z = 2.392226457595825});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_008 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.008.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_009 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_009 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_009 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_009 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_009 , CPhysics{.x= -3.399717330932617 , .y = 0.0, .z = -62.508544921875});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_009 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.009.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_010 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_010 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_010 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_010 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_010 , CPhysics{.x= 3.020688056945801 , .y = 0.0, .z = -62.508544921875});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_010 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.010.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_011 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_011 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_011 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_011 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_011 , CPhysics{.x= -0.09416218101978302 , .y = 0.0, .z = -68.72808837890625});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_011 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.011.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_012 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_012 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_012 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_012 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_012 , CPhysics{.x= -15.655699729919434 , .y = 0.0, .z = -49.32193374633789});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_012 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.012.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_013 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_013 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_013 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_013 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_013 , CPhysics{.x= -22.429546356201172 , .y = 0.0, .z = -41.083473205566406});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_013 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.013.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_014 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_014 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_014 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_014 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_014 , CPhysics{.x= -22.429546356201172 , .y = 0.0, .z = -33.66885757446289});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_014 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.014.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_015 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_015 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_015 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_015 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_015 , CPhysics{.x= -0.13181056082248688 , .y = 0.0, .z = -10.875778198242188});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_015 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.015.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_016 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_016 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_016 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_016 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_016 , CPhysics{.x= 15.192758560180664 , .y = 0.0, .z = -10.875778198242188});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_016 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.016.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_017 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_017 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_017 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_017 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_017 , CPhysics{.x= 22.149681091308594 , .y = 0.0, .z = -26.345779418945312});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_017 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.017.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_018 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_018 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_018 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_018 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_018 , CPhysics{.x= -3.664163589477539 , .y = 0.0, .z = -41.083473205566406});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_018 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.018.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_019 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_019 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_019 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_019 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_019 , CPhysics{.x= 12.586456298828125 , .y = 0.0, .z = -49.23039627075195});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_019 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.019.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_020 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_020 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_020 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_020 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_020 , CPhysics{.x= -11.902623176574707 , .y = 0.0, .z = -19.022701263427734});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_020 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.020.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_021 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_021 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_021 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_021 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_021 , CPhysics{.x= 6.313531398773193 , .y = 0.0, .z = -18.839624404907227});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_021 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.021.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_022 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_022 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_022 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_022 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_022 , CPhysics{.x= 12.273065567016602 , .y = 0.0, .z = -33.71638870239258});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_022 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.022.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_023 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_023 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_023 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_023 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_023 , CPhysics{.x= 3.5006303787231445 , .y = 0.0, .z = -26.469594955444336});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_023 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.023.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_024 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_024 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_024 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_024 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_024 , CPhysics{.x= -11.310800552368164 , .y = 0.0, .z = -8.225475311279297});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_024 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.024.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_025 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_025 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_025 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_025 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_025 , CPhysics{.x= -19.320415496826172 , .y = 0.0, .z = -18.714256286621094});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_025 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.025.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_026 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_026 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_026 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_026 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_026 , CPhysics{.x= -3.5554592609405518 , .y = 0.0, .z = -23.418315887451172});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_026 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.026.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_027 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_027 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_027 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_027 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_027 , CPhysics{.x= -11.056527137756348 , .y = 0.0, .z = -37.53049087524414});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_027 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.027.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_028 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_028 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_028 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_028 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_028 , CPhysics{.x= 11.00169849395752 , .y = 0.0, .z = -12.2302827835083});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_028 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.028.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_029 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_029 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_029 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_029 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_029 , CPhysics{.x= 11.00169849395752 , .y = 0.0, .z = -28.758060455322266});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_029 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.029.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_030 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_030 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_030 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_030 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_030 , CPhysics{.x= 3.691335678100586 , .y = 0.0, .z = -37.530494689941406});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_030 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.030.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_031 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_031 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_031 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_031 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_031 , CPhysics{.x= 11.065266609191895 , .y = 0.0, .z = -45.03156280517578});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_031 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.031.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_032 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_032 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_032 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_032 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_032 , CPhysics{.x= 19.01131248474121 , .y = 0.0, .z = -45.03156280517578});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_032 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.032.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_033 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_033 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_033 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_033 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_033 , CPhysics{.x= 3.564199447631836 , .y = 0.0, .z = -52.15121841430664});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_033 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.033.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_034 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_034 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_034 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_034 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_034 , CPhysics{.x= -3.8097314834594727 , .y = 0.0, .z = -49.099937438964844});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_034 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.034.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto1_035 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto1_035 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto1_035 );
		man_e.addTagToEntity<TWall>(ColiLaberinto1_035 );
		man_e.defineCMP<CPhysics>(ColiLaberinto1_035 , CPhysics{.x= 19.01131248474121 , .y = 0.0, .z = -22.728397369384766});
		man_e.defineCMP<CRenderGL>(ColiLaberinto1_035 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto1/ColiLaberinto1.035.obj", glm::vec3(0,0,0))});
	}
	
	if(a == 2){

		auto& maiz = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
		man_e.addTagToEntity<TInstance>(maiz);
		man_e.addTagToEntity<TNotRenderizable>(maiz);
		man_e.defineCMP<CRenderGL>(maiz, CRenderGL{.modelMatrix= Model("assets/level1/CornLP.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/levelmaze/laberinto2/instances_lab.txt",.iscorn=true});
		auto& ColiLaberinto2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2 , CPhysics{.x= -15.469999313354492 , .y = 0.0, .z = -3.8446156978607178});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_001 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_001 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_001 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_001 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_001 , CPhysics{.x= -0.09416218101978302 , .y = 0.0, .z = 8.621926307678223});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_001 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2_001.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_033 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_033 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_033 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_033 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_033 , CPhysics{.x= 14.852130889892578 , .y = 0.0, .z = -3.8446156978607178});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_033 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.001.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_003 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_003 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_003 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_003 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_003 , CPhysics{.x= -3.399717330932617 , .y = 0.0, .z = 2.392226457595825});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_003 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.003.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_002 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_002 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_002 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_002 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_002 , CPhysics{.x= 3.020688056945801 , .y = 0.0, .z = 2.392226457595825});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_002 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.002.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_005 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_005 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_005 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_005 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_005 , CPhysics{.x= -3.399717330932617 , .y = 0.0, .z = -62.508544921875});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_005 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.005.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_004 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_004 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_004 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_004 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_004 , CPhysics{.x= 3.020688056945801 , .y = 0.0, .z = -62.508544921875});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_004 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.004.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_006 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_006 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_006 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_006 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_006 , CPhysics{.x= -0.09416218101978302 , .y = 0.0, .z = -68.72808837890625});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_006 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.006.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_007 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_007 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_007 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_007 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_007 , CPhysics{.x= 14.852130889892578 , .y = 0.0, .z = -56.42317199707031});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_007 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.007.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_008 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_008 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_008 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_008 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_008 , CPhysics{.x= -14.758895874023438 , .y = 0.0, .z = -56.42317199707031});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_008 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.008.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_009 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_009 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_009 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_009 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_009 , CPhysics{.x= 26.308086395263672 , .y = 0.0, .z = -30.122249603271484});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_009 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.009.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_010 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_010 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_010 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_010 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_010 , CPhysics{.x= -26.32654571533203 , .y = 0.0, .z = -30.122249603271484});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_010 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.010.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_011 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_011 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_011 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_011 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_011 , CPhysics{.x= -3.6707677841186523 , .y = 0.0, .z = -19.67160415649414});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_011 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.011.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_012 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_012 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_012 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_012 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_012 , CPhysics{.x= 3.5760297775268555 , .y = 0.0, .z = -44.234432220458984});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_012 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.012.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_013 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_013 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_013 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_013 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_013 , CPhysics{.x= -18.69833755493164 , .y = 0.0, .z = -18.908782958984375});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_013 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.013.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_014 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_014 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_014 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_014 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_014 , CPhysics{.x= 11.509363174438477 , .y = 0.0, .z = -30.122249603271484});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_014 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.014.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_015 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_015 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_015 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_015 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_015 , CPhysics{.x= 18.756160736083984 , .y = 0.0, .z = -7.924163818359375});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_015 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.015.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_016 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_016 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_016 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_016 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_016 , CPhysics{.x= 18.756160736083984 , .y = 0.0, .z = -22.41775894165039});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_016 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.016.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_017 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_017 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_017 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_017 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_017 , CPhysics{.x= -11.451541900634766 , .y = 0.0, .z = -7.771599769592285});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_017 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.017.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_018 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_018 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_018 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_018 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_018 , CPhysics{.x= -18.698339462280273 , .y = 0.0, .z = -45.14981460571289});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_018 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.018.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_019 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_019 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_019 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_019 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_019 , CPhysics{.x= -11.451541900634766 , .y = 0.0, .z = -37.674171447753906});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_019 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.019.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_020 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_020 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_020 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_020 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_020 , CPhysics{.x= 18.756160736083984 , .y = 0.0, .z = -45.14981460571289});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_020 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.020.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_021 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_021 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_021 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_021 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_021 , CPhysics{.x= 11.509363174438477 , .y = 0.0, .z = -14.94211196899414});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_021 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.021.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_022 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_022 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_022 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_022 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_022 , CPhysics{.x= -3.5944881439208984 , .y = 0.0, .z = -45.07353210449219});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_022 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.022.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_023 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_023 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_023 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_023 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_023 , CPhysics{.x= 15.018339157104492 , .y = 0.0, .z = -48.73507308959961});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_023 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.023.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_024 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_024 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_024 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_024 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_024 , CPhysics{.x= 8.000388145446777 , .y = 0.0, .z = -41.56455993652344});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_024 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.024.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_025 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_025 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_025 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_025 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_025 , CPhysics{.x= 4.262566089630127 , .y = 0.0, .z = -26.61327362060547});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_025 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.025.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_026 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_026 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_026 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_026 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_026 , CPhysics{.x= -11.29897689819336 , .y = 0.0, .z = -18.603656768798828});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_026 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.026.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_027 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_027 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_027 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_027 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_027 , CPhysics{.x= 4.415131568908691 , .y = 0.0, .z = -11.433141708374023});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_027 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.027.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_028 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_028 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_028 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_028 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_028 , CPhysics{.x= 10.060005187988281 , .y = 0.0, .z = -18.527374267578125});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_028 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.028.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_029 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_029 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_029 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_029 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_029 , CPhysics{.x= -18.62205696105957 , .y = 0.0, .z = -33.783790588378906});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_029 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.029.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_030 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_030 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_030 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_030 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_030 , CPhysics{.x= -10.688720703125 , .y = 0.0, .z = -48.88764190673828});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_030 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.030.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_031 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_031 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_031 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_031 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_031 , CPhysics{.x= -14.731670379638672 , .y = 0.0, .z = -26.460710525512695});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_031 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.031.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto2_032 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto2_032 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto2_032 );
		man_e.addTagToEntity<TWall>(ColiLaberinto2_032 );
		man_e.defineCMP<CPhysics>(ColiLaberinto2_032 , CPhysics{.x= 22.188854217529297 , .y = 0.0, .z = -33.7075080871582});
		man_e.defineCMP<CRenderGL>(ColiLaberinto2_032 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto2/ColiLaberinto2.032.obj", glm::vec3(0,0,0))});

	}

	if(a == 3){

		auto& maiz = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
		man_e.addTagToEntity<TInstance>(maiz);
		man_e.addTagToEntity<TNotRenderizable>(maiz);
		man_e.defineCMP<CRenderGL>(maiz, CRenderGL{.modelMatrix= Model("assets/level1/CornLP.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/levelmaze/laberinto3/instances_lab.txt",.iscorn=true});
		auto& ColiLaberinto3 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3 , CPhysics{.x= -15.469999313354492 , .y = 0.0, .z = -3.8446156978607178});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_001 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_001 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_001 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_001 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_001 , CPhysics{.x= -3.399717330932617 , .y = 0.0, .z = 2.392226457595825});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_001 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.001.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_003 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_003 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_003 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_003 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_003 , CPhysics{.x= 3.020688056945801 , .y = 0.0, .z = 2.392226457595825});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_003 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.003.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_002 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_002 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_002 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_002 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_002 , CPhysics{.x= -3.399717330932617 , .y = 0.0, .z = -62.508544921875});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_002 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.002.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_005 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_005 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_005 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_005 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_005 , CPhysics{.x= 3.020688056945801 , .y = 0.0, .z = -62.508544921875});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_005 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.005.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_004 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_004 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_004 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_004 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_004 , CPhysics{.x= -0.09416218101978302 , .y = 0.0, .z = -68.72808837890625});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_004 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.004.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_006 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_006 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_006 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_006 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_006 , CPhysics{.x= -0.09416218101978302 , .y = 0.0, .z = 8.621926307678223});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_006 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.006.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_007 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_007 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_007 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_007 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_007 , CPhysics{.x= 14.847557067871094 , .y = 0.0, .z = -3.8446156978607178});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_007 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.007.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_008 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_008 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_008 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_008 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_008 , CPhysics{.x= 14.847557067871094 , .y = 0.0, .z = -56.4609489440918});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_008 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.008.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_009 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_009 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_009 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_009 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_009 , CPhysics{.x= -14.810920715332031 , .y = 0.0, .z = -56.4609489440918});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_009 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.009.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_010 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_010 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_010 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_010 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_010 , CPhysics{.x= 26.38140869140625 , .y = 0.0, .z = -30.207704544067383});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_010 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.010.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_011 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_011 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_011 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_011 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_011 , CPhysics{.x= -26.25689697265625 , .y = 0.0, .z = -30.207704544067383});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_011 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.011.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_012 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_012 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_012 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_012 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_012 , CPhysics{.x= -18.75582504272461 , .y = 0.0, .z = -41.332176208496094});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_012 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.012.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_013 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_013 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_013 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_013 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_013 , CPhysics{.x= -11.44545841217041 , .y = 0.0, .z = -15.0784273147583});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_013 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.013.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_014 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_014 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_014 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_014 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_014 , CPhysics{.x= -18.75582504272461 , .y = 0.0, .z = -7.958766937255859});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_014 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.014.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_015 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_015 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_015 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_015 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_015 , CPhysics{.x= -18.75582504272461 , .y = 0.0, .z = -22.51593017578125});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_015 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.015.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_016 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_016 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_016 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_016 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_016 , CPhysics{.x= 11.502735137939453 , .y = 0.0, .z = -15.141996383666992});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_016 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.016.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_017 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_017 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_017 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_017 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_017 , CPhysics{.x= 3.620253086090088 , .y = 0.0, .z = -7.895198822021484});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_017 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.017.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_018 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_018 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_018 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_018 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_018 , CPhysics{.x= 11.502735137939453 , .y = 0.0, .z = -29.953432083129883});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_018 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.018.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_019 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_019 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_019 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_019 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_019 , CPhysics{.x= 11.502735137939453 , .y = 0.0, .z = -45.273414611816406});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_019 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.019.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_020 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_020 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_020 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_020 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_020 , CPhysics{.x= 18.74953269958496 , .y = 0.0, .z = -52.52021026611328});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_020 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.020.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_021 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_021 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_021 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_021 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_021 , CPhysics{.x= 3.6202526092529297 , .y = 0.0, .z = -52.52021026611328});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_021 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.021.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_022 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_022 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_022 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_022 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_022 , CPhysics{.x= -11.509027481079102 , .y = 0.0, .z = -52.52021026611328});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_022 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.022.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_023 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_023 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_023 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_023 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_023 , CPhysics{.x= -3.6265454292297363 , .y = 0.0, .z = -45.20984649658203});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_023 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.023.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_024 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_024 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_024 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_024 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_024 , CPhysics{.x= 3.5566844940185547 , .y = 0.0, .z = -37.83591079711914});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_024 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.024.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_025 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_025 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_025 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_025 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_025 , CPhysics{.x= 0.27655506134033203 , .y = 0.0, .z = -33.79296112060547});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_025 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.025.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_026 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_026 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_026 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_026 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_026 , CPhysics{.x= -6.741395950317383 , .y = 0.0, .z = -26.54616355895996});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_026 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.026.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_027 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_027 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_027 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_027 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_027 , CPhysics{.x= 19.347074508666992 , .y = 0.0, .z = -26.54616355895996});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_027 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.027.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_028 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_028 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_028 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_028 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_028 , CPhysics{.x= 19.347074508666992 , .y = 0.0, .z = -41.65001678466797});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_028 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.028.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_029 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_029 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_029 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_029 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_029 , CPhysics{.x= -11.013193130493164 , .y = 0.0, .z = -41.65001678466797});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_029 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.029.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_030 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_030 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_030 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_030 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_030 , CPhysics{.x= -2.851011276245117 , .y = 0.0, .z = -18.689111709594727});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_030 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.030.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_031 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_031 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_031 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_031 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_031 , CPhysics{.x= -0.028574466705322266 , .y = 0.0, .z = -11.518596649169922});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_031 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.031.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_032 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_032 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_032 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_032 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_032 , CPhysics{.x= 21.940664291381836 , .y = 0.0, .z = -11.518596649169922});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_032 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.032.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_033 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_033 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_033 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_033 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_033 , CPhysics{.x= -22.76063346862793 , .y = 0.0, .z = -18.612831115722656});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_033 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.033.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto3_034 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto3_034 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto3_034 );
		man_e.addTagToEntity<TWall>(ColiLaberinto3_034 );
		man_e.defineCMP<CPhysics>(ColiLaberinto3_034 , CPhysics{.x= 15.68553352355957 , .y = 0.0, .z = -18.612831115722656});
		man_e.defineCMP<CRenderGL>(ColiLaberinto3_034 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto3/ColiLaberinto3.034.obj", glm::vec3(0,0,0))});

	}
	
	if(a == 4){
		auto& maiz = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
		man_e.addTagToEntity<TInstance>(maiz);
		man_e.addTagToEntity<TNotRenderizable>(maiz);
		man_e.defineCMP<CRenderGL>(maiz, CRenderGL{.modelMatrix= Model("assets/level1/CornLP.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/levelmaze/laberinto4/instances_lab.txt",.iscorn=true});
		auto& ColiLaberinto4 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4 , CPhysics{.x= -15.469999313354492 , .y = 0.0, .z = -3.8446156978607178});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_012 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_012 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_012 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_012 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_012 , CPhysics{.x= -15.469999313354492 , .y = 0.0, .z = -3.8446156978607178});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_012 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.012.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_011 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_011 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_011 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_011 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_011 , CPhysics{.x= 15.012308120727539 , .y = 0.0, .z = -3.8446156978607178});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_011 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.011.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_010 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_010 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_010 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_010 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_010 , CPhysics{.x= 25.99692153930664 , .y = 0.0, .z = -30.848464965820312});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_010 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.010.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_009 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_009 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_009 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_009 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_009 , CPhysics{.x= -25.905384063720703 , .y = 0.0, .z = -30.848464965820312});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_009 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.009.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_008 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_008 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_008 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_008 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_008 , CPhysics{.x= -15.469999313354492 , .y = 0.0, .z = -56.04351043701172});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_008 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.008.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_007 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_007 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_007 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_007 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_007 , CPhysics{.x= 15.012308120727539 , .y = 0.0, .z = -56.04351043701172});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_007 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.007.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_006 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_006 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_006 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_006 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_006 , CPhysics{.x= -0.09416218101978302 , .y = 0.0, .z = 8.621926307678223});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_006 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.006.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_005 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_005 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_005 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_005 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_005 , CPhysics{.x= -3.399717330932617 , .y = 0.0, .z = 2.392226457595825});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_005 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.005.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_004 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_004 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_004 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_004 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_004 , CPhysics{.x= 3.020688056945801 , .y = 0.0, .z = 2.392226457595825});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_004 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.004.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_003 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_003 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_003 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_003 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_003 , CPhysics{.x= -3.399717330932617 , .y = 0.0, .z = -62.508544921875});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_003 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.003.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_002 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_002 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_002 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_002 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_002 , CPhysics{.x= 3.020688056945801 , .y = 0.0, .z = -62.508544921875});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_002 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.002.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_001 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_001 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_001 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_001 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_001 , CPhysics{.x= -0.09416218101978302 , .y = 0.0, .z = -68.72808837890625});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_001 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.001.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_013 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_013 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_013 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_013 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_013 , CPhysics{.x= -3.7530715465545654 , .y = 0.0, .z = -11.442310333251953});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_013 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.013.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_014 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_014 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_014 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_014 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_014 , CPhysics{.x= 7.689239978790283 , .y = 0.0, .z = -18.582313537597656});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_014 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.014.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_015 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_015 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_015 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_015 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_015 , CPhysics{.x= -7.506149768829346 , .y = 0.0, .z = -26.45462417602539});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_015 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.015.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_016 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_016 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_016 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_016 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_016 , CPhysics{.x= 22.33540153503418 , .y = 0.0, .z = -26.45462417602539});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_016 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.016.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_017 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_017 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_017 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_017 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_017 , CPhysics{.x= 7.689242362976074 , .y = 0.0, .z = -33.594627380371094});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_017 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.017.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_018 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_018 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_018 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_018 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_018 , CPhysics{.x= -15.01230525970459 , .y = 0.0, .z = -33.594627380371094});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_018 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.018.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_019 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_019 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_019 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_019 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_019 , CPhysics{.x= 18.216167449951172 , .y = 0.0, .z = -48.69847869873047});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_019 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.019.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_020 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_020 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_020 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_020 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_020 , CPhysics{.x= -11.076152801513672 , .y = 0.0, .z = -41.46693801879883});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_020 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.020.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_021 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_021 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_021 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_021 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_021 , CPhysics{.x= -22.152311325073242 , .y = 0.0, .z = -48.69847869873047});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_021 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.021.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_022 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_022 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_022 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_022 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_022 , CPhysics{.x= -11.533845901489258 , .y = 0.0, .z = -49.4307861328125});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_022 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.022.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_023 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_023 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_023 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_023 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_023 , CPhysics{.x= -3.5699968338012695 , .y = 0.0, .z = -45.76924514770508});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_023 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.023.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_024 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_024 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_024 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_024 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_024 , CPhysics{.x= 3.4784674644470215 , .y = 0.0, .z = -45.03693771362305});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_024 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.024.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_025 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_025 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_025 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_025 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_025 , CPhysics{.x= 11.442316055297852 , .y = 0.0, .z = -45.03693771362305});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_025 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.025.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_026 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_026 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_026 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_026 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_026 , CPhysics{.x= 18.673856735229492 , .y = 0.0, .z = -37.896934509277344});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_026 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.026.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_027 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_027 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_027 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_027 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_027 , CPhysics{.x= -18.7653865814209 , .y = 0.0, .z = -37.53078079223633});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_027 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.027.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_028 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_028 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_028 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_028 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_028 , CPhysics{.x= -18.7653865814209 , .y = 0.0, .z = -19.406158447265625});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_028 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.028.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_029 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_029 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_029 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_029 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_029 , CPhysics{.x= -11.442306518554688 , .y = 0.0, .z = -21.877696990966797});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_029 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.029.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_032 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_032 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_032 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_032 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_032 , CPhysics{.x= 3.44 , .y = 0.0, .z = -7.81});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_032 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.029.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_030 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_030 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_030 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_030 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_030 , CPhysics{.x= 11.350778579711914 , .y = 0.0, .z = -26.637699127197266});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_030 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.030.obj", glm::vec3(0,0,0))});
		auto& ColiLaberinto4_031 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision>();
		man_e.addTagToEntity<TNotRenderizable>(ColiLaberinto4_031 );
		man_e.addTagToEntity<TCollisionable>(ColiLaberinto4_031 );
		man_e.addTagToEntity<TWall>(ColiLaberinto4_031 );
		man_e.defineCMP<CPhysics>(ColiLaberinto4_031 , CPhysics{.x= 18.673858642578125 , .y = 0.0, .z = -14.73769474029541});
		man_e.defineCMP<CRenderGL>(ColiLaberinto4_031 , CRenderGL{.modelMatrix = Model("assets/levelmaze/laberinto4/ColiLaberinto4.031.obj", glm::vec3(0,0,0))});

	}	

	auto& cuadrado = man_e.createEntity_withCMPS< CRenderGL, CPhysics>();
	man_e.addTagToEntity<TInstance>(cuadrado);
	man_e.addTagToEntity<TNotRenderizable>(cuadrado);
	man_e.defineCMP<CRenderGL>(cuadrado, CRenderGL{.modelMatrix= Model("assets/level1/CornLP.obj", glm::vec3(0,-1,0)),.amount=0, .instancePath="assets/levelmaze/lvlmazes.txt",.iscorn=true});
	
	/*-------- carteles lvl maze -----------*/
	auto& cartel_tumba = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CInformation>();
	man_e.addTagToEntity<TDescription>(cartel_tumba);
	man_e.addTagToEntity<TCollisionable>(cartel_tumba );
	man_e.addTagToEntity<TScaleBoundingBox>(cartel_tumba);
	//man_e.addTagToEntity<TWall>(cartel_tumba);
	man_e.defineCMP<CPhysics>(cartel_tumba , CPhysics{.x= -1.50 , .y = 0.0, .z = -58.51});
	man_e.defineCMP<CRenderGL>(cartel_tumba , CRenderGL{.modelMatrix = Model("assets/level1/Cartel_Der.obj", glm::vec3(0,0,0))});
	man_e.getEntityCMP<CRenderGL>(cartel_tumba).modelMatrix.Rotate(90, 0, 1, 0);

	auto& cartel_casa = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CInformation>();
	man_e.addTagToEntity<TDescription>(cartel_casa);
	man_e.addTagToEntity<TCollisionable>(cartel_casa );
	man_e.addTagToEntity<TScaleBoundingBox>(cartel_casa);
	//man_e.addTagToEntity<TWall>(cartel_casa);
	man_e.defineCMP<CPhysics>(cartel_casa , CPhysics{.x= -1.54 , .y = 0.0, .z = 2.82});
	man_e.defineCMP<CRenderGL>(cartel_casa , CRenderGL{.modelMatrix = Model("assets/level1/Cartel_Izq.obj", glm::vec3(0,0,0))});
	man_e.getEntityCMP<CRenderGL>(cartel_casa).modelMatrix.Rotate(90, 0, 1, 0);

	auto& transitionmazeto2 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CIDLvl>();
	man_e.addTagToEntity<TNotRenderizable>(transitionmazeto2 );
	man_e.addTagToEntity<TCollisionable>(transitionmazeto2 );
	man_e.addTagToEntity<TTransition>(transitionmazeto2);
	man_e.defineCMP<CPhysics>(transitionmazeto2 , CPhysics{.x= -0.09 , .y = 0.0, .z = 10.5});
	man_e.defineCMP<CRenderGL>(transitionmazeto2 , CRenderGL{.modelMatrix = Model("assets/level5/Transitionlvl5to2.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CIDLvl>(transitionmazeto2, CIDLvl{.lvlid = 2});

	//esta transicion tiene que ir al maze
	auto& transitionmazeto4 = man_e.createEntity_withCMPS<CRenderGL, CPhysics, CCollision, CIDLvl>();
	man_e.addTagToEntity<TNotRenderizable>(transitionmazeto4 );
	man_e.addTagToEntity<TCollisionable>(transitionmazeto4 );
	man_e.addTagToEntity<TTransition>(transitionmazeto4);
	man_e.defineCMP<CPhysics>(transitionmazeto4 , CPhysics{.x= -0.09 , .y = 0.0, .z = -70.6});
	man_e.defineCMP<CRenderGL>(transitionmazeto4 , CRenderGL{.modelMatrix = Model("assets/level5/Transitionlvl5to2.obj", glm::vec3(0,0,0))});
	man_e.defineCMP<CIDLvl>(transitionmazeto4, CIDLvl{.lvlid = 4});

	man_e.defineCMP<CInformation>(cartel_tumba, CInformation{.type_of_text = 0, .description{"To the tomb"}});
	man_e.defineCMP<CInformation>(cartel_casa, CInformation{.type_of_text = 0, .description{"To the house"}});


	std::cout << "Entities level maze : " << man_e.getEntityArray().size() <<"\n";

}