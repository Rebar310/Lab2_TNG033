cmake_minimum_required(VERSION 3.13.0...3.31.0)
project(TNG033-Lab-2 VERSION 1.0.0 DESCRIPTION "TNG033 Lab 2" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(enable_warnings target)
    target_compile_options(${target} PUBLIC 
        $<$<CXX_COMPILER_ID:MSVC>:
            /W4                 # Enable the highest warning level
            /w44388             # eneble 'signed/unsigned mismatch' '(off by default)
            /we4715             # turn 'not all control paths return a value' into a compile error
            /permissive-        # Stick to the standard
			/fsanitize=address  # Enable the Address Sanatizer, helps finding bugs at runtime
            >
        $<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra -Wconversion>
    )
    set_target_properties(${target} PROPERTIES 
        XCODE_GENERATE_SCHEME ON
        XCODE_SCHEME_ADDRESS_SANITIZER ON
        XCODE_SCHEME_ADDRESS_SANITIZER_USE_AFTER_RETURN ON
        XCODE_SCHEME_MALLOC_SCRIBBLE ON
        XCODE_SCHEME_UNDEFINED_BEHAVIOUR_SANITIZER ON
        XCODE_SCHEME_UNDEFINED_BEHAVIOUR_SANITIZER_STOP ON
    )
	 target_link_options(${target} PUBLIC 
         $<$<CXX_COMPILER_ID:MSVC>:/INCREMENTAL:NO> # Cant use incremental with asan
    )
endfunction()

add_executable(Exercise1 expression.h expression.cpp polynomial.h polynomial.cpp logarithm.h logarithm.cpp test.cpp)

enable_warnings(Exercise1)