/*ffmpeg_test.c*/

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <stdio.h>
 
int main(int argc,char*argv[])
{
	av_register_all();
	printf("hello, ffmpeg_test!\n");
	return 0;
}
