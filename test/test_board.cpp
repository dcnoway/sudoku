#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "classic_board.hpp"
#include "sample_sudoku.hpp"

using namespace wills::sudoku;

TEST_CASE("rectangle_region check", "[classic_board]")
{
    coordinate zero{0, 0};
    coordinate one{1, 1};
    coordinate two{2, 2};
    auto cell0 = make_shared<square_cell>(zero);
    auto cell11 = make_shared<square_cell>(one);
    auto cell22 = make_shared<square_cell>(two);

    auto cell55 = make_shared<square_cell>(coordinate{5, 5});
    auto cell66 = make_shared<square_cell>(coordinate{6, 6});
    auto cell77 = make_shared<square_cell>(coordinate{7, 7});

    auto cell99 = make_shared<square_cell>(coordinate{9, 9});

    rectangle_region rect;
    REQUIRE(rect.contains(cell0));
    REQUIRE_FALSE(rect.contains(cell11));
    REQUIRE_FALSE(rect.contains(cell22));

    rect.set({1, 1}, {6, 6});
    REQUIRE_FALSE(rect.contains(cell0));
    REQUIRE(rect.contains(cell11));
    REQUIRE(rect.contains(cell22));
    REQUIRE_FALSE(rect.contains(cell99));
    REQUIRE(rect.contains(cell55));
    REQUIRE(rect.contains(cell66));
    REQUIRE_FALSE(rect.contains(cell77));

    rect.set({6, 1}, {1, 6});
    REQUIRE_FALSE(rect.contains(cell0));
    REQUIRE(rect.contains(cell11));
    REQUIRE(rect.contains(cell22));
    REQUIRE_FALSE(rect.contains(cell99));
    REQUIRE(rect.contains(cell55));
    REQUIRE(rect.contains(cell66));
    REQUIRE_FALSE(rect.contains(cell77));
}

TEST_CASE("classic_board read raw data check", "[classic_board]")
{
    classic_board board;
    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    REQUIRE(board.get(1, 1) == 5);
    REQUIRE(board.get(2, 1) == 7);
    REQUIRE(board.get(2, 5) == 2);
    REQUIRE(board.get(9, 9) == 3);
    REQUIRE(board.get(9, 1) == 0);
    REQUIRE(board.get(1, 9) == 0);
    REQUIRE(board.get(8, 9) == 6);

    vector<wills::sudoku::cell_value_t>
        v2(sudoku2, sudoku2 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v2);
    REQUIRE(board.get(1, 1) == 1);
    REQUIRE(board.get(9, 9) == 9);
    REQUIRE(board.get(9, 1) == 0);
    REQUIRE(board.get(1, 9) == 0);
}

TEST_CASE("classic_board get() boundary check", "[classic_board]")
{
    classic_board board;
    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    cell_value_t value = 100;
    REQUIRE_NOTHROW(value = board.get(0, 0));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(1, 0));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(0, 1));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE(board.get(1, 1) == 5);

    REQUIRE_NOTHROW(value = board.get(10, 10));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(9, 10));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(10, 9));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE(board.get(9, 9) == 3);

    REQUIRE_NOTHROW(value = board.get(10, 1));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(10, 0));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(9, 0));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE(board.get(9, 1) == 0);

    REQUIRE_NOTHROW(value = board.get(1, 10));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(0, 10));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(0, 9));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE(board.get(1, 9) == 0);
}

