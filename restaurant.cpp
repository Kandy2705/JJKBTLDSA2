#include "main.h"

int MAXSIZE = 0;

class thucthi;
class nhahangGojo;
class nhahangSukuna;
class HuffTree_AVL;

//* nhà hàng của sư phụ GOJO
class nhahangGojo{
public:
    class Tree_BST;
private:
    vector<Tree_BST> khu_vuc;
public:
    nhahangGojo():khu_vuc(MAXSIZE + 1){}
    void tinhID(int result)
    {
        int ID;
        ID = result % MAXSIZE + 1;
        khu_vuc[ID].insert(result);
    }
    void KOKUSEN()
    {
        for(int i = 1; i < MAXSIZE + 1; i++) khu_vuc[i].remove();
    }

    void print_LIMITLESS(int canxoa)
    {
        if(canxoa <= 0 || canxoa > MAXSIZE) return;
        khu_vuc[canxoa].print();
    }
public:
    class Tree_BST{
        class Node;
    public:
        Node* vaodaukhuvuc;
        queue<int> ttvaokhuvuc;
        int a[1005][1005];
    public:
        Tree_BST():vaodaukhuvuc(nullptr){}
        ~Tree_BST(){
            while(!ttvaokhuvuc.empty()){
                int temp = ttvaokhuvuc.front();
                ttvaokhuvuc.pop();
                vaodaukhuvuc = xoa(vaodaukhuvuc,temp);
            }
        }
        int size(){
            return ttvaokhuvuc.size();
        }
        int sokhachkv(Node* node)
        {
            return node == NULL ? 0 : 1 + sokhachkv(node->left) + sokhachkv(node->right);
        }
///////////////////////////////////////////////////////////////////////////
        Node* them(Node* node, int result)
        {
            if (node == NULL){
                ttvaokhuvuc.push(result);
                  
                return new Node(result);
            }
            if (result < node -> result) {
                node -> left = them(node->left,result);
            }
            else node -> right = them(node->right,result);
            return node;
        }
        void insert(int result){
            vaodaukhuvuc = them(vaodaukhuvuc, result);
            return;
        }
        //////////////////////////////////////////////////////////////////////////
        Node* min(Node*vaodaukhuvuc){
            Node* temp = vaodaukhuvuc;
            while(temp && temp->left != NULL){
                temp = temp->left;
            }
            return temp;
        }
        /////////////////////////////////////////////////////////////////////////
        Node* xoa(Node* root,int result)
        {
            if (root == NULL) return root;
            if (result < root -> result){
                root -> left = xoa(root -> left, result);
            }
            else if (result > root -> result){
                root -> right = xoa(root -> right, result);
            }
            else{
                if (root-> left == NULL && root-> right == NULL){
                    delete root;
                      
                    return NULL;
                }
                else if (root-> left == NULL){
                    Node* temp = root-> right;
                    delete root;
                      
                    return temp;
                }
                else if (root-> right == NULL){
                    Node* temp = root-> left;
                    delete root;
                      
                    return temp;
                }
                Node* temp = min(root-> right);
                root-> result = temp-> result;
                root-> right = xoa(root->right, root ->result);
            }
            return root;
        }

        void mangchinhhop(){
            a[1][0] = 1;
            a[1][1] = 1;
            for(int i = 2; i <= sokhachkv(vaodaukhuvuc); i++){
                for(int j = 0; j <= i; j++){
                    if (j == 0 || j == i) a[i][j] = 1;
                    else a[i][j] = ((a[i - 1][j - 1] % MAXSIZE) + (a[i - 1][j] % MAXSIZE)) % MAXSIZE;
                }
            }
        }

