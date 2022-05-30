#pragma once
#include <array>
struct CInformation   { 
    int type_of_text{};
    const char* entity_name{"no-name"};
    const char* description{"no-description"};
    
    std::array<const char*, 14> text_list{"","","","","","","","","","","","",""};
    const char* descriptionPickable{"no-pickable"};
    int times_to_print_text{200};
    //type_of_text
    // 0  -->  one text line
    // 1  -->  multiple text lines
    // 2  -->  conversation text
    // 3  -->  one line one time 

};