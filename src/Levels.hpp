#pragma once
#include "man/utils/types.hpp"

struct Sys;
struct EngineGL; 
struct Levels{
    
    void clearLevel(Manentity_type& man_e, Sys& systems, EngineGL& GL);
    void emptyAll(Manentity_type& man_e, Sys& systems, EngineGL& GL);
    
    void load_lvl_1(Manentity_type& man_e, Sys& systems, EngineGL& GL);
    void checkStatus_lvl1(Manentity_type& man_e, EngineGL& GL);
    void InitSoundsLvl_1(SoundManager& );
    void load_lv_1_lights(Manentity_type& man_e,EngineGL& GL);

    void load_lvl_2(Manentity_type& man_e, Sys& systems, EngineGL& GL);
    void checkStatus_lvl2(Manentity_type& man_e, Sys& systems, EngineGL& GL);
    void InitSoundsLvl_2(SoundManager& );

    void load_lvl_3(Manentity_type& man_e, Sys& systems, EngineGL& GL); 
    void InitSoundsLvl_3(Manentity_type& man_e, SoundManager& ); 
    void checkStatus_lvl3(Manentity_type& man_e, EngineGL& GL);
    
    void load_lvl_4(Manentity_type& man_e, Sys& systems, EngineGL& GL); 
    void InitSoundsLvl_4(SoundManager& );
    void checkStatus_lvl4(Manentity_type& man_e, EngineGL& GL);

    void load_lvl_5(Manentity_type& man_e, Sys& systems, EngineGL& GL); 
    void InitSoundsLvl_5(SoundManager& );
    void checkStatus_lvl5(Manentity_type& man_e, EngineGL& GL);
    
    void load_lvl_Sotano(Manentity_type& man_e, Sys& systems, EngineGL& GL);
    void InitSoundsLvl_Sotano(SoundManager& );
    void checkStatus_lvl_Sotano(Manentity_type& man_e, EngineGL& GL);

    void load_lvl_Y(Manentity_type& man_e, Sys& systems, EngineGL& GL);
    void InitSoundsLvl_Y(SoundManager& );
    void checkStatus_lvlY(Manentity_type& man_e, EngineGL& GL);

    void load_lvl_maze(Manentity_type& man_e, Sys& systems, EngineGL& GL);
    void InitSoundsLvl_maze(SoundManager& );
    void checkStatus_lvl_Maze(Manentity_type& man_e, EngineGL& GL);

    void save_inventory(Manentity_type& man_e,Sys& systems, EngineGL& GL);
    void reset_game_variables(Manentity_type& man_e,Sys& systems, EngineGL& GL);
    
    //.
    //.
    //.    
};