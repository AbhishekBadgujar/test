#include<iostream>
#include<string.h>
#include<omp.h>
#include<math.h>
#include<stdlib.h>
#define max 10
using namespace std;

class KNN
{
	public:
		float ht;
		int wt,val,dist;
};//end of class

int main()
{
	KNN a[max];
	int cnt1=0,cnt2=0;
	float nh;
	int nw;
	
	
	//Matrix initialisation
	a[0].ht=5.1;
	a[0].wt=40;
	a[0].val=1;

	a[1].ht=5.2;
	a[1].wt=50;
	a[1].val=1;

	a[2].ht=3;
	a[2].wt=45;
	a[2].val=0;

	a[3].ht=5.5;
	a[3].wt=47;
	a[3].val=1;

	a[4].ht=5.3;
	a[4].wt=66;
	a[4].val=0;

	a[5].ht=5;
	a[5].wt=45;
	a[5].val=1;

	a[6].ht=6;
	a[6].wt=55;
	a[6].val=1;

	a[7].ht=5;
	a[7].wt=32;
	a[7].val=0;

	a[8].ht=2.9;
	a[8].wt=40;
	a[8].val=0;

	a[9].ht=6.4;
	a[9].wt=89;
	a[9].val=0;

	
	cout<<"\nEnter the height :";
	cin>>nh;

	cout<<"\nEnter the weight : ";
	cin>>nw;

	#pragma omp parallel for
	for(int i=0;i<max;i++)	//calculation of euclidean distance
		a[i].dist=sqrt((nh-a[i].ht)*(nh-a[i].ht)+(nw-a[i].wt)*(nw-a[i].wt));
		
	int k=3;
	for(int i=0;i<max;i++)	//sorting acc. to euclidean distance
	{
		int first=i%2;
		#pragma omp parallel for shared(a,first)
		for(int j=first;j<max-1;j+=2)
		{
			if(a[j].dist>a[j+1].dist)
			{
				KNN temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	cout<<"\n--------------------SORTED DISTANCES--------------------\n";
	cout<<"\nHEIGHT\tWEIGHT\tDISTANCE\tVALUE\n";
	for(int i=0;i<max;i++)
	{
		cout<<"\n"<<a[i].ht<<"\t"<<a[i].wt<<"\t"<<a[i].dist<<"\t\t"<<a[i].val;
	}				
	cout<<"\nEnter the value of 'k' : ";
	cin>>k;		
	
	for(int i=0;i<k;i++)
	{
		if(a[i].val==0)
		{
			cnt1++;
		}
		else
		{
			cnt2++;
		}
	}
	if(cnt1>cnt2)
	{
		cout<<"\n Person is abnormal(underweight/overweight)";
	}
	else
	{
		cout<<"\n Person is normal(proper weight/balanced ht,wt)";			
	}
return 0;
}		
/*
gautami@Asus:~/HPC$ g++ par_knn.cpp -fopenmp
gautami@Asus:~/HPC$ time ./a.out

Enter the height :40

Enter the weight : 50

--------------------SORTED DISTANCES--------------------

HEIGHT	WEIGHT	DISTANCE	VALUE

5.2	50	34		1
5.5	47	34		1
6	55	34		1
5	45	35		1
5.1	40	36		1
3	45	37		0
5.3	66	38		0
2.9	40	38		0
5	32	39		0
6.4	89	51		0
Enter the value of 'k' : 3

 Person is normal(proper weight/balanced ht,wt)
real	0m15.012s
user	0m0.028s
sys	0m0.004s

*/	
