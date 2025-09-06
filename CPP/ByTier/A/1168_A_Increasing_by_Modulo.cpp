/*
 * Problem URL : https://codeforces.com/contest/1168/problem/A
 * Submit Date : 2025-09-02
 */

//jiudge: 6145: 1648467754
#include<bits/stdc++.h>

int k,n,m;

const int N = 300005;

int a[N];

bool check(int x)
{
	int res = 0;
	int pre = 0;
	for(int i=1;i<=n;++i){
		if(a[i]<pre){
			if(pre-a[i]>x){
				return false;
			}
		}else if(a[i]>pre){
			if(m-a[i]+pre>x){
				pre = a[i];
			}
		}
	}
	return true;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
	}
	
	int l=0,r=m-1,ans ;
	while(l<=r){
		int mid = (l+r)>>1;
		if(check(mid)){
			r = mid-1;
			ans = mid;
		}else{
			l = mid+1;
		}
	}
	
	printf("%d",ans);
	return 0;
}