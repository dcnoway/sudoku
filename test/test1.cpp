#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "dlx.hpp"

//Catch2 unit test example
/*
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    //      Test case name             [cpp file name without .cpp]
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}
*/
using namespace wills;

TEST_CASE( "dlx::node default constractor check", "[dlx]" ) {
    dlx::node<int> node;
    REQUIRE( node.val == 0 );
    REQUIRE( node.col == 0 );
    REQUIRE( node.row == 0 );
    REQUIRE( node.p_col == &node );
    REQUIRE( node.p_up == &node );
    REQUIRE( node.p_down == &node );
    REQUIRE( node.p_left == &node );
    REQUIRE( node.p_right == &node );
}

TEST_CASE( "dlx::node copy constractor check", "[dlx]" ) {
    dlx::node<int> node_a(35);
    node_a.col = 34;
    node_a.row = 33;

    dlx::node<int> node_b(node_a);
    REQUIRE( node_b.val == node_a.val );
    REQUIRE( node_b.col == node_a.col );
    REQUIRE( node_b.row == node_a.row );
    REQUIRE( node_b.p_col == node_a.p_right );
    REQUIRE( node_b.p_up == node_a.p_up );
    REQUIRE( node_b.p_down == node_a.p_down );
    REQUIRE( node_b.p_left == node_a.p_left );
    REQUIRE( node_b.p_right == node_a.p_right );
}

TEST_CASE( "dlx::node copy operator check", "[dlx]" ) {
    dlx::node<int> node_a(35);
    node_a.col = 34;
    node_a.row = 33;

    dlx::node<int> node_c(0);
    node_c = node_a;
    REQUIRE( node_c.val == node_a.val );
    REQUIRE( node_c.col == node_a.col );
    REQUIRE( node_c.row == node_a.row );
    REQUIRE( node_c.p_col == node_a.p_right );
    REQUIRE( node_c.p_up == node_a.p_up );
    REQUIRE( node_c.p_down == node_a.p_down );
    REQUIRE( node_c.p_left == node_a.p_left );
    REQUIRE( node_c.p_right == node_a.p_right );
}

TEST_CASE( "dlx::cheader default constractor check", "[dlx]" ) {
    dlx::cheader<int> ch;
    REQUIRE( ch.val == 0 );
    REQUIRE( ch.col == 0 );
    REQUIRE( ch.row == 0 );
    REQUIRE( ch.row_count == 0 );

    dlx::cheader<int> ch2(35);
    REQUIRE( ch2.val == 35 );
    REQUIRE( ch2.col == 0 );
    REQUIRE( ch2.row == 0 );
    REQUIRE( ch2.row_count == 0 );
}

TEST_CASE( "dlx::cheader::append check", "[dlx]" ) {
    dlx::cheader<int> ch;
    ch.col = 100;

    REQUIRE( ch.append(nullptr) == nullptr );
    REQUIRE( ch.row == 0 );
    REQUIRE( ch.row_count == 0 );

    dlx::node<int> node_a(35);
    node_a.col = 34;
    node_a.row = 33;
    REQUIRE( ch.append(&node_a) == nullptr );
    REQUIRE( ch.row == 0 );
    REQUIRE( ch.p_down == &ch );
    REQUIRE( ch.row_count == 0 );

    node_a.col = 0;
    REQUIRE( ch.append(&node_a) == nullptr );
    REQUIRE( ch.row == 0 );
    REQUIRE( ch.row_count == 0 );

    node_a.col = 100;
    REQUIRE( ch.append(&node_a) == &ch );
    REQUIRE( ch.row == 0 );
    REQUIRE( ch.row_count == 1 );
    REQUIRE( ch.p_up == &node_a );
    REQUIRE( ch.p_down == &node_a );
    REQUIRE( node_a.p_up == &ch );
    REQUIRE( node_a.p_down == &ch );


    dlx::node<int> node_b(35);
    node_b.col = 100;
    REQUIRE( ch.append(&node_b) == &ch );
    REQUIRE( node_b.col == ch.col );
    REQUIRE( ch.row == 0 );
    REQUIRE( ch.row_count == 2 );
    REQUIRE( ch.p_up == &node_b );
    REQUIRE( ch.p_down == &node_a );
    REQUIRE( node_a.p_up == &ch );
    REQUIRE( node_a.p_down == &node_b );
    REQUIRE( node_b.p_up == &node_a );
    REQUIRE( node_b.p_down == &ch );
}

