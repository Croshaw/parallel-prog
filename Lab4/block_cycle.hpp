//
// Created by croshaw on 11/30/24.
//

#ifndef LAB4_BLOCK_CYCLE_HPP
#define LAB4_BLOCK_CYCLE_HPP

#include <omp.h>
#include "base.hpp"

#define BLOCK_COUNT 16

class block_cycle : public base {
protected:
    void find_min() override {
#ifdef INNER_FOR
        int size = ROWS;
#else
        int size = ROWS*COLUMNS;
#endif
        int totalThreads = omp_get_num_threads();
        int blockSize = size / BLOCK_COUNT;
        if(size % BLOCK_COUNT != 0) {
            blockSize++;
        }

#pragma omp parallel
        {
            int curThread = omp_get_thread_num();
            for(int blockId = curThread; blockId < BLOCK_COUNT; blockId+=totalThreads) {
                int start = blockId * blockSize;
                int end = std::min(start+blockSize, size);
#ifdef INNER_FOR
                for(;start < end; start++) {
                    for(int j = 0; j < COLUMNS; j++) {
                        if (_min[start] > _matrix[start][j])
                            _min[start] = _matrix[start][j];
                    }
                }
#else
                for(;start < end; start++) {
                    int row = start / COLUMNS;
                    int col = start - (row*COLUMNS);
                    if(_min[row] > _matrix[row][col])
#pragma omp critical
                        _min[row] = _matrix[row][col];
                }
#endif
            }
        }
    }
public:
    block_cycle(const base& source) : base(source) { init(); }
};


#endif //LAB4_BLOCK_CYCLE_HPP
