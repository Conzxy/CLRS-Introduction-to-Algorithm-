//
// Created by 谁敢反对宁宁，我就打爆他狗头！ on 2021/1/23.
//

#ifndef ITA_RB_TREE_IMPL_H
#define ITA_RB_TREE_IMPL_H
#define rb_cnode typename rb_tree<T>::rb_node const
#include <iostream>
#include <rb_tree.h>

template<typename T>
rb_tree<T>::rb_tree():nil{new rb_node{T{},NIL,NIL,NIL,BLACK}},root(nil){
}

template<typename T>
rb_tree<T>::rb_tree(unsigned n){
    while(n--){
        T x;std::cin>>x;
        insert(x);
    }
}

template<typename T>
rb_tree<T>::rb_tree(rb_tree const& rhs)
:nil(new rb_node{*rhs.nil}),root{clone(rhs.root,rhs.nil)}{
}

template<typename T>
rb_tree<T>::rb_tree(rb_tree && rhs)noexcept
:nil(std::move(rhs.nil)),root{std::move(rhs.root)}{
    rhs.nil=rhs.root=NIL;
}

template<typename T>
typename rb_tree<T>::rb_node* rb_tree<T>::clone(rb_node* node,rb_node* old_nil){
    if(node == old_nil)
        return nil;
    else
        return new rb_node{node->key,clone(node->left,old_nil),clone(node->right,old_nil),
                           node->p,node->color};
}

