/* Translated from Janus program */
#include <stdio.h>      /* printf */
#include <assert.h>
#include <math.h>
#include <vector>
#include <stdlib.h>     /* atoi */


template <std::size_t SIZE1, std::size_t SIZE2>
void allocate_object_forward(std::vector<int> &elem, std::vector<int> &next, int &flp, int &hp, int &cell);
template <std::size_t SIZE1, std::size_t SIZE2>
void allocate_object_reverse(std::vector<int> &elem, std::vector<int> &next, int &flp, int &hp, int &cell);

template <std::size_t SIZE1, std::size_t SIZE2, std::size_t SIZE3>
void move_next_forward(std::vector<int> &elem, std::vector<int> &prev, std::vector<int> &next, int &p);
template <std::size_t SIZE1, std::size_t SIZE2, std::size_t SIZE3>
void move_next_reverse(std::vector<int> &elem, std::vector<int> &prev, std::vector<int> &next, int &p);

template <std::size_t SIZE1, std::size_t SIZE2, std::size_t SIZE3, std::size_t SIZE4>
void tree_search_forward(std::vector<int> &elem, std::vector<int> &parent, std::vector<int> &left, std::vector<int> &right, int &root, int &cell, int &p);
template <std::size_t SIZE1, std::size_t SIZE2, std::size_t SIZE3, std::size_t SIZE4>
void tree_search_reverse(std::vector<int> &elem, std::vector<int> &parent, std::vector<int> &left, std::vector<int> &right, int &root, int &cell, int &p);

template <std::size_t SIZE1, std::size_t SIZE2, std::size_t SIZE3, std::size_t SIZE4>
void tree_insert_forward(std::vector<int> &elem, std::vector<int> &parent, std::vector<int> &left, std::vector<int> &right, int &root, int &flp, int &hp, int &cell);
template <std::size_t SIZE1, std::size_t SIZE2, std::size_t SIZE3, std::size_t SIZE4>
void tree_insert_reverse(std::vector<int> &elem, std::vector<int> &parent, std::vector<int> &left, std::vector<int> &right, int &root, int &flp, int &hp, int &cell);

template <std::size_t SIZE1, std::size_t SIZE2, std::size_t SIZE3, std::size_t SIZE4>
void dfs_rec_forward(std::vector<int> &elem, std::vector<int> &parent, std::vector<int> &left, std::vector<int> &right, int &p, int &v, int &res);
template <std::size_t SIZE1, std::size_t SIZE2, std::size_t SIZE3, std::size_t SIZE4>
void dfs_rec_reverse(std::vector<int> &elem, std::vector<int> &parent, std::vector<int> &left, std::vector<int> &right, int &p, int &v, int &res);

void allocate_object_forward(std::vector<int> &elem, std::vector<int> &next, int &flp, int &hp, int &cell) {
    if (flp == 0) {
        cell ^= hp;
        hp += 1;
        assert(flp == 0 && cell == hp - 1);
    }
    else {
        int tmp = next[flp];
        next[flp] ^= tmp;
        cell ^= tmp;
        tmp ^= cell;
        cell ^= tmp;
        next[flp] ^= tmp;
        assert(tmp == next[flp]);
        cell ^= flp;
        flp ^= cell;
        cell ^= flp;
        assert(!(flp == 0 && cell == hp - 1));
    }
}
void allocate_object_reverse(std::vector<int> &elem, std::vector<int> &next, int &flp, int &hp, int &cell) {
    if (flp == 0 && cell == hp - 1) {
        hp -= 1;
        cell ^= hp;
        assert(flp == 0);
    }
    else {
        cell ^= flp;
        flp ^= cell;
        cell ^= flp;
        int tmp = next[flp];
        next[flp] ^= tmp;
        cell ^= tmp;
        tmp ^= cell;
        cell ^= tmp;
        next[flp] ^= tmp;
        assert(tmp == next[flp]);
        assert(!(flp == 0));
    }
}

void move_next_forward(std::vector<int> &elem, std::vector<int> &prev, std::vector<int> &next, int &p) {
    int tmp = next[p];
    p ^= prev[tmp];
    p ^= tmp;
    tmp ^= p;
    p ^= tmp;
    assert(tmp == 0);
}
void move_next_reverse(std::vector<int> &elem, std::vector<int> &prev, std::vector<int> &next, int &p) {
    int tmp = 0;
    p ^= tmp;
    tmp ^= p;
    p ^= tmp;
    p ^= prev[tmp];
    assert(tmp == next[p]);
}

void tree_search_forward(std::vector<int> &elem, std::vector<int> &parent, std::vector<int> &left, std::vector<int> &right, int &root, int &cell, int &p) {
    p ^= root;
    assert(p == root);
    while (!(cell <= elem[p] && left[p] == 0 || elem[p] < cell && right[p] == 0)) {
        if (cell <= elem[p]) {
            move_next_forward(elem, parent, left, p);
            assert(cell <= elem[parent[p]]);
        }
        else {
            move_next_forward(elem, parent, right, p);
            assert(!(cell <= elem[parent[p]]));
        }
        assert(!(p == root));
    }
}
void tree_search_reverse(std::vector<int> &elem, std::vector<int> &parent, std::vector<int> &left, std::vector<int> &right, int &root, int &cell, int &p) {
    assert(cell <= elem[p] && left[p] == 0 || elem[p] < cell && right[p] == 0);
    while (!(p == root)) {
        if (cell <= elem[parent[p]]) {
            move_next_reverse(elem, parent, left, p);
            assert(cell <= elem[p]);
        }
        else {
            move_next_reverse(elem, parent, right, p);
            assert(!(cell <= elem[p]));
        }
        assert(!(cell <= elem[p] && left[p] == 0 || elem[p] < cell && right[p] == 0));
    }
    p ^= root;
}

