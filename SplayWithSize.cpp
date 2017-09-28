#include <iostream>

class SplayTree {

    struct SplayNode {
        long value;
        long size;
        SplayNode *left, *right;
        SplayNode(long val) : value(val), size(1), left(nullptr), right(nullptr) {}
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
    
    // make sure if only insertions it is valid
    // then make sure splay is valid as well
    void augment(SplayNode *node) {
        node->size = 1;
        if (node->left != nullptr) node->size += node->left->size;
        if (node->right != nullptr) node->size += node->right->size;
    }
    
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
            SplayNode *p = *parent;
            SplayNode *o = *ours;
            (*ours)->usurpParent(parent);
            augment(p);
            augment(o);
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
        } else {
            // we take our parents place and now our grandParent is pointing to us
            o->usurpParent(parent); // parent now points to ours
            // we take grandparents place and give it our right/left element which is not our parent
            o->usurpParent(grandParent); // we now want to take grand parents
        }
        
        // grand parent always has no dependencies on other nodes at end so
        augment(gp);
        // then parent
        augment(p);
        // then us
        augment(o);
        return false;
    }
    void splay(long value) {
        splay(&head, nullptr, nullptr, value);
    }
    
    // cant really do recursion because of stack overflow, but iterative is fine.
    // could also use stack to simulate recursion, but that could get messy
    void insert(long value) {
        SplayNode **current = &head;
        while(*current != nullptr) {
            (*current)->size += 1; // additional size augmentation
            if (value < (*current)->value) current = &(*current)->left;
            else current = &(*current)->right;
        }
        *current = new SplayNode(value);
        splay(value);
    }
};

int main() { return 0; }