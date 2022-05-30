#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <array>
struct DecisionTree;

struct CIA{

    //DecisionTree dt{};
    DecisionTree* dt;
    
    //Pathfinding WayPoints
    static constexpr glm::vec3 invalid{};
    static constexpr uint8_t tot_patrol{12};
    std::array<glm::vec3, tot_patrol> targets;
    float arrival_radius{0.05f};
    uint8_t current{};


    //Steering
    float max_vel{0.04};
    float max_range{15};
    static constexpr float velocity{1.f};
    static constexpr float ttarrive{0.5f};


    //Rotation 
    glm::vec3 face {-1, 0, 0};
    glm::mat4 origin{};
    double prevangl{};

};