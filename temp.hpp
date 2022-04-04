/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_node.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:45:02 by matthieu          #+#    #+#             */
/*   Updated: 2022/02/27 15:58:48 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_NODE_HPP
# define BINARY_TREE_NODE_HPP

//# include "other_functions.hpp"
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
# define RED 0
# define BLACK 1
# define SENTINEL 2

namespace ft {
	template<class T>
		class Node {
			public:
			typedef T	value_type;

			value_type	data;
			Node *		parent;
			Node *		left;
			Node *		right;
			bool		color; // 0 is black, 1 is red

			Node() : parent(NULL), left(NULL), right(NULL) {};
			Node(Node const & src) : parent(src.parent), left(src.left), right(src.left), color(src.color) {};
			~Node() {};

			Node &	operator= (Node const & rhs) {
				parent = rhs.parent;
				left = rhs.left;
				right = rhs.right;
				color = rhs.color;
				return *this;
			};
			static bool is_left_child(Node *node) {
				return (!is_null_node(node->parent) && node->parent->left == node);
			}
			static bool is_right_child(Node *node) {
				return (!is_null_node(node->parent) && node->parent->right == node);
			}
			static Node *sibling(Node* x) {
				if (is_left_child(x))
					return x->parent->right;
				return x->parent->left;
			}
			static bool getColor(Node *x) {
				if (is_null_node(x))
					return BLACK;
				return x->color;
			}
			static bool is_null_node(Node *x) {
//				std::cout << "x is " << x << " | color is " << (x != NULL ? x->color : -1) << std::endl;
				return x == NULL || x->left == NULL;;
			}
#ifdef FT_DEBUG_TREE

				static void DG_tree(Node *root) {
					_print_tree(root, 1, 2);
				}

#define MAX_WORD_WIDTH 20
#define WORD_ADDED_WIDTH 2

#define P_PAD " "
#define PAD " "

#define P_TRUNC "…"
#define TRUNC "+"

#define P_PREFIX "\033[33m☾\033[34m"
#define PREFIX "["

#define P_SUFFIX "\033[33m☽\033[0m"
#define SUFFIX "]"

#define P_JUNCTION "━"
#define JUNCTION "-"

#define P_JUNCTION_LOW_L "\033[35m╭"
#define JUNCTION_LOW_L "/"

#define P_JUNCTION_HIG_L "╯\033[0m"
#define JUNCTION_HIG_L "'"

#define P_JUNCTION_LOW_R "╮\033[0m"
#define JUNCTION_LOW_R "\\"

#define P_JUNCTION_HIG_R "\033[35m╰"
#define JUNCTION_HIG_R "`"


			typedef struct s_tree_display {
				int		block_width;
				int		block_delta;
				int		label_width;
				int		label_delta;
				int		lwidth;
				int		lpos;
				int		rwidth;
				int		rpos;
				int		trunc;
				int		depth;
				int		pos;
			}	t_tree_display;

			t_tree_display tree_dsp;

			typedef struct s_print_style{
				const char	*word;
				int		len;
			}				t_print_style;

			typedef enum e_style_match {
				E_PAD,
				E_TRUNC,
				E_PREFIX,
				E_SUFFIX,
				E_JUNCTION,
				E_JUNCTION_LOW_L,
				E_JUNCTION_LOW_R,
				E_JUNCTION_HIG_L,
				E_JUNCTION_HIG_R,
			}	t_style_match;

			typedef struct s_buf {
				char	*str;
				char	*s;
				int		capacity;
				int		pretty;
			}	t_buf;

			const t_print_style	g_pretty_style[10] = {
				[E_PAD] = {P_PAD, sizeof(P_PAD) - 1},
				[E_TRUNC] = {P_TRUNC, sizeof(P_TRUNC) - 1},
				[E_PREFIX] = {P_PREFIX, sizeof(P_PREFIX) - 1},
				[E_SUFFIX] = {P_SUFFIX, sizeof(P_SUFFIX) - 1},
				[E_JUNCTION] = {P_JUNCTION, sizeof(P_JUNCTION) - 1},
				[E_JUNCTION_LOW_L] = {P_JUNCTION_LOW_L, sizeof(P_JUNCTION_LOW_L) - 1},
				[E_JUNCTION_LOW_R] = {P_JUNCTION_LOW_R, sizeof(P_JUNCTION_LOW_R) - 1},
				[E_JUNCTION_HIG_L] = {P_JUNCTION_HIG_L, sizeof(P_JUNCTION_HIG_L) - 1},
				[E_JUNCTION_HIG_R] = {P_JUNCTION_HIG_R, sizeof(P_JUNCTION_HIG_R) - 1},
			};

			const t_print_style	g_basic_style[10] = {
				[E_PAD] = {PAD, 1},
				[E_TRUNC] = {TRUNC, 1},
				[E_PREFIX] = {PREFIX, 1},
				[E_SUFFIX] = {SUFFIX, 1},
				[E_JUNCTION] = {JUNCTION, 1},
				[E_JUNCTION_LOW_L] = {JUNCTION_LOW_L, 1},
				[E_JUNCTION_LOW_R] = {JUNCTION_LOW_R, 1},
				[E_JUNCTION_HIG_L] = {JUNCTION_HIG_L, 1},
				[E_JUNCTION_HIG_R] = {JUNCTION_HIG_R, 1},
			};
			int	buffer_append_raw(t_buf *b, const char *src, int len)
			{
				const int	cur_len = b->s - b->str;

				if (cur_len + len >= b->capacity)
				{
					b->capacity += 5048;
					b->str = (char *)realloc(b->str, b->capacity);
					if (!b->str)
					{
						b->s = NULL;
						b->capacity = 0;
						return (1);
					}
					b->s = b->str + cur_len;
				}
				memcpy(b->s, src, len);
				b->s += len;
				return (0);
			}

			int	buffer_append(t_buf *b, t_style_match item)
			{
				if (b->pretty)
					return (buffer_append_raw(b, g_pretty_style[item].word,
											  g_pretty_style[item].len));
				return (buffer_append_raw(b, g_basic_style[item].word,
										  g_basic_style[item].len));
			}
			int	buffer_trim_to_newline(t_buf *b)
			{
				while (b->s > b->str && *(b->s - 1) == ' ')
					b->s--;
				return (buffer_append_raw(b, "\n", 1));
			}
			int	buffer_append_mul(t_buf *b, t_style_match item, int repeat)
			{
				int		ret;

				if (repeat < 0)
					return (0);
				ret = 0;
				while (!ret && repeat--)
					ret = buffer_append(b, item);
				return (ret);
			}
			int	buffer_connect_leaf(t_buf *b, int is_l, int len, int *cumul)
			{
				*cumul += len;
				if (is_l)
					return (buffer_append(b, E_JUNCTION_LOW_L)
							|| buffer_append_mul(b, E_JUNCTION, len - 2)
							|| buffer_append(b, E_JUNCTION_HIG_L)
						   );
				return (buffer_append(b, E_JUNCTION_HIG_R)
						|| buffer_append_mul(b, E_JUNCTION, len - 2)
						|| buffer_append(b, E_JUNCTION_LOW_R));
			}
			int	print_connect(t_buf *b, int *printed)
			{
				int		print;
				int		ret;
				int		tmp;

				if (is_null_node(left))
					print = tree_dsp.pos - 1;
				else
					print = left->tree_dsp.pos + left->tree_dsp.block_delta - 1;
				ret = buffer_append_mul(b, E_PAD, print);
				if (ret || is_null_node(left))
					tmp = tree_dsp.lwidth;
				else
				{
					ret = buffer_connect_leaf(b, 1, tree_dsp.pos - print, &print);
					tmp = left->tree_dsp.block_width + left->tree_dsp.block_delta;
				}
				if (!ret && !is_null_node(right))
				{
					tmp = right->tree_dsp.pos + right->tree_dsp.block_delta + tmp
						- tree_dsp.pos + is_null_node(left);
					ret = buffer_connect_leaf(b, 0, tmp, &print);
				}
				*printed += print;
				tree_dsp.depth = 0;
				return (ret);
			}
			int	print_label(t_buf *b, int *printed)
			{
				int			ret;
				std::string	val;
				val = "bonjour";

				ret = buffer_append_mul(b, E_PAD, tree_dsp.label_delta)
					|| buffer_append(b, E_PREFIX)
					|| buffer_append_raw(b, color == 1 ? "\033[31m" : "\033[34m", sizeof("\033[31m") - 1)
					|| buffer_append_raw(b, val.c_str(), tree_dsp.label_width - WORD_ADDED_WIDTH - tree_dsp.trunc)
					;
				if (!ret && tree_dsp.trunc)
					ret = buffer_append(b, E_TRUNC);
				if (!ret)
					ret = buffer_append(b, E_SUFFIX);
				*printed += tree_dsp.label_width + tree_dsp.label_delta;
				tree_dsp.depth = 2;
				return (ret);
			}
			int	layer_print_specific(t_buf *b, int (Node::*layer_fn)(t_buf *b, int *printed), int *ret)
			{
				int		print;

				if (*ret)
					return (0);
				print = tree_dsp.block_delta;
				*ret = buffer_append_mul(b, E_PAD, tree_dsp.block_delta);
				if (!*ret && tree_dsp.depth == 0)
				{
					if (!is_null_node(left))
						print += left->layer_print_specific(b, layer_fn, ret);
					else
					{
						print += tree_dsp.lwidth;
						*ret = buffer_append_mul(b, E_PAD, tree_dsp.lwidth);
					}
					if (!*ret && !is_null_node(right))
						print += right->layer_print_specific(b, layer_fn, ret);
				}
				else if (!*ret)
					*ret = (this->*layer_fn)(b, &print);
				if (!*ret)
					*ret = buffer_append_mul(b, E_PAD,
											 tree_dsp.block_width + tree_dsp.block_delta - print);
				return (tree_dsp.block_width + tree_dsp.block_delta);
			}
			int	layer_print_tree(int max_depth, int fd, int pretty)
			{
				t_buf	b;
				int		ret;

				ret = 0;
				bzero(&b, sizeof(t_buf));
				b.pretty = pretty;
				while (!ret && max_depth >= 0)
				{
					layer_print_specific(&b, &Node::print_label, &ret);
					if (!ret)
						ret = buffer_trim_to_newline(&b);
					if (max_depth--)
					{
						if (!ret)
							layer_print_specific(&b, &Node::print_connect, &ret);
						if (!ret)
							ret = buffer_trim_to_newline(&b);
					}
				}
				if (!ret)
					ret = buffer_append_raw(&b, "\0", 1);
				if (!ret)
					dprintf(fd, "%s", b.str);
				free(b.str);
				return (ret);
			}

			void	label_adjust()
			{
				tree_dsp.label_delta = tree_dsp.pos - tree_dsp.label_width / 2 - 1;
				if (tree_dsp.label_delta < 0)
				{
					tree_dsp.pos -= tree_dsp.label_delta;
					tree_dsp.label_delta = 0;
				}
			}

			void	pos_calc(int depth_left, int depth_right)
			{
				tree_dsp.block_width = std::max(tree_dsp.lwidth + tree_dsp.rwidth + 1, tree_dsp.label_width);
				if (depth_left && depth_right) {
					t_tree_display *l = &left->tree_dsp;
					t_tree_display *r = &right->tree_dsp;
					const int	lpos = l->block_delta + std::max(l->pos + 1, l->pos + (l->label_width - tree_dsp.label_width) / 2);
					const int	rpos = l->block_width + l->block_delta + r->block_delta + std::min(r->pos - 1, r->pos + (r->label_width - tree_dsp.label_width) / 2);
					tree_dsp.pos = (lpos + rpos) / 2;
				} else if (depth_left){
					t_tree_display *l = &left->tree_dsp;
					tree_dsp.pos = l->block_delta + std::max(l->pos + 1, l->pos + (l->label_width - tree_dsp.label_width) / 2);
					if (tree_dsp.lwidth > tree_dsp.label_width)
						--tree_dsp.block_width;
					tree_dsp.rwidth = tree_dsp.block_width - tree_dsp.lwidth;
				} else if (depth_right) {
					t_tree_display *r = &right->tree_dsp;
					const int	rpos = r->block_delta + std::min(r->pos - 1, r->pos + (r->label_width - tree_dsp.label_width) / 2);
					tree_dsp.pos = rpos;
					if (tree_dsp.rwidth > tree_dsp.label_width)
						--tree_dsp.block_width;
					tree_dsp.lwidth = tree_dsp.block_width - tree_dsp.rwidth;
				}
				else
					tree_dsp.pos = tree_dsp.block_width / 2 + 1;
			}

			void	delta_adjust(int depth_left, int depth_right)
			{
				const int	delta = tree_dsp.label_width
					- (tree_dsp.lwidth + tree_dsp.rwidth + 1);

				if (!depth_left || !depth_right)
					return;
				if (delta > 0)
				{
					right->tree_dsp.block_delta = (delta + 1) / 2;
					left->tree_dsp.block_delta = delta - right->tree_dsp.block_delta;
				}
				else
					right->tree_dsp.block_delta = 1;
			}

			void	init_calc()
			{
				std::string	val;
				val = "bonjour";
				
				bzero(&tree_dsp, sizeof(t_tree_display));
				tree_dsp.depth = 1;
				tree_dsp.label_width = var.size();

				if (tree_dsp.label_width > MAX_WORD_WIDTH)
					tree_dsp.trunc = 1;
				tree_dsp.label_width = std::min(tree_dsp.label_width, MAX_WORD_WIDTH) + WORD_ADDED_WIDTH;
			}
			static int	_calc_depth(Node *tree, int depth)
			{
				int				depth_left;
				int				depth_right;

				if (!tree || tree->color == SENTINEL)
					return (0);
				tree->init_calc();
				depth_left = _calc_depth(tree->left, depth + 1);
				depth_right = _calc_depth(tree->right, depth + 1);
				tree->tree_dsp.lwidth = depth_left ? tree->left->tree_dsp.block_width : 0;
				tree->tree_dsp.rwidth = depth_right ? tree->right->tree_dsp.block_width : 0;
				tree->delta_adjust(depth_left, depth_right);
				tree->pos_calc(depth_left, depth_right);
				tree->label_adjust();
				return (std::max(depth, std::max(depth_left, depth_right)));
			}

			static int	_print_tree(Node *root, int pretty, int fd)
			{
				int				ret;

				if (!root)
				{
					if (pretty)
						dprintf(fd, "\033[31mCannot print a NULL tree\033[0m\n");
					else
						dprintf(fd, "Cannot print a NULL tree\n");
					return (0);
				}
				ret = root->layer_print_tree(_calc_depth(root, 0), fd, pretty);
				if (ret)
				{
					if (pretty)
						dprintf(fd, "\033[31mMemory error while printing tree\033[0m\n");
					else
						dprintf(fd, "Memory error while printing tree");
				}
				return (ret);
			}

#endif

		};
};

#endif
