#include <iostream>
#include <memory>
#include "dlx.hpp"
#include "sudoku.hpp"
#include "sample_sudoku.hpp"
#include "classic_board.hpp"
// #include "classic_solver.hpp"
#include "classic_rule.hpp"
using namespace std;
using namespace wills;
using namespace wills::sudoku;

int main(int argc, char const *argv[])
{
    // dlx::dancing_links<unsigned> dlx;
    // auto p_board = std::make_shared<classic_board>();

    vector<wills::sudoku::sudoku_cell_t> 
        v(sudoku1,sudoku1 + sizeof(sudoku1) /sizeof(unsigned));
    // p_board->read(v);
    // cout << *p_board;

    wills::sudoku::sudoku solver;
    solver.load_cells(v);

    solver.add_rule(make_shared<rules::every_cell_must_has_a_number>());
    solver.add_rule(make_shared<rules::no_duplicated_number_in_col>());
    solver.add_rule(make_shared<rules::no_duplicated_number_in_row>());
    solver.add_rule(make_shared<rules::no_duplicated_number_in_region>());


    auto answers = solver.solve();

    for(auto b:answers){
        std::cout << "=================================" << std::endl;
        std::cout << b <<std::endl;
    }

    return 0;
}