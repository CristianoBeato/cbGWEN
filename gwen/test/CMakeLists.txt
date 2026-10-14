#
#============================================================================================
#	cbGWEN
#
#	Copyright (c) 2025 Cristiano Beato.
#
#	MIT License
#
#	Permission is hereby granted, free of charge, to any person obtaining a copy
#	of this software and associated documentation files (the "Software"), to deal
#	in the Software without restriction, including without limitation the rights
#	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#	copies of the Software, and to permit persons to whom the Software is
#	furnished to do so, subject to the following conditions:
#
#	The above copyright notice and this permission notice shall be included in
#	all copies or substantial portions of the Software.
#
#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#	THE SOFTWARE.
#============================================================================================
#

set( TEST_SOURCES test.cpp test.hpp )

add_executable( cbSDLTest WIN32 ${TEST_SOURCES} )
#set_target_properties( cbSDLTest PROPERTIES DISABLE_PRECOMPILED_HEADERS ON )
target_include_directories( cbSDLTest PRIVATE ${CMAKE_SOURCE_DIR}/include )
target_link_libraries( cbSDLTest PRIVATE cbGwen SDL3::SDL3 )
#target_precompile_headers( cbSDLTest PUBLIC "Gwen/Gwen.hpp")