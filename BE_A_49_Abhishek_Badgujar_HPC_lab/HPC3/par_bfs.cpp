#include<iostream>
#include<cstdlib>
#include<queue>
using namespace std;
class node
{
	public:
		node *left,*right;
		int data;
};	 

class Breadthfs
{
	public:
		node* insert(node*, int);
		void bfs(node*);
};

node* insert(node *root, int data)
{
	if(!root)
	{
		root=new node;
		root->left=NULL;
		root->right=NULL;
		root->data=data;
		return root;
	}

	queue<node *> q;
	q.push(root);
	
	while(!q.empty())
	{
		node *temp=q.front();
		q.pop();
	
		if(temp->left==NULL)
		{
			temp->left=new node;
			temp->left->left=NULL;
			temp->left->right=NULL;
			temp->left->data=data;	
			return root;
		}
		else
			q.push(temp->left);

		if(temp->right==NULL)
		{
			
			temp->right=new node;
			temp->right->left=NULL;
			temp->right->right=NULL;
			temp->right->data=data;	
			return root;
		}
		else
			q.push(temp->right);
	}
}

void bfs(node *head)
{
	queue<node*> q;
	q.push(head);
	int qSize;
	int i=0;
	while (!q.empty()) 
	{
		cout<<"\n Level "<<i++;
		qSize = q.size();
		#pragma omp parallel for
		for(int i=0;i<qSize;i++) 
		{
			node* currNode;
			#pragma omp critical
			{
				currNode=q.front();
				q.pop();
				cout<<"\t"<<currNode->data;
			}
			#pragma omp critical
			{
				if(currNode->left)
					q.push(currNode->left);
				if(currNode->right)
					q.push(currNode->right);
			}		
		}
	}
}

int main()
{
	node *root=NULL;
	int data;
	char ans;
	do
	{
		cout<<"\nEnter data : ";
		cin>>data;
		root=insert(root,data);
		cout<<"\nContinue inserting data (y/n) : ";
		cin>>ans;
	
	}while(ans=='y'||ans=='Y');
	cout<<"\n----Breadth First Search----";
	bfs(root);
	cout<<"\n----------------------------";
	return 0;
}
/*
gautami@Asus:~$ cd HPC
gautami@Asus:~/HPC$ g++ par_bfs.cpp -fopenmp
gautami@Asus:~/HPC$ time ./a.out

Enter data : 1

Continue inserting data (y/n) : y

Enter data : 2

Continue inserting data (y/n) : y

Enter data : 3

Continue inserting data (y/n) : y

Enter data : 4

Continue inserting data (y/n) : n

----Breadth First Search----
 Level 0	1
 Level 1	2	3
 Level 2	4
----------------------------
real	0m9.564s
user	0m0.024s
sys	0m0.000s

*/
