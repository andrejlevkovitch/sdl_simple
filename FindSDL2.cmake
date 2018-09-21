# find sdl2 and modules

include(FindPackageHandleStandardArgs)

find_path(SDL2_INCLUDE_DIR SDL.h PATH_SUFFIXES SDL2)

if(SDL2_USE_STATIC_LIBS STREQUAL ON)
  exec_program(sdl2-config ARGS --static-libs OUTPUT_VARIABLE SDL2_LIBRARY
    RETURN_VALUE SDL2_CONFIG_RETVAL)
  if(SDL2_CONFIG_RETVAL)
    message(ERROR "Can't be linked static, becose not found sdl2-config")
  else()
  endif()
  find_library(SDL2_IMAGE_LIBRARY libSDL2_image.a)
else()
  find_library(SDL2_LIBRARY SDL2)
  find_library(SDL2_IMAGE_LIBRARY SDL2_image)
endif()

find_package_handle_standard_args(SDL2 FOUND_VAR SDL2_FOUND
  REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR)
