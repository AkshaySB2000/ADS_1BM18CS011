#include <bits/stdc++.h> 
using namespace std; 
struct node { 
    	int data; 
    	struct node* next; 
}; 
typedef struct node *NODE;
NODE reverse(NODE head, int k) 
{ 
    	stack<NODE> mystack; 
    	NODE curr = head; 
    	NODE prev = NULL; 
    	while (curr != NULL) 
    	{ 
        	int count = 0; 
        	while (curr != NULL && count < k) 
        	{	 
           		mystack.push(curr); 
            		curr = curr->next; 
            		count++; 
        	} 
		while (mystack.size() > 0) 
		{  
            		if (prev == NULL) 
            		{ 
                		prev = mystack.top(); 
                		head = prev; 
                		mystack.pop(); 
            		} 
            		else 
            		{ 
                		prev->next = mystack.top(); 
                		prev = prev->next; 
                		mystack.pop(); 
            		} 
        	} 
    	} 
  	prev->next = NULL; 
  	return head; 
} 
NODE getnode()
{
	NODE p;
	p = (NODE)malloc(sizeof(struct node));
	if(p != NULL)
		return p;
	else
	{
		cout<<"Memory could not be allocated";
		exit(0);
	}
}
NODE insertend(int item, NODE head)
{
	NODE p,q;
	q = getnode();
	q->data = item;
	if(head==NULL)
	{
		q->next = NULL;
		head = q;
		return head;
	}
	else
	{
		p = head;
		while(p->next!=NULL)
		{
			p = p->next;
		}
		p->next = q;
		q->next = NULL;
		return head;
	}
}
void display(NODE head) 
{ 
	NODE p = head;
    	while (p != NULL) 
    	{ 
        	cout<<p->data<<" "; 
        	p = p->next; 
    	} 
    	cout<<endl;
} 	
int main() 
{ 
  	NODE head;
	head = NULL;
	int n,k;
	cout<<"Enter number of elements\n";
	cin>>n;
	int a[n];
	cout<<"Enter the elements\n";
    	for(int i=0; i<n; i++)
    	{
        	cin>>a[i];
		head = insertend(a[i],head);
	}
    	cout<<"\nGiven linked list\n"; 
   	display(head); 
	cout<<"\nEnter value of k\n";
    	cin>>k;
    	head = reverse(head,k); 
  	cout<<"\nReversed Linked list\n"; 
    	display(head); 
    	return 0; 
} 

/*Output:

1.
Enter number of elements
8
Enter the elements
1 2 2 4 5 6 7 8

Given linked list
1 2 2 4 5 6 7 8 

Enter value of k
4

Reversed Linked list
4 2 2 1 8 7 6 5 

2.
Enter number of elements
5
Enter the elements
1 2 3 4 5

Given linked list
1 2 3 4 5 

Enter value of k
3

Reversed Linked list
3 2 1 5 4 
*/	
	
