main: main.o order.o user.o commodity.o
	g++ -o $@ $^
main.o: main.cpp order.h user.h commodity.h
	g++ -c $<
order.o: order.cpp order.h
	g++ -c $<
user.o: user.cpp user.h
	g++ -c $<
commodity.o: commodity.cpp commodity.h
	g++ -c $<

clean:
	rm -f *.o main
