#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define lld long long
#define lld long long
#define p(x) cout << x << "\n";
#define p2(x, y) cout << x << " " << y << "\n";
#define p3(x, y, z) cout << x << " " << y << " " << z << "\n";
#define ps(x) cout << x << " ";
#define ps2(x, y) cout << x << " " << y << " ";
#define ps3(x, y, z) cout << x << " " << y << " " << z << " ";
#define ps4(x, y, z, a) cout << x << " " << y << " " << z << " " << a << " ";
#define ps5(x, y, z, a, b) cout << x << " " << y << " " << z << " " << a << " " << b << " ";
#define pns(x) cout << x;
#define endl "\n"
#define all(x) x.begin(), x.end()
#define dll(x) x.begin(), x.end(), greater<lld>()
#define vect(x, n) vector<lld> x(n, 0);
#define matrix(x, n, m) vector<vector<lld>> x(n, vector<lld>(m, 0));
#define gcd(a, b) __gcd(a, b)
#define lcm(a, b) (a * b) / gcd(a, b)
#define lb lower_bound
#define ub upper_bound
#define pb(x) push_back(x);
#define pf(x) push_front(x);
#define mkp(x, y) make_pair(x, y)
#define same(a, b) a == b
#define inf 999999
void bellman(lld n, vector<vector<pair<lld, lld>>> adj, vector<lld> &distance, lld &negative_cycle_found)
{
    lld s = n + 1;
    //we run bellman ford from alpha=n+1;
    lld relax_edge_modification = 0;
    distance[s] = 0;
    //distance of source is 0
    vector<lld> times_pushed_in_queue(n + 2, 0);
    vector<lld> count(n + 2, 0);
    queue<lld> queue;
    queue.push(s);
    times_pushed_in_queue[s]++;
    lld previous_element = s;
    lld previous_relax_modification = 0;
    lld element, adjacent, dista;
    vector<pair<lld, lld>>::iterator i;
    for (lld times = 1; times <= n + 1; times++)
    {
        //we will run the loop n+1 times as there are n vertices and one alpha;
        previous_relax_modification = relax_edge_modification;
        while (queue.empty() == 0)
        {
            element = queue.front();
            if ((times_pushed_in_queue[element] - 1) / 2 > times)
            {
                //our next iteration must start so we break here;
                break;
            }
            queue.pop();
            times_pushed_in_queue[element]++;

            for (i = adj[element].begin(); i != adj[element].end(); i++)
            {
                adjacent = i->second;
                dista = i->first;
                if (distance[adjacent] > dista + distance[element])
                {
                    distance[adjacent] = dista + distance[element];
                    relax_edge_modification++;
                    count[adjacent] = count[element] + 1;
                    if (count[adjacent] > n - 1 + 1)
                    {
                        negative_cycle_found = 1;
                        p(-1);
                        return;
                    }
                    if (times_pushed_in_queue[adjacent] % 2 == 0)
                    {
                        queue.push(adjacent);
                        times_pushed_in_queue[adjacent]++;
                    }
                }
            }
            previous_element = element;
        }
        if (times == n + 1)
        {
            if (previous_relax_modification < relax_edge_modification)
            {
                //if in the n+1th iteration we get relax edge modification then there is a negative cycle so we return;
                p(-1);
                return;
            }
        }
    }
}
pair<lld, lld> begin(lld arr[], lld n)
{
    //returns the minimum element in the array;
    lld min = inf;
    pair<lld, lld> e = {inf, inf};
    for (lld i = 0; i <= n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
            e = {min, i};
        }
    }
    return e;
}
void erase(lld arr[], lld element)
{
    //we erase the element by making its value inf;
    arr[element] = inf;
}
void array_based_dijkstra(lld n, vector<vector<pair<lld, lld>>> adj, lld s, vector<lld> changed_distance)
{
    lld size = 0;
    //size maintains the number of non inf vertices in the array;
    lld arr[n + 2];
    lld size_of_arr = sizeof(arr) / sizeof(arr[0]);
    for (lld i = 0; i < size_of_arr; i++)
    {
        arr[i] = inf;
    }
    vector<lld> present(n + 2);
    arr[s] = 0;
    vector<lld> distance(n + 2, inf);
    distance[s] = 0;
    present[s] = 1;
    size++;
    vector<lld> shortest_path_fount(n + 2, 0);
    shortest_path_fount[s] = 1;
    pair<lld, lld> top_element;
    vector<pair<lld, lld>>::iterator i;
    while (size)
    {
        //if the size of the array is 0 we break;

        top_element = begin(arr, n);
        //top_element is the vertex having minimum value
        lld element = top_element.second;
        lld dist = top_element.first;
        erase(arr, element);
        //we now extract the minimum element
        present[element] = 0;
        size--;
        for (i = adj[element].begin(); i != adj[element].end(); i++)
        {
            lld adjacent = i->second;
            lld dista = i->first;
            if (shortest_path_fount[adjacent] == 0 && distance[element] != inf && distance[adjacent] > dista + distance[element])
            {
                if (present[adjacent] == 0)
                {
                    //if the adjacent is not present we insert it
                    present[adjacent] = 1;
                    size++;
                }
                distance[adjacent] = dista + distance[element];
                arr[adjacent] = distance[adjacent];
            }
        }
        //we have found the shortest path for the element so we wont insert it again
        shortest_path_fount[element] = 1;
    }
    for (lld i = 1; i < n + 1; i++)
    {
        if (same(i, s))
        {
            //if it is source we print 0
            ps(0);
        }
        else if (same(distance[i], inf))
        {
            // else if distance is inf we print inf
            ps(inf);
        }
        else
        {
            //else we correct the distance and print it
            lld corrected = distance[i] - changed_distance[s] + changed_distance[i];
            ps(corrected);
        }
    }
    p("");
}
void change(vector<vector<pair<lld, lld>>> &adj_changed, vector<lld> distance)
{
    //used to find delta after running bellman ford;
    for (lld i = 0; i < adj_changed.size(); i++)
    {
        for (lld j = 0; j < adj_changed[i].size(); j++)
        {
            if (adj_changed[i][j].first != inf)
                adj_changed[i][j].first += distance[i] - distance[adj_changed[i][j].second];
        }
    }
}
void minimum_heapify(vector<pair<lld, lld>> &v, lld n, lld i, vector<lld> &address)
{
    //heapify the vector;
    lld smallest = i;
    lld left = 2 * smallest + 1;
    lld right = 2 * smallest + 2;
    lld a = left < n;
    if (left < n && v[smallest] > v[left])
    {
        smallest = left;
    }
    lld b = right < n;
    if (right < n && v[smallest] > v[right])
    {
        smallest = right;
    }
    lld go = smallest != i;
    if (go)
    {
        //we swap the element if the parent is larger than any child
        swap(v[i], v[smallest]);
        //we also swap the address of them
        swap(address[v[i].second], address[v[smallest].second]);
        minimum_heapify(v, n, smallest, address);
    }
}
lld parent(lld i)
{
    //returns parent;
    return (i - 1) / 2;
}
void shift_up(vector<pair<lld, lld>> &v, lld n, lld i, vector<lld> &address)
{
    while (i > 0 && v[parent(i)] > v[i])
    {
        // Swap parent and current node
        swap(v[parent(i)], v[i]);
        swap(address[v[parent(i)].second], address[v[i].second]);
        // Update i to parent of i
        i = parent(i);
    }
}
pair<lld, lld> get_min(vector<pair<lld, lld>> v)
{
    //the minimum element in heap is v[0]
    return v[0];
}
void swaps(pair<lld, lld> &a, pair<lld, lld> &b)
{
    pair<lld, lld> e = a;
    a = b;
    b = e;
}
pair<lld, lld> extract_min(vector<pair<lld, lld>> &v, lld &size, vector<lld> &address)
{
    static pair<lld, lld> maxa = v[0];
    swaps(v[0], v[size - 1]);
    swap(address[v[0].second], address[v[size - 1].second]);
    v[size - 1].first = inf;
    size--;
    minimum_heapify(v, size, 0, address);
    return maxa;
}
void push_back(vector<pair<lld, lld>> &v, lld &size, pair<lld, lld> data, vector<lld> &address)
{
    address[data.second] = size;
    v[size++] = data;
    shift_up(v, size, size - 1, address);
}
void decrease_key(vector<pair<lld, lld>> &v, lld &size, lld n, pair<lld, lld> data, pair<lld, lld> new_data, vector<lld> &address)
{
    lld i = address[data.second];
    v[i] = new_data;
    shift_up(v, n, i, address);
}
lld empty(vector<pair<lld, lld>> v, lld n)
{
    if (v[0].first != inf)
    {
        return 0;
    }
    return 1;
}
void binary_heap_based_dijkstra(lld n, vector<vector<pair<lld, lld>>> adj, lld s, vector<lld> changed_distance)
{
    vector<pair<lld, lld>> v(n + 2);
    lld size = 0;
    lld size_of_arr = v.size();
    vector<lld> address(n + 2);
    for (lld i = 0; i < size_of_arr; i++)
    {
        if (i == s)
        {
            //if it is source we insert 0
            pair<lld, lld> data = {0, s};
            push_back(v, size, data, address);
        }
        else
        {
            //else if it is not source we insert all distances
            pair<lld, lld> data = {inf, i};
            push_back(v, size, data, address);
        }
    }
    vector<lld> distance(n + 2, inf);
    distance[s] = 0;
    vector<lld> shortest_path_fount(n + 2, 0);
    shortest_path_fount[s] = 1;
    vector<lld> present(n + 2);
    vector<pair<lld, lld>>::iterator i;
    pair<lld, lld> top_element;
    while (empty(v, n) == 0)
    {
        //get min returns the vertex having minimum wt in the form of {wt,vertex}
        top_element = get_min(v);
        lld element = top_element.second;
        lld dist = top_element.first;
        extract_min(v, size, address);
        for (i = adj[element].begin(); i != adj[element].end(); i++)
        {
            lld adjacent = i->second;
            lld dista = i->first;
            if (shortest_path_fount[adjacent] == 0 && distance[element] != inf && distance[adjacent] > dista + distance[element])
            {
                decrease_key(v, size, n + 2, {distance[adjacent], adjacent}, {dista + distance[element], adjacent}, address);
                distance[adjacent] = dista + distance[element];
            }
        }
        shortest_path_fount[element] = 1;
    }
    for (lld i = 1; i < n + 1; i++)
    {
        if (same(i, s))
        {
            ps(0);
        }
        else if (same(distance[i], inf))
        {
            ps(inf);
        }
        else
        {
            lld corrected = distance[i] - changed_distance[s] + changed_distance[i];
            ps(corrected);
        }
    }
    p("");
}
typedef struct node
{
    lld vertex;
    lld val, degree;
    node *parent, *child, *sibling;
}(node);

