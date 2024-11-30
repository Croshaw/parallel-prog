//
// Created by croshaw on 11/30/24.
//

#ifndef LAB4_CYCLE_FOR_HPP
#define LAB4_CYCLE_FOR_HPP


#include "base.hpp"
class cycle_for : public base {
protected:
    void find_min() override {
#pragma omp parallel
        {
#ifdef INNER_FOR
#pragma omp for
            for(int i = 0; i < ROWS; i++) {
                for(int j = 0 ; j < COLUMNS; j++) {
                    if (_min[i] > _matrix[i][j])
                        _min[i] = _matrix[i][j];
                }
            }
#else
#pragma omp for
            for(int i = 0; i < ROWS*COLUMNS; i++) {
                int row = i / COLUMNS;
                int col = i - (row*COLUMNS);
                if(_min[row] > _matrix[row][col])
#pragma omp critical
                    _min[row] = _matrix[row][col];
            }
#endif
        }
    }
public:
    cycle_for(const base& source) : base(source) { init(); }
};


#endif //LAB4_CYCLE_FOR_HPP
