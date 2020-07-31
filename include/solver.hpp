/**
 * @file solver.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-31
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __WILLS_SUDOKU_SOLVER
#define __WILLS_SUDOKU_SOLVER
#include<string>
#include<memory>
#include "board.hpp"

using namespace std;
namespace wills::sudoku
{
    class solver
    {
        public:
        virtual string get_name() const noexcept = 0;
        virtual shared_ptr<board> solve(shared_ptr<board>)const =0;
    };
}

#endif