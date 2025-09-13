/*
 * Problem URL : https://codeforces.com/contest/2013/problem/E
 * Submit Date : 2025-09-12
 */

#include<algorithm>
#include<iostream>
#include<numeric>
int a[100001];
int main()
{
	std::cin.tie(0)->sync_with_stdio(0);
	int t;
	std::cin>>t;
	while(t--)
	{
		int n,ga=0;
		std::cin>>n;
		for(int i=0;i<n;i++)
			std::cin>>a[i],ga=std::gcd(ga,a[i]);
		long long ans=0;
		int g=0;
		for(int i=0;i<n;i++)
		{
			int x=1e9;
			for(int j=0;j<n;j++)
				x=std::min(x,std::gcd(g,a[j]));
			ans+=g=x;
			if(g==ga)
			{
				ans+=(n-i-1ll)*g;
				break;
			}
		}
		std::cout<<ans<<'\n';
	}
	return 0;
}
