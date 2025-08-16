/*
 * Problem URL : https://codeforces.com/problemset/problem/690/B1
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
#define fast_cin() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
using namespace std;
// long long int n,m,k,flag=0,sz=0,op[51][51],dx[]={0,0,0,1},dtm[]={1,0,0,0};
// string s[51];
// vector<pair<long long int,pair<long long int,long long int>>>vv;
// void dfschng(long long int x,long long int y)
// {
//  if(x<0 || y<0 || x>=n || y>=m)
//  {
//   return;
//  }
//  if(op[x][y] || s[x][y]=='*')
//  {
//   return;
//  }
//  //cout<<x<<" "<<y<<"\n";
//  op[x][y]=1;s[x][y]='*';
//  for(long long int i=0;i<4;i++)
//  {
//   long long int xx=x+dx[i],yy=y+dtm[i];
//   dfschng(xx,yy);
//  }
// }
// void dfs(long long int x,long long int y)
// {
//  if(x<0 || y<0 || x>=n || y>=m)
//  {
//   return;
//  }
//  if(op[x][y] || s[x][y]=='*')
//  {
//   return;
//  }
//  op[x][y]=1;sz++;
//  if(x==0 || y==0 || x==(n0) || y==(m0))
//  {
//   flag=1;
//  }
//  for(long long int i=0;i<4;i++)
//  {
//   long long int xx=x+dx[i],yy=y+dtm[i];
//   dfs(xx,yy);
//  }
// }
// long long int n;
//  cin>>n;
//  for(long long int i=1;i<=n;i+=2)
//  {
//   cout<<i<<" ";
//  }
//  for(long long int i=n-(n&1);i>=1;i-=2)
//  {
//   cout<<i<<" ";
//  }
//  cout<<"\n";
// struct coord
// {
//  long long int x=0,y=0;
// };
void solve()
{
 long long int n,cnt=0;
 cin>>n;
 vector<string>vs(n+2);
 string op="Yes";
 long long int dx[]={1,1,-1,-1},dy[]={1,-1,1,-1};
 for(long long int i=1;i<=n;i++)
 {
  cin>>vs[i];
  vs[i]=" "+vs[i];
 }
 for(long long int i=1;i<=n;i++)
 {
  for(long long int j=1;j<=n;j++)
  {
   if(vs[i][j]-'0')
   {
    cnt=0;
    for(long long int k=0;k<4;k++)
    {
     cnt+=(vs[i+dx[k]][j+dy[k]]-'0'>0);
    }
    if(cnt!=vs[i][j]-'0')
    {
     op="No";
     cout<<op;return;
    }
   }
  }
 }
 cout<<op;
}
int main()
{
    fast_cin();
    long long int t;
    //cin>>t;
    t=1;
    while(t--)
    {
     solve();
    }
   return 0;
}