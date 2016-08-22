CC := clang++
CCFLAGS := -g -Wno-c++11-extensions -Werror -Wall -std=c++11 -I inc

default: release

bases := main Helpers Location Board Piece Player SimpleSquare SimpleSquareFactory
OBJs := $(addprefix obj/, $(addsuffix .o, $(bases)))

release: $(OBJs)
	@$(CC) $(CCFLAGS) -o Chess $^

SUTs := Helpers Location Board Piece Player SimpleSquare SimpleSquareFactory
Mocks := MockSquareFactory
SUT_OBJS := $(addprefix obj/, $(addsuffix .o, $(SUTs) $(addprefix mocks/, $(Mocks))))
TEST_OBJS := obj/test/TestMain.o $(addprefix obj/test/Test, $(addsuffix .o, $(SUTs)))

test: $(TEST_OBJS) $(SUT_OBJS)
	@$(CC) $(CCFLAGS) lib/boost/lib/libboost_unit_test_framework.so -o ChessTest $^ -Wl,-rpath,'$$ORIGIN/lib/boost/lib'
	@./ChessTest --report_level=short

clean:
	@rm -rf obj
	@rm -f ChessTest
	@rm -f Chess

obj/test/%.o: test/%.cpp
	@mkdir -p obj
	@mkdir -p obj/test
	@$(CC) $(CCFLAGS) -I lib/boost/include -c -o $@ $^

obj/mocks/%.o: src/mocks/%.cpp
	@mkdir -p obj/mocks
	@$(CC) $(CCFLAGS) -c -o $@ $^

obj/%.o: src/%.cpp
	@mkdir -p obj
	@$(CC) $(CCFLAGS) -c -o $@ $^