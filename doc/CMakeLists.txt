# Add a target for building the documentation
ADD_CUSTOM_TARGET(docs)
ADD_CUSTOM_COMMAND(
  TARGET   docs
  COMMAND  cd ${CMAKE_SOURCE_DIR} && doxygen doc/Doxyfile
)
