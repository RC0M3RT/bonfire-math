
set(BonfireMath_HEADERS
	"include/math/vector3.hpp"
	"include/math/matrix3.hpp"
)

add_library(BonfireMath INTERFACE ${BonfireMath_HEADERS})

target_include_directories(BonfireMath INTERFACE "include/")
