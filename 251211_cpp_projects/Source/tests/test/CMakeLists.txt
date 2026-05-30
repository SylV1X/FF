set(SOURCES 
	test_bubble.cpp
)

add_executable(test_bubble ${SOURCES})
target_link_libraries(test_bubble 
	${LIBRARY}
	gtest_main 
	gmock_main 
)

add_test(test_bubble2 test_bubble)