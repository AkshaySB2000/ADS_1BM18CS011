#include<bits/stdc++.h>
#include<inttypes.h>
using namespace std;
struct node
{
	int data;
    	struct node* xnp;
};
typedef struct node* NODE;
NODE XOR(NODE p, NODE q)
{
    	return (NODE)((uintptr_t)(p) ^ (uintptr_t)(q));
}
void insertfront(NODE *head, int data)
{
	NODE newnode;
    	newnode = (NODE)malloc(sizeof(struct node));
    	newnode->data = data;
    	newnode->xnp = NULL;
    	if(*head==NULL)
    	{
		*head= newnode;
    	}
     	else
	{
		newnode->xnp = *head;
		(*head)->xnp = XOR((*head)->xnp,newnode);
		*head = newnode;
	}
}
void insertend(NODE *head, int data)
{
	NODE newnode;
    	newnode=(NODE)malloc(sizeof(struct node));
    	newnode->data = data;
	newnode->xnp = NULL;
    	if(head==NULL)
        {
       	*head = newnode;
        }
    	else
    	{
        	NODE curr=*head;
        	NODE prev=NULL;
        	NODE x;
        	while(curr->xnp != prev)
        	{
            		x = curr;
            		curr = XOR(curr->xnp, prev);
			prev = x;
        	}
     		curr->xnp = XOR(curr->xnp,newnode);
		newnode->xnp = curr;

    	}
}
void display(NODE *head)
{
    NODE curr;
    NODE prev=NULL;
    NODE next;
    curr = *head;
    while(curr!= NULL)
    {
        cout<< curr->data<<" ";
        next = XOR(prev,curr->xnp);
        prev = curr;
        curr = next;
    }
}
int main()
{
	    NODE head = NULL;
	    int x,y,n,ch,ch1;
	    do {
	            cout<<"Enter\n1 to insert at front\n2 to insert at end\n";
	    	    cin>>ch;
		    switch(ch) {
		    case 1: cout<<"Enter no of elements to be inserted at the beginning"<<endl;
		    	    cin>>n;
			    cout<<"Enter elements"<<endl;
			    for(int i=0;i<n;i++)
			    {
					cin>>x;
				 	insertfront(&head,x);
			    }
		    	    cout<<"Elements in the list are: "<<endl;
			    display(&head);
			    cout<<endl;
			    break;
		    case 2: cout<<"Enter no of elements to be inserted at the end"<<endl;
		     	    cin>>n;
			    cout<<"Enter elements"<<endl;
			    for(int i=0;i<n;i++)
		     	    {
					cin>>y;
					insertend(&head,y);
		    	    }
		    	    cout<<"Elements in the list are: "<<endl;
		    	    display(&head);
		    	    cout<<endl;
		    	    break;
		    default: cout<<"\nInvalid Input\n";
		    }
		    cout<<"Enter 1 to continue\n";
		    cin>>ch1;
  	    }while(ch1==1);
	    return 0;
}

/*Output :

Enter
1 to insert at front
2 to insert at end
1
Enter no of elements to be inserted at the beginning
3
Enter elements
2 4 8
Elements in the list are: 
8 4 2 
Enter 1 to continue
1
Enter
1 to insert at front
2 to insert at end
2
Enter no of elements to be inserted at the end
4
Enter elements
1 3 5 9
Elements in the list are: 
8 4 2 1 3 5 9 
Enter 1 to continue
2

*/
