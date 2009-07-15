/** \file roxml.c
 *  \brief source for libroxml.so
 *         
 * This is the source file for lib libroxml.so
 * \author blunderer <blunderer@blunderer.org>
 * \date 23 Dec 2008
 *
 * Copyright (C) 2009 blunderer
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef ROXML_C
#define ROXML_C

#include "roxml-internal.h"

static memory_cell_t head_cell = {PTR_NONE, 0, NULL, 0, NULL, NULL};

node_t * roxml_parent_node(node_t *parent, node_t *n)
{
	if(parent)	{
		n->fat = parent;
		if(parent->son == NULL)	{
			parent->son = n;
		} else	{
			node_t *brother = parent->son;
			while(brother->bra != NULL)	{
				brother = brother->bra;
			}
			brother->bra = n;
		}
	}

	return n;
}

node_t * roxml_new_node(int pos, FILE *file, char * buf, unsigned int * idx)
{
	node_t *n = (node_t*)malloc(sizeof(node_t));
	n->type = ((file)?FILE_FILE:FILE_BUFF);
	n->idx = idx;
	n->buf = buf;
	n->fil = file;
	n->pos = pos;
	n->end = pos;
	n->bra = NULL;
	n->son = NULL;
	n->fat = NULL;

	return n;
}

void roxml_close_node(node_t *n, node_t *close)
{
	n->end = close->pos;
	roxml_free_node(close);
}

void roxml_free_node(node_t *n)
{
	free(n);
}

void roxml_parse_node(node_t *n, char *name, char * arg, char * value, int * num, int max)
{
	char c = 0;
	int len = 0;
	int count = 0;
	int mode = MODE_COMMENT_NONE;
	int state = STATE_NODE_NAME;

	PUSH(n)

	while((!ROXML_FEOF(n))&&(c != '>')&&((max >= 0)?(count < max+1):(1)))      {
		c = ROXML_FGETC(n);
		if(c == '"')	{
			if(mode == MODE_COMMENT_NONE)	{
				mode = MODE_COMMENT_DQUOTE;
			} else if(mode == MODE_COMMENT_DQUOTE)	{
				mode = MODE_COMMENT_NONE;
			}
			continue;
		} else if(c == '\'')	{
			if(mode == MODE_COMMENT_NONE)	{
				mode = MODE_COMMENT_QUOTE;
			} else if(mode == MODE_COMMENT_QUOTE)	{
				mode = MODE_COMMENT_NONE;
			}
			continue;
		}
		
		if(mode == MODE_COMMENT_NONE)	{
			if((c == ' ')||(c == '\t'))	{
				if(state == STATE_NODE_NAME)	{
					state = STATE_NODE_ARG;
					len = 0;
				} else if(state == STATE_NODE_ARG)	{
					if(len > 0)	{
						len = 0;
						count++;
					}
				} else if(state == STATE_NODE_ARGVAL)     {
					if(len > 0)	{
						state = STATE_NODE_ARG;
						len = 0;
						count++;
					}
				}
			} else if(c == '=')	{
				if(state == STATE_NODE_ARG)	{
					state = STATE_NODE_ARGVAL;
					len = 0;
				}
			} else if(c == '/')	{
				;
			} else if(c == '>')	{
				if(state == STATE_NODE_ARG)	{
					if(len > 0)	{
						count++;
					}
				} else if(state == STATE_NODE_ARGVAL)	{
					if(len > 0)	{
						count++;
					}
				}
			} else if(state == STATE_NODE_NAME)    {
				if(name)	{
					name[len] = c;
					name[len+1] = '\0';
				}
				len++;
			} else if(state == STATE_NODE_ARG)    {
				if(arg)	{
					arg[len] = c;
					arg[len+1] = '\0';
				}
				len++;
			} else if(state == STATE_NODE_ARGVAL)    {
				if(value)	{
					value[len] = c;
					value[len+1] = '\0';
				}
				len++;
			}
		} else	{
			if(state == STATE_NODE_ARG)	{
				if(arg)	{
					arg[len] = c;
					arg[len+1] = '\0';
				}
				len++;
			} else if(state == STATE_NODE_ARGVAL)	{
				if(value)	{
					value[len] = c;
					value[len+1] = '\0';
				}
				len++;
			}
		}
	}

	if(num)	{
		*num = count;
	}

	POP(n)
}

char * roxml_get_content(node_t *n)
{
	int num;
	int nbs;
	char * content = NULL;
	int len = 0, total = 0;
	char *content_ptr = NULL;
	long long int start = 0, end = 0;	

	nbs = roxml_get_son_nb(n);

	PUSH(n)

	for(num = 0; num < nbs+1; num++)	{
		char c = 0;
		node_t *son = roxml_get_son_nth(n, num);
		if(son)	{
			end = son->pos;
		} else	{
			end = n->end;
		}

		while((!ROXML_FEOF(n))&&(c != '>'))      {
			c = ROXML_FGETC(n);
		}
		if(c == '>')	{
			start = ROXML_FTELL(n);
			len = end - start - 1;
			if(len > 0)	{
				total += len;
			} else	{
				len = 0;
			}
		} else {
			return NULL;
		}
		if(son)	{
			ROXML_FSEEK(son, son->end);
		}
	}
	
	POP(n)
	content = roxml_malloc(sizeof(char), total+1, PTR_CHAR);
	if(content == NULL) { return NULL; }
	memset(content, 0, sizeof(char) * (total+1));
	content_ptr = content;
	len = 0;
	total = 0;
	start = 0;
	end = 0;	
	PUSH(n)

	for(num = 0; num < nbs+1; num++)	{
		char c = 0;
		node_t *son = roxml_get_son_nth(n, num);
		if(son)	{
			end = son->pos;
		} else	{
			end = n->end;
		}

		while((!ROXML_FEOF(n))&&(c != '>'))      {
			c = ROXML_FGETC(n);
		}
		if(c == '>')	{
			start = ROXML_FTELL(n);
			len = end - start - 1;
			if(len > 0)	{
				ROXML_FREAD(content_ptr, len, sizeof(char), n);
				content_ptr += len;
			} else	{
				len = 0;
			}
		} else {
			return NULL;
		}
		if(son)	{
			ROXML_FSEEK(son, son->end);
		}
	}

	POP(n)
	return content;
}

char * roxml_get_raw_content(node_t *n)
{
	char c = 0;
	int len = 0;
	char * content = NULL;
	long long int start = 0;	

	PUSH(n)
	
	while((!ROXML_FEOF(n))&&(c != '>'))      {
		c = ROXML_FGETC(n);
	}

	if(c == '>')	{
		start = ROXML_FTELL(n);
		len = n->end - start - 1;
		if(len < 0)	{
			len = 0;
		}
	}

	POP(n)
	c = 0;
	len = 0;
	start = 0;	
	content = roxml_malloc(sizeof(char), len+1, PTR_CHAR);
	if(content == NULL) { return NULL; }
	memset(content, 0, sizeof(char) * (len+1));
	PUSH(n)

	while((!ROXML_FEOF(n))&&(c != '>'))      {
		c = ROXML_FGETC(n);
	}

	if(c == '>')	{
		start = ROXML_FTELL(n);
		len = n->end - start - 1;
		if(len > 0)	{
			ROXML_FREAD(content, len, sizeof(char), n);
		}
	}

	POP(n)
	return content;
}

char * roxml_get_name(node_t *n)
{
	char * name = (char*)roxml_malloc(sizeof(char), 512, PTR_CHAR);
	memset(name, 0, sizeof(char)*512);

	if(n->fat == NULL)	{
		strcpy(name,"root");
	} else	{
		roxml_parse_node(n, name, NULL, NULL, NULL, 1);
	}
	return name;
}

int ROXML_API roxml_get_attr_nb(node_t *n)
{
	int count;
	roxml_parse_node(n, NULL, NULL, NULL, &count, -1);
	return count;
}

char *roxml_get_attr_val_nth(node_t *n, int nb)
{
	char * val = (char*)roxml_malloc(sizeof(char), 512, PTR_CHAR);
	memset(val, 0, sizeof(char)*512);
	
	roxml_parse_node(n, NULL, NULL, val, NULL, nb);

	return val;
}

char *roxml_get_attr_nth(node_t *n, int nb)
{
	char * arg = (char*)roxml_malloc(sizeof(char), 512, PTR_CHAR);
	memset(arg, 0, sizeof(char)*512);
	
	roxml_parse_node(n, NULL, arg, NULL, NULL, nb);

	return arg;
}

void roxml_close(node_t *n)
{
	node_t *root = n;
	if(root == NULL)	{
		return;
	}
	while(root->fat != NULL)	{
		root = root->fat;
	}
	roxml_del_tree(root->son);
	roxml_del_tree(root->bra);
	if(root->type == FILE_FILE)	{
		fclose(root->fil);
	} else if(root->type == FILE_BUFF)	{
		free(root->idx);
	} else if(root->type == FILE_ARG)	{
		free(root->buf);
		free(root->idx);
	}
	free(root);
	roxml_release(RELEASE_ALL);
}

void roxml_del_tree(node_t *n)
{
	if(n == NULL)	{
		return;
	}
	roxml_del_tree(n->son);
	roxml_del_tree(n->bra);
	free(n);
	return;
}

int roxml_get_son_nb(node_t *n)
{
	node_t *ptr = n;
	int nb = 0;
	if(ptr->son)	{
		ptr = ptr->son;
		nb++;
		while(ptr->bra)	{
			nb++;
			ptr = ptr->bra;
		}
	}
	return nb;
}

node_t *roxml_get_son_nth(node_t *n, int nb)
{
	int count = 0;
	node_t *ptr = n;
	if(nb == 0)	{
		return n->son;
	}
	ptr = n->son;
	while((ptr->bra)&&(nb > count)) {
		count++;
		ptr = ptr->bra;
	}
	if(nb > count)	{ return NULL; }
	return ptr;
}

node_t *roxml_get_parent(node_t *n)
{
	if(n->fat == NULL)	{
		return n;
	} else	{
		return n->fat;
	}
	return NULL;
}

node_t * roxml_load_doc(char *filename)
{
	node_t *current_node = NULL;
	FILE* file = fopen(filename, "r");
	if(file == NULL)	{
		return NULL;
	}
	current_node = roxml_new_node(0, file, NULL, NULL);
	current_node = roxml_parent_node(NULL, current_node);
	return roxml_load(current_node,  file, NULL);
}

node_t * roxml_load_buf(char *buffer)
{
	unsigned int *index = (unsigned int *)malloc(sizeof(unsigned int));
	node_t *current_node = NULL;
	*index = 0;
	current_node = roxml_new_node(0, NULL, buffer, index);
	current_node = roxml_parent_node(NULL, current_node);
	return roxml_load(current_node, NULL, buffer);
}

node_t * roxml_load(node_t *current_node, FILE *file, char *buffer)
{
	int state = STATE_NODE_NONE;
	int mode = MODE_COMMENT_NONE;
	node_t *candidat_node = NULL;

	while(!ROXML_FEOF(current_node))	{
		char c = ROXML_FGETC(current_node);

		if(state != STATE_NODE_CONTENT)	{
			if(c == '"')	{
				if(mode == MODE_COMMENT_NONE)	{
					mode = MODE_COMMENT_DQUOTE;
				} else if(mode == MODE_COMMENT_DQUOTE)	{
					mode = MODE_COMMENT_NONE;
				}
			} else if(c == '\'')	{
				if(mode == MODE_COMMENT_NONE)	{
					mode = MODE_COMMENT_QUOTE;
				} else if(mode == MODE_COMMENT_QUOTE)	{
					mode = MODE_COMMENT_NONE;
				}
			}
		}
		
		if(mode == MODE_COMMENT_NONE)	{
			if(c == '<')	{
				state = STATE_NODE_BEG;
				candidat_node = roxml_new_node(ROXML_FTELL(current_node), file, buffer, current_node->idx);
			} else if(c == '>')	{
				if(state == STATE_NODE_NAME)	{
					state = STATE_NODE_CONTENT;
					current_node = roxml_parent_node(current_node, candidat_node);
				} else if(state == STATE_NODE_ATTR)	{
					state = STATE_NODE_CONTENT;
					current_node = roxml_parent_node(current_node, candidat_node);
				} else if(state == STATE_NODE_SINGLE)	{
					current_node = roxml_parent_node(current_node, candidat_node);
					current_node = current_node->fat;
				} else if(state == STATE_NODE_END)	{
					roxml_close_node(current_node, candidat_node);
					current_node = current_node->fat;
				}
			} else if(c == '/')	{
				if(state == STATE_NODE_BEG)	{
					state = STATE_NODE_END;
				} else if(state == STATE_NODE_NAME)	{
					state = STATE_NODE_SINGLE;
				} else if(state == STATE_NODE_ATTR)	{
					state = STATE_NODE_SINGLE;
				}
			} else if((c == ' ')||(c == '\t'))	{
				if(state == STATE_NODE_NAME)	state = STATE_NODE_ATTR;
			} else	{
				if(state == STATE_NODE_BEG)	state = STATE_NODE_NAME;
			}
		}
	}
	while(current_node->fat)	{ current_node = current_node->fat; }
	return current_node;
}

node_t ** roxml_exec_path(node_t *n, char * path, int *nb_ans)
{
	int index = 0;
	int nb_ans_internal = 0;
	node_t *starting_node = n;
	node_t **resulting_nodes = NULL;
	char * path_to_find;
	if((path[0] == '/')&&(path[1] != '/'))	{
		char *name = NULL;
		path_to_find = strdup(path+1);
		while(starting_node->fat)	{
			starting_node = starting_node->fat;
		}
		name = roxml_get_name(roxml_get_son_nth(starting_node, 0));
		if(strcmp(name, "?xml") == 0)	{
			starting_node = roxml_get_son_nth(starting_node, 0);
		}
		roxml_release(name);
		name = roxml_get_name(starting_node);
		roxml_release(name);
	} else	{
		path_to_find = strdup(path);
	}

	/* two pass algorithm : first: how many node match */
	if(strcmp(path, "/") == 0)	{
		nb_ans_internal = 1;
	} else	{
		roxml_resolv_path(starting_node, path_to_find, &nb_ans_internal, NULL);
	}

	if(nb_ans) { *nb_ans = nb_ans_internal; }
	if(nb_ans_internal == 0)	{
		return NULL;
	}

	/* two pass algorithm : then: copy them */
	index = 0;
	resulting_nodes = (node_t**)roxml_malloc(sizeof(node_t*), nb_ans_internal, PTR_NODE_RESULT);
	if(strcmp(path, "/") == 0)	{
		resulting_nodes[0] = starting_node;
	} else	{
		roxml_resolv_path(starting_node, path_to_find, &index, &resulting_nodes);
	}

	return resulting_nodes;
}

