# ffmpeg-video-process
通过ffmpeg实现图像处理


1.generate_pic.c 

2. yuv video generate:ffmpeg -f lavfi -i testsrc=duration=100:size=1280x720:rate=30:decimals=2 -pix_fmt yuv420p output.yuv

3. yuv2h264.c  yuv video convert to h264 video 
