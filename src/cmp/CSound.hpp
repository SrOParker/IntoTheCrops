#pragma once

struct SoundManager; 
struct CSound { 
    SoundManager* s_mgr;
    const char* name;
//  std::string name; 
    float eventvalue; 
};