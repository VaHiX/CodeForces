// Problem: CF 465 B - Inbox (100500)
// https://codeforces.com/contest/465/problem/B

/*
 * Problem: B. Inbox (100500)
 * Purpose: Determine the minimum number of operations to read all unread letters
 *          in a mailbox, where the user can navigate between the list and individual
 *          letter views.
 * 
 * Algorithm:
 * - Traverse the sequence of letters from left to right.
 * - Track whether we are currently viewing a letter (state variable).
 * - When encountering an unread letter (1) and we are not viewing any letter,
 *   we need to open it (1 operation).
 * - When we are already viewing a letter and encounter an unread letter,
 *   we just need to move to that letter (1 operation).
 * - When we are viewing a letter and encounter a read letter (0),
 *   we must close the letter and return to the list (1 operation).
 * - After processing all letters, if we're still viewing a letter (state == 1)
 *   but we had at least one operation (output > 0), we need to close it (1 operation).
 * 
 * Time Complexity: O(n) - single pass through the input
 * Space Complexity: O(1) - only using a few variables regardless of input size
 */

#include <cstdio>
int main() {
  int n;
  scanf("%d\n", &n);
  bool state = 0;  // 0 means not viewing any letter, 1 means viewing a letter
  int output = 0;  // total operations count
  for (int p = 0; p < n; p++) {
    int unread;
    scanf("%d\n", &unread);
    if (state == 0 && unread == 1) {
      // Not viewing any letter, but found an unread one -> need to open it
      state = 1;
      ++output;
    } else if (state == 1 && unread == 1) {
      // Viewing a letter, and found another unread one -> need to move to it
      ++output;
    } else if (state == 1 && unread == 0) {
      // Viewing a letter, but found a read one -> need to close it and return to list
      ++output;
      state = 0;
    }
  }
  if (state == 0 && output > 0) {
    // If we end up not viewing a letter, but we've done some operations,
    // we need one last operation to close the last opened letter
    --output;
  }
  printf("%d\n", output);
  return 0;
}


// https://github.com/VaHiX/CodeForces/