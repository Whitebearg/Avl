#include "AVL_Node.h"

using namespace std;


AVL_Node*	AVL_Node::OR(AVL_Node* p) // одиночный правый поворот вокруг p
{
	AVL_Node* q = p->left;
	p->left = q->right;
	q->right = p;
	return q;
}

AVL_Node*	AVL_Node::OL(AVL_Node* q) // одиночный левый поворот вокруг q
{
	AVL_Node* p = q->right;
	q->right = p->left;
	p->left = q;
	return p;
}

AVL_Node*	AVL_Node::RL(AVL_Node* q)
{
	AVL_Node* p = q->right,* s = p->left;
	p->left = s->right;
	s->right = p;
	q->right = s;

	q->right = s->left;
	s->left = q;
	return s;
}

AVL_Node*	AVL_Node::LR(AVL_Node* q)
{
	AVL_Node* p = q->left, *s = p->right;
	p->right = s->left;
	s->left = p;
	q->left = s;

	q->left = s->right;
	s->right = q;
	return s;
}

AVL_Node* AVL_Node::left_balance_for_del(AVL_Node* p, bool &h)
{
	if (p->balans <= 0)
	{
		p->balans++;
		if (p->balans == 1)
			h = false;
		return p;
	}

	assert(p->balans == 1);

	if (p->right)
	{
		AVL_Node *q = p->right;
		if (q->balans >= 0)
		{
			OL(p);
			if (q->balans == 0)
			{
				p->balans = 1;
				q->balans = -1;
				h = false;
			}
			else
			{
				p->balans = 0;
				q->balans = 0;
			}
			p = q;
			return p;
		}
		else
			if (p->left)
			{
				AVL_Node *s = p->left;
				RL(p);
				if (s->balans == 1)
					p->balans = -1;
				else
					p->balans = 0;
				if (s->balans = -1)
					q->balans = 1;
				else
					q->balans = 0;
				p = s;
				s->balans = 0;
			}
			else
			{
				{
					AVL_Node *s = p->right->left;
					RL(p);
					if (s->balans == 1)
						p->balans = -1;
					else
						p->balans = 0;
					if (s->balans == -1)
						q->balans = 1;
					else
						q->balans = 0;
					p = s;
					s->balans = 0;

				}
			}
		h = false;
		return p;
	}
}

AVL_Node* AVL_Node::right_balance_for_del(AVL_Node* p, bool &h)
{
	if (p->balans >= 0)
	{
		p->balans --;
		if (p->balans == -1)
			h = false;
		return p;
	}
	if (p->left)
	{
		AVL_Node *q = p->left;
		if (q->balans <= 0)
		{
			OR(p);
			if (q->balans == 0)
			{
				p->balans = -1;
				q->balans = 1;
				h = false;
				p = q;
				return p;
			}
			else
			{
				p->balans = 0;
				q->balans = 0;
			}
			p = q;
		}
		else
			if (p->right)
			{
				AVL_Node *s = p->right;
				LR(p);
				if (s->balans == -1)
					p->balans = 1;
				else
					p->balans = 0;
				if (s->balans = 1)
					q->balans = -1;
				else
					q->balans = 0;
				p = s;
				s->balans = 0;
			}
			else 
			{
				AVL_Node *s = p->left->right;
				LR(p);
				if (s->balans == -1)
					p->balans = 1;
				else
					p->balans = 0;
				if (s->balans == 1)
					q->balans = -1;
				else
					q->balans = 0;
				p = s;
				s->balans = 0;

			}
		h = false;
		return p;
	}
}

AVL_Node* AVL_Node::make_balance_for_right(AVL_Node* p, bool &h)
{
	if (p->balans == -1)//вернулись из правого поддерева
	{
		p->balans = 0;
		h = false;
		return p;
	}
	if (p->balans == 0)
	{
		p->balans = 1;
		return p;
	}
	if (p->balans == 1)
	{
		p->balans = 2;
		AVL_Node *s = p->right;
		if (s->balans == 1)
		{
			OL(p);
			p->balans = 0;
			s->balans = 0;
			p = s;
		}
		else
		{
			if (s->balans == -1)
			{
				AVL_Node *r = s->left;
				RL(p);
				if (r->balans == 1)
				{
					p->balans = -1;
					s->balans = 0;
				}
				if (r->balans == -1)
				{
					p->balans = 0;
					s->balans = 1;
				}
				if (r->balans == 0)
				{
					p->balans = 0;
					s->balans = 0;
				}
				r->balans = 0;
				p = r;
			}
		}
			h = false;
			return p;
	}
}

