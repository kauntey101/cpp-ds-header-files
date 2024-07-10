#pragma once
#include <vector>

template <typename T> class Node {
  public:
    Node<T> *left, *right;
    T val;

    Node(T val) : left(nullptr), right(nullptr), val(val) {}
};

/**
 * @brief An Unbalanced Binary Search Tree.
 * 
 * @tparam T Type of the data to be stored in the Tree.
 */
template <typename T> class BST {
  
  private: 
    Node<T> *root;

  public: 
    /**
     * @brief Create a new BST.
     */
    BST() : root(nullptr) {}

    /**
     * @brief Destroy the BST.
    */
    ~BST() {
      destroyAllNodes(root);
    }

    /** FUNCTIONS 
    * void insert(T key); 
    * void remove(T key);
    * bool search(T key);
    * int size();
    * Node<T>* deleteNode(Node<T> *head, T key);
    * T inOrderPredecessor(Node<T> *head);
    * vector<T> getAll();
    * void inOrder(Node<T> *head, vector<T> &arr);
    * void destroy();
    */

    /**
     * @brief Inserts a key in the BST if not inserted already.
     * @param key The key to be inserted.
    */
    void insert(T key) {
      if(root == nullptr) {
        root = new Node<T>(key);
      }
      else {
        Node<T> *prevNode = nullptr;
        Node<T> *iterator = root;

        while(iterator != nullptr) {
          prevNode = iterator;
          
          if(iterator->val == key) { 
            break;
          } 
          
          if(key > iterator->val) {
            iterator = iterator->right;  
          }
          else {
            iterator = iterator->left;
          }
        }

        if(iterator == nullptr) {
          if(key > prevNode->val) {
            prevNode->right = new Node<T>(key);
          }
          else {
            prevNode->left = new Node<T>(key);
          }
        } 
      }
    }
    
    /**
     * @brief Search for a key in the BST.
     * @param key The key to be searched.
     * @return bool - true if the key is present, otherwise false.
    */
    bool search(T key) { 
      Node<T> *iterator = root;
      
      while(iterator != nullptr) {
        if(iterator->val == key) { 
          break;
        }
        
        if(key > iterator->val) {
          iterator = iterator->right;
        }
        else {
          iterator = iterator->left;
        }
      }

      if(iterator == nullptr) return false; 
      
      return true;
    }

    /**
     * @brief Remove a key from the BST.
     * @param key The key to be removed.
    */
    void remove(T key) {
      root = deleteNode(root, key);
    }

    Node<T>* deleteNode(Node<T> *head, T key) {
      
      if(head == nullptr) return head;

      Node<T> *iterator = head; 
      Node<T> *prevNode = nullptr;
    
      while(iterator != nullptr) {
        if(iterator->val == key) {
          break;
        }
        
        prevNode = iterator;
        if(key > iterator->val) {
          iterator = iterator->right;
        }
        else {
          iterator = iterator->left;
        }
      }

      if(iterator == nullptr) return head;

      
      if(iterator->left == nullptr && iterator->right == nullptr) {
        if(prevNode != nullptr) {
          if(prevNode->val < key) {
            prevNode->right = nullptr;
          }
          else {
            prevNode->left = nullptr;
          }
          delete iterator;
          return head;
        }
        else {
          delete iterator;
          return nullptr;
        }
      }
      else if(iterator->left == nullptr || iterator->right == nullptr) {

        Node<T> *nextAvailableNode = iterator->left == nullptr ? iterator->right : iterator->left;
          
        if(prevNode != nullptr) {
          if(nextAvailableNode->val > prevNode->val) {
            prevNode->right = nextAvailableNode;
          }
          else {
            prevNode->left = nextAvailableNode;
          }
          delete iterator;
          return head;
        }
        else {
          delete iterator;
          return nextAvailableNode;
        }
      } 
      else {
          
        T inOrderPred = inOrderPredecessor(iterator);
        iterator->val = inOrderPred;
        iterator->left = deleteNode(iterator->left, inOrderPred);

        if(prevNode == nullptr) { 
          return iterator;
        }
        else {
          return head;
        }
      }
    }

    T inOrderPredecessor(Node<T> *head) {
      Node<T> *inOrderPred = head->left;
      
      while(inOrderPred->right != nullptr) {
        inOrderPred = inOrderPred->right;
      }

      return inOrderPred->val; 
    }

    /**
     * @brief Get all the keys stored in the BST in Lexicographical Order.
     * @return std::vector<T> - vector of keys
    */
    std::vector<T> getAll() {
      std::vector<T> arr; 
      inOrder(root, arr);
      return arr;
    }

    void inOrder(Node<T> *head, std::vector<T> &arr) {
      while(head != nullptr) {

        if(head->left != nullptr) {
          Node<T> *inOrderPred = head->left;
          while(inOrderPred->right != nullptr && inOrderPred->right != head) {
            inOrderPred = inOrderPred->right;
          }

          if(inOrderPred->right == nullptr) {
            inOrderPred->right = head; 
            head = head->left;
          }
          else {
            arr.push_back(head->val); 
            inOrderPred->right = nullptr; 
            head = head->right;
          }
        }
        else {
          arr.push_back(head->val);
          head = head->right;
        }
      
      }
    }

    /**
     * @brief Size of the BST - Number of keys stored in the BST.
     * @return int - Size of BST
    */
    int size() {
      Node<T> *head = root;
      int n = 0;

      while(head != nullptr) {

        if(head->left != nullptr) {
          Node<T> *inOrderPred = head->left;
          while(inOrderPred->right != nullptr && inOrderPred->right != head) {
            inOrderPred = inOrderPred->right;
          }

          if(inOrderPred->right == nullptr) {
            inOrderPred->right = head; 
            head = head->left;
          }
          else {
            n++; 
            inOrderPred->right = nullptr; 
            head = head->right;
          }
        }
        else {
          n++;
          head = head->right;
        }
      
      }
      return n;
    }

    /**
     * @brief Removes all the keys stored in the BST.
    */
    void destroy() {
      destroyAllNodes(root);
    }

    void destroyAllNodes(Node<T> *head) {
      root = nullptr;
      std::vector<Node<T>*> arr;

      while(head != nullptr) {

        if(head->left != nullptr) {
          Node<T> *inOrderPred = head->left;
          while(inOrderPred->right != nullptr && inOrderPred->right != head) {
            inOrderPred = inOrderPred->right;
          }

          if(inOrderPred->right == nullptr) {
            inOrderPred->right = head; 
            head = head->left;
          }
          else {
            arr.push_back(head); 
            inOrderPred->right = nullptr; 
            head = head->right;
          }
        }
        else {
          arr.push_back(head);
          head = head->right;
        }
      
      }

      for(int i=0;i<arr.size();i++) {
        delete arr[i];
      }
    }

};
