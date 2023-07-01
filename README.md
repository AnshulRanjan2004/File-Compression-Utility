# File-Compression-Utility
We use **Huffman's algorithm** to construct **a tree** that is used for data compression. 
We assume that each character has an associated weight equal to the number of times the character occurs in a file,
When compressing a file we'll need to calculate these weights.

## Huffman Coding Algorithm Description

Huffman's algorithm assumes that we're building a single tree from a group (or forest) of trees. 
Initially, all the trees have a single node with a character and the character's weight. 
Trees are combined by picking two trees, and making a new tree from the two trees. 
This decreases the number of trees by one at each step since two trees are combined into one tree.

### Algorithm Steps:

1. Begin with a forest of trees. All trees are one node, with the weight of the tree equal to the weight of the character in the node. 
Characters that occur most frequently have the highest weights. Characters that occur least frequently have the smallest weights.
Repeat this step until there is only one tree.

2. Choose two trees with the smallest weights, call these trees T1 and T2. Create a new tree whose root has a weight equal to the sum of the weights T1 + T2 and whose left subtree is T1 and whose right subtree is T2.

3. The single tree left after the previous step is an optimal encoding tree.

<p align='center'><img src='https://upload.wikimedia.org/wikipedia/commons/d/d8/HuffmanCodeAlg.png'/></p>

### Main Data Structures Used

#### vector<Node*>:
This vector is used to store pointers to Node objects. It is used to represent the 128 tree nodes corresponding to characters with ASCII values from 0 to 127, along with their frequencies.
#### priority_queue<Node*, vector<Node*>, Compare>:
This priority queue is used to create a min-heap of Node pointers based on their frequencies. It is used during the Huffman tree construction and encoding process.
#### fstream source, destination: 
These objects are used to handle file input and output operations. source is used to read data from the source file, and destination is used to write data to the destination file.

## Class diagram

![WhatsApp Image 2023-07-01 at 10 31 46](https://github.com/AnshulRanjan2004/File-Compression-Utility/assets/91585064/2fc7688b-ec56-45f3-adb6-4c3d22ef281f)

### Running the Program
Complie:
```bat
g++ -o <name-you-want-to-give> main.cpp
```
Running:
```bat
./myprogram.exe
```
