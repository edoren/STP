# - Try to find STP
# Once done this will define
#
# PUGIXML_FOUND - system has Jansson
# PUGIXML_INCLUDE_DIR - the Jansson include directory
# PUGIXML_LIBRARY - Link these to use Jansson

find_path(PUGIXML_INCLUDE_DIR
          NAMES pugixml.hpp pugiconfig.hpp)

find_library(PUGIXML_LIBRARY
             NAMES pugixml)

set(PUGIXML_LIBRARY ${PUGIXML_LIBRARY})
set(PUGIXML_INCLUDE_DIR ${PUGIXML_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PUGIXML_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(PUGIXML DEFAULT_MSG
                                  PUGIXML_LIBRARY PUGIXML_INCLUDE_DIR)

mark_as_advanced(PUGIXML_LIBRARY PUGIXML_INCLUDE_DIR)
