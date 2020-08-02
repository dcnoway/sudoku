/**
 * @file rule.hpp
 * @author Will Wu (willswu@outlook.com)
 * @brief The base class of all rule
 * @version 0.1
 * @date 2020-08-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __WILLS_SUDOKU_RULE
#define __WILLS_SUDOKU_RULE
#include "dlx.hpp"
#include "classic_board.hpp"
using namespace std;
using namespace wills::sudoku;
using namespace wills::dlx;
namespace wills::sudoku
{
    class rule
    {
        virtual size_t dlx_cols(const rectangle_region &board_shape) const = 0;
        virtual value_t<cell_value_t> generate(const rectangle_region & board_shape, const coordinate & coords, cell_value_t cellval) const = 0;
        virtual pair<coordinate, cell_value_t> parse(const rectangle_region & board_shape, value_t<cell_value_t> cell) const = 0;
    };

} // namespace wills::sudoku
#endif