void roxml_resolv_path(node_t *n, char * path, int *idx, node_t ***res)
{
	int i;
	int nb_son = 0;
	if(strlen(path) == 0)	{ return; }
	if(n == NULL)	{ return; }

	/* relative path special nodes */
	if(strncmp(path, "..", strlen("..")) == 0)	{
		char * new_path = path+strlen("..");
		if((strlen(new_path) > 0) && (strcmp(new_path,"/") != 0))	{
			roxml_resolv_path(n->fat, new_path+1, idx, res);
		} else	{
			if(res)	{ (*res)[*idx] = n->fat; }
			(*idx)++;
		}
	}

	/* read only attribute */
	if(strncmp(path, "@", strlen("@")) == 0)	{
		int i;
		int nb_attr = roxml_get_attr_nb(n);
		char * new_path = path+strlen("@");
		for(i = 0; i < nb_attr; i++)	{
			char *name = roxml_get_attr_nth(n, i);
			if(strcmp(new_path, name) == 0)	{
				if(res)	{ 
					char *value = roxml_get_attr_val_nth(n, i);
					node_t *arg = roxml_new_arg_node(name, value);
					(*res)[*idx] = arg; 
					roxml_release(value);
				}
				(*idx)++;
			}
			roxml_release(name);
		}
	}
	

	nb_son = roxml_get_son_nb(n);
	for(i = 0; i < nb_son; i++)	{
		node_t *cur = roxml_get_son_nth(n, i);
		char *name = roxml_get_name(cur);

		if(strncmp(name, path, strlen(name)) == 0)	{
			char * new_path = path+strlen(name);
			if(new_path[0] == '[')	{
				/* conditionnal xpath */
				if(roxml_xpath_conditionnal(cur, new_path))	{
					new_path = strstr(new_path, "]");
					if(new_path)	{
						new_path++;
						if((strlen(new_path) > 0) && (strcmp(new_path,"/") != 0))	{
							roxml_resolv_path(cur, new_path+1, idx, res);
						} else	{
							if(res)	{ (*res)[*idx] = cur; }
							(*idx)++;
						}
					}
				}
			} else	{
				if((strlen(new_path) > 0) && (strcmp(new_path,"/") != 0))	{
					roxml_resolv_path(cur, new_path+1, idx, res);
				} else	{
					if(res)	{ (*res)[*idx] = cur; }
					(*idx)++;
				}
			}
		} else /*if((path[0] == '/') && (path[1] == '/'))*/	{
			printf("%s\n",path+0);
			roxml_resolv_path(cur, path+0, idx, res);
		}
		roxml_release(name);
	}
}

