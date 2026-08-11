// QUAN LY XE BUS - De 2 | MSSV: .......... Ho ten: ..........
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace std;
struct Bus { string licensePlate, driverName, start, dest; int num; };
const string F1 = "data1.txt", F2 = "data2.txt", FSORT = "sortResult.txt", FTIME = "runtime_result.txt";
const char D = '|';
string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    return s.substr(a, s.find_last_not_of(" \t\r\n") - a + 1);
}
Bus* readData(const string& fn, int& n) {
    ifstream fin(fn);
    if (!fin) { n = 0; return nullptr; }
    string line; n = 0;
    while (getline(fin, line)) if (!trim(line).empty()) n++;
    fin.clear(); fin.seekg(0);
    Bus* a = new Bus[n];
    int i = 0;
    while (getline(fin, line)) {
        if (trim(line).empty()) continue;
        stringstream ss(line); string f[5];
        for (int k = 0; k < 5 && getline(ss, f[k], D); k++);
        a[i] = { trim(f[0]), trim(f[1]), trim(f[2]), trim(f[3]), atoi(trim(f[4]).c_str()) };
        i++;
    }
    return a;
}
void writeData(const string& fn, Bus a[], int n) {
    ofstream fout(fn);
    for (int i = 0; i < n; i++)
        fout << a[i].licensePlate << D << a[i].driverName << D << a[i].start << D
        << a[i].dest << D << a[i].num << (i < n - 1 ? "\n" : "");
}
bool validPlate(const string& s) {
    if (s.size() != 10) return false;
    return isdigit((unsigned char)s[0]) && isdigit((unsigned char)s[1]) && isupper((unsigned char)s[2]) &&
        s[3] == '-' && isdigit((unsigned char)s[4]) && isdigit((unsigned char)s[5]) &&
        isdigit((unsigned char)s[6]) && s[7] == '.' && isdigit((unsigned char)s[8]) && isdigit((unsigned char)s[9]);
}
void checkAndFixPlates(Bus a[], int n, const string& fn) {
    bool changed = false;
    for (int i = 0; i < n; i++) {
        if (validPlate(a[i].licensePlate)) continue;
        cout << "\nXe " << i + 1 << " (" << a[i].driverName << ") bien so \"" << a[i].licensePlate << "\" SAI dinh dang.\n";
        string np;
        while (true) {
            cout << "Nhap lai (vd 29B-123.45): ";
            if (!getline(cin, np)) { cout << "(Bo qua do het du lieu nhap)\n"; break; }
            np = trim(np);
            if (validPlate(np)) { a[i].licensePlate = np; changed = true; break; }
        }
    }
    if (changed) { writeData(fn, a, n); cout << "\nDa luu lai " << fn << "\n"; }
    else cout << "\nTat ca bien so deu hop le.\n";
}
void printList(Bus a[], int n) {
    cout << left << setw(14) << "Bien so" << setw(22) << "Ten tai xe" << setw(15) << "Xuat phat"
        << setw(15) << "Den" << "So cho\n" << string(72, '-') << "\n";
    for (int i = 0; i < n; i++)
        cout << left << setw(14) << a[i].licensePlate << setw(22) << a[i].driverName
        << setw(15) << a[i].start << setw(15) << a[i].dest << a[i].num << "\n";
}
void sw(Bus& x, Bus& y) { Bus t = x; x = y; y = t; }

void interchangeSort(Bus a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i].driverName > a[j].driverName) sw(a[i], a[j]);
}
void selectionSort(Bus a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++) if (a[j].driverName < a[m].driverName) m = j;
        if (m != i) sw(a[i], a[m]);
    }
}
void insertionSort(Bus a[], int n) {
    for (int i = 1; i < n; i++) {
        Bus key = a[i]; int j = i - 1;
        while (j >= 0 && a[j].driverName > key.driverName) { a[j + 1] = a[j]; j--; }
        a[j + 1] = key;
    }
}
void bubbleSort(Bus a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool s = false;
        for (int j = 0; j < n - 1 - i; j++)
            if (a[j].driverName > a[j + 1].driverName) { sw(a[j], a[j + 1]); s = true; }
        if (!s) break;
    }
}
int partitionQS(Bus a[], int lo, int hi) {
    string pivot = a[hi].driverName; int i = lo - 1;
    for (int j = lo; j < hi; j++) if (a[j].driverName <= pivot) sw(a[++i], a[j]);
    sw(a[i + 1], a[hi]);
    return i + 1;
}
void quickSortRec(Bus a[], int lo, int hi) {
    if (lo < hi) { int p = partitionQS(a, lo, hi); quickSortRec(a, lo, p - 1); quickSortRec(a, p + 1, hi); }
}
void quickSort(Bus a[], int n) { if (n > 1) quickSortRec(a, 0, n - 1); }

