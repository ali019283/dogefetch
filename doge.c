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

        // FIXME: Maybe put this into its own function?
        int i = 0;
        for (; str[i] != '\0'; i++);
        str[i-2] = 0;

        printf(ANSI_COLOR_YELLOW     " `_/      )      %s \n", &str[13]);

        return 0;
}

int get_mem_total(){
	char mem_total_buffer[BUFFER_SIZE];
	char mem_available_buffer[BUFFER_SIZE];
	FILE *fptr=fopen("/proc/meminfo", "r");
    // MemTotal:
	fgets(mem_total_buffer,BUFFER_SIZE,fptr);
    // MemFree:
	fgets(mem_available_buffer,BUFFER_SIZE,fptr);
    // MemAvailable:
	fgets(mem_available_buffer,BUFFER_SIZE,fptr);
    // MemTotal:
    strtok(mem_total_buffer, " ");
    long mem_total = atol(strtok(NULL, " ")) / 1000;
    strtok(mem_available_buffer, " ");
    long mem_used = (mem_total - (atol(strtok(NULL, " ")) / 1000));

	printf(ANSI_COLOR_GREEN    " (_(_/-(_/    ﳔ   %ld MB/%ld MB \n", 
            mem_used, mem_total);
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
