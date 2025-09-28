// ciphers.cpp
// Compile: g++ -std=c++17 ciphers.cpp -o ciphers
#include <bits/stdc++.h>
using namespace std;

string upclean(const string &s) {
    string r;
    for(char ch : s) {
        if(isalpha((unsigned char)ch)) r.push_back(toupper((unsigned char)ch));
    }
    return r;
}

/* ---------- Caesar ---------- */
string caesar_encrypt(const string &pt, int k) {
    string p = upclean(pt), r;
    for(char ch : p) r.push_back(char((ch - 'A' + k) % 26 + 'A'));
    return r;
}
string caesar_decrypt(const string &ct, int k) {
    return caesar_encrypt(ct, (26 - (k%26))%26);
}

/* ---------- Affine ---------- */
int egcd(int a,int b,int &x,int &y){
    if(!b){ x=1; y=0; return a; }
    int x1,y1; int g = egcd(b,a%b,x1,y1);
    x = y1; y = x1 - (a/b)*y1;
    return g;
}
int modinv(int a,int m){
    int x,y;
    int g = egcd(a,m,x,y);
    if(g!=1) return -1;
    x %= m; if(x<0) x+=m;
    return x;
}
string affine_encrypt(const string &pt, int a, int b) {
    string p = upclean(pt), r;
    for(char ch : p) {
        int x = ch - 'A';
        r.push_back(char((a*x + b) % 26 + 'A'));
    }
    return r;
}
string affine_decrypt(const string &ct, int a, int b) {
    int inv = modinv(a,26);
    if(inv == -1) return string("ERROR: a not invertible mod26");
    string c = upclean(ct), r;
    for(char ch : c) {
        int y = ch - 'A';
        int x = (inv * ((y - b + 26)%26)) % 26;
        r.push_back(char(x + 'A'));
    }
    return r;
}

/* ---------- Permutation cipher (alphabet permutation) ---------- */
string perm_encrypt(const string &pt, const string &perm) {
    // perm: 26 uppercase letters representing image of A..Z
    string p = upclean(pt), r;
    vector<int> map(26,0);
    for(int i=0;i<26;i++) map[i] = perm[i]-'A';
    for(char ch : p) r.push_back(char('A' + map[ch-'A']));
    return r;
}
string perm_decrypt(const string &ct, const string &perm) {
    vector<int> inv(26,0);
    for(int i=0;i<26;i++) inv[perm[i]-'A'] = i;
    string c = upclean(ct), r;
    for(char ch : c) r.push_back(char('A' + inv[ch-'A']));
    return r;
}

/* ---------- Vigenere ---------- */
string vigenere_encrypt(const string &pt, const string &key) {
    string p = upclean(pt), k = upclean(key), r;
    if(k.empty()) return "ERROR: empty key";
    for(size_t i=0;i<p.size();++i) {
        int ki = k[i % k.size()] - 'A';
        r.push_back(char((p[i]-'A' + ki) % 26 + 'A'));
    }
    return r;
}
string vigenere_decrypt(const string &ct, const string &key) {
    string c = upclean(ct), k = upclean(key), r;
    if(k.empty()) return "ERROR: empty key";
    for(size_t i=0;i<c.size();++i) {
        int ki = k[i % k.size()] - 'A';
        r.push_back(char((c[i]-'A' - ki + 26) % 26 + 'A'));
    }
    return r;
}

/* ---------- Playfair ---------- */
struct Pos{int r,c;};
vector<string> build_playfair_table(const string &key) {
    string k = upclean(key);
    // Merge J -> I
    string used(26,0), table="";
    for(char ch : k) {
        char c = (ch=='J' ? 'I' : ch);
        if(!used[c-'A'] && c!='J') { table.push_back(c); used[c-'A']=1; }
    }
    for(char ch='A'; ch<='Z'; ++ch) {
        if(ch=='J') continue;
        if(!used[ch-'A']) { table.push_back(ch); used[ch-'A']=1; }
    }
    vector<string> mat(5);
    for(int i=0;i<5;i++) mat[i]=table.substr(i*5,5);
    return mat;
}
pair<string,string> playfair_prepare(const string &pt) {
    string p = upclean(pt);
    string s;
    for(char ch : p) {
        if(ch=='J') s.push_back('I'); else s.push_back(ch);
    }
    string out;
    for(size_t i=0;i<s.size();) {
        char a = s[i];
        char b = (i+1 < s.size() ? s[i+1] : 'X');
        if(a==b) { out.push_back(a); out.push_back('X'); i+=1; }
        else { out.push_back(a); out.push_back(b); i+=2; }
    }
    if(out.size()%2==1) out.push_back('X');
    return {out, s};
}
string playfair_transform(const string &pt, const vector<string>&mat, bool encrypt) {
    // build position map
    vector<Pos> pos(26,{-1,-1});
    for(int r=0;r<5;r++) for(int c=0;c<5;c++){
        pos[mat[r][c]-'A'] = {r,c};
    }
    string out;
    for(size_t i=0;i<pt.size(); i+=2) {
        char A = pt[i], B = pt[i+1];
        Pos pa = pos[A-'A'], pb = pos[B-'A'];
        if(pa.r == pb.r) {
            int shift = encrypt ? 1 : 4;
            char a = mat[pa.r][(pa.c + shift)%5];
            char b = mat[pb.r][(pb.c + shift)%5];
            out.push_back(a); out.push_back(b);
        } else if(pa.c == pb.c) {
            int shift = encrypt ? 1 : 4;
            char a = mat[(pa.r + shift)%5][pa.c];
            char b = mat[(pb.r + shift)%5][pb.c];
            out.push_back(a); out.push_back(b);
        } else {
            char a = mat[pa.r][pb.c];
            char b = mat[pb.r][pa.c];
            out.push_back(a); out.push_back(b);
        }
    }
    return out;
}
string playfair_encrypt(const string &pt, const string &key) {
    auto mat = build_playfair_table(key);
    auto prepared = playfair_prepare(pt).first;
    return playfair_transform(prepared, mat, true);
}
string playfair_decrypt(const string &ct, const string &key) {
    auto mat = build_playfair_table(key);
    string c = upclean(ct);
    string r = playfair_transform(c, mat, false);
    return r; // further postprocessing (x removal) left to user
}

