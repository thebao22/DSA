#include<iostream>
#include <vector>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};
//khai bao ham
NODE* Search(NODE* pRoot, int x);
void Insert(NODE* &pRoot, int x);
void Remove(NODE* &pRoot, int x);
NODE* createTree(int a[], int n);
void removeTree(NODE* &pRoot);
int Height(NODE* pRoot);
int countLess(NODE* pRoot, int x);
int countGreater(NODE* pRoot, int x);
bool isBST(NODE* pRoot);
bool isFullBST(NODE* pRoot);
//dinh nghia ham
NODE* Search(NODE* pRoot, int x) {
    if (pRoot == nullptr) return nullptr;
    if (pRoot->key == x) return pRoot;
    if (x < pRoot->key) return Search(pRoot->p_left, x);
    else return Search(pRoot->p_right, x);
}
void Insert(NODE* &pRoot, int x){
	if(pRoot == nullptr) {
		pRoot = new NODE();
        pRoot->key = x;
        pRoot->p_left = nullptr;
        pRoot->p_right = nullptr;
		return;
	}
	if(pRoot->key > x) Insert(pRoot->p_left, x);
	else if (pRoot->key < x) Insert(pRoot->p_right, x);
}
void Remove(NODE* &pRoot, int x){
	if(pRoot == nullptr) return;
	if(pRoot -> key > x) {Remove(pRoot->p_left,x); return;}
	else if (pRoot->key < x) {Remove(pRoot->p_right, x); return;}
    else {
	if(pRoot->p_left == nullptr && pRoot -> p_right == nullptr){
		delete pRoot;
		pRoot = nullptr;
	}
	else if (pRoot->p_left == nullptr) {
            NODE* temp = pRoot;
            pRoot = pRoot->p_right;
            delete temp;
        }
        else if (pRoot->p_right == nullptr) {
            NODE* temp = pRoot;
            pRoot = pRoot->p_left;
            delete temp;
        }
	else {
		NODE* temp = pRoot->p_right;
		while(temp->p_left != nullptr) temp = temp->p_left;
		pRoot->key = temp->key;
		Remove(pRoot->p_right, temp->key);
	}
    }
}
NODE* createTree(int a[], int n){
    NODE* pRoot = nullptr;
    for(int i = 0; i < n; i++){
        Insert(pRoot, a[i]);
    }
    return pRoot;
}
void removeTree(NODE* &pRoot){
	if(pRoot == nullptr) return;
	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
	pRoot = nullptr;
}
int Height(NODE* pRoot) {
    if (pRoot == nullptr) return -1;
    vector<NODE*> queue;
    queue.push_back(pRoot);
    size_t front = 0; 
    int height = 0;

    while (front < queue.size()) {
        int size = queue.size() - front;
        for (int i = 0; i < size; ++i) {
            NODE* node = queue[front++];
            if (node->p_left) queue.push_back(node->p_left);
            if (node->p_right) queue.push_back(node->p_right);
        }
        height++;
    }
    return height;
}
int countLess(NODE* pRoot, int x){
	if(pRoot == nullptr)return 0;
	int count = 0;
	if(x <= pRoot->key) count = countLess(pRoot->p_left, x);
	else {
		count += countLess(pRoot->p_right, x) + countLess(pRoot->p_left,x) + 1;
	}
	return count;
}
int countGreater(NODE* pRoot, int x){
    if(pRoot == nullptr)return 0;
    int count = 0;
    if(x >= pRoot->key) count = countGreater(pRoot->p_right, x);
    else {
        count += countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right,x) + 1;
    }
    return count;
}
bool isBST(NODE* pRoot){
    if(pRoot == nullptr) return true;
    if(pRoot->p_left != nullptr && pRoot->p_left->key > pRoot->key) return false;
    if(pRoot->p_right != nullptr && pRoot->p_right->key < pRoot->key) return false;
    return isBST(pRoot->p_left) && isBST(pRoot->p_right);
}
bool isFullBST(NODE* pRoot){
    if(pRoot == nullptr) return true;
    if((pRoot->p_left == nullptr && pRoot->p_right != nullptr) || (pRoot->p_left != nullptr && pRoot->p_right == nullptr)) return false;
    return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
}
int main(){
    int a[] = {5,3,7,1,4,6,8};
    NODE* tree = createTree(a,7);
    cout << "Height of tree: " << Height(tree) << endl;
    cout << "Count less than 4: " << countLess(tree,4) << endl;
    cout << "Count greater than 4: " << countGreater(tree,4) << endl;
    cout << "Is BST: " << isBST(tree) << endl;
    cout << "Is full BST: " << isFullBST(tree) << endl;
    removeTree(tree);
    return 0;
}