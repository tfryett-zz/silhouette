# make a list with all of the header files in it
file(GLOB silhouette_SRC "*.cxx")
file(GLOB silhouette_INC "*.hxx")

add_library(silhouette ${silhouette_SRC})

install(TARGETS silhouette DESTINATION bin)
install(FILES ${silhouette_INC} DESTINATION include/silhouette)
