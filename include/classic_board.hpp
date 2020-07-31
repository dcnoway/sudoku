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
#include <vector>
#include <iostream>
#include <memory>
#include "board.hpp"
namespace wills::sudoku
{
    using namespace std;

    /**
     * @brief the type of cell value
     * 
     * classic sudoku cell is just 1-digital, from 1 to 9.
     * Because int type is the fastest data type on the CPU and system bus,
     * and there is no obvious memory pressre for just board representing,
     * further more, we reserve 0(ZERO) as the blank cell,
     * reserve negative value for future use,
     * hereby int was choosed as the type of cell value.
     */
    using cell_value_t = int;

    constexpr int CELL_COORDS_ERROR = -0xFFFFFF;        //!< indicates that call function with a wrong cell coords
    constexpr int CELL_BLANK = 0;                       //!< indicates a blank cell, which need to be fill a number
    constexpr int CELL_EDGE = -1;                       //!< indicates a board edge, reserved for internal algorithms
    constexpr int BOARD_LINE = -10;                     //!< indicates a common board line
    constexpr int BOARD_LINE_THIN = -11;                //!< indicates a thin board line

    /**
     * @brief the type of cell coordinate factor, ZERO is reserved for internal use
     * 
     */
    using axis_value_t = unsigned;

    /**
     * @brief coordinate of sudoku board cells
     * 
     */
    struct coordinate
    {
        axis_value_t col; //!< column
        axis_value_t row; //!< row
        public:
        /**
         * @brief Construct a new coordinate object
         * 
         */
        coordinate():col(0),row(0){};
        /**
         * @brief Construct a new coordinate object
         * 
         * @param acol 
         * @param arow 
         */
        coordinate(axis_value_t acol,axis_value_t arow):col(acol),row(arow){};
    };

    /**
     * @brief classic square cell
     * 
     */
    class square_cell : public cell, public coordinate
    {
    public:
        square_cell() : cell(), coordinate() {}
        /**
         * @brief Construct a new square cell object
         * 
         * @param cds 
         */
        square_cell(const coordinate &cds) : cell(), coordinate(cds) {}
        ~square_cell(){};
    };

    /**
     * @brief rectangle region for classic sudoku
     * 
     */
    class rectangle_region : public region_t
    {
    protected:
        coordinate a; //!< a and b is two diagonal vertex of the rectangle
        coordinate b; //!< a and b is two diagonal vertex of the rectangle

    public:
        /**
         * @brief Construct a new rectangle region object
         */
        rectangle_region():a(),b(){
            
        }
        /**
         * @brief Construct a new rectangle region object
         * 
         * @param aval one vertex of the rectangle
         * @param bval another vertex of the rectangle
         */
        rectangle_region(const coordinate &aval, const coordinate &bval) : a(aval), b(bval)
        {
        }

        /**
         * @brief Copy constructor
         * 
         * @param obj 
         */
        rectangle_region(const rectangle_region & obj)noexcept
        {
            a = obj.a;
            b = obj.b;
        }

        /**
         * @brief Copy operator
         * 
         * @param obj 
         * @return const rectangle_region& 
         */
        const rectangle_region& operator=(const rectangle_region & obj)noexcept
        {
            a = obj.a;
            b = obj.b;
            return *this;
        }

        /**
         * @brief Destroy the rectangle region object
         */
        virtual ~rectangle_region() = default;

        /**
         * @brief set the vertex coordinates
         * 
         * @param left_up 
         * @param right_down 
         */
        void set(const coordinate &left_up, const coordinate &right_down)
        {
            a = left_up;
            b = right_down;
        }

        /**
         * @brief check this region contains the cell
         * 
         * @param acell a cell
         * @return true this region contains the given cell
         * @return false this region does NOT contain the given cell
         */
        bool contains(const std::shared_ptr<cell> acell) const noexcept override
        {
            square_cell *pcell = dynamic_cast<square_cell *>(acell.get());
            if (pcell)
                return contains(*pcell);
            else
                return false;
        }

        /**
         * @brief check this rectangle_region contains the square_cell with given coordiante or not
         * 
         * @param acell 
         * @return true 
         * @return false 
         */
        bool contains(const square_cell &acell) const noexcept
        {
            return ((acell.col >= std::min(a.col, b.col)) &&
                    (acell.col <= std::max(a.col, b.col)) &&
                    (acell.row >= std::min(a.row, b.row)) &&
                    (acell.row <= std::max(a.row, b.row)));
        }

