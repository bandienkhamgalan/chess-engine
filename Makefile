CC := clang++
CCFLAGS := -Wno-c++11-extensions -std=c++11 -I src

default: release

release: src/main.cpp
	@$(CC) $(CCFLAGS) -o Chess $<

SUTs := Helpers Location
SUT_OBJS := $(addprefix obj/, $(addsuffix .o, $(SUTs)))
TEST_OBJS := obj/test/TestMain.o $(addprefix obj/test/Test, $(addsuffix .o, $(SUTs)))

test: $(TEST_OBJS) $(SUT_OBJS)
	@$(CC) $(CCFLAGS) $(TESTFLAGS) lib/boost/lib/libboost_unit_test_framework.so -o ChessTest $^ -Wl,-rpath,'$$ORIGIN/lib/boost/lib'
	@./ChessTest --report_level=detailed

clean:
	@rm -r obj

obj/test/%.o: src/test/%.cpp
	@mkdir -p obj
	@mkdir -p obj/test
	@$(CC) $(CCFLAGS) -I lib/boost/include -c -o $@ $^

obj/%.o: src/%.cpp
	@mkdir -p obj
	@$(CC) $(CCFLAGS) -c -o $@ $^