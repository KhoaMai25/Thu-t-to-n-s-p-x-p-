#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;

// Lớp sản phẩm Laptop
class Laptop {
public:
    int id;
    string name;
    int price;
    int sold;
    float rating;

    Laptop() : id(0), name(""), price(0), sold(0), rating(0.0) {}

    void hienThi() {
        cout << setw(6) << id << " | "
            << setw(20) << name << " | "
            << setw(12) << price << " | "
            << setw(8) << sold << " | "
            << setw(6) << rating << endl;
    }
};

// Lớp quản lý danh sách laptop
class QuanLyLaptop {
private:
    Laptop* ds;
    int soLuong;
    int dungLuong;

    void moRongMang() {
        dungLuong *= 2;
        Laptop* moi = new Laptop[dungLuong];
        for (int i = 0; i < soLuong; i++) {
            moi[i] = ds[i];
        }
        delete[] ds;
        ds = moi;
    }

public:
    QuanLyLaptop() {
        dungLuong = 100;
        soLuong = 0;
        ds = new Laptop[dungLuong];
    }

    ~QuanLyLaptop() {
        delete[] ds;
    }

    // Đọc dữ liệu từ file
    void docFile(string tenFile) {
        ifstream f(tenFile);
        if (!f.is_open()) {
            cout << "Khong mo duoc file: " << tenFile << endl;
            cout << "Hay dam bao file ton tai trong thu muc hien tai!" << endl;
            return;
        }

        while (!f.eof()) {
            if (soLuong >= dungLuong) {
                moRongMang();
            }
            f >> ds[soLuong].id;
            f.ignore();
            getline(f, ds[soLuong].name);
            f >> ds[soLuong].price >> ds[soLuong].sold >> ds[soLuong].rating;
            if (f.good()) soLuong++;
        }
        f.close();
        cout << "Da doc " << soLuong << " san pham." << endl;
    }

    // Tạo dữ liệu mẫu
    void taoFile(string tenFile, int n) {
        ofstream f(tenFile);
        if (!f.is_open()) {
            cout << "Khong tao duoc file: " << tenFile << endl;
            return;
        }

        string brands[] = { "Dell", "HP", "Asus", "Lenovo", "Acer", "MSI" };
        string models[] = { "Inspiron", "Pavilion", "VivoBook", "ThinkPad", "Aspire", "Gaming" };

        for (int i = 1; i <= n; i++) {
            f << i << endl;
            f << brands[i % 6] << " " << models[i % 6] << " " << i << endl;
            f << (10000000 + (i * 123456) % 40000000) << " ";
            f << (50 + (i * 17) % 500) << " ";
            f << (3.0 + (i % 21) * 0.1) << endl;
        }
        f.close();
        cout << "Da tao file: " << tenFile << endl;
        cout << "File duoc luu tai thu muc hien tai cua chuong trinh." << endl;
        cout << "So luong san pham: " << n << endl;
    }

    // Hiển thị n sản phẩm đầu
    void hienThi(int n) {
        if (n > soLuong) n = soLuong;

        cout << "\n";
        cout << setw(6) << "ID" << " | "
            << setw(20) << "Ten" << " | "
            << setw(12) << "Gia" << " | "
            << setw(8) << "Da ban" << " | "
            << setw(6) << "Diem" << endl;
        cout << string(70, '-') << endl;

        for (int i = 0; i < n; i++) {
            ds[i].hienThi();
        }
        cout << endl;
    }

    // Sao chép mảng để test
    Laptop* saoChep() {
        Laptop* temp = new Laptop[soLuong];
        for (int i = 0; i < soLuong; i++) {
            temp[i] = ds[i];
        }
        return temp;
    }

    // ========== BUBBLE SORT ==========
    void bubbleSort(Laptop* arr, int n, int tieuChi) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                bool swap = false;

                if (tieuChi == 1) // Giá cao -> thấp
                    swap = arr[j].price < arr[j + 1].price;
                else if (tieuChi == 2) // Số lượng bán cao -> thấp
                    swap = arr[j].sold < arr[j + 1].sold;
                else if (tieuChi == 3) // Điểm thấp -> cao
                    swap = arr[j].rating > arr[j + 1].rating;
                else if (tieuChi == 4) // Tên A -> Z
                    swap = arr[j].name > arr[j + 1].name;

