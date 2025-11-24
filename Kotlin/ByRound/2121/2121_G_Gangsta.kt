// Problem: CF 2121 G - Gangsta
// https://codeforces.com/contest/2121/problem/G

/*
 * Problem: G. Gangsta
 *
 * Purpose:
 *   Given a binary string s of length n, compute the sum of f(s[l..r]) over all substrings,
 *   where f(p) is the maximum count of any character in substring p.
 *
 * Algorithm:
 *   - Transform the string into a prefix sum array using +1 for '1' and -1 for '0'.
 *   - Use coordinate compression on prefix sums to map values to indices suitable for Fenwick Tree.
 *   - For each position j, calculate how many previous prefix sums are strictly less than current
 *     and how many are greater or equal, along with their sum.
 *   - Use two Fenwick Trees to maintain counts and sum of prefix sums up to a certain index.
 *   - Apply mathematical formula to compute contributions efficiently.
 *
 * Time Complexity: O(n log n) per test case due to sorting and Fenwick Tree operations
 * Space Complexity: O(n) for storing arrays and Fenwick trees
 */

import kotlin.math.abs

class FenwickTree(val size: Int) {
    private val tree = LongArray(size + 2)
    
    fun update(index: Int, value: Long) {
        var i = index
        while (i <= size) {
            tree[i] += value
            i += i and -i // Move to next node in BIT
        }
    }
    
    fun query(index: Int): Long {
        var i = index
        var res = 0L
        while (i > 0) {
            res += tree[i]
            i -= i and -i // Move to parent node in BIT
        }
        return res
    }
    
    fun queryRange(l: Int, r: Int): Long {
        return query(r) - query(l - 1)
    }
}

fun solve() {
    val n = readLine()!!.toInt()
    val s = readLine()!!
    val a = LongArray(n + 1) // Convert chars to +1/-1
    val p = LongArray(n + 1) // Prefix sums
    
    for (i in 1..n) {
        a[i] = if (s[i - 1] == '1') 1 else -1
        p[i] = p[i - 1] + a[i]
    }
    
    val allP = p.toSet().sorted() // Get unique prefix sums for coordinate compression
    val id = allP.withIndex().associate { (i, v) -> v to (i + 1) } // Map values to indices
    
    val size = allP.size + 2
    val bitCnt = FenwickTree(size) // BIT for maintaining counts of prefix sums
    val bitSum = FenwickTree(size) // BIT for maintaining sum of prefix sums
    
    var mp1 = 0L
    bitCnt.update(id[0L]!!, 1)
    bitSum.update(id[0L]!!, 0)
    
    for (j in 1..n) {
        val idx = id[p[j]]!! // Get compressed index of current prefix sum
        
        val lo = bitCnt.query(idx - 1) // Count values < p[j]
        val jk = bitSum.query(idx - 1) // Sum of values < p[j]
        
        val totalCnt = bitCnt.query(size)
        val totalSum = bitSum.query(size)
        
        val hi = totalCnt - lo // Count values >= p[j]
        val ko = totalSum - jk // Sum of values >= p[j]
        
        mp1 += lo * p[j] - jk
        mp1 += ko - hi * p[j]
        
        bitCnt.update(idx, 1)
        bitSum.update(idx, p[j])
    }
    
    val mp2 = n.toLong() * (n + 1) * (n + 2) / 6 // Total contribution from all subarrays
    val ans = (mp1 + mp2) / 2
    println(ans)
}

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        solve()
    }
}


// https://github.com/VaHiX/CodeForces/