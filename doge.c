#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE        (60)
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

inline void terminator(char *str) {
    int i = 0;
    while(str[i++]);
    str[i-2] = 0;
}

int get_comp(){
        char *filename = "/sys/devices/virtual/dmi/id/product_version";

        /* Some machines may lack this file */
        if(access(filename, F_OK) == 0) {
                char str[BUFFER_SIZE];
                FILE *fptr = fopen(filename, "r");
                fgets(str, BUFFER_SIZE, fptr);
                printf(ANSI_COLOR_CYAN     "  __      _      %s", str);
                fclose(fptr);
        } else { // Very cheap workaround
                char str[BUFFER_SIZE];
                memcpy(str, "Unknown hardware", 17);
                printf(ANSI_COLOR_CYAN     "  __      _      %s\n", str);
        }

        return 0;
}

int get_cpu(){
	int num = 0;
	FILE *fptr=fopen("/proc/cpuinfo", "r");
	char str[BUFFER_SIZE];
	while( num < 5){
		num=num+1;
		fgets(str,BUFFER_SIZE,fptr);
	}
	fclose(fptr);
	printf(ANSI_COLOR_BLUE     "o'')}____//      %s", &str[13]);
	return 0;
}

int get_dist() {
	FILE *fptr = fopen("/etc/os-release", "r");

        // FIXME: Error handling
        if (!fptr) return -1;

        char str[BUFFER_SIZE];

        // Locating a line containing the PRETTY_NAME field
        while (strstr(str, "PRETTY_NAME") == NULL)
                fgets(str, BUFFER_SIZE, fptr);

        fclose(fptr);
        terminator(str);

        printf(ANSI_COLOR_YELLOW     " `_/      )      %s \n", &str[13]);

        return 0;
}

int get_mem_total(){
	char str[BUFFER_SIZE];
	int num = 0;
	FILE *fptr=fopen("/proc/meminfo", "r");
	fgets(str,BUFFER_SIZE,fptr);
	char str1[BUFFER_SIZE];
	fgets(str1,BUFFER_SIZE,fptr);
	fgets(str1,BUFFER_SIZE,fptr);
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
	printf(ANSI_COLOR_GREEN    " (_(_/-(_/    ﳔ   %ld MB/%ld MB \n", ret1, ret);
	return 0;
}


int main (int argc, char const *argv[]) {
	get_comp();
	get_cpu();
	get_dist();
	get_mem_total();
	printf(ANSI_COLOR_GREEN    "              very" ANSI_COLOR_MAGENTA " doge" ANSI_COLOR_CYAN " much" ANSI_COLOR_YELLOW " wow" ANSI_COLOR_RESET "\n");
	return 0;
}
