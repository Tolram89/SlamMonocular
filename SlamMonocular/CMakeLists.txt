# Indique où se trouvent les fichiers .h
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Ajoute les sources situées dans le dossier src/
add_executable (SlamMonocular 
    "src/SlamMonocular.cpp" 
    "src/calibration.cpp"
 "src/preprocessing.cpp" "include/preprocessing.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SlamMonocular PROPERTY CXX_STANDARD 20)
endif()

# Lie les fichiers d'OpenCV à ton exécutable
target_link_libraries(SlamMonocular ${OpenCV_LIBS})