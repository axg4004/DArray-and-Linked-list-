/*************************************************************************
* Timers.h - Instrumentation Macros Module  - Student file
*
* The timing instrumentation macros can be globally enabled by setting 
* the variable EN_TIME (ENable TIMErs) in the compiler command line, e.g., 
* use "gcc -DEN_TIME...." to enable the timers when needed.
* A compiler warning will be issued when the timers are enabled.  
* Note: All timing output should be directed to stderr.
*
*  10/08/2016   R. Repka    Fixed C++ struct warnings 
*  12/03/2016   R. Repka    Added semicolon to DECLARE_TIMER
*  09/10/2019   R. Repka    Always use time.h
*************************************************************************/
#ifndef _TIMERS_H_
#define _TIMERS_H_

#if defined(EN_TIME)
  #include <stdio.h>
  #include <time.h>
  #if defined(WARNING_MSG)
    #warning Timers enabled! Execution could be adversly effected.
  #endif 
#endif 

    struct timmerDetails {                                                    
      clock_t Start;    /* Start Time   - set when the timer is started */
      clock_t Stop;     /* Stop Time    - set when the timer is stopped */
      clock_t Elapsed;  /* Elapsed Time - Accumulated when the timer is stopped */
      int State;        /* Timer State  - 0=stopped / 1=running */
    }; /* Elapsed Time and State must be initialized to zero */
#if defined(EN_TIME)

  #define DECLARE_TIMER(A)                                                    \
    struct timmerDetails                                                      \
     A = /* Elapsed Time and State must be initialized to zero */             \
      {                                                                       \
      /* Start   = */ 0,                                                      \
      /* Stop    = */ 0,                                                      \
      /* Elapsed = */ 0,                                                      \
      /* State   = */ 0,                                                      \
      }; /* Timer has been declared and defined,   ;  IS required */
      
/* Write the timing macros here */

/* Start Timer */
  #define START_TIMER(A) 						      \
      { 								      \
	/* Error if timer is running */ 				      \
	if (1 == A.State) 						      \
	  fprintf(stderr, "Error, Timer "#A" is running.\n"); 		      \
	/* State = running */ 						      \
	A.State = 1; 							      \
	/* Start time */ 						      \
	A.Start = clock(); 						      \
      }

/* Reset Timer */ 
  #define RESET_TIMER(A) 						      \
      { 								      \
	/* Time elapsed = zero*/ 					      \
	A.Elapsed = 0; 							      \
      } 
   
/* Stop Timer  */
  #define STOP_TIMER(A) 						      \
      { 								      \
	/* Stop time */							      \
	A.Stop = clock();						      \
	/* Error if timer is stopped */	  		 	 	      \
	if (0 == A.State) 						      \
	  fprintf(stderr, "Error, timer "#A" is stopped.\n"); 		      \
	else 							              \
	A.Elapsed += A.Stop - A.Start; 					      \
	/* STATE = stopped */ 						      \
	A.State = 0; 							      \
	}

/* Print Timer */  
  #define PRINT_TIMER(A)  						      \
      { 								      \
	/* Stop timer if currently running */			 	      \
     	if (1 == A.State) 						      \
	    STOP_TIMER(A); 						      \
	fprintf(stdout, "Time elapsed ("#A") = %g sec.\n", (double)A.Elapsed /\
					(double)CLOCKS_PER_SEC); 	      \
      }

/* Print RTimer */
  #define PRINT_RTIMER(A,R)                                                   \
      {                                                                       \
        /* Stop the timer (slightly) if it is currently running */            \
        if (1 == A.State){                                                    \
            STOP_TIMER(A);                                                    \
      }									      \
        fprintf(stdout, "Elapsed CPU Time per Iteration ("#A", %d) = % .2e sec.\n"\
	, R, ((double)A.Elapsed / (double)CLOCKS_PER_SEC)/(double)R);  	      \
	} /*PRINT_RTIMER() */
  
  #define DECLARE_REPEAT_VAR(V)						      \
	int var = V; 							      \
  
  #define R (1000)
  #define BEGIN_REPEAT_TIMING(R, V) 					      \
	for(var=0; var < R; var++){ 					      \

  #define END_REPEAT_TIMING						      \
	}								      \



#else
  #define DECLARE_TIMER(A) 		/* Null Macro */
  #define START_TIMER(A)		/* Null Macro */
  #define STOP_TIMER(A)			/* Null Macro */
  #define RESET_TIMER(A)		/* Null Macro */
  #define PRINT_TIMER(A)		/* Null Macro */
  #define PRINT_RTIMER(A,R)		/* Null Macro */
  #define DECLARE_REPEAT_VAR(V)		/* Null Macro */
  #define BEGIN_REPEAT_TIMING(R, V) 	/* Null Macro */
  #define END_REPEAT_TIMING  		/* Null Macro */
  #define DECLARE_REPEAT_VAR(V)		/* Null Macro */

#endif 
#endif /* _TIMERS_H_ */
