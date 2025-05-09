ANSI      = -ansi -pedantic -Wall -Wextra -std=c99
DEBUG     = -O0 -gdwarf-2 -g3 -ggdb
OPTIMIZE  = -O2

.PHONY: all
all: shell tester

shell: pcf.h pcf.c shell.c
	gcc $(ANSI) $(OPTIMIZE) -lm -lc -lgmp -o $@ $^

tester: pcf.h pcf.c tester.c
	gcc $(ANSI) $(OPTIMIZE) -lm -lc -lgmp -o $@ $^

## Clean up
clean:
	@echo Cleaning Up
	rm -f shell tester
