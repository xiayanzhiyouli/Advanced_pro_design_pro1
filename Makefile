main: main.o order.o user.o commodity.o admin.o time.o signIn.o refresh.cpp
	g++ -o $@ $^
main.o: main.cpp order.h user.h commodity.h admin.h time.h signIn.h refresh.h
	g++ -c $<
order.o: order.cpp order.h
	g++ -c $<
user.o: user.cpp user.h 
	g++ -c $<
commodity.o: commodity.cpp commodity.h
	g++ -c $<
admin.o: admin.cpp admin.h
	g++ -c $<
time.o: time.cpp time.h
	g++ -c $<
signIn.o: signIn.cpp signIn.h
	g++ -c $<
refresh.o: refresh.cpp refresh.h
	g++ -c $<

clean:
	rm -f *.o main