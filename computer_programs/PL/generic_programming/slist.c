struct node
{
	struct node *next;
	int data;
};

typedef bool(*remove_fun)(const struct node *node, int value);

bool rm(const struct node *node, int value) 
{
	return (node->data == value) ? true : false;
}

struct node * remove_if(node *head, int value, remove_fn rm) {
	for(struct node *prev = NULL, *cur = head; curr != NULL;) {
		struct node const *next = curr->next;
		if (rm(curr, value)) {
			if (prev) {  // 不是第一个节点的时候
				prev->next = next;  // 改变next指针的指向
			} else {  // 当是第一个节点的时候，prev此时还是NULL，会进入此逻辑
				head = next;  // 改变head指针的指向
			}
			free(curr);
		} else {
			prev = curr;  // 因删除节点的操作是删除此节点，并让此节点的前一个节点指向被删除节点后一个节点，故需要prev保留上一个节点
		}
		curr = next;
	}
	return head;
}

void remove(struct node **head, int value, remove_fn rm)
{
	for(struct node **cur = head; *cur != NULL;) {
		struct node *entry = *cur;
		if (rm(entry, value)) {
			*cur = entry->next;
			free(entry);
		} else {
			cur = &entry->next;  // 指向下一个节点
		}
	}
}