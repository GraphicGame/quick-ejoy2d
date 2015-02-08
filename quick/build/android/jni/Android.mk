LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := ejoy2d

LOCAL_SRC_FILES := main.c font.c

LOCAL_SRC_FILES += \
                  ../../../../lib/dfont.c \
                  ../../../../lib/ejoy2dgame.c \
                  ../../../../lib/fault.c \
                  ../../../../lib/label.c \
                  ../../../../lib/lmatrix.c \
                  ../../../../lib/lparticle.c \
                  ../../../../lib/lrenderbuffer.c \
                  ../../../../lib/lshader.c \
                  ../../../../lib/lsprite.c \
                  ../../../../lib/matrix.c \
                  ../../../../lib/particle.c \
                  ../../../../lib/ppm.c \
                  ../../../../lib/render/carray.c \
                  ../../../../lib/render/log.c \
                  ../../../../lib/render/render.c \
                  ../../../../lib/renderbuffer.c \
                  ../../../../lib/scissor.c \
                  ../../../../lib/screen.c \
                  ../../../../lib/screenshot.c \
                  ../../../../lib/shader.c \
                  ../../../../lib/sprite.c \
                  ../../../../lib/spritepack.c \
                  ../../../../lib/texture.c \
                  ../../../lpng.c \
                  ../../../ljpeg.c \
                  ../../../lutils.c \
                  ../../__engine/platform/winfw.c \
                  ../../../../quick/3rd/zlib/adler32.c \
                  ../../../../quick/3rd/zlib/compress.c \
                  ../../../../quick/3rd/zlib/crc32.c \
                  ../../../../quick/3rd/zlib/deflate.c \
                  ../../../../quick/3rd/zlib/infback.c \
                  ../../../../quick/3rd/zlib/inffast.c \
                  ../../../../quick/3rd/zlib/inflate.c \
                  ../../../../quick/3rd/zlib/inftrees.c \
                  ../../../../quick/3rd/zlib/trees.c \
                  ../../../../quick/3rd/zlib/uncompr.c \
                  ../../../../quick/3rd/zlib/zutil.c \
                  ../../../../quick/engine/display/DisplayObject.cpp \
                  ../../../../quick/engine/display/DisplayObjectContainer.cpp \
                  ../../../../quick/engine/display/GlobalDisplayObjects.cpp \
                  ../../../../quick/engine/display/Layer.cpp \
                  ../../../../quick/engine/display/QSprite.cpp \
                  ../../../../quick/engine/display/Stage.cpp \
                  ../../../../quick/engine/events/EventDispatcher.cpp \
                  ../../../../quick/engine/events/TouchEvent.cpp \
                  ../../../../quick/engine/geom/Point.cpp \
                  ../../../../quick/engine/geom/Rectangle.cpp \
                  ../../../../quick/engine_lua_interface/LuaCommon.cpp \
                  ../../../../quick/engine_lua_interface/LuaEvent.cpp \
                  ../../../../quick/engine_lua_interface/LuaLayer.cpp \
                  ../../../../quick/engine_lua_interface/LuaSprite.cpp \
                  ../../../../quick/engine_lua_interface/LuaStage.cpp


LOCAL_SRC_FILES += \
                  ../../../../lua/lapi.c \
                  ../../../../lua/lauxlib.c \
                  ../../../../lua/lbaselib.c \
                  ../../../../lua/lbitlib.c \
                  ../../../../lua/lcode.c \
                  ../../../../lua/lcorolib.c \
                  ../../../../lua/lctype.c \
                  ../../../../lua/ldblib.c \
                  ../../../../lua/ldebug.c \
                  ../../../../lua/ldo.c \
                  ../../../../lua/ldump.c \
                  ../../../../lua/lfunc.c \
                  ../../../../lua/lgc.c \
                  ../../../../lua/linit.c \
                  ../../../../lua/liolib.c \
                  ../../../../lua/llex.c \
                  ../../../../lua/lmathlib.c \
                  ../../../../lua/lmem.c \
                  ../../../../lua/loadlib.c \
                  ../../../../lua/lobject.c \
                  ../../../../lua/lopcodes.c \
                  ../../../../lua/loslib.c \
                  ../../../../lua/lparser.c \
                  ../../../../lua/lstate.c \
                  ../../../../lua/lstring.c \
                  ../../../../lua/lstrlib.c \
                  ../../../../lua/ltable.c \
                  ../../../../lua/ltablib.c \
                  ../../../../lua/ltm.c \
                  ../../../../lua/lundump.c \
                  ../../../../lua/lvm.c \
                  ../../../../lua/lzio.c


LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/../../../../lib \
                    $(LOCAL_PATH)/../../../../lib/render \
                    $(LOCAL_PATH)/../../__engine/platform \
                    $(LOCAL_PATH)/../../../../lua \
                    $(LOCAL_PATH)/../../../../quick/3rd/libpng \
                    $(LOCAL_PATH)/../../../../quick/3rd/libjpeg \
                    $(LOCAL_PATH)/../../../../quick/3rd/zlib \
                    $(LOCAL_PATH)/../../../../quick \
                    $(LOCAL_PATH)/../../../../quick/engine \
                    $(LOCAL_PATH)/../../../../quick/engine/display \
                    $(LOCAL_PATH)/../../../../quick/engine/events \
                    $(LOCAL_PATH)/../../../../quick/engine/geom \
                    $(LOCAL_PATH)/../../../../quick/engine/utils \
                    $(LOCAL_PATH)/../../../../quick/engine_lua_interface \
                    $(LOCAL_PATH)/../../../../quick/incs

LOCAL_CFLAGS += -lstdc++
LOCAL_CONLYFLAGS := -std=c99 -lstdc++
LOCAL_CPPFLAGS += -std=c++11 -lstdc++ -frtti
#LOCAL_CFLAGS += -x c++
LOCAL_LDLIBS := -llog -lGLESv2
LOCAL_LDFLAGS := $(LOCAL_PATH)/libpng.a $(LOCAL_PATH)/libjpeg.a

include $(BUILD_SHARED_LIBRARY)
