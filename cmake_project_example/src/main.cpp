#include <iostream>
#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>
int main(int argc, const char** argv)
{
    SPDLOG_INFO("hello, opengl");
    if(!glfwInit())
    {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw:{}", description);
        return -1;
    }
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if(!window)
    {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }
    //glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); //1/60초 동안 이벤트를 모으고 1/60초가 지나면 다시 while 루프
    }
    glfwTerminate();
    return 0;
}
//cmake 빌드 명령어
//cmake -Bbuild . -DCMAKE_BUILD_TYPE=Debug
//-B:빌드디렉토리(ex)build
// . :루트 디렉토리
//결과 : 비주얼스튜디오 프로젝트