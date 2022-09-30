raylib = raylib/src

srcdirs = ./src/*.cpp \
		  ./src/GUI/*.cpp \
		  ./src/GUI/Widget/*.cpp \
		  ./src/Layer/*.cpp \
		  ./src/Mouse/*.cpp \
		  ./src/ObjectManager/*.cpp \
		  ./src/TextureManager/*.cpp \
		  ./src/Windows/*.cpp \
		  ./src/Windows/Object/*.cpp \
		  ./src/Widget/*.cpp

executable: ${srcdirs}
	g++ ${srcdirs} -o executable -I${raylib} -L${raylib} -lraylib -ldl -lpthread