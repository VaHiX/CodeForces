/*
 * Problem URL : https://codeforces.com/contest/380/problem/A
 * Submit Date : 2025-09-06
 */

#include <stdio.h>

#include <string.h>

#include <algorithm>

#include <map>

#include <string>

#include <math.h>

#include <queue>

#include <stack>

#include <iostream>

using namespace std;

#define LL long long

#define mod 1000000007

typedef struct Res

{

  int op;

  int x, y;

  LL l, r;

} Res;

Res s[200005];

int Gao(int p, LL x)

{

  int l, r, m;

  if (s[p].op == 1)

    return s[p].x;

  else

  {

    r = x - s[p].l + 1;

    x = (r - 1) % s[p].x + 1;

    l = 1, r = p - 1;

    while (l < r)

    {

      m = (l + r + 1) / 2;

      if (x < s[m].l)

        r = m - 1;

      else

        l = m;
    }

    return Gao(r, x);
  }
}

int main(void)

{

  LL now, p;

  int m, n, i, R;

  scanf("%d", &m);

  for (i = 1; i <= m; i++)

  {

    scanf("%d", &s[i].op);

    if (s[i].op == 1)

      scanf("%d", &s[i].x);

    else

      scanf("%d%d", &s[i].x, &s[i].y);
  }

  R = now = 0;

  scanf("%d", &n);

  for (i = 1; i <= n; i++)

  {

    scanf("%lld", &p);

    while (R != m && p > now)

    {

      R++;

      s[R].l = now + 1;

      if (s[R].op == 1)

        s[R].r = s[R].l;

      else

        s[R].r = s[R].x * s[R].y + now;

      now = s[R].r;
    }

    printf("%d ", Gao(R, p));
  }

  puts("");

  return 0;
}