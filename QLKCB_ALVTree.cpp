#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
struct NGAYTHANG
{
    int ngay;
    int thang;
    int nam;
};
struct BENHNHAN
{
    int STT;
    char hoten[30];
    char diachi[255];
    char sdt[12];
    char BHYT[12];
    NGAYTHANG ngaykham;
    char trangthai[255];
};
typedef struct Node
{
    BENHNHAN data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;
typedef Node *Tree;

Node *createNode(BENHNHAN b)
{
    Node *newNode = new Node;
    newNode->data = b;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Hàm tính chiều cao của một nút trong cây AVL
int getHeight(Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// Hàm lấy giá trị lớn nhất trong hai số
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Hàm cân bằng cây AVL sau khi thêm một nút mới
Node *balanceTree(Node *node)
{
    if (node == NULL)
        return node;

    // Cập nhật chiều cao của nút hiện tại
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getHeight(node->left) - getHeight(node->right);

    // Trường hợp mất cân bằng trái-trái
    if (balanceFactor > 1 && node->data.STT < node->left->data.STT)
    {
        Node *temp = node->left;
        node->left = temp->right;
        temp->right = node;
        return temp;
    }

    // Trường hợp mất cân bằng phải-phải
    if (balanceFactor < -1 && node->data.STT > node->right->data.STT)
    {
        Node *temp = node->right;
        node->right = temp->left;
        temp->left = node;
        return temp;
    }

    // Trường hợp mất cân bằng trái-phải
    if (balanceFactor > 1 && node->data.STT > node->left->data.STT)
    {
        node->left = balanceTree(node->left);
        Node *temp = node->left;
        node->left = temp->right;
        temp->right = node;
        return temp;
    }

    // Trường hợp mất cân bằng phải-trái
    if (balanceFactor < -1 && node->data.STT < node->right->data.STT)
    {
        node->right = balanceTree(node->right);
        Node *temp = node->right;
        node->right = temp->left;
        temp->left = node;
        return temp;
    }

    return node;
}

// Hàm thêm một bệnh nhân mới vào cây AVL
void ThemNodeVaoCay(Node *p, Tree &c)
{
    if (c == NULL)
    {
        c = p;
        printf("\nDa them vao cay AVL de quan ly\n");
        return;
    }

    if (p->data.STT < c->data.STT)
        ThemNodeVaoCay(p, c->left);
    else if (p->data.STT > c->data.STT)
        ThemNodeVaoCay(p, c->right);
    else
    {
        // Bệnh nhân đã tồn tại trong cây, không thực hiện thêm
        delete p; // Xóa nút p để tránh rò rỉ bộ nhớ
        printf("\nTrung so STT khong the them");
        return;
    }

    // Cập nhật chiều cao của nút cha
    c->height = 1 + max(getHeight(c->left), getHeight(c->right));

    // Cân bằng cây AVL
    c = balanceTree(c);
}
bool KiemTraNgayThangNam(int ngay, int thang, int nam)
{
    // Kiểm tra giá trị hợp lệ của ngày, tháng và năm
    if (nam < 0 || thang < 1 || thang > 12 || ngay < 1)
        return false;

    // Kiểm tra số ngày của từng tháng
    int soNgayTrongThang;
    if (thang == 2)
    {
        // Năm nhuận
        if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0))
            soNgayTrongThang = 29;
        else
            soNgayTrongThang = 28;
    }
    else if (thang == 4 || thang == 6 || thang == 9 || thang == 11)
    {
        soNgayTrongThang = 30;
    }
    else
    {
        soNgayTrongThang = 31;
    }

    if (ngay > soNgayTrongThang)
        return false;

    // Ngày tháng năm hợp lệ
    return true;
}
void Nhap(Tree &c)
{
    int n;
    printf("Nhap so luong benh nhan them vao cay n = ");
    scanf("%d", &n);
    getchar(); // Đọc và loại bỏ kí tự '\n' từ bộ nhớ đệm

    for (int i = 0; i < n; i++)
    {
        BENHNHAN bn;
        printf("\nNhap thong tin benh nhan thu %d:\n", i + 1);
        printf("STT: ");
        scanf("%d", &bn.STT);
        getchar(); // Đọc và loại bỏ kí tự '\n' từ bộ nhớ đệm
        printf("Ho ten: ");
        fgets(bn.hoten, sizeof(bn.hoten), stdin);
        bn.hoten[strcspn(bn.hoten, "\n")] = '\0'; // Loại bỏ kí tự '\n' cuối chuỗi
        printf("Dia chi: ");
        fgets(bn.diachi, sizeof(bn.diachi), stdin);
        bn.diachi[strcspn(bn.diachi, "\n")] = '\0'; // Loại bỏ kí tự '\n' cuối chuỗi
        printf("So dien thoai: ");
        fgets(bn.sdt, sizeof(bn.sdt), stdin);
        bn.sdt[strcspn(bn.sdt, "\n")] = '\0'; // Loại bỏ kí tự '\n' cuối chuỗi
        printf("BHYT: ");
        fgets(bn.BHYT, sizeof(bn.BHYT), stdin);
        bn.BHYT[strcspn(bn.BHYT, "\n")] = '\0'; // Loại bỏ kí tự '\n' cuối chuỗi
        // printf("Ngay kham (ngay/thang/nam): ");
        // scanf("%d %d %d", &bn.ngaykham.ngay, &bn.ngaykham.thang, &bn.ngaykham.nam);

        // Nhập ngày kham(ngay / thang / nam)
        const char *ketQua;
        do
        {
            char ngaykhamInput[12];
            printf("Ngay kham (ngay/thang/nam): ");
            fgets(ngaykhamInput, sizeof(ngaykhamInput), stdin);
            ngaykhamInput[strcspn(ngaykhamInput, "\n")] = '\0'; // Loại bỏ kí tự '\n' cuối chuỗi

            // Tách chuỗi thành ngay, thang, nam
            char *token;
            token = strtok(ngaykhamInput, "/");
            if (token != NULL)
            {
                bn.ngaykham.ngay = atoi(token);
                token = strtok(NULL, "/");
                if (token != NULL)
                {
                    bn.ngaykham.thang = atoi(token);
                    token = strtok(NULL, "/");
                    if (token != NULL)
                    {
                        bn.ngaykham.nam = atoi(token);
                    }
                }
            }
            ketQua = KiemTraNgayThangNam(bn.ngaykham.ngay, bn.ngaykham.thang, bn.ngaykham.nam) ? "" : "Ngay Kham khong hop le";
            if (strlen(ketQua) > 0)
                printf("%s\n", ketQua);
        } while (strlen(ketQua) > 0);

        // Nhap thong tin trang thai tu dong
        int tt;
        do
        {
            printf("Trang thai: ");
            printf("\nNhap 1: Cho Kham");
            printf("\nNhap 2: Dieu tri noi tru");
            printf("\nNhap 3: Dieu tri ngoai tru");
            printf("\nMoi nhap trang thai (1-3): ");
            scanf("%d", &tt);
            getchar(); // Đọc kí tự xuống dòng sau khi nhập số

            if (tt == 1)
                strcpy(bn.trangthai, "Cho Kham");
            else if (tt == 2)
                strcpy(bn.trangthai, "Dieu tri noi tru");
            else if (tt == 3)
                strcpy(bn.trangthai, "Dieu tri ngoai tru");
            else
                printf("Nhap sai, moi chon lai.\n");

        } while (tt < 1 || tt > 3);
        printf("Trang thai: %s\n", bn.trangthai);
        // fgets(bn.trangthai, sizeof(bn.trangthai), stdin);
        // bn.trangthai[strcspn(bn.trangthai, "\n")] = '\0'; // Loại bỏ kí tự '\n' cuối chuỗi

        Node *p = createNode(bn);
        ThemNodeVaoCay(p, c);
    }
}
void Xuat(Tree c)
{
    if (c != NULL)
    {
        Xuat(c->left);

        printf("\nSTT: %-10d\n", c->data.STT);
        printf("Ho ten: %-30s\n", c->data.hoten);
        printf("Dia chi: %-50s\n", c->data.diachi);
        printf("So dien thoai: %-15s\n", c->data.sdt);
        printf("BHYT: %-15s\n", c->data.BHYT);
        printf("Ngay kham: %02d/%02d/%04d\n", c->data.ngaykham.ngay, c->data.ngaykham.thang, c->data.ngaykham.nam);
        printf("Trang thai: %-20s\n", c->data.trangthai);

        Xuat(c->right);
    }
}

Node *TimNodeTheoSTT(Tree root, int stt)
{
    if (root == NULL || root->data.STT == stt)
        return root;

    if (stt < root->data.STT)
        return TimNodeTheoSTT(root->left, stt);

    return TimNodeTheoSTT(root->right, stt);
}
Node *TimNodeTheoBHYT(Tree root, char *bhyt)
{
    if (root == NULL || strcmp(root->data.BHYT, bhyt) == 0)
        return root;

    if (strcmp(bhyt, root->data.BHYT) < 0)
        return TimNodeTheoBHYT(root->left, bhyt);

    return TimNodeTheoBHYT(root->right, bhyt);
}
void CapNhatTrangThai(Tree root, int STT)
{
    Node *node = TimNodeTheoSTT(root, STT);
    if (node == NULL)
    {
        printf("\nKhong tim thay benh nhan co STT = %d\n", STT);
        return;
    }
    char *trangThaiMoi;
    // Hiển thị trạng thái bệnh nhân trước khi cập nhật
    printf("Trang thai benh nhan truoc khi cap nhat: %s\n", node->data.trangthai);

    // Cập nhật trạng thái bệnh nhân
    int tt;
    do
    {
        printf("\nCap nhat trang thai: ");
        printf("\nNhap 1: Cho Kham");
        printf("\nNhap 2: Dieu tri noi tru");
        printf("\nNhap 3: Dieu tri ngoai tru");
        printf("\nMoi nhap trang thai (1-3): ");
        scanf("%d", &tt);
        getchar(); // Đọc kí tự xuống dòng sau khi nhập số

        if (tt == 1)
            strcpy(trangThaiMoi, "Cho Kham");
        else if (tt == 2)
            strcpy(trangThaiMoi, "Dieu tri noi tru");
        else if (tt == 3)
            strcpy(trangThaiMoi, "Dieu tri ngoai tru");
        else
            printf("\nNhap sai, moi chon lai.");
        // khong trung trang thai cu
        if (strcmp(node->data.trangthai, trangThaiMoi) == 0)
            printf("\nDang o trang thai nay. Moi chon lai.\n");
        else
            strcpy(node->data.trangthai, trangThaiMoi);
    } while (tt < 1 || tt > 3);
    // Hiển thị trạng thái bệnh nhân sau khi cập nhật
    printf("Trang thai moi benh nhan sau khi cap nhat: %s\n", node->data.trangthai);
}

void searchStandFor(Tree &p, Tree &q)
{
    if (q->left != NULL)
        searchStandFor(p, q->left);
    else
    {
        p->data.STT = q->data.STT;
        q = q->right;
    }
}
void deleteNode(Tree &root, int key)
{
    if (root == NULL)
    {
        printf("Cay rong khong the xoa");
        return;
    }

    if (key < root->data.STT)
        deleteNode(root->left, key);
    else if (key > root->data.STT)
        deleteNode(root->right, key);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            Tree temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }

            delete temp;
        }
        else
        {
            Tree temp;
            searchStandFor(temp, root->right);

            root->data = temp->data;

            deleteNode(root->right, temp->data.STT);
        }
    }

    if (root != NULL)
        root = balanceTree(root);
}
void ReadFile(char *filename, Tree &c)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Khong the mo file.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file))
    {
        // Tách thông tin bệnh nhân từ dòng đọc được
        char *token = strtok(buffer, ";");
        BENHNHAN bn;

        // Lấy thông tin từng trường
        bn.STT = atoi(token);
        token = strtok(NULL, ";");
        strcpy(bn.hoten, token);
        token = strtok(NULL, ";");
        strcpy(bn.diachi, token);
        token = strtok(NULL, ";");
        strcpy(bn.sdt, token);
        token = strtok(NULL, ";");
        strcpy(bn.BHYT, token);
        token = strtok(NULL, ";");
        sscanf(token, "%d/%d/%d", &bn.ngaykham.ngay, &bn.ngaykham.thang, &bn.ngaykham.nam);
        token = strtok(NULL, ";");
        strcpy(bn.trangthai, token);

        // Tạo một node mới với thông tin bệnh nhân
        Node *newNode = createNode(bn);

        // Thêm node vào cây AVL
        ThemNodeVaoCay(newNode, c);
    }

    fclose(file);
}
// void SetConsoleWindowSize(int width, int height)
// {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     SMALL_RECT rect = {0, 0, width - 1, height - 1};
//     COORD size = {width, height};
//     SetConsoleScreenBufferSize(hConsole, size);
//     SetConsoleWindowInfo(hConsole, TRUE, &rect);
// }

