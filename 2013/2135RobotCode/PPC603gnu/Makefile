# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = PPC603gnu
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := C:/windriver/workspace
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/2013-RobotCode



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPC603
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 

IDE_DEFINES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif


#Project Targets
PROJECT_TARGETS = 2013-RobotCode/$(MODE_DIR)/2013-RobotCode.out \
	 2013-RobotCode_partialImage/$(MODE_DIR)/2013-RobotCode_partialImage.o


#Rules

# 2013-RobotCode
ifeq ($(DEBUG_MODE),1)
2013-RobotCode/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
2013-RobotCode/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
2013-RobotCode/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
2013-RobotCode/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
2013-RobotCode/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
2013-RobotCode/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
2013-RobotCode/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
2013-RobotCode/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
2013-RobotCode/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
2013-RobotCode/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
2013-RobotCode/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
2013-RobotCode/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
2013-RobotCode/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h/wrn/coreip 
2013-RobotCode/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
2013-RobotCode/$(MODE_DIR)/% : IDE_DEFINES = 
2013-RobotCode/$(MODE_DIR)/% : PROJECT_TYPE = DKM
2013-RobotCode/$(MODE_DIR)/% : DEFINES = 
2013-RobotCode/$(MODE_DIR)/% : EXPAND_DBG = 0
2013-RobotCode/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
2013-RobotCode/$(MODE_DIR)/% : CPU = PPC603
2013-RobotCode/$(MODE_DIR)/% : TOOL_FAMILY = gnu
2013-RobotCode/$(MODE_DIR)/% : TOOL = gnu
2013-RobotCode/$(MODE_DIR)/% : TOOL_PATH = 
2013-RobotCode/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
2013-RobotCode/$(MODE_DIR)/% : LIBPATH = 
2013-RobotCode/$(MODE_DIR)/% : LIBS = 
2013-RobotCode/$(MODE_DIR)/% : OBJ_DIR := 2013-RobotCode/$(MODE_DIR)

OBJECTS_2013-RobotCode = 2013-RobotCode_partialImage/$(MODE_DIR)/2013-RobotCode_partialImage.o

2013-RobotCode/$(MODE_DIR)/2013-RobotCode.out : $(OBJECTS_2013-RobotCode)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmppc $(OBJECTS_2013-RobotCode) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_2013-RobotCode) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS)  $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

2013-RobotCode/$(MODE_DIR)/2013-RobotCode_compile_file : $(FILE) ;

_clean :: 2013-RobotCode/$(MODE_DIR)/2013-RobotCode_clean

2013-RobotCode/$(MODE_DIR)/2013-RobotCode_clean : 
	$(TRACE_FLAG)if [ -d "2013-RobotCode" ]; then cd "2013-RobotCode"; rm -rf $(MODE_DIR); fi


# 2013-RobotCode_partialImage
ifeq ($(DEBUG_MODE),1)
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
2013-RobotCode_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h/wrn/coreip 
2013-RobotCode_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
2013-RobotCode_partialImage/$(MODE_DIR)/% : IDE_DEFINES = 
2013-RobotCode_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
2013-RobotCode_partialImage/$(MODE_DIR)/% : DEFINES = 
2013-RobotCode_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
2013-RobotCode_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
2013-RobotCode_partialImage/$(MODE_DIR)/% : CPU = PPC603
2013-RobotCode_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = gnu
2013-RobotCode_partialImage/$(MODE_DIR)/% : TOOL = gnu
2013-RobotCode_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
2013-RobotCode_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
2013-RobotCode_partialImage/$(MODE_DIR)/% : LIBPATH = 
2013-RobotCode_partialImage/$(MODE_DIR)/% : LIBS = 
2013-RobotCode_partialImage/$(MODE_DIR)/% : OBJ_DIR := 2013-RobotCode_partialImage/$(MODE_DIR)

2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/CommandBase.o : $(PRJ_ROOT_DIR)/CommandBase.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/CommandBasedRobot.o : $(PRJ_ROOT_DIR)/CommandBasedRobot.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Commands/DriveInASquare.o : $(PRJ_ROOT_DIR)/Commands/DriveInASquare.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Commands/DriveStraight.o : $(PRJ_ROOT_DIR)/Commands/DriveStraight.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Commands/DriveWithJoystick.o : $(PRJ_ROOT_DIR)/Commands/DriveWithJoystick.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Commands/Turn.o : $(PRJ_ROOT_DIR)/Commands/Turn.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/OI.o : $(PRJ_ROOT_DIR)/OI.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Subsystems/Chassis.o : $(PRJ_ROOT_DIR)/Subsystems/Chassis.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


OBJECTS_2013-RobotCode_partialImage = 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/CommandBase.o \
	 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/CommandBasedRobot.o \
	 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Commands/DriveInASquare.o \
	 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Commands/DriveStraight.o \
	 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Commands/DriveWithJoystick.o \
	 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Commands/Turn.o \
	 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/OI.o \
	 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Subsystems/Chassis.o

2013-RobotCode_partialImage/$(MODE_DIR)/2013-RobotCode_partialImage.o : $(OBJECTS_2013-RobotCode_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X  -o "$@" $(OBJECTS_2013-RobotCode_partialImage) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS)  && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

2013-RobotCode_partialImage/$(MODE_DIR)/2013-RobotCode_partialImage_compile_file : $(FILE) ;

_clean :: 2013-RobotCode_partialImage/$(MODE_DIR)/2013-RobotCode_partialImage_clean

2013-RobotCode_partialImage/$(MODE_DIR)/2013-RobotCode_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "2013-RobotCode_partialImage" ]; then cd "2013-RobotCode_partialImage"; rm -rf $(MODE_DIR); fi

force : 

DEP_FILES := 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/CommandBase.d 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/CommandBasedRobot.d 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Commands/DriveInASquare.d \
	 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Commands/DriveStraight.d 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Commands/DriveWithJoystick.d 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Commands/Turn.d \
	 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/OI.d 2013-RobotCode_partialImage/$(MODE_DIR)/Objects/2013-RobotCode/Subsystems/Chassis.d
-include $(DEP_FILES)



-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
