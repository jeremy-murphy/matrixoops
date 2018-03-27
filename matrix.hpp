#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <cstdlib>
#include <iosfwd>
#include <iomanip>
#include <stdexcept>
#include <utility>
#include <type_traits>

namespace OOPS
{
    
// Keep it simple; can only be a matrix of PoD type.
template <typename T, int Rows, int Columns>
class Matrix
{
    template <typename U>
    class ColumnProxy
    {
    public:
        constexpr
        ColumnProxy(U *column) noexcept : column{column} {}
        
        constexpr
        U &operator[](int i) const noexcept
        {
            assert(i < Rows);
            return column[i];
        }
        
    private:
        U *column;
    };
    
public:
    constexpr
    void empty() noexcept(noexcept(std::declval<T&>() = std::declval<T&>()))
    {
        for (int i = 0; i != Rows; i++)
            for (int j = 0; j != Columns; j++)
                data_[j][i] = T(0);
    }
    
    // Unchecked read access.
    constexpr
    ColumnProxy<T const> operator[](int j) const noexcept(noexcept(ColumnProxy<T const>(nullptr)))
    {
        assert(j < Columns);
        return ColumnProxy<T const>(data_[j]);
    }

    // Unchecked write access.
    constexpr
    ColumnProxy<T> operator[](int j) noexcept(noexcept(ColumnProxy<T>(nullptr)))
    {
        assert(j < Columns);
        return ColumnProxy<T>(data_[j]);
    }
    
    // Checked write access.
    constexpr
    void setElement(int row, int col, T value)
    {
        if (row < 0 || row >= Rows)
            throw std::logic_error("Invalid row: " + std::to_string(row));
        if (col < 0 || col >= Columns)
            throw std::logic_error("Invalid column: " + std::to_string(col));
        data_[col][row] = value;
    }
    
    constexpr
    Matrix &operator+=(Matrix const &other)
    noexcept(noexcept(std::declval<T&>() += std::declval<T&>()))
    {
        for (int j = 0; j != Columns; j++)
            for (int i = 0; i != Rows; i++)
                data_[j][i] += other[j][i];
        return *this;
    }
    
private:
    T data_[Columns][Rows]; // Column-major storage.
};


template <typename T, int Rows, int Columns>
Matrix<T, Rows, Columns> operator+(Matrix<T, Rows, Columns> x, Matrix<T, Rows, Columns> const &y)
noexcept(noexcept(std::declval<Matrix<T, Rows, Columns>&>() += std::declval<Matrix<T, Rows, Columns> const &>()))
{
    x += y;
    return x;
}


template <typename T, int Rows, int Columns>
constexpr
bool operator==(Matrix<T, Rows, Columns> const &x, Matrix<T, Rows, Columns> const &y)
noexcept(noexcept(std::declval<T&>() != std::declval<T&>()))
{
    for (int j = 0; j < Columns; j++)
        for (int i = 0; i < Rows; i++)
            if (x[j][i] != y[j][i])
                return false;
    return true;
}

template <typename T, int Rows, int Columns>
constexpr
bool operator!=(Matrix<T, Rows, Columns> const &x, Matrix<T, Rows, Columns> const &y)
noexcept(noexcept(x == y))
{
    return !(x == y);
}


// 'print'
template <typename T, int Rows, int Columns>
std::ostream &operator<<(std::ostream &os, Matrix<T, Rows, Columns> const &A)
{
    for (int i = 0; i != Rows; i++)
    {
        for (int j = 0; j != Columns; j++)
            os << std::setw(5) << std::right << A[j][i];
        os << "\n";
    }
    return os;
}

} // namespace OOPS

#endif
