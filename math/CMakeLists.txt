
set(BonfireMath_HEADERS
	"include/math/vector3.hpp"
	"include/math/vector2.hpp"
	"include/math/vector4.hpp"
	"include/math/matrix3.hpp"
	"include/math/matrix4.hpp"
	"include/math/transformation.hpp"
	"include/math/face.hpp"
)

add_library(BonfireMath INTERFACE ${BonfireMath_HEADERS})

target_include_directories(BonfireMath INTERFACE "include/")
