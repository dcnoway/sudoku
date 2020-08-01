#ifndef __WILLS_SUDOKU_BOARD
#define __WILLS_SUDOKU_BOARD
#include <vector>
#include <memory>
/**
 * @file board.hpp
 * @author Will Wu (willswu@outlook.com)
 * @brief sudoku board representation base class header file
 * @version 0.1
 * @date 2020-07-30
 * 
 * @copyright MIT License
 * 
 */

namespace wills::sudoku{

    /**
     * @brief abstract class for dynamic processing both classic and variant sudoku
     * 
     */
    class cell
    {
        public:
        /**
         * @brief Destroy the cell object
         * 
         */
        virtual ~cell()=default;
    };


    /**
     * @brief abstract region
     * 
     * A region wrapper for both vector implemented board and sub graph in graph implemented board
     * NOTICE:This is a abstract class implemented interface, for runtime dynamic adaptive
     */
    class region_t
    {
        protected:
        /**
         * @brief A weak pointer to the board which this region belongs to
         * 
         */
        std::weak_ptr<region_t> _parent;
        public:
        virtual ~region_t() = default;
        /**
         * @brief check if this region contains the cell with given coordiante or not
         * 
         * NOTICE:This is a pure virtual function, must implemented in derived class
         * @param a_cell cell
         * @return true this region contains the given cell
         * @return false this region does NOT contain the given cell
         */
        virtual bool contains(const std::shared_ptr<cell> a_cell) const noexcept = 0;

        /**
         * @brief check if this region contains a sub region
         * 
         * NOTICE:This is a pure virtual function, must implemented in derived class
         * @param sub pointer to sub region
         * @return true 
         * @return false 
         */
        // virtual bool contains(const std::shared_ptr<region_t> sub) const noexcept= 0;

        /**
         * @brief get all cell coordinates within this region
         * 
         * NOTICE:This is a pure virtual function, must implemented in derived class
         * @return std::vector<coordinate> A vector contains all the cell coordinates within this region
         */
        virtual std::vector<std::shared_ptr<cell>> cells() const noexcept= 0;

        /**
         * @brief Get the parent object
         * 
         * @return std::shared_ptr<region_t> 
         */
        std::shared_ptr<region_t> get_parent() const noexcept
        {
            return _parent.lock();
        }

        /**
         * @brief Is this region the root element in regin tree
         * 
         * @return true 
         * @return false 
         */
        bool is_root() const noexcept{
            return (_parent.lock() == nullptr);
        }

    };
    

    /**
     * @brief sudoku board representation base class
     * 
     */
    class board 
    {
    private:
        /* data */
    protected:
    public:
        /**
         * @brief get all cells
         * 
         * @return std::vector<std::shared_ptr<cell>> 
         */
        virtual std::vector<std::shared_ptr<cell>> cells() const noexcept = 0;

        /**
         * @brief Get the shape of board, using a region data struct
         * 
         * @return const std::shared_ptr<region_t> 
         */
        virtual const std::shared_ptr<region_t> get_shape() const noexcept = 0;

        /**
         * @brief Get all regions instance belongs to this board
         * 
         * @return std::vector<std::shared_ptr<region_t>>
         */
        virtual std::vector<std::shared_ptr<region_t>> regions() const noexcept = 0;

        /**
         * @brief Get a region which the given cell is within
         * 
         * @param pcell A shared_ptr to the cell for dynamic
         * @return std::shared_ptr<region_t> 
         */
        virtual std::shared_ptr<region_t> region(const std::shared_ptr<cell> & pcell) const noexcept = 0;

        /**
         * @brief Create a sub region object
         * 
         * @return std::shared_ptr<region_t> 
         */
        virtual std::shared_ptr<region_t> create_subregion() const noexcept = 0;
    };
    
}
#endif