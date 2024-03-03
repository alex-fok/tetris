cmake_minimum_required(VERSION 3.16)
project(Tetris LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
    # SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../SFML/)
FetchContent_MakeAvailable(SFML)

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_BINARY_DIR}/assets)
add_executable(Tetris src/Resources/FontCollection.cpp src/Utils/Area.cpp src/Utils/Clickable.cpp src/Utils/Drawable.cpp src/Utils/Button.cpp src/Utils/Layer.cpp src/Utils/LayerControl.cpp src/GameAnimation/Animation.cpp src/GameAnimation/Scoring.cpp src/Menu/Base.cpp src/Menu/GameOver.cpp src/Menu/Pause.cpp src/GameEntity/Block.cpp src/GameEntity/ActiveTetromino.cpp src/GameEntity/TetrominoFactory.cpp src/GameEntity/SingleTetroBox.cpp src/GameEntity/Hold.cpp src/GameEntity/PreviewList.cpp src/GameEntity/ScoringSystem.cpp src/GameEntity/Score.cpp src/GameEntity/Tetromino.cpp src/GameEntity/TetrominoContainer.cpp src/main.cpp src/GameUI/UI.cpp)
add_dependencies(Tetris copy_assets)
target_link_libraries(Tetris PRIVATE sfml-graphics)
target_compile_features(Tetris PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Tetris 
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Tetris>
        VERBATIM)
endif()

install(TARGETS Tetris)
