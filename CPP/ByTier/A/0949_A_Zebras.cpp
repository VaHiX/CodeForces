/*
 * Problem URL : https://codeforces.com/contest/949/problem/A
 * Submit Date : 2025-09-04
 */

    #include <cstdio>
    #include <vector>
    using namespace std;
    int i,j,b,m,w;
    char s[200200];
    vector <int> v[200001];
     
    int main()
    {
    	for(scanf("%s",s+1),m=b=0,w=i=1;w&&s[i];++i)
    		s[i]=='0'?(v[b++].push_back(i),1):(--b<0?w--:(v[b].push_back(i),1)),m<b&&(m=b);
    	if(w&&m==b)
    		for(printf("%d\n",m),i=0;v[i].size();puts(""),++i)
    			for(printf("%d",v[i].size()),j=0;j!=v[i].size();++j)
    				printf(" %d", v[i][j]);
    	else
    		puts("-1");
    }