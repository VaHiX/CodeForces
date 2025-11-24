// Problem: CF 1705 F - Mark and the Online Exam
// https://codeforces.com/contest/1705/problem/F

/*
Algorithm: 
The problem requires determining the answer key to a true/false exam by querying a grading system up to 675 times.
The strategy uses a combination of binary search and parity techniques to efficiently deduce each answer.
We use:
1. Initial full 'T' query to determine base count of correct answers (a1).
2. A parity-based query (ask2) to determine answer pattern for pairs of questions.
3. Grouping the questions into triplets and using query results to infer answers.
4. Final check for any remaining individual questions.

Approach:
- The first query is all 'T's to get a baseline (a1).
- Subsequent queries with specific patterns are used to deduce the parity and values of answer pairs.
- The main loop groups questions in triplets and infers answers from these queries.
- Finally, any leftover questions are handled individually.

Time Complexity: O(n) - Each question is effectively processed in constant time per group, and we process in roughly n/3 groups plus n individual checks.
Space Complexity: O(n) - We store the result string and a few temporary variables.
*/

#include <stdlib.h>
#include <iostream>
#include <string>

#define rep(x, l, r) for (int x = l; x <= r; x++)
using namespace std;
int n, a1, a2, p, w, v;
string s, ans;

// Function to make a query and return number of correct answers
int ask(string s) {
  cout << s << "\n";
  cout.flush(); // Flush to ensure output is sent immediately
  int x = 0;
  cin >> x;
  if (x == n)
    exit(0); // If all answers are correct, we're done
  return x;
}

// Function to determine the count of 'F' answers in a range [l,r]
int ask1(int l, int r) {
  string s = "";
  rep(i, 1, n) s += (l <= i && i <= r ? 'F' : 'T'); // Create string where range [l,r] is 'F'
  return (a1 + r - l + 1 - ask(s)) / 2; // Computation based on difference between a1 and new query result
}

// Function to determine the parity of answers in specific pattern
int ask2(int x) {
  string s = "";
  rep(i, 1, n) s += (((i & 1) ^ (i == x || i == x + 1)) ? 'T' : 'F'); // Alternate pattern based on index
  return ask(s);
}

int main() {
  cin >> n; // Read number of questions
  rep(i, 1, n) s += 'T'; // Initialize string with all 'T'
  a1 = ask(s); // Query all 'T's to get base correct count
  a2 = ask2(-1); // Use parity query to get reference pattern, -1 means no specific offset

  // Process the questions in groups of 3
  rep(i, 1, n / 3) {
    p = (i - 1) * 3 + 1; // Start index of triplet
    w = ask1(p, p + 2);  // Get number of 'F' answers in this triplet
    
    if (!w) { // All 'T' in triplet
      ans += "FFF";
      continue;
    }
    if (w == 3) { // All 'F' in triplet
      ans += "TTT";
      continue;
    }

    // Determine answer for specific positions in triplet
    v = ask2(p) - a2; // Difference in parity to determine position parity
    
    if (!v) { // If parity does not change
      if (w == 1)
        ans += "FFT"; // One 'F', two 'T'
      else
        ans += "TTF"; // Two 'T', one 'F'
    } else { // Parity changes
      if ((v < 0) ^ (p & 1)) // Conditional logic based on parity
        ans += "FT"; // First is 'F', second is 'T'
      else
        ans += "TF"; // First is 'T', second is 'F'
      
      if (w == 1)
        ans += "F"; // Third is 'F'
      else
        ans += "T"; // Third is 'T'
    }
  }

  // Handle remaining questions not in triplets
  rep(i, n / 3 * 3 + 1, n) ans += (ask1(i, i) ? 'T' : 'F'); // Individual check for remaining

  cout << ans << "\n";
  cout.flush(); // Flush output
  return 0;
}


// https://github.com/VaHiX/CodeForces/