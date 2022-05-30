#pragma once
struct CPhysics { //quit quit quit t

    float x{}, y{}, z{};
    float vx{}, vy{}, vz{};

    float acelx{}, acely{}, acelz{};
    
    static constexpr double kMaxVel{ 0.03 };
    static constexpr double kMaxAc { kMaxVel/2.0  };
    

};