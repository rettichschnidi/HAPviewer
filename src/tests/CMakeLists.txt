cmake_minimum_required (VERSION 2.6)

#include all test files
set(test_sources "test_gfilter.cpp")
set(test_sources ${test_sources} "test_gutil.cpp")
set(test_sources ${test_sources} "test_HashMapE.cpp")
set(test_sources ${test_sources} "test_ipv6_addr.cpp")
if(HAPVIEWER_ENABLE_PCAP)
	set(test_sources ${test_sources} "test_gfilter_pcap.cpp")
endif()
#if(HAPVIEWER_ENABLE_IPFIX)
#	set(test_sources ${test_sources} "test_gfilter_ipfix.cpp")
#endif()
if(HAPVIEWER_ENABLE_NFDUMP)
	set(test_sources ${test_sources} "test_gfilter_nfdump.cpp")
endif()
if(HAPVIEWER_ENABLE_CFLOW)
	set(test_sources ${test_sources} "test_cflow.cpp")
endif()

#add the cute-headers as well as the ones of our own application
include_directories("../lib/" "../tools/" "cute/")

foreach(test ${test_sources} )
	string(REGEX REPLACE ".*test_(.*)" "\\1" basename "${test}")
	string(REGEX REPLACE "(.*)(.cpp)" "\\1" noext "${basename}")
	add_executable(testexe_${noext} ${test})
	find_package(Threads REQUIRED)
	target_link_libraries(testexe_${noext} 
		hapviz
		${HAPVIEWER_CORELIBS}
		${CMAKE_THREAD_LIBS_INIT}
	)
	add_test(test_${noext} ${EXECUTABLE_OUTPUT_PATH}/testexe_${noext})
	set_tests_properties(test_${noext} PROPERTIES FAIL_REGULAR_EXPRESSION "failure") #this test fails if cute detects an error
endforeach()

