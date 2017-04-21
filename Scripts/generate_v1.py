#!/usr/bin/env python
import itertools

def gendistinct(n):
    leafnode = 'L'
    dp = []
    newset = set()
    newset.add(leafnode)
    dp.append(newset)
    for i in range(1,n):
        newset = set()
        for j in range(i):
            for leftchild in dp[j]:
                for rightchild in dp[i-j-1]:
                    newset.add('(' + '.' + leftchild + rightchild + ')')
        dp.append(newset)
    return dp[-1]

# https://cs.stackexchange.com/questions/40931/enumerating-all-n-tuples-over-a-finite-domain
"""
Here f(l, k) produces all lists of length l all of whose entries are in the 
range 0..k-1. The idea is that if you have all lists of length l-1 (the 
output of f(l-1, k)) you can use that to generate all lists of length l, by 
using a for-loop.
"""
def all_possible_tuples(l, k):
    if l==0:
        yield []
    else:
        for i in range(k):
            for L in all_possible_tuples(l-1, k):
                yield [i]+L

str_leaf = 'X'

def all_possible_trees(n):
    if n == 1:
        yield str_leaf
    for split in range(1, n):
        gen_left = all_possible_trees(split)
        gen_right = all_possible_trees(n-split)
        for left, right in itertools.product(gen_left, gen_right):
            yield [left, right]

def all_possible_trees2(n):
    if n == 1:
        return str_leaf
    list_nodes = list()
    for split in range(1, n):
        gen_left = all_possible_trees(split)
        gen_right = all_possible_trees(n - split)
        for left, right in itertools.product(gen_left, gen_right):
            list_nodes.append([left, right])
    return list_nodes

# http://stackoverflow.com/questions/21447599/getting-the-number-of-digits-of-nonnegative-integers-python

def do_all_possible_trees():

    num_leaf_count = 9

    list_op_names = ['+','-','*','|']
    list_op_funcs = [lambda x,y: (x+y), lambda x,y: (x-y), lambda x,y: (x*y), lambda x,y: x*10**len(str(abs(int(y))))+y]
    num_op_count = len(list_op_names)

    list_op_idxlists = list(all_possible_tuples(num_leaf_count - 1, num_op_count))

    for list_tree in all_possible_trees(num_leaf_count):
        str_thing = str(list_tree)

        num_idx0 = 0
        num_idx1 = 1
        while (num_idx0 >= 0) and (num_idx1 <= num_leaf_count):
            num_idx0 = str_thing.find(str_leaf)
            str_thing = str_thing[0:num_idx0] \
                        + str(num_idx1) \
                        + str_thing[(num_idx0 + 1):]
            num_idx1 += 1
        del num_idx1, num_idx0

        print(str_thing)

        del list_tree

def do_gendistinct():
    #alltrees = gendistinct(4)
    #for tree in alltrees:
    #    print(tree)
    #import sys
    #n = int(sys.argv[1])
    pass

if __name__ == '__main__':
    for thing in all_possible_trees(4):
        print(thing)

    #list_tuples = tuple(all_possible_tuples(8, 4))
    #for num_idx, thing in enumerate(list_tuples):
    #    print(str(num_idx), end=': ')
    #    print(thing)
