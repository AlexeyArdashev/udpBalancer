all: udpBalancerBuild

udpBalancerBuild: balancer.o configreader.o exeptions.o limiter.o main.o udpsocket.o
	g++ -o udpBalancer  balancer.o configreader.o exeptions.o limiter.o main.o udpsocket.o

clean:
	rm -rf udpBalancer *.o
balancer.o: balancer.cpp
	g++ -std=c++11 -c -o  balancer.o balancer.cpp

configreader.o: configreader.cpp
	g++ -std=c++11 -c -o   configreader.o configreader.cpp

exeptions.o: exeptions.cpp
	g++ -std=c++11 -c -o  exeptions.o exeptions.cpp

limiter.o: limiter.cpp
	g++ -std=c++11 -c -o  limiter.o limiter.cpp

main.o: main.cpp
	g++ -std=c++11 -c -o main.o main.cpp

udpsocket.o: udpsocket.cpp
	g++ -std=c++11 -c -o udpsocket.o udpsocket.cpp
