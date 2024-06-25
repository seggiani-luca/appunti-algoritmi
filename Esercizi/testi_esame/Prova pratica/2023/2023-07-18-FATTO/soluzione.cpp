#include <iostream>
#include <unordered_set>

struct Node {
    int label;
    char color;
    Node *left;
    Node *right;

    explicit Node(int label, char color) : label{label}, color{color}, left{nullptr}, right{nullptr} {
    }
};

void insert_node_bst(Node *&n, int label, char color) {
    Node **scan = &n;
    while (*scan != nullptr) {
        if (label <= (*scan)->label) {
            scan = &(*scan)->left;
        } else {
            scan = &(*scan)->right;
        }
    }
    *scan = new Node(label, color);
}


// void destroy_tree(Node *n) {
//     if (n == nullptr) {
//         return;
//     }
//     destroy_tree(n->left);
//     destroy_tree(n->right);
//     delete n;
// }


bool is_surrounded(const Node &n, const Node &father) {
    return n.left != nullptr &&
        n.right != nullptr && 
        n.left->color == father.color && 
        n.right->color == father.color;
}

void get_fathers_of_surrounded_children(const Node *n, std::unordered_set<const Node*> &p) {
    if (n == nullptr) {
        return;
    }
    for (Node *child: {n->left, n->right}) {
        if (child != nullptr && is_surrounded(*child, *n)) {
            p.insert(n);
            break;
        }
    }
    get_fathers_of_surrounded_children(n->left, p);
    get_fathers_of_surrounded_children(n->right, p);
}


void print_tree(const Node *n, const std::unordered_set<const Node*> &nodes) {
    if (n == nullptr) {
        return;
    }
    
    print_tree(n->left, nodes);
    if (nodes.find(n) != nodes.end()) {
        std::cout << n->label << std::endl;
    }
    print_tree(n->right, nodes);
  
}

int main() {
    int n;
    std::cin >> n;

    // if (n <= 0) {
    //     throw std::invalid_argument("n must be greater than 0");
    // }

    Node *node = nullptr;
    for (int i = 0; i < n; i++) {
        int label;
        char color;
        std::cin >> label >> color;
        insert_node_bst(node, label, color);
    }

    std::unordered_set<const Node*> p{};
    get_fathers_of_surrounded_children(node, p);
    print_tree(node, p);

    // destroy_tree(node);

    return 0;
}

