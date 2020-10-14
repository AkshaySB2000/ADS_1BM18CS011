#include<bits/stdc++.h>
using namespace std;
class node {
	public:
	int data;
	node *left;
	node *right;
	int height;
};
int max(int a, int b) {
	return (a>b)?a:b;
}
int returnheight(node *p) {
	if(p == NULL)
		return 0;
	return p->height;
}
node* getnode(int data) {
	node *p = new node();
	p->data = data;
	p->left = NULL;
	p->right = NULL;
	p->height = 1;
	return(p);
}
node *rotateleft(node *a) {
	node *b = a->right;
	node *t = b->left;
	b->left = a;
	a->right = t;
	a->height = max(returnheight(a->right), returnheight(a->left))+1;
	b->height = max(returnheight(b->left), returnheight(b->right))+1;
	return b;
}
node *rotateright(node *b) {
	node *a = b->left;
	node *t = a->right;
	a->right = b;
	b->left = t;
	b->height = max(returnheight(b->left), returnheight(b->right))+1;
	a->height = max(returnheight(a->right), returnheight(a->left))+1;
	return a;
}
int balance(node *p) {
	if(p == NULL)
		return 0;
	return returnheight(p->left)-returnheight(p->right);
}
node* insertion(node* p, int data)  
{  
	if(p == NULL)  
		return(getnode(data));  
      	if(data < p->data)  
        	p->left = insertion(p->left, data);  
    	else if(data > p->data)  
        	p->right = insertion(p->right, data);  
    	else  
        	return p;  
    	p->height = 1 + max(returnheight(p->left), returnheight(p->right));  
    	int bl = balance(p);  
    	if (bl > 1 && data < p->left->data)  
        	return rotateright(p);  
    	if (bl < -1 && data > p->right->data)  
        	return rotateleft(p);  
    	if (bl > 1 && data > p->left->data) {  
        	p->left = rotateleft(p->left);  
        	return rotateright(p);  
    	}  
    	if (bl < -1 && data < p->right->data) {  
        	p->right = rotateright(p->right);  
        	return rotateleft(p);  
    	}  
    	return p;  
}  
node* minvalue(node* root) {
	node* curr = root;
	while(curr->left != NULL)
		curr = curr->left;
	return curr;
}
node* deletion(node* root, int item)  
{  
	if(root == NULL)  
        	return root;  
     	if(item < root->data)  
        	root->left = deletion(root->left, item);  
    	else if(item > root->data)  
        	root->right = deletion(root->right, item);  
    	else
    	{  
        	if((root->left == NULL) || (root->right == NULL))  
        	{  
            		node *t = root->left?root->left:root->right;  
            		if (t == NULL)  
            		{  
            	    		t = root;  
                		root = NULL;  
            		}  
            		else 
            			*root = *t; 
            		free(t);  
        	}  
        	else
        	{  
            		node* t = minvalue(root->right); 
            		root->data = t->data;  
            		root->right = deletion(root->right, t->data);  
        	}  
    	}  
     	if (root == NULL)  
    		return root;  
     	root->height = 1 + max(returnheight(root->left), returnheight(root->right));  
     	int bl = balance(root);  
     	if(bl > 1 && balance(root->left) >= 0)  
        	return rotateright(root);  
     	if(bl > 1 && balance(root->left) < 0)  
    	{  
        	root->left = rotateleft(root->left);  
        	return rotateright(root);  
    	}  
    	if (bl < -1 && balance(root->right) <= 0)  
        	return rotateleft(root);  
    	if (bl < -1 && balance(root->right) > 0)  
    	{  
        	root->right = rotateright(root->right);  
        	return rotateleft(root);  
    	}  
      	return root;  
}  
void preorder(node *root) {
	if(root != NULL) {
		cout<<root->data<<" ";
		preorder(root->left);
		preorder(root->right);
	}
}
int main() {
	int n,ch,ch1,item;
	node *root = NULL;
	cout<<"Enter the number of elements to be inserted\n";
	cin>>n;
	cout<<"Enter the elements\n";
	for(int i = 0; i < n; i++) {
		cin>>item;
		root = insertion(root, item);
	}
	cout<<"\nElements have been inserted\n";
	cout<<"\nThe Preorder traversal of the tree is as follows\n";
	preorder(root);
	cout<<endl;
	cout<<"\nEnter the element to be deleted\n";
	cin>>item;
	root = deletion(root, item);
	cout<<"\nElement has been deleted\n";
	cout<<"\nThe Preorder traversal of the tree after deletion is as follows\n";
	preorder(root);
	cout<<endl;
	return 0;
}		
				
	
	
	
	
	
