#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 1, ERROR = 0 } Status;

typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
    struct BSTNode* parent;
} BSTNode;

BSTNode* CreateNode(int val){
	BSTNode* p = (BSTNode*)malloc(sizeof(BSTNode));
	if(p == NULL) 
	return NULL;
	p->left = NULL;
	p->right = NULL;
	p->data = val;
	p->parent = NULL; 
	return p;
}

Status Insert(BSTNode** root, int val){
	if(root == NULL)
	return ERROR;
	if(*root == NULL){
		*root = CreateNode(val);
		return OK;
	}
	if((*root)->data > val ){
		if((*root)->left == NULL){ 
            (*root)->left = CreateNode(val);
            (*root)->left->parent = *root;  
            return OK;
        } else {
            return Insert(&((*root)->left), val);
        }
	}else if((*root)->data < val ){if((*root)->right == NULL){
            (*root)->right = CreateNode(val);
            (*root)->right->parent = *root; 
            return OK;
        } else {
            return Insert(&((*root)->right), val);
        	}
		}else{
		return ERROR;
		}
}

Status SetParent(BSTNode* root){
	if(root == NULL)
	return ERROR;
	if(root->left != NULL){
		root->left->parent = root;
		SetParent(root->left);
	} 
	if(root->right != NULL){
		root->right->parent = root;
		SetParent(root->right);
	}
	return OK;
}

BSTNode* Search(BSTNode* root, int val){
	if(root == NULL)
	return NULL; 
	if(root->data >val){
		return Search(root->left,val);
	}else if(root->data < val){
		return Search(root->right,val); 
	}else{
	return root;	
	} 
}

BSTNode* GetMin(BSTNode* root){
	if(root == NULL)
	return NULL;
	BSTNode* p = NULL;
	while(root!=NULL){
		p = root;
		root = p->left;
	}
	return p;
}

BSTNode* GetMax(BSTNode* root){
	if(root == NULL)
	return NULL;
	while(root->right != NULL){
		root = root->right;
	} 
 	return root;	
} 

BSTNode* Predecessor(BSTNode* node){
	if(node == NULL)
	return NULL;
	if(node->left != NULL){
		return GetMax(node->left);
	}else{	
		BSTNode *p;
		p = node->parent;
		while(p !=NULL && p->right != node){
			node = p;
			p = node->parent;
		}
		return p;
	}
}

BSTNode* Successor(BSTNode* node){
	if(node == NULL)
	return NULL;
	if(node->right){
		return GetMin(node->right);
	}else{
		BSTNode *p;
		p = node->parent;
		while(p !=NULL && p->left != node){
			node = p;
			p = node->parent;
		}
		return p;
	}
	
}



int GetHeight(BSTNode* root){
	if(root == NULL)
	return 0;
	int l = GetHeight(root->left);
	int r = GetHeight(root->right);
	if(l > r){
		return l+1;
	}else{
		return r+1;
	}
}

int CountNodes(BSTNode* root){
	if(root == NULL)
	return 0;
	return CountNodes(root->left)+CountNodes(root->right)+1;
}

int GetLevel(BSTNode* node){
	if(node == NULL)
	return -1;
	int cnt = 1;
	while(node->parent != NULL){
		cnt++;
		node=node->parent;
	}
	return cnt;
}

int IsBST(BSTNode* root){
	if(root == NULL)
	return 1;
	 if(root->left){
	 	if(root->data <= root->left->data){
	 		return 0;
		 }
	 }
	 if(root->right){
	 	if(root->data >= root->right->data){
	 		return 0;
		 }
	 }
	 return IsBST(root->left)&&IsBST(root->right);
}

Status Delete(BSTNode** root, int val){
    if(root == NULL || *root == NULL)
        return ERROR;
    if((*root)->data < val){
        return Delete(&(*root)->right, val);
    } else if((*root)->data > val){
        return Delete(&(*root)->left, val);
    } else {
        BSTNode* temp = *root;
        if((*root)->left == NULL && (*root)->right == NULL){
            *root = NULL;
            free(temp);
        }
        else if((*root)->left == NULL){
            *root = (*root)->right;
            if(*root) 
			(*root)->parent = temp->parent;
            free(temp);
        }
        else if((*root)->right == NULL){
            *root = (*root)->left;
            if(*root)
			 (*root)->parent = temp->parent;
            free(temp);
        }
        else{
            BSTNode* minNode = GetMin((*root)->right);
            (*root)->data = minNode->data;
            Delete(&(*root)->right, minNode->data);
        }
        return OK;
    }
}

Status DeleteByPred(BSTNode** root, int val){
    if(root == NULL || *root == NULL)
        return ERROR;
    
    if((*root)->data < val){
        return DeleteByPred(&(*root)->right, val);
    } else if((*root)->data > val){
        return DeleteByPred(&(*root)->left, val);
    } else {
        BSTNode *del = *root;
        
        if((*root)->left == NULL && (*root)->right == NULL){
            *root = NULL;
            free(del);
        } else if((*root)->left == NULL){
            *root = (*root)->right;
            (*root)->parent = del->parent;
            free(del);
        } else if((*root)->right == NULL){
            *root = (*root)->left;
            (*root)->parent = del->parent;
            free(del);
        } else {
            BSTNode* MaxNode = GetMax((*root)->left);
            (*root)->data = MaxNode->data;
            return DeleteByPred(&(*root)->left, MaxNode->data);
        }
        return OK;
    }
}
int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/