AVL_Node* AVL_Node::make_balance_for_left(AVL_Node* p, bool &h) // балансировка узла p
{
	if (p->balans == 1) // вернулись из левого поддерева
	{
		p->balans = 0;
		h = false;
		return p;
	}
	if (p->balans == 0)
	{
		p->balans = -1;
		return p;
	}
	if (p->balans == -1)
	{
		p->balans = -2;
		AVL_Node *s = p->left;
		if (s->balans == -1)
		{
			OR(p);
			p->balans = 0;
			s->balans = 0;
			p = s;
		}
		else
		{
			if (s->balans == 1)
			{
				AVL_Node *r = s->right;
				LR(p);
				if (r->balans == -1)
				{
					p->balans = 1;
					s->balans = 0;
				}
				if (r->balans == 1)
				{
					p->balans = 0;
					s->balans = -1;
				}
				if (r->balans == 0)
				{
					p->balans = 0;
					s->balans = 0;
				}
				r->balans = 0;
				p = r;
			}
		}
			h = false;
			return p;
	}
}

AVL_Node* AVL_Node::find_Min(AVL_Node* p) // поиск узла с минимальным ключом в дереве p
{
	if (p->left == NULL)
		return p;
	AVL_Node* Min = p;
	Min = find_Min(p->left);
	return Min;
}

AVL_Node* AVL_Node::Find_k(AVL_Node*p, int key)// поиск узла с ключем к в дереве р
{
	if (p == NULL || key == p->key) return p;

	AVL_Node *q;
	if (key < p->key)  return q = Find_k(p->left, key);
	else return q = Find_k(p->right, key);

}

/* AVL_Node* AVL_Node::Del_Min(AVL_Node* p,bool &h) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = Del_Min(p->left,h);
	return make_balance_for_left(p->left,h = true);
}
*/

AVL_Node* AVL_Node::Add(AVL_Node* p, int k, bool &h) // вставка ключа k в дерево с корнем p
{
	if (p == NULL) return new AVL_Node(k);
	if (p->key == k)
	{
		h = false;
		return p;
	}
	if (k < p->key)
	{
		p->left = Add(p->left, k, h);
		if(h) p = make_balance_for_left(p, h);
	}
	else
	{
		p->right = Add(p->right, k, h);
		if(h) p = make_balance_for_right(p, h);
	}
	return p;
}

AVL_Node* AVL_Node::Del(AVL_Node* p, int k, bool &h) // удаление ключа k из дерева p
{
	if (p == NULL)
	{
		h = false;
		return p;
	}
		
	if (k < p->key)
	{
		p->left = Del(p->left, k, h);
		if (h) p = left_balance_for_del(p,h);
	}
	else if (k > p->key)
	{
		p->right = Del(p->right, k, h);
		if (h) p = right_balance_for_del(p,h);
	}
	else if (p->left != NULL && p->right != NULL)
	{
		AVL_Node *min = find_Min(p->right);
		if (min)
		{
			int min_key = min->key;
			p->key = min_key;
			p->right = Del(p->right, min->key, h);
			if (h) p = right_balance_for_del(p, h);
		}
		else
		{
			assert(!"gfgf");
			p->key = p->right->key;
			p->right = p->right->right;
			if (h) p = right_balance_for_del(p, h);
		}
	}
		//if (h) p = right_balance_for_del(p,h);
	else
		if (p->left != NULL)
			p = p->left;
		else
			p = p->right;

		return p;
}


void AVL_Node::print_levels(AVL_Node *root)// вывод по уровням
{
	deque <AVL_Node*> q;
	q.push_back(root);
	q.push_back(NULL);
	while (!q.empty())
	{
		AVL_Node* u = q.front();
		q.pop_front();
		if (u == NULL)
		{
			puts("");
			if (!q.empty())
				q.push_back(NULL);
		}
		else
		{
			printf("%d ", u->key);
			if (u->left)
			{
				printf("left for %d: ", u->key);
				q.push_back(u->left);
			}
			if (u->right)
			{
				printf("right for %d : ", u->key);
				q.push_back(u->right);
			}
		}
	}
}

void AVL_Node::beautiful_print_Node(AVL_Node *p, int k)
{
	if (p == NULL) return;

	beautiful_print_Node(p->right, k + 5);

	for (int i = 0; i < k; i++) cout << ' ';

	cout<< p->key << endl;

	beautiful_print_Node(p->left, k + 5);
	//cout << endl << endl;
}

int	AVL_Node::get_key()
{
	if (this)
		return key;
	else
		return NULL;
}

AVL_Node::~AVL_Node()
{
}
