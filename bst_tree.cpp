#include<iostream>
#include<utility>
#include<string>
#include<vector>
#include<cmath>
#include<queue>
#include<iterator>
#include<algorithm>
#include<set>

#define ll long long
 
using namespace std;

class Bstnode{
    public:
        ll data;
        ll depth;
        Bstnode* left;
        Bstnode* right;
        Bstnode(ll data){
            this->data= data;
            this->left=NULL;
            this->right=NULL;
        }
};

Bstnode* createNode(ll data){
    Bstnode* newNode = new Bstnode(data);
    return newNode;
}
Bstnode* insert(Bstnode* root, ll data){
    if(root==NULL){
        root = createNode(data);
        return root;
    }
    else if(data<=root->data){
        root->left = insert(root->left, data);
    }
    else{
        root->right = insert(root->right, data);
    }
    return root;
}
Bstnode* findMin(Bstnode* root){
    Bstnode* temp = root;
    while(temp->left!=NULL){
        temp = temp->left;
    }
    return temp;
}

Bstnode* deleteNode(Bstnode* root, ll data){
    if(root == NULL){
        return root;
    }
    if(data<root->data){
        root->left= deleteNode(root->left, data);    
    }
    else if(data>root->data){
        root->right= deleteNode(root->right, data);
    }
    else{
        if(root->right==NULL && root->left==NULL){
            delete root;
            root = NULL;
        }
        else if(root->left==NULL){
            Bstnode* temp = root;
            root = temp->right;
            delete temp;
        }
        else if(root->right==NULL){
            Bstnode* temp = root->left;
            root=temp->left;
            delete temp;
        }else{
            Bstnode* temp = findMin(root->right);
            root->data=temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

void inorder(Bstnode* root){
    if(root==NULL){
        return;
    }
    inorder(root->left);
    cout<<root->data<<' ';
    inorder(root->right);
}
void depth(Bstnode* root, ll d){
    root->depth=d;
    if(root->left!=NULL){
        depth(root->left, d+1);
    }
    if(root->right!=NULL){
        depth(root->right, d+1);
    }
    return;
}

int main(){
    Bstnode* root = NULL;
    for(ll i=0;i<5;i++){
        ll temp;
        cin>>temp;
        root = insert(root, temp);
    }
    inorder(root);
    ll temp;
    cin>>temp;
    root = deleteNode(root, temp);
    inorder(root);

}