#test graphcompare with all available examples
set(GRAPHS_NOT_EQUAL "Graphs are not equal.")
set(GRAPHS_EQUAL "Graphs are equal.")
set(GRAPHS_NOT_ISOMORPH "Graphs are not isomorph.")
file(GLOB graphcompare_testgraphs ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/*.dot)

foreach(testgraph ${graphcompare_testgraphs})
	string(REGEX REPLACE "(\\/.*\\/)([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\\.dot)" "\\2" dotfile "${testgraph}")

	add_test(graphcompare_equal_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${testgraph})
	set_tests_properties(graphcompare_equal_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_EQUAL}")

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localIPLabel/${dotfile})
    	add_test(graphcompare_changed_iplabel_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localIPLabel/${dotfile})
	    set_tests_properties(graphcompare_changed_iplabel_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/not_isomorph/${dotfile})
	    add_test(graphcompare_not_isomorph_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/not_isomorph/${dotfile})
    	set_tests_properties(graphcompare_not_isomorph_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_ISOMORPH}")
    endif()
   
	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localIPShape/${dotfile})
        add_test(graphcompare_changed_ipshape_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localIPShape/${dotfile})
    	set_tests_properties(graphcompare_changed_ipshape_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localPort2RemotePortColor/${dotfile})
	    add_test(graphcompare_changed_localport2remoteportcolor_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localPort2RemotePortColor/${dotfile})
	    set_tests_properties(graphcompare_changed_localport2remoteportcolor_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localPort2RemotePortDirection/${dotfile})
    	add_test(graphcompare_changed_localport2remoteportdirection_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localPort2RemotePortDirection/${dotfile})
    	set_tests_properties(graphcompare_changed_localport2remoteportdirection_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localPort2RemotePortLabel/${dotfile})
    	add_test(graphcompare_changed_localport2remoteportlabel_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localPort2RemotePortLabel/${dotfile})
    	set_tests_properties(graphcompare_changed_localport2remoteportlabel_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localPortLabel/${dotfile})
    	add_test(graphcompare_changed_localportlabel_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localPortLabel/${dotfile})
    	set_tests_properties(graphcompare_changed_localportlabel_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localPortShape/${dotfile})
    	add_test(graphcompare_changed_localportshape_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_localPortShape/${dotfile})
    	set_tests_properties(graphcompare_changed_localportshape_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_protocolLabel/${dotfile})
	    add_test(graphcompare_changed_protocollabel_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_protocolLabel/${dotfile})
	    set_tests_properties(graphcompare_changed_protocollabel_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_protocolShape/${dotfile})
    	add_test(graphcompare_changed_protocolshape_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_protocolShape/${dotfile})
    	set_tests_properties(graphcompare_changed_protocolshape_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_remoteIPLabel/${dotfile})
    	add_test(graphcompare_changed_remoteiplabel_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_remoteIPLabel/${dotfile})
    	set_tests_properties(graphcompare_changed_remoteiplabel_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_remoteIPShape/${dotfile})
	    add_test(graphcompare_changed_remoteipshape_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_remoteIPShape/${dotfile})
	    set_tests_properties(graphcompare_changed_remoteipshape_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_remotePort2RemoteIPColor/${dotfile})
	    add_test(graphcompare_changed_remoteport2remoteipcolor_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_remotePort2RemoteIPColor/${dotfile})
	    set_tests_properties(graphcompare_changed_remoteport2remoteipcolor_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_remotePort2RemoteIPLabel/${dotfile})
	    add_test(graphcompare_changed_remoteport2remoteiplabel_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_remotePort2RemoteIPLabel/${dotfile})
	    set_tests_properties(graphcompare_changed_remoteport2remoteiplabel_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_remotePortLabel/${dotfile})
    	add_test(graphcompare_changed_remoteportlabel_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_remotePortLabel/${dotfile})
    	set_tests_properties(graphcompare_changed_remoteportlabel_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()

	if(EXISTS ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_remotePortShape/${dotfile})
	    add_test(graphcompare_changed_remoteportshape_${dotfile} ${EXECUTABLE_OUTPUT_PATH}/graphcompare ${testgraph} ${CMAKE_SOURCE_DIR}/examples/testcases/graphcompare/changed_remotePortShape/${dotfile})
	    set_tests_properties(graphcompare_changed_remoteportshape_${dotfile} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_NOT_EQUAL}")
    endif()
endforeach()

#test graphcompare with all available examples
set(haplibtest_generated_graphlets ${CMAKE_BINARY_DIR}/haplibtest_generated_graphlets)
file(REMOVE_RECURSE ${haplibtest_generated_graphlets})
file(MAKE_DIRECTORY ${haplibtest_generated_graphlets})
file(GLOB haplibtest_testflows ${CMAKE_SOURCE_DIR}/examples/testcases/cflow4/*.gz)

foreach(haplibtest_testflow ${haplibtest_testflows})
	string(REGEX REPLACE "(\\/.*\\/)([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+)\\.gz" "\\2" haplibtest_ip "${haplibtest_testflow}")
	
	add_test(haplibtest_testflow_${haplibtest_ip} ${EXECUTABLE_OUTPUT_PATH}/haplibtest "${haplibtest_testflow}" "${haplibtest_ip}" -o "${haplibtest_generated_graphlets}/${haplibtest_ip}.dot")
	set_tests_properties(haplibtest_testflow_${haplibtest_ip} PROPERTIES FAIL_REGULAR_EXPRESSION "ERROR")
	
	add_test(haplibtest_testflow_compare_${haplibtest_ip} ${EXECUTABLE_OUTPUT_PATH}/graphcompare "${CMAKE_SOURCE_DIR}/examples/testcases/cflow4/known-good-graphlets/${haplibtest_ip}.dot" "${haplibtest_generated_graphlets}/${haplibtest_ip}.dot")
	set_tests_properties(haplibtest_testflow_compare_${haplibtest_ip} PROPERTIES PASS_REGULAR_EXPRESSION "${GRAPHS_EQUAL}")
endforeach()