#!/usr/bin/env python

# =============================================================================
import itertools
import abc
import typing
import decimal
import sqlite3
# -----------------------------------------------------------------------------

# =============================================================================
class NodeGeneric(abc.ABC):

    # =========================================================================
    count = 0

    # -------------------------------------------------------------------------

    # =========================================================================
    def __init__(self, left=None, right=None):
        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        self.__class__.count += 1
        self.index = self.count
        self.left = left
        self.right = right
        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    # -------------------------------------------------------------------------

    # =========================================================================
    @abc.abstractmethod
    def __str__(self):
        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        raise NotImplementedError()
        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    # -------------------------------------------------------------------------

    # =========================================================================
    def __len__(self):
        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        num_len = 1
        if self.left is not None:
            num_len += len(self.left)
        if self.right is not None:
            num_len += len(self.right)
        return num_len
        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    # -------------------------------------------------------------------------

    # =========================================================================
    def is_leaf(self):
        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        return (self.left is None) and (self.right is None)
        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # -------------------------------------------------------------------------

# -----------------------------------------------------------------------------

# =============================================================================
class NodePostOrderLabel(NodeGeneric):

    # =========================================================================
    str_label_leaf = '1'
    str_label_tree = '0'
    # -------------------------------------------------------------------------

    # =========================================================================
    def __str__(self):
        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        if self.is_leaf():
            return self.str_label_leaf
        else:
            str_format = '{left}{right}' + self.str_label_tree
            return str_format.format(left=self.left, right=self.right)
        # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # -------------------------------------------------------------------------

# -----------------------------------------------------------------------------

# =============================================================================
def all_possible_trees(n, nodeType):
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    if n == 1:
        yield nodeType()
    for split in range(1, n):
        gen_left = all_possible_trees(split, nodeType)
        gen_right = all_possible_trees(n - split, nodeType)
        for left, right in itertools.product(gen_left, gen_right):
            yield nodeType(left, right)
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# -----------------------------------------------------------------------------

# =============================================================================
def all_possible_tuples(l, k):
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    if l==0:
        yield tuple()
    else:
        for i in range(k):
            for L in all_possible_tuples(l-1, k):
                yield (i,) + L
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# -----------------------------------------------------------------------------

# =============================================================================
def len_of_int(n: int) -> int:
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    return len(str(n))
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# -----------------------------------------------------------------------------

# =============================================================================
def to_int(n) -> int:
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    return int(round(n))
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# -----------------------------------------------------------------------------

# =============================================================================
def concatenate_numbers(a,b) -> decimal.Decimal:
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    try:
        return decimal.Decimal(str(round(a)) + str(round(abs(b))))
    except ValueError:
        return decimal.Decimal('NaN')
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# -----------------------------------------------------------------------------

# =============================================================================
dict_all_op_funcs = dict((
    ('+', lambda x,y: (x+y)), # 0 + addition
    ('-', lambda x,y: (x-y)), # 1 - subtraction
    ('*', lambda x,y: (x*y)), # 2 * multiplication
    ('/', lambda x,y: (x/y)), # 3 / division
    ('^', lambda x,y: (x**y)), # 4 exponentiation
    ('|', lambda x,y: concatenate_numbers(x,y)) # 5 concatenation
))
list_all_op_names = list(dict_all_op_funcs.keys())
list_op_indices = [0,1,2,5]
num_op_count = len(list_op_indices)
list_op_names = [list_all_op_names[n] for n in list_op_indices]
# -----------------------------------------------------------------------------

# =============================================================================
def postfix_expression(node_tree, tuple_operators, tuple_operands) -> typing.Iterable:
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # tuple_operators has indices only:
    tuple_operators = tuple(list_op_names[idx] for idx in tuple_operators)

    str_operand_lbl = NodePostOrderLabel.str_label_leaf
    str_operator_lbl = NodePostOrderLabel.str_label_tree

    str_tree = str(node_tree)
    list_tree = list(str_tree)
    list_expression = [None] * len(list_tree)

    num_operand_idx = 0
    num_operator_idx = 0
    for num_idx, elem in enumerate(list_tree):

        if elem == str_operand_lbl:
            list_expression[num_idx] = tuple_operands[num_operand_idx]
            num_operand_idx += 1

        elif elem == str_operator_lbl:
            list_expression[num_idx] = tuple_operators[num_operator_idx]
            num_operator_idx += 1

    return list_expression
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# -----------------------------------------------------------------------------

# =============================================================================
def evaluate_expression(str_expression: str):
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    list_stack = []
    list_expression = list(str_expression)
    for elem in list_expression:
        if elem in list_op_names:
            op_right = list_stack.pop()
            op_left = list_stack.pop()
            try:
                dec_val = dict_all_op_funcs[elem](op_left, op_right)
            except decimal.DecimalException:
                dec_val = decimal.Decimal('NaN')
            list_stack.append(dec_val)
        else:
            #list_stack.append(decimal.Decimal(elem))
            list_stack.append(int(elem))

    return str_expression, list_stack[0]
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# -----------------------------------------------------------------------------

list_num_cache = []
list_data_cache = []

# =============================================================================
def iterate_evaluations(num_max_value):
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    num_leave_count = 9

    tuple_operand_ints = tuple(range(1, num_leave_count + 1))
    tuple_operand_strings = tuple(map(str, tuple_operand_ints))

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # create recursive generator:
    gen_tuples = all_possible_tuples(num_leave_count - 1, num_op_count)
    gen_trees = all_possible_trees(num_leave_count, NodePostOrderLabel)
    gen_trees = (postfix_expression(
        node, ops, tuple_operand_strings)
        for (node, ops) in itertools.product(gen_trees, gen_tuples))
    #gen_trees = ((tree, list('01-') + tree[1:]) for tree in gen_trees)
    #gen_trees = (tree for sublist in gen_trees for tree in sublist)
    gen_trees = (''.join(tree) for tree in gen_trees)
    gen_vals = (evaluate_expression(tree) for tree in gen_trees)

    num_max_count = 2 * abs(num_max_value) + 1
    for num_idx, (str_tree, value) in enumerate(gen_vals):

        if (abs(value) <= num_max_value) and (value not in list_num_cache):
            list_num_cache.append(value)
            tuple_data = (num_idx, str_tree, str(value))
            list_data_cache.append(tuple_data)
            #print('%u %s [%s]' % tuple_data, end='')
            #print(' (max=%d, count=%u)' % (num_max_value, len(list_data_cache)))
        #else:
            #print(len(list_data_cache), end='\n')

        if len(list_data_cache) == num_max_count:
            break
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# -----------------------------------------------------------------------------

# =============================================================================
def main():
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    proc_eval = Process(target=iterate_evaluations, args=(9999,))
    proc_eval.start()
    while proc_eval.is_alive():
        print(len(list_num_cache))
        proc_eval.join(2)

    list_data_cache.sort(key=lambda elem: int(elem[2]))
    for tuple_data in list_data_cache:
        print(tuple_data)

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# -----------------------------------------------------------------------------


# =============================================================================
if __name__ == '__main__':
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    from multiprocessing import Process

    main()
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# -----------------------------------------------------------------------------