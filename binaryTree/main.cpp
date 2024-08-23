#include <iostream>
using namespace std;

//这份代码实现二叉树的创建、遍历、复制、计算总结点、计算叶子总数、树的深度
class Node {
public:
    char c;
    Node* left;
    Node* right;

    Node(){};
    Node(char ch,Node* le=nullptr,Node* ri=nullptr):c(ch),left(le),right(ri) {}
};


//1.利用前序遍历的方法创建二叉树，data字段就设置为char，两个指针域，一个left，一个right
//递归实现创建
void createBinaryTree(Node*& root);
//2.实现二叉树的遍历，并打印二叉树中数据字段   使用中序遍历获取每个元素
void getAllNode(Node*& root);
//3.实现二叉树的复制    使用后续遍历实现二叉树复制
void BinaryTreeCopy(Node*& copy,Node*& root);
//4.求结点总数    在遍历的时候增加传参count用于计数,使用层次遍历和非递归遍历比较麻烦，就是用中序遍历
void getCountofNode(Node*& root,int& count);
//5.求二叉树的深度    传入参数root，使用递归分别计算左右子树的深度，root的深度就max值+1
int Depth(Node*& root);
//计算叶子总数字       传入参数，只有在左右指针域均为nullptr时才++,也要使用到递归遍历,这里与之前有所不同，因为没有双亲指针域所以没办法
//回溯寻找双亲的另一个孩子是否为空，所以在进入之后，先判断是否为空，空就直接返回，再判断左右指针域是否为空，都为空number++
void CountofLeaves(Node*& root,int& number);


int main() {
    Node* root;
    createBinaryTree(root);
    getAllNode(root);
    cout<<endl;
    Node* copyroot;
    BinaryTreeCopy(copyroot,root);
    getAllNode(copyroot);
    cout<<endl;
    int count=0;
    int number=0;
    getCountofNode(root,count);
    cout<<"Count:"<<count<<endl;
    cout<<"Depth:"<<Depth(root)<<endl;
    CountofLeaves(root,number);
    cout<<"Leaves:"<<number<<endl;
    return 0;
}


void createBinaryTree(Node*& root) {
    cout<<"Please input the value of this node"<<endl;
    char ch;
    while(true) {
        cin>>ch;
        if((ch>='a' && ch<='z') || (ch>='A' &&ch<='Z'))
            break;
        cout<<"this input is invalid"<<endl;
    }


    Node* ele=new Node(ch);//创建当前结点并初始化数据字段
    root=ele;     //将ele赋值给上一结点的传入指针

    //选择创建左子树，创建之后并递归调用下一个函数
    char left;
    cout<<"create next left node y/n"<<endl;
    while (true) {
        cin>>left;
        if(left=='y' || left=='n') {
            if(left=='y') {
                createBinaryTree(ele->left);
            }else {
                ele->left=nullptr;
            }
            break;
        }
        cout<<"err:invalid choice,choose again!"<<endl;
    }

    //选择创建右子树，创建之后递归调用创建下一个结点的子树
    char right;
    cout<<"create next right node y/n"<<endl;
    while (true) {
        cin>>right;
        if(right!='y' || right!='n') {
            if(right=='y') {
                createBinaryTree(ele->right);
            }else {
                ele->right=nullptr;
            }
            break;
        }
        cout<<"err:invalid choice,choose again!"<<endl;
    }
}
void getAllNode(Node*& root) {
    if(root==nullptr) {
        return;
    }
    getAllNode(root->left);
    cout<<root->c<<"\t";
    getAllNode(root->right);
}
void BinaryTreeCopy(Node*& copy, Node*& root) {
    if(root==nullptr) {
        copy=nullptr;
        return ;
    }
    Node* ele=new Node();
    copy=ele;
    BinaryTreeCopy(ele->left,root->left);
    BinaryTreeCopy(copy->right,root->right);
    ele->c=root->c;
}
void getCountofNode(Node*& root,int& count) {
    if(root==nullptr)
        return;
    getCountofNode(root->left,count);
    count++;
    getCountofNode(root->right,count);
}
int Depth(Node*& root) {
    if(root==nullptr)
        return 0;
    return (Depth(root->left)>Depth(root->right)?(Depth(root->left)+1):(Depth(root->right)+1));
}
void CountofLeaves(Node*& root,int& number) {
    if(root==nullptr)
        return;
    if(root->left==nullptr && root->right==nullptr) {
        number++;
        return;
    }
    CountofLeaves(root->left,number);
    CountofLeaves(root->right,number);
}
