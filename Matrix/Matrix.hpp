#pragma once

#include <cmath>
#ifdef MATRIX_TESTING
#include <iostream>
#include <iomanip>
#include <string>
#endif
#include <cfloat>
#include <cstring>
#include <array>
#include <vector>


template<class T, size_t R, size_t C>
class Matrix {
  private: 
    std::array<std::array<T,C>, R> m;

  public:

    /// @brief Default Constructor
    Matrix() : m{} {}

    /// ****************************************************************
    /// Copy Constructors which take constant dimension input arguments
    ///
    /// All functions which take a fixed size container as an argument
    ///  will be evaluated for size consistency with the underlying
    ///  matrix at compile time.
    /// If a Matrix of the wrong dimensions is provided, there will
    ///  be no member function with the correct signature, and compilation
    ///  will fail.

    /// @brief 2D c-array copy-constructor
    /// @param const T init[R][C] 
    Matrix(const T init[R][C]) : m(init) {}
  
    /// @brief 1D c-array copy-constructor (vectors only, C==1)
    /// @param const T init[R]
    Matrix(const T init[R]) : Matrix() {
      static_assert(C==1, "Matrix: cannot use single dimension c-array constructor for non-vector matrix with columns greater than 1");
      for (int i=0; i<R;i++) {
        m[i][0] = init[i];
      }
    }

    /// @brief 2D std::array copy-constructor
    /// @param const std::array<std::array<T,C>, R>& init
    Matrix(const std::array<std::array<T,C>, R>& init) : m(init) {}

    /// @brief 1D std::array copy-constructor (vectors only, C==1)
    /// @param const std::array<T,R>& init
    Matrix(const std::array<T,R>& init) : Matrix() {
      static_assert(C==1, "Matrix: cannot use single dimension std::array constructor for non-vector matrix with columns greater than 1");
      for (int i=0; i<R;i++) {
        m[i][0] = init[i];
      }
    }

    /// @brief 2D Matrix copy-constructor
    /// @param const Matrix<T,R,C>& init 
    Matrix(const Matrix<T,R,C>& init) : Matrix(init.m) {}

    /// ****************************************************************
    /// Copy Constructors which take variable dimension input arguments
    ///
    /// variable length input arguments, such as std::vector<std::vector<T>>,
    ///  std::initializer_list<std::initializer_list<T>>), or T**
    ///  should be used with caution, as there is both the potential for memory 
    ///  corruption with T**, and a performance overhead to check overruns with 
    //// std::initializer_list / std::vector

    /// @brief 2D std::initializer_list copy-constructor
    /// @param std::initializer_list<std::initializer_list<T>> init
    Matrix(std::initializer_list<std::initializer_list<T>> init) : Matrix() {
      if(init.size() != R) {
        throw std::runtime_error(
          "Matrix: attempted to initialize matrix with 2D std::initializer_list constructor\n"
          "of incorrect size\n"
          "std::initializer_list argument has " + std::to_string(init.size()) + " rows\n"
          "this matrix has " + std::to_string(R) + " rows" );
      }
      for (auto it_row = init.begin(); it_row != init.end(); ++it_row) {
        if(it_row->size() != C) {
          throw std::runtime_error(
            "Matrix: attempted to initialize matrix with 2D std::initializer_list constructor\n"
            "of incorrect size\n"
            "row " + std::to_string(it_row-init.begin()) + " of std::initializer_list argument has " + std::to_string(it_row->size()) + " columns\n"
            "this matrix has " + std::to_string(C) + " columns" );
        }
      }
      for(auto it_row = init.begin(); it_row-init.begin()<R; ++it_row) {
        for(auto it_col = it_row->begin(); it_col-it_row->begin()<C; ++it_col) {
          m[it_row-init.begin()][it_col-it_row->begin()] = *it_col;
        }
      }
    }

    /// @brief 1D std::initializer_list copy-constructor (vectors only, C==1)
    /// @param std::initializer_list<T> init
    Matrix(std::initializer_list<T> init) : Matrix() {
      static_assert(
        C==1, 
        "Matrix: cannot use single dimension std::initializer_list constructor\n"
        "for non-vector matrix with columns greater than 1");
      if(init.size() != R) {
        throw std::runtime_error(
          "Matrix: attempted to initialize matrix with 1D std::vector constructor\n"
          "of incorrect size\n"
          "std::initializer_list argument has " + std::to_string(init.size()) + " rows\n"
          "this matrix has " + std::to_string(R) + " rows" );
      }
      for(auto it = init.begin(); it-init.begin()<R; ++it) {
        m[it-init.begin()][0] = *it;
      }
    }

