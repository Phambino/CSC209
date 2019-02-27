FLAGS = -Wall -Werror -g -std=gnu99
DEPENDENCIES = ptree.h

all: 

serialize: serialize.o

deserialize: 

%.o: %.c ${DEPENDENCIES}
	gcc ${FLAGS} -c $<

clean:
	rm -f *.o serialize deserialize
