# Problem: CF 1887 F - Minimum Segments
# https://codeforces.com/contest/1887/problem/F

"""
Algorithm/Techniques: 
- Greedy approach with segment analysis and reconstruction
- Uses a helper function to validate and reconstruct the sequence based on the given characteristic r
- Time Complexity: O(n)
- Space Complexity: O(n)

The algorithm works by:
1. Validating the input characteristic r for consistency
2. Identifying which positions need to be assigned values based on the r array
3. Assigning values greedily to ensure all distinct elements appear within required ranges
4. Reconstructing the sequence A based on assignments
"""

def solve(R):
    R.copy()
    N = len(R)
    R.append(N)
    for i in range(N):
        if R[i] > R[i + 1]:
            return None

    if R[0] == N:
        return None

    appears = [False] * (N + 1)
    for r in R:
        appears[r] = True

    targets = [i for i in range(N + 1) if not appears[i]]

    next_same = [-1] * N
    sources = []
    min_balls = 0
    max_balls = R[0]
    num_final = 0
    lo = hi = 0

    for i in range(1, N + 1):
        if R[i] == R[i - 1]:
            while lo < len(targets) and targets[lo] <= i - 1:
                lo += 1
            first = lo
            min_balls = max(min_balls, first - len(sources))

            while hi < len(targets) and targets[hi] <= R[i]:
                hi += 1

            if R[i] == N:
                num_final += 1
            else:
                last = hi - 1
                max_balls = min(max_balls, last - len(sources))

            sources.append(i - 1)
        else:
            next_same[i - 1] = R[i]

    assert len(sources) == len(targets)
    max_balls = min(max_balls, num_final)

    if min_balls > max_balls:
        return None

    sources = [-1] * min_balls + sources
    targets = targets + [N] * min_balls

    for z in range(len(sources)):
        s, t = sources[z], targets[z]
        if s != -1:
            next_same[s] = t

    A = list(range(1, N + 1))

    for i in range(N):
        if next_same[i] < N:
            A[next_same[i]] = A[i]

    return A


def main():
    T = int(input())
    for _ in range(T):
        int(input())
        R = list(map(int, input().split()))
        R = [r - 1 for r in R]
        ans = solve(R)

        if ans:
            print("Yes")
            print(" ".join(map(str, ans)))
        else:
            print("No")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/