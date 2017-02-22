# CMake generated Testfile for 
# Source directory: /Users/adithya/Downloads/opencv-3.2.0/modules/core
# Build directory: /Users/adithya/Downloads/opencv-3.2.0/build/modules/core
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_core "/Users/adithya/Downloads/opencv-3.2.0/build/bin/opencv_test_core" "--gtest_output=xml:opencv_test_core.xml")
set_tests_properties(opencv_test_core PROPERTIES  LABELS "Main;opencv_core;Accuracy" WORKING_DIRECTORY "/Users/adithya/Downloads/opencv-3.2.0/build/test-reports/accuracy")
add_test(opencv_perf_core "/Users/adithya/Downloads/opencv-3.2.0/build/bin/opencv_perf_core" "--gtest_output=xml:opencv_perf_core.xml")
set_tests_properties(opencv_perf_core PROPERTIES  LABELS "Main;opencv_core;Performance" WORKING_DIRECTORY "/Users/adithya/Downloads/opencv-3.2.0/build/test-reports/performance")
add_test(opencv_sanity_core "/Users/adithya/Downloads/opencv-3.2.0/build/bin/opencv_perf_core" "--gtest_output=xml:opencv_perf_core.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_core PROPERTIES  LABELS "Main;opencv_core;Sanity" WORKING_DIRECTORY "/Users/adithya/Downloads/opencv-3.2.0/build/test-reports/sanity")
