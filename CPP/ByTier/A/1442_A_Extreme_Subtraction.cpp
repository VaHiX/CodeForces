/*
 * Problem URL : https://codeforces.com/contest/1442/problem/A
 * Submit Date : 2025-09-01
 */

#include<bits/stdc++.h>
using namespace std;
int t,n,a,m,k,f;
int main() {
    for(scanf("%d",&t); t--; printf(f?"NO\n":"YES\n"),k=f=0)
        for(m=2e6,scanf("%d",&n); n--; scanf("%d",&a),
                f|=(a-=k)<0,a<m?m=a:0,k+=a-=m);
    exit(0);
}