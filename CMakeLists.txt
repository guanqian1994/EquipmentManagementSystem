SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS On)

SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(EquipmentManagementSystem)

#########################################################################################
## GLOBAL VARIABLE
#########################################################################################

FIND_PATH(QT_KIT_PATH REQUIRED)

SET(PROJECT_DIR ${CMAKE_SOURCE_DIR})
SET(DEPENDENCIES_PATH ${PROJECT_SOURCE_DIR}/dependencies)

IF(APPLE)
    SET(CMAKE_FRAMEWORK_PATH "${CMAKE_FRAMEWORK_PATH} ${QT_KIT_PATH}/include/")
ENDIF()

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/)

SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")

IF(MSVC)
    OPTION(COPY_QT_DLL_FILS "Copy QT DLL files" ON)
    OPTION(COPY_DEBUG_DLL "No select will be copy release version" FALSE)

    IF(COPY_DEBUG_DLL)
        SET(QT_LIB_ENDCHAR "d")
    ENDIF()

    IF(COPY_QT_DLL_FILS)
        FILE(COPY ${QT_KIT_PATH}/bin/icudt52.dll DESTINATION ${LIBRARY_OUTPUT_PATH})
        FILE(COPY ${QT_KIT_PATH}/bin/icuin52.dll DESTINATION ${LIBRARY_OUTPUT_PATH})
        FILE(COPY ${QT_KIT_PATH}/bin/icuuc52.dll DESTINATION ${LIBRARY_OUTPUT_PATH})
    ENDIF()
ENDIF()

IF(APPLE)
    SET(EXEC_EXT "")
ELSE(MSVC)
    SET(EXEC_EXT ".exe")
ENDIF()

#########################################################################################
## COMPILER OPTIONS
#########################################################################################

IF(APPLE)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
ELSEIF(MSVC)
    #ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
    ADD_DEFINITIONS(-D_WINDOWS)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DELAYLOAD:advapi32.dll")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DELAYLOAD:psapi.dll")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DELAYLOAD:version.dll")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DELAYLOAD:dbghelp.dll")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DELAY:unload")
    SET(COMPILER_NAME "vc")
    IF(MSVC_VERSION GREATER 1600)
        SET(COMPILER_NAME "11")
    ELSEIF(MSVC_VERSION GREATER 1500)
        SET(COMPILER_NAME "10")
    ELSEIF(MSVC_VERSION GREATER 1400)
        SET(COMPILER_NAME "9")
    ENDIF()
ENDIF()

#########################################################################################
## LINK PATHS
#########################################################################################

LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})

IF(MSVC)
    LINK_DIRECTORIES(${QT_KIT_PATH}/lib)
ENDIF()

#########################################################################################
## MACROS
#########################################################################################

IF(APPLE)
    MACRO(ADD_SYS_FRAMEWORK fwname appname)
        FIND_LIBRARY(FRAMEWORK_${fwname}
        NAMES ${fwname}
        PATHS ${CMAKE_OSX_SYSROOT}/System/Library
        PATH_SUFFIXES Frameworks
        NO_DEFAULT_PATH)
        IF( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
            MESSAGE(ERROR ": Framework ${fwname} not found")
        ELSE()
            TARGET_LINK_LIBRARIES(${appname} "${FRAMEWORK_${fwname}}/${fwname}")
            MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
        ENDIF()
    ENDMACRO(ADD_SYS_FRAMEWORK)

    MACRO(ADD_FRAMEWORK fwpath fwname appname)
        FIND_LIBRARY(FRAMEWORK_${fwname}
        NAMES ${fwname}
        PATHS ${fwpath}
        PATH_SUFFIXES Frameworks
        NO_DEFAULT_PATH)
        IF( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
            MESSAGE(ERROR ": Framework ${fwname} not found")
        ELSE()
            TARGET_LINK_LIBRARIES(${appname} "${FRAMEWORK_${fwname}}/${fwname}")
            MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
        ENDIF()
    ENDMACRO(ADD_FRAMEWORK)

    MACRO(ADD_QT_LIB fwname)
       ADD_FRAMEWORK(${QT_KIT_PATH}/lib Qt${fwname} ${LIB_NAME})
    ENDMACRO(ADD_QT_LIB)

ELSEIF(MSVC)

    INCLUDE_DIRECTORIES(${QT_KIT_PATH}/include)

    MACRO(ADD_QT_LIB fwname)
        TARGET_LINK_LIBRARIES(${LIB_NAME} Qt5${fwname}${QT_LIB_ENDCHAR})

        IF(MSVC AND COPY_QT_DLL_FILS)
            FILE(COPY ${QT_KIT_PATH}/bin/Qt5${fwname}${QT_LIB_ENDCHAR}.dll DESTINATION ${LIBRARY_OUTPUT_PATH})
            IF(COPY_DEBUG_DLL)
                FILE(COPY ${QT_KIT_PATH}/bin/Qt5${fwname}${QT_LIB_ENDCHAR}.pdb DESTINATION ${LIBRARY_OUTPUT_PATH})
            ENDIF()
        ENDIF()
    ENDMACRO(ADD_QT_LIB)
ENDIF()

MACRO(ADD_DEPENDENCIES_LIB libname)
    TARGET_LINK_LIBRARIES(${LIB_NAME} ${libname})
    INCLUDE_DIRECTORIES(${DEPENDENCIES_PATH}/${libname})
ENDMACRO(ADD_DEPENDENCIES_LIB)

MACRO(QT_MOC filepath filein filelist)
    STRING(REPLACE ".h" "" fileout ${filein})
    EXECUTE_PROCESS(COMMAND ${QT_KIT_PATH}/bin/moc${EXEC_EXT} -o ${filepath}/moc_${fileout}.cpp ${filepath}/${filein})
    SET(${filelist} ${${filelist}} moc_${fileout}.cpp)
ENDMACRO(QT_MOC)

MACRO(QT_UIC filepath filein sourcelist)
    STRING(REPLACE ".ui" "" fileout ${filein})
    EXECUTE_PROCESS(COMMAND ${QT_KIT_PATH}/bin/uic${EXEC_EXT} -o ${filepath}/ui_${fileout}.h ${filepath}/${filein})
    SET(${sourcelist} ${${sourcelist}} ui_${fileout}.h)
ENDMACRO(QT_UIC)

#########################################################################################
## SUBDIRECTORY
#########################################################################################

ADD_SUBDIRECTORY(src)
