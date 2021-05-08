current project overview:
tuple.c: defines Tuple struct, which is 3 float/int unions together with a float. This is meant to represent points and vectors,
    differentiated by the last float. This seems inefficient and the reason for doing this has yet to become clear to me. The only apparent
    "benefit" is to allow 3d translations to be represented as linear transformations on a 4d space where all vectors have w component
    of 1, and therefore allow matrix multiplication as a method to compose translations with rotations, reflections, and shears; this seems
    even more inefficient. The int options are to allow Tuples to be used to represent colors as well. This has got to be the worst library
    in the project so far.
color.c: defines Color, Canvas struct. currently Color is an alias for Tuple. Associated functions include file output.
matrix.c: confusingly does not define a Matrix struct, only an M4 struct (4X4 matrix).
    Most functions support smaller matrices, which are stored as subsets of an M4. constructor functions for transformation matrices only
    create 4X4 matrices.
sdl_graphics.c: defines functions to easily display images with SDL. Currently only allows reading from file, not dealing with Canvas
    objects directly
