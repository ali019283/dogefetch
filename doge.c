//       _                   __      _       _
//    __| | ___   __ _  ___ / _| ___| |_ ___| |__
//   / _` |/ _ \ / _` |/ _ \ |_ / _ \ __/ __| '_ \
//  | (_| | (_) | (_| |  __/  _|  __/ || (__| | | |
//   \__,_|\___/ \__, |\___|_|  \___|\__\___|_| |_|
//               |___/
//  __      _
// o'')}____//
//  `_/      )
//  (_(_/-(_/
//  This   Project
//  is     made by
//  Ali Burak Çetin
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE        (60)
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#ifndef INSTALL_PREFIX
#define INSTALL_PREFIX "/usr/local"
#endif
bool check_path(const char *cmd) {
    if(strchr(cmd, '/')) {
        return access(cmd, X_OK)==0;
    }
    const char *path = getenv("PATH");
    if(!path) return 1;
    char *buf = malloc(strlen(path)+strlen(cmd)+3);
    if(!buf) return 1;
    for(; *path; ++path) {
        char *p = buf;
        for(; *path && *path!=':'; ++path,++p) {
            *p = *path;
        }
        if(p==buf) *p++='.';
        if(p[-1]!='/') *p++='/';
        strcpy(p, cmd);
        if(access(buf, X_OK)==0) {
            free(buf);
            return 0;
        }
        if(!*path) break;
    }
    free(buf);
    return 1;
}

int get_comp(){
        char *filename = "/sys/devices/virtual/dmi/id/product_version";

        /* Some machines may lack this file */
        if(access(filename, F_OK) == 0) {
                char str[BUFFER_SIZE];
                FILE *fptr = fopen(filename, "r");
                fgets(str, BUFFER_SIZE, fptr);
                printf(ANSI_COLOR_RED "├"ANSI_COLOR_CYAN     "   ➜ %s", str);
                fclose(fptr);
        } else { // Very cheap workaround
                char str[BUFFER_SIZE];
                memcpy(str, "Unknown hardware", 17);
                printf(ANSI_COLOR_GREEN     "├   ➜ %s\n", str);
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
        printf(ANSI_COLOR_RED "├"ANSI_COLOR_BLUE      "   ➜ %s", &str[13]);
        return 0;
}

int get_dist() {
        FILE *fptr = fopen("/etc/os-release", "r");

        // FIXME: Error handling
        if (!fptr) return -1;

        char str[BUFFER_SIZE];
        char* distro;

        // Locating a line containing the PRETTY_NAME field
        while (strstr(str, "PRETTY_NAME") == NULL)
                fgets(str, BUFFER_SIZE, fptr);
        fclose(fptr);
        strtok(str, "=\"");
        distro = strtok(NULL, "=\"");
        printf(ANSI_COLOR_RED "├" ANSI_COLOR_YELLOW     "   ➜ %s \n", distro);
        return 0;
}

int get_mem_total(){
        char mem_total_buffer[BUFFER_SIZE];
        char mem_available_buffer[BUFFER_SIZE];
        FILE *fptr=fopen("/proc/meminfo", "r");

        while(strstr(mem_total_buffer, "MemTotal:") == NULL)
                fgets(mem_total_buffer, BUFFER_SIZE, fptr);
        while(strstr(mem_available_buffer, "MemAvailable:") == NULL)
                fgets(mem_available_buffer, BUFFER_SIZE, fptr);
        fclose(fptr);

        strtok(mem_total_buffer, " ");
        long mem_total = atol(strtok(NULL, " ")) / 1000;
        strtok(mem_available_buffer, " ");
        long mem_used = (mem_total - (atol(strtok(NULL, " ")) / 1000));

        printf(ANSI_COLOR_RED"├"ANSI_COLOR_GREEN    " ﳔ  ➜ %ld MB/%ld MB \n",  mem_used, mem_total);
        return 0;
}

int pack(){
        char *dists[] = {"dpkg", " -L", "pacman", " -Q"};
        int package_count = 0;
        char *str = NULL;
        size_t len = 0;
        for(int i = 0; i < (sizeof(dists) / sizeof(dists[0]))-1; i+=2){
                if(check_path(dists[i])){continue;}
                size_t newlen = strlen(dists[i]) + strlen(dists[i+1]);
                if (!str || newlen > len) {
                        str = realloc(str, newlen + 1);
                        len = newlen;
                }
                memset(str, '\0', len + 1);
                strcat(str, dists[i]);
                strcat(str, dists[i+1]);
                FILE * in = popen(str, "r");
                int c;
                while ((c = fgetc(in)) != EOF) {
                        if (c == '\n') package_count++;
                }
                printf(ANSI_COLOR_RED"└   ➜ %d\n" ANSI_COLOR_RESET, package_count);
                return 0;
        }
        printf(ANSI_COLOR_RED"└   ➜ Unknown Distro\n" ANSI_COLOR_RESET);
        return 1;
}

int host_name(){
        char hostname[60], *name;
        gethostname(hostname, 60);
        name=getlogin();
        printf(ANSI_COLOR_RED"\x1b[1mPC ➜ %s@%s\n", name, hostname);
        
}

int main (int argc, char const *argv[]) {
	FILE *fptr;
	char c, str[BUFFER_SIZE];
	fptr = fopen(INSTALL_PREFIX"/share/dogefetch/doggo", "r");
	c = fgetc(fptr);
	for (int i = 0; i < argc ; i++){
		if (strcmp(argv[i], "--doggo-color=yellow") == 0){
			while (c != EOF){
				printf (ANSI_COLOR_YELLOW "%c",c);
				c = fgetc(fptr);
			}
		}else if (strcmp(argv[i], "--doggo-color=green") == 0){
			while (c != EOF){
				printf (ANSI_COLOR_GREEN "%c",c);
				c = fgetc(fptr);
			}
		
		}else if (strcmp(argv[i], "--doggo-color=red") == 0){
			while (c != EOF){
				printf (ANSI_COLOR_RED "%c",c);
				c = fgetc(fptr);
			}

		}
		else if (argc < 2){
			fgets(str, BUFFER_SIZE, fptr);
			printf(ANSI_COLOR_CYAN " %s", str);
			fgets(str, BUFFER_SIZE, fptr);
			printf(ANSI_COLOR_BLUE "%s", str);
			fgets(str, BUFFER_SIZE, fptr);
			printf(ANSI_COLOR_YELLOW "%s", str);
			fgets(str, BUFFER_SIZE, fptr);
			printf(ANSI_COLOR_GREEN "%s", str);
		}
	}

	fclose(fptr);
	printf("\033[4A");
	printf("\033[9999999D");
        printf("\033[13C");
        host_name();
	printf("\033[13C");
	get_comp();
        printf("\033[13C");
        get_cpu();
        printf("\033[13C");
        get_dist();
        printf("\033[13C");
        get_mem_total();
        printf("\033[13C");
        pack();

    return 0;
}
