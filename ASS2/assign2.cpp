//
//  assign2.cpp
//  C++Assignment2
//
//  Created by CHYEN on 2022/3/31.
//

#include "assign2.hpp"

assign2_exception::exception add_node(tree_node *father, tree_node *child, int child_direction)
{
    assign2_exception::exception e = 0;
    if (father == nullptr)
    {
        e |= NULL_POINTER_EXCEPTION;
    }
    if (child == nullptr)
    {
        e |= NULL_POINTER_EXCEPTION;
    }else if (child->father != nullptr){
        e |= DUPLICATED_FATHER_EXCEPTION;
    }
    if (child_direction != CHILD_DIRECTION_LEFT && child_direction != CHILD_DIRECTION_RIGHT) {
        e |= INVALID_CHILD_DIRECTION_EXCEPTION;
    }
    if (father != nullptr && child != nullptr) {
        if (child->father != nullptr) {
            e |= DUPLICATED_FATHER_EXCEPTION;
        }else{
            child->father = father;
        }
        switch (child_direction)
        {
        case CHILD_DIRECTION_LEFT:
                if (father->l_child == nullptr){
                    father->l_child = child;
                    father->tree_count += child->tree_count;
                }
            else
                e |= DUPLICATED_LEFT_CHILD_EXCEPTION;
            break;
        case CHILD_DIRECTION_RIGHT:
                if (father->r_child == nullptr){
                    father->r_child = child;
                    father->tree_count += child->tree_count;
                }
            else
                e |= DUPLICATED_RIGHT_CHILD_EXCEPTION;
            break;
        default:
            e |= INVALID_CHILD_DIRECTION_EXCEPTION;
            break;
        }
    }
    return e;
}

assign2_exception::exception judge_child_direction(tree_node *node, int *child_direction)
{
    assign2_exception::exception e = 0;

    if (node == nullptr || child_direction == nullptr)
    {
        e |= NULL_POINTER_EXCEPTION;
    }

    if (node != nullptr && node->father == nullptr)
    {
        e |= ROOTS_FATHER_EXCEPTION;
        
    }
    if (node != nullptr && child_direction != nullptr && node->father != nullptr) {
        if (node->father->l_child == node) {
            *child_direction = CHILD_DIRECTION_LEFT;
        }
        if (node->father->r_child == node) {
            *child_direction = CHILD_DIRECTION_RIGHT;
        }
        if (node->data > node->father->data)
            *child_direction = CHILD_DIRECTION_RIGHT;
        if (node->data < node->father->data)
            *child_direction = CHILD_DIRECTION_LEFT;
    }
    return e;
}

assign2_exception::exception insert_into_BST(BST *bst, uint64_t data, tree_node **inserted_node)
{
    assign2_exception::exception e = 0;
    if (bst == nullptr || inserted_node == nullptr) {
        e |= NULL_POINTER_EXCEPTION;
    }
    if (bst != nullptr && bst->comp == nullptr) {
        e |= NULL_COMP_FUNCTION_EXCEPTION;
    }
    if (bst != nullptr && inserted_node != nullptr && bst->comp != nullptr) {
        tree_node *node = new tree_node;
        node->data = data;
        node->father = node->l_child = node->r_child = nullptr;
        node->node_count = 1;
        node->tree_count = 1;
        if (bst->root == nullptr)
        {
            bst->root = node;
            *inserted_node = node;
            return e;
        }
        delete node;
        if (bst->comp( data , bst->root->data) < 0)
        {
            BST *new_bst = new BST;
            new_bst->comp = bst->comp;
            new_bst->root = bst->root->l_child;
            e |= insert_into_BST(new_bst, data, inserted_node);
//            add_node(bst->root, new_bst->root, CHILD_DIRECTION_LEFT);
//            ADD_NODE_LEFT(bst->root, new_bst->root);
            {
                bst->root->l_child = new_bst->root;
                new_bst->root->father = bst->root;
                bst->root->tree_count ++;
            }

            delete new_bst;
        }
        else if (bst->comp(data , bst->root->data) > 0)
        {
            BST *new_bst = new BST;
            new_bst->comp = bst->comp;
            new_bst->root = bst->root->r_child;
            e |= insert_into_BST(new_bst, data, inserted_node);
//            add_node(bst->root, new_bst->root, CHILD_DIRECTION_RIGHT);
//            ADD_NODE_RIGHT(bst->root, new_bst->root);
            {
                bst->root->r_child = new_bst->root;
                new_bst->root->father = bst->root;
                bst->root->tree_count ++;
            }
            delete new_bst;
        }
        else if (bst->comp(data , bst->root->data) == 0)
        {
            bst->root->node_count++;
            bst->root->tree_count++;
        }
    }
    
    return e;
}

