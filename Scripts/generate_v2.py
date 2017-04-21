#!/usr/bin/env python
import itertools

# catalan numbers C_0, ..., C_30:
list_catalan = [
    1,1,2,5,14,42,132,429,1430,4862,16796,58786,
    208012,742900,2674440,9694845,35357670,129644790,
    477638700,1767263190,6564120420,24466267020,
    91482563640,343059613650,1289904147324,
    4861946401452,18367353072152,69533550916004,
    263747951750360,1002242216651368,3814986502092304]

def all_possible_trees_1(n):
    if n == 1:
        yield 'L'
    for split in range(1, n):
        gen_left = all_possible_trees_1(split)
        gen_right = all_possible_trees_1(n-split)
        for left, right in itertools.product(gen_left, gen_right):
            yield [left, right]

def all_possible_trees_2(n):
    if n == 1:
        return 'L'
    list_nodes = list()
    for split in range(1, n):
        gen_left = all_possible_trees_2(split)
        gen_right = all_possible_trees_2(n - split)
        for l in gen_left:
            for r in gen_right:
                list_nodes.append([l,r])
    return list_nodes

class Node:

    count = 0

    def __init__(self, left=None, right=None):
        self.__class__.count += 1
        self.index = self.count
        self.left = left
        self.right = right

    def __str__(self):
        str_format = '{left}{right}0 '
        if self.is_leaf():
            return '1 '
            #return str_format.format(index='', left='', right='')
        else:
            return str_format.format(left=self.left, right=self.right)

    def __len__(self):
        num_len = 1
        if self.left is not None:
            num_len += len(self.left)
        if self.right is not None:
            num_len += len(self.right)
        return num_len

    def is_leaf(self):
        return (self.left is None) and (self.right is None)

def all_possible_trees_2b(n):

    list_nodes = [Node()] * list_catalan[(n - 1)]

    #if n == 1:
    #    return [Node()]

    num_rotIdx = 0
    for split in range(1, n):
        list_left = all_possible_trees_2b(split)
        list_right = all_possible_trees_2b(n - split)

        num_leftLen = len(list_left)#; print(num_leftLen)
        num_rightLen = len(list_right)#; print(num_rightLen)

        for num_leftIdx in range(num_leftLen):
            for num_rightIdx in range(num_rightLen):
                list_currRotLeft = list_left[num_leftIdx]
                list_currRotRight = list_right[num_rightIdx]
                list_nodes[num_rotIdx] = Node(list_currRotLeft,list_currRotRight)
                num_rotIdx += 1
    return list_nodes

def all_possible_trees_3(n, level=0):
    print_pad = lambda m : print((' ' * level) + m)

    print_pad('all_possible_trees_3({},{})'.format(n,level))
    if n == 1:
        print('  returning 1 leaf object "L"')
        return 'L'

    print_pad('  creating new empty "list_nodes" ...')
    list_nodes = list()
    for split in range(1, n):
        print_pad('    split=({},{})'.format(split,n-split))
        gen_left = all_possible_trees_3(split,level+2)
        print_pad('    recursive call (left) ... RETURNED')
        print_pad('    "gen_left" ({} elems): {}'.format(len(gen_left),
                                                   str(gen_left)))

        gen_right = all_possible_trees_3(n - split,level+2)
        print_pad('    recursive call (right) ... RETURNED')
        print_pad('    "gen_right" ({} elems): {}'.format(len(gen_right),
                                                   str(gen_right)))

        print_pad('    iterating over (sub-)trees with same split:')
        for l in gen_left:
            for r in gen_right:
                print_pad('      appending: {} to "list_nodes"'.format(str([l,r])))
                list_nodes.append([l,r])

    print_pad('  returning "list_nodes" ({} elems):'.format(len(list_nodes)))
    print_pad('    {}'.format(str(list_nodes)))
    return list_nodes

if __name__ == '__main__':
    list_trees = all_possible_trees_2b(12)
    list_tree_strings = [str(tree) for tree in list_trees]

    set_seen = set()
    list_uniq = []
    for x in list_tree_strings:
        if x not in set_seen:
            list_uniq.append(x)
            set_seen.add(x)
        del x



    for idx,s in enumerate(list_tree_strings):
        print('%u %s' % (idx, s))
        del s, idx

    print('trees %u' % len(list_tree_strings))
    print('uniq %u' % len(list_uniq))