    /// @brief 2D std::vector copy-constructor
    /// @param std::vector<std::vector<T>> init
    Matrix(std::vector<std::vector<T>> init) : Matrix() {
      if(init.size() != R) {
        throw std::runtime_error(
          "Matrix: attempted to initialize matrix with 2D std::vector constructor\n"
          "of incorrect size\n"
          "std::vector argument has " + std::to_string(init.size()) + " rows\n"
          "this matrix has " + std::to_string(R) + " rows" );
      }
      for (size_t i=0; i<R; i++) {
        if(init[i].size() != C) {
          throw std::runtime_error(
            "Matrix: attempted to initialize matrix with 2D std::vector constructor\n"
            "of incorrect size\n"
            "row " + std::to_string(i) + " of std::vector argument has " + std::to_string(init[i].size()) + " columns\n"
            "this matrix has " + std::to_string(C) + " columns" );
        }
      }

      for(size_t i=0; i<R; i++) {
        std::memcpy(this->m[i].data(), init[i].data(), sizeof(T)*C);
      } 
    }

    /// @brief 1D std::vector copy-constructor (vectors only, C==1)
    /// @param std::vector<T> init
    Matrix(std::vector<T> init) : Matrix() {
      static_assert(
        C==1, 
        "Matrix: cannot use single dimension std::vector constructor\n"
        "for non-vector matrix with columns greater than 1");
      if(init.size() != R) {
        throw std::runtime_error(
          "Matrix: attempted to initialize matrix with 1D std::vector constructor\n"
          "of incorrect size\n"
          "std::vector argument has " + std::to_string(init.size()) + " rows\n"
          "this matrix has " + std::to_string(R) + " rows" );
      }
      for(size_t i=0; i<R; i++) {
        m[i][0] = init[i];
      }
    }

#ifdef MATRIX_ENABLE_UNSAFE_CONSTRUCTORS

    /// @brief 2D T** copy-constructor
    /// Note: This is an unsafe constructor, as there is no way to bounds check
    ///       the input argument
    /// 
    /// @param T** init - pointer to the beginning of an array of R pointers to T
    ///                   (one array of pointers for each row in the Matrix)
    ///                   Each of the R pointers to T, points to the beggining of
    ///                   an array of C elements of type T
    ///                   (one array of elements of type T for each column in the Matrix)
    /// Note: T** is a double pointer to T, **not** a 2D array of type T
    ///       Unlike a 2D array (int foo[R][C];) where foo == foo[0], init != init[0]
    Matrix(T** init) : Matrix() {
      for(size_t i=0; i<R; i++) {
        std::memcpy(this->m[i].data(), init[i], sizeof(T)*C);
      } 
    }

    /// @brief 1D T* copy-constructor
    /// Note: This is an unsafe constructor, as there is no way to bounds check
    ///       the input argument
    /// @param T* init - pointer to the beginning of an array of R elements of type T
    ///                   (one array of elements of type T for each row in the Matrix)
    Matrix(T* init) : Matrix() {
      static_assert(C==1, "Matrix: cannot use single dimension T* constructor for non-vector matrix with columns greater than 1");
      std::memcpy(m[0].data(), init, sizeof(T) * R);
    }

#endif

    /// @brief swap member function
    /// @param Matrix<T,R,C>& rhs 
    void swap(Matrix<T,R,C>& rhs) {
      std::swap(this->m, rhs.m);
    }

    /// @brief 2D std::initializer_list assignment operator
    /// @param std::initializer_list<std::initializer_list<T>> init 
    /// @return Matrix<T,R,C>
    Matrix<T,R,C> operator=(std::initializer_list<std::initializer_list<T>> init) {
      Matrix<T,R,C> temp(init);
      this->swap(temp);
      return *this;
    }

    /// @brief 1D std::initializer_list assignment operator (vectors only, C==1)
    /// @param std::initializer_list<T> init 
    /// @return Matrix<T,R,C>
    Matrix<T,R,C> operator=(std::initializer_list<T> init) {
      Matrix<T,R,C> temp(init);
      this->swap(temp);
      return *this; 
    }

    
    /// static_asserts are not required to ensure that the rows and columns of 
    ///  each operand are equal for the addition and substraction operators.
    /// This is similarly the case for the multiplication operator wrt the
    ///  columns of the left-hand matrix versus the rows of the right-hand matrix.
    ///
    /// SFINAE (substitution failure is not an error) will prevent a function 
    ///  from being considered if the template parameters cannot be properly substituted.
    ///  This will cause a compile-time failure if matrices of invalid dimensions are
    ///  operated upon.
    
