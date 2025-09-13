/*
 * Problem URL : https://codeforces.com/contest/1987/problem/H
 * Submit Date : 2025-09-11
 */

#include"bits/stdc++.h"
using namespace std;
map<pair<int,int>,int>mp;
int qry(int x,int y)
{
    if(mp.count({x,y}))return mp[{x,y}];
    int ans;
    cout<<"? "<<x<<" "<<y<<endl;
    cin>>ans;
    mp[{x,y}]=ans;
    return ans;
}
int a[5005][5005];
int ax,ay;
int num=0;
int qry2(int x,int y)
{
    int lx=ax,rx=x,ly=ay,ry=y;
    if(lx==rx&&ly==ry)return 0;
    if(lx>rx)swap(lx,rx);
    if(ly>ry)swap(ly,ry);num++;
    return ry+rx-ly-lx+abs(a[rx][ry]-a[lx-1][ry]-a[rx][ly-1]+a[lx-1][ly-1]);
}
int main()
{
    srand(time(0));
    int t;
    cin>>t;
    while(t--)
    {
        int n,m;mp.clear();
        cin>>n>>m;/*
        num=0;
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=1;
        ax=rand()%n+1;ay=rand()%m+1;
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]+=a[i-1][j];
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]+=a[i][j-1];*/
        int nowx=rand()%n+1,nowy=rand()%m+1;
        int ans=qry(nowx,nowy);
        while(ans>0)
        {
            int dx=ans,dy=ans;
            if(rand()%2)dx/=2;
            else if(rand()%2)dy/=2;
            if(rand()%5==0)
            {
                if(rand()%2)dx=sqrt(dx);
                else dx=sqrt(dx+100);
            }
            else if(rand()%5==0)
            {
                if(rand()%2)dy=sqrt(dy);
                else dy=sqrt(dy+100);
            }
            int lx=nowx-dx,rx=nowx+dx,ly=nowy-dy,ry=nowy+dy;
            if(lx<=1)lx=1;if(ly<=1)ly=1;if(rx>=n)rx=n;if(ry>=m)ry=m;
            int nx=rand()%(rx-lx+1)+lx;
            int ny=rand()%(ry-ly+1)+ly;
            int c=qry(nx,ny);
            if(c<=ans)
            {
                ans=c;
                nowx=nx;
                nowy=ny;
            }
        }//cout<<"!!"<<num<<endl;
        cout<<"! "<<nowx<<" "<<nowy<<endl;
    }
    return 0;
}
