// Problem: CF 1107 B - Digital root
// https://codeforces.com/contest/1107/problem/B

/*
B. Digital root
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
Today at the lesson of mathematics, Petya learns about the digital root.
The digital root of a non-negative integer is the single digit value obtained by an iterative process of summing digits, on each iteration using the result from the previous iteration to compute a digit sum. The process continues until a single-digit number is reached. 
Let's denote the digital root of $$$x$$$ as $$$S(x)$$$. Then $$$S(5)=5$$$, $$$S(38)=S(3+8=11)=S(1+1=2)=2$$$, $$$S(10)=S(1+0=1)=1$$$.
As a homework Petya got $$$n$$$ tasks of the form: find $$$k$$$-th positive number whose digital root is $$$x$$$.
Petya has already solved all the problems, but he doesn't know if it's right. Your task is to solve all $$$n$$$ tasks from Petya's homework.

Algorithms/Techniques: Pattern recognition and mathematical formula
Time complexity: O(n), where n is the number of test cases
Space complexity: O(1)

The pattern for numbers with a specific digital root x is:
- For digital root 1: 1, 10, 19, 28, ...
- For digital root 2: 2, 11, 20, 29, ...
- And so on...

Each sequence can be represented as an arithmetic progression. 
The k-th number in the sequence with digital root x is:
9 * (k - 1) + x
*/
#include <cstdio>
typedef long long ll;
int main() {
  long n; // Read number of test cases
  scanf("%ld", &n);
  while (n--) {
    ll k, x; // k is the position in sequence, x is the target digital root
    scanf("%lld %lld", &k, &x);
    printf("%lld\n", 9 * (k - 1) + x); // Calculate and print the k-th number with digital root x
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/