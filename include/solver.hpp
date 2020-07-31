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
    /**
     * @brief abstract class, like a interface
     * 
     */
    class solver
    {
        public:
        /**
         * @brief Get the name object
         * 
         * @return string 
         */
        virtual string get_name() const noexcept = 0;
        /**
         * @brief solve 
         * 
         * @param board a unsolved sudoku board
         * @return shared_ptr<board> 
         */
        virtual shared_ptr<board> solve(shared_ptr<board> board)const =0;
    };
}

#endif