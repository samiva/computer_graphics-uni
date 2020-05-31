# include_directories(${CG_SOURCE})
include_directories(${PROJ_INCLUDES})
# include_directories(${MY_INCLUDES})
include_directories(${SDL2_INCLUDE})
include_directories(${CMAKE_SOURCE_DIR})

set(ASSIGNMENT_INCLUDES 
                    ${MY_INCLUDES}/Assignment2.h
                    ${MY_INCLUDES}/Assignment3.h
                    ${MY_INCLUDES}/camera.h
                    ${MY_INCLUDES}/cube.h
                    ${MY_INCLUDES}/helpers.h
                    ${MY_INCLUDES}/MonkeyScene.h
                    ${MY_INCLUDES}/object.h
                    ${MY_INCLUDES}/vertex.h
                    )

set(ASSIGNMENT_SRC                         
                    ${MY_SOURCE}/Assignment2.cpp
                    ${MY_SOURCE}/Assignment3.cpp
                    ${MY_SOURCE}/camera.cpp
                    ${MY_SOURCE}/cube.cpp
                    ${MY_SOURCE}/helpers.cpp
                    ${MY_SOURCE}/MonkeyScene.cpp
                    ${MY_SOURCE}/object.cpp
                    )

set(CG_INC ${CG_SOURCE}/debugmessagecallback.h
                    ${CG_SOURCE}/examplescene1.h
                    ${CG_SOURCE}/examplescene2.h
                    ${CG_SOURCE}/examplescene3.h
                    ${CG_SOURCE}/examplescene4.h
                    ${CG_SOURCE}/objparser.h
                    ${CG_SOURCE}/scene.h
                    ${CG_SOURCE}/sdlwrapper.h
                    ${CG_SOURCE}/shaderprogram.h
                    ${CG_SOURCE}/streamredirector.h
                    ${CG_SOURCE}/texture.h)

set(CG_SRC ${CG_SOURCE}/debugmessagecallback.cpp
                    ${CG_SOURCE}/examplescene1.cpp
                    ${CG_SOURCE}/examplescene2.cpp
                    ${CG_SOURCE}/examplescene3.cpp
                    ${CG_SOURCE}/examplescene4.cpp
                    ${CG_SOURCE}/objparser.cpp
                    ${CG_SOURCE}/sdlwrapper.cpp
                    ${CG_SOURCE}/shaderprogram.cpp
                    ${CG_SOURCE}/texture.cpp
		    ${CG_SOURCE}/main.cpp)


source_group("include" FILES ${ASSIGNMENT_INCLUDES})
source_group("include" FILES ${CG_INC})
source_group("source" FILES ${ASSIGNMENT_SRC} ${CG_SRC})
source_group("source" FILES ${CG_SRC})


if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(LIB_DIR ${LIBRARIES}/x64)
    set(OUTPUT_DIR ${BIN_DIR}/x64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(LIB_DIR ${LIBRARIES}/Win32)
    set(OUTPUT_DIR ${BIN_DIR}/Win32)
endif()

link_directories(${LIB_DIR})

find_library(glew32 glew32.lib ${LIB_DIR})
find_library(SDL2 SDL2.lib ${LIB_DIR})
find_library(SDL2_image SDL2_image.lib ${LIB_DIR})
find_library(SDL2main SDL2main.lib ${LIB_DIR})
find_library(OpenGL32 opengl32.lib)


add_executable(computer_graphics ${ASSIGNMENT_INCLUDES} ${ASSIGNMENT_SRC} ${CG_INC} ${CG_SRC})
target_link_libraries(computer_graphics glew32 OpenGL32 SDL2 SDL2_image SDL2main)

set_target_properties(computer_graphics PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

install(TARGETS computer_graphics RUNTIME DESTINATION ${OUTPUT_DIR}/_install)
