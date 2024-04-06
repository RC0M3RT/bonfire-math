
set(BonfireMath_HEADERS
	"include/math/vector3.hpp"
	"include/math/matrix3.hpp"
	"include/math/print_helpers.hpp"
)

add_library(BonfireMath INTERFACE ${BonfireMath_HEADERS})

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(BonfireMath INTERFACE -Weverything
	#-Wno-switch-enum
	#-Wno-signed-enum-bitfield
	#-Wno-deprecated-register
	-Wno-c++98-compat
	-Wno-c++98-compat-pedantic
	-Wno-c++98-c++11-compat-pedantic
	#-Wno-nested-anon-types
	#-Wno-gnu-anonymous-struct
	#-Wno-missing-prototypes
	#-Wno-documentation
	#-Wno-documentation-unknown-command
	#-Wno-weak-vtables
	#-Wno-unused-const-variable
	#-Wno-format-nonliteral
	#-Wno-global-constructors
	#-Wno-exit-time-destructors
	#-Wno-error=padded
	-Wno-float-equal # comparing floating point with == or != is unsafe [-Wfloat-equal]
  )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
endif()

target_include_directories(BonfireMath INTERFACE "include/")