void heapify(Bus a[], int n, int i) {
    int lg = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && a[l].driverName > a[lg].driverName) lg = l;
    if (r < n && a[r].driverName > a[lg].driverName) lg = r;
    if (lg != i) { sw(a[i], a[lg]); heapify(a, n, lg); }
}
void heapSort(Bus a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(a, n, i);
    for (int i = n - 1; i > 0; i--) { sw(a[0], a[i]); heapify(a, i, 0); }
}
void shellSort(Bus a[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            Bus t = a[i]; int j = i;
            while (j >= gap && a[j - gap].driverName > t.driverName) { a[j] = a[j - gap]; j -= gap; }
            a[j] = t;
        }
}
void mergeArr(Bus a[], int lo, int mid, int hi) {
    int n1 = mid - lo + 1, n2 = hi - mid;
    Bus* L = new Bus[n1], * R = new Bus[n2];
    for (int i = 0; i < n1; i++) L[i] = a[lo + i];
    for (int j = 0; j < n2; j++) R[j] = a[mid + 1 + j];
    int i = 0, j = 0, k = lo;
    while (i < n1 && j < n2) a[k++] = (L[i].driverName <= R[j].driverName) ? L[i++] : R[j++];
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
    delete[] L; delete[] R;
}
void mergeSortRec(Bus a[], int lo, int hi) {
    if (lo < hi) { int mid = (lo + hi) / 2; mergeSortRec(a, lo, mid); mergeSortRec(a, mid + 1, hi); mergeArr(a, lo, mid, hi); }
}
void mergeSort(Bus a[], int n) { if (n > 1) mergeSortRec(a, 0, n - 1); }

Bus* cloneArr(Bus a[], int n) { Bus* c = new Bus[n]; for (int i = 0; i < n; i++) c[i] = a[i]; return c; }

