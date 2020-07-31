/**
 * @file classic_solver.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-31
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __WILLS_SUDOKU_CLASSIC_SOLVER
#define __WILLS_SUDOKU_CLASSIC_SOLVER
#include<string>
#include<memory>
#include "solver.hpp"

using namespace std;
namespace wills::sudoku
{
    class classic_solver:public solver
    {
        public:
        string get_name() const noexcept override{
            return "classic";
        }
        shared_ptr<board> solve(shared_ptr<board>)const override;
    };
}

#endif