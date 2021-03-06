INCLUDE_DIRECTORIES(
	${PYTHON_INCLUDE_PATH}
)

# The PythonModuleUTest is derived from the CogServer class, and so
# cannot be tested unless the cogserver is actually being built!
IF (HAVE_SERVER)
	ADD_CXXTEST(PythonModuleUTest)
	ADD_DEPENDENCIES(PythonModuleUTest
		PythonModule
	)

	TARGET_LINK_LIBRARIES(PythonModuleUTest
		PythonModule
		server
		${ATOMSPACE_LIBRARIES}
		${COGUTIL_LIBRARY}
	)
	SET_TESTS_PROPERTIES(PythonModuleUTest
		PROPERTIES ENVIRONMENT
		"PYTHONPATH=${PROJECT_BINARY_DIR}/opencog/cython:${PROJECT_SOURCE_DIR}/tests/cython/agents/:${PYTHON_ROOT}"
	)
ENDIF (HAVE_SERVER)


# The PyEvalUTest is derived from the CogServer class, and so
# cannot be tested unless the cogserver is actually being built!
IF (HAVE_SERVER)
	ADD_CXXTEST(PyEvalUTest)

	TARGET_LINK_LIBRARIES(PyEvalUTest
		py-shell
		server
		${ATOMSPACE_LIBRARIES}
		${COGUTIL_LIBRARY}
	)
ENDIF (HAVE_SERVER)

IF (HAVE_NOSETESTS)

	IF (HAVE_SERVER)
		ADD_TEST(CythonServer ${NOSETESTS_EXECUTABLE} -vs
			${CMAKE_SOURCE_DIR}/tests/cython/server/)
			SET_PROPERTY(TEST CythonServer
				PROPERTY ENVIRONMENT
				"PYTHONPATH=${PYTHON_ROOT}:${PROJECT_BINARY_DIR}/opencog/cython:${PROJECT_SOURCE_DIR}/tests/cython/agents:${PYTHON_ROOT}"
				"GUILE_LOAD_PATH=${GUILE_LOAD_PATH}"
				)
	ENDIF(HAVE_SERVER)

	IF (HAVE_STATISTICS)
		ADD_TEST(CythonStatistics ${NOSETESTS_EXECUTABLE} -vs
			${CMAKE_SOURCE_DIR}/tests/cython/statistics/)
		SET_PROPERTY(TEST CythonStatistics
			PROPERTY ENVIRONMENT
				"PYTHONPATH=${PYTHON_ROOT}:${PROJECT_BINARY_DIR}/opencog/cython:${PYTHON_ROOT}"
				"GUILE_LOAD_PATH=${GUILE_LOAD_PATH}"
				)
	ENDIF (HAVE_STATISTICS)

        IF (HAVE_OPENPSI)
		ADD_TEST(OpenPsiCythonTest ${NOSETESTS_EXECUTABLE} -vs
			${CMAKE_SOURCE_DIR}/tests/cython/openpsi/)
		# Use LTDL_LIBRARY_PATH to make Guile load *.so libraries from build dir
		SET_PROPERTY(TEST OpenPsiCythonTest
			PROPERTY ENVIRONMENT
				"PYTHONPATH=${PROJECT_BINARY_DIR}/opencog/cython:${PROJECT_BINARY_DIR}/opencog/openpsi:${PYTHON_ROOT}"
				"GUILE_LOAD_PATH=${GUILE_LOAD_PATH}"
				)
	ENDIF (HAVE_OPENPSI)

ENDIF (HAVE_NOSETESTS)
