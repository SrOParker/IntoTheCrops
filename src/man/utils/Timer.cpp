#include "Timer.hpp"

teo_time::Timer::Timer(){
    m_start = std::chrono::system_clock::now(); 
}

void teo_time::Timer::setTimer(){
    m_start = std::chrono::system_clock::now(); 
}

teo_time::time teo_time::Timer::getElapsedTime(){
    m_end   = std::chrono::system_clock::now(); 
    return m_end - m_start;
}
