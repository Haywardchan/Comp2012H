#ifndef __SKIPLIST_T_
#define __SKIPLIST_T_

// #include "skiplist.hpp"

template <typename K, typename V>
Skiplist<K, V>::Node::Node() {
    nexts = new Node*[1];
    nexts[0] = nullptr;
    levels = 1;
}

template <typename K, typename V>
Skiplist<K, V>::Node::Node(K key, V value, int levels) {
    this->nexts = new Node*[levels];
    for (int i = 0; i < levels; i++) {
        this->nexts[i] = nullptr;
    }
    this->levels = levels;
    this->key = key;
    this->value = value;
}

template <typename K, typename V>
Skiplist<K, V>::Node::~Node() {
    delete [] this->nexts;
}

template <typename K, typename V>
Skiplist<K, V>::Skiplist(double prob) {
    this->prob = prob;
    head = new Node();
}

template <typename K, typename V>
Skiplist<K, V>::~Skiplist() {
    Node* prevNode = head;
    Node* curNode = prevNode->nexts[0];
    while (prevNode) {
        delete prevNode;
        prevNode = curNode;
        if (curNode) curNode = curNode->nexts[0];
    }
}

template <typename K, typename V>
Skiplist<K, V>& Skiplist<K, V>::operator=(const Skiplist<K, V>& other) {
    // First, delete the old skiplist except the sentinel node
    Node* prevNode = head->nexts[0];
    if (prevNode) {
        Node* curNode = prevNode->nexts[0];
        while (prevNode) {
            delete prevNode;
            prevNode = curNode;
            if (curNode) curNode = curNode->nexts[0];
        }
    }

    // Then, deep copy everything from the given skiplist
    this->prob = other.prob;

    // First, copy the sentinel node
    int height = other.head->levels;
    delete [] this->head->nexts;
    this->head->nexts = new Node*[height];
    this->head->levels = height;

    // Stores the current rightmost node of each level
    Node** rightmostNodes = new Node*[height];
    // initialize it with the sentinel node
    for (int i = 0; i < height; i++) {
        rightmostNodes[i] = this->head;
    }

    // Create the nest of the nodes
    for (Node* node = other.head->nexts[0]; node; node = node->nexts[0]) {
        Node* curNode = new Node(node->key, node->value, node->levels);
        for (int i = 0; i < node->levels; i++) {
            rightmostNodes[i]->nexts[i] = curNode;
            rightmostNodes[i] = curNode;
        }
    }

    // Assign nullptr to the rest
    for (int i = 0; i < height; i++) {
        rightmostNodes[i]->nexts[i] = nullptr;
    }

    delete [] rightmostNodes;

    return *this;
}

template <typename K, typename V>
Skiplist<K, V>::Skiplist(const Skiplist<K, V>& other) {
    this->prob = prob;
    head = new Node();
    *this = other;
}

template <typename K, typename V>
bool Skiplist<K, V>::get(const K& get_key, V& rtn_value) const {
    int curLevel = head->levels - 1;
    Node* prevNode = head;
    Node* curNode = head->nexts[curLevel];
    while (curLevel >= 0) {
        if (curNode) {
            if (curNode->key == get_key) {
                rtn_value = curNode->value;
                return true;
            } else if (curNode->key > get_key) { // revert and go forward
                curLevel--;
                curNode = prevNode->nexts[curLevel];
            } else { // go forward :D
                prevNode = curNode;
                curNode = curNode->nexts[curLevel];
            }
        } else {
            curLevel--;
            curNode = prevNode->nexts[curLevel];
        }
    }
    return false;
}

