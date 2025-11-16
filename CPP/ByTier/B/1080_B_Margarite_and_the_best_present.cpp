// Problem: CF 1080 B - Margarite and the best present
// https://codeforces.com/contest/1080/problem/B

#include <cstdio>
typedef long long ll;
int main() {
  ll q;
  scanf("%lld", &q);
  while (q--) {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    ll res(0);
    ll n = b - a + 1; // Length of the range [a, b]
    if (n % 2) { // If the number of elements is odd
      res += (b % 2) ? (-b) : b; // Add the last element's value depending on whether it's odd or even
    }
    res += (a % 2 ? 1 : -1) * (n / 2); // Add contribution from pairs of elements
    printf("%lld\n", res);
  }
  return 0;
}
/*
B. Margarite and the best present
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
Little girl Margarita is a big fan of competitive programming. She especially loves problems about arrays and queries on them.
Recently, she was presented with an array $$$a$$$ of the size of $$$10^9$$$ elements that is filled as follows: 
 
 $$$a_1 = -1$$$ 
 $$$a_2 = 2$$$ 
 $$$a_3 = -3$$$ 
 $$$a_4 = 4$$$ 
 $$$a_5 = -5$$$ 
 And so on ... 
That is, the value of the $$$i$$$-th element of the array $$$a$$$ is calculated using the formula $$$a_i = i \cdot (-1)^i$$$.
She immediately came up with $$$q$$$ queries on this array. Each query is described with two numbers: $$$l$$$ and $$$r$$$. The answer to a query is the sum of all the elements of the array at positions from $$$l$$$ to $$$r$$$ inclusive.
Margarita really wants to know the answer to each of the requests. She doesn't want to count all this manually, but unfortunately, she couldn't write the program that solves the problem either. She has turned to you — the best programmer.
Help her find the answers!
Input
The first line contains a single integer $$$q$$$ ($$$1 \le q \le 10^3$$$) — the number of the queries.
Each of the next $$$q$$$ lines contains two integers $$$l$$$ and $$$r$$$ ($$$1 \le l \le r \le 10^9$$$) — the descriptions of the queries.
Output
Print $$$q$$$ lines, each containing one number — the answer to the query. 
Example
Input

5
1 3
2 5
5 5
4 4
2 3

Output

-2
-2
-5
4
-1

Note
In the first query, you need to find the sum of the elements of the array from position $$$1$$$ to position $$$3$$$. The sum is equal to $$$a_1 + a_2 + a_3 = -1 + 2 -3 = -2$$$.
In the second query, you need to find the sum of the elements of the array from position $$$2$$$ to position $$$5$$$. The sum is equal to $$$a_2 + a_3 + a_4 + a_5 = 2 -3 + 4 - 5 = -2$$$.
In the third query, you need to find the sum of the elements of the array from position $$$5$$$ to position $$$5$$$. The sum is equal to $$$a_5 = -5$$$.
In the fourth query, you need to find the sum of the elements of the array from position $$$4$$$ to position $$$4$$$. The sum is equal to $$$a_4 = 4$$$.
In the fifth query, you need to find the sum of the elements of the array from position $$$2$$$ to position $$$3$$$. The sum is equal to $$$a_2 + a_3 = 2 - 3 = -1$$$.

Algorithms/Techniques: Mathematical pattern recognition, optimized range sum calculation
Time Complexity: O(q), where q is the number of queries
Space Complexity: O(1)
*/

// https://github.com/VaHiX/codeForces/