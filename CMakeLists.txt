cmake_minimum_required(VERSION 3.23)
project(ece-city-2-i C)

set(CMAKE_C_STANDARD 99)

add_executable(ece-city-2-i main.c jeu.c jeu.h Affichage.c Affichage.h Initialisation.c Initialisation.h Graphe.c Graphe.h BFS.c)
IF(WIN32)
    target_link_libraries(ece-city-2-i -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE()
    INCLUDE_DIRECTORIES(/usr/local/Cellar/allegro/5.2.7.0/include)
    LINK_DIRECTORIES(/usr/local/Cellar/allegro/5.2.7.0/lib)
    file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.7.0/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(ece-city-2-i ${LIBRARIES})
ENDIF(WIN32)
