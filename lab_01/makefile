#inlcude src
cc := gcc
cflags := -Wall -Werror -pedantic
header := ./head/
object := ./obj/
source := ./src/

# obj := $(srx:.c=.o)

run: app.exe
	./app.exe
	
app.exe: $(object)main.o $(object)normalize.o $(object)IO.o $(object)division.o
	$(cc) $^  -o $@
	
$(object)main.o: main.c $(header)main.h
	$(cc) $(cflags) -I$(header) -c $< -o $@

$(object)normalize.o: $(source)normalize.c $(header)normalize.h
	$(cc) $(cflags) -I$(header) -c $< -o $@

$(object)IO.o: $(source)IO.c $(header)io.h
	$(cc) $(cflags) -I$(header) -c $< -o $@

$(object)division.o: $(source)division.c $(header)functions.h
	$(cc) $(cflags) -I$(header) -c $< -o $@

.PHONY: clean
del: clean

clean:
	rm -rf *.exe ./obj/*.o