                if (swap) {
                    Laptop temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    // ========== SELECTION SORT ==========
    void selectionSort(Laptop* arr, int n, int tieuChi) {
        for (int i = 0; i < n - 1; i++) {
            int viTri = i;

            for (int j = i + 1; j < n; j++) {
                bool chon = false;

                if (tieuChi == 1)
                    chon = arr[j].price > arr[viTri].price;
                else if (tieuChi == 2)
                    chon = arr[j].sold > arr[viTri].sold;
                else if (tieuChi == 3)
                    chon = arr[j].rating < arr[viTri].rating;
                else if (tieuChi == 4)
                    chon = arr[j].name < arr[viTri].name;

                if (chon) viTri = j;
            }

            if (viTri != i) {
                Laptop temp = arr[i];
                arr[i] = arr[viTri];
                arr[viTri] = temp;
            }
        }
    }

    // ========== INTERCHANGE SORT ==========
    void interchangeSort(Laptop* arr, int n, int tieuChi) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                bool swap = false;

                if (tieuChi == 1) // Giá cao -> thấp
                    swap = arr[i].price < arr[j].price;
                else if (tieuChi == 2) // Số lượng bán cao -> thấp
                    swap = arr[i].sold < arr[j].sold;
                else if (tieuChi == 3) // Điểm thấp -> cao
                    swap = arr[i].rating > arr[j].rating;
                else if (tieuChi == 4) // Tên A -> Z
                    swap = arr[i].name > arr[j].name;

                if (swap) {
                    Laptop temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }

    // ========== INSERTION SORT ==========
    void insertionSort(Laptop* arr, int n, int tieuChi) {
        for (int i = 1; i < n; i++) {
            Laptop key = arr[i];
            int j = i - 1;

            while (j >= 0) {
                bool chen = false;

                if (tieuChi == 1)
                    chen = arr[j].price < key.price;
                else if (tieuChi == 2)
                    chen = arr[j].sold < key.sold;
                else if (tieuChi == 3)
                    chen = arr[j].rating > key.rating;
                else if (tieuChi == 4)
                    chen = arr[j].name > key.name;

                if (chen) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                else {
                    break;
                }
            }
            arr[j + 1] = key;
        }
    }

    // ========== QUICK SORT ==========
    int partition(Laptop* arr, int low, int high, int tieuChi) {
        Laptop pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            bool nhoHon = false;

            if (tieuChi == 1)
                nhoHon = arr[j].price > pivot.price;
            else if (tieuChi == 2)
                nhoHon = arr[j].sold > pivot.sold;
            else if (tieuChi == 3)
                nhoHon = arr[j].rating < pivot.rating;
            else if (tieuChi == 4)
                nhoHon = arr[j].name < pivot.name;

            if (nhoHon) {
                i++;
                Laptop temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        Laptop temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        return i + 1;
    }

    void quickSortHelper(Laptop* arr, int low, int high, int tieuChi) {
        if (low < high) {
            int pi = partition(arr, low, high, tieuChi);
            quickSortHelper(arr, low, pi - 1, tieuChi);
            quickSortHelper(arr, pi + 1, high, tieuChi);
        }
    }

    void quickSort(Laptop* arr, int n, int tieuChi) {
        quickSortHelper(arr, 0, n - 1, tieuChi);
    }

    // ========== MERGE SORT ==========
    void merge(Laptop* arr, int l, int m, int r, int tieuChi) {
        int n1 = m - l + 1;
        int n2 = r - m;

        Laptop* L = new Laptop[n1];
        Laptop* R = new Laptop[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;

        while (i < n1 && j < n2) {
            bool chonL = false;

            if (tieuChi == 1)
                chonL = L[i].price >= R[j].price;
            else if (tieuChi == 2)
                chonL = L[i].sold >= R[j].sold;
            else if (tieuChi == 3)
                chonL = L[i].rating <= R[j].rating;
            else if (tieuChi == 4)
                chonL = L[i].name <= R[j].name;

            if (chonL) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }

    void mergeSortHelper(Laptop* arr, int l, int r, int tieuChi) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSortHelper(arr, l, m, tieuChi);
            mergeSortHelper(arr, m + 1, r, tieuChi);
            merge(arr, l, m, r, tieuChi);
        }
    }

    void mergeSort(Laptop* arr, int n, int tieuChi) {
        mergeSortHelper(arr, 0, n - 1, tieuChi);
    }

    // Test thuật toán
    void testThuatToan(int tieuChi, string tenTieuChi) {
        cout << "\n========== Test: " << tenTieuChi << " ==========\n";

        string tenThuatToan[] = { "Bubble Sort", "Selection Sort", "Interchange Sort", "Insertion Sort", "Quick Sort", "Merge Sort" };
        double tongThoiGian[6] = { 0, 0, 0, 0, 0, 0 };

        // Chạy 5 lần mỗi thuật toán
        for (int lan = 0; lan < 5; lan++) {
            cout << "Lan chay " << (lan + 1) << "...\n";

            // Test từng thuật toán
            for (int thuat = 0; thuat < 6; thuat++) {
                Laptop* temp = saoChep();

                auto start = chrono::high_resolution_clock::now();

                if (thuat == 0) bubbleSort(temp, soLuong, tieuChi);
                else if (thuat == 1) selectionSort(temp, soLuong, tieuChi);
                else if (thuat == 2) interchangeSort(temp, soLuong, tieuChi);
                else if (thuat == 3) insertionSort(temp, soLuong, tieuChi);
                else if (thuat == 4) quickSort(temp, soLuong, tieuChi);
                else if (thuat == 5) mergeSort(temp, soLuong, tieuChi);

                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration = end - start;

                tongThoiGian[thuat] += duration.count();

                delete[] temp;
            }
        }

        // Hiển thị kết quả
        cout << "\nKet qua trung binh (5 lan):\n";
        cout << string(40, '-') << endl;
        for (int i = 0; i < 6; i++) {
            cout << setw(20) << tenThuatToan[i] << ": "
                << fixed << setprecision(2) << (tongThoiGian[i] / 5.0) << " ms" << endl;
        }
    }

    // Chạy tất cả test
    void chayTatCaTest() {
        testThuatToan(1, "Sap xep theo GIA (cao -> thap)");
        testThuatToan(2, "Sap xep theo SO LUONG BAN (cao -> thap)");
        testThuatToan(3, "Sap xep theo DIEM DANH GIA (thap -> cao)");
        testThuatToan(4, "Sap xep theo TEN (A -> Z)");
    }

    // Mở rộng: Sắp xếp theo sold, nếu bằng thì theo tên
    void sapXepSoldVaTen() {
        for (int i = 0; i < soLuong - 1; i++) {
            for (int j = 0; j < soLuong - i - 1; j++) {
                bool swap = false;

                if (ds[j].sold < ds[j + 1].sold) {
                    swap = true;
                }
                else if (ds[j].sold == ds[j + 1].sold && ds[j].name > ds[j + 1].name) {
                    swap = true;
                }

                if (swap) {
                    Laptop temp = ds[j];
                    ds[j] = ds[j + 1];
                    ds[j + 1] = temp;
                }
            }
        }
    }

    // Mở rộng: Lọc và sắp xếp theo giá
    void locVaSapXepTheoGia(int minGia, int maxGia) {
        // Đếm số sản phẩm thỏa mãn
        int dem = 0;
        for (int i = 0; i < soLuong; i++) {
            if (ds[i].price >= minGia && ds[i].price <= maxGia) {
                dem++;
            }
        }

        if (dem == 0) {
            cout << "Khong co san pham nao trong khoang gia nay.\n";
            return;
        }

        // Tạo mảng mới chứa sản phẩm thỏa mãn
        Laptop* loc = new Laptop[dem];
        int idx = 0;
        for (int i = 0; i < soLuong; i++) {
            if (ds[i].price >= minGia && ds[i].price <= maxGia) {
                loc[idx++] = ds[i];
            }
        }

        // Sắp xếp theo giá tăng dần
        for (int i = 0; i < dem - 1; i++) {
            for (int j = 0; j < dem - i - 1; j++) {
                if (loc[j].price > loc[j + 1].price) {
                    Laptop temp = loc[j];
                    loc[j] = loc[j + 1];
                    loc[j + 1] = temp;
                }
            }
        }

        // Hiển thị
        cout << "\nCo " << dem << " san pham trong khoang [" << minGia << ", " << maxGia << "]:\n";
        cout << setw(6) << "ID" << " | "
            << setw(20) << "Ten" << " | "
            << setw(12) << "Gia" << " | "
            << setw(8) << "Da ban" << " | "
            << setw(6) << "Diem" << endl;
        cout << string(70, '-') << endl;

        for (int i = 0; i < dem; i++) {
            loc[i].hienThi();
        }

        delete[] loc;
    }
};

// Hàm main
int main() {
    QuanLyLaptop ql;
    int chon;

    do {
        cout << "\n===== HE THONG QUAN LY LAPTOP =====\n";
        cout << "1. Tao file du lieu mau\n";
        cout << "2. Doc file du lieu\n";
        cout << "3. Hien thi n san pham dau\n";
        cout << "4. Chay tat ca test (10,000 san pham)\n";
        cout << "5. Sap xep theo sold, neu bang thi theo ten\n";
        cout << "6. Loc va sap xep theo gia\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        if (chon == 1) {
            int n;
            cout << "Nhap so luong san pham can tao: ";
            cin >> n;
            ql.taoFile("laptops.txt", n);

        }
        else if (chon == 2) {
            ql.docFile("laptops.txt");

        }
        else if (chon == 3) {
            int n;
            cout << "Nhap so san pham can hien thi: ";
            cin >> n;
            ql.hienThi(n);

        }
        else if (chon == 4) {
            ql.chayTatCaTest();

        }
        else if (chon == 5) {
            ql.sapXepSoldVaTen();
            cout << "Da sap xep!\n";
            ql.hienThi(10);

        }
        else if (chon == 6) {
            int a, b;
            cout << "Nhap gia min: ";
            cin >> a;
            cout << "Nhap gia max: ";
            cin >> b;
            ql.locVaSapXepTheoGia(a, b);
        }

    } while (chon != 0);

    return 0;
}
