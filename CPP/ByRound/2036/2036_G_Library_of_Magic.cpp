/*
 * Problem URL : https://codeforces.com/contest/2036/problem/G
 * Submit Date : 2025-09-05
 */

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,sum,pre,x,ans;
bool one;
signed _main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);cout.tie(0);
	cin>>n;
	cout<<"xor "<<1<<' '<<n<<endl;
	cin>>sum;
	for(int i=__lg(n);i>=0;--i){
		int l=(1ll<<i),r=(1ll<<(i+1))-1;
		l^=pre,r^=pre;
		r=min(n,r);
		if(l>n) continue;
		cout<<"xor "<<l<<' '<<r<<endl;
		cin>>x;
		if(x!=sum&&x!=0){
			if(one){
				cout<<"ans "<<ans<<' '<<x<<' '<<(sum^x)<<endl;
				return 0;
			}
//			if(!sum) sum=ans=x,one=1;
//			else{
				int t=x^ans;
				bool p=l<=x&&x<=r;
				bool q=l<=t&&t<=r;
				if(p&&q){
					cout<<"xor "<<x<<' '<<x<<endl;
					int tt;cin>>tt;
					p=(tt==x);
				}
				if(p) ans=x,sum^=x;
				else{
					ans=(sum^x),sum=x;
					pre^=(1ll<<i);
				}
				one=1;
//			}
		}else if(sum&&x==sum) pre^=(1ll<<i);
	}
	return 0;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		ans=pre=0;
		one=0;
		_main();
	}
}