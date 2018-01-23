#define _GNU_SOURCE			//Access to nonStandard GNU/Linux functions (Needed for syscall)
#include <unistd.h> 			//Access to POSIX (Needed for syscall)
#include <sys/syscall.h>
#include <stdio.h>
#include <time.h> 			//EPOCH TO Date Conversion

int main()
{
    long time;
    time = syscall(201);		//getting time in seconds
    
    printf("%s", ctime(&time));		//convert time in seconds to "DayOfWeek month day hh:mm:ss year"
    
    return 0;
}

