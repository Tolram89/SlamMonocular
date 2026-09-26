# CMakeList.txt : projet CMake pour SlamMonocular, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.
add_executable (SlamMonocular "SlamMonocular.cpp" "SlamMonocular.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SlamMonocular PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
# Lie les fichiers d'OpenCV à ton exécutable
target_link_libraries(SlamMonocular ${OpenCV_LIBS})