#include <iostream>
using namespace std;
class Student {
	char* name;
	int age;
public:
	Student(const char* n, int a) : name(_strdup(n)), age(a) {
		cout << "Construct with parametr;" << endl;
	}
	Student() {
		name = 0;
		age = 0;
	}
	~Student() {
		//delete[]name;
		cout << "Delete obj\n";
	}
	void Print() {
		cout << "Name : " << name << endl;
		cout << "Age : " << age << endl;
	}
	Student(const Student& st) {
		cout << "Copy construct" << endl;
		name = _strdup(st.name);
		age = st.age;
	}
	Student& operator = (const Student& st) { // навчили виконувати дію " = "
		cout << "Operator = \n";
		if (&st != this) {
			delete[]name;
			name = _strdup(st.name);
			age = st.age;
		}
		return *this;
	}
	const char* getName() {
		return name;
	}
	int getAge() {
		return age;
	}
};
class Group {
private:
	int N; // кількість в масиві
	Student* st;
	char* name;
public:
	Group(const char* n) : name(_strdup(n)), N(0), st(0) {
	}
	~Group() {
		delete[]name;
		delete[]st;
		cout << "Delete obj\n";
	}
	void Push(const Student& s) {
		Student* nst = new Student[N + 1];
		for (size_t i = 0; i < N; i++)
			nst[i] = st[i];
		delete[]st;
		st = nst;
		st[N] = s;
		N++;
	}
	void Push() {
		cout << "Enter name: ";
		char buf[50];
		cin >> buf;
		int a;
		cout << "Enter age: ";
		cin >> a;
		Push(Student(buf, a));
	}
	void Print() {
		cout << "Name" << name << endl;
		cout << "Count: " << N << endl;
		for (size_t i = 0; i < N; i++) {
			st[i].Print();
		}
	}
	void Delete(int a) { // переписати 
		Student* nst = new Student[N - 1];

		for (size_t i = 0; i < N; i++)



			nst[i] = st[i];
		delete[]st;
		st = nst;
		N--;
	}
	void Save(const char* fn) { // fn - filename
		FILE* fs;
		if (fopen_s(&fs, fn, "wb")) {
			cout << "Error";
			return;
		}
		int len = name ? strlen(name) : 0;
		fwrite(&len, sizeof(len), 1, fs);
		fwrite(name, len, 1, fs);
		fwrite(&N, sizeof(N), 1, fs);
		for (int i = 0; i < N; i++) {
			len = st[i].getName() ? strlen(st[i].getName()) : 0; //дописати гетеры для студентывських полыв роки та імя
			fwrite(st[i].getName(), len, 1, fs);
			len = st[i].getAge();
			fwrite(&len, sizeof(len), 1, fs);
		}
		fclose(fs);
	}
	void ShowRead(const char* fn) { // fn - filename //передивитись порядок в якому читаэться файл, бо не працюэ
		FILE* fs;
		if (fopen_s(&fs, fn, "rb")) {
			cout << "Error";
			return;
		}
		int len = name ? strlen(name) : 0;
		fread(&len, sizeof(len), 1, fs);
		fread(name, len, 1, fs);
		fread(&N, sizeof(N), 1, fs);
		delete[] st;
		st = new Student[N];
		for (int i = 0; i < N; i++) {
			//len = st[i].setName() ? strlen(st[i].getName()) : 0; //дописати гетеры та сетери для студентывських полыв роки та імя
			char* buf;
			fread(&len, sizeof(len), 1, fs);
			buf = new char[len + 1]{ 0 };
			fread(buf, len, 1, fs);
			fread(&len, sizeof(len), 1, fs);
			st[i] = Student(buf, len);
			delete[]buf;
		}
		fclose(fs);
	}

};

//*************************
void Show(Student s) {
	s.Print();
}
Student NewStud() {
	return Student("Ivan", 30); //k;
} //DB
int main() {
	Student A("Piter", 20); //k // 1 копія
	A.Print();
	//Show(A);
	Student N = NewStud();
	N.Print();
	Student B(A); // 2 копія
	Student C = B; // 3 копія
	A = B; // 4 
	B = B;
	B.Print();
	//************************
	Group PE911("PE911");
	PE911.Push(Student("Ivan", 30));
	cout << "*********************************************************" << endl;
	cout << "sizeof(PE911) = " << sizeof(PE911) << endl;
	cout << "*********************************************************" << endl;
	PE911.Print();
	cout << "*********************************************************" << endl;
	PE911.Push();
	PE911.Print();
	cout << "*********************************************************" << endl;
	cout << "sizeof(PE911) = " << sizeof(PE911) << endl;
	cout << "*********************************************************" << endl;
	PE911.Save("base.bin");
	PE911.ShowRead("base.bin");
} // DA, DN