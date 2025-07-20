#include "s21_matrix_oop.hpp"

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0)
    throw std::length_error("Matrix size must be greater or equal than 0");
  AllocateMemory(rows_, cols_);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  AllocateMemory(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() noexcept { DeallocateMemory(); }

int S21Matrix::GetCols() const noexcept { return cols_; }
int S21Matrix::GetRows() const noexcept { return rows_; }

void S21Matrix::SetCols(int cols) {
  if (cols < 1)
    throw std::length_error("New cols' size must be greater than 0");
  if (cols != cols_) {
    S21Matrix tmp(rows_, cols);
    int min = std::min(cols_, cols);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < min; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp);
  }
}

void S21Matrix::SetRows(int rows) {
  if (rows < 1)
    throw std::length_error("New rows' size must be greater than 0");
  if (rows != rows_) {
    S21Matrix tmp(rows, cols_);
    int min = std::min(rows_, rows);
    for (int i = 0; i < min; ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp);
  }
}

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::out_of_range("Index is out of range");
  return matrix_[row][col];
}

double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::out_of_range("Index is out of range");
  return matrix_[row][col];
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(rows_, cols_);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(rows_, cols_);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double number) const {
  S21Matrix result(*this);
  result.MulNumber(number);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    DeallocateMemory();
    rows_ = other.rows_;
    cols_ = other.cols_;
    AllocateMemory(other.rows_, other.cols_);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    DeallocateMemory();
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double number) noexcept {
  MulNumber(number);
  return *this;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j)
      if (std::fabs(matrix_[i][j] - other(i, j)) > EPS) return false;
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::range_error("Matrices must be same dimensions");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::range_error("Matrices must be same dimensions");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error("Incorrect matrix size for multiplication");
  }

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        result(i, j) += (matrix_[i][k] * other.matrix_[k][j]);
      }
    }
  }
  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() noexcept {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(j, i) = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::calcMinor(const int row_s, const int col_s) {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int current_row = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != row_s) {
      int current_col = 0;
      for (int j = 0; j < cols_; j++) {
        if (j != col_s) {
          minor(current_row, current_col) = matrix_[i][j];
          current_col++;
        }
      }
      current_row++;
    }
  }
  return minor;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) throw std::logic_error("Matrix must be N x N size");
  double result = 0.0;
  switch (rows_) {
    case 1:
      result = matrix_[0][0];
      break;
    case 2:
      result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
      break;
    default:
      int sign = 1;
      for (int i = 0; i < cols_; i++) {
        S21Matrix minor = calcMinor(0, i);
        double determ_min = minor.Determinant();
        result += sign * matrix_[0][i] * determ_min;
        sign *= -1;
      }
      break;
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) throw std::logic_error("Matrix must be N x N size");
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = calcMinor(i, j);
      double calc = minor.Determinant();
      if ((i + j) % 2 != 0) calc *= -1;
      result(i, j) = calc;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) throw std::logic_error("Matrix must be N x N size");
  double determinant = Determinant();
  if (determinant == 0) throw std::logic_error("Determinant must be non-zero");
  S21Matrix matr_complements = CalcComplements();
  S21Matrix result = matr_complements.Transpose();
  result *= (1 / determinant);
  return result;
}

void S21Matrix::AllocateMemory(int rows, int cols) {
  matrix_ = new double*[rows];
  for (int i = 0; i < rows; ++i) {
    try {
      matrix_[i] = new double[cols]();
    } catch (std::bad_alloc&) {
      for (int j = 0; j < i; ++j) {
        delete[] matrix_[j];
      }
      delete[] matrix_;
      throw std::out_of_range("Memory allocation error");
    }
  }
}

void S21Matrix::DeallocateMemory() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < GetRows(); ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

// Для отладки
void S21Matrix::PrintMatrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
