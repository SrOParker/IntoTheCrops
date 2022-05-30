#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

struct myImGui{
    myImGui( );
    ~myImGui();
    void init(GLFWwindow* window);
    void update();
    void Render(GLFWwindow* window);
    void createWindow1();
    const char* getglslVersion();
    void newFrame(); 

    private: 
        ImVec4 clear_color;
        const char* glsl_version;
};