TEST_CASE("classic_board set() boundary check", "[classic_board]")
{
    classic_board board;
    REQUIRE_THROWS(board.set({0,0},1));
    REQUIRE_THROWS(board.set({1, 0},1));
    REQUIRE_THROWS(board.set({0, 1},1));
    REQUIRE_THROWS(board.set({1, 1},1));

    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    cell_value_t value = 100;
    REQUIRE_THROWS(board.set({0,0},value));
    REQUIRE_THROWS(board.set({1, 0},value));
    REQUIRE_THROWS(board.set({0, 1},value));
    REQUIRE_NOTHROW(board.set({1, 1},value));
    REQUIRE(board.get({1, 1}) == value);

    REQUIRE_THROWS(board.set({10,0},value));
    REQUIRE_THROWS(board.set({10, 1},value));
    REQUIRE_THROWS(board.set({9, 0},value));
    REQUIRE_NOTHROW(board.set({9, 1},value));
    REQUIRE(board.get({9, 1}) == value);

    REQUIRE_THROWS(board.set({0,9},value));
    REQUIRE_THROWS(board.set({1, 10},value));
    REQUIRE_THROWS(board.set({0, 10},value));
    REQUIRE_NOTHROW(board.set({1, 9},value));
    REQUIRE(board.get({1, 9}) == value);


    REQUIRE_THROWS(board.set({10,10},value));
    REQUIRE_THROWS(board.set({10, 9},value));
    REQUIRE_THROWS(board.set({9, 10},value));
    REQUIRE_NOTHROW(board.set({9, 9},value));
    REQUIRE(board.get({9, 1}) == value);
}

TEST_CASE("classic_board regions() check", "[classic_board]")
{
    classic_board board;

    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    auto regions = board.regions();
    REQUIRE(regions.size() == 9);

    shared_ptr<cell> pcell11 = std::make_shared<square_cell>(coordinate{1,1});
    REQUIRE(regions[0]->contains(pcell11));
    for(int i = 1;i<regions.size();++i){
        REQUIRE_FALSE(regions[i]->contains(pcell11));
    }

    shared_ptr<cell> pcell99 = std::make_shared<square_cell>(coordinate{9,9});
    REQUIRE(regions[8]->contains(pcell99));
    for(int i = 0;i<regions.size() - 1;++i){
        REQUIRE_FALSE(regions[i]->contains(pcell99));
    }
}

TEST_CASE("classic_board regions() boundary check", "[classic_board]")
{
    classic_board board;

    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    auto regions = board.regions();
    REQUIRE(regions.size() == 9);

    shared_ptr<cell> pcell00 = std::make_shared<square_cell>(coordinate{0,0});
    for(int i = 0;i<regions.size();++i){
        REQUIRE_FALSE(regions[i]->contains(pcell00));
    }

    shared_ptr<cell> pcellxx = std::make_shared<square_cell>(coordinate{10,10});
    for(int i = 0;i<regions.size();++i){
        REQUIRE_FALSE(regions[i]->contains(pcellxx));
    }
}

TEST_CASE("classic_board region() check", "[classic_board]")
{
    classic_board board;

    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    auto regions = board.regions();
    REQUIRE(regions.size() == 9);

    shared_ptr<cell> pcell00 = std::make_shared<square_cell>(coordinate{0,0});
    std::shared_ptr<region_t> preg;
    REQUIRE_NOTHROW(preg = board.region(pcell00));
    REQUIRE(preg == nullptr);

    shared_ptr<cell> pcellxx = std::make_shared<square_cell>(coordinate{10,10});
    REQUIRE_NOTHROW(preg = board.region(pcellxx));
    REQUIRE(preg == nullptr);

    std::shared_ptr<region_t> preg11,preg33,preg44,preg99;
    shared_ptr<cell> pcell11 = std::make_shared<square_cell>(coordinate{1,1});
    shared_ptr<cell> pcell33 = std::make_shared<square_cell>(coordinate{3,3});
    shared_ptr<cell> pcell44 = std::make_shared<square_cell>(coordinate{4,4});
    shared_ptr<cell> pcell99 = std::make_shared<square_cell>(coordinate{9,9});
    REQUIRE_NOTHROW(preg11 = board.region(pcell11));
    REQUIRE_NOTHROW(preg33 = board.region(pcell33));
    REQUIRE_NOTHROW(preg44 = board.region(pcell44));
    REQUIRE_NOTHROW(preg99 = board.region(pcell99));
    REQUIRE(preg11 != nullptr);
    REQUIRE(preg33 != nullptr);
    REQUIRE(preg44 != nullptr);
    REQUIRE(preg99 != nullptr);
    REQUIRE(((preg11 != preg44)&&(preg44 != preg99)));
    REQUIRE(preg11->contains(pcell11));
    REQUIRE(preg11->contains(pcell33));
    REQUIRE(preg44->contains(pcell44));
    REQUIRE(preg99->contains(pcell99));
    REQUIRE(preg11 == preg33);
}