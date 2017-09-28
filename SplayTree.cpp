#include <iostream>

class SplayTree {

    struct SplayNode {
        long value;
        SplayNode *left, *right;
        SplayNode(long val) : value(val), left(nullptr), right(nullptr) {}
        /*
        You are only passed a neighbor: left, right, or parent
        */
        void usurpParent(SplayNode **neighbor) {
            bool areOnLeft = (*neighbor)->left == this;
            if (areOnLeft) {
                (*neighbor)->left = right;
                right = *neighbor;
            } else {
                (*neighbor)->right = left;
                left = *neighbor;
            }
            *neighbor = this; //set the parents pointer to element to ours
        }
    };

    SplayNode *head;
    
public:
    SplayTree(): head(nullptr) {}
    
    bool splay(SplayNode **ours, SplayNode **parent, SplayNode **grandParent, long value) {
        bool haveValue;
        if (*ours == nullptr) {
            return true; // tell parent to splay up their element
        }
        else if (value == (*ours)->value) {
            haveValue = true;
        } 
        else if (value < (*ours)->value) {
            haveValue = splay(&(*ours)->left, ours, parent, value);
        } else {
            haveValue = splay(&(*ours)->right, ours, parent, value);
        }
        if (!haveValue) return true; // if we don't have value, next person has it
        
        
        
        if (grandParent == nullptr && parent == nullptr) {
            // at top
            return true;
        } 
        else if (grandParent == nullptr) {
            // on odd case
            (*ours)->usurpParent(parent);
            return true;
        }
        
        // our pointers have changed so lets add this so we know what we are talking about after messing with double pointers a bit better
        SplayNode *o = *ours;
        SplayNode *p = *parent;
        SplayNode *gp = *grandParent;

        
        // are we in inline case
        bool inLine = (*parent == (*grandParent)->left) == (*ours == (*parent)->left);
        if (inLine) {
            // we make parent go into place of grandParent shifting grandparent to the right/left
            p->usurpParent(grandParent); // grandParent now points to our parent
            // grandParent pointer is now pointing at parent
            o->usurpParent(grandParent);  // we want to pass grandParents pointer so that we replace the access from element above
            return false;
        } else {
            // we take our parents place and now our grandParent is pointing to us
            o->usurpParent(parent); // parent now points to ours
            // we take grandparents place and give it our right/left element which is not our parent
            o->usurpParent(grandParent); // we now want to take grand parents
            return false;
        }
    }
    void splay(long value) {
        splay(&head, nullptr, nullptr, value);
    }
    
    void insert(long value) {
        SplayNode **current = &head;
        while(*current != nullptr) {
            if (value < (*current)->value) current = &(*current)->left;
            else current = &(*current)->right;
        }
        *current = new SplayNode(value);
        splay(value);
    }


    void print(const SplayNode *current, int depth) {
        if (current == nullptr) return;
        for (int i = 0; i < depth; i++) std::cout << " ";
        std::cout << current->value << std::endl;
        print(current->right, depth + 1);
        for (int i = 0; i < depth; i++) std::cout << " ";
        std::cout << current->value << std::endl;
        print(current->left, depth + 1);
        for (int i = 0; i < depth; i++) std::cout << " ";
        std::cout << current->value << std::endl;
    }
    void print() {
        print(head, 0);
    }
};


int main() {
    SplayTree tree;
    for (int i = 0; i < 20; i++) {
        tree.insert(i);
    }
    while (true) {
        char c;
        long v;
        std::cin >> c;
        if (c == 'p') {
            std::cout << std::endl;
            tree.print();
            
        } 
        else if (c == 's') {
            std::cin >> v;
            tree.splay(v);
        } else {
            std::cin >> v;
            tree.insert(v);
        }
    }
    
    return 0;
}