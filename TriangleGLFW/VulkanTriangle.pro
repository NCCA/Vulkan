TARGET=VulkanTriangle
CONFIG+=c++14
SOURCES+=$$PWD/src/main.cpp \
         $$PWD/src/VulkanInstance.cpp

HEADERS+=$$PWD/include/VulkanInstance.h

OTHER_FILES+=$$PWD/src/*.glsl

VULKAN_SDK=/Users/jmacey/teaching/Vulkan/vulkansdk-macos-1.1.73.0/MoltenVK
VULKANSDKBASE=/Users/jmacey/teaching/Vulkan/vulkansdk-macos-1.1.73.0/MoltenVK
INCLUDEPATH+= $$VULKANSDKBASE/include
message($$INCLUDEPATH)
INCLUDEPATH += $$PWD/include
INCLUDEPATH += /usr/local/include
CONFIG -= app_bundle
LIBS += -L$$VULKANSDKBASE/macOS -lMoltenVK
macx:LIBS+=-L/usr/local/lib -lglfw3 -framework Cocoa -framework Metal -framework IOKit -framework CoreVideo



## VertexShaders
VERTEXSHADERS=$$PWD/shaders/TriangleVertex.glsl
# this flag list the sources we wish to input to this custom compiler, in this case listed above
# in the glslSOURCES variable
glslVertex.input = VERTEXSHADERS
# now we need to say what files to output, for glsl we want to create the .spv
glslVertex.output = ${QMAKE_FILE_BASE}.spv
# this is the actual compile command we wish to call in this case it wil be
# glsl -o (output).c input.l
glslVertex.commands = glslc  -fshader-stage=vertex -o $$PWD/shaders/${QMAKE_FILE_IN_BASE}.spv ${QMAKE_FILE_IN}
glslVertex.CONFIG = no_link target_predeps
# this tells the make clean command what files to remove
glslVertex.clean =  $$PWD/shaders/${QMAKE_FILE_IN_BASE}.spv
# this is just the name of the extra compiler used in the make file (make glsl for example)
glslVertex.name = glslVertex


## FragmentShaders
FRAGMENTSHADERS=$$PWD/shaders/TriangleFragment.glsl
# this flag list the sources we wish to input to this custom compiler, in this case listed above
# in the glslSOURCES variable
glslFragment.input = FRAGMENTSHADERS
# now we need to say what files to output, for glsl we want to create the .spv
glslFragment.output = ${QMAKE_FILE_BASE}.spv
# this is the actual compile command we wish to call in this case it wil be
# glsl -o (output).c input.l
glslFragment.commands = glslc  -fshader-stage=fragment -o $$PWD/shaders/${QMAKE_FILE_IN_BASE}.spv ${QMAKE_FILE_IN}
glslFragment.CONFIG = no_link target_predeps
# this tells the make clean command what files to remove
glslFragment.clean =  $$PWD/shaders/${QMAKE_FILE_IN_BASE}.spv
# this is just the name of the extra compiler used in the make file (make glsl for example)
glslFragment.name = glslFragment
# finally add this to the qmake project so it will have the makefile generated

QMAKE_EXTRA_COMPILERS += glslVertex
QMAKE_EXTRA_COMPILERS += glslFragment
