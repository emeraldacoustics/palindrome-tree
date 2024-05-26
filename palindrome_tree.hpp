#include <vector>

using namespace std;

template <class T>
class PalindromeTree
{
public:
	static const int sigma = 26;
	static const int eroot = 0;
	static const int oroot = 1;

	class Node
	{
	public:
		int len;
		int slnk;
		int son[sigma];

		Node(void) : len(0), slnk(0)
		{
			memset(son, 0, sizeof son[0] * sigma);
		}
	};

	int sz, cur;
	vector<T> s;
	vector<Node> nodes;

	int idx(const T & c)
	{
		return c - 'a';
	}

	PalindromeTree(void)
	{
		clear();
	}

	Node & operator [] (const int & x)
	{
		return nodes[x];
	}

	void clear(void)
	{
		sz = cur = 0;
		nodes.clear();
		add_node();
		nodes[eroot].len = 0;
		nodes[eroot].slnk = oroot;
		add_node();
		nodes[oroot].len = -1;
		nodes[oroot].slnk = oroot;
	}

	int add_node(void)
	{
		nodes.push_back(Node());
		return sz++;
	}

	bool is_equal(const int & u, const int & p)
	{
		return p >= nodes[u].len + 1 && s[p - nodes[u].len - 1] == s[p];
	}

	void extend(const int & p)
	{
		int & u = cur;
		for (; !is_equal(u, p); u = nodes[u].slnk);
		const int c = idx(s[p]);
		if (!nodes[u].son[c])
		{
			int v = add_node();
			nodes[v].len = nodes[u].len + 2;
			nodes[u].son[c] = v;
			if (nodes[v].len == 1)
				nodes[v].slnk = eroot;
			else
			{
				int r = nodes[u].slnk;
				for (; !is_equal(r, p); r = nodes[r].slnk);
				nodes[v].slnk = nodes[r].son[c];
			}
		}
		u = nodes[u].son[c];
	}

	void build(const T * first, const T * last)
	{
		const T * & s = first;
		const int n = strlen(s);

		this->s.resize(n);
		for (int i = 0; i < n; i++)
			this->s[i] = s[i];
		clear();
		for (int i = 0; i < n; i++)
			extend(i);
	}

	vector<int> sorted_indices(void)
	{
		int mxlen = 0;
		for (int u = 0; u < sz; u++)
			mxlen = max(mxlen, nodes[u].len);
		vector<int> occ(mxlen + 2);
		for (int u = 0; u < sz; u++)
			occ[nodes[u].len + 1]++;
		for (int i = 1; i <= mxlen + 1; i++)
			occ[i] += occ[i - 1];
		vector<int> ans(sz);
		for (int u = 0; u < sz; u++)
			ans[--occ[nodes[u].len + 1]] = u;
		return ans;
	}

	vector<int> sorted_indices(const vector<int> & qry)
	{
		int mxlen = 0;
		for (const auto & u : qry)
			mxlen = max(mxlen, nodes[u].len);
		vector<int> occ(mxlen + 2);
		for (const auto & u : qry)
			occ[nodes[u].len + 1]++;
		for (int i = 1; i <= mxlen + 1; i++)
			occ[i] += occ[i - 1];
		vector<int> ans(qry.size());
		for (const auto & u : qry)
			ans[--occ[nodes[u].len + 1]] = u;
		return ans;
	}
};

