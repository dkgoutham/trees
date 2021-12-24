#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<utility>
#include<algorithm>

using namespace std;

#define ll long long

class Avlnode{
    public:
        ll data;
        ll rh;
        ll lh;
        ll height;
        ll balance;
        ll depth;
        ll inorder;
        Avlnode* right;
        Avlnode* left;
        Avlnode(ll data){
            this->data=data;
            this->lh=-1;
            this->rh=-1;
            this->right=NULL;
            this->left=NULL;
        }
};

void update(Avlnode* root){
    if(root->left!=NULL){
        root->lh = root->left->height;
    }
    if(root->right!=NULL){
        root->rh = root->right->height;
    }
    root->height = 1+ max(root->lh, root->rh);
    root->balance = root->rh-root->lh;
}
Avlnode* createNode(ll data){
    Avlnode* root = new Avlnode(data);
    return root;
}
Avlnode* leftRotation(Avlnode* root){
    Avlnode* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    // root = temp;
    // delete temp;   memory reduction ig
    // update(root->left);
    // update(root);
    // return root;
    update(root);
    update(temp);
    return temp;
}
Avlnode* rightRotation(Avlnode* root){
    Avlnode* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    // root = temp;
    // delete temp;   memory reduction ig
    // update(root->left);
    // update(root);
    // return root;
    update(root);
    update(temp);
    return temp;
}
Avlnode* leftLeftcase(Avlnode* root){
    return rightRotation(root);
}
Avlnode* rightRightcase(Avlnode* root){
    return leftRotation(root);
}
Avlnode* leftRightcase(Avlnode* root){
    root->left= leftRotation(root->left);
    return leftLeftcase(root);
}
Avlnode* rightLeftcase(Avlnode* root){
    root->right = rightRotation(root->right);
    return rightRightcase(root);
}
Avlnode* balanceTree(Avlnode* root){
    if(root->balance == 2){
        if(root->right->balance >= 0){
            return rightRightcase(root);
        }else{
            return rightLeftcase(root);
        }
    }
    if(root->balance == -2){
        if(root->left->balance <= 0){
            return leftLeftcase(root);        
        }else{
            return leftRightcase(root);
        }
    }
    return root;
}
void depthValue(Avlnode* root, ll d){
    root->depth=d;
    if(root->left!=NULL){
        depthValue(root->left, d+1);
    }
    if(root->right!=NULL){
        depthValue(root->right, d+1);
    }
    return;
}
ll maxDepth(Avlnode* root){
    if(root==NULL){
        return 0;
    }else{
        ll left = maxDepth(root->left);
        ll right = maxDepth(root->right);
        if(left>right){
            return (left+1);
        }else{
            return (right+1);
        }
    }
}
ll i=0;
void inorder(Avlnode* root){
    if(root==NULL){
        return;
    }
    inorder(root->left);
    cout<<root->data;
    root->inorder = i;
    i++;
    inorder(root->right);
}
void allotingInorder(Avlnode* root, vector< vector<char> >& mat){
    if(root==NULL){
        return;
    }
    allotingInorder(root->left, mat);
    mat[root->depth][root->inorder]=root->data;
    allotingInorder(root->right, mat);
}
Avlnode* insertion(ll data, Avlnode* root){
    if(root==NULL){
        root = createNode(data);
    }
    if(root->data>data){
        root->left = insertion(data, root->left);
    }
    if(root->data<data){
        root->right = insertion(data, root->right);
    }
    update(root);
    return balanceTree(root);
}

int main(){
    Avlnode* root=NULL;
    for(ll i=0;i<10;i++){
        ll temp;
        cin>>temp;
        root = insertion(temp, root);
    }
    depthValue(root, 0);
    inorder(root);
    ll d=maxDepth(root);
    cout<<d<<'\n';
    vector< vector<char> >mat(d, vector<char>(11, ' '));
    allotingInorder(root, mat);
    for(ll i=0;i<d;i++){
        for(ll j=0;j<11;j++){
            cout<<mat[i][j];
        }
        cout<<'\n';
    }
}