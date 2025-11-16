// Problem: CF 2159 D1 - Inverse Minimum Partition (Easy Version)
// https://codeforces.com/contest/2159/problem/D1

/*
D1. Inverse Minimum Partition (Easy Version)

Algorithm:
This solution uses dynamic programming with a TreeMap to efficiently find the minimum cost to partition the array.
- For each position k, we compute dp[k] as the minimum cost to partition the first k elements.
- The key idea is to maintain a TreeMap of values and their indices where we can make a cut.
- For each element, we remove entries from the TreeMap that are >= current element.
- Then we query for valid previous positions by looking up the largest value < ceilDiv(current_element, cost).
- Time Complexity: O(n * log n) per test case due to TreeMap operations and outer loop.
- Space Complexity: O(n) for dp array and TreeMap.

Techniques:
- Dynamic Programming
- TreeMap for efficient range queries and updates
- Ceiling division calculation

*/
import java.util.TreeMap
import kotlin.math.min

fun main() {
    repeat(readln().toInt()) {
        val n = readln().toInt()
        val xs = listOf(0L) + readln().split(" ").map(String::toLong)
        val treeMap = TreeMap<Long, Int>() // Stores (value, index) pairs, sorted by value
        treeMap[0L] = 0
        val dp = IntArray(n + 1) { n + 1 } // dp[i] represents min cost to partition first i elements
        dp[0] = 0
        for (k in 1..n) {
            while (treeMap.lastKey() >= xs[k]) { // Remove values greater than or equal to current element
                treeMap.remove(treeMap.lastKey())
            }
            treeMap[xs[k]] = k // Insert current element and its index into TreeMap
            for (cost in 1..5) {
                val prev = treeMap.lowerEntry(ceilDiv(xs[k], cost.toLong())).value // Find largest entry < ceilDiv(xs[k], cost)
                dp[k] = min(dp[k], dp[prev] + cost) // Update dp with minimum cost
            }
        }
        println(dp[n])
    }
}

fun ceilDiv(x: Long, y: Long) = (x + y - 1L) / y


// https://github.com/VaHiX/CodeForces/