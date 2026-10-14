#
#============================================================================================
#	GWEN
#
#	Copyright (c) 2025-2026 Cristiano Beato.
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

set( GWEN_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Anim.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Anim.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AutoPointer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ControlList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ControlList.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Debug.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Debug.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DragAndDrop.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DragAndDrop.h
    ${CMAKE_CURRENT_SOURCE_DIR}/events.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Events.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Exports.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Font.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Gwen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gwen.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/InputHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/InputHandler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Hook.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Hook.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Macros.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Structures.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TextObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TextObject.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ToolTip.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ToolTip.h
    ${CMAKE_CURRENT_SOURCE_DIR}/UserData.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WindowProvider.h

    # Platform
    #${CMAKE_CURRENT_SOURCE_DIR}/Platform/Null.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/SDL3Platform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/SDL3Platform.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Platform.hpp

    # Renderers 
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Base.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Base.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/OpenGL.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/OpenGL.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Renderers/SDLOpenGL.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Renderers/SDLOpenGL.hpp
    
    # Skins
    ${CMAKE_CURRENT_SOURCE_DIR}/Skins/Base.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Skins/Base.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Skins/Simple.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Skins/TexturedBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Skins/Texturing.h
    
    # Controls 
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Base.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Base.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Canvas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Canvas.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Label.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Label.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Text.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Text.hpp
    
    ## TODO: Update 
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Button.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Button.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/CheckBox.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/CheckBox.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/CollapsibleCategory.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/CollapsibleCategory.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/CollapsibleList.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ColorControls.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ColorControls.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ColorPicker.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ColorPicker.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ComboBox.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ComboBox.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/CrossSplitter.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/CrossSplitter.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/DockBase.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/DockBase.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/DockedTabControl.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/DockedTabControl.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dragger.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dragger.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/FieldLabel.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/FilePicker.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/FolderPicker.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/GroupBox.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/GroupBox.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Highlight.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/HorizontalScrollBar.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/HorizontalScrollBar.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/HorizontalSlider.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/HorizontalSlider.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/HSVColorPicker.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/HSVColorPicker.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ImagePanel.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ImagePanel.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/LabelClickable.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/LabelClickable.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ListBox.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ListBox.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Menu.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Menu.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/MenuItem.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/MenuItem.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/MenuStrip.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/MenuStrip.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Modal.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/NumericUpDown.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/NumericUpDown.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/PageControl.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/PageControl.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ProgressBar.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ProgressBar.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Properties.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Properties.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/PropertyTree.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/PropertyTree.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/RadioButton.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/RadioButton.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/RadioButtonController.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/RadioButtonController.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Rectangle.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Rectangle.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ResizableControl.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ResizableControl.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Resizer.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Resizer.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/RichLabel.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/RichLabel.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBar.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBar.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBarBar.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBarBar.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBarButton.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBarButton.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollControl.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollControl.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Slider.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Slider.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/SplitterBar.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/SplitterBar.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Splitters.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/StatusBar.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabButton.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabButton.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabControl.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabControl.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabStrip.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabStrip.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabTitleBar.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TextBox.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TextBox.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TextBoxNumeric.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/ToolBar.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TreeControl.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TreeControl.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TreeNode.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/TreeNode.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/VerticalScrollBar.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/VerticalScrollBar.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/VerticalSlider.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/VerticalSlider.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/WindowButtons.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/WindowCanvas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/WindowCanvas.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/WindowControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/WindowControl.hpp

    # Layouts
    #${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Layout/Position.h  
    #${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Layout/Table.h  
    #${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Layout/Tile.h

    # Property
    #${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/BaseProperty.h  
    #${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/ColorSelector.h  
    #${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/File.h    
    #${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/Text.h
    #${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/Checkbox.h      
    #${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/ComboBox.h       
    #${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/Folder.h

    #
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/FileOpen.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/FileOpen.h  
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/FileSave.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/FileSave.h  
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/FolderOpen.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/FolderOpen.h  
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/Query.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/Query.h
    )

add_library( cbGwen STATIC ${GWEN_SOURCES} )
target_include_directories( cbGwen PRIVATE ${CMAKE_SOURCE_DIR}/include )
target_compile_definitions( cbGwen PRIVATE "-DGWEN_NO_ANIMATION" )
target_precompile_headers( cbGwen 
    PRIVATE 
        <cstdio>
        <cstdint>
        <cstdlib>
        <cstring>
        <vector>
        <string>
        <set>
        <list>
        <map>
        <algorithm>
        <atomic>
        <memory.h>
    #PUBLIC // we don't leak to test app  
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Macros.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Config.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Exports.h>"
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Structures.h>"
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Platform/Platform.hpp>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/AutoPointer.hpp>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Utility.hpp>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Debug.hpp>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/TextObject.hpp>"
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Font.h>"
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Texture.hpp>"
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Renderer/Base.hpp>"
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Skins/Base.hpp>"
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/ControlList.h>"
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Events.h>"
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/DragAndDrop.h>"
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/UserData.h>"
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Controls/Base.hpp>"
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/ToolTip.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen/Gwen.hpp>" 
    )