        unsigned long long sohoanvi(Node* node)
        {
            if (node == NULL) return 1;
            if (sokhachkv(node) <= 2) return 1;
            mangchinhhop();
            return ((a[sokhachkv(node) - 1][sokhachkv(node -> left)] % MAXSIZE) * (sohoanvi(node -> right) % MAXSIZE)*(sohoanvi(node -> left) % MAXSIZE)) % MAXSIZE;
        }
        void remove(){
            if(ttvaokhuvuc.empty()) return;
            unsigned long long canxoa = sohoanvi(vaodaukhuvuc) % MAXSIZE;

            number_KOKUSEN.push_back(canxoa);

            while(canxoa != 0 && !ttvaokhuvuc.empty())
            {
                int temp = ttvaokhuvuc.front();
                ttvaokhuvuc.pop();
                vaodaukhuvuc = xoa(vaodaukhuvuc ,temp);
                canxoa --;
            }
        }
        void print_recursive(Node* node)
        {
            if(node != NULL){
                print_recursive(node->left);
                solution << node->result << "\n";
                print_recursive(node->right);
            }
        }
        void print(){print_recursive(vaodaukhuvuc);}
    private:
        class Node{
        private:
            int result;
            Node* left;
            Node* right;
            friend class Tree_BST;
        public:
            Node(int result) : result(result), left(NULL), right(NULL) {}
        };
    public:

    };
};
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//* nhà hàng sư phụ Sukuna


class nhahangSukuna{
    class Node;
private:
    vector<Node* > luutrukhuvuc;
    list<Node* > LRU;
private:

    int vitri(Node* index){
        int i = 0;
        for (list<Node*>::iterator it = LRU.begin(); it != LRU.end(); ++it) {
            if (index == *it){
                return i;
            }
            else i++;
        }
        return i;
    }

    void ReHeap_down(int index)
    {
        if (index*2 + 1 >= luutrukhuvuc.size()) return;
        else if (index*2 + 1 == luutrukhuvuc.size() - 1){
            if ((luutrukhuvuc[index*2 + 1] -> size() < luutrukhuvuc[index]-> size()) ||
                (luutrukhuvuc[index*2 + 1] -> size() == luutrukhuvuc[index]-> size() &&
                 vitri(luutrukhuvuc[index]) < vitri(luutrukhuvuc[index*2 + 1]))){
                swap(luutrukhuvuc[index*2 + 1] , luutrukhuvuc[index]);
                return;
            }
            else return;
        }//themvaosomheapsomlalonhon
        int contrai = index*2 + 1;
        int conphai = index*2 + 2;
        int connho = ((luutrukhuvuc[contrai] -> size() < luutrukhuvuc[conphai] -> size()) ||
                      (luutrukhuvuc[contrai] -> size() == luutrukhuvuc[conphai] -> size()
                       && vitri(luutrukhuvuc[contrai]) > vitri(luutrukhuvuc[conphai]))) ? contrai : conphai;
        if ((luutrukhuvuc[connho] -> size() > luutrukhuvuc[index] -> size()) ||
            (luutrukhuvuc[connho] -> size() == luutrukhuvuc[index] -> size() && vitri(luutrukhuvuc[index]) > vitri(luutrukhuvuc[connho]))) return;
        swap(luutrukhuvuc[connho], luutrukhuvuc[index]);
        ReHeap_down(connho);
    }

    void ReHeap_up(int index)
    {
        int cha = (index - 1) / 2;
        if(index == 0 || (luutrukhuvuc[index] -> size() > luutrukhuvuc[cha] -> size()) ||
           (luutrukhuvuc[index] -> size() == luutrukhuvuc[cha] -> size() && vitri(luutrukhuvuc[index]) < vitri(luutrukhuvuc[cha]))) {
            return;
        }
        swap(luutrukhuvuc[index], luutrukhuvuc[cha]);
        ReHeap_up(cha);
    }

    void moveTop(Node* node)
    {
        LRU.remove(node);
        LRU.push_front(node);
    }

    void xoanode(Node* node)
    {
        LRU.remove(node);
    }
public:
    nhahangSukuna(){}
    ~nhahangSukuna(){
        for(int i = 0; i < luutrukhuvuc.size(); i++){
            delete luutrukhuvuc[i];
                
        }
    }

