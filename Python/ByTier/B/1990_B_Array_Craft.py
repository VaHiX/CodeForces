# Problem: CF 1990 B - Array Craft
# https://codeforces.com/contest/1990/problem/B

"""
Algorithm/Technique: Constructive Algorithm

The problem asks to construct an array of size n with elements either 1 or -1,
such that:
- The maximum prefix sum occurs at position x (smallest such index)
- The maximum suffix sum occurs at position y (largest such index)

Approach:
1. Initialize an array of size n+1 (1-indexed) with all zeros.
2. Set all elements from position x to n as 1. This ensures the prefix sum reaches its maximum at or after x.
3. Set elements from position x-1 down to 1 alternating between -1 and 1. This ensures the prefix sum is maximized at x.
4. Set elements from position x+1 to n alternating between -1 and 1. This maintains the maximum suffix sum at y.
5. Print the resulting array excluding the 0th index.

Time Complexity: O(n) per test case
Space Complexity: O(n) for the array storage
"""

def arr(size, start, end):
    array = [0] * (size + 1)  # Initialize 1-indexed array

    # Set all positions from 'end' to 'size' as 1
    for i in range(end, size + 1):
        array[i] = 1

    # Fill from 'end-1' down to 1 with alternating -1 and 1
    toggle = -1
    for i in range(end - 1, 0, -1):
        array[i] = toggle
        toggle = -toggle

    # Fill from 'start+1' to 'size' with alternating -1 and 1
    toggle = -1
    for i in range(start + 1, size + 1):
        array[i] = toggle
        toggle = -toggle

    # Output the result (excluding index 0)
    print(" ".join(map(str, array[1:])))


def main():
    import sys

    input = sys.stdin.read
    data = input().split()

    pos = 0
    test_cases = int(data[pos])
    pos += 1

    for _ in range(test_cases):
        size = int(data[pos])
        start = int(data[pos + 1])
        end = int(data[pos + 2])
        pos += 3
        arr(size, start, end)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/