void tree_insert_forward(std::vector<int> &elem, std::vector<int> &parent, std::vector<int> &left, std::vector<int> &right, int &root, int &flp, int &hp, int &cell) {
    if (root == 0) {
        int tmp = 0;
        allocate_object_forward(elem, right, flp, hp, tmp);
        root ^= tmp;
        tmp ^= root;
        root ^= tmp;
        elem[root] ^= cell;
        assert(tmp == 0);
        assert(left[root] == 0 && right[root] == 0);
    }
    else {
        int p = 0;
        tree_search_forward(elem, parent, left, right, root, cell, p);
        int tmp = 0;
        allocate_object_forward(elem, right, flp, hp, tmp);
        elem[tmp] ^= cell;
        parent[tmp] ^= p;
        if (cell < elem[p]) {
            left[p] ^= tmp;
            tmp ^= left[p];
            move_next_forward(elem, parent, left, p);
            assert(cell < elem[parent[p]]);
        }
        else {
            right[p] ^= tmp;
            tmp ^= right[p];
            move_next_forward(elem, parent, right, p);
            assert(!(cell < elem[parent[p]]));
        }
        assert(tmp == 0);
        tree_search_reverse(elem, parent, left, right, root, cell, p);
        assert(p == 0);
        assert(!(left[root] == 0 && right[root] == 0));
    }
}
void tree_insert_reverse(std::vector<int> &elem, std::vector<int> &parent, std::vector<int> &left, std::vector<int> &right, int &root, int &flp, int &hp, int &cell) {
    if (left[root] == 0 && right[root] == 0) {
        int tmp = 0;
        elem[root] ^= cell;
        root ^= tmp;
        tmp ^= root;
        root ^= tmp;
        allocate_object_reverse(elem, right, flp, hp, tmp);
        assert(tmp == 0);
        assert(root == 0);
    }
    else {
        int p = 0;
        tree_search_forward(elem, parent, left, right, root, cell, p);
        int tmp = 0;
        if (cell < elem[parent[p]]) {
            move_next_reverse(elem, parent, left, p);
            tmp ^= left[p];
            left[p] ^= tmp;
            assert(cell < elem[p]);
        }
        else {
            move_next_reverse(elem, parent, right, p);
            tmp ^= right[p];
            right[p] ^= tmp;
            assert(!(cell < elem[p]));
        }
        parent[tmp] ^= p;
        elem[tmp] ^= cell;
        allocate_object_reverse(elem, right, flp, hp, tmp);
        assert(tmp == 0);
        tree_search_reverse(elem, parent, left, right, root, cell, p);
        assert(p == 0);
        assert(!(root == 0));
    }
}

void dfs_rec_forward(std::vector<int> &elem, std::vector<int> &parent, std::vector<int> &left, std::vector<int> &right, int &p, int &v, int &res) {
    if (v == elem[p]) {
        int tmp = p;
        res ^= tmp;
        assert(tmp == res);
        assert(v == elem[p]);
    }
    if (left[p] != 0) {
        int tmp = left[p];
        dfs_rec_forward(elem, parent, left, right, tmp, v, res);
        assert(tmp == left[p]);
        assert(left[p] != 0);
    }
    if (right[p] != 0) {
        int tmp = right[p];
        dfs_rec_forward(elem, parent, left, right, tmp, v, res);
        assert(tmp == right[p]);
        assert(right[p] != 0);
    }
}
void dfs_rec_reverse(std::vector<int> &elem, std::vector<int> &parent, std::vector<int> &left, std::vector<int> &right, int &p, int &v, int &res) {
    if (right[p] != 0) {
        int tmp = right[p];
        dfs_rec_reverse(elem, parent, left, right, tmp, v, res);
        assert(tmp == right[p]);
        assert(right[p] != 0);
    }
    if (left[p] != 0) {
        int tmp = left[p];
        dfs_rec_reverse(elem, parent, left, right, tmp, v, res);
        assert(tmp == left[p]);
        assert(left[p] != 0);
    }
    if (v == elem[p]) {
        int tmp = res;
        res ^= tmp;
        assert(tmp == p);
        assert(v == elem[p]);
    }
}

int main(int argc, char **argv) {
    /* Added for research purposes */
    if (argc < 2) {
        return 1;
    }

    int n = 0;

    n += (int) atoi(argv[1]);
    /*                             */

    std::vector<int> elem(n + 1, 0);
    std::vector<int> parent(n + 1, 0);
    std::vector<int> left(n + 1, 0);
    std::vector<int> right(n + 1, 0);
    int root = 0;
    int flp = 0;
    int hp = 0;
    int cell = 0;
    int p = 0;
    int v = 0;
    int res = 0;

    hp += 1;

    /* Added for research purposes */
    cell = n / 2;
    tree_insert_forward(elem, parent, left, right, root, flp, hp, cell);

    for (int i = 0; i < n / 2; i++) {
        cell = i;
        tree_insert_forward(elem, parent, left, right, root, flp, hp, cell);
    }

    for (int i = n / 2 + 1; i < n; i++) {
        cell = i;
        tree_insert_forward(elem, parent, left, right, root, flp, hp, cell);
    }
    /*                             */

    v += n / 2 - 1;
    dfs_rec_forward(elem, parent, left, right, root, v, res);

    return 1;
}
