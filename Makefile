APP := CQG_TradeMatchingEndgin
TEST_APP := test_app
SRC_DIR := src
TEST_DIR:= test
OBJ_DIR := obj
DEP_DIR := dep
BIN_DIR := bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.obj,$(SRC_FILES))
TEST_SRC_FILES := $(filter-out src/main.cpp, $(SRC_FILES) $(wildcard $(TEST_DIR)/*.cpp))
TEST_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.obj ,$(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.obj,$(TEST_SRC_FILES)))

CXX=g++
CXXFLAGS= -std=c++11 -pedantic -pedantic-errors -Wall

all: $(OBJ_DIR) $(DEP_DIR) $(BIN_DIR) $(BIN_DIR)/$(APP)

$(BIN_DIR)/$(APP): $(OBJ_FILES)
	@echo Linking $@
	@$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.obj: $(SRC_DIR)/%.cpp
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) -o $@ -c $< -MMD -MF $(patsubst $(SRC_DIR)/%.cpp, $(DEP_DIR)/%.d, $<)


$(BIN_DIR):
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

$(DEP_DIR):
	@mkdir -p $@

.PHONY: clean test
clean:
	@echo Cleaning...
	@rm $(OBJ_DIR) -rf
	@rm $(DEP_DIR) -rf
	@rm $(BIN_DIR) -rf
	@rm $(APP) -f
	@rm $(TEST_APP) -f

.PHONY:
test: $(DEP_DIR) $(OBJ_DIR) $(BIN_DIR) $(BIN_DIR)/$(TEST_APP)
	@./$(BIN_DIR)/$(TEST_APP)

$(BIN_DIR)/$(TEST_APP): $(TEST_OBJ_FILES)
	@$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.obj: $(TEST_DIR)/%.cpp
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) -o $@ -c $< -MMD -MF $(patsubst $(TEST_DIR)/%.cpp, $(DEP_DIR)/%.d, $<)


-include $(DEP_DIR)/*.d

