#include <bits/stdc++.h>
using namespace std;
class node{
	int *data;
	node **child;
	int n;
	bool leaf;
	public:
		node(bool leaf);
		void traversal();
		int search(int item);
		void insertionnonfull(int item);
		void splitc(int i, node *y);
		void deletion(int item);
		void deletionleaf(int itemx);
		void deletionnonleaf(int itemx);
		int predecessor(int itemx);
		int successor(int itemx);
		void fill(int itemx);
		void borrownext(int itemx);
		void borrowprev(int itemx);
		void merge(int itemx);
		friend class twothree;
};
class twothree{
	node *root = NULL;
	public:
		void traversal()
		{
			if(root != NULL)
				root->traversal();
		}
		void insertion(int item);
		void deletion(int item);
};
node::node(bool leaf1){
	leaf = leaf1;
	data = new int[3];
	child = new node *[4];
	n = 0;
}
int node::search(int item){
	int itemx = 0;
	while(itemx<n && data[itemx]<item)
		++itemx;
	return itemx;
}
void twothree::insertion(int item){
	if(root == NULL){
		root = new node(true);
		root->data[0] = item;
		root->n = 1;
	}
	else{
		if(root->n == 3){
			node *s = new node(false);
			s->child[0] = root;
			s->splitc(0, root);
			int i = 0;
			if(s->data[0]<item)
				i++;
			s->child[i]->insertionnonfull(item);
			root = s;
		}
		else
			root->insertionnonfull(item);
	}
}
void node::insertionnonfull(int item){
	int i = n-1;
	if(leaf == true)
	{
		while(i>=0 && data[i] > item)
		{
			data[i+1] = data[i];
			i--;
		}
		data[i+1] = item;
		n = n + 1;
	}
	else{
		while(i>=0 && data[i]>item)
			i--;
		if(child[i+1]->n == 3)
		{
			splitc(i+1, child[i+1]);
			if(data[i+1]<item)
				i++;
		}
		child[i+1]->insertionnonfull(item);
	}
}
void node::splitc(int i, node *y){
	node *z = new node(y->leaf);
	z->n = 1;
	z->data[0] = y->data[2];
	if(y->leaf == false){
		for(int j=0; j<2; j++)
			z->child[j] = y->child[j+2];
	}
	y->n = 1;
	for(int j=n; j>=i+1; j--)
		child[j+1] = child[j];
	child[i+1] = z;
	for (int j = n-1; j >= i; j--) 
        	data[j+1] = data[j]; 
  
    	data[i] = y->data[1]; 
     	n = n + 1; 
}
void node::traversal(){
	cout<<endl;
	int i;
	for(i=0; i<n; i++){
		if(leaf == false)
			child[i]->traversal();
		cout<<" "<<data[i];
	}
	if(leaf == false)
		child[i]->traversal();
	cout<<endl;
}
void node::deletion(int item){
	int itemx = search(item);
	if(itemx<n && data[itemx] == item){
		if(leaf)
			deletionleaf(itemx);
		else
			deletionnonleaf(itemx);
	}
	else{
		if(leaf){
			cout<<"The key doesn't exist"<<endl;
			return;
		}
		bool flag = ((itemx==n)?true : false);
		if(child[itemx]->n < 2)
			fill(itemx);
		if(flag && itemx>n)
			child[itemx-1]->deletion(item);
		else
			child[itemx]->deletion(item);
	}
	return;
}
void node::deletionleaf(int itemx){
	for(int i=itemx+1; i<n; ++i)
		data[i-1] = data[i];
	n--;
	return;
}
void node::deletionnonleaf(int itemx){
	int item = data[itemx];
	if(child[itemx]->n >=2){
		int pred = predecessor(itemx);
		data[itemx] = pred;
		child[itemx]->deletion(pred);
	}
	else if(child[itemx+1]->n >= 2){
		int succ = successor(itemx);
		data[itemx] = succ;
		child[itemx+1]->deletion(succ);
	}
	else{
		merge(itemx);
		child[itemx]->deletion(item);
	}
	return;
}
int node::predecessor(int itemx){
	node *curr = child[itemx];
	while(!curr->leaf)
		curr = curr->child[curr->n];
	return curr->data[curr->n-1];
}
int node::successor(int itemx){ 
	node *curr = child[itemx+1]; 
    	while (!curr->leaf) 
    		curr = curr->child[0]; 
    	return curr->data[0]; 
} 
void node::fill(int itemx){ 
	if(itemx!=0 && child[itemx-1]->n>=2) 
        	borrowprev(itemx); 
    	else if (itemx!=n && child[itemx+1]->n>=2) 
        	borrownext(itemx); 
    	else{ 
        	if (itemx != n) 
            		merge(itemx); 
        	else
            		merge(itemx-1); 
    	} 
    	return; 
} 
void node::borrowprev(int itemx){ 
    	node *c=child[itemx]; 
    	node *sibling=child[itemx-1]; 
    	for (int i=c->n-1; i>=0; --i) 
        	c->data[i+1] = c->data[i]; 
    	if (!c->leaf){ 
        	for(int i=c->n; i>=0; --i) 
        	    c->child[i+1] = c->child[i]; 
    	} 
    	c->data[0] = data[itemx-1]; 
    	if(!c->leaf) 
        	c->child[0] = sibling->child[sibling->n]; 
    	data[itemx-1] = sibling->data[sibling->n-1]; 
    	c->n += 1; 
    	sibling->n -= 1; 
   	return; 
} 
void node::borrownext(int itemx) { 
      	node *c=child[itemx]; 
    	node *sibling=child[itemx+1]; 
      	c->data[(c->n)] = data[itemx]; 
    	if (!(c->leaf)) 
        	c->child[(c->n)+1] = sibling->child[0];  
    	data[itemx] = sibling->data[0]; 
     	for (int i=1; i<sibling->n; ++i) 
        	sibling->data[i-1] = sibling->data[i]; 
    	if (!sibling->leaf){ 
        	for(int i=1; i<=sibling->n; ++i) 
            		sibling->child[i-1] = sibling->child[i]; 
    	} 
    	c->n += 1; 
    	sibling->n -= 1; 
    	return; 
} 
void node::merge(int itemx){ 
    	node *c = child[itemx]; 
    	node *sibling = child[itemx+1]; 
    	c->data[1] = data[itemx]; 
    	for (int i=0; i<sibling->n; ++i) 
        	c->data[i+2] = sibling->data[i]; 
    	if (!c->leaf){ 
        	for(int i=0; i<=sibling->n; ++i) 
            		c->child[i+2] = sibling->child[i]; 
    	} 
      	for (int i=itemx+1; i<n; ++i) 
        	data[i-1] = data[i]; 
     	for (int i=itemx+2; i<=n; ++i) 
        	child[i-1] = child[i]; 
    	c->n += sibling->n+1; 
    	n--; 
    	delete(sibling); 
    	return; 
} 
void twothree::deletion(int item){ 
    	if (!root){ 
        	cout << "The tree is empty\n"; 
        	return; 
    	} 
     	root->deletion(item); 
    	if (root->n==0){ 
        	node *temp = root; 
        	if (root->leaf) 
            		root = NULL; 
        	else
            		root = root->child[0]; 
 
        	delete temp; 
    	} 
    	return; 
} 
int main() { 
    	twothree t; 
	int n,k;
	cout<<"Enter the no. of elements\n";
	cin>>n;
	cout<<"Enter the data to be inserted\n";
	for(int i=0; i<n; i++)
	{
		cin>>k;
		t.insertion(k);
	}
	cout<<"Traversal of tree after insertion is:\n"; 
    	t.traversal();
	cout<<"Enter the key to be deleted"<<endl;
	cin>>k;
	t.deletion(k);
	cout<<"Traversal of tree after deletion is"<<endl;
	t.traversal();
	return 0;

}
