/**
 * @file classic_rule.hpp
 * @author Will Wu (willswu@outlook.com)
 * @brief classic sudoku dancing links algorithm rules
 * @version 0.1
 * @date 2020-08-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __WILLS_SUDOKU_CLASSIC_RULES
#define __WILLS_SUDOKU_CLASSIC_RULES
#include "rule.hpp"
namespace wills::sudoku::rules
{
    //some rule generator need board info, i.e how many regions in board  and cell belongs to which region and how many cells per region
    //one rule generate one or more rows for dlx, on the contrarary, one solve result row from dlx need one or more rule parser
    //TODO: class diagram need refactor to fit above two lines
    //TODO: design class diagram for post solve or rules contain computetaional relation between two or more cells, like N-sum sudokuddd
    class every_cell_must_has_a_number : public rule
    {
        public:
        size_t dlx_cols(const rectangle_region &board_shape) const override;
        value_t<cell_value_t> generate(const rectangle_region & board_shape, const coordinate & coords, cell_value_t cellval) const override;
        pair<coordinate, cell_value_t> parse(const rectangle_region & board_shape, value_t<cell_value_t> cell) const override;        
    };

    class no_duplicated_number_in_row : public rule
    {
        size_t dlx_cols(const rectangle_region &board_shape) const override;
        value_t<cell_value_t> generate(const rectangle_region & board_shape, const coordinate & coords, cell_value_t cellval) const override;
        pair<coordinate, cell_value_t> parse(const rectangle_region & board_shape, value_t<cell_value_t> cell) const override;        
    };
    class no_duplicated_number_in_col :public rule
    {
        size_t dlx_cols(const rectangle_region &board_shape) const override;
        value_t<cell_value_t> generate(const rectangle_region & board_shape, const coordinate & coords, cell_value_t cellval) const override;
        pair<coordinate, cell_value_t> parse(const rectangle_region & board_shape, value_t<cell_value_t> cell) const override;        
    };
    class no_duplicated_number_in_region : public rule
    {
        size_t dlx_cols(const rectangle_region &board_shape) const override;
        value_t<cell_value_t> generate(const rectangle_region & board_shape, const coordinate & coords, cell_value_t cellval) const override;
        pair<coordinate, cell_value_t> parse(const rectangle_region & board_shape, value_t<cell_value_t> cell) const override;        
    };
} // namespace wills::sudoku

#endif