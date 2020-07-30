/**
 * @file classic_board.hpp
 * @author Will Wu (willswu@outlook.com)
 * @brief header file for classic sudoku board represnetation
 * @version 0.1
 * @date 2020-07-30
 * 
 * @copyright MIT License
 * 
 */

#ifndef __WILLS_SUDOKU_CLASSIC_BOARD
#define __WILLS_SUDOKU_CLASSIC_BOARD
#include<vector>
#include<iostream>
#include<memory>
#include "board.hpp"
namespace wills::sudoku{
    using namespace std;
    class rectangle_region:public region_t{
        protected:
        coordinate a,b;
        public:
        rectangle_region():a(),b(){};
        rectangle_region(const coordinate & aval, const coordinate & bval):a(aval),b(bval)
        {
        }
        void set(const coordinate &left_up,const coordinate & right_down)
        {
            a = left_up;
            b = right_down;
        }
        bool contains(const coordinate & cell) const noexcept override{
            return false;
        }
        std::vector<coordinate> cells() const noexcept override{
            return vector<coordinate>();
        }
    };
    /**
     * @brief classic sudoku board
     * 
     */
    class classic_board :public board
    {
    private:
        axis_value_t col_size = 0;
        axis_value_t row_size = 0;
        vector<cell_value_t> cells;
    protected:
        /**
         * @brief read SQUARE sudoku data from a vector<int>
         * 
         * @param arr contains all cell values, row by row, no seperate symbol
         * @return size_t counter of readed cells, ZERO for fail
         */
        size_t read(const std::vector<int> & arr);
        inline size_t coords2index(const axis_value_t col, const axis_value_t row)const noexcept;
        inline coordinate index2coords(const size_t cell_idx)const noexcept;
        inline coordinate coords2region(const axis_value_t col, const axis_value_t row)const noexcept;
    public:
        classic_board(/* args */):board(),cells(){
        }
        ~classic_board(){

        }
        // friend istream & operator >>(istream & is, classic_board & obj);

        /**
         * @brief get the cell value by the given coordinate
         * 
         * @param col col axis value of the coordinate
         * @param row row axis value of the coordinate
         * @return cell_value_t cell_value_t value of the cell
         */
        cell_value_t  get(const axis_value_t col,const axis_value_t row)const;

        /**
         * @brief get the cell value by the given coordinate
         * 
         * @param cords coordinate point to the cell
         * @return cell_value_t value of the cell
         */
        cell_value_t  get(const coordinate &cords)const;

        /**
         * @brief set cell value by the given coordinate
         * 
         * @param cords coordinate point to the cell
         * @param val value to set
         */
        void set(const coordinate & cords,const cell_value_t val);

        /**
         * @brief get all regions in the board
         * 
         * Implements the abstract function of base class board
         * @return vector<region_t> 
         */
        vector<region_t> regions() const noexcept override;

        /**
         * @brief get the region of the given cell coordinate
         * 
         * @param cords coordinate of the cell
         * @return region_t a region which contains the cell
         */
        std::shared_ptr<region_t> region(const coordinate & cords) const noexcept override;
    };
}
#endif