TEST_CASE( "dlx::cheader::cover_node check", "[dlx]" ) {
    //begin prepare test
    dlx::cheader<int> ch;
    ch.col = 100;
    dlx::node<int> node_a(35);
    node_a.col = 100;
    REQUIRE( ch.append(&node_a) != nullptr);
    REQUIRE( ch.row_count == 1 );
    dlx::node<int> node_b(53);
    node_b.col = 100;
    REQUIRE( ch.append(&node_b) != nullptr);
    REQUIRE( ch.row_count == 2 );
    //end prepare test

    //check nullptr input
    REQUIRE( ch.cover_node(nullptr) == nullptr );

    //check wrong col node cover
    dlx::node<int> node_w1(53);
    node_w1.col = 10;
    REQUIRE( ch.cover_node(&node_w1) == nullptr );

    //check cover middle node first
    REQUIRE( ch.cover_node(&node_a) == &ch );
    REQUIRE( ch.row_count == 1 );
    REQUIRE( ch.p_up == &node_b );
    REQUIRE( ch.p_down == &node_b );
    REQUIRE( node_a.p_up == &ch );
    REQUIRE( node_a.p_down == &node_b );
    REQUIRE( node_b.p_up == &ch );
    REQUIRE( node_b.p_down == &ch );
    //check cover next node
    REQUIRE( ch.cover_node(&node_b) == &ch );
    REQUIRE( ch.row_count == 0 );
    REQUIRE( ch.p_up == &ch );
    REQUIRE( ch.p_down == &ch );
    REQUIRE( node_a.p_up == &ch );
    REQUIRE( node_a.p_down == &node_b );
    REQUIRE( node_b.p_up == &ch );
    REQUIRE( node_b.p_down == &ch );

    REQUIRE( ch.cover_node(&node_b) == nullptr );
    REQUIRE( ch.row_count == 0 );
    REQUIRE( ch.p_up == &ch );
    REQUIRE( ch.p_down == &ch );
    REQUIRE( node_a.p_up == &ch );
    REQUIRE( node_a.p_down == &node_b );
    REQUIRE( node_b.p_up == &ch );
    REQUIRE( node_b.p_down == &ch );
}

TEST_CASE( "dlx::cheader::uncover_node check", "[dlx]" ) {
    //begin prepare test
    dlx::cheader<int> ch;
    ch.col = 100;
    dlx::node<int> node_a(35);
    node_a.col = 100;
    REQUIRE( ch.append(&node_a) != nullptr);
    dlx::node<int> node_b(53);
    node_b.col = 100;
    REQUIRE( ch.append(&node_b) != nullptr);
    //end prepare test

    //check nullptr input
    REQUIRE( ch.cover_node(nullptr) == nullptr );

    //check cover middle node first
    REQUIRE( ch.cover_node(&node_a) == &ch );
    //check cover next node
    REQUIRE( ch.cover_node(&node_b) == &ch );

    //uncover null node
    REQUIRE( ch.uncover_node(nullptr) == nullptr);
    //uncover node with wrong col index
    node_b.col = 10;
    REQUIRE( ch.uncover_node(&node_b) == nullptr);

    //start normal uncover
    node_b.col = 100;
    REQUIRE( ch.uncover_node(&node_b) == &ch );
    REQUIRE( ch.row_count == 1);
    REQUIRE( ch.uncover_node(&node_a) == &ch );
    REQUIRE( ch.row_count == 2);
    REQUIRE( node_b.col == ch.col );
    REQUIRE( ch.row == 0 );
    REQUIRE( ch.p_up == &node_b );
    REQUIRE( ch.p_down == &node_a );
    REQUIRE( node_a.p_up == &ch );
    REQUIRE( node_a.p_down == &node_b );
    REQUIRE( node_b.p_up == &node_a );
    REQUIRE( node_b.p_down == &ch );

}

