// EE538 Lab 1: Matrix multiplication with Divide & Conquer and Strassen's method
// Author: thutapea (spotifytimh@gmail.com)

#include <ctime>
#include <fstream>

// Allocates an n x n matrix of zeros using double pointers.
int **createMatrix(int n) {
  int **m = new int *[n];
  for (int i = 0; i < n; i++) {
    m[i] = new int[n];
    for (int j = 0; j < n; j++) {
      m[i][j] = 0;
    }
  }
  return m;
}

void deleteMatrix(int **m, int n) {
  for (int i = 0; i < n; i++) {
    delete[] m[i];
  }
  delete[] m;
}

void addMatrix(int **A, int **B, int **C, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
}

void subtractMatrix(int **A, int **B, int **C, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      C[i][j] = A[i][j] - B[i][j];
    }
  }
}

// Copies the n x n block of src starting at (row, col) into dest.
void copyFromBlock(int **src, int **dest, int row, int col, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      dest[i][j] = src[row + i][col + j];
    }
  }
}

// Copies the n x n matrix src into the block of dest starting at (row, col).
void copyToBlock(int **src, int **dest, int row, int col, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      dest[row + i][col + j] = src[i][j];
    }
  }
}

// Question 1: simple divide and conquer, 8 recursive multiplications.
void divideAndConquer(int **A, int **B, int **C, int n) {
  if (n == 1) {
    C[0][0] = A[0][0] * B[0][0];
    return;
  }

  int h = n / 2;

  int **a11 = createMatrix(h);
  int **a12 = createMatrix(h);
  int **a21 = createMatrix(h);
  int **a22 = createMatrix(h);
  int **b11 = createMatrix(h);
  int **b12 = createMatrix(h);
  int **b21 = createMatrix(h);
  int **b22 = createMatrix(h);

  copyFromBlock(A, a11, 0, 0, h);
  copyFromBlock(A, a12, 0, h, h);
  copyFromBlock(A, a21, h, 0, h);
  copyFromBlock(A, a22, h, h, h);
  copyFromBlock(B, b11, 0, 0, h);
  copyFromBlock(B, b12, 0, h, h);
  copyFromBlock(B, b21, h, 0, h);
  copyFromBlock(B, b22, h, h, h);

  int **c11 = createMatrix(h);
  int **c12 = createMatrix(h);
  int **c21 = createMatrix(h);
  int **c22 = createMatrix(h);

  int **left = createMatrix(h);
  int **right = createMatrix(h);

  // C11 = A11*B11 + A12*B21
  divideAndConquer(a11, b11, left, h);
  divideAndConquer(a12, b21, right, h);
  addMatrix(left, right, c11, h);

  // C12 = A11*B12 + A12*B22
  divideAndConquer(a11, b12, left, h);
  divideAndConquer(a12, b22, right, h);
  addMatrix(left, right, c12, h);

  // C21 = A21*B11 + A22*B21
  divideAndConquer(a21, b11, left, h);
  divideAndConquer(a22, b21, right, h);
  addMatrix(left, right, c21, h);

  // C22 = A21*B12 + A22*B22
  divideAndConquer(a21, b12, left, h);
  divideAndConquer(a22, b22, right, h);
  addMatrix(left, right, c22, h);

  copyToBlock(c11, C, 0, 0, h);
  copyToBlock(c12, C, 0, h, h);
  copyToBlock(c21, C, h, 0, h);
  copyToBlock(c22, C, h, h, h);

  deleteMatrix(a11, h);
  deleteMatrix(a12, h);
  deleteMatrix(a21, h);
  deleteMatrix(a22, h);
  deleteMatrix(b11, h);
  deleteMatrix(b12, h);
  deleteMatrix(b21, h);
  deleteMatrix(b22, h);
  deleteMatrix(c11, h);
  deleteMatrix(c12, h);
  deleteMatrix(c21, h);
  deleteMatrix(c22, h);
  deleteMatrix(left, h);
  deleteMatrix(right, h);
}