        /**
         * @brief get all cordinates within this region
         * 
         * @return std::vector<coordinate> A vector contains all the cell coordinate within this region
         */
        std::vector<std::shared_ptr<cell>> cells() const noexcept override
        {
            //TODO: Implement this
            std::cerr << "Not implemented yet!" << std::endl;
            return std::vector<std::shared_ptr<cell>>();
        }
    };

    /**
     * @brief classic sudoku board
     * 
     */
    class classic_board : public board
    {
    private:
        axis_value_t col_size = 0;      //<! the amount size of current board columns
        axis_value_t row_size = 0;      //<! the amount size of current board rows
        vector<cell_value_t> cells;     //!< cells array
        vector<std::shared_ptr<rectangle_region>> _regions;

    protected:
        /**
         * @brief convert cell coords to the cell array element index
         * 
         * @param col 
         * @param row 
         * @return size_t 
         */
        inline size_t coords2index(const axis_value_t col, const axis_value_t row) const noexcept;
        /**
         * @brief convert element index for the cell to a coordinate
         * 
         * @param cell_idx 
         * @return coordinate 
         */
        inline coordinate index2coords(const size_t cell_idx) const noexcept;
        /**
         * @brief convert cell coords to the coords of region that contains the cell
         * 
         * @param col 
         * @param row 
         * @return coordinate 
         */
        inline coordinate coords2region(const axis_value_t col, const axis_value_t row) const noexcept;

        /**
         * @brief check coords validaties
         * 
         * @param col 
         * @param row 
         * @return true 
         * @return false 
         */
        inline bool check_coords(const axis_value_t col, const axis_value_t row) const noexcept
        {
            return ((col > 0) && (row > 0) && (col <= col_size) && (row <= row_size));
        }

    public:
        /**
         * @brief 
         * 
         */
        classic_board(/* args */) : board(), cells()
        {
        }
        /**
         * @brief Destroy the classic board object
         * 
         */
        ~classic_board()
        {
        }
        // friend istream & operator >>(istream & is, classic_board & obj);
        /**
         * @brief stream out the classic_board
         * 
         * @param os 
         * @param v 
         * @return ostream& 
         */
        friend ostream &operator<<(ostream &os, const classic_board &v);

        /**
         * @brief read SQUARE sudoku data from a vector<int>
         * 
         * @param arr contains all cell values, row by row, no seperate symbol
         * @return size_t counter of readed cells, ZERO for fail
         */
        size_t read(const std::vector<cell_value_t> &arr);

        /**
         * @brief get the cell value by the given coordinate
         * 
         * @param col [1,n] col axis value of the coordinate
         * @param row [1,n] row axis value of the coordinate
         * @return cell_value_t >0 the cell value; CELL_BLANK, CELL_COORDS_ERROR; other value reserved
         */
        cell_value_t get(const axis_value_t col, const axis_value_t row) const;

        /**
         * @brief get the cell value by the given coordinate
         * 
         * @param cords coordinate point to the cell
         * @return cell_value_t value of the cell
         */
        cell_value_t get(const coordinate &cords) const;

        /**
         * @brief set cell value by the given coordinate
         * 
         * @param cords coordinate point to the cell
         * @param val value to set
         */
        void set(const coordinate &cords, const cell_value_t val);

        /**
         * @brief get all regions in the board
         * 
         * Implements the abstract function of base class board
         * @return std::vector<std::shared_ptr<region_t>> 
         */
        std::vector<std::shared_ptr<region_t>> regions() const noexcept override;

        /**
         * @brief get all rectangle_regions in the loaded classic_board instance
         * 
         * @return vector<rectangle_region> 
         */
        vector<std::shared_ptr<rectangle_region>> rect_regions() const noexcept;

        /**
         * @brief get the region of the given cell coordinate
         * 
         * @param pcell a cell
         * @return std::shared_ptr<region_t> a region which contains the cell
         */
        std::shared_ptr<region_t> region(const shared_ptr<cell> &pcell) const noexcept override;

        /**
         * @brief 
         * 
         * @param cell 
         * @return const rectangle_region& 
         */
        std::shared_ptr<rectangle_region> region(const square_cell &cell) const noexcept;

        /**
         * @brief Create a subregion object
         * 
         * @return std::shared_ptr<region_t> 
         */
        std::shared_ptr<region_t> create_region() const noexcept override;
    };
} // namespace wills::sudoku
#endif