// Problem: CF 2127 C - Trip Shopping
// https://codeforces.com/contest/2127/problem/C

/*
C. Trip Shopping

Purpose:
This program computes the optimal outcome of a game between Ali and Bahamin,
where they alternate making moves on two arrays a and b for k rounds to either
minimize or maximize the sum of absolute differences between elements.

Algorithms/Techniques:
- Greedy approach with sorting and pair manipulation.
- For each round, Bahamin can rearrange values to maximize the total difference.
- Ali chooses pairs to minimize the impact on the result.

Time Complexity: O(n log n) per test case due to sorting operations.
Space Complexity: O(n) for storing arrays and intermediate data structures.

Input:
Each test case contains:
- Two integers n (length of arrays) and k (number of rounds).
- Two lines of n integers each representing arrays a and b.

Output:
For each test case, output the minimum possible value of v = sum(|a[i] - b[i]|) 
after both players play optimally.
*/

fun main() {
    val T = readln().toInt(); // Number of test cases
    repeat(T) {
        val (n, k) = readln().split(" ").map { it.toInt() } // Read n and k
        val a = readln().split(" ").map { it.toInt() }.toIntArray() // Read array a
        val b = readln().split(" ").map { it.toInt() }.toIntArray() // Read array b
        
        // Step 1: For each index, ensure a[i] <= b[i] to simplify further logic
        for (i in 0 until n) {
            if (a[i] > b[i]) {
                val tmp = a[i]
                a[i] = b[i]
                b[i] = tmp
            }
        }

        // Step 2: Create pairs of (a[i], b[i])
        var pairs = a.zip(b)
        
        // Step 3: Sort by second element in descending order to prioritize larger b values
        pairs = pairs.sortedBy { -it.second }
        
        // Step 4: Re-sort by first element in ascending order to group smaller a values together
        pairs = pairs.sortedBy { it.first }
        
        // Step 5: Find minimum additional cost over all adjacent pairs
        var minAdditional = Long.MAX_VALUE
        for (i in 0 until n - 1) {
            // Compute how much we can gain by swapping two adjacent elements to reduce total difference
            minAdditional = Math.min(minAdditional, 2L * Math.max(0, pairs[i + 1].first - pairs[i].second))
        }

        // Step 6: Calculate initial total difference
        var ans = 0L
        for (i in 0 until n) {
            ans += Math.abs(pairs[i].first - pairs[i].second)
        }

        // Step 7: Add the minimal possible gain from optimal swaps across k rounds
        println(ans + minAdditional);
    }
}


// https://github.com/VaHiX/CodeForces/