    void tinhID(int result)
    {
        int ID = result % MAXSIZE + 1;
        int index = -1;
        for(int i = 0; i < luutrukhuvuc.size(); i++){
            if (luutrukhuvuc[i] -> ID == ID){
                index = i;
                break;
            }
        }

        if(index == -1){
            luutrukhuvuc.push_back(new Node(ID));
              
            index = luutrukhuvuc.size() - 1;
            luutrukhuvuc[index]->insert(result);
            this->moveTop(luutrukhuvuc[index]);
            this->ReHeap_up(index);
        }
        else
        {
            luutrukhuvuc[index]->insert(result);
            this->moveTop(luutrukhuvuc[index]);
            this->ReHeap_down(index);
        }
    }
    void remove_KEITEIKEN(int canxoa)
    {
        if(luutrukhuvuc.size() <= 0) return;
        
        vector<Node* > newkv(luutrukhuvuc.begin(), luutrukhuvuc.end());
        queue<Node* > listDelete;
        for(int i = 0;  luutrukhuvuc.size() && i < canxoa; i++)
        {
            Node* nodeDelete = luutrukhuvuc[0];
            swap(luutrukhuvuc[0], luutrukhuvuc[luutrukhuvuc.size() - 1]);
            luutrukhuvuc.pop_back();
            this->ReHeap_down(0);
            
            listDelete.push(nodeDelete);
        }
        
        luutrukhuvuc = newkv;
        
        while(listDelete.size()){
            Node* nodeDelete = listDelete.front();
            listDelete.pop();
            nodeDelete->remove(canxoa);
            
            int index = 0;
            while(luutrukhuvuc[index] !=  nodeDelete) {
                index++;
            }
            if(nodeDelete->size() == 0)
            {
                swap(luutrukhuvuc[index], luutrukhuvuc[luutrukhuvuc.size() - 1]);
                this -> xoanode(luutrukhuvuc[luutrukhuvuc.size() - 1]);
                delete luutrukhuvuc[luutrukhuvuc.size() - 1];
                luutrukhuvuc.pop_back();
            }
            this -> ReHeap_down(index);
        }
    }

    void print_pre_order(int index, int canxoa)
    {
        if((index >= this->luutrukhuvuc.size()) || (canxoa <= 0)) {
            return;
        }
        this->luutrukhuvuc[index]->print(canxoa);
        print_pre_order(index * 2 + 1, canxoa);
        print_pre_order(index * 2 + 2, canxoa);
    }
    void print_LIMITLESS(int canxoa)
    {
        print_pre_order(0, canxoa);
    }
private:
    class Node{
    private:
        int ID;
        list<int> head;
        friend class nhahangSukuna;
    public:
        Node(int ID) : ID(ID) {}
        int size() const { return head.size(); }
        void insert(int result){head.push_front(result);}
        void remove(int canxoa)
        {
            while(canxoa != 0 && !head.empty())
            {
                solution << head.back() << "-" <<ID << "\n";
                head.pop_back();
                canxoa--;
            }
        }
        void print(int canxoa)
        {
            for(list<int>::iterator it = head.begin(); canxoa > 0 && it != head.end(); ++it, --canxoa)
            {
                solution << ID << "-" << *it  << "\n";
            }
        }
    };
};
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

// Xây dựng cây HUFF
class HuffTree_AVL{
    class Node;
private:
    Node* vaodaukhuvuc = nullptr;
public:
    ~HuffTree_AVL(){
        clear(vaodaukhuvuc);
    }
    void clear(Node* node)
    {
        if(node)
        {
            clear(node->left);
            clear(node->right);
            delete node;
              
        }
    }

    static bool kieuchu(int i){
        if (i >= 65 && i <= 90){
            return true;
        }
        return false;
    }
    static bool cachxep(const std::pair<char, int>& a, const std::pair<char, int>& b) {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        if (kieuchu(static_cast<int>(a.first)) == kieuchu(static_cast<int>(b.first))){
            return a.first > b.first;
        }
        else{
            return kieuchu(static_cast<int>(a.first)) == true ? true : false;
        }
    }
    vector<pair<char, int>> xulychuoi(string& name)
    {
        int tmp[123] = {0};
        vector<pair<char, int>>ketqua;

        for(int i = 0; i < name.size(); i++){
            tmp[name[i]]++;
        }
        for(int i = 0; i < 123; i++){
            if (tmp[i] != 0){
                ketqua.emplace_back(static_cast<char>(i),tmp[i]);
            }
        }
        if(ketqua.size() < 3) return {};
        vector<pair<char, int>>temp = ketqua;
        for(int i = 0; i < ketqua.size(); i++){
            for(int j = ketqua[i].second; j > 0 ; j--){
                if (ketqua[i].first == 'Z'){
                    ketqua[i].first = static_cast<char>(65);
                }
                else if (ketqua[i].first == 'z'){
                    ketqua[i].first = static_cast<char>(97);
                }
                else{
                    ketqua[i].first = static_cast<char>(static_cast<int>(ketqua[i].first) + 1);
                }
            }
        }
        for(int i = 0; i < name.length(); i++){
            for(int j = 0; j < temp.size();j++){
                if (name[i] == temp[j].first){
                    name[i] = ketqua[j].first;
                    break;
                }
            }
        }
        vector<pair<char, int>> freq;
        for (int i = 0; i < ketqua.size(); ++i) {
            if (ketqua[i].second > 0) {
                int tong = ketqua[i].second;
                for (int j = i + 1; j < ketqua.size(); ++j) {
                    if (ketqua[i].first == ketqua[j].first) {
                        tong += ketqua[j].second;
                        ketqua[j].second = 0;
                    }
                }
                freq.emplace_back(ketqua[i].first, tong);
            }
        }
        if (freq.size() > 1){
            sort(freq.begin(), freq.end(),cachxep);
        }
        return freq;
    }

