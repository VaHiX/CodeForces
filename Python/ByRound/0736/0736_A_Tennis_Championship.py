# Problem: CF 736 A - Tennis Championship
# https://codeforces.com/contest/736/problem/A

"""
Algorithm: Fibonacci Sequence Approach
This problem is solved using the Fibonacci sequence properties. The key insight is that in a valid knockout tournament where players can only play against others whose number of games played differs by at most one, the maximum number of games the winner can play corresponds to a specific index in the Fibonacci sequence.

The Fibonacci sequence is built such that each term is the sum of the two preceding terms:
F(0) = 1, F(1) = 1, F(n) = F(n-1) + F(n-2)

For n players, the maximum number of games the winner can play is determined by finding the largest Fibonacci number less than or equal to n, and returning the index of that Fibonacci number minus 1.

Time Complexity: O(log n) - The loop to build the Fibonacci sequence takes log n steps since Fibonacci numbers grow exponentially.
Space Complexity: O(log n) - The space used to store the Fibonacci sequence up to 10^18.
"""

fib = [1, 1]
while fib[-1] <= 10**18:
    a, b = fib[-2], fib[-1]
    fib.append(a + b)


def process(n):
    for i in range(len(fib) - 1):
        if fib[i] <= n < fib[i + 1]:
            return i - 1


n = int(input())
print(process(n))


# https://github.com/VaHiX/CodeForces/