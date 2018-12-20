#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char* argv[]){



	
	int scheduler = sched_getscheduler(getpid());
	int pid = getpid();
	struct sched_param p;
	int res =sched_getparam(0, &p);

	int pmax = sched_get_priority_max(scheduler);
	int pmin = sched_get_priority_min(scheduler);
	// printf("SCHED_OTHER: %d\n",SCHED_OTHER); // 0
	// printf("SCHED_FIFO: %d\n",SCHED_FIFO);   // 1
    // printf("SCHED_RR: %d\n",SCHED_RR);       // 2
  	
    switch(scheduler){
    	case 0:
    		printf("política actual de planificación del pid %d: SCHED_OTHER\n", pid);
    		break;
    	case 1:
    		printf("política actual de planificación del pid %d: SCHED_FIFO\n", pid);
    		break;
    	case 2:
    		printf("política actual de planificación del pid %d: SCHED_RR\n", pid);
    		break;
    	default:
    		break;
    }

    printf("El valor mínimo de esta política de planificación es %d y el máximo %d\n", pmin, pmax);
    printf("Este proceso tiene prioridad %d\n",p.sched_priority);
 
	
	return 0;

}