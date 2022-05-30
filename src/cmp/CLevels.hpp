#pragma once
#include <array>
#include <vector>
#include <cstdint>
struct CLevels
{   //??????????????????????????????????????????????
    int actual{0};
    int contador_Y{0};
    //[0] -> first text first way ------
    //[1] -> second text second way -----
    //[2] -> door -------
    //[3] -> third text grave yard -----
    //[4] -> key-------
    //[5] -> burnable-------
    //[6] -> fourth text going to level 2 ------
    //[7] -> fiveth text going to level 2 ------
    std::vector<int> lvl_1_objects_status{};

    //[0] -> door
    //[1] -> window figure
    //[2] -> mailbox 
    //[3] -> KEY
    //[4] -> boca mailbox
    std::vector<int> lvl_2_objects_status{};

    //[0] -> salon puerta
    //[1] -> habitacion p
    //[2] -> aseo p
    //[3] -> p trasera
    //[4] -> fusible
    //[5] -> tlf
    //[6] -> farmer
    //[7] -> quemable
    //[8] -> enemy 1
    //[9] -> enemy 2
    //[10]-> enemy 3
    //[11]-> cuadro
    //[12]-> cajafuerte
    //[13]-> anillo
    std::vector<int> lvl_3_objects_status{};
    
    //[0] -> cuadro pickable
    //[1] -> texto dialogo
    //[2] -> texto spawn
    //[3] -> id enemigo1 al 6 todos seguidos
    std::vector<int> lvl_4_objects_status{};

    //[0] -> puerta del granero
    //[1] -> trampilla
    //[2] -> cizallas
    std::vector<int> lvl_5_objects_status{};
    
    //Si es 0 no tienes Rueda si
    //Si es id tienes Rueda y su id
    int lvl_Sotano_objects_status{0};

};