node_t* roxml_new_arg_node(char * name, char * value)
{
	int size, close;
	node_t *node;
	
	size = 2*strlen(name) + strlen(value) + 6;
	close = strlen(name) + strlen(value) + 3;
	node = (node_t*)roxml_malloc(sizeof(node_t), 1, PTR_NODE);
	node->buf = (char*)roxml_malloc(sizeof(char), size, PTR_CHAR);
	node->idx = (unsigned int*)roxml_malloc(sizeof(unsigned int), 1, PTR_INT);
	sprintf(node->buf,"<%s>%s</%s>",name,value,name);
	node->type = FILE_ARG;
	node->son = NULL;
	node->bra = NULL;
	node->fat = NULL;
	node->fil = NULL;
	*node->idx = 0;
	node->pos = 0;
	node->end = close;
	node->prv = 0;

	return node;
}

int roxml_is_arg(node_t *n)
{
	if(n->type == FILE_ARG)	{
		return 1;
	}
	return 0;
}

int roxml_get_node_index(node_t *n, int * last)
{
	int i = 0, idx = 0;
	int nb_bra = 0, nb_same_bra = 0;
	char * realn = roxml_get_name(n);

	nb_bra = roxml_get_son_nb(n->fat);
	for(i = 0; i < nb_bra; i++)	{
		node_t *tmp = roxml_get_son_nth(n->fat, i);
		char * name = roxml_get_name(tmp);
		if(tmp == n)	{ idx = nb_same_bra; }
		if(strcmp(name, realn) == 0)	{ nb_same_bra++; }
		roxml_release(name);
	}
	roxml_release(realn);		

	if(last) { *last = nb_same_bra-1; }

	if(nb_same_bra > 1)	{ return idx; }
	return -1;
}

