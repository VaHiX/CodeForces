/*
 * Problem URL : https://codeforces.com/problemset/problem/609/E
 * Submit Date : 2025-08-16
 */

#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 212345
typedef long long ll;

int con[MAX],par[MAX], sz[MAX], add[MAX];
ll mst=0, ret[MAX];

struct E{
    int u, v, w, id;
}e[MAX];

bool cmp(E a, E b){
    return a.w<b.w;
}

int get(int u, int v, int w){
    int maxi=0;
    while((par[u]!=u || par[v]!=v) && u!=v){
        if(par[u] == u || (par[v] != v && sz[v]<=sz[u])){
            maxi = max(maxi, con[v]);
            v = par[v];
        }
        else {
            maxi = max(maxi, con[u]);
            u = par[u];
        }
    }
    if(u==v) return w-maxi;
    if(sz[u]<sz[v])swap(u,v);
    sz[u]+=sz[v];
    par[v]=u;
    con[v]=w;
    mst+=w;
    return 0;
}

int main(){
    int u, v, w, n, m, i;
    scanf("%d %d", &n, &m);
    for(i=0; i<m; i++){
        scanf("%d %d %d", &u, &v, &w);
        e[i].u = u;
        e[i].v = v;
        e[i].w = w;
        e[i].id = i;
    }
    sort(e, e+m, cmp);

    for(i=1; i<=n; i++){
        par[i] = i;
        sz[i] = 1;
    }

    for(i=0; i<m; i++)
        add[e[i].id] = get(e[i].u,e[i].v,e[i].w);

    for(i=0; i<m; i++)
        printf("%lld\n", mst+add[i]);

    return 0;
}
