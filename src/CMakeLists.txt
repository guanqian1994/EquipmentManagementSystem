PROJECT(EquipmentManagementSystem)

SET(LIB_NAME EquipmentManagementSystem)

#########################################################################################
## QT C
#########################################################################################

SET(DO_MOC_HEADER_LIST
    mainwindow.h
)

SET(DO_UIC_LIST
    mainwindow.ui
)

SET(MOC_OUT_LIST)
SET(UIC_OUT_LIST)

FOREACH(MOC_FILE ${DO_MOC_HEADER_LIST})
    QT_MOC(${CMAKE_CURRENT_SOURCE_DIR} ${MOC_FILE} MOC_OUT_LIST)
ENDFOREACH()

FOREACH(UI_FILE ${DO_UIC_LIST})
    QT_UIC(${CMAKE_CURRENT_SOURCE_DIR} ${UI_FILE} UIC_OUT_LIST)
ENDFOREACH()

#########################################################################################
## FILES
#########################################################################################

SOURCE_GROUP(${LIB_NAME}\\window\\moc FILES ${MOC_OUT_LIST})
SOURCE_GROUP(${LIB_NAME}\\window\\uic FILES ${UIC_OUT_LIST})

SET(MASTER_SRC_LIST
    main.cpp
    db_layer.h
    singleton.h
)
SOURCE_GROUP(${LIB_NAME} FILES ${MASTER_SRC_LIST})

SET(WINDOW_SRC_LIST
    mainwindow.h
    mainwindow.cpp
	${DO_UIC_LIST}
)
SOURCE_GROUP(${LIB_NAME}\\window FILES ${WINDOW_SRC_LIST})

ADD_EXECUTABLE(${LIB_NAME} 
#   \\
    ${MASTER_SRC_LIST}
#   \\window
    ${WINDOW_SRC_LIST}
#   \\window\\\moc
    ${MOC_OUT_LIST}
#   \\window\\\uic
    ${UIC_OUT_LIST}
)

#########################################################################################
## INCLUDE & LINK
#########################################################################################

FOREACH(QT_LIB
  Core
  Gui
  Widgets
  Sql
)
    ADD_QT_LIB(${QT_LIB})
ENDFOREACH()

#########################################################################################
## Others
#########################################################################################

SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH}
    ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${LIBRARY_OUTPUT_PATH}
    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${LIBRARY_OUTPUT_PATH}
    LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH}
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH}
    LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${LIBRARY_OUTPUT_PATH}
    LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${LIBRARY_OUTPUT_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH}
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${LIBRARY_OUTPUT_PATH}
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${LIBRARY_OUTPUT_PATH}
    PROJECT_LABEL ${LIB_NAME}
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)