#include "main.h"

int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class nhahangGojo;
class nhahangSukuna;
class HuffTree;

// nhà hàng GOJO
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
		for(int i = 1; i < MAXSIZE + 1; i++) {
            khu_vuc[i].remove();
        }
 	}

	void print_LIMITLESS(int number)
	{
		if(number <= 0 || number > MAXSIZE) return;
		khu_vuc[number].print();
	}
public:
	class Tree_BST{
		class Node;
	public:
		Node* vaodaukhuvuc;
		queue<int> ttvaokhuvuc;
        int a[1005][1005];
	public:
		Tree_BST():vaodaukhuvuc(nullptr){

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
        Node* min(Node*root){
            Node* temp = root;
            while(temp && temp->left != NULL){
                temp = temp->left;
            }
            return temp;
        }
    /////////////////////////////////////////////////////////////////////////
		Node* xoa(Node* root,int result)
		{
			//TODO TODO TODO  TODO TODO TODO
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
                    else a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
                }
            }
        }

        unsigned long long DFS(Node* node)
        {
            if (node == NULL) return 1;
            if (sokhachkv(node) <= 2) return 1;
            mangchinhhop();
            return a[sokhachkv(node) - 1][sokhachkv(node -> left)]*DFS(node -> right)*DFS(node -> left);
        }

		void remove(){
			if(this->size() == 0 || this->size() == 1) return;
			unsigned long long canxoa = DFS(vaodaukhuvuc) % MAXSIZE;
			while(canxoa != 0 && !ttvaokhuvuc.empty())
			{
				int temp = ttvaokhuvuc.front();
				ttvaokhuvuc.pop();
				vaodaukhuvuc = xoa(vaodaukhuvuc ,temp);
				canxoa--;
			}
		}

		string print_recursive(Node* node)
		{
			if(node == nullptr) return "NULL";

			string left = print_recursive(node->left);
			solution << node->result << " ";
			string right = print_recursive(node->right);


			if(node->left == nullptr && node->right == nullptr) return to_string(node->result);
			return to_string(node->result)+"("+left +","+right+")";
		}
		void print(){
			if(this->size() == 0){
				solution << "EMPTY" ;
				return;
			}
			solution << "inoder: ";
			string s = print_recursive(vaodaukhuvuc);
			solution << "\nTree: " << s;
            std::queue<int> tempQueue = ttvaokhuvuc;
            solution << "\nQueue: ";
            while (!tempQueue.empty()) {
                solution << tempQueue.front() << " ";
                tempQueue.pop();
            }
		}
	//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
	};
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// nhà hàng sukuna
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
        //TODO: với giá trị xét là luutrukhuvuc[index].size()
        //TODO: này là min heap nên luutrukhuvuc[index].size() nào bé hơn thì ở trên
        //TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khác vào gần nhất dùng list<Node* > LRU;
        //TODO: ví dụ khu A và khu B có số khách bằng nhau nếu khu A mới có khách vào thì so sánh min heap thì khu B đang nhỏ hơn khu A nên ở trên khu A
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

    void removeNode(Node* node)
    {
        //TODO:
        LRU.remove(node);
    }
