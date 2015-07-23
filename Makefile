CC        := g++
LD        := g++

R_DIR     := resource
G_DIR     := src-gen
SRC_DIR   := src nse $(G_DIR)
UT_DIR    := gtest/gtest gtest/utest
BUILD_DIR := build

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cc))
OBJ       := $(patsubst %.cc,build/%.o,$(SRC))
UT_SRC    := $(foreach sdir,$(UT_DIR),$(wildcard $(sdir)/*.cc))
UT_OBJ    := $(patsubst %.cc,build/%.o,$(UT_SRC))
R_SRC     := $(wildcard $(R_DIR)/*.proto)
G_SRC     := $(patsubst $(R_DIR)/%.proto,$(G_DIR)/%.cc,$(R_SRC))
INCLUDES  := -Iinclude -Igtest $(addprefix -I,$(SRC_DIR) $(UT_DIR)) 
LIBS      := -ljson2pb -ljansson -lprotobuf -lpthread
UT_LIBS   := -lboost_iostreams -L/usr/local/lib

.PHONY: all checkdirs clean utest-run protoc 

all: checkdirs build/utest.exe utest-run

$(BUILD_DIR)/utest.exe: $(OBJ) $(UT_OBJ)
	$(LD) $^ $(LIBS) $(UT_LIBS) -o $@
#	@cp -rf gtest/data $(BUILD_DIR)
#	@cd $(BUILD_DIR) && ./utest.exe

utest-run:
	@rm -rf $(BUILD_DIR)/data
	@cp -rf gtest/data $(BUILD_DIR)
	@cd $(BUILD_DIR) && ./utest.exe
			
checkdirs: $(addprefix $(BUILD_DIR)/,$(SRC_DIR) $(UT_DIR))

$(addprefix $(BUILD_DIR)/,$(SRC_DIR) $(UT_DIR)):
	@mkdir -p $@

protoc: $(G_SRC)

$(G_DIR)/%.cc: $(R_DIR)/%.proto
	protoc --proto_path=$(R_DIR) --proto_path=$(PROTOBUF_PATH) --cpp_out=$(G_DIR) $?
		
clean:
	@rm -rf $(BUILD_DIR) 
	#@rm $(G_DIR)/*

$(BUILD_DIR)/%.o: %.cc
	$(CC) -Wall -g -c $(INCLUDES) $< -o $@
