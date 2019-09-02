#ubuntu ffmpeg complie, install and test 


linux ffmpeg的编译和使用

1.FFmpeg编译
1.1.安装yasm
这里我是直接通过ubuntu包安装的，当然也可以通过编译源码来安装。

sudo apt-get install yasm
1.2.下载FFmpeg
git clone https://git.ffmpeg.org/ffmpeg.git
1.3.配置、编译FFMPEG
./configure --prefix=host --enable-shared --disable-static --disable-doc 
关于FFMPEG的配置参数，我们可以通过下面命令来查看

./configure --help
然后执行

make
make install
就可以在host目录下找到我们需要的动态库和头文件了

复制代码
.
├── bin
│   ├── ffmpeg
│   ├── ffprobe
│   └── ffserver
├── include
│   ├── libavcodec
│   ├── libavdevice
│   ├── libavfilter
│   ├── libavformat
│   ├── libavutil
│   ├── libswresample
│   └── libswscale
├── lib
│   ├── libavcodec.so -> libavcodec.so.57.64.101
│   ├── libavcodec.so.57 -> libavcodec.so.57.64.101
│   ├── libavcodec.so.57.64.101
│   ├── libavdevice.so -> libavdevice.so.57.1.100
│   ├── libavdevice.so.57 -> libavdevice.so.57.1.100
│   ├── libavdevice.so.57.1.100
│   ├── libavfilter.so -> libavfilter.so.6.65.100
│   ├── libavfilter.so.6 -> libavfilter.so.6.65.100
│   ├── libavfilter.so.6.65.100
│   ├── libavformat.so -> libavformat.so.57.56.101
│   ├── libavformat.so.57 -> libavformat.so.57.56.101
│   ├── libavformat.so.57.56.101
│   ├── libavutil.so -> libavutil.so.55.34.101
│   ├── libavutil.so.55 -> libavutil.so.55.34.101
│   ├── libavutil.so.55.34.101
│   ├── libswresample.so -> libswresample.so.2.3.100
│   ├── libswresample.so.2 -> libswresample.so.2.3.100
│   ├── libswresample.so.2.3.100
│   ├── libswscale.so -> libswscale.so.4.2.100
│   ├── libswscale.so.4 -> libswscale.so.4.2.100
│   ├── libswscale.so.4.2.100
│   └── pkgconfig
└── share
    └── ffmpeg
复制代码
2.使用FFMPEG
上面我们编译完了FFMPEG之后可以去运行以下bin目录下生成的可执行文件

~/tmp/ffmpeg/ffmpeg/host/bin$ ./ffmpeg 
./ffmpeg: error while loading shared libraries: libavdevice.so.57: cannot open shared object file: No such file or directory
发现系统提示找不到动态库，可以用

ldd ffmpeg
来查看运行当前可执行文件需要哪些动态库

复制代码
~/tmp/ffmpeg/ffmpeg/host/bin$ ldd ffmpeg 
    linux-vdso.so.1 =>  (0x00007fffcfeaf000)
    libavdevice.so.57 => not found
    libavfilter.so.6 => not found
    libavformat.so.57 => not found
    libavcodec.so.57 => not found
    libswresample.so.2 => not found
    libswscale.so.4 => not found
    libavutil.so.55 => not found
    libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f41d6d9e000)
    libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f41d6b7f000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f41d67b9000)
    /lib64/ld-linux-x86-64.so.2 (0x00007f41d70c7000)
复制代码
应该有很多人和我一样，不想编译FFMPEG之后还要动自己系统的环境，这时有一个简单的方法可以解决这个问题。就是在当前终端export一个环境变量。

~/tmp/ffmpeg/ffmpeg/host$ export LD_LIBRARY_PATH=lib/
 

