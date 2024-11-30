//
// Created by croshaw on 11/30/24.
//

#ifndef LAB4_BLOCK_HPP
#define LAB4_BLOCK_HPP

#include <omp.h>
#include "base.hpp"

class block : public base {
protected:
    void find_min() override {
        int totalThreads = omp_get_num_threads();
#ifdef INNER_FOR
        int size = ROWS;
#else
        int size = ROWS*COLUMNS;
#endif
#pragma omp parallel
        {
            int curThread = omp_get_thread_num();
            int blockSize = (size-1) / totalThreads+1;
            int ibeg = curThread * blockSize;
            int iend = ibeg + blockSize;
            if(ibeg > size) {
                iend = ibeg - 1;
            } else if (iend > size) {
                iend = size - 1;
            }
            for(; ibeg < iend; ibeg++) {
#ifdef INNER_FOR
                for(int j = 0; j < COLUMNS; j++) {
                    if (_min[ibeg] > _matrix[ibeg][j])
                        _min[ibeg] = _matrix[ibeg][j];
                }
#else
                int row = ibeg / COLUMNS;
                int col = ibeg - (row*COLUMNS);
                if(_min[row] > _matrix[row][col])
#pragma omp critical
                    _min[row] = _matrix[row][col];
#endif
            }
        }
    }
public:
    block(const base& source) : base(source) { init(); }
};


#endif //LAB4_BLOCK_HPP
