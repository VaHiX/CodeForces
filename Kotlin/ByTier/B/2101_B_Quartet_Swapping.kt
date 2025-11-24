// Problem: CF 2101 B - Quartet Swapping
// https://codeforces.com/contest/2101/problem/B

/*
B. Quartet Swapping

Purpose:
This program finds the lexicographically smallest permutation that can be obtained from a given permutation by performing a specific swap operation. The allowed operation swaps pairs of elements at indices (i, i+1) and (i+2, i+3), effectively rotating four consecutive elements as a group.

Algorithms/Techniques:
- Pairwise sorting approach: Split the input array into two groups based on even and odd indices. Sort each group independently.
- Binary Indexed Tree (Fenwick Tree): Used to efficiently compute the parity of inversions in O(log n) time for each insertion.

Time Complexity: O(n log n) per test case due to sorting and BIT operations.
Space Complexity: O(n) for storing the array, split subarrays, and BIT.

Operations:
- Each operation allows swapping elements at positions (i, i+1) with (i+2, i+3).
- This effectively permits cyclic rotation of groups of 4 elements.
- By splitting even and odd indexed elements, we can sort each group separately to get a locally optimal result.
- If the parity mismatch occurs, we try swapping last two elements from even-indexed sorted group.
*/

fun main() {
    val out = StringBuilder()
    repeat(readLine()!!.toInt()) {
        val n = readLine()!!.toInt()
        val p = readLine()!!.split(" ").map(String::toInt).toIntArray()
        // Split into two arrays: one for even indices, another for odd indices
        val split = Array(2) { x -> (x until n step 2).map(p::get).sorted() }
        // Reconstruct the answer by interleaving sorted groups
        val answer = IntArray(n) { split[it % 2][it / 2] }
        // Check parity and fix if necessary using a specific swap
        if (parity(answer) != parity(p)) {
            val a = answer[n - 3]
            val b = answer[n - 1]
            answer[n - 3] = b
            answer[n - 1] = a
        }
        out.appendLine(answer.joinToString(" "))
    }
    print(out)
}

// Parity function computes inversion parity using BIT
fun parity(p: IntArray): Int {
    val n = p.size
    val bit = BinaryIndexTree(1, n)
    var result = 0
    for (k in p) {
        // Count elements larger than k that came after it (inversions)
        result += bit[k + 1, n]
        bit.update(k, 1)
    }
    return result % 2
}

// Binary Indexed Tree implementation for range queries and updates
class BinaryIndexTree(val treeFrom: Int, treeTo: Int) {
    val value = IntArray(treeTo - treeFrom + 2)
    
    // Update the BIT at index with delta
    fun update(index: Int, delta: Int) {
        var i = index + 1 - treeFrom
        while (i < value.size) {
            value[i] += delta
            i += i and -i
        }
    }
    
    // Query prefix sum up to 'to'
    fun query(to: Int): Int {
        var res = 0
        var i = to + 1 - treeFrom
        while (i > 0) {
            res += value[i]
            i -= i and -i
        }
        return res
    }
    
    // Get difference between prefix sums [from, to]
    operator fun get(from: Int, to: Int) = if (to < from) 0 else query(to) - query(from - 1)
}


// https://github.com/VaHiX/CodeForces/