#include "main.h"

int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class nhahangGojo;
class nhahangSakuna;
class HuffTree;

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
		//* tới khu number kêu nhân viên liệt kê tất cả khách hàng ra 
		if(number <= 0 || number > MAXSIZE) return; //! quá kí tự
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

		//* nhân viên sẽ liệt kê ra các khách hàng gián điệp để dễ dàng đuổi
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
	//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//^hàm in ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* hàm này theo trung thứ tự (in-order) thôi không gì khó hết
		string print_recursive(Node* node)
		{
			if(node == nullptr) return "NULL"; //! trường hợp dừng print

			string left = print_recursive(node->left);
			solution << node->result << " ";
			string right = print_recursive(node->right);
			

			if(node->left == nullptr && node->right == nullptr) return to_string(node->result); //! tr
			return to_string(node->result)+"("+left +","+right+")";
		}
		void print(){
			//! trường hợp rỗng bỏ qua
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class nhahangSakuna{
    class Node;
private:
    vector<Node* > luutrukhuvuc;  //! nơi lưu trữ các khu vực
    list<Node* > LRU; 		  //!  Least Recently Used này là cơ chế khu vực nào có khác vào nhà hàng lâu nhất
private:

    //* hàm gợi ý của anh thôi dùng hay không thì tùy các bạn nha -> nên suy nghĩ khác
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
//    bool Compere(int index1, int index2)
//    {
//
//    }

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
        //TODO: với giá trị xét là luutrukhuvuc[index].size()
        //TODO: này là min heap nên luutrukhuvuc[index].size() nào bé hơn thì ở trên
        //TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khác vào gần nhất
        //TODO: này xử lí tương tự reheap_down
        int cha = (index - 1) / 2;
        if(index == 0 || (luutrukhuvuc[index] -> size() > luutrukhuvuc[cha] -> size()) ||
           (luutrukhuvuc[index] -> size() == luutrukhuvuc[cha] -> size() && vitri(luutrukhuvuc[index]) < vitri(luutrukhuvuc[cha]))) {
            return;
        }
        swap(luutrukhuvuc[index], luutrukhuvuc[cha]);
        ReHeap_up(cha);
    }

    //* nếu node chưa tồn tại trong LRU thì thêm vô nếu tồn tại thì dịch nó lên đầu danh sách
    void moveTop(Node* node)
    {
        LRU.remove(node);
        LRU.push_front(node);
    }

    //* xóa một node ra khỏi danh sách liên kết không gần gọi delete nha vì đã dùng bên dưới hàm xóa
    void removeNode(Node* node)
    {
        //TODO:
        LRU.remove(node);
    }
public:
    nhahangSakuna(){}

    void insertluutrukhuvuc(int result)
    {
        int ID = result % MAXSIZE + 1;
        //*bước 1: kiểm tra xem heap có đang quản lí khu ID hay không nếu chưa quản lí thì phải thêm ở bước sau
        int index = -1;
        //TODO TODO TODO TODO TODO bước 1
        for(int i = 0; i < luutrukhuvuc.size(); i++){
            if (luutrukhuvuc[i] -> ID == ID){
                index = i;
                break;
            }
        }

        //*bước 2: xem thử có khu này trong heap chưa để thêm vô
        if(index == -1){
            luutrukhuvuc.push_back(new Node(ID));
            index = luutrukhuvuc.size() - 1;
            luutrukhuvuc[index]->insert(result);
            this->moveTop(luutrukhuvuc[index]);
            this->ReHeap_up(index);
        }
            //*bước 3: thêm khách hàng mới vào khu khách hàng muốn thêm vào và tiến hàn reheap down bàn này xuống vì có số khách đông hơn
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

        //* đuổi num khách hàng tại num khu vực
        int numberRemove = number;
        while(luutrukhuvuc.size() != 0 && number != 0){
            //* lấy ra khu đang ở đầu đầu heap xóa number khách hàng đầu linklist
            solution << "remove customers in the area ID = " << luutrukhuvuc[0]->ID << ": ";
            luutrukhuvuc[0]->remove(numberRemove);
            solution << "\n";

            //* trường hợp xóa hết thì xóa nó trong heap sau đó reheap down khu xuống vì đang ở đầu hàng
            if(luutrukhuvuc[0]->size() == 0)
            {
                swap(luutrukhuvuc[0], luutrukhuvuc[luutrukhuvuc.size() - 1]);
                //! xóa nó khỏi danh sách liên kết
                this->removeNode(luutrukhuvuc[luutrukhuvuc.size() - 1]);
                delete luutrukhuvuc[luutrukhuvuc.size() - 1];

                //! xóa trong heap nữa
                luutrukhuvuc.pop_back();
            }
            this->ReHeap_down(0);
            number --;
        }
    }
//^hàm in ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
    class Node{
    private:
        int ID;					//! ID của bàn đó
        list<int> head; 		//! lưu danh sách các result của khách hàng
        friend class nhahangSakuna;
    public:
        Node(int ID) : ID(ID) {}
        int size() const { return head.size(); }
        //* thêm vô đầu danh sách
        void insert(int result){head.push_front(result);}
        //* xóa ở cuối với số lượng là number cơ chế FIFO vô sớm thì cút sớm
        void remove(int number)
        {
            //TODO: xóa number khác hàng ở cuối danh sách tương ứng với vô sớm nhất
            //^ gợi ý dùng hàm của linklist có sẵn
            //* thêm solution << head.back() << " "; để in ra
            for(int i = 0; i < number && !head.empty(); ++i){
                solution << head.back() << " ";
                head.pop_back();
            }
        }
        //* print ra number khách hàng mới đến gần nhất theo cơ chế LIFO các khách hàng gần nhất
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
    Node* root;
public:
    int encode(string name){
        return stoi(name);
    }

    void print(){}
private:
    class Node{
    public:
        int weight;
        char c;
        int rankingPosition;
        Node* left;
        Node* right;
        friend class HuffTree_AVL;
    public:
        Node(int weight, char c,Node* left = nullptr, Node* right = nullptr ): weight(weight), c(c), left(left), right(right) {}
        bool isLeaf() const { return left == nullptr && right == nullptr; }
    };
};

class JJK_RESTAURANT_OPERATIONS
{
private:
    HuffTree New_customers_arrive;
    nhahangGojo hash;
    nhahangSakuna heap;

public:

    void LAPSE(string name)
    {
        //* mã hóa HuffTree kế quả là 10 kí tự nhị phân cuối chuyển sang thập phân
        int result = New_customers_arrive.encode(name);

        //* phân chia nhà hàng 
        if(result % 2 == 1) hash.tinhID(result);
        else heap.insertluutrukhuvuc(result);
    }

    //* xử lí nhà hàng gojo
    void KOKUSEN(){hash.KOKUSEN();}
    void LIMITLESS(int num){hash.print_LIMITLESS(num);}

    //* xử lí nhà hàng Sukuna
    void KEITEIKEN(int num){heap.remove_KEITEIKEN(num);}
    void CLEAVE(int num){heap.print_CLEAVE(num);}

    //* xử lý HuffTree
    void HAND(){New_customers_arrive.print();}
};


