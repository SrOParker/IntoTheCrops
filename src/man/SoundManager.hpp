#pragma once
#include <fmod.h>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <fsbank_errors.h>
#include <stdio.h>
#include <iostream>   
#include <string>
#include <map>
#include <glm/vec3.hpp>
class SoundManager{

    private:
        FMOD::Studio::System * soundSystem;
        FMOD::System* low_sys;
        FMOD::Studio::Bus*  masterBus;
        FMOD::Studio::Bank* master;
        FMOD::Studio::Bank* stringmaster; 
        FMOD::Studio::Bank* hardfx;
        FMOD::Studio::Bank* characters;
        FMOD::Studio::Bank* enviroment;
        std::map<std::string, FMOD::Studio::EventDescription*> eventMapDesc;
        std::map<std::string, FMOD::Studio::EventInstance*>    eventInstancesMap;
        float lastx, lasty, lastz;
        glm::vec3 look, up;

        void createEvent(     const std::string&);

    public:
        SoundManager();
        ~SoundManager(); 
        void drop();
        
        

        void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);

        void setParameter(    const std::string , const std::string, float);
        
        void initBanks(       const std::string&, const std::string&); 
        bool check(           const std::string );
        void playSound(       const std::string);
        void stopOne(         const std::string );
        void stopSteps();
        bool state(           FMOD::Studio::EventInstance* );
        void walking(         bool , uint8_t );
        void set3DProp(       const std::string , const float , const float , const float );
        void setListenerProp( const  float, const float, const float, glm::vec3, glm::vec3);
        void update(          float, float, float ,glm::vec3 , glm::vec3 );
        void update(); 
        void setVolume(       float);
        void stopAll(); 

};
