
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<regex.h>
#include<sys/mman.h>

int main(void)
{
	char text[1024];
	//const char *rstr="<address>\\([^<]\\+\\?\\)</address>";
	const char *rstr="<a href=\\([^>]\\+\\?\\)>";
	const char *title="<div class=\"title\"\\([^<]\\+\\?\\)</div>";
	const char *src="<img src=\\([^>]\\+\\?\\)>";
	//创建正则类型
	regex_t link_Reg,title_Reg,src_Reg;
	//生成
	regcomp(&link_Reg,rstr,0);
	regcomp(&title_Reg,title,0);
	regcomp(&src_Reg,src,0);
	//位置数组
	regmatch_t ma[2];
	//通过mmap映射,将文件数据加载到进程内存
	int fd,size;
	fd=open("news.txt",O_RDWR);
	size=lseek(fd,0,SEEK_END);
	char* data=NULL;
	data=mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
	close(fd);

	while(1/*(regexec(&link_Reg,data,2,ma,0))==0*/){
		if((regexec(&link_Reg,data,2,ma,0))==0){
			bzero(text,1024);//初始化数组
			snprintf(text,ma[1].rm_eo-ma[1].rm_so+1,"%s",data+ma[1].rm_so);
			printf("提取成功：%s\n",text);
			//提取成功，首地址偏移，避免重复匹配
			data+=ma[0].rm_eo;
		}
		if((regexec(&title_Reg,data,2,ma,0))==0){

			bzero(text,1024);//初始化数组
			snprintf(text,ma[1].rm_eo-ma[1].rm_so+1,"%s",data+ma[1].rm_so);
			printf("提取成功：%s\n",text);
			//提取成功，首地址偏移，避免重复匹配
			data+=ma[0].rm_eo;
			}
		if((regexec(&src_Reg,data,2,ma,0))==0){
			bzero(text,1024);//初始化数组
			snprintf(text,ma[1].rm_eo-ma[1].rm_so+1,"%s",data+ma[1].rm_so);
			printf("提取成功：%s\n",text);
			//提取成功，首地址偏移，避免重复匹配
			data+=ma[0].rm_eo;
		}
		continue;
	}
	regfree(&link_Reg);
	regfree(&title_Reg);
	regfree(&src_Reg);
	return 0;
}

