/*
 * Problem URL : https://codeforces.com/contest/926/problem/A
 * Submit Date : 2025-09-04
 */


#include<iostream>
using namespace std;
long long l,r,t,a,b;
int main()
{
	cin>>l>>r;
	for(a=1;a<=r;a*=2)
	{
		for(b=1;b<=r;b*=3) 
			if(l<=a*b && a*b<=r)
			    t++;
	}
	cout << t;
}