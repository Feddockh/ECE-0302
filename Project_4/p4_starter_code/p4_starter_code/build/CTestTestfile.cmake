# CMake generated Testfile for 
# Source directory: /home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code
# Build directory: /home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(student-tests "student-tests")
set_tests_properties(student-tests PROPERTIES  _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;36;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test00 "pathfinder" "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/tests/maze00.png" "output00.png")
set_tests_properties(test00 PROPERTIES  _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;37;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test00-compare "compare" "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/tests/output00.png" "output00.png")
set_tests_properties(test00-compare PROPERTIES  _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;38;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test01 "pathfinder" "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/tests/maze01.png" "output01.png")
set_tests_properties(test01 PROPERTIES  _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;39;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test01-compare "compare" "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/tests/output01.png" "output01.png")
set_tests_properties(test01-compare PROPERTIES  _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;40;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test02 "pathfinder" "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/tests/maze02.png" "output02.png")
set_tests_properties(test02 PROPERTIES  _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;41;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test02-compare "compare" "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/tests/output02.png" "output02.png")
set_tests_properties(test02-compare PROPERTIES  _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;42;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test04 "pathfinder" "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/tests/maze04.png" "output04.png")
set_tests_properties(test04 PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;43;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test05 "pathfinder" "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/tests/maze05.png" "output05.png")
set_tests_properties(test05 PROPERTIES  _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;44;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test05-compare "compare" "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/tests/output05.png" "output05.png")
set_tests_properties(test05-compare PROPERTIES  _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;45;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test07 "pathfinder" "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/tests/maze07.png" "output07.png")
set_tests_properties(test07 PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;46;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test08 "pathfinder" "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/tests/maze00.png")
set_tests_properties(test08 PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;47;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test09 "pathfinder" "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code")
set_tests_properties(test09 PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;48;add_test;/home/feddockh/ECE_0302/ECE_0302/Project_4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
subdirs("lib")