node *root = NULL;
node *getparent(node *head)
{
    return head->parent;
}
node *get(node *head)
{
    return head;
}
void join_two_binomial_heaps(node *h1, node *h2)
{
    //links the two binomial tree h1 and h2;
    h1->parent = get(h2);
    h1->sibling = h2->child;
    h2->child = h1;
    h2->degree = h2->degree + 1;
}
lld ret(lld a)
{
    return a;
}
node *createnode(lld n, lld vertex)
{
    node *new_node = new node;
    new_node->parent = NULL;
    new_node->val = ret(n);
    new_node->sibling = NULL;
    new_node->child = NULL;
    new_node->vertex = ret(vertex);
    new_node->degree = 0;
    return new_node;
}
lld exists(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 2;
}
lld bigger(lld a, lld b)
{
    return a > b;
}
lld lesser(lld a, lld b)
{
    return a < b;
}
lld equals(lld a, lld b)
{
    return a == b;
}
node *sibling(node *head)
{
    return head->sibling;
}
node *merget_binomial_heaps(node *h1, node *h2)
{
    if (!h1)
        return h2;
    if (h2 == NULL)
        return h1;
    vector<node *> v;
    //we will merge the two heaps in the vector v and then store them into res;
    node *res = NULL;
    while (h1 != NULL && h2 != NULL)
    {
        if (h1->degree < h2->degree)
        {
            v.pb(h1);
            h1 = h1->sibling;
        }
        else if (h1->degree == h2->degree)
        {
            v.pb(h1);
            h1 = h1->sibling;
        }
        else
        {
            v.pb(h2);
            h2 = h2->sibling;
        }
    }
    if (h1 == NULL)
    {
        while (h2)
        {
            v.pb(h2);
            h2 = h2->sibling;
        }
    }
    if (h2 == NULL)
    {
        while (h1)
        {
            v.pb(h1);
            h1 = h1->sibling;
        }
    }
    lld i = 0;
    for (i = 0; i < v.size() - 1; i++)
    {
        //the sibling of v[i] is v[i+1];
        v[i]->sibling = v[i + 1];
    }
    v[i]->sibling = NULL;
    res = v[0];
    return res;
}
node *union_binomial_heaps(node *h1, node *h2)
{
    //we will union the heaps using this function
    lld alpha = !h1 && h2 == NULL;
    if (alpha)
        return NULL;
    node *res = merget_binomial_heaps(h1, h2);
    node *prev = NULL;
    node *curr = res;
    node *next = curr->sibling;
    while (next)
    {
        alpha = (curr->degree != next->degree) || ((next->sibling != NULL) && (next->sibling)->degree == curr->degree);
        if (alpha)
        {
            prev = curr;
            curr = next;
        }

        else
        {
            alpha = curr->val <= next->val;
            lld beta = prev == NULL;
            if (alpha)
            {
                curr->sibling = next->sibling;
                join_two_binomial_heaps(next, curr);
            }
            else
            {
                if (beta)
                    res = get(next);
                else
                    prev->sibling = get(next);
                join_two_binomial_heaps(curr, next);
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return res;
}
void insert_binomial_heap(lld x, lld vertex, vector<node *> &address)
{
    //we will make a new node having value x and vertex vertex;
    //we will store the address of the vertex in address[vertex]
    address[vertex] = createnode(x, vertex);
    root = union_binomial_heaps(root, address[vertex]);
}
void reverse_linked_list(node *h)
{
    if (h->sibling)
    {
        reverse_linked_list(h->sibling);
        (h->sibling)->sibling = h;
    }
    else
        root = h;
}

node *extract_minimum_binomial_heap(node *h)
{
    //if the heap is empty we return null;
    if (exists(h) == 0)
        return NULL;

    node *min_node_prev = NULL;
    node *min_node = h;
    lld min = h->val;
    node *curr = h;
    while (curr->sibling)
    {
        if (lesser((curr->sibling)->val, min))
        {
            min = (curr->sibling)->val;
            min_node_prev = curr;
            min_node = curr->sibling;
        }
        curr = curr->sibling;
    }
    lld single_node = min_node_prev == NULL && min_node->sibling == NULL;
    lld gamma = min_node_prev == NULL;
    //if there is only one node then h=NULL;
    if (single_node)
        h = NULL;
    else if (gamma)
        h = min_node->sibling;
    else
        min_node_prev->sibling = min_node->sibling;
    lld theta = min_node->child != NULL;
    if (theta)
    {
        reverse_linked_list(min_node->child);
        (min_node->child)->sibling = NULL;
    }
    else
    {
        root = NULL;
    }
    node *temp = root;
    while (temp != NULL)
    {
        temp->parent = NULL;
        temp = temp->sibling;
    }
    return union_binomial_heaps(h, root);
}
void decrease_key_binomial_heap(node *H, lld old_val, lld vertex, lld new_val, vector<node *> &address)
{
    //address returns the address of the vertex;
    node *newnode = address[vertex];
    // if the element is not present we return;
    if (exists(newnode) == 0)
        return;
    newnode->val = new_val;
    node *parent = newnode->parent;
    //else we update the value and similarly shift up
    while (1)
    {
        lld breakage = parent && newnode->val < parent->val;
        if (!breakage)
        {
            break;
        }
        swap(newnode->val, parent->val);
        swap(newnode->vertex, parent->vertex);
        newnode = get(parent);
        parent = getparent(parent);
    }
}
pair<lld, lld> get_min(node *h)
{
    if (h == NULL)
        return {inf, inf};
    node *min_node = h;
    lld min = h->val;
    lld vertex = h->vertex;
    node *curr = h;
    while (curr->sibling)
    {
        lld theta = (curr->sibling)->val < min;
        if (theta)
        {
            min = (curr->sibling)->val;
            vertex = (curr->sibling)->vertex;
            min_node = curr->sibling;
        }
        curr = curr->sibling;
    }
    //we return the minimum value in the heap;
    return {min, vertex};
}
void binomial_heap_based_dijkstra(lld n, vector<vector<pair<lld, lld>>> adj, lld s, vector<lld> changed_distance)
{
    root = NULL;
    vector<lld> present(n + 2);
    present[s] = 1;
    vector<node *> address(n + 2);
    insert_binomial_heap(0, s, address);

    vector<lld> distance(n + 2, inf);
    distance[s] = 0;
    vector<lld> shortest_path_fount(n + 2, 0);
    shortest_path_fount[s] = 1;
    vector<pair<lld, lld>>::iterator i;
    pair<lld, lld> top_element;
    while (root != NULL)
    {
        //we find the minimum element using get_min function
        top_element = get_min(root);
        lld element = top_element.second;
        present[element] = 0;
        address[element] = NULL;
        lld dist = top_element.first;
        root = extract_minimum_binomial_heap(root);

        for (i = adj[element].begin(); i != adj[element].end(); i++)
        {
            lld adjacent = i->second;
            lld dista = i->first;
            if (shortest_path_fount[adjacent] == 0 && distance[element] != inf && distance[adjacent] > dista + distance[element])
            {
                if (present[adjacent] == 1)
                {
                    //if the adjacent is present in the heap we decrease key
                    decrease_key_binomial_heap(root, distance[adjacent], adjacent, dista + distance[element], address);
                }
                else
                {
                    //if it is not present we insert it
                    insert_binomial_heap(distance[element] + dista, adjacent, address);
                    present[element] = 1;
                }
                distance[adjacent] = dista + distance[element];
            }
        }
        shortest_path_fount[element] = 1;
    }
    for (lld i = 1; i < n + 1; i++)
    {
        if (same(i, s))
        {
            ps(0);
        }
        else if (same(distance[i], inf))
        {
            ps(inf);
        }
        else
        {
            lld corrected = distance[i] - changed_distance[s] + changed_distance[i];
            ps(corrected);
        }
    }
    p("");
}
template <class V>
class FibonacciHeap;

template <class V>
struct fibonode
{
    fibonode<V> *prev, *next, *child, *parent;
    V value;
    lld vertex;
    lld degree;
    lld marked;
    friend class FibonacciHeap<V>;
};

template <class V>
class FibonacciHeap
{
protected:
    fibonode<V> *heap;
    vector<fibonode<V> *> fib_address;

public:
    fibonode<V> *get_node(fibonode<V> *a)
    {
        return a;
    }
    FibonacciHeap(lld n)
    {
        //we will store the address of different nodes in fib_address
        for (lld i = 0; i < n + 2; i++)
        {
            fib_address.push_back(NULL);
        }
        heap = _empty();
    }
    virtual ~FibonacciHeap()
    {
        if (heap)
        {
            _delete_fibo_heap_full(heap);
        }
    }
    fibonode<V> *insert(V value, lld vertex)
    {
        //we insert node having value value and vertex vertex;
        fibonode<V> *ret = _singleton(value, vertex);
        //we store the address in the fib_address;
        fib_address[vertex] = ret;
        heap = _merge_fibo_heaps(heap, fib_address[vertex]);
        return ret;
    }
    lld isEmpty()
    {
        //returns 1 if heap is empty;
        if (heap)
        {
            return 0;
        }
        return 1;
    }
    void merge(FibonacciHeap &other)
    {
        heap = _merge_fibo_heaps(heap, other.heap);
        other.heap = _empty();
    }
    V getMinimum()
    {
        //returns minimum value;
        if (heap)
            return heap->value;
        return inf;
    }
    pair<lld, lld> get_min()
    {
        //returns minimum key,value pair;
        lld va = heap->value;
        lld ve = heap->vertex;
        return {va, ve};
    }
    V extract_minimum_fibo_heap()
    {
        //removes minimum value;
        //old store the minimum value;
        fibonode<V> *old = get_node(heap);
        heap = _extract_minimum_fibo_heap(heap);
        V ret = old->value;
        //we save the value minimum value in ret;
        //we also make the address of minimum value as null as it is now deleted;
        fib_address[old->vertex] = NULL;
        delete old;
        return ret;
    }
    void decreaseKey(fibonode<V> *n, V value, lld vertex)
    {
        //used to decrease key;
        heap = _decreaseKey(heap, n, value, vertex);
    }
    fibonode<V> *find(V value, lld vertex)
    {
        //we return the fib_address[vertex] which is the address of the vertex;
        //we do this find in order 1;
        return fib_address[vertex];
    }
    pair<lld, lld> valvertex(fibonode<V> *a)
    {
        //returns value vertex pair of a node;
        return {a->value, a->vertex};
    }

public:
    fibonode<V> *_empty()
    {
        return get_node(NULL);
    }
    fibonode<V> *_singleton(V value, lld vertex)
    {
        //makes a new node;
        fibonode<V> *n = new fibonode<V>;
        n->value = value;
        n->vertex = vertex;
        n->prev = n->next = n;
        n->parent = NULL;
        n->degree = 0;
        n->marked = 0;
        n->child = get_node(NULL);
        return n;
    }
    fibonode<V> *_merge_fibo_heaps(fibonode<V> *a, fibonode<V> *b)
    {
        //merges two fib heaps;
        if (!a)
            return b;
        if (b == NULL)
            return a;
        if (valvertex(a) > valvertex(b))
        {
            swap(a, b);
        }
        fibonode<V> *an = a->next;
        a->next = b;
        lld theta;
        fibonode<V> *bp = b->prev;
        b->prev = get_node(a);
        an->prev = get_node(bp);
        bp->next = get_node(an);
        return a;
    }
    void _delete_fibo_heap_full(fibonode<V> *n)
    {
        lld breakage;
        if (n)
        {
            fibonode<V> *c = n;
            do
            {
                fibonode<V> *d = c;
                c = get_node(c->next);
                _delete_fibo_heap_full(d->child);
                delete d;
                breakage = c != n;
            } while (breakage);
        }
    }
    void _append_child(fibonode<V> *parent, fibonode<V> *child)
    {
        child->prev = child->next = get_node(child);
        child->parent = get_node(parent);
        parent->degree += 1;
        parent->child = _merge_fibo_heaps(parent->child, child);
    }
    void _unMarkAndUnParentAll(fibonode<V> *n)
    {
        if (!n)
            return;
        fibonode<V> *c = n;
        do
        {
            //the parent will be null as it is now cut;
            c->parent = NULL;
            //we unmakr it as it is now root;
            c->marked = 0;
            c = get_node(c->next);
        } while (c != n);
    }
    fibonode<V> *_extract_minimum_fibo_heap(fibonode<V> *n)
    {
        _unMarkAndUnParentAll(n->child);
        lld same_node = n->next == n;
        //if n->next =n that means there is only one node in the parent doubly linked list;
        if (same_node)
        {
            n = n->child;
        }
        else if (!same_node)
        {
            n->next->prev = get_node(n->prev);
            n->prev->next = get_node(n->next);
            n = _merge_fibo_heaps(n->next, n->child);
        }
        if (!n)
            return n;
        fibonode<V> *trees[64] = {NULL};

        while (1)
        {
            if (trees[n->degree] != NULL)
            {
                fibonode<V> *t = get_node(trees[n->degree]);
                lld same = t == n;
                if (same)
                    break;
                trees[n->degree] = NULL;
                t->prev->next = get_node(t->next);
                t->next->prev = get_node(t->prev);
                lld theta = valvertex(n) < valvertex(t);
                if (theta)
                {
                    _append_child(n, t);
                }
                else
                {
                    lld gamma = n->next == n;
                    lld same = gamma;
                    if (gamma)
                    {
                        t->next = t;
                        t->prev = t;
                    }
                    else if (!same)
                    {
                        n->prev->next = get_node(t);
                        n->next->prev = get_node(t);
                        t->next = get_node(n->next);
                        t->prev = get_node(n->prev);
                    }
                    _append_child(t, n);
                    n = get_node(t);
                }
                continue;
            }
            else
            {
                trees[n->degree] = get_node(n);
            }
            n = get_node(n->next);
        }
        //we update the minimum pointer
        fibonode<V> *min = n;
        lld breakage;
        do
        {
            if (valvertex(n) < valvertex(min))
                min = n;
            n = n->next;
            breakage = n != min;
        } while (breakage);
        return min;
    }

    fibonode<V> *_cut(fibonode<V> *heap, fibonode<V> *n)
    {
        //if n->next is same as n that means only one node in the parent doubly linked list;
        lld same_node = n->next == n;
        if (same_node)
        {
            n->parent->child = NULL;
        }
        else
        {
            n->next->prev = get_node(n->prev);
            n->parent->child = n->prev->next = get_node(n->next);
        }
        //we unmark it;
        n->marked = 0;
        //we make the next and previuos as n ;
        n->next = n;
        n->prev = n;
        //we reduct the parents degree;
        n->parent->degree -= 1;
        //we then merge;
        fibonode<V> *res = _merge_fibo_heaps(heap, n);
        return res;
    }
    fibonode<V> *_decreaseKey(fibonode<V> *heap, fibonode<V> *n, V value, lld vertex)
    {
        if (n->value < value)
            return heap;
        n->value = value;
        fibonode<V> *parent = n->parent;
        if (parent && valvertex(n) < valvertex(parent))
        {
            heap = _cut(heap, n);
            n->parent = NULL;
            while (parent && parent->marked == 1)
            {
                heap = _cut(heap, parent);
                n = get_node(parent);
                parent = n->parent;
                n->parent = get_node(NULL);
            }
            if (parent && parent->parent)
                parent->marked = 1;
            if (valvertex(n) < valvertex(heap))
                heap = n;
        }
        fibonode<V> *min = heap;
        n = heap;
        //we update the minimum pointer
        if (heap)
        {
            do
            {
                if (valvertex(n) < valvertex(min))
                    min = n;
                n = n->next;
            } while (n != min);
        }
        heap = min;
        return heap;
    }
};
void fibo_heap_based_dijkstra(lld n, vector<vector<pair<lld, lld>>> adj, lld s, vector<lld> changed_distance)
{
    FibonacciHeap<lld> fh(n);
    //we make a class fh;
    vector<lld> present(n + 2);
    present[s] = 1;
    fh.insert(0, s);
    //we insert {0,s} in the heap;
    vector<lld> distance(n + 2, inf);
    distance[s] = 0;
    vector<lld> shortest_path_fount(n + 2, 0);
    shortest_path_fount[s] = 1;
    vector<pair<lld, lld>>::iterator i;
    pair<lld, lld> top_element;
    while (fh.isEmpty() == 0)
    {
        top_element = fh.get_min();
        //get_min is only order 1 as it returns heap->value and heap->vertex;
        lld element = top_element.second;
        present[element] = 0;
        lld dist = top_element.first;
        fh.extract_minimum_fibo_heap();
        for (i = adj[element].begin(); i != adj[element].end(); i++)
        {
            lld adjacent = i->second;
            lld dista = i->first;
            if (shortest_path_fount[adjacent] == 0 && distance[element] != inf && distance[adjacent] > dista + distance[element])
            {
                if (present[adjacent] == 1)
                {
                    //if the element is present we find it in order 1 and then call decrease key;
                    fibonode<lld> *n = fh.find(distance[adjacent], adjacent);
                    fh.decreaseKey(n, dista + distance[element], adjacent);
                }
                else
                {
                    //if the element is not present we insert it into the heap;
                    fh.insert(distance[element] + dista, adjacent);
                    present[adjacent] = 1;
                }
                distance[adjacent] = dista + distance[element];
            }
        }
        shortest_path_fount[element] = 1;
    }
    for (lld i = 1; i < n + 1; i++)
    {
        if (same(i, s))
        {
            ps(0);
        }
        else if (same(distance[i], inf))
        {
            ps(inf);
        }
        else
        {
            lld corrected = distance[i] - changed_distance[s] + changed_distance[i];
            ps(corrected);
        }
    }
    p("");
}
void directed_johnson(lld n, lld d, lld argc, char **argv)
{
    if (n == 0)
    {
        p("");
        return;
    }
    vector<vector<pair<lld, lld>>> adj(n + 2);
    vector<vector<pair<lld, lld>>> adj_changed(n + 2);
    lld negative_cycle_found = 0;
    lld negative_edge_found = 0;
    lld input;
    for (lld i = 1; i <= n; i++)
    {
        for (lld j = 1; j <= n; j++)
        {
            cin >> input;
            if (input < 0)
            {
                negative_edge_found = 1;
                if (d == 0)
                {
                    //if the graph is undirected and negative edge is found therefore there is a negative cycle
                    negative_cycle_found = 1;
                }
            }
            if (input != inf)
            {
                if (i != j)
                {
                    //if the input is not inf we push it in our 2D vector
                    adj[i].push_back(pair<lld, lld>(input, j));
                    adj_changed[i].push_back(pair<lld, lld>(input, j));
                }
            }
        }
    }
    if (negative_cycle_found == 1)
    {
        p(-1);
        return;
    }
    for (lld j = 1; j <= n; j++)
    {
        input = 0;
        adj[n + 1].push_back(pair<lld, lld>(input, j));
        adj_changed[n + 1].push_back(pair<lld, lld>(input, j));
    }
    vector<lld> distance(n + 2, inf);
    if (negative_edge_found)
    {
        bellman(n, adj, distance, negative_cycle_found);
        if (negative_cycle_found == 1)
        {
            return;
        }
        change(adj_changed, distance);
    }

    for (lld i = 1; i <= n; i++)
    {
        if (argc == 1)
        {
            //default case is fibo;
            fibo_heap_based_dijkstra(n, adj_changed, i, distance);
        }
        else if (*argv[1] == '1')
        {
            array_based_dijkstra(n, adj_changed, i, distance);
        }
        else if (*argv[1] == '2')
        {
            binary_heap_based_dijkstra(n, adj_changed, i, distance);
        }
        else if (*argv[1] == '3')
        {
            binomial_heap_based_dijkstra(n, adj_changed, i, distance);
        }
        else if (*argv[1] == '4')
        {
            fibo_heap_based_dijkstra(n, adj_changed, i, distance);
        }
    }
}

signed main(int argc, char **argv)
{
    fastio;
    lld t;
    cin >> t;
    clock_t start[t], end[t];
    lld iteration = 0;
    while (t--)
    {
        start[iteration] = clock();
        lld n, d;
        cin >> n >> d;
        directed_johnson(n, d, argc, argv);
        end[iteration++] = clock();
    }
    double time_taken;
    //now we will print the times;
    for (lld i = 0; i < iteration; i++)
    {
        time_taken = double(end[i] - start[i]) / double(CLOCKS_PER_SEC);
        cout << fixed << time_taken << setprecision(5);
        ps("");
    }
}
//i have checked my code on windows on repl online compiler and on tutorialspoint online compiler and it runs fine
