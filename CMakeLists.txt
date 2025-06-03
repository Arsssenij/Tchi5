cmake_minimum_required(VERSION 3.16)

project(TextEditorGUI)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Файлы проекта
set(SOURCES
    main.cpp
    mainwindow.cpp
    domain/Document.cpp
    domain/InsertCommand.cpp
    domain/EditorFactory.cpp
    domain/DeleteCommand.cpp
    domain/UndoManager.cpp
    logger/ConsoleLogger.cpp
    logger/LoggerFactory.cpp
    logger/FileLogger.cpp
)

set(HEADERS
    mainwindow.h
    domain/Document.h
    domain/InsertCommand.h
    domain/DeleteCommand.h
    domain/EditorFactory.h
    domain/UndoManager.h
    domain/ICommand.h
    logger/ConsoleLogger.h
    logger/LoggerFactory.h
    logger/ILogger.h
    logger/FileLogger.h
)

set(UIS
    mainwindow.ui
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UIS})

# Укажи пути к заголовкам, если используются подкаталоги
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/domain
    ${CMAKE_CURRENT_SOURCE_DIR}/logger
)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
add_subdirectory(tests)
