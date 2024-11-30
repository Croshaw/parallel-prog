//void
// Created by croshaw on 11/28/24.
//

#ifndef LAB4_BASE_HPP
#define LAB4_BASE_HPP
#include <iostream>
#include <vector>
#include <ctime>
#include "settings.hpp"

class base {
private:
    bool _is_filled;
    void fill() {
        for(int i = 0 ; i < ROWS; i++) {
            for(int j = 0; j < COLUMNS; j++) {
                _matrix[i][j] = rand() % (MAX - MIN + 1) + MIN;
            }
        }
        _is_filled = true;
    }
    void hz() {
#ifdef USE_OMP_WTIME
        double start = omp_get_wtime();
#else
        time_t start = clock();
#endif
        find_min();
#ifdef USE_OMP_WTIME
        _time = (omp_get_wtime() - start)* 1000;
#else
        _time = (double)(clock() - start) / CLOCKS_PER_SEC * 1000;
#endif
    }
protected:
    std::vector<std::vector<int>> _matrix;
    std::vector<int> _min;
    double _time;
    virtual void find_min() {
        for(int i = 0; i < ROWS; i++) {
            int min = _matrix[i][0];
            for(int j = 1; j < COLUMNS; j++) {
                if(_matrix[i][j] < min) {
                    min = _matrix[i][j];
                }
            }
            _min[i] = min;
        }
    }
public:
    base() : _matrix(ROWS, std::vector<int>(COLUMNS)), _min(ROWS, MAX) {

    }
    base(const std::vector<std::vector<int>>& matrix) : _matrix(matrix), _min(ROWS, MAX) {
        _is_filled = true;
    }
    base(const base& source) : base(source._matrix) {
    }
    double get_time() const {
        return _time;
    }
    void init() {
        if(!_is_filled)
            fill();
        hz();
    }
    void print_time() const {
        std::cout << "Время выполнения: " << _time << " мс." << std::endl;
    }
    void print_min() const {
        for(int i = 0; i < ROWS; i++) {
            std::cout << _min[i] << std::endl;
        }
    }
    void print() const {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                std::cout << _matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
    bool equal_min(const base& other) const {
        if(other._min.size() != _min.size())
            return false;
        for(int i = 0; i < _min.size(); i++) {
            if(_min[i] != other._min[i])
                return false;
        }
        return true;
    }
};


#endif //LAB4_BASE_HPP
