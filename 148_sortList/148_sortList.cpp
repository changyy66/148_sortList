// 148_sortList.cpp : 定义控制台应用程序的入口点。
//
/*
在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。

示例 1:

输入: 4->2->1->3
输出: 1->2->3->4
示例 2:

输入: -1->5->3->4->0
输出: -1->0->3->4->5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

/**
* Definition for singly-linked list.
*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode *sort(ListNode* head1, ListNode*head2)
	{
		ListNode newhead = ListNode(0), *tmp;
		tmp = &newhead;
		while (head1&&head2)
		{
			if (head1->val > head2->val)
			{
				tmp->next = head2;
				tmp = head2;
				head2 = head2->next;
			}
			else
			{
				tmp->next = head1;
				tmp = head1;
				head1 = head1->next;
			}
		}
		if (head1)
		{
			tmp->next = head1;
		}
		if (head2)
		{
			tmp->next = head2;
		}
		return newhead.next;
		//delete newhead;
		//return tmp;
	}

	ListNode *cut(ListNode *head, int len) {
		ListNode *tmp = head;
		len--;
		while (len&&tmp)
		{
			tmp = tmp->next;
			len--;
		}
		if (tmp)
		{
			ListNode *newhead = tmp->next;
			tmp->next = NULL;
			return newhead;
		}
		return NULL;

	}

	ListNode* sortList(ListNode* head) {
		ListNode *tmp = head;
		ListNode newHead = ListNode(0), *newTail, *newTmp;;
		newTail = &newHead;
		newTmp = &newHead;
		newHead.next = head;
		int len = 0;
		while (tmp)
		{
			len++;
			tmp = tmp->next;
		}
		tmp = head;
		int offset = 1;
		while (offset < len)
		{
			for (int i = 0; i < len; i += offset * 2)
			{
				ListNode *tmp1 = tmp;
				ListNode *tmp2 = cut(tmp1, offset);
				tmp = cut(tmp2, offset);
				newTmp->next = sort(tmp1, tmp2);
				while (newTmp->next)
				{
					newTmp = newTmp->next;
				}
			}
			offset *= 2;
			tmp = newHead.next;
			newTmp = &newHead;
		}
		return newHead.next;
		//newTmp = newHead.next;
		//return newTmp;
	}
};
ListNode *construct(vector<int>& v)
{
	if (v.size()==0)
	{
		return NULL;
	}
	ListNode *head = new ListNode(v[0]);
	ListNode *tmp = head;
	for (int i = 1; i < v.size(); i++)
	{
		tmp->next = new ListNode(v[i]);
		tmp = tmp->next;
	}
	return head;
}

void print(ListNode *head)
{
	while (head)
	{
		cout << head->val << "->";
		head = head->next;
	}
	cout << endl;
}

int main()
{
	vector<int> v = { 6,4,3,5,7,2,8,1,9 };
	ListNode *head = construct(v);

	vector<int> v1 = { 0,2,3 };
	vector<int> v2 = { 1,4,5 };
	ListNode *head1 = construct(v1);
	ListNode *head2 = construct(v2);

	Solution s;
	print(s.sort(head1, head2));

	print(s.sortList(head));
    return 0;
}

