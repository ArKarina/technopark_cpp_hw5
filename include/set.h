#ifndef SET_H
#define SET_H

#include <cmath>
#include <iostream>

#include "errors.h"
#include "iterator.h"

enum node_color { red, black };

template <typename T> 
class Iterator;

template <typename T> 
struct Node {
  Node()
      : data(T()), color(black), left(nullptr), right(nullptr),
        parent(nullptr) {}
  Node(const T &data, node_color color, Node<T> *left, Node<T> *right,
       Node<T> *parent)
      : data(data), color(color), left(left), right(right), parent(parent) {}
  Node(const Node<T> &node)
      : data(node.data), color(node.color), left(node.left), right(node.right),
        parent(node.parent) {}

  T data;
  node_color color;
  Node<T> *left;
  Node<T> *right;
  Node<T> *parent;
};

template <typename T> 
class Set {
public:
  Set() : size_(0), leaf(new Node<T>), root(leaf) {}

  template <class Iter> 
  Set(Iter First, Iter Last) : Set() {
    while (First != Last) {
      insertElem(*First);
      ++First;
    }
  }

  Set(std::initializer_list<T> list) : Set() {
    for (auto &elem : list)
      insertElem(elem);
  }

  Set(const Set<T> &set) : Set() {
    size_ = set.size_;
    if (set.root == set.leaf)
      return;

    root = new Node<T>(*(set.root));
    root->left = leaf;
    root->right = leaf;
    root->parent = leaf;
    copyNodes(set.root, set.leaf, root);
  }

  Set<T> &operator=(const Set<T> &set) {
    Set<T> tmp(set);
    if (this != &set) {
      tmp.swap(*this);
    }
    return *this;
  }

  ~Set() {
    clear(root);
    delete leaf;
  }

  Node<T> *getLeaf() const { return leaf; }

  Node<T> *getRoot() const { return root; }

  size_t size() const { return size_; }

  bool empty() const { return size_ == 0; }

  void swap(Set<T> &set) {
    std::swap(size_, set.size_);
    std::swap(leaf, set.leaf);
    std::swap(root, set.root);
  }

  void insert(T elem) { insertElem(elem); }

  void erase(const T &elem) {
    Node<T> *tmp = root;

    while (tmp->data != elem && tmp != leaf)
      if (tmp->data < elem)
        tmp = tmp->right;
      else
        tmp = tmp->left;

    if (tmp == leaf)
      return;

    deleteElem(tmp);
  }

  bool operator==(const Set<T> &set) const {
    if (size_ != set.size_)
      return false;

    for (auto i : set)
      if (find(i) == end())
        return false;

    return true;
  }

  Iterator<T> find(const T &elem) const {
    Node<T> *tmp = root;

    while (tmp != leaf) {
      if (tmp->data < elem)
        tmp = tmp->right;
      else if (elem < tmp->data)
        tmp = tmp->left;
      else
        return Iterator<T>(this, tmp);
    }

    return Iterator<T>(this, tmp);
  }

  Iterator<T> lower_bound(const T &elem) const {
    Node<T> *tmp = root, *result = leaf;

    while (tmp != leaf) {
      if (tmp->data < elem)
        tmp = tmp->right;
      else if (elem < tmp->data) {
        result = tmp;
        tmp = tmp->left;
      } else
        return Iterator<T>(this, tmp);
    }

    return Iterator<T>(this, result);
  }

  Iterator<T> begin() const {
    Node<T> *elem = root;

    while (elem != leaf && elem->left != leaf)
      elem = elem->left;

    return Iterator<T>(this, elem);
  }

  Iterator<T> end() const { return Iterator<T>(this, leaf); }

private:
  size_t size_;
  Node<T> *leaf;
  Node<T> *root;

  void smallRightRotation(Node<T> *node) {
    Node<T> *left_child = node->left;

    node->left = left_child->right;
    left_child->right->parent = node;
    left_child->right = node;

    if (node->parent == leaf)
      root = left_child;
    else if (node->parent->left == node)
      node->parent->left = left_child;
    else
      node->parent->right = left_child;

    left_child->parent = node->parent;
    node->parent = left_child;
  }

  void smalLeftRotation(Node<T> *node) {
    Node<T> *right_child = node->right;

    node->right = right_child->left;
    right_child->left->parent = node;
    right_child->left = node;

    if (node->parent == leaf)
      root = right_child;
    else if (node->parent->left == node)
      node->parent->left = right_child;
    else
      node->parent->right = right_child;

    right_child->parent = node->parent;
    node->parent = right_child;
  }

