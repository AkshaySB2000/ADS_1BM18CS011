#include<bits/stdc++.h>
using namespace std;
void uniquedigit(int l, int r) {
	for(int i = l; i <= r; i++) {
		int num = i;
		bool digit[10] = {false};
		while(num) {
			if(digit[num%10])
				break;
			digit[num%10] = true;
			num = num/10;
		}
		if (num == 0)
			cout<<i<<" ";
	}
	cout<<endl;
}
int main() {
	int l, r;
	cout<<"L = ";
	cin>>l;
	cout<<"R = ";
	cin>>r;
	cout<<"Output: \n";
	uniquedigit(l,r);
	return 0;
}

