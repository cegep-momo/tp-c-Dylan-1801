cmake_minimum_required(VERSION 3.21)
project(bibliotheque)

file(GLOB SOURCES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES}
    main.cpp
    library.cpp
    user.cpp
    filemanager.cpp
    book.cpp 
)

# Specifie qu'on veut la version C++17 du langage
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)


# flag pour tous les warnings possible
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)


# Pour definir le chemin du dossier data
target_compile_definitions(bibliotheque PRIVATE
    DATA_DIR="${CMAKE_SOURCE_DIR}/data"
)