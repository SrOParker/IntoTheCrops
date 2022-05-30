#pragma once
#include <chrono>
namespace teo_time
{
    using time = std::chrono::duration<float>;
    struct Timer{
        
        Timer();
        teo_time::time getElapsedTime(); 
        void setTimer(); 
        std::chrono::system_clock::time_point m_start;
        std::chrono::system_clock::time_point   m_end;
    };
}