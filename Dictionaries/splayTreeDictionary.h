#include <iostream>
#include <chrono>
#include <utility>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <map>

/*
 * Splay Tree Dictionary
 */
template<typename KeyType, typename ValueType>
class SplayTreeMap
{
  public:
    
    using key_type = KeyType;
    using mapped_type = ValueType;
    using value_type = std::pair<const key_type, mapped_type>;

    struct Node
    {
        Node(const key_type &_key, const mapped_type &_value)
            : key(_key), value(_value)
        { }
        key_type key;
        mapped_type value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    SplayTreeMap() = default;    // default constructor
    ~SplayTreeMap() = default;   // default destructor

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
    void insert(const key_type& key, const mapped_type &value)
    {
        auto new_ptr = std::make_unique<Node>(key, value);
        if (!root) {
            root = std::move(new_ptr);
            treeSize++;
            return;
        }
        root = std::move(splay(root, key));
        if (key == root->key) {
            root->value = value;
            return;
        }
        if (key > root->key) {
            new_ptr->right = std::move(root->right);
            new_ptr->left = std::move(root);
        }
        else
        {
            new_ptr->left = std::move(root->left);
            new_ptr->right = std::move(root);
        }
        root = std::move(new_ptr);
        treeSize++;
    }

    /*!
     * insert element to dictionary - arguments are starting node, key and mapped type
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

    void bfs() {
        std::cout << "BFS" << std::endl;
        std::vector<Node*> vec = {root.get()};
        for (int i = 0; i < vec.size(); i++) {
            Node *akt = vec[i];
            if (akt) {
                std::cout << i << " "<<vec[i]->key << ":" << vec[i]->value << " ";
                vec.push_back(akt->left.get());
                vec.push_back(akt->right.get());
            }
        }
        std::cout << std::endl << "KONIEC BFSA" << std::endl;
    }

    /*!
     * return reference on value for given key
     */
    mapped_type& find(const key_type& key)
    {

        if (!root)
            throw std::range_error("empty tree");
        root = std::move(splay(root, key));
        if (root->key != key)
            throw std::range_error("not found in tree");
        return root->value;
    }

    /*!
     * return true if dictionary contains given key
     */
    bool contains(const key_type& key) const{
        try {
            find(key);
        } catch(std::range_error &e) {
            return false;
        }
        return true;
    }

    /*!
     * return size of dictionary
     */
    size_t size() const {
        return treeSize;
    }
private:
    int treeSize = 0;
    std::unique_ptr<Node> root;

    /*!
     * rotate left aroung node x
     */
    std::unique_ptr<Node> leftRotation(std::unique_ptr<Node> &x) {
        std::unique_ptr<Node> RightChild = std::move(x->right);
        x->right = std::move(RightChild->left);
        RightChild->left = std::move(x);
        return std::move(RightChild);
    }

    /*!
     * rotate right aroung node x
     */
    std::unique_ptr<Node> rightRotation(std::unique_ptr<Node> &x) {
        std::unique_ptr<Node> LeftChild = std::move(x->left);
        x->left = std::move(LeftChild->right);
        LeftChild->right = std::move(x);
        return std::move(LeftChild);
    }

    /*!
     * splay node x
     */
    std::unique_ptr<Node> splay(std::unique_ptr<Node> &root, const key_type& key) {
        if (!root || key == root->key)
            return std::move(root);
        if (key < root->key) {
            if (root->left == NULL)    return std::move(root);
            if (key < root->left->key) {    //ZIG ZIG left-left
                root->left->left = std::move(splay(root->left->left, key));
                root = std::move(rightRotation(root));
            }
            else if (key > root->left->key) { //ZIG ZAG left-right
                root->left->right = std::move(splay(root->left->right, key));
                if (root->left->right != NULL)
                    root->left = std::move(leftRotation(root->left));
            }
            return root->left ? std::move(rightRotation(root)) : std::move(root); //perform second rotation
        }
        else {
            if (root->right == NULL)    return std::move(root);
            if (key > root->right->key) {   //ZIG ZIG right-right
                root->right->right = std::move(splay(root->right->right, key));
                root = std::move(leftRotation(root));
            }
            else if (key < root->right->key) { //ZIG ZAG right-left
                root->right->left = std::move(splay(root->right->left, key));
                if (root->right->left != NULL) {
                    root->right = std::move(rightRotation(root->right));
                }
            }
            return root->right ? std::move(leftRotation(root)) : std::move(root); //perform second rotation
        }
    }
};