    /// @brief Addition Operator
    /// @param const Matrix<T,R,C>& rhs 
    /// @return Matrix<T,R,C>
    Matrix<T,R,C> operator+(const Matrix<T,R,C>& rhs) const {
      Matrix<T,R,C> result;
      for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
          result.m[i][j] = this->m[i][j] + rhs[i][j];
        }
      }
      return result;
    }

    /// @brief Addition assingment operator
    /// @param rhs const Matrix<T,R,C>& rhs
    /// @return Matrix<T,R,C>&
    Matrix<T,R,C>& operator+=(const Matrix<T,R,C>& rhs) {
      *this = *this + rhs;
      return *this;
    }
    
    /// @brief Subtraction Operator
    /// @param const Matrix<T,R,C>& rhs 
    /// @return Matrix<T,R,C>
    Matrix<T,R,C> operator-(const Matrix<T,R,C>& rhs) const {
      Matrix<T,R,C> result = { { 0 } };
      for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
          result.m[i][j] = this->m[i][j] - rhs[i][j];
        }
      }
      return result;
    }

    /// @brief Subtraction assingment operator
    /// @param const Matrix<T,R,C>& rhs 
    /// @return Matrix<T,R,C>&
    Matrix<T,R,C>& operator-=(const Matrix<T,R,C>& rhs) {
      *this = *this - rhs;
      return *this;
    }

    /// @brief Matrix Multiplication Operator
    /// @tparam Rrhs 
    /// @tparam Crhs 
    /// @param const Matrix<T,Rrhs,Crhs>& rhs 
    /// @return Matrix<T,R,Crhs>
    template<size_t Rrhs = C, size_t Crhs> 
    Matrix<T,R,Crhs> operator*(const Matrix<T,Rrhs,Crhs>& rhs) const {
      Matrix<T,R,Crhs> result;
      for (int i=0; i<R; i++) {
        for (int j=0; j<Crhs; j++) {
          for (int k=0; k<C; k++) {
            result(i,j) += (*this)(i,k) * rhs(k,j);
          }
        }
      }
      return result;
    }

    /// @brief Matrix Multiplication assingment operator
    /// Square matrices only, as matrix dimensions are immutable
    /// @param const Matrix<T,R,C>& rhs 
    /// @return Matrix<T,R,C>&
    Matrix<T,R,C>& operator*=(const Matrix<T,R,C>& rhs) {
      static_assert(R==C, "Matrix: attempted to multiply assign non-square matrix!");
      *this = *this * rhs;
      return *this;
    }

    /// Note: 
    /// Member function scalar multiplication operators do not follow the
    ///  typical order of operations which expects a scalar to be placed to the
    ///  left of the matrix it multiplies

    /// @brief Scalar Multiplication assingment operator
    /// @param T scalar 
    /// @return Matrix<T,R,C>&
    Matrix<T,R,C>& operator*=(T scalar) {
      for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
          (*this)(i,j) *= scalar;
        }
      }
      return *this;
    }

    /// @brief Scalar Multiplication operator (member function)
    /// @param T scalar 
    /// @return Matrix<T,R,C>
    Matrix<T,R,C> operator*(T scalar) const {
      Matrix<T,R,C> result(*this);
      
      return result *= scalar;
    }

    /// @brief Scalar Multiplication operator (friend function)
    /// @param T scalar 
    /// @param const Matrix<T,R,C>& matrix 
    /// @return Matrix<T,R,C>
    friend Matrix<T,R,C> operator*(T scalar, const Matrix<T,R,C>& matrix) {
      return matrix * scalar;
    }

    /// @brief Matrix Division Operator
    /// There is not technically such a thing as matrix 'division'
    ///  This function rather computes the inverse of the 'divisor' 
    ///  and multiplies it by the 'dividend'
    /// @tparam Rrhs 
    /// @tparam Crhs 
    /// @param const Matrix<T,Rrhs,Crhs>& rhs 
    /// @return Matrix<T,R,Crhs>
    template<size_t Rrhs = C, size_t Crhs> 
    Matrix<T,R,Crhs> operator/(const Matrix<T,Rrhs,Crhs>& divisor) const {
      return *this * divisor.Inverse();
    }

    /// @brief Matrix Division assingment operator
    /// Square matrices only, as matrix dimensions are immutable
    /// @param const Matrix<T,R,C>& rhs 
    /// @return Matrix<T,R,C>&
    Matrix<T,R,C>& operator/=(const Matrix<T,R,C>& rhs) {
      static_assert(R==C, "Matrix: attempted to divide assign non-square matrix!");
      *this = *this / rhs;
      return *this;
    }

    /// Note:
    /// 'const' qualified Member Access operators will be selected when 
    ///  retrieving member objects from 'const' declared Matrices & Vectors

    /// @brief Constant [2D] Member Access Operator (implemented using '()' operator)
    /// @param size_t row 
    /// @param size_t col 
    /// @return const T&
    const T& operator()(size_t row, size_t col) const {
      return m[row][col];
    }

    /// @brief Mutable [2D] Member Access Operator (implemented using '()' operator) 
    /// @param size_t row 
    /// @param size_t col 
    /// @return T&
    T& operator()(size_t row, size_t col) {
      return m[row][col];
    }

    /// @brief Constant [1D / Vector]  Member Access Operator (implemented using '()' operator)
    /// @param size_t row 
    /// @return const T& 
    const T& operator()(size_t row) const {
      static_assert(C==1, "Attempted to access vector member in Matrix with columns greater than 1!");
      return m[row][0];
    }

    /// @brief Mutable [1D / Vector] Member Access Operator (implemented using '()' operator)
    /// @param size_t row 
    /// @return T&
    T& operator()(size_t row) {
      static_assert(C==1, "Matrix: attempted to access vector member in Matrix with columns greater than 1!");
      return m[row][0];
    }

    /// @brief  Calculate Matrix Determinant
    /// Requires locally defined non-member function to ensure that compile time recursion is terminated
    ///  at the appropriate depth. This is ensured by using multiple overloads of the locally defined
    ///  _MatrixDeterminant(Matrix<T,R,C>) function which have specifcally sized Matrix input parameters.
    ///  The correct function is then selected at compile time via overload resolution.  
    /// @return T 
    T Determinant() const {
      static_assert(R==C, "Matrix: attempted to calculate determinant of non-square matrix!");
      
      return _MatrixDeterminant(*this);
    }

    /// @brief Find the minor component for any component of this matrix
    /// @param size_t row 
    /// @param size_t col 
    /// @return T
    T Minor(size_t row, size_t col) const {
      static_assert(R==C, "Matrix: calculating the Minor of a non-square matrix is not supported");
      Matrix<T,R-1,C-1> temp;
      int iOffset = 0;
      for(size_t i=0; i<R; i++) {
        if(i==row) {
          iOffset=1;
          continue;
        }
        int jOffset = 0;
        for(size_t j=0; j<C; j++) {
          if(j==col) {
            jOffset=1;
            continue;
          }
          temp(i-iOffset,j-jOffset) = (*this)(i,j);
        }
      }
      return temp.Determinant();
    }

    /// @brief Compute the Transpose of this Matrix
    /// @return Matrix<T,C,R>
    /// Note: R & C are swapped in the template instantiation of the return/result types
    ///       because the output will have the same number of rows as the input has 
    ///       columns, and visa versa
    Matrix<T,C,R> Transposed() const {
      Matrix<T,C,R> result(*this);
      for (size_t i=0; i<R; i++) {
        for (size_t j=i; j<C; j++) {
          result(i,j) = (*this)(j,i);
        }
      }
      return result;
    }

    /// @brief Transpose this Matrix
    /// @return Matrix<T,C,R>
    /// Note: Can only transpose in place a square matrix
    Matrix<T,C,R>& Transpose() {
      static_assert(R==C, "Matrix: Cannot transpose in place a non-square matrix");
      for (size_t i=0; i<R; i++) {
        for (size_t j=i; j<C; j++) {
          std::swap((*this)(i,j), (*this)(j,i));
        }
      }
      return *this;
    }

    /// @brief Compute the Adjoint of this Matrix
    /// @return Matrix<T,R,C>
    Matrix<T,R,C> Adjoint() const {
      static_assert(R==C, "Matrix: adjoint of non-square matrix is not supported!");

      Matrix<T,R,C> result;

      for (size_t i=0; i<R; i++) {
        for (size_t j=0; j<C; j++) {
          result(i,j) = pow(-1,i+j) * this->Minor(i,j);
        }
      }
      return result.Transpose();
    }

    /// @brief Compute the Inverse of this Matrix
    /// @return Matrix<T,R,C>
    Matrix<T,R,C> Inverse() const {
      static_assert(R==C, "Matrix: attempted to find inverse of non-square matrix!");
      T determinant = this->Determinant();
      if ( determinant == 0 ) {
        throw std::runtime_error("Matrix: cannot find Inverse of this matrix, determinant is zero!");
      }

      T determinantInverse = 1.0 / determinant;

      return determinantInverse * this->Adjoint();
    }

    /// @brief Invert this Matrix
    /// @return Matrix<T,R,C>
    Matrix<T,R,C>& Invert() {
      return *this = this->Inverse();
    }

    /// @brief Normalize the columns of this matrix such that their sums are all eqaul to 1
    /// @return Matrix<T,R,C>
    Matrix<T,R,C>& Normalize() {
      for (size_t j=0; j < C; j++) {
        double sum = 0;
        for (size_t i=0; i < R; i++) {
          sum += (*this)(i,j);
        }
        for (int i=0; i < R; i++) {
          (*this)(i,j) /= sum;
        }
      }
      return *this;
    }

    /// @brief Find the normalized vector and return it
    /// @return Matrix<T,R,C>
    Matrix<T,R,C> Normalized() const {
      Matrix<T,R,C> result(*this);
      return result.Normalize();
    }