template <typename K, typename V>
void Skiplist<K, V>::update(const K& update_key, const V& update_value) {

    int curLevel = head->levels - 1;
    Node* prevNode = head;
    Node* curNode = head->nexts[curLevel];
    Node** rightmostNodes = new Node*[head->levels];
    while (curLevel >= 0) {
        if (curNode) {
            if (curNode->key == update_key) {
                curNode->value = update_value;
                delete [] rightmostNodes;
                return;
            } else if (curNode->key > update_key) { // revert and go forward
                rightmostNodes[curLevel] = prevNode;
                curLevel--;
                if (curLevel >= 0) curNode = prevNode->nexts[curLevel];
            } else { // go forward :D
                prevNode = curNode;
                curNode = curNode->nexts[curLevel];
            }
        } else {
            rightmostNodes[curLevel] = prevNode;
            curLevel--;
            if (curLevel >= 0) curNode = prevNode->nexts[curLevel];
        }
    }

    // now if it is not found, the rightmostNodes is just LESS than the update_key
    Node* newNode = new Node(update_key, update_value, getRandomLevels());
    int oldLevels = head->levels;
    if (newNode->levels > head->levels) { // extend the head nexts
        Node** newNexts = new Node*[newNode->levels];
        int i = 0;
        for (; i < head->levels; i++) newNexts[i] = head->nexts[i];
        for (; i < newNode->levels; i++) newNexts[i] = nullptr;
        delete [] head->nexts;
        head->nexts = newNexts;
        head->levels = newNode->levels;
    }
    for (int i = 0; i < newNode->levels; i++) {
        if (i < oldLevels) {
            newNode->nexts[i] = rightmostNodes[i]->nexts[i];
            rightmostNodes[i]->nexts[i] = newNode;
        } else {
            newNode->nexts[i] = head->nexts[i];
            head->nexts[i] = newNode;
        }
    }
    delete [] rightmostNodes;

}

template <typename K, typename V>
bool Skiplist<K,V>::remove(const K& remove_key) {

    int height = head->levels - 1;
    Node* prev = head;
    Node* curr = head->nexts[height];
    Node** prev_nodes = new Node*[head->levels];
    bool found = false;
    while (height >= 0) {
        if (curr) {
            if (curr->key == remove_key) {
                found = true;
                prev_nodes[height] = prev;
                height--;
                if (height >= 0) curr = prev->nexts[height];
            } else if (curr->key > remove_key) { // revert and go forward
                prev_nodes[height] = prev;
                height--;
                if (height >= 0) curr = prev->nexts[height];
            } else { // go forward :D
                prev = curr;
                curr = curr->nexts[height];
            }
        } else {
            prev_nodes[height] = prev;
            height--;
            if (height >= 0) curr = prev->nexts[height];
        }
    }

    if (found) {
        // prev_nodes now store all nodes immediately LESS than curr, and
        Node* del = curr;
        int i;
        for (i = 0; i < head->levels; i++) {
            if (prev_nodes[i]->nexts[i])
                prev_nodes[i]->nexts[i] = del->nexts[i]; // reroute every layer
            if (head->nexts[i] == nullptr) break;
        }
        if (i < head->levels) {
            Node** newNexts = new Node*[i];
            for (int j = 0; j < i; i++) {
                newNexts[j] = head->nexts[i];
            }
            delete [] head->nexts;
            head->nexts = newNexts;
            head->levels = i + 1;
        }
        delete del;
    }
    delete [] prev_nodes;
    return found;
}

template <typename K, typename V>
int Skiplist<K,V>::size() const {
    int i = 0;
    for (Node* node = head->nexts[0]; node; node = node->nexts[0], i++);
    return i;
}

template <typename K, typename V>
bool Skiplist<K,V>::empty() const {
    return (head->nexts[0] == nullptr);
}

template <typename K, typename V>
void Skiplist<K,V>::print() const {
    std::cout << "{";
    for (Node* node = head->nexts[0]; node; node = node->nexts[0]) {
        std::cout << node->key << ": " << node->value;
        if (node->nexts[0]) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
}

template <typename K, typename V>
template <typename T>
Skiplist<K, T> Skiplist<K,V>::map(T (*f)(V value)) const {
    Skiplist<K, T> res;
    for (Node* node = head->nexts[0]; node; node = node->nexts[0]) {
        res.update(node->key, f(node->value));
    }
    return res;
}

template <typename K, typename V>
Skiplist<K,V> Skiplist<K,V>::filter(bool (*f)(V value)) const {
    Skiplist<K, V> res;
    for (Node* node = head->nexts[0]; node; node = node->nexts[0]) {
        if (f(node->value))
            res.update(node->key, node->value);
    }
    return res;
}

template <typename K, typename V>
Skiplist<K,V> Skiplist<K,V>::operator+(const Skiplist<K,V>& other) const {
    Skiplist<K, V> res;
    for (Node* node = this->head->nexts[0]; node; node = node->nexts[0]) {
        res.update(node->key, node->value);
    }
    for (Node* node = other.head->nexts[0]; node; node = node->nexts[0]) {
        res.update(node->key, node->value);
    }
    return res;
}

#endif // __SKIPLIST_T_