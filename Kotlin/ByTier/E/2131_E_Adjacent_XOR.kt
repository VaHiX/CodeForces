// Problem: CF 2131 E - Adjacent XOR
// https://codeforces.com/contest/2131/problem/E

/**
 * Problem: E. Adjacent XOR
 * 
 * Purpose:
 *   Given two arrays `a` and `b`, determine if it's possible to transform array `a` into array `b`
 *   by performing XOR operations on adjacent elements in `a`. For each element at index `i` (where `1 <= i < n`),
 *   we can optionally perform the operation: `a[i] := a[i] XOR a[i + 1]`.
 * 
 * Algorithm:
 *   - The key idea is to use reverse simulation:
 *     Start from the last element and work backwards.
 *     At each step, if current `b[i]` doesn't match any of three possible values derived from `a[i]`, `a[i+1]`, and `b[i+1]`,
 *     then transformation is impossible.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing arrays `a` and `b`
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val t = br.readLine().toInt()
    repeat(t) {
        val n = br.readLine().toInt()
        val a = LongArray(n)
        val b = LongArray(n)
        var st = StringTokenizer(br.readLine())
        for (i in 0 until n) a[i] = st.nextToken().toLong()
        st = StringTokenizer(br.readLine())
        for (i in 0 until n) b[i] = st.nextToken().toLong()
        
        // Check if last element matches
        var ok = (b[n - 1] == a[n - 1])
        
        // Traverse backwards to validate transformation possibilities
        for (i in n - 2 downTo 0) {
            val x1 = a[i]                         // Current value of a[i]
            val x2 = a[i] xor a[i + 1]           // Value after XOR with next element
            val x3 = a[i] xor b[i + 1]           // Derived from previous `b` value
            
            // If current b[i] does not match any valid transformation, impossible to achieve
            if (b[i] != x1 && b[i] != x2 && b[i] != x3) {
                ok = false
                break
            }
        }
        println(if (ok) "YES" else "NO")
    }
}


// https://github.com/VaHiX/CodeForces/