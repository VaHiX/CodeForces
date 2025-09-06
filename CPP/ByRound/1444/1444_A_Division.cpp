/*
 * Problem URL : https://codeforces.com/contest/1444/problem/A
 * Submit Date : 2025-09-01
 */

#include <bits/stdc++.h>
using namespace std;

int64_t t,A,B,a,b,x,i;

main()
{
cin>>t; while (t--)
{
cin>>A>>B;

set<int64_t> p;
b=B;
for (i=2; i*i<=b; ++i)
{
while (b%i==0) b/=i, p.insert(i);
}
if (b>1) p.insert(b);

x=1;
for (auto i: p)
{
a=A;
while (a%B==0) a/=i;
x=max(x,a);
}

cout<<x<<"\n";
}
}