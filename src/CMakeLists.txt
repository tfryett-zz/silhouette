# add all c++ files to a variable
file(GLOB silhouette_SRCS "*.cxx")

# make library out of source files
add_library(silhouette SHARED ${silhouette_SRCS} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

# when requested install them
install(TARGETS silhouette DESTINATION bin)
