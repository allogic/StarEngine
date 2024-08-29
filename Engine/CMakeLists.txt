find_package (OpenGL REQUIRED)

file (GLOB_RECURSE TARGET_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set (TARGET_NAME Engine)

add_executable (${TARGET_NAME}
	${TARGET_SOURCE}
)

target_precompile_headers (${TARGET_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/PreCompiled.h
)

set_target_properties (${TARGET_NAME} PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/$<CONFIG>
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/$<CONFIG>
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/$<CONFIG>
	CXX_STANDARD 20
)

target_compile_options (${TARGET_NAME} PRIVATE
	$<$<CONFIG:Debug>:
		$<$<CXX_COMPILER_ID:MSVC>:/MDd>
		$<$<CXX_COMPILER_ID:GNU>:-g>
		$<$<CXX_COMPILER_ID:Clang>:-g>
	>

	$<$<CONFIG:Release>:
		$<$<CXX_COMPILER_ID:MSVC>:/MD>
		$<$<CXX_COMPILER_ID:GNU>:-O3>
		$<$<CXX_COMPILER_ID:Clang>:-O3>
	>
)

target_compile_definitions (${TARGET_NAME} PRIVATE
	$<$<CONFIG:Debug>:
		SE_DEBUG
	>

	$<$<PLATFORM_ID:Windows>:
		SE_PLATFORM_WINDOWS
		_CRT_SECURE_NO_WARNINGS
	>

	$<$<PLATFORM_ID:Linux>:
		SE_PLATFORM_LINUX
	>
)

target_link_options (${TARGET_NAME} PRIVATE
	$<$<CONFIG:Debug>:
		$<$<CXX_COMPILER_ID:MSVC>:
			/IGNORE:4099
		>
	>
)

target_include_directories (${TARGET_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries (${TARGET_NAME} PRIVATE
	${OPENGL_LIBRARIES}

	$<$<PLATFORM_ID:Windows>:
		${CMAKE_SOURCE_DIR}/Library/glfw3.lib
		${CMAKE_SOURCE_DIR}/Library/assimp-vc143-mt.lib
		${CMAKE_SOURCE_DIR}/Library/zlibstatic.lib
	>

	$<$<PLATFORM_ID:Linux>:
		${CMAKE_SOURCE_DIR}/Library/glfw3.a
		${CMAKE_SOURCE_DIR}/Library/assimp-vc143-mt.a
		${CMAKE_SOURCE_DIR}/Library/zlibstatic.a
	>
)