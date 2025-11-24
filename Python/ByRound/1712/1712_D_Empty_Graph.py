# Problem: CF 1712 D - Empty Graph
# https://codeforces.com/contest/1712/problem/D

"""
Algorithm: Binary Search on Answer
Technique: 
  - Use binary search to find the maximum possible diameter.
  - For a given diameter value x, check if it's possible to achieve it 
    by making at most K changes to the array such that the resulting 
    graph has diameter <= x.
  - To check feasibility:
    - Mark elements < x/2 as infinity (they can't contribute to a valid edge weight).
    - Check if there exists a continuous subarray of length >= 2 with all elements >= x.
    - If not, then we need to ensure that all elements are < x (i.e., the whole array is invalid).
    - Count how many changes are needed to make the array valid under constraint x.
  - Time Complexity: O(N * log(max_value))
  - Space Complexity: O(N)

Approach:
  - Binary search on the answer (diameter).
  - For each candidate answer, simulate the process to determine if valid using at most K operations.
"""

T = int(input())

inf = 10**9
for _ in range(T):
    N, K = map(int, input().split())
    A = list(map(int, input().split()))

    def det(x):
        # Create a copy of array A to work with
        V = [a for a in A]
        ct = 0
        
        # Mark elements less than x/2 as infinity (can't be part of valid edge)
        for i, a in enumerate(V):
            if 2 * a < x:
                ct += 1
                V[i] = inf

        # Check whether there exists a valid continuous segment of length >= 2
        flag = True
        for i in range(N - 1):
            if V[i] >= x and V[i + 1] >= x:
                flag = False  # Found a valid continuous segment
                break
        ct += int(flag)  # If no valid segment, one more change needed

        # If all elements are less than x, we must change all of them
        ct += int(all(V[i] < x for i in range(N)))

        return ct <= K  # Return if changes required are within K

    rt = inf + 1  # Right boundary for binary search
    lt = 0        # Left boundary for binary search
    while rt - lt > 1:
        ct = (rt + lt) // 2  # Midpoint
        if det(ct):
            lt = ct  # Try higher diameter
        else:
            rt = ct  # Try lower diameter

    print(lt)


# https://github.com/VaHiX/CodeForces/