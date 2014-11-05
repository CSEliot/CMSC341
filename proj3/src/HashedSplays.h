#ifndef HASHEDSPLAYS_H
#define HASHEDSPLAYS_H
#include "SplayTree.h"
#include "Node.h"
#include "Util.h"
class HashedSplays
{
public:
    int m_trees;
    HashedSplays(int size);
    ~HashedSplays();

    /*ATTEMPTS to read in file, should fail and throw exception if it can't.
     * Pre: A valid filename in the local workspace
     * Post: file is loaded to be read from.
     */
    void FileReader(std::string inFileName);

    /*Prints the given tree by number, a being 0, b being 1, etc.
     * Pre: a valid number 0 - size m_trees - 1
     * Post: A printed format of the given tree.
     */
    void PrintTree(int index);

    /*Prints the given tree by letter, a being 0, b being 1, etc.
     * Pre: a valid letter a-z
     * Post: A printed format of the given tree.
     */
    void PrintTree(std::string letter);

    /*Prints the root value (to the screen) at each index in order and display
     *how many nodes each tree contains.
     * Pre: None
     * Post: Printed statement.
     */
    void PrintHashCounts();

    /*Find words within a certain tree index
     * Pre: A pattern to parse a tree for.
     * Post: The printed value of all matching strings.
     */
    void FindAll(std::string inPart);

private:
    SplayTree<Node> *table; //exists to be overwritten in constructor
    std::string GetIndex(std::string inLetter);

};

#endif // HASHEDSPLAYS_H
