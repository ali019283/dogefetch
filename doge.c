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

int get_comp(){
        char *filename = "/sys/devices/virtual/dmi/id/product_version";

        /* Some machines may lack this file */
        if(access(filename, F_OK) == 0) {
                char str[BUFFER_SIZE];
                FILE *fptr = fopen(filename, "r");
                fgets(str, BUFFER_SIZE, fptr);
                printf(ANSI_COLOR_CYAN     "   %s", str);
                fclose(fptr);
        } else { // Very cheap workaround
                char str[BUFFER_SIZE];
                memcpy(str, "Unknown hardware", 17);
                printf(ANSI_COLOR_CYAN     "   %s\n", str);
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
        printf(ANSI_COLOR_BLUE      "   %s", &str[13]);
        return 0;
}

int get_pkg_count() {
        /*
                Identify the package manager

        */
        // Copied from get_dist()

        FILE *fptr = fopen("/etc/os-release", "r");

        // FIXME: Error handling
        if (!fptr) return -1;

        char str[BUFFER_SIZE];
        char* distro;
        char* pkgcount_command;
        // FILE *pkgcount_command_fptr;
        // Locating a line containing the PRETTY_NAME field
        while (strstr(str, "PRETTY_NAME") == NULL)
                fgets(str, BUFFER_SIZE, fptr);
        fclose(fptr);

        strtok(str, "=\"");
        distro = strtok(NULL, "=\"");

        if(strstr(distro, "Raspbian") || strstr(distro, "Debian")  || strstr(distro, "Ubuntu")  || strstr(distro, "ubuntu") || strstr(distro, "MX") ) {  // Debian base support (which uses apt)
                // I additionally added "ubuntu" to identify Xubuntu Lubuntu etc.
                pkgcount_command = "echo \"$(dpkg-query -f '.\n' -W | wc -l) packages\"";
        }

        if(strstr(distro, "Arch") || strstr(distro, "Artix") || strstr(distro, "Manjaro") || strstr(distro, "Endeavour") || strstr(distro, "Garuda") ) {
                pkgcount_command = "echo \"$(pacman -Qq --color never | wc -l) packages\"", "r";
        }


        char line[128];

        FILE *pkgcount_command_fptr = popen(pkgcount_command, "r");
        if (pkgcount_command_fptr) {
           while (fgets(line, sizeof line, pkgcount_command_fptr)) {
                fscanf(pkgcount_command_fptr,"", line);
                printf(ANSI_COLOR_YELLOW     "\uf8d5  \uf178 %s  \n", line);
           }
           pclose(pkgcount_command_fptr);
        }

        // printf(ANSI_COLOR_YELLOW     "\uf8d5  \uf178 %s \n", pkgcount_command);
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
        printf(ANSI_COLOR_YELLOW     "   %s \n", distro);
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

        printf(ANSI_COLOR_GREEN    "ﳔ   %ld MB/%ld MB \n", 
                mem_used, mem_total);
        return 0;
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
	printf("[4A");
	printf("[9999999D");
	printf("[13C");
	get_comp();
    printf("\t\t");
    get_cpu();
    printf("\t\t");
    get_dist();
    printf("\t\t");
    get_mem_total();
    printf("\t\t");
    get_pkg_count();


    return 0;
}
