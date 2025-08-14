#include <bits/stdc++.h>

using namespace std;

class Book{
	public:
	string name;
	string author;
	double p;
	int id;
	bool iss;
	
	Book(){}
	Book(string name,string author,double p,int id){
		this->name = name;
		this->author = author;
		this->p = p;
		this->id = id;
		this->iss = false;
	}
};

class Library {
private:
	
    Library() {} 

public:
    map<int, Book*> books;

    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;

    static Library& getInstance() {
        static Library instance; 
        return instance;
    }

    void addBook(string name, string author, double p, int id) {
        books[id] = new Book(name, author, p, id);
        cout << "Book added\n";
        cout << "Total books: " << books.size() << endl;
    }

    ~Library() {
        for (auto &b : books) {
            delete b.second;
        }
    }
};


 class Member{
 	public:
 	string name;
	int id;
	int std;
	// int b_id;
	bool iss;
	
	Member(){}
	
	Member(string name, int id, int std){
		this->name = name;
		this->id = id;
		this->std = std;
		iss = false;
	}
 };
 
 class Membermng{
 	private:
 	
 	Membermng(){}
 	
 	public:
 	map<int,Member*> members;
	Membermng(const Membermng&) = delete;
    Membermng& operator=(const Membermng&) = delete;

    static Membermng& getInstance() {
        static Membermng instance; 
        return instance;
    }
    
	
	void addMember(string name, int id, int std){
		members[id] = new Member(name,id,std);
		cout<<"member added"<<endl;
		cout << "Total members: " << members.size() << endl;
	}
	
	~Membermng() {
        for (auto &m : members) {
            delete m.second;
        }
    }
 };

class Issue {
private:
    map<int, int> issuedBooks; 
    Issue() {} 

public:
    Issue(const Issue&) = delete;
    Issue& operator=(const Issue&) = delete;

    static Issue& getInstance() {
        static Issue instance;
        return instance;
    }

    void issueBook(int memberId, int bookId) {
        Library& lib = Library::getInstance();
        Membermng& mm = Membermng::getInstance();

        if (lib.books.find(bookId) == lib.books.end()) {
            cout << "Book not found!\n";
            return;
        }
        if (mm.members.find(memberId) == mm.members.end()) {
            cout << "Member not found!\n";
            return;
        }

        Book* book = lib.books[bookId];
        Member* mem = mm.members[memberId];

        if (book->iss) {
            cout << "Book already issued!\n";
            return;
        }
        if (mem->iss) {
            cout << "Member already has a book issued!\n";
            return;
        }

        book->iss = true;
        mem->iss = true;
        issuedBooks[memberId] = bookId;

        cout << "Book issued successfully!\n";
    }

    void returnBook(int memberId) {
        Library& lib = Library::getInstance();
        Membermng& mm = Membermng::getInstance();

        if (issuedBooks.find(memberId) == issuedBooks.end()) {
            cout << "This member has no issued books!\n";
            return;
        }

        int bookId = issuedBooks[memberId];
        Book* book = lib.books[bookId];
        Member* mem = mm.members[memberId];

        book->iss = false;
        mem->iss = false;
        issuedBooks.erase(memberId);

        cout << "Book returned successfully!\n";
    }

    void displayIssuedBooks() {
        if (issuedBooks.empty()) {
            cout << "No books are issued.\n";
            return;
        }
        cout << "Issued Books:\n";
        for (auto& entry : issuedBooks) {
            cout << "Member ID: " << entry.first
                 << " -> Book ID: " << entry.second << endl;
        }
    }
};
	
int main() {
    Library& lib = Library::getInstance();
    Membermng& mm = Membermng::getInstance();
    Issue& iss = Issue::getInstance();

    lib.addBook("C++ Primer", "Lippman", 45.5, 101);
    lib.addBook("Effective C++", "Scott Meyers", 55.0, 102);

    mm.addMember("Shiva", 1, 12);
    mm.addMember("Raghav", 2, 11);

    iss.issueBook(1, 101);
    iss.issueBook(2, 102);
    iss.displayIssuedBooks();

    iss.returnBook(1);
    iss.displayIssuedBooks();
}

