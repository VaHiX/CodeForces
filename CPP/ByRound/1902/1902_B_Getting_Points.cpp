// Problem: CF 1902 B - Getting Points
// https://codeforces.com/contest/1902/problem/B

/*
B. Getting Points
time limit per test1 second
memory limit per test256 megabytes

Monocarp is a student at Berland State University. Due to recent changes in the Berland education system, Monocarp has to study only one subject — programming.
The academic term consists of n days, and in order not to get expelled, Monocarp has to earn at least P points during those n days. There are two ways to earn points — completing practical tasks and attending lessons. For each practical task Monocarp fulfills, he earns t points, and for each lesson he attends, he earns l points.
Practical tasks are unlocked "each week" as the term goes on: the first task is unlocked on day 1 (and can be completed on any day from 1 to n), the second task is unlocked on day 8 (and can be completed on any day from 8 to n), the third task is unlocked on day 15, and so on.
Every day from 1 to n, there is a lesson which can be attended by Monocarp. And every day, Monocarp chooses whether to study or to rest the whole day. When Monocarp decides to study, he attends a lesson and can complete no more than 2 tasks, which are already unlocked and not completed yet. If Monocarp rests the whole day, he skips a lesson and ignores tasks.
Monocarp wants to have as many days off as possible, i. e. he wants to maximize the number of days he rests. Help him calculate the maximum number of days he can rest!

Algorithm: Binary search on the number of days Monocarp can rest.
We want to maximize the number of rest days = n - (number of study days)
Let x be the number of study days.
Then number of points that can be earned from x study days is limited by:
  - Each study day allows 1 lesson and up to 2 tasks
  - Total points = (x * l) + (at most 2 * number of tasks completed * t)
  - Number of tasks that could be unlocked in x days: (x + 6) / 7
  - So maximum points from x study days: x * l + 2 * (x+6)/7 * t

Time Complexity: O(log n) per test case due to binary search over number of rest days.
Space Complexity: O(1) — only using a constant amount of extra space.

*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, P, l, s;
    scanf("%lld %lld %lld %lld", &n, &P, &l, &s);
    
    // ns stores number of tasks that can be unlocked in n days
    ll ns = (n + 6) / 7;
    
    // a: minimum number of study days needed if we complete tasks optimally
    // b: minimum number of study days needed if we attend lessons optimally
    
    ll a = (P + l + 2 * s - 1) / (l + 2 * s); // number of days using both lesson + task points, rounded up
    ll b = (P - s * ns + l - 1) / l;          // number of days if we only use lesson points
    
    // Choose the maximum of a and b to get minimum required study days
    ll res = n - (a > b ? a : b);
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/