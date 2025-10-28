// Problem: CF 1910 H - Sum of Digits of Sums
// https://codeforces.com/contest/1910/problem/H

/*
H. Sum of Digits of Sums
time limit per test6 seconds
memory limit per test512 megabytes

Task:
Given an array of positive integers, for each element ai, compute the sum of digit sums of all pairwise sums (ai + aj) for j from 1 to n.
F(x) = sum of digits in x

Algorithms/Techniques:
- Digit DP + Binary Search
- Precompute digit sums and modular remainders for efficient querying
- Use prefix-like approach with sorted arrays for counting elements greater than a threshold

Time Complexity: O(9 * n * log(n)) where 9 is max number of digits, n is array size.
Space Complexity: O(9 * n) for storing precomputed remainders and powers of 10.

This solution uses the fact that sum of digits can be split by place value (units, tens, hundreds etc.) and for each digit place
we calculate how many numbers when added to a[i] will cause carry operations. These carries affect the total digit sum.
*/

import java.io.BufferedReader
import java.io.InputStreamReader
import java.lang.StringBuilder

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val n = br.readLine()!!.toInt()
    val a = br.readLine()!!.split(' ').map { it.toInt() }.toIntArray()
    
    // Compute digit sum for each element in array
    val f = IntArray(n) {
        var s = 0
        var x = a[it]
        while (x > 0) {
            s += x % 10
            x /= 10
        }
        s
    }
    
    val sumF = f.sum().toLong() // Total sum of all digit sums
    
    // Precompute powers of 10 for each digit place (0 to 8)
    val p = LongArray(9) { 1L }.apply {
        for (i in 0..8) this[i] = this.getOrElse(i - 1) { 1L } * 10L
    }
    
    // Precompute remainders of all numbers modulo powers of 10
    val m = Array(9) { IntArray(n) }
    for (k in 0..8) {
        val pk = p[k].toInt()
        for (j in 0 until n) m[k][j] = a[j] % pk
        m[k].sort() // Sort for binary search
    }
    
    // Binary search function to find leftmost position where value >= v
    fun lb(arr: IntArray, v: Int): Int {
        var l = 0
        var r = arr.size
        while (l < r) {
            val mid = (l + r) ushr 1
            if (arr[mid] < v) l = mid + 1 else r = mid
        }
        return l
    }
    
    val sb = StringBuilder()
    for (i in 0 until n) {
        var carries = 0L // Count number of carries in each digit place
        for (k in 0..8) {
            val bi = a[i] % p[k].toInt() // Remainder of current element at k-th digit place
            val th = p[k].toInt() - bi    // Threshold to reach next higher multiple
            carries += (n - lb(m[k], th)) // Count how many numbers will cause carry
        }
        
        // Final result calculation:
        // n * f[i] + sumF - 9L * carries 
        // Where 9L * carries is because each carry in any digit place contributes +1 to that digit,
        // and we have 9 such places (0 through 8). Total carries are subtracted from total sum.
        val res = n.toLong() * f[i] + sumF - 9L * carries
        sb.append(res).append(' ')
    }
    
    println(sb.toString().trim())
}


// https://github.com/VaHiX/codeForces/