#include<iostream>
#include<cstdlib>
#include<omp.h>
#include<time.h>
#define MAX 10000
using namespace std;

void swap(int &a, int &b)
{
	int x=a;
	a=b;
	b=x;
}

void display(int array[MAX], int n)
{
	cout<<"\nArray : ";
	for(int i=00;i<n;i++)
		cout<<array[i]<<"\t";
}
clock_t start=clock();
void parallel_bubble(int array[MAX],int n)
{
	for(int k=0;k<n-1;k++)
	{
		if(k%2==0)	//even
		{
			//#pragma omp parallel for
			for(int i=0;i<n/2;i++)
			{
				if(array[2*i]>array[2*i+1])
					swap(array[2*i],array[2*i+1]);
			}
		}
		
		else
		{
			//#pragma omp parallel for
			for(int i=0;i<(n/2)-1;i++)
			{
				if(array[2*i+1]>array[2*i+2])
					swap(array[2*i+1],array[2*i+2]);
			}
		}
	}
}
clock_t stop=clock();

int main()
{
	int n,array[MAX];
	cout<<"\n Enter the number of elements : ";
	cin>>n;
	
	for(int i=0;i<n;i++)
		array[i]=rand()%22;
		
	display(array,n);
	parallel_bubble(array,n);
	display(array,n);
	
	cout<<"\nTime required : "<<(double)(stop-start)*1000.0/CLOCKS_PER_SEC<<" ms";			
	return 0;
}

/*
gautami@Asus:~/HPC$ g++ par_bubble.cpp -fopenmp
gautami@Asus:~/HPC$ time ./a.out

 Enter the number of elements : 50

Array : 17	10	17	13	1	15	0	6	3	18	7	16	3	7	4	20	10	2	0	21	8	5	11	4	6	0	21	3	21	21	18	10	14	7	9	7	8	13	10	721	15	1	0	21	4	20	7	6	
Array : 0	0	0	0	1	1	1	2	3	33	4	4	4	5	6	6	6	7	7	77	7	7	8	8	8	9	10	10	10	10	11	13	13	14	15	15	16	17	17	18	20	20	21	21	21	21	21	21	
Time required : 0.002 ms
real	0m3.489s
user	0m0.004s
sys	0m0.000s
*/

