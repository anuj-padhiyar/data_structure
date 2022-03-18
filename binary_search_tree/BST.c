#include<stdio.h>
#include<stdlib.h>

typedef struct BST{
    int data;
    struct BST *left,*right;
}BST;

BST* find_min(BST* node){
    while(node->left != NULL)
        node = node->left;
    return node;
}

BST* find_max(BST* node){
    while(node->right != NULL)
        node = node->right;
    return node;
}

BST* insert(BST* node,int value){
    if(node == NULL){
        node = (BST*)malloc(sizeof(BST));
        node->data = value;
        node->right = NULL;
        node->left = NULL;
        return node;
    }
    if(value > node->data)
        node->right = insert(node->right,value);
    else
        node->left = insert(node->left,value);
    return node;
}

BST* delete(BST* node,int value){
    BST* temp;
    if(node == NULL){
        return node;
    }
    if(value < node->data){
        node->left = delete(node->left,value);
        return node;
    }
    if(value > node->data){
        node->right = delete(node->right,value);
        return node;
    }

    if(node->left == NULL && node->right == NULL){
        temp = node;
        free(temp);
        return NULL;
    }
    if(node->left == NULL){
        temp = node;
        node = node->right;
        free(temp);
        return node;
    }
    if(node->right == NULL){
        temp = node;
        node = node->left;
        free(temp);
        return node;
    }
    
    temp = find_min(node->right);
    node->data = temp->data;
    node->right = delete(node->right,value);
    return node;
}

void preorder_traversal(BST* root){
    if(root != NULL){
        printf("%d ",root->data);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

void inorder_traversal(BST* root){
    if(root != NULL){
        inorder_traversal(root->left);
        printf("%d ",root->data);
        inorder_traversal(root->right);
    }
}

void postorder_traversal(BST* root){
    if(root != NULL){
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ",root->data);
    }
}

BST* search(BST* node,int value){
    if(node ==NULL)
        return NULL;
    if(value == node->data)
        return node;
    if(value > node->data)
        return search(node->right,value);
    return search(node->left,value);
}

int check_tree(BST* node){
    if(node == NULL){
        printf("Tree Not Available");
        return 0;
    }
    return 1;
}

int total_node(BST* node){
    if(node == NULL)
        return 0;
    return 1+total_node(node->left)+total_node(node->right);
}

int count_leaf(BST* node){
    if(node == NULL)
        return 0;
    if(node->left==NULL && node->right == NULL)
        return 1;
    return count_leaf(node->left)+count_leaf(node->right);
}

int count_degree1(BST* node){
    if(node == NULL || (node->left==NULL && node->right==NULL))
        return 0;
    if(node->left == NULL || node->right == NULL)
        return 1+count_degree1(node->left)+count_degree1(node->right);
    return count_degree1(node->left)+count_degree1(node->right);
}

int count_degree2(BST* node){
    if(node == NULL || (node->left==NULL && node->right==NULL))
        return 0;
    if(node->left == NULL || node->right == NULL)
        return count_degree2(node->left)+count_degree2(node->right);
    return 1+count_degree2(node->left)+count_degree2(node->right);
}

int height(BST* node){
    if(node == NULL || (node->left==NULL && node->right==NULL))
        return 0;
    int hl = height(node->left);
    int hr = height(node->right);
    if(hl>hr)
        return hl+1;
    return hr+1;
}

void main(){
    int choice,value,size,i;
    BST *root = NULL;
    while(1){
        system("clear");
        printf("\n\n1)Insertion\n2)Deletation\n3)Traversal\n4)Search\n");
        printf("5)Find Max\n6)Find Min\n7)Total Nodes\n8)Total Node With Degree 2\n");
        printf("9)Total Node With Degree 1\n10)Total Leaf Node\n11)Height Of Tree\n12)Exit");
        printf("\nEnter Your Choice : ");
        scanf("%d",&choice);
        switch (choice){
            case 1:
                printf("\n\n1)Insert Multiple Data\n2)Insert Single Data\nEnter Choice : ");
                scanf("%d",&choice);
                switch (choice){
                    case 1:
                        printf("Enter Total Length Of Insert Data : ");
                        scanf("%d",&size);
                        printf("Enter Multiple Data Seperate By Space : ");
                        for(i=0;i<size;i++){
                            scanf("%d",&value);
                            root = insert(root,value);
                        }
                        break;

                    case 2:
                        printf("Enter Data : ");
                        scanf("%d",&value);
                        root = insert(root,value);
                        break;

                    default:
                        break;
                }
                printf("Inserted");
                break;

            case 2:
                if(check_tree(root)){
                    printf("Enter Data Of Node For Delete : ");
                    scanf("%d",&value);
                    if(search(root,value) != NULL){
                        delete(root,value);
                        printf("Deleted");
                    }else
                        printf("No Record Found !!");
                }
                break;

            case 3:
                if(check_tree(root)){
                    printf("\n\n1)Preorder\n2)Inorder\n3)Postorder\nEnter Choice : ");
                    scanf("%d",&choice);
                    switch (choice){
                        case 1:
                            printf("Preorder Traversal : ");
                            preorder_traversal(root);
                            break;

                        case 2:
                            printf("Inorder Traversal : ");
                            inorder_traversal(root);
                            break;

                        case 3:
                            printf("Postorder Traversal : ");
                            postorder_traversal(root);
                            break;
                    
                        default:
                            break;
                    }
                }
                break;

            case 4:
                if(check_tree(root)){
                    printf("Enter Data Searching : ");
                    scanf("%d",&value);
                    root = search(root,value);
                    if(root == NULL)
                        printf("%d Not Found",value);
                    else
                        printf("%d Is Found.",value);
                }
                break;

            case 5:
                if(check_tree(root))
                    printf("Maximum Value In The Tree Is %d",find_max(root)->data);
                break;

            case 6:
                if(check_tree(root))
                    printf("Minimum Value In The Tree Is %d",find_min(root)->data);
                break;

            case 7:
                printf("Total Nodes In Tree: %d",total_node(root));
                break;

            case 8:
                printf("Total Nodes With Degree 1 : %d",count_degree1(root));
                break;

            case 9:
                printf("Total Nodes With Degree 2 : %d",count_degree2(root));
                break;
                
            case 10:
                printf("Total Leaf Nodes : %d",count_leaf(root));
                break;
            
            case 11:
                printf("Height Of Tree : %d",height(root));
                break;

            case 12:
            default:
                exit(0);
                break;
        }
    }
}