/*
 * Problem URL : https://codeforces.com/contest/1352/problem/A
 * Submit Date : 2025-08-27
 */

#include<stdio.h>
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		int n,arr[6],k=0,p=1,i;
		scanf("%d",&n);
		for(;n>0;p*=10,n/=10)
			if((arr[k]=(n%10)*p)>0)
                k++;
		printf("%d\n",k);
		for(i=0;i<k;i++)
            printf("%d ",arr[i]);
	}
}