template<typename T>
rb_tree<T>& rb_tree<T>::operator=(rb_tree<T> const& rhs){
    if(rhs!=this) {
        auto copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
}

template<typename T>
rb_tree<T>& rb_tree<T>::operator=(rb_tree && rhs)noexcept{
    std::swap(root,rhs.root);
    std::swap(nil,rhs.nil);
    rhs.root=rhs.nil=NIL;
    return *this;
}

template<typename T>
rb_tree<T>::~rb_tree(){
    destroy(root);
    delete nil;
}

template<typename T>
void rb_tree<T>::insert(T const& item){
    //node_p 跟踪node，指向其parents
    rb_node* node_p=nil;
    //find 找空地
    auto find=root;

    auto node=new rb_node{item,nil,nil,nil,RED};
    //开始寻找，当find找到空地时终止循环
    while(find!=nil){
        node_p=find;
        if(item<find->key) find=find->left;
        else find=find->right;
    }
    //链接node的parents
    node->p=node_p;
    //链接node_p与孩子
    //如果node_p为叶子，则改写root
    if(node_p==nil) root=node;
    else if(item<node_p->key) node_p->left=node;
    else node_p->right=node;
    //出现两个连续红节点，破坏了RB性质3
    insert_fixup(node);
}

template<typename T>
void rb_tree<T>::inOrderWalk(){
    inOrderWalk_AUX(root);
}

template<typename T>
void rb_tree<T>::inOrderWalk_AUX(rb_node const* node){
    if(node != nil){
        inOrderWalk_AUX(node->left);
        std::cout << node->key << "("
                  << (node->color==RED?"R":"B")<<") ";
        inOrderWalk_AUX(node->right);
    }
}

template<typename T>
rb_cnode* rb_tree<T>::search(T const& item){
    return searchIterative(root,item);
}

template<typename T>
rb_cnode* rb_tree<T>::searchRecursion(rb_node const* root,T const& item){
    if(root!=nil && root->key!=item){
        if(item<root->key)
            searchRecursion(root->left,item);
        else searchRecursion(root->right,item);
    }else return root;
}

template<typename T>
rb_cnode* rb_tree<T>::searchIterative(rb_node const* root,T const& item){
    while(root!=nil && root->key!=item){
        if(item<root->key)
            root=root->left;
        else root=root->right;
    }
    return root;
}

template<typename T>
rb_cnode* rb_tree<T>::maximum(){
    return maximum_AUX(root);
}
template<typename T>
rb_cnode* rb_tree<T>::maximum_AUX(rb_node const* root){
    while(root->right!=nil){
        root=root->right;
    }
    return root;
}

template<typename T>
rb_cnode* rb_tree<T>::minimum(){
    return minimum_AUX(root);
}

template<typename T>
rb_cnode* rb_tree<T>::minimum_AUX(rb_node const* root){
    while(root->left!=nil){
        root=root->left;
    }
    return root;
}

template<typename T>
rb_cnode* rb_tree<T>::successor(){
    if(root->right!=nil)
        return minimum_AUX(root->right);

    auto y=root->p;
    while(y!=nil && root==y->right){
        root=y;
        y=y->p;
    }
    return y;
}

template<typename T>
rb_cnode* rb_tree<T>::predecessor(){
    if(root->left!=nil)
        return maximum_AUX(root->left);

    auto y=root->p;
    while(y!=nil && y->left == root){
        root=y;
        y=y->p;
    }

    return y;
}

template<typename T>
void rb_tree<T>::transplant(rb_node *oldSub,rb_node *newSub){
    if(oldSub->p==nil)
        root=newSub;
    else{
        if(oldSub == oldSub->p->right)
            oldSub->p->right=newSub;
        else oldSub->p->left=newSub;
    }
    newSub->p=oldSub->p;
}

template<typename T>
void rb_tree<T>::remove(T const& item){
    //我们用node表示要删除点
    auto node=const_cast<rb_node*>(search(item));

    if(node==nil)
        return ;
    //old_node表示将被代替的节点
    //1:single or one child，要移去的点
    //2:后继
    auto old_node=node;
    auto old_original_color=old_node->color;
    //new_node表示替代old_node的节点
    rb_node* new_node;
    if(node->left==nil){
        new_node=old_node->right;
        transplant(node,node->right);
    }
    else if(node->right==nil) {
        new_node=old_node->left;
        transplant(node, node->left);
    }
    else{
        old_node=const_cast<rb_node*>(minimum_AUX(old_node->right));
        old_original_color=old_node->color;
        new_node=old_node->right;
        if(old_node->p == node)
            new_node->p = old_node;
        else{
            transplant(old_node,new_node);
            old_node->right=node->right;
            old_node->right->p=old_node;
        }
        transplant(node,old_node);
        old_node->left=node->left;
        old_node->left->p=old_node;
    }
    delete node;

    if(old_original_color==BLACK)
        remove_fixup(new_node);
}

template<typename T>
void rb_tree<T>::LR(rb_node* node){
    //Notice:先转交new_node的左子树，以及链接好node的parents，再旋转改变相对位置
    //因为若一开始就改变了相对位置，我们就丢失了node的parents和new_node的左子树的内存地址
    auto new_node=node->right;
    //转交左子树
    node->right=new_node->left;
    //链接子树的parents
    if(new_node->left != NIL)
        new_node->left->p=node;
    //链接new_node和node's parents
    new_node->p = node->p;
    if(node->p == nil)
        root=new_node;
    else if(node->p->left == node)
        node->p->left = new_node;
    else
        node->p->right =new_node;

    //new_node成为新的根节点
    new_node->left=node;
    //链接parents
    node->p=new_node;
}

template<typename T>
void rb_tree<T>::RR(rb_node * node){
    auto new_node = node->left;
    //思路同LR
    node->left=new_node->right;
    if(new_node->right != NIL)
        new_node->right->p = node;

    new_node->p = node->p;
    if(node->p == nil)
        root = new_node;
    else if(node->p->left == node)
        node->p->left = new_node;
    else
        node->p->right = new_node;

    new_node->right = node;
    node->p = new_node;
}

template<typename T>
void rb_tree<T>::insert_fixup(rb_node* node) {
    while(node->p->color == RED){
        auto grandpa=node->p->p;
        auto parents=node->p;
        //判断uncle相对位置：uncle相对node在右
        if(grandpa->left == parents){
            auto uncle = grandpa->right;
            //CASE1:uncle's color is red
            if(uncle->color == RED){
                //recolor
                uncle->color=BLACK;
                parents->color=BLACK;
                grandpa->color=RED;
                node=grandpa;
            }
            else{
                //CASE2:uncle's color is black and node is a right child
                if(parents->right == node){
                    node = parents;
                    LR(parents);
                    parents=node->p;
                    grandpa=node->p->p;
                }
                //CASE3:uncle's color is black and node is a left child
                //可以改写
                parents->color=BLACK;
                grandpa->color=RED;
                RR(grandpa);
            }
        } //end if of uncle predicate
        else{
            //uncle 相对在左
            auto uncle=grandpa->left;
            if(uncle->color == RED){
                uncle->color=BLACK;
                parents->color=BLACK;
                grandpa->color=RED;
                node=grandpa;
            }
            else{
                if(parents->left == node){
                    node = parents;
                    RR(parents);
                    parents=node->p;
                    grandpa=node->p->p;
                }
                parents->color=BLACK;
                grandpa->color=RED;
                LR(grandpa);
            }
        }
    }
    root->color=BLACK;
}

template<typename T>
void rb_tree<T>::remove_fixup(rb_node* node){
    while(node!=root && node->color ==BLACK){
        auto parents=node->p;
        //先判断sibling是否在右边
        if(parents->left == node){
            auto sibling=parents->right;
            //CASE1:sibling's color is red
            if(sibling->color == RED){
                sibling->color=BLACK;
                parents->color=RED;
                LR(parents);
            }
            else{
                //CASE2:sibling's color is black and sibling have two black child
                if(sibling->left->color == BLACK && sibling->right->color == BLACK){
                    sibling->color=RED;
                    node=parents;
                }
                else{
                    //CASE3:sibling's color is black and only sibling's right child's color is black
                    if(sibling->right->color == BLACK){
                        sibling->color=RED;
                        sibling->left->color=BLACK;
                        RR(sibling);
                        sibling=parents->right;
                    }
                    //CASE4:sibling's color is black and sibling's right child's color is red
                    sibling->right->color=BLACK;
                    sibling->color=parents->color;
                    parents->color=BLACK;
                    LR(parents);
                    node=root;
                }
            }
        }
        else{
            auto sibling=parents->left;
            if(sibling->color == RED){
                sibling->color=BLACK;
                parents->color=RED;
                RR(parents);
            }
            else{
                if(sibling->left->color == BLACK && sibling->right->color == BLACK){
                    sibling->color=RED;
                    node=parents;
                }
                else{
                    if(sibling->left->color == BLACK){
                        sibling->right->color=BLACK;
                        sibling->color=RED;
                        LR(sibling);
                        sibling=parents->left;
                    }
                    sibling->left->color=BLACK;
                    sibling->color=parents->color;
                    parents->color=BLACK;
                    RR(parents);
                    node=root;
                }
            }
        }
    }
    node->color=BLACK;
}

template<typename T>
void rb_tree<T>::destroy(rb_node* node){
    if(node != nil){
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}


#endif //ITA_RB_TREE_IMPL_H
