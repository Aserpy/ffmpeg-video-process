HEADER = -I/home/tronlong/ffmpeg/ffmpeg-3.2.14/host/include
FFMPEG_LIB=-L/home/tronlong/ffmpeg/ffmpeg-3.2.14/host/lib -lavdevice -lavfilter -lavformat -lavcodec -ldl -lX11 -lasound -lSDL -lpthread  -lmp3lame -lfaac -lz -lrt -lswresample -lswscale -lavutil -lm


#export LD_LIBRARY_PATH=/home/tronlong/ffmpeg/ffmpeg-3.2.14/host/lib

all:
	#gcc -o generate_pic generate_pic.c
	#gcc ffmpeg_test.c  -lavdevice -lavfilter -lavformat -lavcodec -ldl -lX11 -lasound -lSDL -lpthread -lopencore-amrwb -lopencore-amrnb -lmp3lame -lgsm -lfaac -lz -lrt -lswresample -lswscale -lavutil -lm
	#gcc -o test ffmpeg_test.c $(HEADER)  $(FFMPEG_LIB)
	g++ -o test ffmpeg_test.cpp $(HEADER)  $(FFMPEG_LIB)

	#g++  $(FFMPEG_LIB) -o yuv2h264 -c yuv2h264.cpp
	#gcc ffmpeg_test.c -lavcodec -lavformat -lavdevice -lavutil -o test

clean:
	rm generate_pic yuv2h264 test