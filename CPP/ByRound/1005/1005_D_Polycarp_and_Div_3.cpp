/*
 * Problem URL : https://codeforces.com/contest/1005/problem/D
 * Submit Date : 2025-08-31
 */

#include<cstdio>
int n,d,a,b;
char m;
int main()
{
	while((m=getchar())!='\n')
	{
		n=m-48;
		if(n%3==0||(n+a)%3==0||(n+a+b)%3==0)
			d++,a=b=0;
		else
			b=a,a=n;
	}
	printf("%d",d);
}