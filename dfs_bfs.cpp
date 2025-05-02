// BFS:
#include <iostream>
#include <queue>
#include <omp.h> // Include OpenMP for parallel processing

#include <vector>
#include <stack>


using namespace std;

class Node
{
public:
    int data;
    Node *left, *right;

    Node(int val)
    {
        data = val;
        left = right = nullptr;
    }
};

class BreadthFS
{
public:
    Node *insert(Node *, int);
    void bfs(Node *);
};

// Function to insert a node in a binary tree (level order insertion)
Node *BreadthFS::insert(Node *root, int data)
{
    if (!root)
    {
        return new Node(data);
    }

    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();

        if (temp->left == nullptr)
        {
            temp->left = new Node(data);
            return root;
        }
        else
        {
            q.push(temp->left);
        }

        if (temp->right == nullptr)
        {
            temp->right = new Node(data);
            return root;
        }
        else
        {
            q.push(temp->right);
        }
    }
    return root;
}

// Function to perform Breadth-First Search (BFS) traversal
void BreadthFS::bfs(Node *head)
{
    if (!head)
        return;

    queue<Node *> q;
    q.push(head);

    while (!q.empty())
    {
        int qSize = q.size();

#pragma omp parallel for // Parallel processing
        for (int i = 0; i < qSize; i++)
        {
            Node *currNode;

#pragma omp critical // Ensure thread-safe access
            {
                currNode = q.front();
                q.pop();
                cout << "\t" << currNode->data;
            }

#pragma omp critical // Thread-safe queue operations
            {
                if (currNode->left)
                    q.push(currNode->left);
                if (currNode->right)
                    q.push(currNode->right);
            }
        }
    }
}

int main()
{
    BreadthFS tree;
    Node *root = nullptr;
    int data;
    char ans;

    do
    {
        cout << "\nEnter data: ";
        cin >> data;
        root = tree.insert(root, data);

        cout << "Do you want to insert another node? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    cout << "\nBreadth-First Search (BFS) traversal:";
    tree.bfs(root);

    return 0;
}


// DFS:

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void dfs(int node)
{
    stack<int> s;
    s.push(node);

    while (!s.empty())
    {
        int curr_node = s.top();
        s.pop();

        if (!visited[curr_node])
        {
            visited[curr_node] = true;
            cout << curr_node << " ";

#pragma omp parallel for
            for (int i = 0; i < graph[curr_node].size(); i++)
            {
                int adj_node = graph[curr_node][i];
                if (!visited[adj_node])
                {
#pragma omp critical
                    s.push(adj_node);
                }
            }
        }
    }
}

int main()
{
    int n, m, start_node;
    cout << "Enter number of nodes, edges, and start node: ";
    cin >> n >> m >> start_node;

    cout << "Enter pairs of edges: \n";
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }

    cout << "Depth-First Search (DFS) traversal: ";
    dfs(start_node);

    return 0;
}