typedef void (*SortFn)(Bus[], int);
struct Algo { string name; SortFn fn; };
Algo ALGOS[8] = {
    {"Interchange Sort", interchangeSort}, {"Selection Sort", selectionSort},
    {"Insertion Sort", insertionSort},     {"Bubble Sort", bubbleSort},
    {"Quick Sort", quickSort},             {"Heap Sort", heapSort},
    {"Shell Sort", shellSort},             {"Merge Sort", mergeSort}
};
void sortAndExport(Bus a[], int n) {
    if (n == 0) { cout << "Rong.\n"; return; }
    cout << "\nChon thuat toan:\n";
    for (int i = 0; i < 8; i++) cout << i + 1 << ". " << ALGOS[i].name << "\n";
    int c; cin >> c; cin.ignore();
    if (c < 1 || c > 8) { cout << "Khong hop le!\n"; return; }
    Bus* t = cloneArr(a, n);
    ALGOS[c - 1].fn(t, n);
    printList(t, n);
    writeData(FSORT, t, n);
    cout << "Da xuat " << FSORT << "\n";
    delete[] t;
}
void searchByStart(Bus a[], int n) {
    cout << "Nhap noi xuat phat: ";
    string place; getline(cin, place); place = trim(place);
    bool found = false;
    cout << left << setw(14) << "Bien so" << setw(22) << "Ten tai xe" << setw(15) << "Xuat phat"
        << setw(15) << "Den" << "So cho\n" << string(72, '-') << "\n";
    for (int i = 0; i < n; i++)
        if (a[i].start == place) {
            cout << left << setw(14) << a[i].licensePlate << setw(22) << a[i].driverName
                << setw(15) << a[i].start << setw(15) << a[i].dest << a[i].num << "\n";
            found = true;
        }
    if (!found) cout << "Khong tim thay.\n";
}
int countUnder30(Bus a[], int n) {
    int c = 0;
    for (int i = 0; i < n; i++) if (a[i].num < 30) c++;
    return c;
}
void generateRandomData(const string& fn, int n) {
    string fname[] = { "Nguyen","Tran","Le","Pham","Hoang","Huynh","Phan","Vu","Vo","Dang","Bui","Do","Ngo","Duong","Ly" };
    string mname[] = { "Van","Thi","Huu","Duc","Minh","Ngoc","Thanh","Cong","Quang","Kim" };
    string lname[] = { "An","Binh","Cuong","Dung","Em","Phong","Giang","Hoa","Iem","Khanh","Linh","Mai","Nam","Oanh","Phuc","Quyen","Son","Tam","Uyen","Viet" };
    string city[] = { "Ha Noi","Sai Gon","Da Nang","Hue","Can Tho","Bien Hoa","Vung Tau","Nha Trang","Da Lat","Hai Phong","Quy Nhon","Vinh","Buon Ma Thuot","My Tho" };
    ofstream fout(fn);
    for (int i = 0; i < n; i++) {
        stringstream plate;
        plate << setfill('0') << setw(2) << rand() % 100 << char('A' + rand() % 26) << "-"
            << setfill('0') << setw(3) << rand() % 1000 << "." << setfill('0') << setw(2) << rand() % 100;
        string driver = fname[rand() % 15] + " " + mname[rand() % 10] + " " + lname[rand() % 20];
        string s = city[rand() % 14], d;
        do { d = city[rand() % 14]; } while (d == s);
        fout << plate.str() << D << driver << D << s << D << d << D << (16 + rand() % 35) << (i < n - 1 ? "\n" : "");
    }
    cout << "Da sinh " << n << " ban ghi vao " << fn << "\n";
}
void measureRuntime() {
    int n; Bus* data = readData(F2, n);
    if (!data || n == 0) { cout << "Chua co " << F2 << ", hay sinh du lieu truoc.\n"; return; }
    double t[8];
    ofstream fout(FTIME);
    fout << "KET QUA DO THOI GIAN 8 THUAT TOAN (n=" << n << ")\n" << left << setw(20) << "Thuat toan" << "Thoi gian (ms)\n";
    for (int i = 0; i < 8; i++) {
        Bus* tmp = cloneArr(data, n);
        auto t0 = chrono::high_resolution_clock::now();
        ALGOS[i].fn(tmp, n);
        auto t1 = chrono::high_resolution_clock::now();
        t[i] = chrono::duration<double, milli>(t1 - t0).count();
        delete[] tmp;
        cout << left << setw(20) << ALGOS[i].name << fixed << setprecision(3) << t[i] << " ms\n";
        fout << left << setw(20) << ALGOS[i].name << fixed << setprecision(3) << t[i] << "\n";
    }
    cout << "Da luu " << FTIME << "\n";
    delete[] data;
}
int main() {
    srand((unsigned)time(0));
    int n = 0;
    Bus* buses = readData(F1, n);
    cout << "Da doc " << n << " ban ghi tu " << F1 << "\n";

    int c;
    do {
        cout << "\n QUAN LY XE BUS\n"
            << "1. Kiem tra/sua bien so\n2. In danh sach\n3. Sap xep , xuat sortResult.txt\n"
            << "4. Tim theo noi xuat phat\n5. Dem xe < 30 cho\n6. Sinh du lieu ngau nhien n=1000\n"
            << "7. Do thoi gian 8 thuat toan\n0. Thoat\nChon: ";
        cin >> c; cin.ignore();
        switch (c) {
        case 1: checkAndFixPlates(buses, n, F1); break;
        case 2: printList(buses, n); break;
        case 3: sortAndExport(buses, n); break;
        case 4: searchByStart(buses, n); break;
        case 5: cout << "So xe < 30 cho: " << countUnder30(buses, n) << "\n"; break;
        case 6: generateRandomData(F2, 1000); break;
        case 7: measureRuntime(); break;
        case 0: cout << "Bye\n"; break;
        default: cout << "Lua chon khong hop le!\n";
        }
    } while (c != 0);

    delete[] buses;
    return 0;
}