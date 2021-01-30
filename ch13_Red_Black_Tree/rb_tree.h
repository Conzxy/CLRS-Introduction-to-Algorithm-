//
// Created by 谁敢反对宁宁，我就打爆他狗头！ on 2021/1/29.
//

#ifndef ITA_RB_TREE_H
#define ITA_RB_TREE_H
#define NIL nullptr

template<typename T>
class rb_tree{
    struct rb_node;
public:
    enum Color{RED,BLACK};

    rb_tree();
    explicit rb_tree(unsigned n);
    rb_tree(rb_tree const&);
    rb_tree(rb_tree &&)noexcept;
    rb_tree& operator=(rb_tree const&);
    rb_tree& operator=(rb_tree &&)noexcept;
    ~rb_tree();


    void insert(T const&);
    void remove(T const&);
    bool isEmpty(){ return root == nil; }
    rb_node const* search(T const&);
    void inOrderWalk();
    rb_node const* maximum();
    rb_node const* minimum();
    rb_node const* successor();
    rb_node const* predecessor();
private:
    void inOrderWalk_AUX(rb_node const*);
    rb_node const* maximum_AUX(rb_node const*);
    rb_node const* minimum_AUX(rb_node const*);
    rb_node const* searchRecursion(rb_node const*,T const&);
    rb_node const* searchIterative(rb_node const*,T const&);
    void transplant(rb_node* ,rb_node*);
    void insert_fixup(rb_node*);
    void remove_fixup(rb_node*);
    void LR(rb_node*);
    void RR(rb_node*);
    void destroy(rb_node*);
    rb_node* clone(rb_node*,rb_node*);
    rb_node* nil;
    rb_node* root;

    struct  rb_node{
        T key;
        rb_node* left,*right,*p;
        Color color;
    };

};
#endif //ITA_RB_TREE_H
