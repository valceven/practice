#include "node.h"
#include <iostream>
#include <cstdlib>
using namespace std;
class BSTree {
    node* root;
    int size;

    public:
    BSTree() {
        root = NULL;
        size = 0;
    }

    node* create_node(int num,bool is_red, node* parent){
        node* temp = (node*) calloc (1,sizeof(node));
        temp->element = num;
        temp->is_red = is_red;
        temp->parent = parent;

        return temp;
    }

    void insert(int num){
        if(!root){
            root = create_node(num,false,NULL);
            size++;
            return;
        }

        node* curr = root;
        node* parent = NULL;

        while(curr){
            parent = curr;

            if(num < curr->element){
                curr = curr->left;
            }else{
                curr = curr->right;
            }
        }

        node* temp = create_node(num,true,NULL);

        if(num < parent->element){
            parent->left = curr;
        }else{
            parent->right = curr;
        }

        restructure(temp);
        size++;
    }

    void remove(int num){

        node* curr = root;
        node* parent = curr->parent;
        
        while(curr){
            parent = curr;

            if(num < curr->element){
                curr = curr->left;
            }else{
                curr = curr->right;
            }

            if(curr->element == num){
                node* temp = curr->right;
                while(temp){
                    temp = temp->left;
                }
                curr->element = temp->element;
                if(temp->is_red){
                    if(temp->parent && temp->parent->left == temp){
                        if(temp->left){
                            temp->parent->left = temp->left;
                            temp->left->parent = temp->parent;
                        }else if(temp->right){
                            temp->parent->right = temp->right;
                            temp->left->parent = temp->parent;
                        }
                    }else if(temp->parent && temp->parent->right == temp){
                        if(temp->left){
                            temp->parent->left = temp->left;
                            temp->left->parent = temp->parent;
                        }else if(temp->right){
                            temp->parent->right = temp->right;
                            temp->left->parent = temp->parent;
                        }
                    }
                    delete temp;
                    size--;
                    return;
                }else{
                    if(!temp->is_red && temp->right->is_red){
                        temp->right->is_red = false;
                        size--;
                        delete temp;
                        return;
                    }
                    if(!temp->is_red && !temp->right->is_red){

                    }
                }
            }
        }
    }

    private:

    void recolor(node* n){
        n->is_red = false;
        n->left->is_red = true;
        n->right->is_red = true;
    }

    void restructure(node* n){
        
        node* par = n->parent;

        if(!par || !par->is_red || !n->is_red){
            return;
        }

        node* gPar = par->parent;
        node* uncle = gPar->left == par ? gPar->right : gPar->left;

        if(!uncle && !uncle->is_red){
            cout << "TEST CASE 1" << endl;

            bool ptopr = par->left == n;
            bool gtopr = gPar->left == par;

            if(ptopr && gtopr){
                zigright(par);
                recolor(par);
                cout << "ZIGRIGHT" << endl;
            }else if(!ptopr && gtopr){
                zigleft(n);
                zigright(n);
                recolor(n);
                cout << "ZIGZAGRIGHT" << endl;
            }else if(!gtopr && ptopr){
                zigright(n);
                zigleft(n);
                recolor(n);
                cout << "ZIGZAGLEFT" << endl;
            }else{
                zigleft(par);
                recolor(n);
                cout << "ZIGLEFT" << endl;
            }
        }else{
            cout << "TEST CASE 2" << endl;

            par->is_red = false;
            uncle->is_red =  false;

            if(gPar != root){
                gPar->is_red = true;
            }

            if(gPar->parent && gPar->parent->is_red){
                restructure(gPar->parent);
            }
            return;
        }

    }

     void zigleft(node* curr) {
        node* x = curr;
        node* y = x->parent;
    
        if(y != root){
            node* z = y->parent;
            if(y == z->left){
                x = z->left;
            }else{
                x = z->right;
            }
            z = x->parent;
        }else{
            root = x;
            x->parent = NULL;
        }

        if(x->left){
            y->right = x->left;
            x->left->parent = y;
        }else{
            y->right = NULL;
        }

        x->left = y;
        y->parent = x;
    }

    void zigright(node* curr){

        node* x = curr;
        node* y = x->parent;

        if(y != root){
            node* z = y->parent;
            if(y == z->right){
                x = z->right;
            }else{
                x = z->left;
            }
            z = x->parent;
        }else{
            x = root;
            x->parent = NULL;
        }

        if(x->right){
            y->left = x->right;
            x->right->parent = y;
        }else{
            y->left = NULL;
        }

        x->right = y;
        y->parent = x;
    }


    public: 
    
    // WARNING. Do not modify these methods below.
    // Doing so will nullify your score for this activity.
    void print() {
        if (isEmpty()) {
            cout << "EMPTY" << endl;
            return;
        }
        cout << "PRE-ORDER: ";
        print_preorder(root);
        cout << endl << "IN-ORDER: ";
        print_inorder(root);
        cout << endl << "POST-ORDER: ";
        print_postorder(root);
        cout << endl << "STATUS: " << check_health(root, NULL) << endl;
    }

    bool isEmpty() {
        return size == 0;
    }

    void print_preorder(node* curr) {
        cout << curr->element;
        if (curr->is_red) {
            cout << "(R) ";
        } else {
            cout << "(B) ";
        }
        if (curr->left != NULL) {
            print_preorder(curr->left);
        }
        if (curr->right != NULL) {
            print_preorder(curr->right);
        }
    }

    void print_inorder(node* curr) {
        if (curr->left != NULL) {
            print_inorder(curr->left);
        }
        cout << curr->element;
        if (curr->is_red) {
            cout << "(R) ";
        } else {
            cout << "(B) ";
        }
        if (curr->right != NULL) {
            print_inorder(curr->right);
        }
    }

    void print_postorder(node* curr) {
        if (curr->left != NULL) {
            print_postorder(curr->left);
        }
        if (curr->right != NULL) {
            print_postorder(curr->right);
        }
        cout << curr->element;
        if (curr->is_red) {
            cout << "(R) ";
        } else {
            cout << "(B) ";
        }
    }

    // WARNING. Do not modify this method.
    // Doing so will nullify your score for this activity.
    bool check_health(node* curr, node* parent) {
        bool health = curr->parent == parent;
        if (curr->left != NULL) {
            health &= check_health(curr->left, curr);
        }
        if (curr->right != NULL) {
            health &= check_health(curr->right, curr);
        }
        return health;
    }
};