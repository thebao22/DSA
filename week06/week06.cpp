#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;
const short p = 31;
const int m = 2000;
struct Company
{
    string name;
    string profit_tax;
    string address;
};
struct HashTable
{
    vector<Company> Company_list[m];
};
istream &operator>>(istream &in, Company &data);
ostream &operator<<(ostream &out, const Company &data);
vector<Company> readCompanyList(string file_name);
long long hashString(string company_name);long long hashString(string company_name);
HashTable* createHashTable(vector<Company> list_company);
Company *search(HashTable *hash_table, string company_name);
void insert(HashTable* hash_table, Company company);
//-----------------------------------------------------------------------------------------------------
istream &operator>>(istream &in, Company &data)
{
    getline(in, data.name, '|');
    getline(in, data.profit_tax, '|');
    getline(in, data.address);
    return in;
}
ostream &operator<<(ostream &out, Company &data)
{
    out << data.name << "|" << data.profit_tax << "|" << data.address << endl;
    return out;
}

vector<Company> readCompanyList(string file_name)
{
    vector<Company> result;
    ifstream file(file_name);
    if (!file.is_open())
    {
        cout << "Error opening file: " << file_name << endl;
        return result;
    }
    Company company;
    file >> company;

    while (file >> company)
    {
        result.push_back(company);
    }
    return result;
}
long long hashString(string company_name)
{
    string sub;
    if (company_name.length() <= 20)
        sub = company_name;
    else
        sub = company_name.substr(company_name.length() - 20);
    long long hash = 0;
    long long pow = 1;
    for (int i = 0; i < sub.length(); i++)
    {
        hash = (hash + (long long)sub[i] * pow) % m;
        pow = (pow * p) % m;
    }
    return hash;
}
long long hashString2(string company_name,int i){
    long long hash = 0;
    hash = hashString(company_name);
    hash = (hash + i*i) % m;
    return hash;
}
HashTable* createHashTable(vector<Company> list_company){
    HashTable *hash_table = new HashTable;
    for (int i = 0; i < list_company.size(); i++)
    {
        long long hash = hashString(list_company[i].name);
        int j = 0;
        while(!hash_table->Company_list[hash].empty())
        {
            hash = hashString2(list_company[i].name,j);
            j++;
        }
        hash_table->Company_list[hash].push_back(list_company[i]);
    }
    return hash_table;
}
Company *search(HashTable *hash_table, string company_name)
{
    int cnt = 0;
    long long i = hashString(company_name);
    for (i; cnt < m; i = hashString2(company_name,cnt)){
        for (Company &x: hash_table->Company_list[i]){
            if (x.name == company_name) return &x;
        }
        cnt++;
    }
    return nullptr;
}
void insert(HashTable* hash_table, Company company){
    long long hash = hashString(company.name);
    int j = 1;
    while(hash > m || !hash_table->Company_list[hash].empty())
        {
            hash = hashString2(company.name,j);
            j++;
        }
    hash_table->Company_list[hash].push_back(company);
}
int main()
{
    ofstream file("output.txt");
    ifstream file1("input.txt");
    if (!file1.is_open())
    {
        cout << "Error opening file: " << "input.txt" << endl;
        return 1;
    }
    vector<Company> company_list = readCompanyList("MST.txt");
    HashTable* hashtable =createHashTable(company_list);
    string company_name;
    while(getline(file1, company_name))
    {
        Company *company = search(hashtable, company_name);
        if (company != nullptr)
        {
            cout << *company;
            file << *company;
        }
        else
        {
            cout << "Company not found: " << company_name << endl;
            file << "Company not found: " << company_name << endl;
        }
    }
    file1.close();
    insert(hashtable, {"CONG TY TNHH THIET KE PHAN MEM DANG BUI THE BAO", "24120261", "Kong Hoa, Phu Ly, Ha Nam"});
     Company *company = search(hashtable, "CONG TY TNHH THIET KE PHAN MEM DANG BUI THE BAO");
        if (company != nullptr)
        {
            cout << *company;
            file << *company;
        }
        else
        {
            cout << "Company not found: " << company_name << endl;
            file << "Company not found: " << company_name << endl;
        }
        file.close();
    delete hashtable;    
    return 0;
}