#include <iostream>
#include "dlx.hpp"
#include "sudoku.hpp"
using namespace std;
using namespace wills;
int main(int argc, char const *argv[])
{
    dlx::dancing_links<unsigned> dlx;
    dlx.init_cols(10);
    dlx::value_t<unsigned> values1[5]{{1,11},{3,33},{5,55},{7,77},{9,99}};
    size_t rs1 = 0;
    rs1 = dlx.append_row(values1,5);
    cout<<dlx<<endl;

    return 0;
}