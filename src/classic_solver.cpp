/**
 * @file classic_solver.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-31
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "classic_solver.hpp"
#include "classic_board.hpp"
#include "dlx.hpp"

using namespace std;
using namespace wills::dlx;
namespace wills::sudoku
{
    shared_ptr<board> classic_solver::solve(shared_ptr<board> board)const
    {
        classic_board * pb = dynamic_cast<classic_board*>(board.get());
        dlx::dancing_links<cell_value_t> dlx;
        // pb->
        
        //Rule 1: every cell has a number

        //Rule 2: every line contains every number in [1,col_size]

        //Rule 3: every column contains every number in [1,row_size]

        //Rule 4: every rectangle region contains every number in [1,col_size]


        return nullptr;
    }

}