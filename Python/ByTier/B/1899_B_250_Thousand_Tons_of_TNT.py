# Problem: CF 1899 B - 250 Thousand Tons of TNT
# https://codeforces.com/contest/1899/problem/B

"""
Code Purpose:
This program computes the maximum absolute difference between the total weights of any two trucks when loading boxes into trucks with a fixed number of boxes per truck. The strategy is to try all valid numbers of boxes per truck (k) that divide the total number of boxes (n), then compute the weight of each truck for that k, and find the maximum difference between the heaviest and lightest truck.

Algorithms/Techniques:
- Prefix sums to efficiently compute the sum of boxes in each truck
- Iterating over all divisors of n to test possible k values
- Dynamic update of maximum difference

Time Complexity:
O(N * sqrt(N)) - We iterate through all possible divisors k of N, and for each k, we compute a list of truck weights which takes O(N/k) time. The sum of N/k over all divisors k is O(N * sqrt(N)).

Space Complexity:
O(N) - For storing the prefix sum array and the list of truck weights for each k.
"""

for t in range(int(input())):
    N = int(input())
    A = list(map(int, input().split()))
    # Compute prefix sums for efficient range sum queries
    prefix = [0]
    for a in A:
        prefix.append(prefix[-1] + a)
    
    # Initialize answer with the difference between max and min box weights
    # This handles the case when only one truck is used
    ans = max(A) - min(A)
    
    # Start checking from k=2 since k=1 implies only one truck (difference is 0)
    k = 2
    while k < N:
        # Check if k divides N evenly (valid number of boxes per truck)
        if N % k == 0:
            # Compute the total weight of each truck
            B = [prefix[i] - prefix[i - k] for i in range(k, N + 1, k)]
            # Update the maximum difference between truck weights
            ans = max(ans, max(B) - min(B))
        k += 1
    print(ans)


# https://github.com/VaHiX/CodeForces/