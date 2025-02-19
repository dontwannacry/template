struct node{
	node *left = nullptr,*right = nullptr;
	char type;
	node(char x){type = x;}
	void del(){
		left->right = right;
		right->left = left;
		delete this;
	}
	void push_right(node *x){
		x->right = right;
		x->left = this;
		if(right != nullptr)right->left = x;
		right = x;
	}
};
