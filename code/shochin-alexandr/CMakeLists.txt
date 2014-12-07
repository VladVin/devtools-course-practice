#############################################
##### Declaring
#############################################

set(libname  "shochin-alexandr-tconv-library")
set(testname "shochin-alexandr-tconv-test")
set(appname "shochin-alexandr-tconv-application")


message("")
message("############################################")
message("##### Testing ${appname}")
message("############################################")
message("")

#############################################
##### Building
#############################################

# Declare directory with public headers
add_dir_inc("./")

# Declare static library
add_lib_static(${libname} "include" "src")

# Declare application
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