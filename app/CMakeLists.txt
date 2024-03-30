
set(BonfireApp_SOURCES


	"main.cpp"
)

add_executable(BonfireApp ${BonfireApp_SOURCES})

target_link_libraries(BonfireApp PRIVATE GLEW::glew glfw imgui::imgui BonfireMath)