assign2_exception::exception find_in_BST(BST *bst, uint64_t data, tree_node **target_node)
{
    assign2_exception::exception e = 0;
    if (bst == nullptr || target_node == nullptr) {
        e |= NULL_POINTER_EXCEPTION;
    }
    if (bst != nullptr && bst->comp == nullptr) {
        e |= NULL_COMP_FUNCTION_EXCEPTION;
    }
    if (bst != nullptr && target_node != nullptr && bst->comp != nullptr) {
        if (bst->root == nullptr){
            *target_node = nullptr;
            return e;
        }
        else if (bst->comp( bst->root->data , data) == 0) {
            (*target_node) = bst->root;
            return e;
        }
        else if (bst->comp( data , bst->root->data) < 0){
            BST *new_bst = new BST;
            new_bst->comp = bst->comp;
            new_bst->root = bst->root->l_child;
            find_in_BST(new_bst, data, target_node);
            delete new_bst;
        }
        else if (bst->comp(data, bst->root->data) > 0){
            BST *new_bst = new BST;
            new_bst->comp = bst->comp;
            new_bst->root = bst->root->r_child;
            find_in_BST(new_bst, data, target_node);
            delete new_bst;
        }
    }
    return e;
}

assign2_exception::exception splay(BST *bst, tree_node *node)
{
    assign2_exception::exception e = 0;
    if (bst == nullptr || node == nullptr) {
        e |= NULL_POINTER_EXCEPTION;
    }
    if (bst != nullptr && bst->comp == nullptr) {
        e |= NULL_COMP_FUNCTION_EXCEPTION;
    }
    if (bst != nullptr && node != nullptr && bst->comp != nullptr) {
        if (bst->root == nullptr) {
            e |= SPLAY_NODE_NOT_IN_TREE_EXCEPTION;
        }
        if (bst->root != nullptr) {
            if (bst->root == node) {
                return e;
            }
            if (bst->comp(node->data , bst->root->data)<0) {
                if (bst->root->l_child == nullptr) {
                    e |= SPLAY_NODE_NOT_IN_TREE_EXCEPTION;
                    return e;
                }
                if (bst->comp(node->data , bst->root->l_child->data)<0) {
                    BST* new_bst = new BST;
                    new_bst->comp = bst->comp;
                    new_bst->root = bst->root->l_child->l_child;
                    e |= splay(new_bst, node);
                    bst->root = right_rotation(bst->root);
                    update(bst->root->l_child);
                    update(bst->root);
                    delete new_bst;
                }
                else if (bst->comp(node->data , bst->root->l_child->data)>0){
                    BST* new_bst = new BST;
                    new_bst->comp = bst->comp;
                    new_bst->root = bst->root->l_child->r_child;
                    e |= splay(new_bst, node);
                    if (bst->root->l_child->r_child != nullptr) {
                        bst->root->l_child = left_rotation(bst->root->l_child);
                        update(bst->root->l_child->r_child);
                        update(bst->root->l_child);
                    }
                    delete new_bst;
                }
                bst->root = (bst->root->l_child == nullptr)? bst->root : right_rotation(bst->root);
                update(bst->root->l_child);
                update(bst->root);
                return e;
            }
            else{
                if (bst->root->r_child == nullptr) {
                    e |= SPLAY_NODE_NOT_IN_TREE_EXCEPTION;
                    return e;
                }
                if (bst->comp(node->data , bst->root->r_child->data)<0) {
                    BST* new_bst = new BST;
                    new_bst->comp = bst->comp;
                    new_bst->root = bst->root->r_child->l_child;
                    e |= splay(new_bst, node);
                    if (bst->root->r_child->l_child != nullptr) {
                        bst->root->r_child = right_rotation(bst->root->r_child);
                        update(bst->root->r_child->l_child);
                        update(bst->root->r_child);
                    }
                }
                else if (bst->comp(node->data , bst->root->r_child->data)>0){
                    BST* new_bst = new BST;
                    new_bst->comp = bst->comp;
                    new_bst->root = bst->root->r_child->r_child;
                    e |= splay(new_bst, node);
                    bst->root = left_rotation(bst->root);
                    update(bst->root->r_child);
                    update(bst->root);
                }
                bst->root = (bst->root->r_child == nullptr)? bst->root : left_rotation(bst->root);
                update(bst->root->r_child);
                update(bst->root);
                return e;
            }
        }
        
    }
    
    return e;
}

tree_node* right_rotation(tree_node* x){
    tree_node* y = x->l_child;
    x->l_child = y->r_child;
    y->r_child = x;
    return y;
}

tree_node* left_rotation(tree_node* x){
    tree_node* y = x->r_child;
    x->r_child = y->l_child;
    y->l_child = x;
    return y;
}

void update(tree_node* node){
    if (node != nullptr) {
        node->tree_count = ((node->l_child != nullptr)?node->l_child->tree_count:0) + ((node->r_child != nullptr)?node->r_child->tree_count:0) + node->node_count;
    }
}

void right_rotation(BST* bst){
    tree_node* new_root = bst->root->l_child;
    bst->root->l_child = new_root->r_child;
    new_root->r_child = bst->root;
    bst->root = new_root;
    update(bst->root->l_child);
    update(bst->root->r_child);
    update(bst->root);
}

void left_rotation(BST* bst){
    tree_node* new_root = bst->root->r_child;
    bst->root->r_child = new_root->l_child;
    new_root->l_child = bst->root;
    bst->root = new_root;
    update(bst->root->l_child);
    update(bst->root->r_child);
    update(bst->root);
}