/* ---------- UI ---------- */
void print_menu() {
    cout << "Classical Ciphers - Menu\n";
    cout << "1) Caesar\n2) Affine\n3) Permutation (alphabet)\n4) Vigenere\n5) Playfair\n0) Exit\nChoose: ";
}

int main(){
    while(true){
        print_menu();
        int m; if(!(cin>>m)) return 0;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if(m==0) break;
        if(m==1){
            cout<<"Caesar selected. Type E for encrypt, D for decrypt: ";
            char t; cin>>t; cin.ignore();
            if(t=='E' || t=='e'){
                cout<<"Plaintext: "; string pt; getline(cin,pt);
                cout<<"Key (0-25): "; int k; cin>>k;
                cout<<"Ciphertext: "<<caesar_encrypt(pt,k)<<"\n";
            } else {
                cout<<"Ciphertext: "; string ct; getline(cin,ct);
                cout<<"Key (0-25): "; int k; cin>>k;
                cout<<"Plaintext: "<<caesar_decrypt(ct,k)<<"\n";
            }
        } else if(m==2){
            cout<<"Affine selected. E encrypt, D decrypt: ";
            char t; cin>>t; cin.ignore();
            cout<<"Text: "; string txt; getline(cin,txt);
            cout<<"a (must be coprime with 26): "; int a; cin>>a;
            cout<<"b (0..25): "; int b; cin>>b;
            if(t=='E' || t=='e') cout<<"Cipher: "<<affine_encrypt(txt,a,b)<<"\n";
            else cout<<"Plain: "<<affine_decrypt(txt,a,b)<<"\n";
        } else if(m==3){
            cout<<"Permutation selected. You must provide 26-letter permutation of A..Z (no J restriction)\n";
            cout<<"Permutation (26 letters): "; string perm; getline(cin,perm);
            while(perm.size()==0) getline(cin,perm);
            // clean
            string pclean;
            for(char ch : perm) if(isalpha((unsigned char)ch)) pclean.push_back(toupper(ch));
            if(pclean.size()!=26){ cout<<"Invalid permutation length\n"; continue; }
            cout<<"E or D: "; char t; cin>>t; cin.ignore();
            if(t=='E' || t=='e'){ cout<<"Plaintext: "; string pt; getline(cin,pt);
                cout<<"Cipher: "<<perm_encrypt(pt,pclean)<<"\n";
            } else { cout<<"Ciphertext: "; string ct; getline(cin,ct);
                cout<<"Plain: "<<perm_decrypt(ct,pclean)<<"\n";
            }
        } else if(m==4){
            cout<<"Vigenere selected. E or D: ";
            char t; cin>>t; cin.ignore();
            if(t=='E' || t=='e'){ cout<<"Plaintext: "; string pt; getline(cin,pt);
                cout<<"Key: "; string key; getline(cin,key);
                cout<<"Cipher: "<<vigenere_encrypt(pt,key)<<"\n";
            } else { cout<<"Ciphertext: "; string ct; getline(cin,ct);
                cout<<"Key: "; string key; getline(cin,key);
                cout<<"Plain: "<<vigenere_decrypt(ct,key)<<"\n";
            }
        } else if(m==5){
            cout<<"Playfair selected. E or D: ";
            char t; cin>>t; cin.ignore();
            cout<<"Key: "; string key; getline(cin,key);
            if(t=='E' || t=='e'){ cout<<"Plaintext: "; string pt; getline(cin,pt);
                cout<<"Cipher: "<<playfair_encrypt(pt,key)<<"\n";
            } else { cout<<"Ciphertext: "; string ct; getline(cin,ct);
                cout<<"Plain: "<<playfair_decrypt(ct,key)<<"\n";
            }
        } else cout<<"Invalid choice\n";
        cout<<"\n----------------------\n";
    }
    return 0;
}
