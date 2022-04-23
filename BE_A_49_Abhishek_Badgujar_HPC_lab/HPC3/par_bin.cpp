#include<iostream>
#include<stdlib.h>
#include<omp.h>
#define MAX 50
using namespace std;

int binary(int array[], int low, int high, int key)
{
	int mid;	
	mid=(low+high)/2;
	int low1,low2,high1,high2,mid1,mid2,found=0,loc=-1;
	#pragma omp parallel sections
	{
		#pragma omp section
    		{ 
			low1=low;
			high1=mid;
			while(low1<=high1)
			{
				if(!(key>=array[low1] && key<=array[high1]))
				{
					low1=low1+high1;
					continue;
				}
				mid1=(low1+high1)/2;
				if(key==array[mid1])
				{
					found=1;
					loc=mid1;
					low1=high1+1;
				}
					
				else if(key>array[mid1])
					low1=mid1+1;
				
				else if(key<array[mid1])
					high1=mid1-1;
			}
		}
				  
		#pragma omp section
    		{ 
      			low2=mid+1;
			high2=high;
			while(low2<=high2)
			{
				if(!(key>=array[low2] && key<=array[high2]))
				{
					low2=low2+high2;
					continue;
				}
				
				mid2=(low2+high2)/2;
				
				if(key==array[mid2])
				{
					found=1;
					loc=mid2;
					low2=high2+1;	
				}									
				else if(key>array[mid2])
					low2=mid2+1;
				else if(key<array[mid2])
					high2=mid2-1;
			}	
    		}
	}
	return loc;
}
int main()
{
	int array[MAX],i,n,key,loc=-1;
	cout<<"\nEnter the number of elements : ";
	cin>>n;
	
	cout<<"\nEnter the elements (in ascending order) : \n";
	for(i=0;i<n;i++)
		cin>>array[i];
	
	cout<<"\nEnter the key (number to be found) :";
	cin>>key;
	
	loc=binary(array,0,n-1,key);

	if(loc==-1)
		cout<<"\nKey not found.";
	else
		cout<<"\nKey found at position : "<<loc+1;
	return 0;
}
/*
gautami@Asus:~/HPC$ g++ par_bin.cpp -fopenmp
gautami@Asus:~/HPC$ time ./a.out

Enter the number of elements : 3

Enter the elements (in ascending order) : 
1
2
3

Enter the key (number to be found) :3

Key found at position : 3
real	0m10.198s
user	0m0.008s
sys	0m0.000s

*/
