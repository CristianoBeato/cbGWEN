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

set( GWEN_SOURCES_MAIN 
    ${CMAKE_CURRENT_SOURCE_DIR}/Anim.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BaseRender.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ControlList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DragAndDrop.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/events.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inputhandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gwen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Hook.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Skin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ToolTip.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/Renderers/OpenGL.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/Renderers/FontData.h

    ${CMAKE_SOURCE_DIR}/include/Gwen/Align.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Anim.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/BaseRender.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Config.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/ControlList.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/DragAndDrop.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Events.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Exports.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Font.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Gwen.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Hook.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/InputHandler.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Macros.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Skin.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Structures.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/TextObject.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Texture.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/ToolTip.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/UserData.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Utility.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/WindowProvider.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Skins/Simple.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Skins/TexturedBase.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Skins/Texturing.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Platform/Platform.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Platform/Renderers/OpenGL.h
    )

set( GWEN_SOURCES_CONTROLS
    #
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Base.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Button.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Canvas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/CheckBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/CollapsibleCategory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ColorControls.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ColorPicker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ComboBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/CrossSplitter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialog
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/DockBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/DockedTabControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dragger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/GroupBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/HorizontalScrollBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/HorizontalSlider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/HSVColorPicker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ImagePanel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/LabelClickable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Label.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ListBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Menu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/MenuItem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/MenuStrip.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/NumericUpDown.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/PageControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ProgressBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Properties.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/PropertyTree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/RadioButtonController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/RadioButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Rectangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ResizableControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Resizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/RichLabel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBarBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBarButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/ScrollControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Slider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/SplitterBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TabStrip.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TextBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TextBoxNumeric.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Text.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TreeControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/TreeNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/VerticalScrollBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/VerticalSlider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/WindowCanvas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/WindowControl.cpp   
    # 
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Base.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Button.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Canvas.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/CheckBox.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/CollapsibleCategory.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/CollapsibleList.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/ColorControls.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/ColorPicker.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/ComboBox.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/CrossSplitter.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Dialogs
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/DockBase.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/DockedTabControl.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Dragger.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/FieldLabel.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/FilePicker.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/FolderPicker.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/GroupBox.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Highlight.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/HorizontalScrollBar.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/HorizontalSlider.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/HSVColorPicker.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/ImagePanel.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/LabelClickable.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Label.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Layout
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/ListBox.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Menu.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/MenuItem.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/MenuStrip.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Modal.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/NumericUpDown.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/PageControl.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/ProgressBar.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Properties.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/PropertyTree.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/RadioButtonController.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/RadioButton.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Rectangle.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/ResizableControl.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Resizer.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/RichLabel.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/ScrollBarBar.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/ScrollBarButton.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/ScrollBar.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/ScrollControl.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Slider.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/SplitterBar.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Splitters.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/StatusBar.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/TabButton.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/TabControl.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/TabStrip.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/TabTitleBar.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/TextBox.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Text.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/ToolBar.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/TreeControl.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/TreeNode.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/VerticalScrollBar.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/VerticalSlider.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/WindowButtons.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/WindowCanvas.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/WindowControl.h
    #
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Layout/Position.h  
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Layout/Table.h  
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Layout/Tile.h
    #
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/BaseProperty.h  
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/ColorSelector.h  
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/File.h    
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/Text.h
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/Checkbox.h      
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/ComboBox.h       
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Property/Folder.h
    )

set( GWEN_SOURCES_CONTROLS_DIALOGS
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialog/FileOpen.cpp
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Dialogs/FileOpen.h  
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialog/FileSave.cpp
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Dialogs/FileSave.h  
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialog/FolderOpen.cpp
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Dialogs/FolderOpen.h  
    ${CMAKE_CURRENT_SOURCE_DIR}/Controls/Dialog/Query.cpp
    ${CMAKE_SOURCE_DIR}/include/Gwen/Controls/Dialogs/Query.h
    )

set( GWEN_SOURCES 
    ${GWEN_SOURCES_MAIN}
    ${GWEN_SOURCES_CONTROLS}
    ${GWEN_SOURCES_CONTROLS_DIALOGS}
    )

add_library( cbGewen STATIC ${GWEN_SOURCES} )
target_include_directories( cbGewen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )
target_precompile_headers( cbGewen 
    PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.hpp>" 
    PUBLIC "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/include/Gwen/Gwen.h>" 
    )