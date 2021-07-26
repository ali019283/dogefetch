#include <stdio.h>
#include <stdlib.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
int get_comp(){
	char str[60];
	FILE *fptr=fopen("/sys/devices/virtual/dmi/id/product_version", "r");
	fgets(str,60,fptr);
	printf(ANSI_COLOR_CYAN     "\n      %s \n", str);
	fclose(fptr);
	return 0;
}

int get_cpu(){
	int num = 0;
	FILE *fptr=fopen("/proc/cpuinfo", "r");
	char str[60];
	while( num < 5){
		num=num+1;
		fgets(str,60,fptr);
	}
	fclose(fptr);
	printf(ANSI_COLOR_BLUE     "      %s \n", &str[13]);
	return 0;
}

int get_dist(){
	char str[60];
	int num = 0;
	FILE *fptr=fopen("/etc/os-release", "r");
	while (num < 3){
		num=num+1;
		fgets(str, 60, fptr);
	}
	fclose(fptr);
	int i = 0;
	for (; str[i] != '\0'; i++);
	str[i-2] = 0;
	printf(ANSI_COLOR_YELLOW     "      %s \n \n", &str[13]);
	return 0;
	
}

int get_mem_total(){
	char str[60];
	int num = 0;
	FILE *fptr=fopen("/proc/meminfo", "r");
	fgets(str,60,fptr);
	char str1[60];
	fgets(str1,60,fptr);
	fgets(str1,60,fptr);
	int i = 0;
	for (; str[i] != '\0'; i++);
	str[i-7] = 0;
	int a = 0;
	for (; str1[a] != '\0'; a++);
	str1[a-7] = 0;
	char *ptr1;
	long ret1;
	ret1 = strtol(&str1[17], &ptr1, 10);
	char *ptr;
	long ret;
	ret = strtol(&str[17], &ptr, 10);
	ret1=ret-ret1;
	printf(ANSI_COLOR_GREEN    "   ﳔ   %ld MB/%ld MB \n \n", ret1, ret);
	return 0;
}


int main (int argc, char const *argv[]) {
	get_comp();
	get_cpu();
	get_dist();
//	get_mem();
	get_mem_total();
	return 0;
}
