#ExternalProject 관련 명령어셋 추가
#include : add ExternalProject 기능사용
include(ExternalProject)

#dependency variable setting
#PROJECT_BINARY_DIR : build folder
 
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

#ExternalProject_Add : ExternalProject's function
#git clone and excute cmakelists
ExternalProject_Add(
    dep_spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.x"
    GIT_SHALLOW 1 #GIT_SHALLOW = true, commit log omitted
    UPDATE_COMMAND "" #no update
    PATCH_COMMAND "" #no modify source by command
    #-D:definition
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
    TEST_COMMAND ""
)
#glfw
ExternalProject_Add(
    dep_glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.3.2"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
    TEST_COMMAND ""
    )
#glad
ExternalProject_Add(
    dep_glad
    GIT_REPOSITORY "https://github.com/Dav1dde/glad"
    GIT_TAG "v0.1.34"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLAD_INSTALL=ON
    TEST_COMMAND ""
    )
set(DEP_LIST ${DEP_LIST} dep_glfw)
set(DEP_LIST ${DEP_LIST} dep_spdlog)
set(DEP_LIST ${DEP_LIST} dep_glad)
# Dependency 리스트 및 라이브러리 파일 리스트 추가
# 리스트 형식으로 사용할때 set(DEP_LIST ${DEP_LIST} A B C D) : A B C D 값이 들어감
# set(DEP_LIST ${DEP_LIST} dep_spdlog)
# dep_libs는 실제 라이브러리 연결시 사용(.lib파일명)
set(DEP_LIBS ${DEP_LIBS} glfw3)
set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>) #$<$<CONFIG:Debug>:d> : 빌드단계서 변환, d를 붙일지 말지 결정, .lib 확장자를 뺀 이름을 넣어줌, spdlogd로 들어감
set(DEP_LIBS ${DEP_LIBS} glad)
