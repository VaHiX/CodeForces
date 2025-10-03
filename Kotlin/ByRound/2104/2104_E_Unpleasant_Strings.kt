// Problem: CF 2104 E - Unpleasant Strings
// https://codeforces.com/contest/2104/problem/E

/*
E. Unpleasant Strings

Purpose:
This solution determines the minimum number of allowed letters to append to a query string t so that it stops being a subsequence of the given string s.

Algorithms/Techniques:
- Preprocessing using dynamic programming with a suffix array approach
- For each position in s, we store the last occurrence of each character
- We build a lookup table C[i][j] which represents the next position where character j appears after position i in s
- We compute for each prefix of s how many operations are needed to make it unpleasant

Time Complexity: O(n * k + q * m) where n is length of s, k is number of allowed letters, q is number of queries, m is total length of all t strings.
Space Complexity: O(n * k + n + q)

*/
fun main() {
    val (N, K) = readLine()!!.split(" ").map { it.toInt() }
    val S = readLine()!!
    val A = IntArray(K) { N } // Tracks last occurrence of each letter
    val Ans = IntArray(N + 1) // Stores minimum operations needed for subsequence ending at position i
    val C = Array(N) { IntArray(K) } // C[i][j] is the next position of character j after position i
    
    for (i in N - 1 downTo 0) {
        Ans[i] = Ans[A.max()!!] + 1  // Compute minimum steps to make subsequence ending at i unpleasant
        C[i] = A.copyOf()            // Copy current state for lookup table
        A[S[i] - 'a'] = i           // Update last seen index of character S[i]
    }
    
    val Q = readLine()!!.toInt()
    repeat(Q) {
        val T = readLine()!!
        var j = -1                  // Tracks current position in s
        for (ch in T) {
            j = if (j == -1) {
                if (ch == S[0]) 0 else C[0][ch - 'a']  // If starting fresh, see if ch matches first char or not
            } else {
                C[j][ch - 'a']   // Move to next occurrence of ch from current position j
            }
            if (j == N) break    // If no valid next character found, stop
        }
        println(Ans[j])          // Print minimal steps needed for this subsequence
    }
}


// https://github.com/VaHiX/CodeForces/