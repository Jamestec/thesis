project(CFE_FIR2_APP C)

include_directories(fsw/mission_inc)
include_directories(fsw/platform_inc)
include_directories(../sample_app/fsw/platform_inc)
include_directories(../sample_app/fsw/src)

# Create the app module
add_cfe_app(fir2_app fsw/src/fir2_app.c)

add_cfe_app_dependency(fir2_app sample_app sample_lib fpgam_lib mmio_lib)

# Add table
add_cfe_tables(fir2AppTable fsw/tables/fir2_app_tbl.c)

# If UT is enabled, then add the tests from the subdirectory
# Note that this is an app, and therefore does not provide
# stub functions, as other entities would not typically make 
# direct function calls into this application.
#if (ENABLE_UNIT_TESTS)
#  add_subdirectory(unit-test)
#endif (ENABLE_UNIT_TESTS)
