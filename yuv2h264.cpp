/**************************************************
Copyright:
Author:cxw
Date:2019.08.
Filename:yuv2h264.c
Description:yuv video convert to h264 video.
**************************************************/

#include <iostream>

extern "C"
{
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libavutil/imgutils.h>
	#include <libavutil/opt.h>
}


#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
#endif

using namespace std;


// static void encode(AVCodecContext *enc_ctx, AVFrame *frame, AVPacket *pkt, FILE *outfile)
// {
//     int ret;
//     if (frame)
//         printf("Send frame %3lld\n", frame->pts);
//     ret = avcodec_send_frame(enc_ctx, frame);
//     if (ret < 0)
//     {
//         fprintf(stderr, "Error sending a frame for encoding\n");
//         exit(1);
//     }
//     while (ret >= 0)
//     {
//         ret = avcodec_receive_packet(enc_ctx, pkt);
//         if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
//             return;
//         else if (ret < 0)
//         {
//             fprintf(stderr, "Error during encoding\n");
//             exit(1);
//         }
//         printf("Write packet %3lld(size=%5d)\n", pkt->pts, pkt->size);
//         fflush(stdout);
//         fwrite(pkt->data, 1, pkt->size, outfile);
//         av_packet_unref(pkt);
//     }
// }
// int EncodeYUVToH264(const char *input_fileName, const char* out_fileName, int in_w, int in_h, int framenum)
// {
//     // 打开输入YUV序列
//     FILE *in_file = NULL;
//     fopen_s(&in_file, input_fileName, "rb");
//     if (!in_file)
//     {
//         cout << "can not open file!" << endl;
//         return -1;
//     }

//     // 打开输出视频文件
//     FILE *out_file = NULL;
//     fopen_s(&out_file, out_fileName, "wb");

//     // 初始化AVFormatContext结构体,根据文件名获取到合适的封装格式
//     AVFormatContext *pFormatCtx = avformat_alloc_context();
//     avformat_alloc_output_context2(&pFormatCtx, NULL, NULL, out_fileName);
//     AVOutputFormat *fmt = pFormatCtx->oformat;

//     // 初始化视频码流
//     AVStream *video_st = avformat_new_stream(pFormatCtx, 0);
//     if (video_st == NULL)
//     {
//         printf("failed allocating output stream\n");
//         return -1;
//     }
//     video_st->time_base.num = 1;
//     video_st->time_base.den = 25;

//     // 编码器Context设置参数
//     AVCodecContext *pCodecCtx = avcodec_alloc_context3(NULL);
//     avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[0]->codecpar);
//     pCodecCtx->codec_id = fmt->video_codec;
//     pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
//     pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
//     pCodecCtx->width = in_w;
//     pCodecCtx->height = in_h;
//     pCodecCtx->time_base.num = 1;
//     pCodecCtx->time_base.den = 25;
//     pCodecCtx->bit_rate = 400000;
//     pCodecCtx->gop_size = 12;
//     if (pCodecCtx->codec_id == AV_CODEC_ID_H264)
//     {
//         pCodecCtx->qmin = 10;
//         pCodecCtx->qmax = 51;
//         pCodecCtx->qcompress = 0.6;
//     }
//     if (pCodecCtx->codec_id == AV_CODEC_ID_MPEG2VIDEO)
//         pCodecCtx->max_b_frames = 2;
//     if (pCodecCtx->codec_id == AV_CODEC_ID_MPEG1VIDEO)
//         pCodecCtx->mb_decision = 2;

//     // 寻找编码器 
//     AVCodec *pCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
//     if (!pCodec)
//     {
//         cout << "no right encoder!" << endl;
//         return -1;
//     }

//     // 打开编码器
//     if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
//     {
//         cout << "open encoder fail!" << endl;
//         return -1;
//     }

//     // 输出格式信息
//     av_dump_format(pFormatCtx, 0, out_fileName, 1);

//     // 初始化帧
//     AVFrame *pictureFrame = av_frame_alloc();
//     pictureFrame->width = pCodecCtx->width;
//     pictureFrame->height = pCodecCtx->height;
//     pictureFrame->format = pCodecCtx->pix_fmt;

//     // ffmpeg4.0
//     int size = av_image_get_buffer_size(pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, 1);
//     uint8_t *picture_buf = (uint8_t *)av_malloc(size);
//     av_image_fill_arrays(pictureFrame->data, pictureFrame->linesize, picture_buf, AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1);

//     // 写头文件
//     avformat_write_header(pFormatCtx, NULL);

//     // 创建已编码帧
//     AVPacket *pkt = av_packet_alloc();
//     if (!pkt)
//     {
//         return -1;
//     }

//     // 编码器Context大小
//     int y_size = pCodecCtx->width*pCodecCtx->height;

//     //循环每一帧
//     for (int i = 0; i < framenum; i++)
//     {
//         // 读入YUV
//         if (fread(picture_buf, 1, y_size * 3 / 2, in_file) <= 0)
//         {
//             cout << "read file fail!" << endl;
//             return -1;
//         }
//         else if (feof(in_file))
//         {
//             break;
//         }
//         pictureFrame->data[0] = picture_buf; // Y
//         pictureFrame->data[1] = picture_buf + y_size; // U
//         pictureFrame->data[2] = picture_buf + y_size * 5 / 4;// V
//         pictureFrame->pts = i;
//         // encode the image
//         encode(pCodecCtx, pictureFrame, pkt, out_file);
//     }
//     // flush the encoder 
//     encode(pCodecCtx, NULL, pkt, out_file);
//     av_write_trailer(pFormatCtx);
//     // 释放内存
//     av_frame_free(&pictureFrame);
//     av_packet_free(&pkt);
//     avcodec_free_context(&pCodecCtx);
//     av_free(picture_buf);
//     avformat_free_context(pFormatCtx);
//     fclose(out_file);
//     fclose(in_file);
// }






