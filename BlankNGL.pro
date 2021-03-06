# This specifies the exe name
TARGET=BlankNGL
# where to put the .o files
OBJECTS_DIR=obj
# core Qt Libs to use add more here if needed.
QT+=gui opengl core

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
	cache()
	DEFINES +=QT5BUILD
}
# where to put moc auto generated files
MOC_DIR=moc
# on a mac we don't create a .app bundle file ( for ease of multiplatform use)
CONFIG-=app_bundle
# Auto include all .cpp files in the project src directory (can specifiy individually if required)
SOURCES+= $$PWD/src/BaseObject.cpp \
          $$PWD/src/CollisionThread.cpp \
          $$PWD/src/ImpactObject.cpp \
          $$PWD/src/main.cpp \
          $$PWD/src/Model.cpp \
          $$PWD/src/NGLScene.cpp \
          $$PWD/src/NGLSceneMouseControls.cpp \
          $$PWD/src/ObjectUpdateThread.cpp \
          $$PWD/src/ParticleContainer.cpp

# same for the .h files
HEADERS+= $$PWD/include/BaseObject.h \
          $$PWD/include/CollisionThread.h \
          $$PWD/include/ImpactObject.h \
          $$PWD/include/Model.h \
          $$PWD/include/NGLScene.h \
          $$PWD/include/ObjectUpdateThread.h \
          $$PWD/include/Particle.h \
          $$PWD/include/ParticleContainer.h \
          $$PWD/include/Ray.h \
          $$PWD/include/WindowParams.h

# Didn't end up using CUDA, but will leave things commented for future reference
# and add the include dir into the search path for Qt and make
INCLUDEPATH +=./include
#INCLUDEPATH += $$PWD/cuda/include

#CUDA_PATH = "/usr"
#NVCC_CXXFLAGS += -ccbin g++
#NVCC = $(CUDA_PATH)/bin/nvcc

#NVCC_OPTIONS = --use_fast_math

#OS_SIZE = 64
# Compute capabilities
#SMS = 50 52

#for(sm, SMS) {
#  GENCODE_FLAGS += -gencode arch=compute_$$sm,code=sm_$$sm
#}

#INCLUDEPATH += /usr/include/cuda

#CUDA_INCLUDES = $$join(INCLUDEPATH, ' -I', '-I', '')

#QMAKE_LIBDIR += $$CUDA_PATH/lib
#LIBS += -lcudart

#OTHER_FILES += $$CUDA_SOURCES $$CUDA_HEADERS

#cuda.input = CUDA_SOURCES
#cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
#cuda.commands = $$NVCC $$NVCC_CXXFLAGS -m$$OS_SIZE $$GENCODE_FLAGS -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME} $$NVCC_OPTIONS $$CUDA_INCLUDES
#cuda.dependency_type = TYPE_C

#QMAKE_EXTRA_COMPILERS += cuda
#CUDA_ARCH = sm_20

#NVCCFLAGS     = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v

# Prepare the extra compiler configuration
#CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')

#cuda.commands = $$CUDA_DIR/bin/nvcc -m64 -O3 -arch=$$CUDA_ARCH -c $$NVCCFLAGS \
#                $$CUDA_INC $$LIBS  ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT} \
#               2>&1 | sed -r \"s/\\(([0-9]+)\\)/:\\1/g\" 1>&2
# nvcc error printout format ever so slightly different from gcc
# http://forums.nvidia.com/index.php?showtopic=171651

#cuda.dependency_type = TYPE_C # there was a typo here. Thanks workmate!
#cuda.depend_command = $$CUDA_DIR/bin/nvcc -O3 -M $$CUDA_INC $$NVCCFLAGS   ${QMAKE_FILE_NAME}

#cuda.input = CUDA_SOURCES
#cuda.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}_cuda.o
# Tell Qt that we want add more stuff to the Makefile
#QMAKE_EXTRA_COMPILERS += cuda
# where our exe is going to live (root of project)
DESTDIR=./
# add the glsl shader files
OTHER_FILES+= README.md \
              $$PWD/models/Bomberman_fixed.obj \
              $$PWD/models/Sphere.obj \
              $$PWD/models/Particle.obj \
              $$PWD/shaders/VertShader.glsl \
              $$PWD/shaders/FragShader.glsl \
              $$PWD/textures/ParticleTexture.png
# were are going to default to a console app
CONFIG += console
# note each command you add needs a ; as it will be run as a single line
# first check if we are shadow building or not easiest way is to check out against current
#!equals(PWD, $${OUT_PWD}){
#	copydata.commands = echo "creating destination dirs" ;
#	# now make a dir
#	copydata.commands += mkdir -p $$OUT_PWD/shaders ;
#	copydata.commands += echo "copying files" ;
#	# then copy the files
#	copydata.commands += $(COPY_DIR) $$PWD/shaders/* $$OUT_PWD/shaders/ ;
#	# now make sure the first target is built before copy
#	first.depends = $(first) copydata
#	export(first.depends)
#	export(copydata.commands)
#	# now add it as an extra target
#	QMAKE_EXTRA_TARGETS += first copydata
#}
NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
	message("including $HOME/NGL")
	include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
	message("Using custom NGL location")
	include($(NGLDIR)/UseNGL.pri)
}
