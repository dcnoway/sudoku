/**
 * @file classic_rule.cpp
 * @author Will Wu(willswu@outlook.com)
 * @brief Four classic sudoku rules
 * @version 0.1
 * @date 2020-08-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include<memory>
#include "classic_rule.hpp"
using namespace std;
using namespace wills::dlx;
namespace wills::sudoku::rules
{
    size_t every_cell_must_has_a_number::dlx_cols(const rectangle_region &board_shape) const
    {
        return board_shape.size();
    }
    value_t<cell_value_t> every_cell_must_has_a_number::generate(const rectangle_region & board_shape, const coordinate & coords, cell_value_t cellval) const
    {
        value_t<cell_value_t> result;
        result.val = cellval;
        result.col = board_shape.coords2index(coords.col, coords.row) + 1;
        return result;
    }
    pair<coordinate, cell_value_t> every_cell_must_has_a_number::parse(const rectangle_region & board_shape, value_t<cell_value_t> cell) const
    {
        return {board_shape.index2coords(cell.col - 1),cell.val};
    }

    /**********************************************************************************************/
    size_t no_duplicated_number_in_row::dlx_cols(const rectangle_region &board_shape) const
    {
        return board_shape.cells_per_row() * board_shape.cells_per_row();
    }

    value_t<cell_value_t> no_duplicated_number_in_row::generate(const rectangle_region & board_shape, const coordinate & coords, cell_value_t cellval) const
    {
        value_t<cell_value_t> result;
        if(cellval > 0){
            result.val = cellval;
            // row 1 has 1,row 1 has 2,row 1 has 3...,row 1 has cells_per_row, row has 1, row 2 has 2...
            result.col = board_shape.cells_per_row() * (coords.row -1) + cellval;
        }
        else if(cellval == 0){
            for(cell_value_t i = 1;i<=board_shape.cells_per_row();++i){
                result.col = board_shape.cells_per_row() * (coords.row -1) + i;
                result.val = cellval;
            }
        }
        else{
            throw logic_error("Not implemented yet. Negative cell value reserved for variant sudoku.");
        }
        return result;
    }
    pair<coordinate, cell_value_t> no_duplicated_number_in_row::parse(const rectangle_region & board_shape, value_t<cell_value_t> cell) const
    {
    }

    /**********************************************************************************************/
    size_t no_duplicated_number_in_col::dlx_cols(const rectangle_region &board_shape) const
    {
        return board_shape.cells_per_col() * board_shape.cells_per_col();
    }
    value_t<cell_value_t> no_duplicated_number_in_col::generate(const rectangle_region & board_shape, const coordinate & coords, cell_value_t cellval) const
    {
        value_t<cell_value_t> result;
        if(cellval > 0){
            result.val = cellval;
            // row 1 has 1,row 1 has 2,row 1 has 3...,row 1 has cells_per_row, row has 1, row 2 has 2...
            result.col = board_shape.cells_per_col() * (coords.col -1) + cellval;
        }
        else if(cellval == 0){
            for(cell_value_t i = 1;i<=board_shape.cells_per_col();++i){
                result.col = board_shape.cells_per_col() * (coords.col -1) + i;
                result.val = cellval;
            }
        }
        else{
            throw logic_error("Not implemented yet. Negative cell value reserved for variant sudoku.");
        }
        return result;
    }
    pair<coordinate, cell_value_t> no_duplicated_number_in_col::parse(const rectangle_region & board_shape, value_t<cell_value_t> cell) const
    {
    }

    /**********************************************************************************************/
    size_t no_duplicated_number_in_region::dlx_cols(const rectangle_region &board_shape)const
    {
        //TODO: amount of regions * how many cells per region
    }
    value_t<cell_value_t> no_duplicated_number_in_region::generate(const rectangle_region & board_shape, const coordinate & coords, cell_value_t cellval) const
    {
        //TODO: region index of cell * how many cells per region + cellval;
    }
    pair<coordinate, cell_value_t> no_duplicated_number_in_region::parse(const rectangle_region & board_shape, value_t<cell_value_t> cell) const
    {
    }
    
} // namespace wills::sudoku
