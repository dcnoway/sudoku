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
    class every_cell_must_has_a_number : public rule
    {
        private:
        std::shared_ptr<classic_board> board;
        public:
        string getname() const override {return "Classic:every_cell_must_has_a_number";};
        void attach(const std::shared_ptr<classic_board> &board) override;
        bool parse() override {return true;};
        size_t dlx_cols() const override;
        std::vector<row_t<sudoku_cell_t>> generate_dlx_row() const override;
        std::vector<classic_board> parse_dlx_result(const std::vector<row_t<sudoku_cell_t>> & rslt) const override;
        bool check_answer(const std::shared_ptr<classic_board> &board) const override;
    };

    class no_duplicated_number_in_row : public rule
    {
        private:
        std::shared_ptr<classic_board> board;
        public:
        string getname() const override {return "Classic:no_duplicated_number_in_row";};
        void attach(const std::shared_ptr<classic_board> &board) override;
        bool parse() override {return true;};
        size_t dlx_cols() const override;
        std::vector<row_t<sudoku_cell_t>> generate_dlx_row() const override;
        std::vector<classic_board> parse_dlx_result(const std::vector<row_t<sudoku_cell_t>> & rslt) const override;
        bool check_answer(const std::shared_ptr<classic_board> &board) const override;
    };
    class no_duplicated_number_in_col :public rule
    {
        private:
        std::shared_ptr<classic_board> board;
        public:
        string getname() const override {return "Classic:no_duplicated_number_in_col";};
        void attach(const std::shared_ptr<classic_board> &board) override;
        bool parse() override {return true;};
        size_t dlx_cols() const override;
        std::vector<row_t<sudoku_cell_t>> generate_dlx_row() const override;
        std::vector<classic_board> parse_dlx_result(const std::vector<row_t<sudoku_cell_t>> & rslt) const override;
        bool check_answer(const std::shared_ptr<classic_board> &board) const override;
    };
    class no_duplicated_number_in_region : public rule
    {
        private:
        std::shared_ptr<classic_board> board;
        public:
        string getname() const override {return "Classic:no_duplicated_number_in_region";};
        void attach(const std::shared_ptr<classic_board> &board) override;
        bool parse() override {return true;};
        size_t dlx_cols() const override;
        std::vector<row_t<sudoku_cell_t>> generate_dlx_row() const override;
        std::vector<classic_board> parse_dlx_result(const std::vector<row_t<sudoku_cell_t>> & rslt) const override;
        bool check_answer(const std::shared_ptr<classic_board> &board) const override;
    };
} // namespace wills::sudoku

#endif