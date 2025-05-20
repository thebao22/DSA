#include<iostream>
#include <vector>
using namespace std;
struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};
//Khai bao ham
NODE* createNode(int data);
void Insert(NODE* &pRoot, int x);
void Remove(NODE* &pRoot, int x);
bool isAVL(NODE* pRoot);
//dinh nghia ham
NODE* createNode(int data){
    NODE* newnode = new NODE();
    newnode->key = data;
    newnode->p_left = nullptr;
    newnode->p_right = nullptr;
    newnode->height = 1; // Initialize height to 1 for a new node
    return newnode;
}
int getHeight(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    return pRoot->height;
}
int max(int a, int b){
	if(a>b) return a;
	else return b;
}
int updateHeight(NODE* pRoot){
    if(pRoot == nullptr) return 0;
    pRoot->height = max(getHeight(pRoot->p_left), getHeight(pRoot->p_right)) + 1;
    return pRoot->height;
}
NODE* LeftRotate(NODE* pRoot){
	NODE* temp = pRoot -> p_right;
	NODE* temp2 = temp -> p_left;
	
	temp->p_left = pRoot;
	pRoot -> p_right = temp2;
	
	updateHeight(pRoot);
	updateHeight(temp);

	return temp;
}
NODE* RightRotate(NODE* pRoot){
	NODE* temp = pRoot -> p_left;
	NODE* temp2 = temp -> p_right;
	
	temp->p_right = pRoot;
	pRoot -> p_left= temp2;
	
	updateHeight(pRoot);
	updateHeight(temp);
	
	return temp;
}
void Insert(NODE* &pRoot, int x){
	if(pRoot == nullptr){
		pRoot = createNode(x);
		return;
	}
	if(pRoot->key > x) Insert(pRoot->p_left,x);
	else if(pRoot->key < x) Insert(pRoot->p_right,x);
	else return;
	
	updateHeight(pRoot);
	
	int check = getHeight(pRoot->p_left) - getHeight(pRoot->p_right);
	if(check > 1){
		if(x < pRoot->p_left->key) pRoot = RightRotate(pRoot);
		else if(x>pRoot->p_left->key){
			pRoot->p_left = LeftRotate(pRoot->p_left);
			pRoot = RightRotate(pRoot);
		}
	}
	if(check < -1){
		if(x > pRoot->p_right->key) pRoot = LeftRotate(pRoot);
		else if(x<pRoot->p_right->key){
			pRoot->p_right = RightRotate(pRoot->p_right);
			pRoot = LeftRotate(pRoot);
		}
	}
}
void Remove(NODE* &pRoot, int x){
	if(pRoot == nullptr) return;
	if(pRoot -> key > x) {
		Remove(pRoot->p_left,x);
		return;
	}
	else if (pRoot->key < x) {
		Remove(pRoot->p_right, x);
		return;
	}
	if(pRoot->p_left == nullptr && pRoot -> p_right == nullptr){
		delete pRoot;
		pRoot = nullptr;
	}
	    else if(pRoot->p_left == nullptr){
        NODE* temp = pRoot;
        pRoot = pRoot->p_right;
        delete temp;
    }
    else if(pRoot->p_right == nullptr){
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
	if (pRoot == nullptr) return;
	updateHeight(pRoot);
	
	int check = getHeight(pRoot->p_left) - getHeight(pRoot->p_right);
	if(check > 1){
		int check_2 = getHeight(pRoot->p_left->p_left) - getHeight(pRoot->p_left->p_right);
		if(check_2 >= 0) pRoot = RightRotate(pRoot);
		else {
			pRoot->p_left = LeftRotate(pRoot->p_left);
			pRoot = RightRotate(pRoot);
		}
	}
	if(check < -1){
		int check_2 = getHeight(pRoot->p_right->p_left) - getHeight(pRoot->p_right->p_right);
		if(check_2 <= 0) pRoot = LeftRotate(pRoot);
		else {
			pRoot->p_right = RightRotate(pRoot->p_right);
			pRoot = LeftRotate(pRoot);
		}
	}

}
bool isAVL(NODE* pRoot){
	if(pRoot == nullptr)return true;
	int check = getHeight(pRoot->p_left) - getHeight(pRoot->p_right);
	if(check > 1 || check <-1) return false;
	return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}
int main(){
    NODE* pRoot = nullptr;
    int a[] = {1,2,3,4,5,6,7};
    for(int i = 0; i < 7; i++){
        Insert(pRoot,a[i]);
    }
    bool check = isAVL(pRoot);
    cout << "Is AVL: " << check << endl;
    Remove(pRoot, 4);
    check = isAVL(pRoot);
    cout << "Is AVL: " << check << endl;
}