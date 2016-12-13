
#include <vector>

using namespace std;

// Vector QuickSort
//*****************************************************************************
// 
// Quicksort functions
// - Credit to http://code.runnable.com/VEzwVDYBBzgHZ0VI/quicksort-for-c%2B%2B-and-sorting
//*****************************************************************************
/**
 * Partition the elements of A, such that you first have elements smaller than
 * "who", followed by eleemnts larger than "who". Return the last poistion of an
 * element smaller or equal to "who".
 */
template<class T>
int partition(vector<T>& A, int left, int right, int who) {
  for (int i=left; i<right; ++i) {
    if (A[i] <= who) {
      swap(A[i], A[left]);
      left ++;
    }
  }
  return left - 1;
}

template<class T, class U>
int partitionMirror(vector<T>& A, vector<U>& B, int left, int right, int who) {
  for (int i=left; i<right; ++i) {
    if (A[i] <= who) {
      swap(A[i], A[left]);
      swap(B[i], B[left]);
      left ++;
    }
  }
  return left - 1;
}

/**
 * Quick sort vector A, between index "left" and index "right".
 */
template<class T>
void qsort(vector<T>& A, int left, int right) {
  if (left >= right) return;
  
  int middle = left + (right - left) / 2;
  swap(A[middle], A[left]);
  int midpoint = partition(A, left + 1, right, A[left]);
  swap(A[left], A[midpoint]);
  qsort(A, left, midpoint);
  qsort(A, midpoint + 1, right);
}

// Sort a vector, and mirror swaps it into another
template<class T, class U>
void qsortMirror(vector<T>& A, vector<U>& B, int left, int right)
{
  if (left >= right) return;
  
  int middle = left + (right - left) / 2;
  swap(A[middle], A[left]);
  swap(B[middle], B[left]);
         
  int midpoint = partitionMirror(A, B, left + 1, right, A[left]);
  
  swap(A[left], A[midpoint]);
  swap(B[left], B[midpoint]);
  
  qsort(A, left, midpoint);
  qsort(A, midpoint + 1, right);
}