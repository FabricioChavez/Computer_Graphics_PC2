cmake_minimum_required(VERSION 3.17)
project(Vector_Test)

# Configurar el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Habilitar pruebas
enable_testing()

# Encontrar el paquete de Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Función para agregar ejecutables automáticamente
function(add_cpp_executable filename)
    # Extraer el nombre base del archivo (sin extensión)
    get_filename_component(base_name ${filename} NAME_WE)
    
    # Agregar ejecutable
    add_executable(${base_name} ${filename})
    
    # Vincular con Google Test
    target_link_libraries(${base_name} ${GTEST_LIBRARIES} pthread)
    
    # Agregar como prueba
    add_test(NAME ${base_name}_test COMMAND ${base_name})
    
    message(STATUS "Added executable and test for: ${base_name}")
endfunction()

# Encontrar todos los archivos .cpp en el directorio actual
file(GLOB CPP_FILES "*.cpp")

# Agregar ejecutables para cada archivo .cpp encontrado
foreach(cpp_file ${CPP_FILES})
    add_cpp_executable(${cpp_file})
endforeach()

# Mensaje informativo
message(STATUS "Found ${CMAKE_BINARY_DIR} CPP files to compile")