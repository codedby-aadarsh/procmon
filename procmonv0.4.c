#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

/*  what this code does:
1. printf("%-8s %-20s %-6s %8s\n", "PID", "Name", "State", "Mem(kB)") */

int main(void)
{
    printf("%-8s %-39s %-6s %8s\n", "PID", "Name", "State", "Mem(kB)");
    while (1)
    {   system("clear");
        fflush(stdout);
        DIR *d = opendir("/proc");
    	if (!d) return -1;
    	struct dirent *entry;
        while ((entry = readdir(d)) != NULL)
        {
            if (atoi(entry->d_name) == 0)
                continue;
            char path[50], buffer[256];
            if (snprintf(path, sizeof(path), "/proc/%d/status", atoi(entry->d_name)) < 0)
                break;

            FILE *fp = fopen(path, "r");
            if (!fp)
            {   if(errno==ENOENT) continue;
                else perror(path); 
                break;
            }
            int pid;
            char name[100];
            char state;
            int mem;
            while (fgets(buffer, sizeof(buffer), fp) > 0)
            {
                if (strncmp(buffer, "Pid", 3) == 0)
                    sscanf(buffer, "Pid:\t%d", &pid);
                else if (strncmp(buffer, "Name", 4) == 0)
                    sscanf(buffer, "Name:\t%s", name);
                else if (strncmp(buffer, "State", 5) == 0)
                    sscanf(buffer, "State:\t%c", &state);
                else if (strncmp(buffer, "VmRSS", 5) == 0)
                    sscanf(buffer, "VmRss:\t%d", &mem);
            }
            fclose(fp);
            printf("%-8d %-39s %-6c %8d\n", pid, name, state, mem);
        }
	closedir(d);
        sleep(2);
    }
    return 0;
}
