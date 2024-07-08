#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct stadium {
    string stadiumName;
    int capacity;
    string city;
    string clubs;
    string renovation;
    string Rc;
    string address;
};

stadium* readFile(const string& filename, int &n) {
    fstream f;
    f.open(filename);
    if (!f.is_open()) {
        return NULL;
    }

    string line;
    while (getline(f, line)) {  
        ++n;
    }
    f.close();
    n-=2; // tru dong tieu de va dong cuoi
    stadium* temp = new stadium[n];
    f.open(filename);
    getline(f, line);  // doc bo dong tieu de

    for (int i = 0; i < n; i++) 
    {
        getline(f, line);
        int cnt = 0;

        // Stadium name
        if(line[0] == '"')
        {
            line.erase(0,1);
            cnt=line.find('"');
            temp[i].stadiumName=line.substr(0,cnt);
            line.erase(0,cnt+2);
        }
        else
        {
            cnt = line.find(',');
            temp[i].stadiumName = line.substr(0, cnt);
            line.erase(0, cnt + 1);
        }

        // Capacity
        string ok;
        cnt=line.find(',');
        ok=line.substr(0,cnt);
        if(ok.size()==3)
        {
            temp[i].capacity = stoi(ok);
            line.erase(0, cnt + 1);
        }
        else
        {
            cnt = line.find(' ');
            temp[i].capacity = stoi(line.substr(0, cnt));
            line.erase(0, cnt + 1);
            cnt = line.find(',');
            temp[i].capacity = temp[i].capacity * 1000 + stoi(line.substr(0, cnt));
            line.erase(0, cnt + 1);
        }

        // City
        cnt = line.find(',');
        temp[i].city = line.substr(0, cnt);
        line.erase(0, cnt + 1);

        // Clubs
        cnt = line.find(',');
        temp[i].clubs = line.substr(0, cnt);
        line.erase(0, cnt + 1);

        // Renovation
        if (line[0] == '"') 
        {
            line.erase(0, 1);
            cnt = line.find('"');
            temp[i].renovation = line.substr(0, cnt);
            line.erase(0, cnt + 2);
        }
        else 
        {
            cnt = line.find(',');
            temp[i].renovation = line.substr(0, cnt);
            line.erase(0, cnt + 1);
        }

        // Record attendance
        if (line[0] == '"') 
        {
            line.erase(0, 1);
            cnt = line.find('"');
            temp[i].Rc = line.substr(0, cnt);
            line.erase(0, cnt + 2);
        } 
        else 
        {
            cnt = line.find(',');
            temp[i].Rc = line.substr(0, cnt);
            line.erase(0, cnt + 1);
        }

        // Address
        if (line[0] == '"') 
        {
            line.erase(0, 1);
            cnt = line.find('"');
            temp[i].address = line.substr(0, cnt);
        } 
        else 
        {
            temp[i].address = line;
        }
    }
    f.close();
    return temp;
}

int main() 
{
    int n = 0;
    stadium* oke = readFile("stadium.csv", n);
    cout<<n<<endl;
    if (oke != NULL) 
    {
        for (int i = 0; i < n; i++) 
        {
            cout << oke[i].stadiumName << " " << oke[i].capacity << " " << oke[i].city << " "<< oke[i].clubs << " " << oke[i].renovation << " " << oke[i].Rc << " " << oke[i].address << endl;
        }
        delete[] oke;
    } 
    return 0;
}
