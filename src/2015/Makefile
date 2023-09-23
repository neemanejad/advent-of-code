CPPFLAGS = g++ -Wall -Werror -g

ARTIFACTS = 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

.PHONY: all

all: $(ARTIFACTS)

$(ARTIFACTS): %: %.cpp
	$(CPPFLAGS) -o $@ $<

%.cpp:
	touch $@; echo "int main(void) { return 0; }" >> $@

clean: 
	rm -rf $(ARTIFACTS)