#include<bits/stdc++.h>
using namespace std;

struct Node {
    char data;
    struct Node * left;
    struct Node * right;
};

Node * newNode(char data){
    Node * temp = new Node;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void findMinDistanceFromNodeToLeaf(Node * root,int *distance,int curDistance){
    if(root==NULL)
    return;
    
    if(root->left == NULL && root->right == NULL)
    if(curDistance<*distance){
    *distance = curDistance;
    return;
    }
    
    findMinDistanceFromNodeToLeaf(root->left,distance,curDistance+1);
    findMinDistanceFromNodeToLeaf(root->right,distance,curDistance+1);
}

bool findMinSuccessorLeafDistance(Node * root,int key,int *distance,int *backDistance){
    if(root==NULL)
    return false;
    if(root->data == key){
    *backDistance = *backDistance + 1;
     findMinDistanceFromNodeToLeaf(root,distance,0);
     //cout<<endl<<"decendents of node '"<<root->data<<"' computed: "<<*distance<<endl;
     return true;
    }
    
     int backDist = 0;
    if(findMinSuccessorLeafDistance(root->left,key,distance,&backDist)){
        findMinDistanceFromNodeToLeaf(root->right,distance,backDist+1);
        *backDistance = *backDistance + 1;
        return true;
    }
    else if(findMinSuccessorLeafDistance(root->right,key,distance,&backDist)){
        //cout<<endl<<"I am a parent"<<endl;
        //cout<<endl<<"I found my child a key in distance: "<<backDist<<endl;
        findMinDistanceFromNodeToLeaf(root->left,distance,backDist+1);
        //cout<<endl<<"My computed distance: "<<*distance<<endl;
        *backDistance = *backDistance + 1;
        return true;
    }else
    return false;
    
}


void printTree(Node * root,int level){
    if(root==NULL)
    return;
    printTree(root->left,level+1);
    if(level == 1)
    cout<<"Root ->";
    for(int i=1;i<level;i++)
    cout<<"           ";
    cout<<root->data<<endl;
    printTree(root->right,level+1);
}

int main()
{
    struct Node *root        = newNode('A');
    root->left               = newNode('B');
    root->right              = newNode('C');
    root->right->left        = newNode('E');
    root->right->right       = newNode('F');
    root->right->left->left  = newNode('G');
    root->right->left->left->left  = newNode('I');
    root->right->left->left->right = newNode('J');
    root->right->right->right      = newNode('H');
    root->right->right->right->left = newNode('K');
    printTree(root,1);
    
    int distance = INT_MAX;
    int backDistance = 0;
    //findMinDistanceFromNodeToLeaf(root->right,&distance,0);
    //cout<<endl<<"Distance to all leaf from C: "<<distance;
    //distance = INT_MAX;
    findMinSuccessorLeafDistance(root,'H',&distance,&backDistance);
    cout<<endl<<"Overall distance: "<<distance;
    
    return 0;
}