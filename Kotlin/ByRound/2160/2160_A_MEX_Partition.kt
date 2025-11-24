// Problem: CF 2160 A - MEX Partition
// https://codeforces.com/contest/2160/problem/A

/*
 * Problem: A. MEX Partition
 * Algorithms/Techniques: Frequency counting, MEX calculation
 *
 * Time Complexity: O(n) per test case, where n is the size of input array.
 * Space Complexity: O(1) since we use a fixed-size array of size 101 for counting.
 *
 * The solution calculates the minimum possible score over all valid partitions of the given multiset.
 * For each test case:
 *   - Count frequency of each number in the range [0, 100].
 *   - Find the smallest non-negative integer (MEX) that is not present in the count.
 * This value represents the minimum score achievable for any valid partition.
 */

fun main() {
    val cin = System.`in`.bufferedReader()
    val cout = System.out.bufferedWriter()
    repeat(cin.readLine().toInt()) {
        val n = cin.readLine().toInt() // Read size of input array
        val a = cin.readLine().split(" ").map { it.toInt() } // Read array elements
        val cnt = IntArray(101) // Count frequency of each number (0 to 100)
        for (v in a) cnt[v]++ // Populate the frequency count
        var ans = 0
        for (mex in 0 until 101) { // Iterate through possible MEX values from 0 upwards
            if (cnt[mex] == 0) { // If current number is not present in input
                ans = mex // This is the MEX, hence minimum score
                break
            }
        }
        cout.write("${ans}\n") // Output result for this test case
    }
    cout.flush() // Ensure output is written
}


// https://github.com/VaHiX/CodeForces/