int roxml_xpath_conditionnal(node_t *n, char *condition)
{
	char *cond = condition+1;
	while((*cond == ' ')||(*cond == '\t'))	{ cond++; }
	if(cond[0] == '@')	{
		/* condition on attribut */
		int i;
		int nb_attr = roxml_get_attr_nb(n);
		if(nb_attr == 0) { return 0; }
		for(i = 0; i < nb_attr; i++)	{
			char *name = roxml_get_attr_nth(n, i);
			if(strncmp(name, cond+1, strlen(name)) == 0)	{
				char *value = roxml_get_attr_val_nth(n, i);
				char *request = strstr(cond+1, "=");
				char *end = strstr(cond+1, "]");
				if((request) && (request<end))	{
					request++;
					if(strncmp(value, request, strlen(value)) == 0)	{
						roxml_release(name);
						roxml_release(value);
						return 1;
					}
				} else {
					roxml_release(value);
					roxml_release(name);
					return 1;
				}
				roxml_release(value);
			}
			roxml_release(name);
		}
		return 0;
	} else if((cond[0] >= 0x30)&&(cond[0] <= 0x39))	{
		/* condition on table id */
		int ask = atoi(cond);
		int idx = roxml_get_node_index(n, NULL);
		if(ask == idx)	{ return 1; }
		return 0;
	} else if(strncmp(cond, "last()", strlen("last()")) == 0)	{
		char *ptr = cond+strlen("last()");
		int last = 0;
		int offset = atoi(ptr);
		int idx = roxml_get_node_index(n, &last);
		if(idx == last+offset) { return 1; }
		return 0;
	} else if(strncmp(cond, "first()", strlen("first()")) == 0)	{
		char *ptr = cond+strlen("first()");
		int idx = roxml_get_node_index(n, NULL);
		int offset = atoi(ptr);
		if(idx == offset) { return 1; }
		return 0;
	} else if(strncmp(cond, "position()", strlen("position()")) == 0)	{
		/* select operator between: < > = != <= >= */
		char *op = NULL;
		char *ptr = cond+strlen("position()");
		int idx = roxml_get_node_index(n, NULL);
		if((op = strstr(ptr, "!=")))	{
			int val = atoi(op+strlen("!="));
			if(idx != val)	{ return 1; }
		} else if((op = strstr(ptr, ">=")))	{
			int val = atoi(op+strlen(">="));
			if(idx >= val)	{ return 1; }
		} else if((op = strstr(ptr, "<=")))	{
			int val = atoi(op+strlen("<="));
			if(idx <= val)	{ return 1; }
		} else if((op = strstr(ptr, "=")))	{
			int val = atoi(op+strlen("="));
			if(idx == val)	{ return 1; }
		} else if((op = strstr(ptr, "<")))	{
			int val = atoi(op+strlen("<"));
			if(idx < val)	{ return 1; }
		} else if((op = strstr(ptr, ">")))	{
			int val = atoi(op+strlen(">"));
			if(idx > val)	{ return 1; }
		}
		return 0;
	} else if(strncmp(cond, "position()", strlen("position()")) == 0)	{
		/* other not yet handled */
		return 0;
	}
	return 0;
}

