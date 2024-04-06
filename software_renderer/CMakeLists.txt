set(SoftwareRenderer_SOURCES


	"main.cpp"
)

add_executable(SoftwareRenderer ${SoftwareRenderer_SOURCES})

target_link_libraries(SoftwareRenderer PRIVATE
	SDL2::SDL2
)