// void SetConsoleTextColor(int color)
// {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     SetConsoleTextAttribute(hConsole, color);
// }
void menu()
{
    Tree c = NULL;
    Node *p = NULL;
    int x;
    char ma[12];
    int choice;
    // SetConsoleWindowSize(80, 20);

    // SetConsoleTextColor(10); // Màu vàng 14 xanh 10
    do
    {
        printf("\n----------------------- MENU ------------------------");
        printf("\n|                                                   |");
        printf("\n| 1. Them benh nhan                                 |");
        printf("\n| 2. Xuat danh sach benh nhan                       |");
        printf("\n| 3. Tim thong tin benh nhan theo STT               |");
        printf("\n| 4. Tim thong tin benh nhan theo ma BHYT           |");
        printf("\n| 5. Cap nhat trang thai moi theo STT               |");
        printf("\n| 6. Xoa thong tin benh nhan theo STT               |");
        printf("\n| 7. Doc du lieu tu file data                       |");
        printf("\n| 0. Thoat                                          |");
        printf("\n|                                                   |");
        printf("\n-----------------------------------------------------");
        printf("\nNhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            Nhap(c);
            break;
        case 2:
            printf("\nDanh sach benh nhan:\n");
            Xuat(c);
            break;
        case 3:
            printf("\nNhap STT benh nhan can tim: ");
            scanf("%d", &x);
            p = TimNodeTheoSTT(c, x);
            Xuat(p);
            break;
        case 4:
            printf("\nNhap ma BHYT benh nhan can tim: ");
            gets(ma);
            p = TimNodeTheoBHYT(c, ma);
            Xuat(p);
            break;
        case 5:
            printf("\nNhap STT benh nhan can cap nhat: ");
            scanf("%d", &x);
            CapNhatTrangThai(c, x);
            break;
        case 6:
            printf("\nNhap STT benh nhan can xoa: ");
            scanf("%d", &x);
            deleteNode(c, x);
            break;
        case 7:
            ReadFile("data.txt", c);
            printf("\nDa doc xong du lieu tu file data\n");
            Xuat(c);
            break;
        case 0:
            printf("Cam on ban da su dung chuong trinh!\n");
            break;
        default:
            printf("Lua chon khong hop le. Vui long chon lai!\n");
            break;
        }
    } while (choice != 0);
}
int main(int argc, char *argv[])
{
    menu();
    return 0;
}
