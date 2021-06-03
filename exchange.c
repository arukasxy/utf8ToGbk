#include <windows.h>
#include <stdio.h>
#include <wchar.h> 
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

void utf8ToGbk(char *utf8String, char *gbkString)
{
wchar_t *unicodeStr = NULL;
int nRetLen = 0;
nRetLen = MultiByteToWideChar(CP_UTF8, 0, utf8String, -1, NULL, 0);
//求需求的宽字符数大小
unicodeStr = (wchar_t *)malloc(nRetLen * sizeof(wchar_t));
nRetLen = MultiByteToWideChar(CP_UTF8, 0, utf8String, -1, unicodeStr, nRetLen);
//将utf-8编码转换成unicode编码
nRetLen = WideCharToMultiByte(CP_ACP, 0, unicodeStr, -1, NULL, 0, NULL, 0);
//求转换所需字节数
nRetLen = WideCharToMultiByte(CP_ACP, 0, unicodeStr, -1, gbkString, nRetLen, NULL, 0);
//unicode编码转换成gbk编码
free(unicodeStr);
}


int main(int argc,char *argv[])
{
 char buf[MAX_LINE];  /*缓冲区*/
 FILE *fp;            /*输入文件指针*/
 FILE *fpout;         /*输出文件指针*/
 int len;             /*行字符个数*/
 char gbk[MAX_LINE];  /*输出缓存区*/
 
 if((fp = fopen(argv[1],"r")) == NULL)
 {
 perror("fail to read");
 
 /*void perror(const char *str) 把一个描述性错误消息输出到标准错误 stderr。首先输出字符串 str*/
 
 exit (1) ;
 }
 
 fpout=fopen("./out.txt","w");
 if(NULL==fpout)
 {
	 perror("fail to create");
	 exit(1);
 }
 setbuf(fpout,NULL);
 
 while(fgets(buf,MAX_LINE,fp) != NULL)
 {
/*  len = strlen(buf);
 buf[len-1] = '\0';  
 printf("%s %d \n",buf,len - 1); */
	utf8ToGbk(buf,gbk);
	fprintf(fpout,"%s",gbk);
	fflush(fpout);
 }
 
  fclose(fp);
  fclose(fpout);
  return 0;
}
