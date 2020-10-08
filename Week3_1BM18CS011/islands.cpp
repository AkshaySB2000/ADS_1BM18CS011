#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
#include<vector>
using namespace std;
class Islands {
	int parent[100];
	public: 
		int count;
		Islands(int n) {
			for(int i = 0; i < n; i++)
			parent[i] = i;
			count = 0;
		}
		int findparent(int x) {
			if(parent[x] == x) 
				return x;
			else
				return parent[x] = findparent(parent[x]);
		}
		void makeunion(int x, int y) {
			int xroot = findparent(x);
			int yroot = findparent(y);
			if(xroot != yroot) {
				parent[xroot] = yroot;
				count--;
			}
		}
		void countset(int n) {
			count = n;
		}
		int returncount() {
			return count;
		}
};
int noofislands(vector<vector<int>>matrix) {
	int count = 0;
	int a = matrix.size();
	int b = matrix[0].size();
	int prd;
	for(int i = 0; i < a; i++) {
		for(int j = 0; j < b; j++) {
			if(matrix[i][j] != 0)
				count++;
		}
	}
	prd = a*b;
	Islands il(prd);
	il.countset(count);
	for(int i = 0; i < a; i++) {
		for(int j = 0; j < b; j++) {
			if(matrix[i][j] != 0) {
				if(i > 0 && matrix[i-1][j] != 0) 
					il.makeunion(b*i+j, b*(i-1)+j);
				if(i < a-1 && matrix[i+1][j] != 0) 
					il.makeunion(b*i+j, b*(i+1)+j);
				if(j > 0 && matrix[i][j-1] != 0) 
					il.makeunion(b*i+j, b*i+(j-1));
				if(j < b-1 && matrix[i][j+1] != 0) 
					il.makeunion(b*i+j, b*i+(j+1));
				if(i > 0 && j > 0 && matrix[i-1][j-1] != 0) 
					il.makeunion(b*i+j, b*(i-1)+(j-1));
				if(i > 0 && j < b-1 && matrix[i-1][j+1] != 0) 
					il.makeunion(b*i+j, b*(i-1)+(j+1));
				if(i < a-1 && j > 0 && matrix[i+1][j-1] != 0) 
					il.makeunion(b*i+j, b*(i+1)+(j-1));
				if(i < a-1 && j < b-1 && matrix[i+1][j+1] != 0) 
					il.makeunion(b*i+j, b*(i+1)+(j+1));
			}
		}
	}
	return il.count;
}
int main() {
	int k,m,n,res;
	vector<vector<int>>matrix;
	cout<<"Enter the number of rows and columns\n";
	cin>>m>>n;
	cout<<"Enter 0 or 1 for each position in the matrix\n";
	for(int i = 0; i < m; i++) {
		vector<int>m1;
		for(int j = 0; j < n; j++) {
			cin>>k;
			m1.push_back(k);
		}
		matrix.push_back(m1);
	}
	res = noofislands(matrix);
	cout<<"\nThe number of islands in the entered matrix = "<<res<<endl;
	return 0;
}
	
				
