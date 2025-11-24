# Problem: CF 1957 B - A BIT of a Construction
# https://codeforces.com/contest/1957/problem/B

"""
Constructs a sequence of n non-negative integers that sum to k,
such that the number of 1s in the binary representation of their bitwise OR is maximized.

Algorithm:
1. For n = 1, simply output k.
2. For n > 1:
   - Find the largest number `ans` such that (1 << i) - 1 <= k for some i.
   - This ensures `ans` has all 1s in its binary representation up to some bit.
   - Then set the second element to (k - ans), and rest to 0.
   
Time Complexity: O(log k) per test case
Space Complexity: O(1) excluding output storage
"""

def main():
    import sys

    input = sys.stdin.read
    data = input().strip().split()

    tt = int(data[0])
    index = 1

    results = []

    for _ in range(tt):
        n = int(data[index])
        k = int(data[index + 1])
        index += 2

        if n == 1:
            results.append(str(k))
            continue

        # Find the largest value with all 1s in binary representation that is <= k
        ans = 0
        for i in range(33):  # 33 because k <= 10^9, which fits in 30 bits
            if k >= (1 << i) - 1:
                ans = (1 << i) - 1  # This gives us a number like 1, 3, 7, 15, ... (2^i - 1)
            else:
                break

        # First two elements: ans and (k - ans)
        # Remaining elements are 0
        result = [str(ans), str(k - ans)]
        result.extend(["0"] * (n - 2))
        results.append(" ".join(result))

    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/