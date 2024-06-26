cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)

# dirty hack to force disable wayland for glfw (idk how to do it properly)
option(GLFW_BUILD_WAYLAND "yolo" OFF)

project(editiles)
add_subdirectory(raylib)

add_executable(editiles
        ./src/GUI/TabsHandler.cpp
        ./src/GUI/Mouse/DragAndDropObject.cpp
        ./src/GUI/Mouse/MouseObject.cpp
        ./src/GUI/WindowCorner.cpp
        ./src/GUI/Widget/Label.cpp
        ./src/GUI/Widget/ElementList.cpp
        ./src/GUI/Widget/U8Field.cpp
        ./src/GUI/Widget/CppStringValue.cpp
        ./src/GUI/Widget/Button.cpp
        ./src/GUI/Widget/Widget.cpp
        ./src/GUI/Widget/IntValue.cpp
        ./src/GUI/Widget/WidgetManager.cpp
        ./src/GUI/Widget/IntField.cpp
        ./src/GUI/Widget/CppStringField.cpp
        ./src/GUI/BorderlessWindow.cpp
        ./src/GUI/Themes/ColorTheme.cpp
        ./src/GUI/Window.cpp
        ./src/GUI/WindowManager.cpp
        ./src/GUI/TabBar.cpp
        ./src/GUI/BottomBar.cpp
        ./src/GUI/MainWindow.cpp
        ./src/ParseFunctions.cpp
        ./src/Level.cpp
        ./src/Application.cpp
        ./src/EditorTabsHandler.cpp
        ./src/Widget/InstancePropertiesList.cpp
        ./src/Widget/TextureList.cpp
        ./src/Widget/TexturePreview.cpp
        ./src/Widget/ObjectList.cpp
        ./src/Widget/LayerList.cpp
        ./src/Widget/ImageFileReceiver.cpp
        ./src/Widget/Palette.cpp
        ./src/Widget/ObjectPropertiesList.cpp
        ./src/Layer/GridLayer.cpp
        ./src/Layer/InstanceLayer.cpp
        ./src/Layer/Instance.cpp
        ./src/Layer/Layer.cpp
        ./src/FileUtil/PathUtil.cpp
        ./src/FileUtil/FileUtil.cpp
        ./src/main.cpp
        ./src/Editor.cpp
        ./src/ObjectManager/ObjectProperty.cpp
        ./src/ObjectManager/ObjectTemplate.cpp
        ./src/ObjectManager/ObjectManager.cpp
        ./src/TextureManager/TextureManager.cpp
        ./src/TextureManager/TextureObject.cpp
        ./src/Windows/SaveWindow.cpp
        ./src/Windows/Texture/TextureInfoWindow.cpp
        ./src/Windows/Texture/TextureListWindow.cpp
        ./src/Windows/Texture/NewTextureWindow.cpp
        ./src/Windows/ZoomWindow.cpp
        ./src/Windows/Object/NewPropertyWindow.cpp
        ./src/Windows/Object/RenameObjectWindow.cpp
        ./src/Windows/Object/ObjectInfoWindow.cpp
        ./src/Windows/Object/ChangePropertyWindow.cpp
        ./src/Windows/Object/NewObjectWindow.cpp
        ./src/Windows/Object/RenamePropertyWindow.cpp
        ./src/Windows/Object/ObjectListWindow.cpp
        ./src/Windows/Layer/LayerInfoWindow.cpp
        ./src/Windows/Layer/LayerListWindow.cpp
        ./src/Windows/PaletteWindow.cpp
        ./src/Windows/NewLevelWindow.cpp
        ./src/Windows/Instance/ChangeInstancePropWindow.cpp
        ./src/Windows/Instance/InstanceInfoWindow.cpp
        ./src/CLI.cpp
)

target_link_libraries(editiles PRIVATE raylib)
