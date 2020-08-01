/**
 * @file classic_solver.cpp
 * @author Will Wu (willswu@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-31
 * 
 * @copyright Copyright (c) Will Wu 2020
 * 
 */

#include "classic_solver.hpp"
#include "classic_board.hpp"
#include "dlx.hpp"

using namespace std;
using namespace wills::dlx;
namespace wills::sudoku
{
    shared_ptr<board> classic_solver::solve(shared_ptr<board> board) const
    {
        if (board == nullptr)
        {
            cerr << "Call classic_solver::solve() with a nullptr param." << endl;
            return nullptr;
        }
        classic_board *pb = dynamic_cast<classic_board *>(board.get());
        dlx::dancing_links<cell_value_t> dlx;
        rectangle_region bshape = pb->shape();
        if (bshape.size() == 0)
        {
            cerr << "Call classic_solver::solve() with a empty sudoku board." << endl;
            return nullptr;
        }

        size_t dlxcol   = bshape.size() 
                        + bshape.colsize() * bshape.colsize() 
                        + bshape.rowsize() * bshape.rowsize() 
                        + pb->regions().size() * bshape.colsize();

        dlx.init_cols(dlxcol);

        for (size_t i = 0; i < bshape.size(); ++i)
        {
            // coordinate coords = pb->index2coords(i);
            // dlx::value_t<cell_value_t> dlxrowbuf[4];    //4 group of rules for classic sudoku board
            //Rule 1: every cell has a number

            //Rule 2: every line contains every number in [1,col_size]

            //Rule 3: every column contains every number in [1,row_size]

            //Rule 4: every rectangle region contains every number in [1,col_size]
        }
        return nullptr;
    }

} // namespace wills::sudoku