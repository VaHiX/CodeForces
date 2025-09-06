/*
 * Problem URL : https://codeforces.com/contest/1042/problem/C
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;

int a[200010];
int main(){
	int n,f=0,p=0,x=0,y=0;
	a[0]=-1e9;
	cin>>n;
	for(int i=1;i<=n;i++)
	   scanf("%d",&a[i]),f^=a[i]<0,a[i]<0&&a[i]>=a[p]? p=i:p;
	if(f) a[p]=0;
	for(int i=1;i<=n;i++){
		if(!a[i]){
			if(x)
				printf("%d %d %d\n",1,x,i);
			x=i;
		}
		else{
			if(y)
			    printf("%d %d %d\n",1,y,i);
			y=i;
		}
	}
	if(x&&y) cout<<2<<" "<<x;
}