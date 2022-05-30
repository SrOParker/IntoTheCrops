
#include "SoundManager.hpp"


void SoundManager::ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << "\n";
        exit(-1);
    }
}
#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

SoundManager::SoundManager(){
    //std::cout << "Creando SoundManager\n"; 
    ERRCHECK(FMOD::Studio::System::create(&soundSystem));
    ERRCHECK(soundSystem->getCoreSystem(&low_sys));
    ERRCHECK(low_sys->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0)); 
    ERRCHECK(low_sys->setOutput(FMOD_OUTPUTTYPE_AUTODETECT)); 
                                                                //    FMOD_INIT_NORMAL de momento usamos esta para irrlichts
                                                                //    FMOD_INIT_3D_RIGHTHANDED esta se usará en opengl
    ERRCHECK(soundSystem->initialize(48, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_3D_RIGHTHANDED, 0));


    ERRCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &master));

    ERRCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringmaster));
    
    ERRCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/HardFX.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &hardfx));

    ERRCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Characters.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &characters));
        
    ERRCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Enviroment.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &enviroment));

    ERRCHECK(soundSystem->getBus("Bus:/", &masterBus));

    createEvent("event:/Music/MainMenu");
    createEvent("event:/Music/PantallaCarga");
    createEvent("event:/Enviroment/Ambiente");
    createEvent("event:/Enviroment/AmbienteInterior");
    createEvent("event:/Character/Fire (Oil)");
    createEvent("event:/Character/Pasos");
    createEvent("event:/Character/creepy");
    createEvent("event:/Character/LowHp");
    createEvent("event:/HardFX/TV");
    createEvent("event:/HardFX/coche");
    createEvent("event:/HardFX/Llave");
    createEvent("event:/HardFX/Telefono");
    createEvent("event:/HardFX/PuertaBloqueada");
    createEvent("event:/HardFX/Door");
    createEvent("event:/HardFX/LlamarPuerta");
    createEvent("event:/HardFX/CerrarPuerta");
    createEvent("event:/HardFX/Quemar");
    createEvent("event:/HardFX/PuertaIglesia");
    createEvent("event:/HardFX/SlideDoor");
    createEvent("event:/HardFX/cadenas");
    createEvent("event:/UI/Pop");
    createEvent("event:/Music/End");
    createEvent("event:/Music/MainTheme");

    setVolume(50); 
    lastx = 0;
    lasty = 1.5;
    lastz = -4; 
    look  = {0,0,1};
    up    = {0,1,0};
    setListenerProp(lastx, lasty, lastz, look, up);

}

SoundManager::~SoundManager(){
    drop();
}

void SoundManager::drop(){
    std::cout << "\nDeleting Sound_Manager\n";

    for(auto instance : eventInstancesMap)
        ERRCHECK(instance.second->release());
    
    for(auto description : eventMapDesc)
        ERRCHECK(description.second->releaseAllInstances());
        
    ERRCHECK(soundSystem->unloadAll());
    //Creo que falta liberar los eventos

    ERRCHECK(soundSystem->release());
    soundSystem = nullptr;
    
    if(!soundSystem)
        std::cout << "Sound_Manager deleted\n\n";

}

void SoundManager::initBanks(const std::string &locmaster, const std::string& locstringmaster){

    //std::cout << "Init de los bancos\n"; 
    FMOD::Studio::Bank* masterBank = nullptr;
    ERRCHECK(soundSystem->loadBankFile(locmaster.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank));
    FMOD::Studio::Bank* stringsBank = nullptr;
    ERRCHECK(soundSystem->loadBankFile(locstringmaster.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank));
    
}

void SoundManager::createEvent(const std::string &path){
    
    //std::cout << "\nCreando Evento: " << path << "\n";
    FMOD::Studio::EventDescription* eventDescription = nullptr;

    ERRCHECK(soundSystem->getEvent(path.c_str(), &eventDescription));
    
    FMOD::Studio::EventInstance* musica = nullptr;
    ERRCHECK(eventDescription->createInstance(&musica));
    eventMapDesc[path] = eventDescription;
    eventInstancesMap[path] = musica;
       
    if(path.find("Ambiente") != std::string::npos || path.find("AmbienteInterior") != std::string::npos){

        //std::cout << "La cadena tiene Ambiente\n";
        FMOD_STUDIO_PARAMETER_DESCRIPTION paramDesc;

        if(path.find("AmbienteInterior") != std::string::npos){

            //Iniciarlizar valor de interior
            //std::cout << "Iniciando valor AmbienteInterior\n";    
            ERRCHECK( eventDescription->getParameterDescriptionByName("AmbienteInterior", &paramDesc) );

        }else{

            //Inicializar valor de exterior
            //std::cout << "Iniciando valor Ambiente\n";
            ERRCHECK( eventDescription->getParameterDescriptionByName("Ambiente", &paramDesc) );

        }
        
        FMOD_STUDIO_PARAMETER_ID surfaceID = paramDesc.id;    
        float surfaceParameterValue = 2.0f;
        ERRCHECK( musica->setParameterByID(surfaceID, surfaceParameterValue) );
    
    }
    //std::cout << "añadido: " << eventInstancesMap.find(path)->first << "\n";
    //ERRCHECK(musica->start());
    
}

