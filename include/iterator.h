#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>

#include "errors.h"
#include "set.h"

template <typename T> 
struct Node;

template <typename T> 
class Set;

template <typename T>
class Iterator
    : public std::iterator<std::bidirectional_iterator_tag, const T> {
public:
  Iterator() : set(nullptr), elem(nullptr) {}
  Iterator(const Set<T> *set, Node<T> *elem) : set(set), elem(elem) {}
  ~Iterator() = default;

  bool operator==(const Iterator<T> &iterator) const {
    return (set == iterator.set && elem == iterator.elem);
  }

  bool operator!=(const Iterator<T> &iterator) const {
    return (!(*this == iterator));
  }

  const T &operator*() { return elem->data; }
  const T *operator->() { return &**this; }

  Iterator<T> &operator++() {
    if (elem == set->getLeaf())
      return *this;

    if (elem->right == set->getLeaf()) {
      while (elem->parent != set->getLeaf() && elem->parent->right == elem)
        elem = elem->parent;
      elem = elem->parent;
      return *this;
    }

    elem = elem->right;
    while (elem->left != set->getLeaf())
      elem = elem->left;

    return *this;
  }

  const Iterator<T> operator++(int) {
    Iterator<T> tmp = *this;
    ++(*this);
    return tmp;
  }

  Iterator<T> &operator--() {
    if (elem == set->getLeaf()) {
      elem = set->getRoot();
      if (elem == set->getLeaf())
        return *this;

      while (elem->right != set->getLeaf())
        elem = elem->right;

      return *this;
    }

    if (elem->left == set->getLeaf()) {
      while (elem->parent != set->getLeaf() && elem->parent->left == elem)
        elem = elem->parent;
      elem = elem->parent;
      return *this;
    }

    elem = elem->left;
    while (elem->right != set->getLeaf())
      elem = elem->right;

    return *this;
  }

  const Iterator<T> operator--(int) {
    Iterator<T> tmp = *this;
    --(*this);
    return tmp;
  }

private:
  const Set<T> *set;
  Node<T> *elem;
};

#endif // ITERATOR_H
