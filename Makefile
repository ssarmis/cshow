CC = g++
CSTD = -std=c++11
CFLAGS = -Wdeprecated-declarations -fdiagnostics-color -Wfatal-errors -w
CSDLLIB = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
CFFMPEGLIB = -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample -lswscale
CLIBFOLDERS = -Llib/SDL -Llib/ffmpeg
CINCLUDES = -Iinclude/SDL -Iinclude/ffmpeg

all:
	$(CC) $(CFLAGS) $(CSTD) -o build/cshow src/*.cpp $(CINCLUDES) $(CLIBFOLDERS) $(CSDLLIB) $(CFFMPEGLIB)
				    

