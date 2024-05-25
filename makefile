C_FLAGS = -c -Wall -fopenmp
LINK_FLAGS = -fopenmp -lgdi32 -o

all: ray_tracing

ray_tracing: main.o functions.o Cuboid.o Sphere.o Tetrahedron.o Disp.o Kinescope.o autotests.o Point.o Figure.o
	g++ main.o functions.o Cuboid.o Sphere.o Tetrahedron.o Disp.o Kinescope.o autotests.o Point.o Figure.o $(LINK_FLAGS) ray_tracing

main.o: main.cpp
	g++ $(C_FLAGS) main.cpp

functions.o: functions.cpp
	g++ $(C_FLAGS) functions.cpp

Cuboid.o: Cuboid.cpp
	g++ $(C_FLAGS) Cuboid.cpp

Sphere.o: Sphere.cpp
	g++ $(C_FLAGS) Sphere.cpp

Tetrahedron.o: Tetrahedron.cpp
	g++ $(C_FLAGS) Tetrahedron.cpp

Disp.o: Disp.cpp
	g++ $(C_FLAGS) Disp.cpp

Kinescope.o: Kinescope.cpp
	g++ $(C_FLAGS) Kinescope.cpp

autotests.o: autotests.cpp
	g++ $(C_FLAGS) autotests.cpp

Point.o: Point.cpp
	g++ $(C_FLAGS) Point.cpp

Figure.o: Figure.cpp
	g++ $(C_FLAGS) Figure.cpp


clean: 
	rm -rf *.o ray_tracing