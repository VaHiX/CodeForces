// Problem: CF 2131 F - Unjust Binary Life
// https://codeforces.com/contest/2131/problem/F

/*
 * Problem: F. Unjust Binary Life
 * Purpose: Given two binary strings a and b of length n, construct an n×n grid where cell (i,j) has value a[i] XOR b[j].
 *          Find the sum of minimum operations needed to make a journey from (1,1) to each cell (x,y).
 *          A journey is possible if all cells on the path have value 0.
 *          Each operation allows flipping one bit in string a or b.
 *
 * Algorithm:
 *   - Transform strings into arrays of "scores" using: score = 2 * prefix_count - index
 *   - Sort array b's scores to enable binary search
 *   - Use Segment Tree for range sum queries and point updates
 *   - For each element in a's score array, compute the cost to make it reachable,
 *     by calculating how many elements in sorted b are less than or equal to -score.
 *   - Total operations = (n^3 * (n+1)) / 2 - sum of all absolute differences
 *
 * Time Complexity: O(n log n) per test case due to sorting and segment tree operations
 * Space Complexity: O(n) for storing arrays and segment tree
 */

class SegmentTree(private val n: Int) {
    private val tree = LongArray(4 * n)
    
    // Build the segment tree from the given array
    fun build(arr: LongArray, idx: Int = 1, l: Int = 0, r: Int = n - 1) {
        if (l == r) {
            tree[idx] = arr[l]
            return
        }
        val mid = (l + r) / 2
        build(arr, idx * 2, l, mid)
        build(arr, idx * 2 + 1, mid + 1, r)
        tree[idx] = tree[idx * 2] + tree[idx * 2 + 1]
    }
    
    // Query sum of elements in range [qL, qR]
    fun query(qL: Int, qR: Int, idx: Int = 1, l: Int = 0, r: Int = n - 1): Long {
        if (qR < l || qL > r) return 0
        if (qL <= l && r <= qR) return tree[idx]
        val mid = (l + r) / 2
        return query(qL, qR, idx * 2, l, mid) + query(qL, qR, idx * 2 + 1, mid + 1, r)
    }
}

fun main() {
    val br = System.`in`.bufferedReader()
    val T = br.readLine().toInt()
    val out = StringBuilder()
    
    repeat(T) {
        val n = br.readLine().toInt()
        val a = br.readLine()
        val b = br.readLine()
        
        var cnt = 0
        // vecM: Compute score for each position in string a
        val vecM = LongArray(n) { i ->
            if (a[i] == '1') cnt++
            2L * cnt - (i + 1)
        }
        
        cnt = 0
        // vecA: Compute score for each position in string b, then sort it
        val vecA = LongArray(n) { i ->
            if (b[i] == '1') cnt++
            2L * cnt - (i + 1)
        }.also { it.sort() }
        
        // Build segment tree with vecA values
        val seg = SegmentTree(n)
        seg.build(vecA)
        
        var Sabs = 0L
        val totalSum = seg.query(0, n - 1)
        
        // For each element in vecM, calculate contribution to sum
        for (x in vecM) {
            val p = vecA.binarySearch(-x).let { if (it < 0) -it - 1 else it }
            
            // Compute prefix sum from 0 to p-1
            val sumL = if (p > 0) seg.query(0, p - 1) else 0
            
            // Compute suffix sum from p to n-1
            val sumR = if (p < n) seg.query(p, n - 1) else 0
            
            // Add cost for making this position reachable
            Sabs += (-x) * p - sumL + x * (n - p) + sumR
        }
        
        // Final result based on formula: (n^3 * (n+1)) / 2 - Sabs
        val mp = 1L * n * n * (n + 1)
        out.append((mp - Sabs) / 2).append('\n')
    }
    print(out)
}


// https://github.com/VaHiX/codeForces/