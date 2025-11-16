# Problem: CF 1857 C - Assembly via Minimums
# https://codeforces.com/contest/1857/problem/C

"""
Task: Restore an array 'a' from a shuffled array 'b' where 'b' contains all pairwise minimums of 'a'.

Algorithm:
- Sort the array 'b' in ascending order.
- The smallest element of 'b' must be the minimum of the array 'a'.
- The second smallest element of 'b' must be the minimum of 'a' and the second element of 'a'.
- Iterate through the sorted array and build the result using a greedy approach:
    - Start with the smallest element as the first element of 'a'.
    - For each subsequent element, use the next available element in the sorted array.
- The last element of 'a' is simply the largest element of 'b'.

Time Complexity: O(n^2 * log(n^2)) due to sorting the array of size n*(n-1)/2
Space Complexity: O(n^2) for storing array 'b' and O(n) for the result array 'a', so overall O(n^2)

"""

def main():
    t = int(input())
    r = [str(solution(i, t)) for i in range(t)]

    print("\n".join(r))


def solution(ti, tn):
    n = int(input())
    bb = list(map(int, input().split()))

    aa = []
    bb.sort()

    k = n - 1
    i = 0

    while k > 0:
        aa.append(bb[i])
        i += k
        k -= 1

    aa.append(bb[-1])

    return " ".join(map(str, aa))


main()


# https://github.com/VaHiX/CodeForces/