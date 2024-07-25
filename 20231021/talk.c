
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
	const char *rstr1="<h5 class=\"user-bar-uname\">\\([^<]\\+\\?\\)</h5>";
	const char *rstr2="<span class=\"type-text\">\\([^<]\\+\\?\\)</span>";
	const char *rstr3="<span class=\"time\">\\([^>]\\+\\?\\)</span>";
	const char *rstr4= "<div class=\"area\">\\([^>]\\+\\?\\)</div>";
	//创建正则类型
	regex_t rstr1_Reg,rstr2_Reg,rstr3_Reg,rstr4_Reg;
	//生成
	regcomp(&rstr1_Reg,rstr1,0);
	regcomp(&rstr2_Reg,rstr2,0);
	regcomp(&rstr3_Reg,rstr3,0);
	regcomp(&rstr4_Reg,rstr4,0);
	//位置数组
	regmatch_t ma[2];
	//通过mmap映射,将文件数据加载到进程内存
	int fd,size;
	fd=open("talk.txt",O_RDWR);
	size=lseek(fd,0,SEEK_END);
	char* data=NULL;
	data=mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
	close(fd);

	while(1/*(regexec(&link_Reg,data,2,ma,0))==0*/){
		if((regexec(&rstr1_Reg,data,2,ma,0))==0){
			bzero(text,1024);//初始化数组
			snprintf(text,ma[1].rm_eo-ma[1].rm_so+1,"%s",data+ma[1].rm_so);
			printf("提取成功：%s\n",text);
			//提取成功，首地址偏移，避免重复匹配
			data+=ma[0].rm_eo;
		}
		if((regexec(&rstr2_Reg,data,2,ma,0))==0){

			bzero(text,1024);//初始化数组
			snprintf(text,ma[1].rm_eo-ma[1].rm_so+1,"%s",data+ma[1].rm_so);
			printf("提取成功：%s\n",text);
			//提取成功，首地址偏移，避免重复匹配
			data+=ma[0].rm_eo;
			}
		if((regexec(&rstr3_Reg,data,2,ma,0))==0){
			bzero(text,1024);//初始化数组
			snprintf(text,ma[1].rm_eo-ma[1].rm_so+1,"%s",data+ma[1].rm_so);
			printf("提取成功：%s\n",text);
			//提取成功，首地址偏移，避免重复匹配
			data+=ma[0].rm_eo;
			}
		if((regexec(&rstr4_Reg,data,2,ma,0))==0){
			bzero(text,1024);//初始化数组
			snprintf(text,ma[1].rm_eo-ma[1].rm_so+1,"%s",data+ma[1].rm_so);
			printf("提取成功：%s\n",text);
			//提取成功，首地址偏移，避免重复匹配
			data+=ma[0].rm_eo;
			}
	}
	regfree(&rstr1);
	regfree(&rstr2);
	redfree(&rstr3);
	regfree(&rstr4);
	return 0;

}
