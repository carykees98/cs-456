projectName = chat-app
cppStandard = c++17

sourceFolder = src/
intermediateFolder = intermediates/
output = build/$(projectName)

objects = RSA.o client.o
objectFiles = $(intermediateFolder)RSA.o $(intermediateFolder)client.o
linkedLibraries = -lm -lntl -lgmp -lzmqpp -lzmq
main = $(sourceFolder)main.cpp

all: $(project-name)-main

$(project-name)-main: $(main) $(objects) build/
	g++ -std=$(cppStandard) $(main) $(objectFiles) -o $(output) $(linkedLibraries)

RSA.o: intermediates/ $(sourceFolder)RSA.cpp $(sourceFolder)RSA.h
	g++ -c -std=$(cppStandard) $(sourceFolder)RSA.cpp -o $(intermediateFolder)RSA.o

client.o: intermediates/ $(sourceFolder)client.cpp $(sourceFolder)client.h
	g++ -c -std=$(cppStandard) $(sourceFolder)client.cpp -o $(intermediateFolder)client.o

intermediates/:
	mkdir intermediates

build/:
	mkdir build

clean: 
	rm *.o