复制代码
~/tmp/ffmpeg/ffmpeg/host/bin$ export LD_LIBRARY_PATH=../lib/
~/tmp/ffmpeg/ffmpeg/host/bin$ ldd ffmpeg 
    linux-vdso.so.1 =>  (0x00007fff25150000)
    libavdevice.so.57 => ../lib/libavdevice.so.57 (0x00007f7348cc8000)
    libavfilter.so.6 => ../lib/libavfilter.so.6 (0x00007f73488e8000)
    libavformat.so.57 => ../lib/libavformat.so.57 (0x00007f73484cc000)
    libavcodec.so.57 => ../lib/libavcodec.so.57 (0x00007f7347034000)
    libswresample.so.2 => ../lib/libswresample.so.2 (0x00007f7346e17000)
    libswscale.so.4 => ../lib/libswscale.so.4 (0x00007f7346b8f000)
    libavutil.so.55 => ../lib/libavutil.so.55 (0x00007f7346917000)
    libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f73465f1000)
    libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f73463d3000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f734600d000)
    libxcb.so.1 => /usr/lib/x86_64-linux-gnu/libxcb.so.1 (0x00007f7345dee000)
    libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f7345be9000)
    /lib64/ld-linux-x86-64.so.2 (0x00007f7348edb000)
    libXau.so.6 => /usr/lib/x86_64-linux-gnu/libXau.so.6 (0x00007f73459e5000)
    libXdmcp.so.6 => /usr/lib/x86_64-linux-gnu/libXdmcp.so.6 (0x00007f73457de000)
复制代码
然后再去运行上面的可执行文件就可以了

复制代码
~/tmp/ffmpeg/ffmpeg/host/bin$ ./ffmpeg 
ffmpeg version n3.2.2-8-g64bb329 Copyright (c) 2000-2016 the FFmpeg developers
  built with gcc 4.8 (Ubuntu 4.8.2-19ubuntu1)
  configuration: --prefix=host --enable-shared --disable-static --disable-doc
  libavutil      55. 34.101 / 55. 34.101
  libavcodec     57. 64.101 / 57. 64.101
  libavformat    57. 56.101 / 57. 56.101
  libavdevice    57.  1.100 / 57.  1.100
  libavfilter     6. 65.100 /  6. 65.100
  libswscale      4.  2.100 /  4.  2.100
  libswresample   2.  3.100 /  2.  3.100
Hyper fast Audio and Video encoder
usage: ffmpeg [options] [[infile options] -i infile]... {[outfile options] outfile}...
Use -h to get full help or, even better, run 'man ffmpeg'
复制代码
3.测试程序
程序可以打印出FFmpeg类库的基本信息，使用该程序通常可以验证FFmpeg是否正确的安装配置

复制代码
#include <stdio.h>  
  
#define __STDC_CONSTANT_MACROS  
  
#ifdef __cplusplus  
extern "C"  
{  
#endif  
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavfilter/avfilter.h"
#ifdef __cplusplus  
};  
#endif  
  
  
/** 
 * AVFormat Support Information 
 */  
char * avformatinfo(){  
  
    char *info=(char *)malloc(40000);  
    memset(info,0,40000);  
  
    av_register_all();  
  
    AVInputFormat *if_temp = av_iformat_next(NULL);  
    AVOutputFormat *of_temp = av_oformat_next(NULL);  
    //Input  
    while(if_temp!=NULL){  
        sprintf(info, "%s[In ] %10s\n", info, if_temp->name);  
        if_temp=if_temp->next;  
    }  
    //Output  
    while (of_temp != NULL){  
        sprintf(info, "%s[Out] %10s\n", info, of_temp->name);  
        of_temp = of_temp->next;  
    }  
    return info;  
}  
  
/** 
 * AVCodec Support Information 
 */  
char * avcodecinfo()  
{  
    char *info=(char *)malloc(40000);  
    memset(info,0,40000);  
  
    av_register_all();  
  
    AVCodec *c_temp = av_codec_next(NULL);  
  
    while(c_temp!=NULL){  
        if (c_temp->decode!=NULL){  
            sprintf(info, "%s[Dec]", info);  
        }  
        else{  
            sprintf(info, "%s[Enc]", info);  
        }  
        switch (c_temp->type){  
        case AVMEDIA_TYPE_VIDEO:  
            sprintf(info, "%s[Video]", info);  
            break;  
        case AVMEDIA_TYPE_AUDIO:  
            sprintf(info, "%s[Audio]", info);  
            break;  
        default:  
            sprintf(info, "%s[Other]", info);  
            break;  
        }  
  
        sprintf(info, "%s %10s\n", info, c_temp->name);  
  
        c_temp=c_temp->next;  
    }  
    return info;  
}  
  
