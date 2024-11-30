//
// Created by croshaw on 11/28/24.
//

#ifndef LAB4_SETTINGS_HPP
#define LAB4_SETTINGS_HPP

#define INNER_FOR
#define USE_OMP_WTIME
#if defined(_WIN32) || defined(WIN32)
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

static const int ROWS = 5000;
static const int COLUMNS = 8000;

static const int MIN = -5000;
static const int MAX = 5000;
#endif //LAB4_SETTINGS_HPP