    int height(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = height(node->left);
        int rh = height(node->right);
        return (lh > rh ? lh : rh) + 1;
    }
    int taobalance(Node* node) {
        return (node == NULL) ? 0 : height(node->left) - height(node->right);
    }
    Node* xoayphai(Node* root) {
        if ((root -> left == NULL && root -> right == NULL) || root == NULL) return root;
        Node*temp = root -> left;
        if (temp -> right != NULL){
            Node*nhanh = temp -> right;
            temp -> right = root;
            root -> left = nhanh;
            root = temp;
        }
        else{
            temp -> right = root;
            root -> left = NULL;
            root = temp;
        }
        return root;
    }
    Node* xoaytrai(Node* root) {
        if ((root -> left == NULL && root -> right == NULL) || root == NULL) return root;
        Node*temp = root -> right;
        if (temp -> left != NULL){
            Node*nhanh = temp -> left;
            temp -> left = root;
            root -> right = nhanh;
            root = temp;
        }
        else{
            temp -> left = root;
            root -> right = NULL;
            root = temp;
        }
        return root;
    }
    Node* balanceNode(Node* node, int& count)
    {
        if (node == NULL) return NULL;
        int balance = taobalance(node);
        //LL
        if (balance > 1 && taobalance(node -> left) >= 0){
            count = count + 1;
            node = xoayphai(node);
        }
            //RR
        else if(balance < -1 && taobalance(node -> right) <= 0){
            count = count + 1;
            node = xoaytrai(node);
        }
            //LR
        else if(balance > 1 && taobalance(node -> left) < 0){
            count = count + 1;
            node -> left = xoaytrai(node -> left);
//            count = count + 2;
//            if (count >= 4) return node;
            node = xoayphai(node);
        }
        else if (balance < -1 && taobalance(node -> right) > 0){
            count = count + 1;
            node -> right = xoayphai(node -> right);
//            count = count + 2;
//            if (count >= 4) return node;
            node = xoaytrai(node);
        }
        return node;
    }

    Node* balanceTree(Node* node, int& count)
    {
        if (count == 1 || node == NULL) return node;
        node = balanceNode(node,count);
        node -> left = balanceTree(node -> left,count);
        node -> right = balanceTree(node -> right, count);
        return node;
    }
    Node* buildHuff(vector<pair<char, int>> freq)
    {
        vector<Node*> build;
        for(int i = 0; i < freq.size(); i++){
            
            build.emplace_back(new Node(freq[i].second,freq[i].first));
        }

        while(build.size() > 1)
        {
            int count = 0;
            Node*nhoI = build.back();
            build.pop_back();
            Node*nhoII = build.back();
            build.pop_back();
            Node*newNode = new Node(nhoI->weight + nhoII->weight,'\0',nhoI,nhoII);
              
//        Node* newNode = nullptr;
            newNode = balanceTree(newNode,count);
            count = 0;
            newNode = balanceTree(newNode,count);
            count = 0;
            newNode = balanceTree(newNode,count);
//            if ((static_cast<int>(newNode -> c) >= 65 && static_cast<int>(newNode -> c) <= 90)
//                || (static_cast<int>(newNode -> c) >= 97 && static_cast<int>(newNode -> c) <= 122) ) return NULL;
            if (build.size() != 0){
                int vitri = build.size();
                for(int i = 0; i < build.size(); i++){
                    if (build[i]->weight <= newNode -> weight){
                        vitri = i;
                        break;
                    }
                }
                build.insert(build.begin() + vitri, newNode);
            }
            else{
                build.insert(build.begin() + 0, newNode);
            }
            //sort(build.begin(),build.end(),xep);
        }
//    for(int i = 0; i <= build.size(); i++){
//        int count = 0;
//        build[i] = balanceTree(build[i], count);
//    }

        return build[0];
    }
    void mahoa_rec(vector<string>& encoding, Node* node, string s = "")
    {
        if (node == NULL) return;
        if (node -> left == NULL && node -> right == NULL) {
            encoding[node -> c] = s;
        }
        mahoa_rec(encoding,node -> left, s + '0');
        mahoa_rec(encoding,node -> right, s + '1');
    }
    int mahoa(Node * root,string nameCaesar)
    {
        if(root->left == nullptr && root->right == nullptr) return 0;

        vector<string> encoding(256, "");
        mahoa_rec(encoding, root);

        string binary = "";
        for(int i = nameCaesar.length() - 1; i >= 0; i--){
            if (binary.length() <= 10){
                binary = encoding[nameCaesar[i]] + binary;
            }
            else{
                break;
            }
        }
        if (binary.length() > 10){
            binary = binary.substr(binary.length() - 10, 10);
        }
        reverse(binary.begin(),binary.end());
        int result = 0;
        result = stoi(binary, nullptr, 2);

        return result;
    }