#ifdef MATRIX_TESTING
    /// @brief Pretty Print a matrix
    void Print() const {
      std::cout << "matrix: " << R << " x " << C << std::endl;
      std::cout << "[ ";
      for (size_t i=0; i<R; i++) {
        if (i > 0) {
          std::cout << "  ";
        }
        std::cout << "[ ";
        for (size_t j=0; j<C; j++) {
          std::cout << std::setw(12) << std::setprecision(6) << (*this)(i,j) << " ";
          if(j < C-1) {
            std::cout << ", ";
          }
        }
        std::cout << "]";
        if(i < R-1) {
          std::cout << "," << std::endl;
        }
      }
      std::cout << " ]" << std::endl;
    }
#endif
};

namespace std {
  template<class T, size_t R, size_t C>
  void swap(Matrix<T,R,C>& lhs, Matrix<T,R,C>& rhs) {
    lhs.swap(rhs);
  }
}

/// @brief using declaration to allow declaring a vector like Vector<type,rows>
/// @tparam T matrix contained type
/// @tparam R rows
template<class T, size_t R>
using Vector = Matrix<T,R,1>;

/// @brief Calculate the determinant of a 0x0 matrix
/// @tparam T matrix contained type
/// @param const Matrix<T,0,0>& matrix
/// @return T
template<class T>
static inline T _MatrixDeterminant(const Matrix<T,0,0>& matrix) {
  return 1;
}

