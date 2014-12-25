#############################################
##### Declaring
#############################################

set(libname  "kruchinin-dmitry-stack-library")
set(testname "kruchinin-dmitry-stack-test")
set(appname  "kruchinin-dmitry-stack-application")

message("")
message("############################################")
message("##### Testing ${libname}")
message("############################################")
message("")

#############################################
##### Building
#############################################

# Declare directory with public headers
add_dir_inc("./")

# Declare static library
add_lib_static(${libname} "include" "src")

# Declare module with unit tests
add_local_dependency(${libname})
add_app(${testname} "test")
target_link_libraries(${testname})

# Declare application
add_local_dependency(${libname})
add_app(${appname} "application")

#############################################
##### Testing
#############################################

include("CTestTests.txt")
