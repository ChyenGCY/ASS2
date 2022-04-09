//
//  mytest.cpp
//  C++Assignment2
//
//  Created by CHYEN on 2022/4/5.
//

#include "mytest.hpp"

int main(){
    BST *bst = new BST;
    tree_node *node = new tree_node;
    node->data = 50;
    node->l_child = NULL;
    node->r_child = NULL;
    node->father = NULL;
    node->node_count = 1;
    node->tree_count = 1;
    bst->root = node;
    bst->comp = comp;
    tree_node *targetnode;
    // std::cout<<"wrong\n";
    insert_into_BST(bst, 20, &targetnode);
    insert_into_BST(bst, 10, &targetnode);
    insert_into_BST(bst, 30, &targetnode);
    insert_into_BST(bst, 60, &targetnode);
    insert_into_BST(bst, 55, &targetnode);
    insert_into_BST(bst, 100, &targetnode);
    splay(bst, bst->root->l_child);
    std::string *s1 = new std::string;
    inorder(bst, s1);
    std::cout<<*s1<<std::endl;
}

int comp(uint64_t a, uint64_t b)
{
    if (a == b)
        return 0;
    else if (a > b)
        return 1;
    else
        return -1;
};

void inorder(BST *const bst, std::string *s)
{
    if (bst->root != NULL)
    {
        if (bst->root->l_child != NULL)
        {
            BST *new_bst = new BST;
            new_bst->comp = bst->comp;
            new_bst->root = bst->root->l_child;
            inorder(new_bst, s);
            delete new_bst;
            new_bst = NULL;
        }
        // std::cout<<bst->root->data<<" "<<bst->root->node_count<<" "<<bst->root->tree_count<<"\n";
        s->append(std::to_string(bst->root->data));
        s->append(" ");
        s->append(std::to_string(bst->root->node_count));
        s->append(" ");
        s->append(std::to_string(bst->root->tree_count));
        s->append(" ");
        if (bst->root->r_child != NULL)
        {
            BST *new_bst = new BST;
            new_bst->comp = bst->comp;
            new_bst->root = bst->root->r_child;
            inorder(new_bst, s);
            delete new_bst;
            new_bst = NULL;
        }
    }
    else
        return;
};

void preorder(BST *const bst, std::string *s)
{
    if (bst->root != NULL)
    {
        // std::cout<<bst->root->data<<" "<<bst->root->node_count<<" "<<bst->root->tree_count<<"\n";
        s->append(std::to_string(bst->root->data));
        s->append(" ");
        s->append(std::to_string(bst->root->node_count));
        s->append(" ");
        s->append(std::to_string(bst->root->tree_count));
        s->append(" ");
        if (bst->root->l_child != NULL)
        {
            BST *new_bst = new BST;
            new_bst->comp = bst->comp;
            new_bst->root = bst->root->l_child;
            preorder(new_bst, s);
            delete new_bst;
            new_bst = NULL;
        }
        if (bst->root->r_child != NULL)
        {
            BST *new_bst = new BST;
            new_bst->comp = bst->comp;
            new_bst->root = bst->root->r_child;
            preorder(new_bst, s);
            delete new_bst;
            new_bst = NULL;
        }
    }
    else
        return;
};
