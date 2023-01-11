#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <spdlog/spdlog.h>


 //매크로 펑션 
 //using counter = long; long을 counter로 대체
 //##: klassNamePtr 로 만들어줌

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;


//std::optional 포인터 대신 쓸수있음
// 어떤 값을 string으로 표현한다고 했을때 그값이 아예 null일시와 ""일때를 구분할 수 없음
// string* 포인터로 리턴할시 동적할당이 일어나고 이를 잘해제해주어야함
//가장 큰 특징 : 아무것도 들고있지 않은 상태에서는 디폴트 객체를 가질 필요가 없다.
//즉 optional<Aclass> a; 시 아무것도 생성하지 않음
std::optional<std::string> LoadTextFile(const std::string& filename);

#endif