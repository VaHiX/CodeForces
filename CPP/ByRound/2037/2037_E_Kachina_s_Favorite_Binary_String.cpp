/*
 * Problem URL : https://codeforces.com/contest/2037/problem/E
 * Submit Date : 2025-09-05
 */

#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,cnt=0,z=0;
		cin>>n;
		string ans;
		for(int i=2,x;i<=n;i++){
			printf("? 1 %d\n",i);
			fflush(stdout);
			scanf("%d",&x);
			if(cnt==0){
				if(x==0) continue;
				for(int j=1;j<i-x;j++) ans+='1';
				for(int j=1;j<=x;j++) ans+='0';
				ans+='1';
				z=x;
			}
			else {
				int val=x-cnt;
				if(val==0){
					ans+='0';z++;
				}
				else if(val==z){
					ans+='1';
				}
				else break;
			}
			cnt=x;
		}
		if(ans.length()!=n){
			printf("! IMPOSSIBLE\n");
		}
		else cout<<"! "<<ans<<endl;
		fflush(stdout);
	}
}