// int main(int argc, char* argv[])
// {
//     cout<<"ffmpeg encode yuv to h264!"<<endl;

//     // 输入YUV序列
//     const char *input_fileName = "output.yuv";
//     // 输入YUV宽度和高度、帧数
//     int in_w = 352, in_h = 288;
//     int framenum = 300;
//     // 输出H264文件
//     const char* out_fileName = "../H264/test_out.h264";
//     if (EncodeYUVToH264(input_fileName, out_fileName, in_w, in_h, framenum) < 0)
//         cout << "encode failed!" << endl;
//     cout << "encode finished!" << endl;

// 	return 0;
// }


//test different codec
#define TEST_H264  1
#define TEST_HEVC  0

int main(int argc, char* argv[])
{
    AVCodecContext *pCodecCtx= NULL;
    int i, ret, got_output;
    FILE *fp_in;
	FILE *fp_out;
    AVFrame *pFrame;
    AVPacket pkt;
	int y_size;
	int framecnt=0;
 
 
	//char filename_in[]="ds_480x272.yuv";
	char filename_in[]="output.yuv";
 
 
#if TEST_HEVC
	AVCodecID codec_id=AV_CODEC_ID_HEVC;
	char filename_out[]="ds.hevc";
#else
	AVCodecID codec_id=AV_CODEC_ID_H264;
	char filename_out[]="ds.h264";
#endif
 
 
 
 
	int in_w=480,in_h=272;	
	int framenum=100;	
 
 
	avcodec_register_all();
 
 
    AVCodec * pCodec = avcodec_find_encoder(codec_id);
    if (!pCodec) {
        printf("Codec not found\n");
        return -1;
    }
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if (!pCodecCtx) {
        printf("Could not allocate video codec context\n");
        return -1;
    }
    pCodecCtx->bit_rate = 400000;
    pCodecCtx->width = in_w;
    pCodecCtx->height = in_h;
    pCodecCtx->time_base.num=1;
	pCodecCtx->time_base.den=25;
    pCodecCtx->gop_size = 10;
    pCodecCtx->max_b_frames = 1;
    pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
 
 
    if (codec_id == AV_CODEC_ID_H264)
        av_opt_set(pCodecCtx->priv_data, "preset", "slow", 0);
 
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        printf("Could not open codec\n");
        return -1;
    }
    
    pFrame = av_frame_alloc();
    if (!pFrame) {
        printf("Could not allocate video frame\n");
        return -1;
    }
    pFrame->format = pCodecCtx->pix_fmt;
    pFrame->width  = pCodecCtx->width;
    pFrame->height = pCodecCtx->height;
 
 
    ret = av_image_alloc(pFrame->data, pFrame->linesize, pCodecCtx->width, pCodecCtx->height,
                         pCodecCtx->pix_fmt, 16);
    if (ret < 0) {
        printf("Could not allocate raw picture buffer\n");
        return -1;
    }
	//Input raw data
 
 
	fp_in = fopen(filename_in, "rb");
	if (!fp_in) {
		printf("Could not open %s\n", filename_in);
		return -1;
	}
	//Output bitstream
	fp_out = fopen(filename_out, "wb");
	if (!fp_out) {
		printf("Could not open %s\n", filename_out);
		return -1;
	}
 
 
	y_size = pCodecCtx->width * pCodecCtx->height;
    //Encode
    for (i = 0; i < framenum; i++) {
        av_init_packet(&pkt);
        pkt.data = NULL;    // packet data will be allocated by the encoder
        pkt.size = 0;
		//Read raw YUV data
		if (fread(pFrame->data[0],1,y_size,fp_in)<= 0||		// Y
			fread(pFrame->data[1],1,y_size/4,fp_in)<= 0||	// U
			fread(pFrame->data[2],1,y_size/4,fp_in)<= 0){	// V
			return -1;
		}else if(feof(fp_in)){
			break;
		}
 
 
        pFrame->pts = i;
        /* encode the image */
        ret = avcodec_encode_video2(pCodecCtx, &pkt, pFrame, &got_output);
        if (ret < 0) {
            printf("Error encoding frame\n");
            return -1;
        }
        if (got_output) {
            printf("Succeed to encode frame: %5d\tsize:%5d\n",framecnt,pkt.size);
			framecnt++;
            fwrite(pkt.data, 1, pkt.size, fp_out);
            av_free_packet(&pkt);
        }
    }
    //Flush Encoder
    for (got_output = 1; got_output; i++) {
        ret = avcodec_encode_video2(pCodecCtx, &pkt, NULL, &got_output);
        if (ret < 0) {
            printf("Error encoding frame\n");
            return -1;
        }
        if (got_output) {
            printf("Flush Encoder: Succeed to encode 1 frame!\tsize:%5d\n",pkt.size);
            fwrite(pkt.data, 1, pkt.size, fp_out);
            av_free_packet(&pkt);
        }
    }
 
 
    fclose(fp_out);
    avcodec_close(pCodecCtx);
    av_free(pCodecCtx);
    av_freep(&pFrame->data[0]);
    av_frame_free(&pFrame);
 
 
	return 0;
}