    int encode(string name){
        vector<pair<char, int>> freq  = this->xulychuoi(name);
        if(freq.size() == 0) return -1;
        this->clear(vaodaukhuvuc);
        vaodaukhuvuc = this->buildHuff(freq);
        if(vaodaukhuvuc->left == nullptr && vaodaukhuvuc->right == nullptr) return 0;
        return this->mahoa(vaodaukhuvuc ,name);
    }

    void print_recursive(Node* node){
        if(node == nullptr) return;
        print_recursive(node->left);
        if(node->c == '\0') solution << node->weight << "\n";
        else solution << node->c << "\n";
        print_recursive(node->right);
    }
    void print_HAND(){
        print_recursive(vaodaukhuvuc);
    }

private:
    class Node{
    public:
        int weight;
        char c;
        Node* left;
        Node* right;
        friend class HuffTree_AVL;
    public:
        Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr ):  weight(weight), c(c), left(left), right(right) {}
    };
};



class thucthi
{
private:
    HuffTree_AVL khachhangmoi;
    nhahangGojo hash;
    nhahangSukuna heap;

public:

    void LAPSE(string name)
    {

        if(name[0] >= '0' && name[0] <= '9') //! BỎ lúc nộp
        {
            int result = stoi(name);
            if(result % 2 == 1) hash.tinhID(result);
            else heap.tinhID(result);
            return;
        }

        int result = khachhangmoi.encode(name);
        if(result == -1) return;

        if(result % 2 == 1) hash.tinhID(result);
        else heap.tinhID(result);
    }

    //của nhà hàng gojo
    void KOKUSEN(){
        hash.KOKUSEN();
    }
    void LIMITLESS(int num){
        hash.print_LIMITLESS(num);
    }

    //của nhà hàng sukuna
    void KEITEIKEN(int num){
        heap.remove_KEITEIKEN(num);
    }
    void CLEAVE(int num){
        heap.print_LIMITLESS(num);
    }

    //in cây huff
    void HAND(){
        khachhangmoi.print_HAND();
    }
};



void simulate(string filename)
{
    ifstream ss(filename);
    string str, name;
    int num;

    ss >> str; ss >> MAXSIZE;

    thucthi* divaoham = new thucthi();

    while (ss >> str)
    {
        // LAPSE <NAME>
        if (str == "LAPSE")
        {
            ss >> name;
            divaoham->LAPSE(name);
        }
        // KOKUSEN
        else if (str == "KOKUSEN")
        {
            divaoham->KOKUSEN();
        }
        // KEITEIKEN <NUM>
        else if (str == "KEITEIKEN")
        {
            ss >> num;
            divaoham->KEITEIKEN(num);
        }
         // HAND
        else if (str == "HAND")
        {
            divaoham->HAND();
        }
        // LIMITLESS <NUM>
        else if (str == "LIMITLESS")
        {
            ss >> num;
            divaoham->LIMITLESS(num);
        }
        // CLEAVE <NUM>
        else if (str == "CLEAVE")
        {
            ss >> num;
            divaoham->CLEAVE(num);
        }
    }
    
    delete divaoham;
}