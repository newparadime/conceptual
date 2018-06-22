//
// Definition for binary tree:
// template<typename T>
// struct Tree {
//   Tree(const T &v) : value(v), left(nullptr), right(nullptr) {}
//   T value;
//   Tree *left;
//   Tree *right;
// };
 
struct stack_t {
    int size;
    void* mallocStart;
    int nElem;
    Tree<int>** data;
};

stack_t* stackCreate(int size) {
    stack_t* stack = (stack_t*)malloc(sizeof(stack_t));
    stack->size = size;
    stack->nElem = 0;
    stack->mallocStart = malloc(sizeof(Tree<int>*)*size);
    stack->data = (Tree<int>**)stack->mallocStart;
    return stack;
}

void stackDestroy(stack_t* stack) {
    free(stack->mallocStart);
    free(stack);
}

void stackPush(stack_t* stack, Tree<int>* elem) {
    size_t offset = stack->data - (Tree<int>**)stack->mallocStart;
    if(stack->size <= stack->nElem+offset) {
        if(offset >= stack->size/2) {
            memcpy(stack->mallocStart, stack->data, stack->nElem*sizeof(Tree<int>*));
            stack->data = (Tree<int>**)stack->mallocStart;
        }
        else {
            stack->mallocStart = realloc(stack->mallocStart, stack->size*2*sizeof(Tree<int>*));
            stack->data = (Tree<int>**)stack->mallocStart + offset;
            stack->size *= 2;    
        }
    }
    stack->data[stack->nElem] = elem;
    stack->nElem++;
}

Tree<int>* stackPop(stack_t* stack) {
    Tree<int>* val = stack->data[0];
    stack->data++;
    stack->nElem--;
    return val;
}

std::vector<int> traverseTree(Tree<int> * t) {
    stack_t* q = stackCreate(100);
    std::vector<int> R;
    stackPush(q, t);
    while(q->nElem > 0) {
        Tree<int>* node = stackPop(q);
        if (node != nullptr) {
            R.push_back(node->value);
            stackPush(q, node->left);
            stackPush(q, node->right);    
        }
    }
    stackDestroy(q);
    return R;
}