TEST_CASE( "dlx::dlx::init_cols check", "[dlx]" ) {
    dlx::dancing_links<unsigned> dlx;
    REQUIRE_NOTHROW(dlx.init_cols(10));
    REQUIRE_NOTHROW(cout<<dlx);
    REQUIRE(dlx.col_size() == 10);

    REQUIRE_NOTHROW(dlx.clear_cols());
    REQUIRE_NOTHROW(cout<<dlx);
    REQUIRE(dlx.col_size() == 0);
}

TEST_CASE( "dlx::dlx::append_row values length boundary check", "[dlx]" ) {
    dlx::dancing_links<unsigned> dlx;
    dlx.init_cols(10);

    //Check normal append 
    REQUIRE(dlx.row_size() == 0);
    dlx::value_t<unsigned> values1[5]{{1,11},{3,33},{5,55},{7,77},{9,99}};
    size_t rs1 = 0;
    REQUIRE_NOTHROW(rs1 = dlx.append_row(values1,5));
    REQUIRE(rs1>0);
    REQUIRE(dlx.row_size() == rs1);

    //Check normal append 
    REQUIRE(dlx.row_size() == 1);
    dlx::value_t<unsigned> values2[5]{{2,22},{4,44},{6,66},{8,88},{10,1010}};
    size_t rs2 = 0;
    REQUIRE_NOTHROW(rs2 = dlx.append_row(values2,5));
    REQUIRE(rs2>0);
    REQUIRE(dlx.row_size() == rs2);

    //Check blank row append 
    REQUIRE(dlx.row_size() == 2);
    dlx::value_t<unsigned> values3[]{};
    size_t rs3 = 0;
    REQUIRE_NOTHROW(rs3 = dlx.append_row(values3,0));
    REQUIRE(rs3 == 2);
    REQUIRE(dlx.row_size() == 2);

    //Check full row append
    REQUIRE(dlx.row_size() == 2);
    dlx::value_t<unsigned> values4[10]{{1,11},{2,22},{3,33},{4,44},{5,55},{6,66},{7,77},{8,88},{9,99},{10,1010}};
    size_t rs4 = 0;
    REQUIRE_NOTHROW(rs4 = dlx.append_row(values4,10));
    REQUIRE(rs4 == 3);
    REQUIRE(dlx.row_size() == 3);

    //Check exceed value length append
    REQUIRE(dlx.row_size() == 3);
    dlx::value_t<unsigned> values7[11]{{1,11},{2,22},{3,33},{4,44},{5,55},{6,66},{7,77},{8,88},{9,99},{10,1010},{100,100100}};
    REQUIRE_THROWS(dlx.append_row(values7,11));
    REQUIRE(dlx.row_size() == 3);
}

TEST_CASE( "dlx::dlx::append_row values.col boundary check", "[dlx]" ) {
    dlx::dancing_links<unsigned> dlx;
    dlx.init_cols(10);

    //Check zero col value append
    REQUIRE(dlx.row_size() == 0);
    dlx::value_t<unsigned> values5[1]{{0,255}};
    REQUIRE_THROWS(dlx.append_row(values5,1));
    REQUIRE(dlx.row_size() == 0);

    //Check exceed col value append
    REQUIRE(dlx.row_size() == 0);
    dlx::value_t<unsigned> values6[10]{{11,1111},{2,22},{3,33},{4,44},{5,55},{6,66},{7,77},{8,88},{9,99},{10,1010}};
    REQUIRE_THROWS(dlx.append_row(values6,10));
    REQUIRE(dlx.row_size() == 0);


    //check duplicated col append
    REQUIRE(dlx.row_size() == 0);
    dlx::value_t<unsigned> values8[6]{{2,22},{2,22},{4,44},{6,66},{8,88},{10,1010}};
    REQUIRE_THROWS(dlx.append_row(values8,6));
    REQUIRE(dlx.row_size() == 0);
    
    //check unordered values append
    dlx::value_t<unsigned> values9[6]{{3,33},{2,22},{4,44},{6,66},{8,88},{10,1010}};
    REQUIRE_THROWS(dlx.append_row(values9,6));
    REQUIRE(dlx.row_size() == 0);
}


