/*
 * Problem URL : https://codeforces.com/contest/1281/problem/A
 * Submit Date : 2025-08-27
 */

#import<ios>
char a[1001];
int i;
main()
{
    for(gets(a);gets(a);i=0)
        while(a[i+1]?++i:puts(a[i]<98?"KOREAN":a[i]>'o'?"JAPANESE":"FILIPINO"));
}