  void fixTreeInsert(Node<T> *node) {
    Node<T> *father = node->parent, *uncle;
    while (node != root && father->color == red) {
      if (father->parent->left == father)
        uncle = father->parent->right;
      else
        uncle = father->parent->left;

      if (uncle->color == red) {
        father->color = black;
        uncle->color = black;
        father->parent->color = red;

        node = father->parent;
        father = node->parent;
      } else {
        if (father->parent->left == father && node == father->right) {
          node = father;
          smalLeftRotation(node);
        } else if (father->parent->right == father && node == father->left) {
          node = father;
          smallRightRotation(node);
        }
        father = node->parent;
        father->color = black;
        father->parent->color = red;

        if (father->parent->left == father)
          smallRightRotation(father->parent);
        else
          smalLeftRotation(father->parent);
      }
    }
    root->color = black;
  }

  void insertElem(const T elem) {
    Node<T> *new_node, *tmp, *parent;
    tmp = root;
    parent = leaf;

    while (tmp != leaf) {
      if (!(tmp->data < elem) && !(elem < tmp->data))
        return;

      parent = tmp;
      if (elem < tmp->data)
        tmp = tmp->left;
      else
        tmp = tmp->right;
    }

    new_node = new Node<T>(elem, red, leaf, leaf, parent);
    if (parent == leaf)
      root = new_node;
    else if (elem < parent->data)
      parent->left = new_node;
    else
      parent->right = new_node;

    size_++;
    fixTreeInsert(new_node);
  }

  void fixTreeDelete(Node<T> *node) {
    Node<T> *brother, *child_left;
    while (node != root && node->color == black) {
      if (node->parent->left == node)
        brother = node->parent->right;
      else
        brother = node->parent->left;

      if (brother->color == red) {
        brother->color = black;
        node->parent->color = red;

        if (node->parent->left == node) {
          smalLeftRotation(node->parent);
          brother = node->parent->right;
        } else {
          smallRightRotation(node->parent);
          brother = node->parent->left;
        }
      }

      if (brother->left->color == black && brother->right->color == black) {
        brother->color = red;
        node = node->parent;
      } else {
        child_left = brother->left;
        if (child_left->color == red) {
          brother->color = red;
          child_left->color = black;

          if (node->parent->left == node) {
            smallRightRotation(brother);
            brother = node->parent->right;
          } else {
            smalLeftRotation(brother);
            brother = node->parent->left;
          }
        }

        brother->color = node->parent->color;
        node->parent->color = black;

        if (node->parent->left == node) {
          brother->right->color = black;
          smalLeftRotation(node->parent);
        } else {
          brother->left->color = black;
          smallRightRotation(node->parent);
        }
        node = root;
      }
    }
    node->color = black;
  }

  void deleteElem(Node<T> *node) {
    if (!node || node == leaf)
      return;

    size_--;
    Node<T> *node_delete = node;

    if (node->left != leaf && node->right != leaf) {
      node_delete = node->right;
      while (node_delete->left != leaf)
        node_delete = node_delete->left;
    }

    Node<T> *child = node_delete->left;
    if (node_delete->left == leaf)
      child = node_delete->right;

    child->parent = node_delete->parent;

    if (node_delete->parent == leaf)
      root = child;
    else if (node_delete->parent->left == node_delete)
      node_delete->parent->left = child;
    else
      node_delete->parent->right = child;

    if (node_delete != node)
      node->data = node_delete->data;

    if (node_delete->color == black)
      fixTreeDelete(child);

    delete node_delete;
  }

  void copyNodes(Node<T> *first, Node<T> *last, Node<T> *&result) {
    if (first == last) {
      result = leaf;
      return;
    }

    if (first->left == last)
      result->left = leaf;
    else {
      result->left = new Node<T>(*(first->left));
      result->left->parent = result;
      copyNodes(first->left, last, result->left);
    }

    if (first->right == last)
      result->right = leaf;
    else {
      result->right = new Node<T>(*(first->right));
      result->right->parent = result;
      copyNodes(first->right, last, result->right);
    }
  }

  void clear(Node<T> *node) {
    if (node == leaf)
      return;
    clear(node->left);
    clear(node->right);
    delete node;
    node = leaf;
  }
};

#endif // SET_H
