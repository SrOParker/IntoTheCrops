#include "Information_system.hpp"






void InformationSystem::update(Manentity_type& EM){
	auto update_one_entity = [&](Entity& e, CInformation& cinf){

    };
	EM.foreach<SYSCMPs, SYSTAGs>(update_one_entity);
};