// Question 2: Strassen's method, 7 recursive multiplications.
void strassen(int **A, int **B, int **C, int n) {
  if (n == 1) {
    C[0][0] = A[0][0] * B[0][0];
    return;
  }

  int h = n / 2;

  int **a11 = createMatrix(h);
  int **a12 = createMatrix(h);
  int **a21 = createMatrix(h);
  int **a22 = createMatrix(h);
  int **b11 = createMatrix(h);
  int **b12 = createMatrix(h);
  int **b21 = createMatrix(h);
  int **b22 = createMatrix(h);

  copyFromBlock(A, a11, 0, 0, h);
  copyFromBlock(A, a12, 0, h, h);
  copyFromBlock(A, a21, h, 0, h);
  copyFromBlock(A, a22, h, h, h);
  copyFromBlock(B, b11, 0, 0, h);
  copyFromBlock(B, b12, 0, h, h);
  copyFromBlock(B, b21, h, 0, h);
  copyFromBlock(B, b22, h, h, h);

  int **m1 = createMatrix(h);
  int **m2 = createMatrix(h);
  int **m3 = createMatrix(h);
  int **m4 = createMatrix(h);
  int **m5 = createMatrix(h);
  int **m6 = createMatrix(h);
  int **m7 = createMatrix(h);

  int **t1 = createMatrix(h);
  int **t2 = createMatrix(h);

  // M1 = (A11 + A22) * (B11 + B22)
  addMatrix(a11, a22, t1, h);
  addMatrix(b11, b22, t2, h);
  strassen(t1, t2, m1, h);

  // M2 = (A21 + A22) * B11
  addMatrix(a21, a22, t1, h);
  strassen(t1, b11, m2, h);

  // M3 = A11 * (B12 - B22)
  subtractMatrix(b12, b22, t2, h);
  strassen(a11, t2, m3, h);

  // M4 = A22 * (B21 - B11)
  subtractMatrix(b21, b11, t2, h);
  strassen(a22, t2, m4, h);

  // M5 = (A11 + A12) * B22
  addMatrix(a11, a12, t1, h);
  strassen(t1, b22, m5, h);

  // M6 = (A21 - A11) * (B11 + B12)
  subtractMatrix(a21, a11, t1, h);
  addMatrix(b11, b12, t2, h);
  strassen(t1, t2, m6, h);

  // M7 = (A12 - A22) * (B21 + B22)
  subtractMatrix(a12, a22, t1, h);
  addMatrix(b21, b22, t2, h);
  strassen(t1, t2, m7, h);

  int **c11 = createMatrix(h);
  int **c12 = createMatrix(h);
  int **c21 = createMatrix(h);
  int **c22 = createMatrix(h);

  // C11 = M1 + M4 - M5 + M7
  addMatrix(m1, m4, t1, h);
  subtractMatrix(t1, m5, t2, h);
  addMatrix(t2, m7, c11, h);

  // C12 = M3 + M5
  addMatrix(m3, m5, c12, h);

  // C21 = M2 + M4
  addMatrix(m2, m4, c21, h);

  // C22 = M1 - M2 + M3 + M6
  subtractMatrix(m1, m2, t1, h);
  addMatrix(t1, m3, t2, h);
  addMatrix(t2, m6, c22, h);

  copyToBlock(c11, C, 0, 0, h);
  copyToBlock(c12, C, 0, h, h);
  copyToBlock(c21, C, h, 0, h);
  copyToBlock(c22, C, h, h, h);

  deleteMatrix(a11, h);
  deleteMatrix(a12, h);
  deleteMatrix(a21, h);
  deleteMatrix(a22, h);
  deleteMatrix(b11, h);
  deleteMatrix(b12, h);
  deleteMatrix(b21, h);
  deleteMatrix(b22, h);
  deleteMatrix(m1, h);
  deleteMatrix(m2, h);
  deleteMatrix(m3, h);
  deleteMatrix(m4, h);
  deleteMatrix(m5, h);
  deleteMatrix(m6, h);
  deleteMatrix(m7, h);
  deleteMatrix(t1, h);
  deleteMatrix(t2, h);
  deleteMatrix(c11, h);
  deleteMatrix(c12, h);
  deleteMatrix(c21, h);
  deleteMatrix(c22, h);
}

// Writes the top-left n x n part of the result: each number followed by a
// space, one row per line.
void writeMatrix(const char *fileName, int **M, int n) {
  std::ofstream out(fileName);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      out << M[i][j] << " ";
    }
    out << "\n";
  }
  out.close();
}

int main() {
  std::ifstream in("input.txt");
  if (!in.is_open()) {
    return 1;
  }

  int n = 0;
  in >> n;

  // Pad up to the next power of two so the matrices can always be halved.
  int size = 1;
  while (size < n) {
    size = size * 2;
  }

  int **A = createMatrix(size);
  int **B = createMatrix(size);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      in >> A[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      in >> B[i][j];
    }
  }
  in.close();

  int **C1 = createMatrix(size);
  int **C2 = createMatrix(size);

  clock_t start = clock();
  divideAndConquer(A, B, C1, size);
  clock_t end = clock();
  long timeDivideAndConquer = (long)(end - start);

  start = clock();
  strassen(A, B, C2, size);
  end = clock();
  long timeStrassen = (long)(end - start);

  writeMatrix("output_m1.txt", C1, n);
  writeMatrix("output_m2.txt", C2, n);

  std::ofstream outTime("output_q3.txt");
  outTime << timeDivideAndConquer << " " << timeStrassen;
  outTime.close();

  deleteMatrix(A, size);
  deleteMatrix(B, size);
  deleteMatrix(C1, size);
  deleteMatrix(C2, size);

  return 0;
}