/** 
 * AVFilter Support Information 
 */  
char * avfilterinfo()  
{  
    char *info=(char *)malloc(40000);  
    memset(info,0,40000);  
  
    avfilter_register_all();  
  
    AVFilter *f_temp = (AVFilter *)avfilter_next(NULL);  
      
    while (f_temp != NULL){  
        sprintf(info, "%s[%15s]\n", info, f_temp->name);  
        f_temp=f_temp->next;  
    }  
    return info;  
}  
  
/** 
 * Configuration Information 
 */  
char * configurationinfo()  
{  
    char *info=(char *)malloc(40000);  
    memset(info,0,40000);  
  
    av_register_all();  
  
    sprintf(info, "%s\n", avcodec_configuration());  
  
    return info;  
}  
  
int main(int argc, char* argv[])  
{  
    char *infostr=NULL;  
    infostr=configurationinfo();  
    printf("\n<<Configuration>>\n%s",infostr);  
    free(infostr);  
  
    infostr=avformatinfo();  
    printf("\n<<AVFormat>>\n%s",infostr);  
    free(infostr);  
  
    infostr=avcodecinfo();  
    printf("\n<<AVCodec>>\n%s",infostr);  
    free(infostr);  
  
    infostr=avfilterinfo();  
    printf("\n<<AVFilter>>\n%s",infostr);  
    free(infostr);  
  
    return 0;  
}  
复制代码
编译方法

~/tmp/ffmpeg/ffmpeg/host/test$ g++ -I ../include/ hello_world.cpp -o hello_world -L../lib/ -lavcodec -lavdevice -lavfilter -lavformat -lavutil
-I 指定头文件的搜索路径， -L指定动态库的搜索路径 -l指定要链接的动态库

 

2017/4/22：

这样编译出来的bin文件里面没有ffplay如果要生成ffplay需要下面两个步骤

1.编译SDL2
安装 libasound2-dev

sudo apt-get install libasound2-dev
否则可能会报下面的错误，不能播放声音

SDL_OpenAudio (2 channels, 32000 Hz): No such audio device
SDL_OpenAudio (1 channels, 32000 Hz): No such audio device
No more combinations to try, audio open failed
下载SDL2

http://www.libsdl.org/release/SDL2-2.0.5.zip

编译SDL2

unzip SDL2-2.0.5.zip
cd SDL2-2.0.5/
./configure --prefix=/usr/local/
make
sudo make install
2.重新配置编译FFMPEG
在执行./configure是添加 --enable-ffplay

./configure --prefix=host --enable-shared --disable-static --disable-doc --enable-ffplay
make
make install
这样就会在host/bin目录下生成ffplay了

 



ffplay 播放yuv视频

ffplay -pixel_format yuva444p10le -video_size 1920x1080 test.yuv
 2018/10/22:

编译debug版ffmpeg

./configure --enable-debug --enable-gpl --disable-optimizations --enable-shared --enable-static --enable-ffplay --disable-x86asm --prefix=host
调试ffmpeg时，因为make install拷贝到prefix目录的动态库是不带调试信息的，可以在/etc/ld.so.conf.d目录下添加ffmpeg.conf文件然后运行sudo ldconfig


/home/xxx/source/ffmpeg/libavcodec
/home/xxx/source/ffmpeg/libavdevice
/home/xxx/source/ffmpeg/libavfilter
/home/xxx/source/ffmpeg/libavformat
/home/xxx/source/ffmpeg/libavresample
/home/xxx/source/ffmpeg/libavutil
/home/xxx/source/ffmpeg/libpostproc
/home/xxx/source/ffmpeg/libswresample
/home/xxx/source/ffmpeg/libswscale
