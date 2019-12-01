#include <iostream>
#include <utility>
#include <stdexcept>

/*
 * AVL Tree Dictionary
 */
template<typename KeyType, typename ValueType>
class AVLTreeMap
{
  public:
    using key_type = KeyType;
    using mapped_type = ValueType;
    using value_type = std::pair<const key_type, mapped_type>;

    AVLTreeMap() = default;    // default constructor
    ~AVLTreeMap() = default;   // default destructor

    struct Node {
        Node(key_type _key, mapped_type _value) :  key(_key), value(_value){}
        ~Node() {
            delete left;
            delete right;
        }
        int h = 1;          // depth of node
        Node *left = NULL;
        Node *right = NULL;
        key_type key;
        mapped_type value;
    };

    /*!
     * true if dictionary is empty
     */
    bool isEmpty() const
    {
        return !treeSize;
    }

    /*!
     * insert element to dictionary - arguments are starting node, key and mapped type
     */
    void insert(const key_type& key, const mapped_type &value) {
        insert(root, key, value);
    }

    /*!
     * insert element to dictionary - arguments are starting node, key and mapped type
     */
    void insert(Node*& node,const key_type& key, const mapped_type &value)
    {
        if (!node) {
            node = new Node(key, value); // insert node
            treeSize++;
            return;
        }
        else if (key == node->key) {
            node->value = value;
            return;
        }

        if (key < node->key)
            insert(node->left, key, value);
        else
            insert(node->right, key, value);
        
        node->h = 1 + std::max(height(node->left),  
                        height(node->right));  

        int balance = height(node->left) - height(node->right);
        if (balance > 1 && key < node->left->key)           // left - left case
            rotateRight(node);
        else if (balance < -1 && key > node->right->key)    // right - right case
            rotateLeft(node);
        else if (balance > 1 && key > node->left->key) {    // left - right case
            rotateLeft(node->left);
            rotateRight(node);
        }
        else if (balance < -1 && key < node->right->key) {  // right - left case
            rotateRight(node->right);
            rotateLeft(node);
        }

        return;
    }

    void print() {
        std::vector<Node*> vec = {root};
        for(int i = 0; i < vec.size(); i++) {
            Node *akt = vec[i];
            if (akt) {
                std::cout << i << " " << akt->key << std::endl;
                vec.push_back(akt->left);
                vec.push_back(akt->right);
            }
        }
    }

    /*!
     * insert element to dictionary - argument is pair consisting of key and mapped type 
     */
    void insert(const value_type &key_value)
    {
        insert(key_value.first, key_value.second);
    }

   /*!
     * return reference on value for given key
     *
     * if there is no key in dictionary, it is added with default mapped value
     */
    mapped_type& operator[](const key_type& key)
    {
        try {
            return find(key);
        } catch(std::range_error &e) {
            insert(key, mapped_type());
            return find(key);
        }
    }

    /*!
     * return reference on value for given key
     */
    mapped_type& find(const key_type& key) const
    {
        Node *tmp = root;
        
        while (tmp && tmp->key != key)
            tmp = (key < tmp->key ? tmp->left : tmp->right);
        if (!tmp)
            throw std::range_error("There is no such a key");
        return tmp->value;
    }

    /*!
     * return true if dictionary contains given key
     */
    bool contains(const key_type& key) const {
        Node *tmp = root;
        
        while (tmp && tmp->key != key)
            tmp = (key < tmp->key ? tmp->left : tmp->right);
        return tmp && tmp->key == key;
    }

    /*!
     * return size of dictionary
     */
    size_t size() const {
        return treeSize;
    }
private:
    int treeSize = 0;
    Node *root = NULL;

    /*!
     * return depth of node
     */
    int height(Node *n) {
        if (!n)
            return 0;
        return n->h;
    }

    /*!
     * rotate left aroung node x
     */
    void rotateLeft(Node*& x) {
        Node *y = x->right;

        x->right = y->left;
        y->left = x;

        // update heights
        x->h = std::max(height(x->left), height(x->right)) + 1;
        y->h = std::max(height(y->left), height(y->right)) + 1;
        
        // update root
        x = y;
    }

    /*!
     * rotate right aroung node x
     */
    void rotateRight(Node*& x) {
        Node *y = x->left;
        x->left = y->right;
        y->right = x;

        // update heights
        x->h = std::max(height(x->left), height(x->right)) + 1;
        y->h = std::max(height(y->left), height(y->right)) + 1;
        
        // update root
        x = y;
    }

};