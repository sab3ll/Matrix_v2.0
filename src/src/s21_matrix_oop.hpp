#ifndef S21_MATRIX_H
#define S21_MATRIX_H
#define EPS 1e-07

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  void AllocateMemory(int rows, int cols);
  void DeallocateMemory();
  S21Matrix calcMinor(const int row_s, const int col_s);

 public:
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;

  int GetCols() const noexcept;
  int GetRows() const noexcept;
  void SetCols(int cols);
  void SetRows(int rows);

  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  double Determinant();
  S21Matrix Transpose() noexcept;
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(double number) const;
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double number) noexcept;
  double& operator()(int row, int col);
  double& operator()(int row, int col) const;

  // Для отладки
  void PrintMatrix();
};

#endif
