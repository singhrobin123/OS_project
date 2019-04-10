#include <stdbool.h> 
#include<stdio.h>
#include <pthread.h> 
#include <semaphore.h>
#include<iostream>
#include <string>
using namespace std;
#define ll long long int
#define REP(i,n) for(int i=0;i<(n);i++)
#define P(sem) ( sem_wait(&(sem)))
#define V(sem) ( sem_post(&(sem)))
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
sem_t reindeerHarness, reindeerHarnessDone,reindeerPull , reindeerPullDone;
sem_t elfPuzzled , elfPuzzledDone,elfEnter,elfEnterDone,elfConsult , elfConsultDone;
sem_t wakeup, wakeupReindeer, wakeupElves,harness, harnessDone,pull , pullDone,enter , enterDone;
sem_t consult , consultDone,reindeerBack, reindeerBackDone;
bool b;
void *Reindeer(void *arg)
{ int t;
FOR(t,0,200)
{
P(reindeerBack);
V(reindeerBack);
P(reindeerBackDone);
 V(reindeerBackDone); 
P(reindeerHarness); 
V(reindeerHarness);
P(reindeerHarnessDone);
V(reindeerHarnessDone); 
P(reindeerPull ) ;
V(reindeerPull ) ;
 P(reindeerPullDone);
 V(reindeerPullDone);
}
}
void *Santa(void *arg)
{int i;
FOR(i,0,10)
{
	P(wakeup); 

	if ( b) 
	{
		b = false ; 
        printf("Santa starts \n");  
        V(wakeup);
        P(wakeupReindeer);
		V(wakeupReindeer); 
		P(harness); 
		V(harnessDone); 
		P(pull) ;
		V(pullDone);
	}
	else
	{
    V(wakeup);
	V(wakeupElves);
	FOR(i,0,3){P(enter ) ;V(enter ) ; P(enterDone);V(enterDone); P(consult ) ;V(consult ) ; 
P(consultDone);V(consultDone);}}}
}
void *Sleigh ( void *arg)
{int i;
FOR(i,0,9){P(reindeerBack); V(reindeerBack);}
FOR(i,0,9)
{ P(reindeerBackDone);V(reindeerBackDone);
b = true ;
P(wakeup); V(wakeup); 
P(wakeupReindeer);V(wakeupReindeer);
}
FOR(i,0,9)V(reindeerHarness);
FOR(i,0,9)P(reindeerHarnessDone); V(harness); P(harnessDone);
FOR(i,0,9) V(reindeerPull ) ;
FOR(i,0,9)P(reindeerPullDone);V(pull ) ; P(pullDone);
}

void *Shop(void *arg)
{int i;
FOR(i,0,3){P(elfPuzzled ) ;V(elfPuzzled ) ;}
FOR(i,0,3)
{
 P(elfPuzzledDone);V(elfPuzzledDone);
 P(wakeup);V(wakeup);
 P(wakeupElves);V(wakeupElves);
  }
FOR(i,0,3)
{
P(elfEnter ); V(elfEnter); 
P(elfEnterDone);V(elfEnterDone);
P(enter); V(enter ) ; 
P(enterDone);V(enterDone);
P(elfConsult);V(elfConsult ) ;
P(elfConsultDone); V(elfConsultDone);
P(consult);V(consult ) ; 
P(consultDone);V(consultDone);
}
}
void *Elf ( void *arg)
{
P(elfPuzzled ) ; V(elfPuzzled ) ;
P(elfPuzzledDone);V(elfPuzzledDone);
 P(elfEnter ) ; V(elfEnter ) ;
P(elfEnterDone);V(elfEnterDone);
 P(elfConsult ) ;V(elfConsult ) ;
 P(elfConsultDone);V(elfConsultDone);
 }
 void set(){
sem_init(&wakeup,0,1); 
sem_init (&wakeupReindeer,0,1); 
sem_init (&wakeupElves,0,1);
sem_init(&harness,0,1);
sem_init(&harnessDone,0,1);
sem_init(&pull,0,1);
sem_init(&pullDone,0,1);
sem_init(&enter,0,1);
sem_init(&enterDone,0,1);
sem_init(&consult,0,1); 
sem_init(&consultDone,0,1);
sem_init(&reindeerBack,0,1); 
sem_init(&reindeerBackDone,0,1);
sem_init(&reindeerHarness,0,1);
sem_init(&reindeerHarnessDone,0,1);
sem_init(&reindeerPull,0,1); 
sem_init(&reindeerPullDone,0,1);
sem_init(&elfPuzzled,0,1); 
sem_init(&elfPuzzledDone,0,1);
sem_init(&elfEnter,0,1);
 sem_init(&elfEnterDone,0,1);
sem_init(&elfConsult,0,1);
 sem_init(&elfConsultDone,0,1);
 }
int main()
{ set();
int i;
pthread_t tid ;
FOR(i,0,9)pthread_create (&tid, NULL, Reindeer, NULL);
FOR(i,0,20)pthread_create (&tid, NULL, Elf, NULL);
pthread_create (&tid, NULL, Sleigh, NULL); 
pthread_create (&tid, NULL, Shop, NULL);
pthread_create (&tid, NULL, Santa, NULL); 
pthread_join (tid , NULL);
return 0;
}