void * roxml_malloc(int size, int num, int type)
{
	memory_cell_t *cell = &head_cell;
	while(cell->next != NULL) { cell = cell->next; }
	cell->next = (memory_cell_t*)malloc(sizeof(memory_cell_t));
	if(!cell->next) { return NULL; }
	cell->next->next = NULL;
	cell->next->prev = cell;
	cell = cell->next;
	cell->type = type;
	cell->id = pthread_self();
	cell->occ = size;
	cell->ptr = malloc(size*num);
	head_cell.prev = cell;
	return cell->ptr;
}

void roxml_release(void * data)
{
	memory_cell_t *ptr = &head_cell;
	memory_cell_t *to_delete = NULL;

	if(data == RELEASE_LAST)	{
		while((ptr->prev != NULL)&&(ptr->prev->id != pthread_self())) { ptr = ptr->prev; } 
		if(ptr->prev == NULL)	{ return; }

		to_delete = ptr->prev;
		if(to_delete->next) { 
			to_delete->prev->next = to_delete->next;
			to_delete->next->prev = to_delete->prev;
		} else {
			if(to_delete->prev != &head_cell)	{
				head_cell.prev = to_delete->prev;
			} else {
				head_cell.prev = NULL;
			}
			to_delete->prev->next = NULL;
		}

		if(PTR_IS_STAR(to_delete))	{
			int i = 0;
			for(i = 0; i < to_delete->occ; i++) { free(((void**)(to_delete->ptr))[i]); }
		}
		if(to_delete->type != PTR_NONE)	{
			free(to_delete->ptr);
			to_delete->type = PTR_NONE;
			free(to_delete);
		}
	} else if(data == RELEASE_ALL) {
		while((ptr != NULL) && (ptr->next != NULL)) { 
			to_delete = ptr->next;
			if(to_delete->next) { to_delete->next->prev = ptr; }
			ptr->next = to_delete->next;
			if(PTR_IS_STAR(to_delete))	{
				int i = 0;
				for(i = 0; i < to_delete->occ; i++) { free(((void**)(to_delete->ptr))[i]); }
			}
			free(to_delete->ptr);
			to_delete->type = PTR_NONE;
			free(to_delete);
			ptr = ptr->next;
		}
	} else	{
		while((ptr->next != NULL)&&(ptr->next->ptr != data)) { ptr = ptr->next; }
		if(ptr->next == NULL)	{ 
			free(data);
			return;
		}

		to_delete = ptr->next;
		if(to_delete->next) {
			to_delete->next->prev = ptr; 
		} else {
			if(ptr == &head_cell)	{
				head_cell.prev = NULL;
			} else {
				head_cell.prev = to_delete->prev;
			}
		}
		ptr->next = to_delete->next;
		if(PTR_IS_STAR(to_delete))	{
			int i = 0;
			for(i = 0; i < to_delete->occ; i++) { free(((void**)(to_delete->ptr))[i]); }
		}
		free(to_delete->ptr);
		to_delete->type = PTR_NONE;
		free(to_delete);
	}
}

void roxml_write_node(node_t * n, FILE *f)
{
	char *name = roxml_get_name(n);
	int nb = roxml_get_son_nb(n);
	if(nb > 0)	{
		int i = 0;
		fprintf(f, "<%s>", name);
		for(i = 0; i < nb; i++)	{
			roxml_write_node(roxml_get_son_nth(n, i), f);
		}
		fprintf(f, "</%s>", name);
	} else {
		fprintf(f, "<%s/>", name);
	}
	roxml_release(name);
}

void roxml_commit_changes(node_t *n)
{
	FILE *fout = fopen("/tmp/out.xml", "w");
	if(fout)	{
		roxml_write_node(n, fout);
		fclose(fout);	
	}
}


#endif /* ROXML_C */

