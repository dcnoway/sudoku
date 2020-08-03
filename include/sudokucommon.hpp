/**
 * @file sudokucommon.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-08-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __WILLS_SUDOKU_COMMON_DEFINETIONS
#define __WILLS_SUDOKU_COMMON_DEFINETIONS
namespace wills::sudoku
{
    /**
     * @brief sudoku type defines
     * 
     */
    using sudoku_type = unsigned;
    constexpr unsigned Classic =                0x00000001;
    constexpr unsigned Jiagsaw =                0x00000002;
    constexpr unsigned Diagonal =               0x00000004;
    constexpr unsigned Addsum =                 0x00000008;
    constexpr unsigned NeighbourDifference =    0x00000010;

    //TODO: MERGE conflict between sudoku_cell_t here and cell_value_t in classic_board
    using sudoku_cell_t = int;
}
#endif