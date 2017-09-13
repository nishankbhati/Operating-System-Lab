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
#include<bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<pthread.h>
using namespace std;

inline void FAST_IO(void){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
};
const long long int INF=2e18;
const long MOD=1e9+7;

#define PB push_back
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define read(type) readInt<type>()
const double pi=acos(-1.0);
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef map<int,int> MPII;
typedef set<int> SETI;
typedef multiset<int> MSETI;
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;
/*Original program starts*/

int arr[10];
int bur[10];

void findWaitingTime(int arr[], int n,
             int bur[], int wt[], int quan)
{
    int store_bur[n];
    for (int i = 0 ; i < n ; i++)
        store_bur[i] =  bur[i];

    int t = 0;
    while (true)
    {
        bool done = true;
    for (int i = 0 ; i < n; i++)
        {if (store_bur[i] > 0)
            {done = false;
            if (store_bur[i] > quan)
                {
                    t += quan;
                    store_bur[i] -= quan;
                }
            else
                {
                    t = t + store_bur[i];
                    wt[i] = t - bur[i];
                    store_bur[i] = 0;
                }
            }
        }


        if (done == true)
          break;
    }
}


void findTurnAroundTime(int arr[], int n,int bur[], int wt[], int tat[])
{
   for (int i = 0; i < n ; i++)
        tat[i] = bur[i] + wt[i];
}


void* execute(void* v)
{   int n=10;
    int quan =1;
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(arr, n, bur, wt, quan);
    findTurnAroundTime(arr, n, bur, wt, tat);
     cout << "arrival time "<< "Burst time "
         << " Waiting time " << " Turn around time\n";


    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i+1 << "\t\t" << bur[i] <<"\t "
             << wt[i] <<"\t\t " << tat[i] <<endl;
    }

    cout << "Average waiting time = "<< (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "<< (float)total_tat / (float)n;
    cout << "\n";
}
void swap(int *a,int* b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}
void *create(void* arri)
{
	int i,temp1,temp2;
	for(i=0;i<10;i++)
	{
		arr[i] = rand()%10+1;
		bur[i] = rand()%10+1;

	}
	int j ;
	for(i=0;i<10;i++)
	{
		for(j=0;j<9;j++)
		{
			if(arr[j] > arr[j+1])
			{   temp1 = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp1;
                temp2 = bur[j];
                bur[j] = bur[j+1];
                bur[j+1] = temp2;
			}
		}
	}


}
int main()
{
	int i=1;
	pthread_t t1;
	pthread_create(&t1,NULL,create,&i);
	pthread_t t2;
	pthread_create(&t2,NULL,execute,&i);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}
