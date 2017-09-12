/*
Q> Implement multi-threaded Round Robin scheduling algorithm by creating two
threads in main program. Thread one will generate one or many processes after some time slice
(using random numbers for process arrival time starting from 0 to n, its Burst time) and you can
assume any suitable time quantum. The second thread performs the actual execution of these
processes as per the Round Robin algorithm and displays the process execution sequence. At last,
main program will display various performance matrices for each process including completion
time, turnaround time, waiting time, response time and their averages for this execution. The
generated arrival time should be in increasing order.
*/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<bits/stdc++.h>
using namespace std;
int arr[10];
int bur[10];
void findwaitingtime(int arr[],int bur[],int n,int quan,int wt[])
{
	int rem_bt[n];
	int t;
	int i=0;
	for(i=0;i<n;i++)
	rem_bt[i]=bur[i];
	while(1){
		bool done = true;
		for(i=0;i<n;i++)
		{
			if(rem_bt[i]>0)
			{
				done=false;
				if(rem_bt[i]>quan)
				{
					t+=quan;
					rem_bt[i]-=quan;
				}
				else
				{
					t=t+rem_bt[i];
					wt[i]=t-bur[i];
					rem_bt[i]=0;
				}
			}
		}
		if(done==true) break;
	}
}

void turnaroundtime(int arr[],int bur[],int  n,int quan,int tat[],int wt[])
{
	int i=0;
	for(i=0;i<n;i++)
		tat[i]=bur[i]+wt[i];
}

void* findavgtime(void* v)
{
	int n=10;
	int quan=1;
	int wt[n];
	int tat[n];
	float avg_wt;
	int tot_wt;
	int tot_tat;
	float avg_tat;
	int ct[n];
	findwaitingtime(arr,bur,n,quan,wt);
	turnaroundtime(arr,bur,n,quan,tat,wt);
	int i=0;
	printf("Arrival-time , Burst-time , waiting time , turn-around-time , Complition-time\n");
	for(i=0;i<n;i++)
	{
		tot_wt+=wt[i];
		tot_tat+=tat[i];
		ct[i]=tat[i]+arr[i];
		printf("%d\t%d\t%d\t%d\t%d\n",arr[i],bur[i],wt[i],tat[i],ct[i]);
	}
	avg_wt=(float)tot_wt/(float)n;
	avg_tat=(float)tot_tat/(float)n;
	printf("Avarage Waiting time: %f\n",avg_wt);
	printf("Avarage Turn Around Time: %f\n",avg_tat);
}

void swap(int *a,int* b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void *generate(void* arri)
{
	int i;
	for(i=0;i<10;i++)
	{
		arr[i] = rand()%10;
		bur[i] = rand()%30;
		printf("arr[%d]: %d and brst[%d]: %d\n",i,arr[i],i,bur[i]);
	}
	int j=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<10;j++)
		{
			if(arr[j] > arr[j+1])
			{
				swap(arr[j],arr[j+1]);
				swap(bur[j],bur[j+1]);
			}
		}
	}
	printf("\n\n");
	for(i=0;i<10;i++)
	{
		
		printf("arr[%d]: %d and brst[%d]: %d\n",i,arr[i],i,bur[i]);
	}
}
int main()
{
	int i=1;
	pthread_t p1;
	pthread_create(&p1,NULL,generate,&i);
	pthread_t p2;
	pthread_create(&p2,NULL,findavgtime,&i);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
}