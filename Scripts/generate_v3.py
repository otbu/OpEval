#!/usr/bin/env python


# catalan numbers C_0, ..., C_30:
list_catalan = [
    1,1,2,5,14,42,132,429,1430,4862,16796,58786,
    208012,742900,2674440,9694845,35357670,129644790,
    477638700,1767263190,6564120420,24466267020,
    91482563640,343059613650,1289904147324,
    4861946401452,18367353072152,69533550916004,
    263747951750360,1002242216651368,3814986502092304]

def len_of_int(n: int) -> int:
    return len(str(n))

def float_to_int(n: float) -> int:
   return int(round(abs(n)))

list_op_names = ['+','-','*','|']
list_op_funcs = [lambda x,y: (x+y),
                 lambda x,y: (x-y),
                 lambda x,y: (x*y),
                 lambda x,y: x*10**len_of_int(int(round(abs(y)))) + int(round(abs(y)))]
num_op_count = len(list_op_names)

class Node:

    count = 0

    def __init__(self, left=None, right=None):
        self.__class__.count += 1
        self.index = self.count
        self.left = left
        self.right = right

    def __str__(self):
        str_format = '{left}{right}0'
        if self.is_leaf():
            return '1'
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

def all_possible_trees(n):
    list_nodes = [Node()] * list_catalan[(n - 1)]
    num_rotIdx = 0
    for split in range(1, n):
        list_left = all_possible_trees(split)
        list_right = all_possible_trees(n - split)

        num_leftLen = len(list_left)#; print(num_leftLen)
        num_rightLen = len(list_right)#; print(num_rightLen)

        for num_leftIdx in range(num_leftLen):
            for num_rightIdx in range(num_rightLen):
                list_currRotLeft = list_left[num_leftIdx]
                list_currRotRight = list_right[num_rightIdx]
                list_nodes[num_rotIdx] = Node(list_currRotLeft,list_currRotRight)
                num_rotIdx += 1
    return list_nodes

