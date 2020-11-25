#include<bits/stdc++.h>
using namespace std;
const int MAX = 200;
class Hashnode {
   	public:
      		int key;
      		int value;
      		Hashnode(int key, int value) {
         		this->key= key;
         		this->value = value;
      		}
};
class Dictionary {
   	private:
      		Hashnode **t;
   	public:
      		Dictionary() {
         		t = new Hashnode * [MAX];
         		for (int i = 0; i< MAX; i++) {
            		t[i] = NULL;
         	}
      	}
      	~Dictionary() {
         	for (int i = 0; i < MAX; i++) {
            		if (t[i] != NULL)
               		delete t[i];
               		delete[] t;
         	}
      	}
      	int hashfunc(int key);
      	void insertion(int key, int value);
      	int search(int key);
      	void deletion(int key);
};
int Dictionary::hashfunc(int key) {
      	return key % MAX;
}
void Dictionary::insertion(int key, int value) {
	int h = hashfunc(key);
	while (t[h] != NULL && t[h]->key != key) {
            	h = hashfunc(h + 1);
	}
        if (t[h] != NULL)
            	delete t[h];
        t[h] = new Hashnode(key, value);
}
int Dictionary::search(int key) {
        int h = hashfunc(key);
        while (t[h] != NULL && t[h]->key != key) {
            	h = hashfunc(h + 1);
        }
        if (t[h] == NULL)
            	return -1;
        else
            	return t[h]->value;
}
void Dictionary::deletion(int key) {
        int h = hashfunc(key);
        while (t[h] != NULL) {
            	if (t[h]->key == key)
               	break;
            	h = hashfunc(h + 1);
        }
        if (t[h] == NULL) {
            	cout<<"No element at key "<<key<<endl;
            	return;
        } else {
            	delete t[h];
        }
        cout<<"Element has been deleted"<<endl;
} 
int main() {
   	Dictionary dic;
   	int key, value;
   	int ch;
   	while(1) {
      		cout<<"\nEnter\n1. Insertion to dictionary\n2. Search in dictionary using key\n3. Delete from dictionary\n4. Exit\n";
      		cin>>ch;
      		switch(ch) {
         		case 1: cout<<"\nEnter element to be inserted: ";
            	  		cin>>value;
            			cout<<"Enter the key at which element is to be inserted: ";
            			cin>>key;
            			dic.insertion(key, value);
         			break;
         		case 2: cout<<"\nEnter key of the element to be searched: ";
            			cin>>key;
            			if(dic.search(key) == -1) {
               			cout<<"No element found at key "<<key<<endl;
               			continue;
            			} else {
               			cout<<"Element at key "<<key<<" : ";
               			cout<<dic.search(key)<<endl;
            			}
         			break;
         		case 3: cout<<"\nEnter key of the element to be deleted: ";
            			cin>>key;
            			dic.deletion(key);
         			break;
         		case 4: exit(1);
         		default: cout<<"\nInvalid Choice!\n";
      		}
   	}
   	return 0;
}

