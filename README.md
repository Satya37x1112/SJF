## SJF (SHORTEST JOB FIRST) Scheduling
In the Shortest Job First scheduling algorithm, the processes are scheduled in ascending order of their CPU burst times, i.e. the CPU is allocated to the process with the shortest execution time.
Variants of SJF Scheduling

**There are two variants of SJF scheduling −**

## SJF non-preemptive scheduling
In the non-preemptive version, once a process is assigned to the CPU, it runs into completion. Here, the short term scheduler is invoked when a process completes its execution or when a new process(es) arrives in an empty ready queue.

## SJF preemptive scheduling
This is the preemptive version of SJF scheduling and is also referred as Shortest Remaining Time First (SRTF) scheduling algorithm. Here, if a short process enters the ready queue while a longer process is executing, process switch occurs by which the executing process is swapped out to the ready queue while the newly arrived shorter process starts to execute. Thus the short term scheduler is invoked either when a new process arrives in the system or an existing process completes its execution.
