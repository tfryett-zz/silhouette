add_executable(Test test.cxx)
target_link_libraries(Test silhouette ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})
add_test(Test Test)
