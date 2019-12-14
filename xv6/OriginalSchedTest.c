#include "types.h"
#include "user.h"

int main()
{
    const int fork_num = 10;
    int i;
    struct timeVariables *t[fork_num];
    int childrenId[fork_num];
    int creationTime, terminationTime, sleepingTime, readyTime, runningTime;
	int sum_terminationTime = 0, sum_WaitingTime = 0, sum_creationTime = 0;
	int avg_terminationTime, avg_waitinTime, avg_creationTime;

	changePolicy(1);

    for (i = 0; i < fork_num; i++)
        t[i] = (struct timeVariables *)malloc(sizeof(struct timeVariables));

    for (i = 0; i < fork_num; i++)
    {
        if (fork() == 0)
        {
            for (i = 0; i < 1000; i++)
                printf(1, "%d: %d\n", getpid(), (i+1));
            exit();
        }
    }
    for (i = 0; i < fork_num; i++){
        childrenId[i] = waitForChild(t[i]);
    }
	printf(1, "\n");
    for (i = 0; i < fork_num; i++)
    {
        if (childrenId[i] != -1)
        {
            creationTime = t[i]->creationTime;
            terminationTime = t[i]->terminationTime;
            sleepingTime = t[i]->sleepingTime;
            readyTime = t[i]->readyTime;
            runningTime = t[i]->runningTime;
            printf(1, "process %d -> created: %d - terminated: %d - slept: %d - ready: %d - running: %d\n", childrenId[i], creationTime, terminationTime, sleepingTime, readyTime, runningTime);
            printf(1, "T.T: %d, W.T: %d, CBT: %d\n", (terminationTime - creationTime), (terminationTime - creationTime - runningTime), runningTime);
            printf(1, "====================================================================================\n");
			sum_terminationTime += terminationTime - creationTime;
			sum_WaitingTime += terminationTime - creationTime - runningTime;
			sum_creationTime += runningTime;
        }
    }
	avg_terminationTime = sum_terminationTime / fork_num;
	avg_waitinTime = sum_WaitingTime / fork_num;
	avg_creationTime = sum_creationTime / fork_num;
	printf(1, "\nAvg T.T: %d, Avg W.T: %d, Avg CBT: %d\n", avg_terminationTime, avg_waitinTime, avg_creationTime);
	printf(1, "=========================================\n");

	return 0;
}
