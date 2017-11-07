#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //For sleep function.

//Compute CPU usage in the past second.
int
main()
{
  unsigned long user, nice, system, idle, iowait, irq, softirq, steal;
  unsigned long total_time1, total_time2;
  unsigned long cpu_time1, cpu_time2;
  
  //First reading of /proc/stat file.
  FILE *stat_f1 = fopen ("/proc/stat", "r");
  if (stat_f1)
  {
    fscanf(stat_f1, "cpu %lu %lu %lu %lu %lu %lu %lu %lu", 
        &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
    total_time1 = user + nice + system + idle + iowait + irq + softirq + steal;
    cpu_time1 = user + nice + system;

    fclose(stat_f1);
  }

  //Sleep for 1 second.
  sleep(1);

  //Second reading of /proc/stat file.
  FILE *stat_f2 = fopen ("/proc/stat", "r");
  if (stat_f2)
  {
    fscanf(stat_f2, "cpu %lu %lu %lu %lu %lu %lu %lu %lu", 
        &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
    total_time2 = user + nice + system + idle + iowait + irq + softirq + steal;
    cpu_time2 = user + nice + system;

    fclose(stat_f2);
  }
  
  //CPU usage = CPU processing clocks / Total clocks
  printf ("CPU usage: %.2f%%\n", 100.0 * (cpu_time2 - cpu_time1) / (total_time2 - total_time1));
}
