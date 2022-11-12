raylib = raylib/src


guisrcdir = ./src/GUI/*.cpp \
		    ./src/GUI/Mouse/*.cpp \
		    ./src/GUI/Widget/*.cpp \

srcdirs = ./src/*.cpp \
		  ./src/FileUtil/*.cpp \
		  ./src/Layer/*.cpp \
		  ./src/ObjectManager/*.cpp \
		  ./src/TextureManager/*.cpp \
		  ./src/Windows/*.cpp \
		  ./src/Windows/Instance/*.cpp \
		  ./src/Windows/Layer/*.cpp \
		  ./src/Windows/Object/*.cpp \
		  ./src/Windows/Texture/*.cpp \
		  ./src/Widget/*.cpp

executable: ${srcdirs} ${guisrcdir}
	clang++ ${srcdirs} ${guisrcdir} -o executable -Wall -Wextra -Wno-unused-parameter -I${raylib} ./raylib/src/libraylib.a -ldl -lpthread

lib/libGUI.so: ${guisrcdir}
	g++ ${guisrcdir} -shared -fPIC -o lib/libGUI.so -I${raylib} -L${raylib} -lraylib -ldl -lpthread