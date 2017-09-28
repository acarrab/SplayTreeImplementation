# Splay Tree Implementation

This is an implementation of the splay tree data structure. I made it as a random project.
It uses an operation called Usurp, which just makes a node take the place of a parent node.
You can use a method like this or rotations, but with this you do not have to specifiy things based upon
the side of a node we are placed on.

`SplayWithSize.cpp` is an example of augmenting a splay tree with size so that you can do things
like determine the rank of an element by splaying it to the top of the tree, then looking at the left
childs size.

The operations are visualized using a reverse printed eulerian traversal so that if you look at the output
on the terminal bottom to top, that is correspondingly left to right.

for example:

        [1]
       /   \
    [2]     [3]

would correspond to

    1
      3
      3
      3
    1
      2
      2
      2
    1


There are also some ways to mess with the splay tree with the 
commands 

- `p` : prints the tree
- `i x` : inserts number, for example '`i 10`' inserts 10 into the tree
- `s x` : splays a value to the top of the tree, for example '`i 7`' splays 7 or its predecessor or sucessor to the top of the tree


Operations done are `O(log(n))` amortized time.