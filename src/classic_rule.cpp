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
#include "classic_rule.hpp"
using namespace std;
using namespace wills::dlx;
namespace wills::sudoku::rules
{
    void every_cell_must_has_a_number::attach(const std::shared_ptr<classic_board> &board)
    {
        this->board = board;
    }

    size_t every_cell_must_has_a_number::dlx_cols() const
    {
        return board->shape().size();
    }

    std::vector<row_t<sudoku_cell_t>> every_cell_must_has_a_number::generate_dlx_row() const
    {
        std::vector<row_t<sudoku_cell_t>> result;

        // result.val = cellval;
        // result.col = board_shape.coords2index(coords.col, coords.row) + 1;
        return result;
    }
    std::vector<classic_board> every_cell_must_has_a_number::parse_dlx_result(const std::vector<row_t<sudoku_cell_t>> &rslt) const
    {
        std::vector<classic_board> result;
        return result;
    }
    bool every_cell_must_has_a_number::check_answer(const std::shared_ptr<classic_board> &board)const
    {
        return false;
    }

    /**********************************************************************************************/
    void no_duplicated_number_in_row::attach(const std::shared_ptr<classic_board> &board)
    {
        this->board = board;
    }
    
    size_t no_duplicated_number_in_row::dlx_cols() const
    {
        return board->shape().cells_per_row() * board->shape().cells_per_row();
    }

    std::vector<row_t<sudoku_cell_t>> no_duplicated_number_in_row::generate_dlx_row() const
    {
        std::vector<row_t<sudoku_cell_t>> result;
        /* Logic for a single cell
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

        */
        return result;        
    }
    std::vector<classic_board> no_duplicated_number_in_row::parse_dlx_result(const std::vector<row_t<sudoku_cell_t>> & rslt) const
    {
        std::vector<classic_board> result;
        return result;
    }

    bool no_duplicated_number_in_row::check_answer(const std::shared_ptr<classic_board> &board) const
    {
        return false;
    }
    /**********************************************************************************************/
    void no_duplicated_number_in_col::attach(const std::shared_ptr<classic_board> &board)
    {
        this->board = board;
    }

    size_t no_duplicated_number_in_col::dlx_cols() const
    {
        return board->shape().cells_per_col() * board->shape().cells_per_col();
    }

    std::vector<row_t<sudoku_cell_t>> no_duplicated_number_in_col::generate_dlx_row() const
    {
        std::vector<row_t<sudoku_cell_t>> result;
        /*
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
        */
        return result;
    }

    std::vector<classic_board> no_duplicated_number_in_col::parse_dlx_result(const std::vector<row_t<sudoku_cell_t>> & rslt) const
    {
        std::vector<classic_board> result;
        // return make_pair<coordinate,cell_value_t>(coordinate{0,0},0);
        return result;
    }

    bool no_duplicated_number_in_col::check_answer(const std::shared_ptr<classic_board> &board) const
    {
        return false;
    }

    /**********************************************************************************************/
    void no_duplicated_number_in_region::attach(const std::shared_ptr<classic_board> &board)
    {
        this->board = board;
    }

    size_t no_duplicated_number_in_region::dlx_cols()const
    {
        //TODO: amount of regions * how many cells per region
        return 0;
    }

    std::vector<row_t<sudoku_cell_t>> no_duplicated_number_in_region::generate_dlx_row() const
    {
        //TODO: region index of cell * how many cells per region + cellval;
        std::vector<row_t<sudoku_cell_t>> result;
        return result;
    }

    std::vector<classic_board> no_duplicated_number_in_region::parse_dlx_result(const std::vector<row_t<sudoku_cell_t>> & rslt) const
    {
        std::vector<classic_board> result;
        // return make_pair<coordinate,cell_value_t>(coordinate{0,0},0);
        return result;
    }

    bool no_duplicated_number_in_region::check_answer(const std::shared_ptr<classic_board> &board) const
    {
        return false;
    }
    
} // namespace wills::sudoku
