cmake_minimum_required(VERSION 2.8.12)
project(Devsi)

    # X11
    if(UNIX AND NOT APPLE)
    	find_library(X_11 X11)
    	find_library(X_TST Xtst)
    	set(EXTRA_LIBS ${X_11} ${X_TST})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/local/include")
    endif(UNIX AND NOT APPLE)

    # Apple
    if(APPLE)
       find_library(APP_SERVICES ApplicationServices)
       find_library(CARBON Carbon)
       find_library(CORE_FOUNDATION CoreFoundation)
       set(EXTRA_LIBS ${APP_SERVICES_LIBRARY} ${CARBON} ${CORE_FOUNDATION})
	   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
    endif(APPLE)
	
	# Windows
	if(WIN32)
		#find_library(USER_32 User32.Lib)
		#set(EXTRA_LIBS ${USER_32})
	endif(WIN32)
	
	set(SOURCE_FILES
		main.cpp
		devsi_mouse.cpp
		)

add_executable(devsi ${SOURCE_FILES})
target_link_libraries(devsi ${EXTRA_LIBS} )
