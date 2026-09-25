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

    ${CMAKE_CURRENT_SOURCE_DIR}/Align.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Anim.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Anim.h
    ${CMAKE_CURRENT_SOURCE_DIR}/BaseRender.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BaseRender.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ControlList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ControlList.h
    ${CMAKE_CURRENT_SOURCE_DIR}/DragAndDrop.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DragAndDrop.h
    ${CMAKE_CURRENT_SOURCE_DIR}/events.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Events.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Exports.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Font.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Gwen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gwen.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inputhandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/InputHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Hook.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Hook.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Macros.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Skin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Skin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Structures.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TextObject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ToolTip.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ToolTip.h
    ${CMAKE_CURRENT_SOURCE_DIR}/UserData.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.h
    ${CMAKE_CURRENT_SOURCE_DIR}/WindowProvider.h

    # Platform
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Null.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/SDL3Platform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/SDL3Platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Platform.h

    # Renderers 
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Renderers/OpenGL.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Renderers/OpenGL.h
    
    # Skin
    ${CMAKE_CURRENT_SOURCE_DIR}/Skins/Simple.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Skins/TexturedBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Skins/Texturing.h
    
    # Controls 
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Base.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Base.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Button.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Button.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Canvas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Canvas.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/CheckBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/CheckBox.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/CollapsibleCategory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/CollapsibleCategory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/CollapsibleList.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ColorControls.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ColorControls.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ColorPicker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ColorPicker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ComboBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ComboBox.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/CrossSplitter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/CrossSplitter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/DockBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/DockBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/DockedTabControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/DockedTabControl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dragger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dragger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/FieldLabel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/FilePicker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/FolderPicker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/GroupBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/GroupBox.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Highlight.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/HorizontalScrollBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/HorizontalScrollBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/HorizontalSlider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/HorizontalSlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/HSVColorPicker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/HSVColorPicker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ImagePanel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ImagePanel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Label.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Label.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/LabelClickable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/LabelClickable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ListBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ListBox.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Menu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Menu.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/MenuItem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/MenuItem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/MenuStrip.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/MenuStrip.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Modal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/NumericUpDown.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/NumericUpDown.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/PageControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/PageControl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ProgressBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ProgressBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Properties.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Properties.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/PropertyTree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/PropertyTree.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/RadioButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/RadioButton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/RadioButtonController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/RadioButtonController.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Rectangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Rectangle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ResizableControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ResizableControl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Resizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Resizer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/RichLabel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/RichLabel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBarBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBarBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBarButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBarButton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollControl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Slider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Slider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/SplitterBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/SplitterBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Splitters.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/StatusBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabButton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabControl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabStrip.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabStrip.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabTitleBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Text.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Text.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TextBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TextBox.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TextBoxNumeric.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ToolBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TreeControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TreeControl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TreeNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TreeNode.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/VerticalScrollBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/VerticalScrollBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/VerticalSlider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/VerticalSlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/WindowButtons.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/WindowCanvas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/WindowCanvas.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/WindowControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/WindowControl.h

    # Layouts
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Layout/Position.h  
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Layout/Table.h  
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Layout/Tile.h

    # Property
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/BaseProperty.h  
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/ColorSelector.h  
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/File.h    
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/Text.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/Checkbox.h      
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/ComboBox.h       
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/Folder.h

    #
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/FileOpen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/FileOpen.h  
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/FileSave.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/FileSave.h  
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/FolderOpen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/FolderOpen.h  
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/Query.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialogs/Query.h
    )

add_library( cbGewen STATIC ${GWEN_SOURCES} )
target_include_directories( cbGewen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )
target_precompile_headers( cbGewen 
    PRIVATE 
        <cstdio>
        <cstdint>
        <cstdlib>
        <cstring>
        <vector>
        <string>
        <set>
        <list>
        <algorithm>
        <atomic>
        <memory.h>
    PUBLIC 
        "$<$<COMPILE_LANGUAGE:CXX>:Macros.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Config.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Exports.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Structures.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Skin.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Controls/Base.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Controls/Canvas.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Align.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:ToolTip.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Utility.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Platform/Platform.h>" 
        "$<$<COMPILE_LANGUAGE:CXX>:Gwen.h>" 
    )