void SoundManager::stopAll(){
    for(auto instance : eventInstancesMap){
        if (instance.first.compare("event:/Music/End") != 0){
            instance.second->stop(FMOD_STUDIO_STOP_IMMEDIATE);
        }
    }
}

void SoundManager::stopOne(const std::string name){
    auto instancia = eventInstancesMap.find(name);
    ERRCHECK(instancia->second->stop(FMOD_STUDIO_STOP_IMMEDIATE));
}

void SoundManager::stopSteps(){
    auto instancia = eventInstancesMap.find("event:/Character/Pasos");
    instancia->second->stop(FMOD_STUDIO_STOP_IMMEDIATE); 
}

void SoundManager::playSound(const std::string name){
    auto instancia = eventInstancesMap.find(name);
    
    if(instancia == eventInstancesMap.end()){
        std::cout << "la instancia no existe en el mapa \n";
        return;
    }
    //std::cout << "entrosound\n" << name << "\n";
    ERRCHECK(instancia->second->start());

}

bool SoundManager::state(FMOD::Studio::EventInstance* event){
    bool exit;
    event->getPaused(&exit);
    return exit;
}

void SoundManager::setParameter(const std::string eventName, const std::string valueName, float value){

    auto evento = eventInstancesMap.find(eventName);

    if(evento == eventInstancesMap.end()){
        std::cout << "evento no encontrado\n";
        return;
    }
    
    ERRCHECK(evento->second->setParameterByName(valueName.c_str(), value, false));
    
}

void SoundManager::walking(bool walking, uint8_t surface){

    auto event = eventInstancesMap.find("event:/Character/Pasos");

    if(event == eventInstancesMap.end()){
        return;
    }
    auto andar = event->second;

    ERRCHECK(andar->start());

}

void SoundManager::set3DProp(const std::string name, const float x, const float y, const float z){

    //std::cout << "Creando parametros 3D para evento: " << name << "\n";
    auto event = eventInstancesMap.find(name);
    if(event == eventInstancesMap.end())
        return; 
    
    FMOD_VECTOR pos {x, y, z};
    FMOD_VECTOR vel {0.0f, 0.0f, 0.0f};
    FMOD_VECTOR forward {0.0f, 0.0f, 1.0f};
  	FMOD_VECTOR up {0.0f, 1.0f, 0.0f};
    FMOD_3D_ATTRIBUTES attributes {pos, vel, forward, up};
    ERRCHECK(event->second->set3DAttributes(&attributes));
}

void SoundManager::setListenerProp(const float x, const float y, const float z, glm::vec3 lookAt, glm::vec3 Up){

    FMOD_VECTOR pos     {x, y, z};
    FMOD_VECTOR vel     {0.0f, 0.0f, 0.0f};
    FMOD_VECTOR forward {lookAt.x, lookAt.y, lookAt.z};
  	FMOD_VECTOR up      {Up.x, Up.y, Up.z};
    FMOD_3D_ATTRIBUTES attributes {pos, vel, forward, up};
    ERRCHECK( soundSystem->setListenerAttributes(0, &attributes) );
}

void SoundManager::update(float x, float y, float z, glm::vec3 lookAt, glm::vec3 Up){		
    
    //Hay que hacer que no se actualice en todas las iteraciones del bucle, únicamente cuando haya un cambio en la posición del jugador
    if(x != lastx || y != lasty || z != lastz || lookAt != look || up != Up){
        setListenerProp(x, y, z , lookAt, Up);     
        lastx = x;
        lastz = z;
        lasty = y;

    }
    ERRCHECK(soundSystem->update());
}

void SoundManager::update(){		
    
    ERRCHECK(soundSystem->update());
}

void SoundManager::setVolume(float vol){
    //std::cout << "setteo el volumen del mbus a " << vol/100 << "\n";
    masterBus->setVolume(vol/100);
    update(); 
}