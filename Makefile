COMPILING_TEXT 	   := @echo -e "\033[0m \033[0;33m Compiling:\033[0m"
COMPILING_TEXT_OK  := @echo -e "\033[0m \033[0;32m [All compiled succesfully]\033[0m"
LINKING_TEXT       := @echo -e "\033[0m \033[0;33m Linking...\033[0m"
LINKING_TEXT_OK    := @echo -e "\033[0m \033[0;32m [Linked succesfully]\033[0m"
ALL_CLEANED_TEXT   := @echo -e "\033[0m \033[0;32m [Cleaned succesfully]\033[0m"
ENGINE_CLEANED_TEXT:= @echo -e "\033[0m \033[0;32m [Engine cleaned succesfully]\033[0m"
SRC_CLEANED_TEXT   := @echo -e "\033[0m \033[0;32m [SRC cleaned succesfully]\033[0m"
#EXECUTING_TEXT     := @echo -e "\033[0m \033[5;32m Executing...\033[0m"
JUMP_LINE		   := @echo



SOURCES  	:= $(wildcard *.cpp)

NAME_EXE	:= IntoTheCrops
CXXFLAGS 	+= -Wall -Wno-unknown-pragmas -std=c++20 

# Objs del juego

OBJ_PATH    := obj
SRC_PATH	:= src

ALLCPPS		:= $(shell find src/ -type f -iname *.cpp)
ALLCPPSOBJ	:= $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(ALLCPPS))
SUBDIRS		:= $(shell find src/ -type d)
OBJSUBDIRS  := $(patsubst $(SRC_PATH)%,$(OBJ_PATH)%,$(SUBDIRS))



ALLCS		:= $(shell find src/ -type f -iname *.c)
ALLCSOBJ	:= $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(ALLCS))

# Objs de Engine

OBJ_CLE_PATH    := obj
SRC_CLE_PATH  	:= src
MAIN_CLE		:= obj/main.o


ifdef DEBUG
	CXXFLAGS += -g
else
	CXXFLAGS += -O3
endif

LIBS 	    +=  -L./includes -L./src/fmod/core/inc -L./lib/fmod/lib -L./src/IMGUI/src -Wl,-rpath=includes 
LIBS 	    +=  -lfmod -lfmodstudio -lfreetype -lGLEW -limgui -lglfw -lGL -lassimp #-lasan

INCLUDE     := -I./lib/fmod/lib -I./src/fmod/core/inc -I./src/fmod/studio/inc -I./src/fmod/fsbank/inc -I./includes -I./src/IMGUI/src
CC			:= g++

SANITIZE     := -g3 #-fsanitize=address#,undefined

ifdef CACHE
	CC := ccache g++
	CXXFLAGS += -fuse-ld=gold
else
	CC := g++
endif


#Esto crea el ejecutable
# Junta todos los .o en un ejecutable
$(NAME_EXE): $(OBJSUBDIRS) $(ALLCPPSOBJ) $(ALLCSOBJ) 
	$(COMPILING_TEXT_OK)
	$(JUMP_LINE)
	$(LINKING_TEXT)
	$(CC) $(SANITIZE) -o $(NAME_EXE)  $(ALLCSOBJ) $(ALLCPPSOBJ)  $(INCLUDE) $(LIBS) $(CXXFLAGS)
	$(LINKING_TEXT_OK)
	$(JUMP_LINE)


#Compila todos los cpp y los pasa a .o
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(PRUEBA_TEXT)
	$(COMPILING_TEXT) $<
	@$(CC) $(CXXFLAGS) -o $@ -c $^ $(INCLUDE)
	

$(OBJSUBDIRS):
	@mkdir -p $(OBJSUBDIRS)

info:
	$(info --------- Informacion ----------)
	$(info Objetos CPP: $(ALLCPPSOBJ_CLE))
	$(info Subdirs: $(SUBDIRS))
	$(info Objsubdirs: $(OBJSUBDIRS))
	$(info Bin: $(BIN)/)
	$(info AllCpps: $(ALLCPPS))
	$(info AllObj: $(ALLCPPSOBJ))

.PHONY: clean
clean:
	@rm -Rf obj/ || rm -f $(NAME_EXE)
	$(SRC_CLEANED_TEXT)

.PHONY: all
all:
	@make clean && make -j && ./IntoTheCrops

.PHONY: c
c:
	@make -j && ./IntoTheCrops

.PHONY: laure
laure:
	@make clean && make -j4 && ./IntoTheCrops
