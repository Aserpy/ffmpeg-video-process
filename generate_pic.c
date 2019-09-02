/**************************************************
Copyright:
Author:cxw
Date:2019.08.
Filename:generate_pic.c
Description:generate pic,such gray.
**************************************************/


/*header */
#include <stdio.h>


/************************************************* 
Function:       gen_yuv420p_graybar 
Description:    generate pic 
Calls:          None 
Table Accessed: None 
Table Updated:  None
Input:          width Width of Output YUV file
				height Height of Output YUV file
				barnum Number of bars
				ymin Min value of Y
				ymax Max value of Y  
Output:         yuv file 
Return:         0
Others:         None
*************************************************/  
int gen_yuv420p_graybar(int width, int height,int barnum,unsigned char ymin,unsigned char ymax){
 
	int barwidth;
	float lum_inc;
	unsigned char lum_temp;
	int uv_width,uv_height;
	FILE *fp=NULL;
	unsigned char *data_y=NULL;
	unsigned char *data_u=NULL;
	unsigned char *data_v=NULL;
	int t=0,i=0,j=0;
	char filename[100]={0};
 
	//Check
	if(width<=0||height<=0||barnum<=0){
		printf("Error: Width, Height or Bar Number cannot be 0 or negative number!\n");
		printf("Default Param is used.\n");
		width=640;
		height=480;
		barnum=10;
	}
	if(width%barnum!=0){
		printf("Warning: Width cannot be divided by Bar Number without remainder!\n");
	}
	barwidth=width/barnum;
	lum_inc=((float)(ymax-ymin))/((float)(barnum-1));
	uv_width=width/2;
	uv_height=height/2;
 
	data_y=(unsigned char *)malloc(width*height);
	data_u=(unsigned char *)malloc(uv_width*uv_height);
	data_v=(unsigned char *)malloc(uv_width*uv_height);
 
	sprintf(filename,"graybar_%dx%d_yuv420p.yuv",width,height);
	if((fp=fopen(filename,"wb+"))==NULL){
		printf("Error: Cannot create file!");
		return -1;
	}
 
	//Output Info
	printf("Y, U, V value from picture's left to right:\n");
	for(t=0;t<(width/barwidth);t++){
		lum_temp=ymin+(char)(t*lum_inc);
		printf("%3d, 128, 128\n",lum_temp);
	}
	//Gen Data
	//设置相应的Y值
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			t=i/barwidth;
			lum_temp=ymin+(char)(t*lum_inc);
			data_y[j*width+i]=lum_temp;
		}
	}
	//设置相应的U值
	for(j=0;j<uv_height;j++){
		for(i=0;i<uv_width;i++){
			//data_u[j*uv_width+i]=128+128%(i+1);
			data_u[j*uv_width + i] = 128;
		}
	}
	//设置相应的V值
	for(j=0;j<uv_height;j++){
		for(i=0;i<uv_width;i++){
			//data_v[j*uv_width+i]=128+128/(i+1);
			data_v[j*uv_width + i] = 128;
		}
	}
	//写入相应的图片数据
	fwrite(data_y,width*height,1,fp);
	fwrite(data_u,uv_width*uv_height,1,fp);
	fwrite(data_v,uv_width*uv_height,1,fp);
	fclose(fp);
	free(data_y);
	free(data_u);
	free(data_v);
	printf("Finish generate %s!\n",filename);
    return 0;
}




/************************************************* 
Function:       // 函数名称 
Description:    // 函数功能、性能等的描述 
Calls:          // 被本函数调用的函数清单 
Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序） 
Table Updated: // 被修改的表（此项仅对于牵扯到数据库操作的程序） 
Input:          // 输入参数说明，包括每个参数的作 
                  // 用、取值说明及参数间关系。 
Output:         // 对输出参数的说明。 
Return:         // 函数返回值的说明 
Others:         // 其它说明 
*************************************************/  







int main()
{
	printf("hello,ffmpeg!\n");
	//All picture's resolution is 1280x720
	//Gray Bar, from 16 to 235
	gen_yuv420p_graybar(1280,720,10,16,235);

	return 0;
}