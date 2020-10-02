#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define MAX_LEVEL 3
const float P = 0.5;
using namespace std;
struct node {
	int data;
	node **forw;
    	node(int level, int &data) {
        	forw = new node * [level + 1];
        	memset(forw, 0, sizeof(node*) * (level + 1));
        	this->data = data; 
    	}
    	~node() {
        	delete [] forw;        
    	}	 
};
struct skiplist {
	node *head;
    	int data;
    	int level;
    	skiplist() {
        	head = new node(MAX_LEVEL, data);
        	level = 0;
    	}
    	~skiplist() {
        	delete head;
    	}
	void displaylist();
    	bool searchlist(int &);
    	void insertlist(int &);
    	void deletelist(int &);        
};
float frand() {
	return (float) rand() / RAND_MAX;
}
int randomlevel() {
	static bool first = true;
    	if (first) {
        	srand((unsigned)time(NULL));
        	first = false;
    	}
    	int lvl = (int) (log(frand()) / log(1.-P));
    	return lvl < MAX_LEVEL ? lvl : MAX_LEVEL;
}
void skiplist::insertlist(int &data) {
    	node *x = head;	
    	node *update[MAX_LEVEL + 1];
    	memset(update, 0, sizeof(node*) * (MAX_LEVEL + 1));
    	for (int i = level;i >= 0;i--) {
        	while (x->forw[i] != NULL && x->forw[i]->data < data) {
        		x = x->forw[i];
        	}
        	update[i] = x; 
    	}
    	x = x -> forw[0];
    	if (x == NULL || x->data != data) {        
        	int lvl = randomlevel();
        	if (lvl > level) {
        		for (int i = level + 1;i <= lvl;i++) {
                		update[i] = head;
            		}
            		level = lvl;
        	}
        	x = new node(lvl, data);
        	for (int i = 0;i <= lvl;i++) {
            		x->forw[i] = update[i]->forw[i];
            		update[i] -> forw[i] = x;
        	}
    	}
}
void skiplist::deletelist(int &data) {
    	node *x = head;	
    	node *update[MAX_LEVEL + 1];
    	memset(update, 0, sizeof(node*) * (MAX_LEVEL + 1));
    	for (int i = level;i >= 0;i--) {
        	while (x -> forw[i] != NULL && x -> forw[i]->data < data) {
            		x = x -> forw[i];
        	}
        	update[i] = x; 
    	}
    	x = x->forw[0];
    	if (x->data == data) {
        	for (int i = 0;i <= level;i++) {
        		if (update[i] -> forw[i] != x) 
        			break;
            	update[i] -> forw[i] = x -> forw[i];
        	}
        	delete x;
        	while (level > 0 && head -> forw[level] == NULL) {
            		level--;
        	}
    	}
}
void skiplist::displaylist() { 
    	for (int i = 0;i <= level; i++) { 
        	node *x = head->forw[i]; 
        	cout<<"Level "<<i<<": "; 
        	while (x != NULL) { 
            		cout << x->data<<" "; 
            		x = x->forw[i]; 
        	} 
        	cout<<endl; 
    	} 
}; 
bool skiplist::searchlist(int &sdata) {
    	node *x = head;
    	for (int i = level;i >= 0;i--) {
        	while (x->forw[i] != NULL && x->forw[i]->data < sdata) {
            	x = x->forw[i];
        	}
    	}
    	x = x -> forw[0];
    	return x != NULL && x->data == sdata;
}
int main() {
    	skiplist sl;
    	int choice, item;
    	while(1) {
         	cout << "Enter your choice\n1 to insert element\n2 to search element\n3 to delete element \n4 to diplay elements\n5 to exit\n";
        	cin >> choice;
        	switch(choice) {
        		case 1: cout <<"\nEnter the element to be inserted: ";
             			cin >> item;
             			sl.insertlist(item);
             			break;
              		case 2: cout << "Enter the element to be searched: ";
             			cin >> item; 
             			if(sl.searchlist(item)) 
             				cout << "\nElement " << item << " is in the list\n" << endl;
             			else 
             				cout << "\nElement " << item << " not found\n" << endl;
             			break;
        		case 3: cout << "\nEnter the element to be deleted: ";
             			cin >> item;
             			if(!sl.searchlist(item)) {
                 			cout << "\nElement not found\n" << endl;
                 			break;
             			}
             			sl.deletelist(item);
             			break;
        		case 4: cout << "\nThe skip list is as follows\n";
             			sl.displaylist();
             			break;
        		case 5: exit(1);
                		break;
        		default: cout << "\nInvalid choice!\n" << endl;
        	}
        	cout<<endl;
    	}
    	return 0;
}
 


