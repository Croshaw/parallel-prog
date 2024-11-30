//
// Created by croshaw on 11/28/24.
//

#ifndef LAB4_CYCLE_HPP
#define LAB4_CYCLE_HPP

#include <omp.h>
#include "base.hpp"

class cycle : public base {
protected:
    void find_min() override {
        int totalThreads = omp_get_num_threads();
#pragma omp parallel
        {
                int curThread = omp_get_thread_num();
#ifdef INNER_FOR
            for(int i = curThread; i < ROWS; i+=totalThreads) {
                for(int j = 0; j < COLUMNS; j++) {
                    if (_min[i] > _matrix[i][j])
                        _min[i] = _matrix[i][j];
                }
            }
#else
                for(int i = curThread; i < ROWS * COLUMNS; i+=totalThreads) {
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
    cycle(const base& source) : base(source) { init(); }
};


#endif //LAB4_CYCLE_HPP
