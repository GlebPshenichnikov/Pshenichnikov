#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>
#include <signal.h>

#define N 5
int num; // семафор на кол-во филосовов за столом
int semid;//N семафарово на вилки

void eat(int i)
{
    printf("Философ номер %d is eating\n", i);
    sleep(3);
}

void think(int i)
{
    printf("Философ номер %d is thinking\n", i);
    sleep(3);
}


void take_fork(int i)
{
    struct sembuf sem;
    sem.sem_num = i;
    sem.sem_op = -1;
    sem.sem_flg = 0;

    semop(semid, &sem, 1);
}

void put_fork(int i)
{
    struct sembuf sem;
    sem.sem_num = i;
    sem.sem_op = 1;
    sem.sem_flg = 0;

    semop(semid, &sem, 1);
}

void up(int num)
{
    struct sembuf sem;
    sem.sem_num = 0;
    sem.sem_op = 1;
    sem.sem_flg = 0;

    semop(num, &sem, 1);
}

void down(int num)
{
    struct sembuf sem;
    sem.sem_num = 0;
    sem.sem_op = -1;
    sem.sem_flg = 0;

    semop(num, &sem, 1);
}


void philosopher (int i)
{ 
    while (1) 
    { 
        think(i);
        down(num); /* входит в столовую, садится за стол */
        take_fork(i); /*берет левую вилку*/
        take_fork((i+1)%N); /*берет правую вилку*/

        eat(i); 

        put_fork(i); /*кладет обратно левую вилку*/
        put_fork((i+1)%N); /* кладет обратно правую вилку */
        up(num); /* встает из-за стола, идет гулять в сад */
    }
}

int main()
{
    int i;
    semid = semget(IPC_PRIVATE, N, IPC_CREAT | 0666);
    num = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666); 

    semctl(num, 0, SETVAL, 4);
    for (i = 0; i < N; i++) semctl(semid, i, SETVAL, 1);
    
    for (i = 0; i < N; i++)
        if (fork() == 0)
        {
            philosopher(i);
            exit(0);
        }
        
    signal(SIGINT, SIG_IGN);
    for (i = 0; i < N; i++)
        wait(NULL);

    semctl(semid, 0, IPC_RMID, 0);
    semctl(num, 0, IPC_RMID, 0);
    
}