public:
    nhahangSukuna(){}

    void insertluutrukhuvuc(int result)
    {
        int ID = result % MAXSIZE + 1;
        int index = -1;
        //TODO TODO TODO TODO TODO bước 1
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

    void remove_KEITEIKEN(int number)
    {
        if(luutrukhuvuc.size() <= 0) return;

        int numberRemove = number;
        while(luutrukhuvuc.size() != 0 && number != 0){
            solution << "remove customers in the area ID = " << luutrukhuvuc[0]->ID << ": ";
            luutrukhuvuc[0]->remove(numberRemove);
            solution << "\n";

            if(luutrukhuvuc[0]->size() == 0)
            {
                swap(luutrukhuvuc[0], luutrukhuvuc[luutrukhuvuc.size() - 1]);
                this->removeNode(luutrukhuvuc[luutrukhuvuc.size() - 1]);
                delete luutrukhuvuc[luutrukhuvuc.size() - 1];

                luutrukhuvuc.pop_back();
            }
            this->ReHeap_down(0);
            number --;
        }
    }

    void print_pre_order(int index, int number)
    {
        if(index >= this->luutrukhuvuc.size()) return;

        this->luutrukhuvuc[index]->print(number);
        print_pre_order(index * 2 + 1, number);
        print_pre_order(index * 2 + 2, number);
    }
    void print_CLEAVE(int number)
    {
        if(number <= 0) return;

        solution << "Heap : ";
        for(auto it : this->luutrukhuvuc)
        {
            int order = 0;
            for (auto ix : LRU) {
                if (ix == it) break;
                ++order;
            }
            solution << it->ID << "(len="<< it->size() <<",index=" << order <<")" << " ";
        }
        solution << "\n";

        solution << "Heap : ";
        for(auto it : this->luutrukhuvuc) solution << it->ID  << " ";
        solution << "\n";

        solution << "list LRU : ";
        for(auto it : LRU) solution << it->ID << " ";
        solution << "\n";


        print_pre_order(0, number);
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
        void remove(int number)
        {
            for(int i = 0; i < number && !head.empty(); ++i){
                solution << head.back() << " ";
                head.pop_back();
            }
        }
        void print(int number)
        {
            solution << "customers in the area ID = " << ID << ": ";
            for(list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
            {
                solution << *it << " ";
            }
            solution << "\n";
        }
    };
};

class HuffTree{
    class Node;
private:
    Node* root = nullptr;
public:
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
    vector<pair<char, int>> string_Processing(string& name)
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
        //TODO: Rotate and return new root after rotate
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
        //TODO: Rotate and return new root after rotate
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
            node -> left = xoaytrai(node -> left);
            count = count + 2;
            if (count >= 4) return node;
            node = xoayphai(node);
        }
        else if (balance < -1 && taobalance(node -> right) > 0){
            node -> right = xoayphai(node -> right);
            count = count + 2;
            if (count >= 4) return node;
            node = xoaytrai(node);
        }
        return node;
    }

//* tiến hành đệ quy theo preOrder -> nếu count >= 3 thì dừng lại không cân bằng nữa
    Node* balanceTree(Node* node, int& count)
    {
        //TODO
        if (count >= 3 || node == NULL) return node;
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
    void encodingHuffman_rec(vector<string>& encoding, Node* node, string s = "")
    {
        //TODO
        if (node == NULL) return;
        if (node -> left == NULL && node -> right == NULL) {
            encoding[node -> c] = s;
        }
        encodingHuffman_rec(encoding,node -> left, s + '0');
        encodingHuffman_rec(encoding,node -> right, s + '1');
    }
    int encodingHuffman(Node * root,string nameCaesar)
    {
        if(root->left == nullptr && root->right == nullptr) return 0;

        vector<string> encoding(256, "");
        encodingHuffman_rec(encoding, root);

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
        //TODO
        result = stoi(binary, nullptr, 2);

        return result;
    }


    int encode(string name){

        if(name.length() < 3) return -1;
        vector<pair<char, int>> freq = this->string_Processing(name);
        solution << "freq     : {";
        for (int i = 0; i <freq.size();i++){
            if(i == freq.size() - 1)  solution << "{" <<"'"<< freq[i].first <<"'" << "," << freq[i].second << "}";
            else  solution << "{" <<"'"<< freq[i].first <<"'" << "," << freq[i].second << "},";
        }
        solution << "}"<<endl;
        root = this->buildHuff(freq);

        if(root->left == nullptr && root->right == nullptr) return 0; //! trường hợp chỉ có 1 node
        this->print();

        solution << "name   = " << name << endl;
        int result = this->encodingHuffman(root ,name);
        solution << "result = " << result << endl;
        return -1;
    }


    void rec_print(const Node* tree) {
        if (tree == nullptr) {
            return;
        }
        if(tree->c) solution << "[" << tree->weight << "," << tree->c << "]";
        else solution << "[" << tree->weight << "]";

        if (tree->left != nullptr || tree->right != nullptr) {
            solution << "(";
            rec_print(tree->left);
            solution << ",";
            rec_print(tree->right);
            solution << ")";
        }
    }

    void print()
    {
        solution << "root : ";
        rec_print(root);
        solution << '\n';
    }

private:
    class Node{
    public:
        int weight;
        char c;
        Node* left;
        Node* right;
        friend class HuffTree;
    public:
        Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr ): weight(weight), c(c), left(left), right(right) {}
    };
};


class JJK_RESTAURANT_OPERATIONS
{
private:
    HuffTree New_customers_arrive;
    nhahangGojo hash;
    nhahangSukuna heap;

public:

    void LAPSE(string name)
    {
        int result = New_customers_arrive.encode(name);
        return;
    }

    // xử lí nhà hàng gojo
    void KOKUSEN(){}
    void LIMITLESS(int num){}

    // xử lí nhà hàng Sukuna
    void KEITEIKEN(int num){}
    void CLEAVE(int num){}

    // xử lý HuffTree
    void HAND(){New_customers_arrive.print();}
};