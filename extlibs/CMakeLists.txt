# Configurable locations of dependencies of this project.
set(SFML_DIR "${DEPENDENCIES_DIR}/SFML" CACHE PATH "Path to SFML")
set(PUGIXML_DIR "${DEPENDENCIES_DIR}/pugixml" CACHE PATH "Path to PUGIXML")
set(ZLIB_DIR "${DEPENDENCIES_DIR}/zlib" CACHE PATH "Path to ZLIB")


###############################################################################


# Find SFML
set(SFML_ROOT ${SFML_DIR})
if(!STP_SHARED_LIBS)
    add_definitions(-DSFML_STATIC)
endif()
if (SFML_INCLUDE_DIR)
    set(SFML_LIBRARIES sfml-graphics sfml-window sfml-system)
else()
    find_package(SFML 2 COMPONENTS graphics window system)
    if(SFML_FOUND)
        # Nothing to do, already there
    elseif(SFML_SOURCE_DIR AND SFML_BINARY_DIR)
        set(SFML_INCLUDE_DIR "${SFML_SOURCE_DIR}/include")
        set(SFML_LIBRARIES sfml-graphics sfml-window sfml-system)
    else()
        message("\n-> SFML directory not found. Put the SFML's top-level path "
                "(containing \"include\" and \"lib\" directories) in the "
                "/extlibs/SFML folder.\n")
    endif()
endif()


# PUGIXML
if (USE_SHARED_PUGIXML)
    find_package(PugiXML REQUIRED)
    set(PUGIXML_INCLUDE_DIR ${PUGIXML_INCLUDE_DIR})
    set(PUGIXML_LIBRARIES ${PUGIXML_LIBRARY})
else()
    add_subdirectory(
        "${PUGIXML_DIR}/scripts"
        "${TEMP_DIR}/pugixml"
        EXCLUDE_FROM_ALL
    )
    set(PUGIXML_INCLUDE_DIR "${PUGIXML_DIR}/src")
    set(PUGIXML_LIBRARIES pugixml)
    set(COMPILED_DEPENDENCIES ${COMPILED_DEPENDENCIES} ${PUGIXML_LIBRARIES})
endif()

# ZLIB
if (USE_SHARED_ZLIB)
    find_package(ZLIB REQUIRED)
    set(ZLIB_INCLUDE_DIR ${ZLIB_INCLUDE_DIR})
    set(ZLIB_LIBRARIES ${ZLIB_LIBRARIES})
else()
    add_subdirectory("${ZLIB_DIR}" "${TEMP_DIR}/zlib" EXCLUDE_FROM_ALL)
    set(ZLIB_INCLUDE_DIR
        "${TEMP_DIR}/zlib"
        "${ZLIB_DIR}"
    )
    if(STP_SHARED_LIBS)
        set(ZLIB_LIBRARIES zlib)
    else()
        set(ZLIB_LIBRARIES zlibstatic)
    endif()
    set(COMPILED_DEPENDENCIES ${COMPILED_DEPENDENCIES} ${ZLIB_LIBRARIES})
endif()

###############################################################################

# Set the dependencies folder
set_property(TARGET ${COMPILED_DEPENDENCIES} PROPERTY FOLDER "Dependencies")

# Add the dependencies to the parent scope
set(SFML_LIBRARIES ${SFML_LIBRARIES} PARENT_SCOPE)
set(PUGIXML_LIBRARIES ${PUGIXML_LIBRARIES} PARENT_SCOPE)
set(ZLIB_LIBRARIES ${ZLIB_LIBRARIES} PARENT_SCOPE)

# Set the third party include directories
set(DEPENDENCIES_INCLUDES
        ${SFML_INCLUDE_DIR}
        ${PUGIXML_INCLUDE_DIR}
        ${ZLIB_INCLUDE_DIR}
    PARENT_SCOPE)
