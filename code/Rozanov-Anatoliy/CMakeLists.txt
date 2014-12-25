#############################################
##### Declaring
#############################################

set(libname  "rozanov-anatoliy-interpsearch-library")
set(testname "rozanov-anatoliy-interpsearch-test")
set(appname  "rozanov-anatoliy-interpsearch-application")

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
add_app(${appname} "application")


#############################################
##### Testing
#############################################

include("CTestTests.txt")