/// @brief Calculate the determinant of a 1x1 matrix
/// @tparam T matrix contained type
/// @param const Matrix<T,1,1>& matrix
/// @return T
template<class T>
static inline T _MatrixDeterminant(const Matrix<T,1,1>& matrix) {
  return matrix(0,0);
}

/// @brief Calculate the determinant of a 2x2 matrix
/// @tparam T matrix contained type
/// @param const Matrix<T,2,2>& matrix
/// @return T
template<class T>
static inline T _MatrixDeterminant(const Matrix<T,2,2>& matrix) {
  return matrix(0,0) * matrix(1,1) - matrix(0,1) * matrix(1,0);
}

/// @brief Calculate the determinant of a nxn matrix
/// @tparam T matrix contained type
/// @param const Matrix<T,R,C>& matrix
/// @return T
template<class T, size_t R, size_t C>
static inline T _MatrixDeterminant(const Matrix<T,R,C>& matrix) {
  constexpr size_t D = R;
  T result = 0;

  for(size_t i = 0; i < D; i++) {
    Matrix<T,R-1,C-1> subMatrix;
    for(int j = 1; j < D; j++) {
        int z = 0;
        for(int k = 0; k < D; k++) {
            if(k != i) {
                subMatrix(j-1,z) = matrix(j,k);
                z++;
            }
        }
    }
    
    //recursive call
    result += pow(-1,i) * matrix(0,i) * subMatrix.Determinant();
  }
  return result;
}
