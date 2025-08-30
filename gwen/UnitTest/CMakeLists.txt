#
#============================================================================================
#	GWEN
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

set( UNIT_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Button.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Checkbox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/CollapsibleList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ColorPicker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ComboBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CrossSplitter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GroupBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ImagePanel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Label.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LabelMultiline.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ListBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MenuStrip.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Numeric.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PageControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProgressBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RadioButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/ScrollControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Slider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatusBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TabControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TextBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TreeControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UnitTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UnitTest.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp
    )

add_library( UnitTest STATIC ${UNIT_TEST_SOURCES} )
target_precompile_headers( UnitTest 
    PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/UnitTest.h>" 
    PUBLIC "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/include/Gwen/Gwen.h>" 
    )   