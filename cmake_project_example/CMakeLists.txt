cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME cmake_project_example)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "Hello, Opengl!")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} src/main.cpp) #실행파일이름, 실행파일재료
 
include(Dependency.cmake) #dependency.cmake 파일을 포함

# 라이브러리들을 현재 프로젝트에 적용하기(spdlog include / lib 를 연결시키기)
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

#define A B 코드 효과와 동일
target_compile_definitions(${PROJECT_NAME} PUBLIC
WINDOW_NAME="${WINDOW_NAME}"
WINDOW_WIDTH=${WINDOW_WIDTH}
WINDOW_HEIGHT=${WINDOW_HEIGHT}
)
#dependency들이 먼저 빌드될수있도록
add_dependencies(${PROJECT_NAME} ${DEP_LIST})