TEST_CASE( "dlx::dlx::clear() check", "[dlx]" ) {
    dlx::dancing_links<unsigned> dlx;
    REQUIRE_NOTHROW(dlx.clear());
    REQUIRE(dlx.col_size() == 0);

    REQUIRE_NOTHROW(dlx.init_cols(10));
    REQUIRE(dlx.col_size() == 10);

    REQUIRE_NOTHROW(dlx.clear());
    REQUIRE(dlx.col_size() == 0);

    REQUIRE_NOTHROW(dlx.init_cols(20));
    REQUIRE(dlx.col_size() == 20);

    REQUIRE_NOTHROW(dlx.clear());
    REQUIRE(dlx.col_size() == 0);

    REQUIRE_NOTHROW(dlx.init_cols(100));
    REQUIRE(dlx.col_size() == 100);

    REQUIRE_NOTHROW(dlx.clear());
    REQUIRE(dlx.col_size() == 0);
}

TEST_CASE( "dlx::dancing_link::solve_once() on a solvable problem check", "[dlx]" ) {
    dlx::dancing_links<unsigned> dlx;
    dlx.init_cols(10);
    dlx::value_t<unsigned> values1[5]{{1,11},{3,33},{5,55},{7,77},{9,99}};
    REQUIRE_NOTHROW(dlx.append_row(values1,5));

    dlx::value_t<unsigned> values2[5]{{2,22},{4,44},{6,66},{8,88},{10,1010}};
    REQUIRE_NOTHROW(dlx.append_row(values2,5));

    dlx::value_t<unsigned> values4[10]{{1,11},{2,22},{3,33},{4,44},{5,55},{6,66},{7,77},{8,88},{9,99},{10,1010}};
    REQUIRE_NOTHROW( dlx.append_row(values4,10));

    optional<dlx::result_t<unsigned>> res;
    REQUIRE_NOTHROW(res = dlx.solve_once());
    REQUIRE(res.has_value());
    REQUIRE(res->size() == 2);
    REQUIRE(res.value()[0].size() == 5);
    REQUIRE(
        ((res.value()[0][0].col == 2) ||
        (res.value()[0][1].col == 2) ||
        (res.value()[0][2].col == 2) ||
        (res.value()[0][3].col == 2) ||
        (res.value()[0][4].col == 2))
    );
    REQUIRE(
        ((res.value()[1][0].col == 1) &&
        (res.value()[1][1].col == 3) &&
        (res.value()[1][2].col == 5) &&
        (res.value()[1][3].col == 7) &&
        (res.value()[1][4].col == 9))
    );
}

TEST_CASE( "dlx::dancing_link::solve_once() on a unsolvable problem check", "[dlx]" ) {
    dlx::dancing_links<unsigned> dlx;
    dlx.init_cols(10);
    dlx::value_t<unsigned> values1[5]{{1,11},{3,33},{5,55},{7,77},{9,99}};
    REQUIRE_NOTHROW(dlx.append_row(values1,5));

    dlx::value_t<unsigned> values2[5]{{1,11},{3,33},{6,66},{8,88},{10,1010}};
    REQUIRE_NOTHROW(dlx.append_row(values2,5));

    dlx::value_t<unsigned> values4[8]{{1,11},{2,22},{3,33},{4,44},{5,55},{6,66},{7,77},{8,88}};
    REQUIRE_NOTHROW( dlx.append_row(values4,8));

    optional<dlx::result_t<unsigned>> res;
    REQUIRE_NOTHROW(res = dlx.solve_once());
    REQUIRE_FALSE(res.has_value());
}