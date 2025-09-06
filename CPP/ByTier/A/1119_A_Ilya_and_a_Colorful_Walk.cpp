/*
 * Problem URL : https://codeforces.com/contest/1119/problem/A
 * Submit Date : 2025-08-29
 */

#include<stdio.h>
int n,a[300000],i,j;
int main(){
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",a+i);
		if(a[i]!=a[0])j=i;
	}
	for(i=0;i<n;i++)if(a[i]!=a[n-1])break;
	if(j>n-i-1)printf("%d\n",j);
	else printf("%d\n",n-i-1);
}