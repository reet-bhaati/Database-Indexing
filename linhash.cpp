#include "bits/stdc++.h"
using namespace std;

int hashval = 2;
int R = 0;
int N = 2;
const float threshold = 0.75;
const int num_entries = 256;

typedef struct bucket
{
    int entries[num_entries];
    bucket *overflow;
} Bucket;

vector<Bucket *> hashtable;

Bucket *create_bucket()
{
    Bucket *temp = (Bucket *)malloc(sizeof(Bucket));
    for (int i = 0; i < num_entries; i++)
        temp->entries[i] = INT_MIN;
    temp->overflow = NULL;
    N++;
    return temp;
}

int nearest_power(int n)
{
    int p = 2;
    while (p <= n)
        p *= 2;
    if (p > n)
        p /= 2;
    return p;
}

void print()
{
    for (int i = 0; i < N; i++)
    {
        cout << "Bucket " << i << ": ";
        Bucket *curr = hashtable[i];
        while (curr)
        {
            for (int j = 0; j < num_entries; j++)
            {
                if (hashtable[i]->entries[j] != INT_MIN)
                    cout << hashtable[i]->entries[j] << " ";
            }
            curr = curr->overflow;
        }
        cout << endl;
    }
}

int search(int val)
{
    int x = val % hashval;
    if (x < 0)
    {
        x += hashval;
    }

    if (x >= hashtable.size())
    {
        x -= hashval / 2;
    }

    return x;
}

void insert_val(int bucket_num, int val)
{
    Bucket *curr = hashtable[bucket_num];
    int ins = 0;
    while (curr)
    {
        for (int i = 0; i < num_entries; i++)
        {
            if (curr->entries[i] == INT_MIN)
            {
                curr->entries[i] = val;
                ins = 1;
                break;
            }
        }
        if (ins == 1)
            break;
        if (curr->overflow == NULL)
        {
            Bucket *temp = create_bucket();
            curr->overflow = temp;
        }
        curr = curr->overflow;
    }
    return;
}

void split_bucket()
{
    int insert_at = hashtable.size();
    hashtable.push_back(create_bucket());
    int split_bucket_num = insert_at - nearest_power(insert_at);
    hashval = (hashtable.size() > hashval) ? 2 * hashval : hashval;

    Bucket *curr = hashtable[split_bucket_num];
    while (curr)
    {
        for (int i = 0; i < num_entries; i++)
        {
            int flag = 0;
            int x = curr->entries[i] % hashval;
            if (x < 0)
                x += hashval;
            if (x == insert_at)
            {
                insert_val(insert_at, curr->entries[i]);
                curr->entries[i] = INT_MIN;
            }
        }
        curr = curr->overflow;
    }
}

void insert(int val)
{
    int bucket_num = search(val);
    Bucket *curr = hashtable[bucket_num];
    while (curr)
    {
        for (int i = 0; i < num_entries; i++)
        {
            if (curr->entries[i] == val)
                return;
        }
        curr = curr->overflow;
    }
    cout << val << endl;
    insert_val(bucket_num, val);
    R++;
    float fr = (float)R / (float)(N * num_entries);
    if (fr >= threshold)
        split_bucket();
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "Please provide filename\nUsage: ./a.out filename" << endl;
        return 0;
    }
    for (int i = 0; i < 2; i++)
    {
        Bucket *temp = create_bucket();
        hashtable.push_back(temp);
    }
    string filename = argv[1];
    ifstream file(filename);
    string command;
    while (getline(file, command))
    {
        if (command.size() > 0)
        {
            int rec = stoi(command);
            insert(rec);
        }
    }
    return 0;
}