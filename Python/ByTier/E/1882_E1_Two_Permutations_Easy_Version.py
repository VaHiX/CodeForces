# Problem: CF 1882 E1 - Two Permutations (Easy Version)
# https://codeforces.com/contest/1882/problem/E1

"""
Algorithm: Two Permutations (Easy Version)
Purpose: Transform two permutations into sorted order using specific operations.
Approach:
1. Process each permutation from left to right, bringing the next expected element to the front.
2. For each step, determine which index to use for the operation (i for p, j for q).
3. Apply the operation and update the permutations accordingly.
4. Handle edge cases where both permutations are already sorted.
5. If final state is not correct, check for parity conditions for possible solution.

Time Complexity: O(n^2 + m^2) - due to nested loops and index searching
Space Complexity: O(n + m) - for storing permutations and answer list
"""

from sys import stdin


def line():
    return stdin.readline().strip()


def rd(converter=int):
    return converter(line())


def rl(converter=int, delimeter=None):
    return list(map(converter, line().split(delimeter)))


def rls(num_lines, converter=int):
    return [rd(converter) for i in range(num_lines)]


def rg(num_lines, converter=int, delimeter=None):
    return [rl(converter, delimeter) for i in range(num_lines)]


MULTIPLE_CASES = 0


def main():
    n, m = rl()
    a_ = rl()
    b_ = rl()

    ans = []
    an, bn = 1, 1

    # Continue until both permutations are sorted
    while an != n or bn != m:
        i1, i2 = -1, -1

        # For permutation p: determine index i to use for operation
        if an == n:
            # If p is already sorted, start from position 1
            i1 = 1 if a_[0] == 1 else n
        else:
            # If last element matches current expected value
            if a_[-1] == an:
                # Find index of next expected element and use it
                i1 = a_.index(an + 1) + 1
                an += 1
            else:
                # Find index of current expected element and add 1
                i1 = a_.index(an) + 2

        # For permutation q: determine index j to use for operation
        if bn == m:
            # If q is already sorted, start from position 1
            i2 = 1 if b_[0] == 1 else m
        else:
            # If last element matches current expected value
            if b_[-1] == bn:
                # Find index of next expected element and use it
                i2 = b_.index(bn + 1) + 1
                bn += 1
            else:
                # Find index of current expected element and add 1
                i2 = b_.index(bn) + 2

        # Record operation
        ans.append((i1, i2))
        # Apply operation on p
        a_ = a_[i1:] + [a_[i1 - 1]] + a_[: i1 - 1]
        # Apply operation on q
        b_ = b_[i2:] + [b_[i2 - 1]] + b_[: i2 - 1]

    # Final check if permutations are properly sorted
    if a_ != sorted(a_) or b_ != sorted(b_):
        # If not properly sorted, check for special cases
        if n % 2 == m % 2 == 0:
            # If both have even length, impossible to solve
            print(-1)
            return

        # Handle case where one is sorted and the other is not
        if a_ == sorted(a_):
            # p is sorted but q isn't
            if n % 2 == 0:
                # Add one special operation and then sequence of operations
                ans.append((1, m))
                ans += [(n if i % 2 == 0 else 1, 1) for i in range(m)]
            else:
                # Just add sequence of operations
                ans += [(1, m if i % 2 == 0 else 1) for i in range(n)]
        else:
            # q is sorted but p isn't
            if m % 2 == 0:
                # Add one special operation and then sequence of operations
                ans.append((n, 1))
                ans += [(1, m if i % 2 == 0 else 1) for i in range(n)]
            else:
                # Just add sequence of operations
                ans += [(n if i % 2 == 0 else 1, 1) for i in range(m)]

    # Output solution
    print(len(ans))
    for i1, i2 in ans:
        print(i1, i2)


for i in range(rd(int) if MULTIPLE_CASES else 1):
    main()


# https://github.com/VaHiX/CodeForces/