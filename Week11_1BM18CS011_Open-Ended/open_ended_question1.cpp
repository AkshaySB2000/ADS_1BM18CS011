#include<bits/stdc++.h>
using namespace std;
void twogreatest(int arr[], int n) {
	sort(arr, arr+n);
	for(int i = 0; i < n-2; i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}
int main() {
	int t, n;
	cin>>t;
	for(int i = 0; i < t; i++) {
		cin>>n;
		int arr[n];
		for(int j = 0; j < n; j++)
			cin>>arr[j];
		cout<<"Output: ";
		twogreatest(arr,n);
	}
	return 0;
}
