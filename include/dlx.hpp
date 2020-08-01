/**
 * @file dlx.hpp
 * @author Will Wu (willswu@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __WILLS_SUDOKU_DLX
#define __WILLS_SUDOKU_DLX
#include <vector>
#include <memory>
#include <iostream>
#include <exception>
#include <stack>
#include <functional>
using namespace std;

namespace wills::dlx
{
    /**
     * @brief An internal link node class used by DancingLinks
     * 
     * @tparam T The typename of the value you wanna stored in the node
     */
    template <typename T>
    class node
    {
    public:
        T val;                   //!< value associated to the node
        size_t col = 0;          //!< column index of the node
        size_t row = 0;          //!< row index of the node
        node *p_up = nullptr;    //!< pointer to the up node
        node *p_down = nullptr;  //!< pointer to the down node
        node *p_left = nullptr;  //!< pointer to the left node
        node *p_right = nullptr; //!< pointer to the right node
        node *p_col = nullptr;   //!< pointer to the column header

        /**
         * @brief Construct a new node object with default value
         */
        node() : val() { p_up = p_down = p_left = p_right = p_col = this; };
        /**
         * @brief Construct a new node object
         * 
         * @param v the associated value stored in the node
         */
        node(T v) : val(v) { p_up = p_down = p_left = p_right = p_col = this; }
        /**
         * @brief Copy constructor
         * 
         * @param obj Another node instance
         */
        node(const node &obj) : val(obj.val)
        {
            col = obj.col;
            row = obj.row;
            p_up = obj.p_up;
            p_down = obj.p_down;
            p_left = obj.p_left;
            p_right = obj.p_right;
            p_col = obj.p_col;
        }
        /**
         * @brief copy operator
         * 
         * @param obj the right side node instance
         * @return const node& the left side node instance
         */
        const node &operator=(const node &obj) noexcept
        {
            val = obj.val;
            col = obj.col;
            row = obj.row;
            p_up = obj.p_up;
            p_down = obj.p_down;
            p_left = obj.p_left;
            p_right = obj.p_right;
            p_col = obj.p_col;
            return *this;
        }

        /**
         * @brief Simple stream output operator
         * 
         * @param os 
         * @param nd 
         * @return ostream& 
         */
        friend ostream &operator<<(ostream &os, const node &nd)
        {
            os << "dlx::node{";
            os << "val=" << nd.val << ", column=" << nd.col << ", row=" << nd.row;
            os << ", p_up=" << nd.p_up << ", p_down =" << nd.p_down;
            os << ", p_left=" << nd.p_left << ", p_right=" << nd.p_right;
            os << ", p_col=" << nd.p_col << '}';
            return os;
        }
    };

    /**
     * @brief column header node in the dancing links
     * 
     * @tparam T typename of the associated value stored in the dancing links node
     */
    template <typename T>
    class cheader : public node<T>
    {
    public:
        using node<T>::node;
        using node<T>::val;
        using node<T>::p_up;
        using node<T>::p_down;
        using node<T>::p_left;
        using node<T>::p_right;
        using node<T>::p_col;
        using node<T>::col;
        using node<T>::row;

        size_t row_count = 0; //!< the total sum count of the node on the down side of this column header node

        /**
         * @brief Construct a new cheader object
         * 
         */
        cheader()
        {
            p_up = this;
            p_down = this;
            p_left = this;
            p_right = this;
            p_col = this;
            col = 0;
            row = 0;
        }
        /**
         * @brief Construct a new cheader object
         * 
         * @param v 
         */
        cheader(T v)
        {
            val = v;
            p_up = this;
            p_down = this;
            p_left = this;
            p_right = this;
            p_col = this;
            col = 0;
            row = 0;
        }

        /**
         * @brief append a node to the last node on the downside of column header
         *
         * NOTICE: a node can NOT be append twice! This function never check same node appends. 
         * @param pnode pointer to the node to be appended
         * @return cheader* 
         * - nullptr: failed
         * - this: succeded
         */
        cheader *append(node<T> *pnode) noexcept
        {
            if (pnode)
            {
                if (pnode->col == col)
                {
                    pnode->p_up = p_up;
                    pnode->p_down = this;
                    pnode->p_col = this;
                    p_up->p_down = pnode;
                    p_up = pnode;
                    ++row_count;
                    return this;
                }
                else
                {
                    cerr << "append a node to cheader with different col index number." << endl;
                    return nullptr;
                }
            }
            else
            {
                cerr << "append a nullptr to a cheader!" << endl;
                return nullptr;
            }
        }

        /**
         * @brief break the poiter link of the given node from its upper link node and down side link node
         * 
         * NOTICE: 
         * 1. this operation only break the up and down link
         * 2. this operation DO NOT break the left and right link
         * 3. adjust the row_count of the column header node
         * 4. this operation DO NOT delete the node instance
         * @param pnode pointer to the node which will be removed
         * @return cheader* 
         * - nullptr: failed
         * - this: succeded
         */
        cheader *cover_node(node<T> *pnode) noexcept
        {
            if (pnode)
            {
                for (node<T> *p = p_down; p != this; p = p->p_down)
                {
                    if (p == pnode)
                    {
                        p->p_up->p_down = p->p_down;
                        p->p_down->p_up = p->p_up;
                        --row_count;
                        return this;
                        break;
                    }
                }
                return nullptr;
            }
            else
            {
                cerr << "cover a node with nullptr on a cheader!" << endl;
                return nullptr;
            }
        }

        /**
         * @brief resume the link of the given node
         * 
         * @param pnode the node which will be resumed
         * @return cheader* 
         * - nullptr: failed
         * - this: succeded
         */
        cheader *uncover_node(node<T> *pnode) noexcept
        {
            if (pnode)
            {
                if (pnode->col == col)
                {
                    pnode->p_up->p_down = pnode;
                    pnode->p_down->p_up = pnode;
                    ++row_count;
                    return this;
                }
                else
                {
                    cerr << "uncover a node not in given col!" << endl;
                    return nullptr;
                }
            }
            else
            {
                cerr << "uncover a node with nullptr on a cheader!" << endl;
                return nullptr;
            }
        }

        /**
         * @brief the stream output operation of cheader instance
         * 
         * @param os 
         * @param ch 
         * @return ostream& 
         */
        friend ostream &operator<<(ostream &os, const cheader &ch)
        {
            os << "dlx::cheader{";
            os << "row_count=" << ch.row_count << ',';
            os << static_cast<node<T>>(ch) << '}';
            return os;
        }
    };

    /**
     * @brief template alias for std::shared_ptr<cheader<T>>
     * 
     * @tparam T typename of the associated value that stored in the node
     */
    template <typename T>
    using pheader_t = typename std::shared_ptr<cheader<T>>;

    /**
     * @brief template alias for std::shared_ptr<node<T>>
     * 
     * @tparam T typename of the associated value that stored in the node
     */
    template <typename T>
    using pnode_t = typename std::shared_ptr<node<T>>;

    /**
     * @brief helper struct for call dancing_links functions
     * 
     * @tparam T typename of the associated value that stored in the node
     */
    template <typename T>
    struct value_t
    {
        size_t col; //!< column index
        T val;      //!< stored value
    };

    /**
     * @brief helper typename alias
     * 
     * @tparam T 
     */
    template <typename T>
    using row_t = typename std::vector<value_t<T>>;

    /**
     * @brief helper typename alias
     * 
     * @tparam T 
     */
    template <typename T>
    using result_t = typename std::vector<row_t<T>>;

    /**
     * @brief A class implemented classical dancing links algorithm
     * 
     * @tparam T typename of the associated value that stored in the node
     */
    template <typename T>
    class dancing_links
    {
        /**
         * @brief the root node of all the dancing link nodes
         * 
         * root.row_count is the indicator of the max row index of whole dancing links
         */
        cheader<T> root;

        /**
         * @brief A vector holds all nodes's shared_ptr
         * NOTICE:
         * 1. No automatic node delete while cover operation, prevent invalid ptr access and segement fault
         * 2. Auto delete all nodes when dlx obj expired, prevent memory leak
         */
        vector<pnode_t<T>> nodes;

    protected:
        /**
         * @brief A helper function to check column header for consistance and linkage
         * 
         * @return true status ok
         * @return false status bad
         */
        bool check_cols() noexcept
        {
            size_t vector_size = headers.size();

            size_t right_size = 0;
            for (node<T> *ptr = root.p_right; ptr != nullptr && ptr != &root; ptr = ptr->p_right)
                ++right_size;

            size_t left_size = 0;
            for (node<T> *ptr = root.p_left; ptr != nullptr && ptr != &root; ptr = ptr->p_left)
                ++left_size;

            return ((vector_size == right_size) && (right_size == left_size));
        }

    private:
        /**
         * @brief A vector stores all the smart pointer to the column header node
         * NOTICE: column index start from ONE, but this vector's element index start from ZERO
         * 
         */
        vector<pheader_t<T>> headers;
        /**
         * @brief classic dancing links COVER operation
         * 
         * @param ph pointer to the column header which need to be COVERED
         */
        void cover(cheader<T> *ph)
        {
            if (!ph)
                throw invalid_argument("Call dlx::dancing_links::cover with a nullptr");
            ph->p_left->p_right = ph->p_right;
            ph->p_right->p_left = ph->p_left;
            for (auto ptr = ph->p_down; ptr != ph; ptr = ptr->p_down)
            {
                for (auto p = ptr->p_right; p != ptr; p = p->p_right)
                {
                    cheader<T> *pcol = static_cast<cheader<T> *>(p->p_col);
                    if (pcol->cover_node(p) != pcol)
                        throw logic_error("cover node failed.");
                }
                --root.row_count;
            }
        }

        /**
         * @brief classic dancing links UNCOVER operation
         * 
         * @param ph pointer to the column header which need to be UNCOVERED
         */
        void uncover(cheader<T> *ph)
        {
            if (!ph)
                throw invalid_argument("Call dlx::dancing_links::cover with a nullptr");
            for (auto ptr = ph->p_up; ptr != ph; ptr = ptr->p_up)
            {
                for (auto p = ptr->p_left; p != ptr; p = p->p_left)
                {
                    cheader<T> *pcol = static_cast<cheader<T> *>(p->p_col);
                    if (pcol->uncover_node(p) != pcol)
                        throw logic_error("uncover node failed.");
                }
                ++root.row_count;
            }
            ph->p_left->p_right = ph;
            ph->p_right->p_left = ph;
        }

    public:
        /**
         * @brief Construct a new dancing links object
         * 
         */
        dancing_links() : root(), headers(), nodes(){};

        /**
         * @brief stream output function for whole dancing link
         * 
         * @param os 
         * @param dlx 
         * @return ostream& 
         */
        friend ostream &operator<<(ostream &os, const dancing_links &dlx)
        {
            os << "dlx::dancing_links{" << endl;
            os << "root=" << dlx.root << endl;
            os << "column header[" << dlx.nodes.size() << "]={" << endl;
            for (auto ele : dlx.headers)
            {
                os << *ele << endl;
            }
            os << "},";
            os << "nodes[" << dlx.nodes.size() << "]={" << endl;
            for (auto it : dlx.nodes)
            {
                os << it << endl;
            }
            os << "}" << endl
               << '}' << endl;
            return os;
        }

        /**
         * @brief Initilize column header node with given column count
         * 
         * @param col_count the total sum of column
         */
        void init_cols(size_t col_count)
        {
            if (headers.size() != 0)
                throw logic_error("dancing_links::init() on a NOT empty headers!");

            cheader<T> *ptr = &root;
            for (size_t i = 1; i <= col_count; ++i)
            {
                auto head = make_shared<cheader<T>>(0);
                headers.push_back(head);
                head->val = 0;
                head->col = i;
                head->p_left = ptr;
                head->p_right = &root;

                ptr->p_right = head.get();
                root.p_left = head.get();
                ptr = head.get();
            }
            if (!check_cols())
                throw logic_error("column header link list error!");
        }

        /**
         * @brief clears and delete all the column header node instance
         * 
         */
        void clear_cols() noexcept
        {
            if (nodes.size() == 0)
            {
                headers.clear();
                root.p_left = &root;
                root.p_right = &root;
            }
        }

        /**
         * @brief get total amount of column node stay in dancing link (directly or indirectly links with root)
         * 
         * @return size_t total amount of column node 
         */
        size_t col_size() noexcept
        {
            // return headers.size();
            size_t result = 0;
            for (cheader<T> *ptr = static_cast<cheader<T> *>(root.p_right);
                 ptr != &root;
                 ptr = static_cast<cheader<T> *>(ptr->p_right))
                ++result;
            return result;
        }

        size_t append_row(const row_t<T> & row)
        {
            return append_row(row.begin(),row.size());
        }

        /**
         * @brief append a row to the end of the dancing links
         * 
         * @param values a array contains all column index and the node value.
         * - a valid column index MUST belongs to [1,col_size()] of the DancingLinks instance.
         * - the length of values[] MUST belongs to [0,col_size()] of the DancingLinks instance.
         * - call this function with a blank row(means that a zero length array values), it will do nothing but return the current max row index.
         * @param values_len the length of values[]
         * @return size_t the row index of appended row.
         * - 0       append failed.
         * - no-zero append succeded and return value is the row index of appended row.
         */
        size_t append_row(const value_t<T> values[], const size_t values_len)
        {
            //==================================================
            //Begin paramter validaties check
            if (values_len > headers.size())
                throw length_error("append row length exceed col limits.");

            //check the maximum col in the values array
            for (size_t i = 0; i < values_len; ++i)
            {
                if (values[i].col == 0)
                    throw invalid_argument("append a dlx row with a zero col index.");
                if (values[i].col > headers.size())
                    throw invalid_argument("the maximum col of append row exceed col limits.");
            }

            //check values array is sorted by col or not
            //if values array is unsorted, then the link list logic will goes wrong
            for (size_t i = 1; i < values_len; ++i)
            {
                if (values[i].col <= values[i - 1].col)
                    throw logic_error("call append_row with a unsorted value array.");
            }
            //End paramter validaties check
            //==================================================

            //Blank row append with no effections
            if (values_len == 0)
                return root.row_count;

            node<T> *pfirst = nullptr;
            for (int i = 0; i < values_len; ++i)
            {
                auto v = values[i];
                pnode_t<T> pnode = std::make_shared<node<T>>(v.val);
                pnode->col = v.col;
                pnode->row = root.row_count + 1;

                if (headers[v.col - 1]->append(pnode.get()) != headers[v.col - 1].get())
                    throw logic_error("append node error!");
                else
                {
                    //pleft pright
                    if (nullptr == pfirst)
                    {
                        pfirst = pnode.get();
                    }
                    pnode->p_left = pfirst->p_left;
                    pnode->p_right = pfirst;

                    pnode->p_left->p_right = pnode.get();
                    pnode->p_right->p_left = pnode.get();
                    //keep smart ptr managed by a vector
                    nodes.push_back(pnode);
                }
            }
            return ++root.row_count;
        }

        /**
         * @brief clear and delete all nodes except root and column header node instance
         * 
         */
        void clear_rows() noexcept
        {
            nodes.clear();
            root.row_count = 0;
            for (cheader<T> *p = static_cast<cheader<T> *>(root.p_right);
                 p != &root;
                 p = static_cast<cheader<T> *>(p->p_right))
            {
                p->p_up = p;
                p->p_down = p;
                p->row_count = 0;
            }
        }

        /**
         * @brief get the total row size of whole dancing links
         * 
         * @return size_t total row size
         */
        size_t row_size() noexcept
        {
            return root.row_count;
        }

        /**
         * @brief get the total amount of all the nodes links in the dancing link root (exclude root and column header node)
         * 
         * @return size_t total amount of all the nodes 
         */
        size_t node_size() noexcept
        {
            size_t result = 0;
            for (auto pcol = root.p_right; pcol != &root; pcol = pcol->p_right)
            {
                for (auto pn = pcol->p_down; pn != pcol; pn = pn->p_down)
                {
                    ++result;
                }
            }
            return result;
        }
        /**
         * @brief clear and delete all nodes and column header nodes
         * 
         */
        void clear() noexcept
        {
            clear_rows();
            clear_cols();
        }

        private:
        /**
         * @brief An internal private function to solve problem recursively
         * 
         * @param row_stack 
         * @return true 
         * @return false 
         */
        bool _recursive_solve(stack<node<T>*> & row_stack)
        {
            if (this->root.p_right == &(this->root))
                return true;

            cheader<T> *pcol = static_cast<cheader<T> *>(root.p_right);
            cover(pcol);
            for (auto p = pcol->p_down; p != pcol; p = p->p_down)
            {
                row_stack.push(p);
                for (auto pn = p->p_right; pn != p; pn = pn->p_right)
                    cover(static_cast<cheader<T> *>(pn->p_col));
                if (_recursive_solve(row_stack))
                    return true;
                for (auto pn = p->p_left; pn != p; pn = pn->p_left)
                    uncover(static_cast<cheader<T> *>(pn->p_col));
                row_stack.pop();
            }
            uncover(pcol);
            return false;
        }

        public:
        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        optional<result_t<T>> solve_once()
        {
            stack<node<T> *> row_stack;
            result_t<T> result;

            if (_recursive_solve(row_stack))
            {
                while (row_stack.size() != 0)
                {
                    auto pnode = row_stack.top();
                    row_t<T> _row;
                    auto ptr = pnode;
                    do{
                        value_t<T> v;
                        v.col = ptr->col;
                        v.val = ptr->val;
                        _row.push_back(v);
                        ptr = ptr->p_right;
                    }while(ptr != pnode);
                    result.push_back(_row);
                    row_stack.pop();
                }
                return result;
            }
            return nullopt;
        }

        // /**
        //  * @brief 
        //  * 
        //  * @return true 
        //  * @return false 
        //  */
        // optional<result_t<T>> solve_multiple()
        // {
        //     return nullopt;
        // }
    };
} // namespace wills::dlx

#endif