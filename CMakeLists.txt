CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(gameio)

FIND_PACKAGE(Boost REQUIRED COMPONENTS system)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

SET (CMAKE_CXX_STANDARD 11)
SET(SOURCES
	src/Connection.cpp
	src/CommunicationChannel.cpp
	src/Server.cpp
	src/Client.cpp
)


# temporário
ADD_EXECUTABLE(gameserver ${SOURCERS} src/server.cpp)
TARGET_LINK_LIBRARIES(gameserver ${Boost_SYSTEM_LIBRARY})

ADD_EXECUTABLE(gameclient ${SOURCERS} src/client.cpp)
TARGET_LINK_LIBRARIES(gameclient ${Boost_SYSTEM_LIBRARY})

ADD_EXECUTABLE(main ${SOURCERS} src/main.cpp)
TARGET_LINK_LIBRARIES(main ${Boost_SYSTEM_LIBRARY})
