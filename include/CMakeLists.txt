# make a list with all of the header files in it
file(GLOB silhouette_INC "*.hxx")

install(FILES ${silhouette_INC} DESTINATION include/silhouette)