// Problem: CF 2151 A - Incremental Subarray
// https://codeforces.com/contest/2151/problem/A

/*
 * Problem: Count how many times a given array `a` appears as a subarray in the concatenated sequence b,
 * where b is formed by concatenating arrays [1], [1,2], ..., [1,2,...,n].
 * 
 * Algorithms/Techniques: Incremental Subarray
 * 
 * Time Complexity: O(n + m), where n is the maximum number written and m is the length of array `a`.
 * Space Complexity: O(1), excluding input/output buffers.
 */
fun main() {
    val cin = System.`in`.bufferedReader()
    val cout = System.out.bufferedWriter()
    repeat(cin.readLine().toInt()) {
        val (n, m) = cin.readLine().split(" ").map { it.toInt() }
        val a = cin.readLine().split(" ").map { it.toInt() }
        var ans = 1
        // If the array `a` spans from the beginning to the end of a complete block,
        // we can calculate how many such blocks start after the first one.
        if (a[m-1] - a[0] + 1 == m) {
            ans = n - a[m-1] + 1
        }
        cout.write("${ans}\n")
    }
    cout.flush()
}


// https://github.com/VaHiX/CodeForces/