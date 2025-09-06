/*
 * Problem URL : https://codeforces.com/contest/1299/problem/A
 * Submit Date : 2025-09-02
 */

#include <stdio.h>
int a[100010];
int main(){
	int n,i,j,cnt,k,t;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	for(j=30;j>=0;j--){
		cnt=0;
		for(i=1;i<=n;i++)
			if((a[i]>>j)&1)cnt++,k=i;
		if(cnt==1)break;
	}
	if(cnt==1)t=a[1],a[1]=a[k],a[k]=t;
	printf("%d",a[1]);
	for(i=2;i<=n;i++)printf(" %d",a[i]);
	printf("\n");
}