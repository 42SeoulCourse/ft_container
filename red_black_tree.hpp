#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP
 
namespace ft {
// 컬러 설정
typedef bool RB_tree_node_color;
const RB_tree_node_color      RED = false;
const RB_tree_node_color      BLACK = true;

// 노드 구조체 및 successor, predecessor
template <typename V>
struct RB_tree_node {
  typedef RB_tree_node_color color_type;
  typedef RB_tree_node_color<Value> *node_type;

  V value;
  color_type color;
  node_type parent;
  node_type left;
  node_type right;

// 노드가 어떤 타입인지 모르기때문에 x라는 미지수를 사용하자
  static node_type minimum(node_type x) {
    while (x->left != 0) x = x->left;
    return x;
  }
  static node_type maximum(node_type x) {
    while (x->right != 0) x = x->right;
    return x;
  }
};

ㅅㄷ

};  // namespace ft

#endif RED_BLACK_TREE_HPP