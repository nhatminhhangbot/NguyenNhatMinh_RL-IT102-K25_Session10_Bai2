#include <stdio.h>
#include <string.h>

#define MAX_VE 50

typedef struct {
    int maVe;
    char tenSuKien[50];
    char loaiVe[20];
    float giaGoc;
    int isEarlyBird;
    int daCheckIn;
} VeSuKien;

int timVeTheoMa(VeSuKien danhSach[], int soLuong, int maVe);
float tinhGiaThanhToan(VeSuKien ve);
void hienThiDanhSach(VeSuKien danhSach[], int soLuong);
int phatHanhVe(VeSuKien danhSach[], int *soLuong, VeSuKien veMoi);
int checkInVe(VeSuKien danhSach[], int soLuong, int maVe);
int huyVe(VeSuKien danhSach[], int *soLuong, int maVe);

int timVeTheoMa(VeSuKien danhSach[], int soLuong, int maVe) {
    for (int i = 0; i < soLuong; i++) {
        if (danhSach[i].maVe == maVe) {
            return i;
        }
    }
    return -1;
}

float tinhGiaThanhToan(VeSuKien ve) {
    if (ve.isEarlyBird == 1) {
        return ve.giaGoc * 0.85f;
    }
    return ve.giaGoc;
}

void hienThiDanhSach(VeSuKien danhSach[], int soLuong) {
    printf("\n========================================================================================\n");
    printf("%-8s | %-25s | %-10s | %-12s | %-10s | %-12s | %-10s\n", 
           "Ma Ve", "Ten Su Kien", "Loai Ve", "Gia Goc", "Early Bird", "Gia Thuc Te", "Check-In");
    printf("----------------------------------------------------------------------------------------\n");
    if (soLuong == 0) {
        printf("Danh sach ve hien tai dang trong (0 ve).\n");
    } else {
        for (int i = 0; i < soLuong; i++) {
            float giaTT = tinhGiaThanhToan(danhSach[i]);
            printf("%-8d | %-25s | %-10s | %-12.0f | %-10s | %-12.0f | %-10s\n",
                   danhSach[i].maVe,
                   danhSach[i].tenSuKien,
                   danhSach[i].loaiVe,
                   danhSach[i].giaGoc,
                   danhSach[i].isEarlyBird ? "Co (15%)" : "Khong",
                   giaTT,
                   danhSach[i].daCheckIn ? "Da check-in" : "Chua");
        }
    }
    printf("========================================================================================\n");
}

int phatHanhVe(VeSuKien danhSach[], int *soLuong, VeSuKien veMoi) {
    if (*soLuong >= MAX_VE) {
        printf("Khong the phat hanh them ve. Da dat gioi han MAX_VE = %d!\n", MAX_VE);
        return 0;
    }
    if (timVeTheoMa(danhSach, *soLuong, veMoi.maVe) != -1) {
        printf("Ma ve %d da ton tai trong he thong!\n", veMoi.maVe);
        return 0;
    }
    danhSach[*soLuong] = veMoi;
    (*soLuong)++;
    printf("Phat hanh thanh cong ve ma: %d\n", veMoi.maVe);
    return 1;
}

int checkInVe(VeSuKien danhSach[], int soLuong, int maVe) {
    if (soLuong == 0) {
        printf("Danh sach ve dang trong, khong the thuc hien check-in!\n");
        return 0;
    }
    
    int index = timVeTheoMa(danhSach, soLuong, maVe);
    if (index == -1) {
        printf("Ma ve %d khong ton tai trong he thong soat ve!\n", maVe);
        return 0;
    }
    
    if (danhSach[index].daCheckIn == 1) {
        printf("Ma ve %d da duoc check-in truoc do! Tu choi quyen truy cap!\n", maVe);
        return -1;
    }
    
    danhSach[index].daCheckIn = 1;
    printf("Chao mung ban den voi %s (Loai ve: %s)!\n", 
           danhSach[index].tenSuKien, danhSach[index].loaiVe);
    return 1;
}

int huyVe(VeSuKien danhSach[], int *soLuong, int maVe) {
    if (*soLuong == 0) {
        printf("Danh sach ve dang trong, khong co ve de huy!\n");
        return 0;
    }
    
    int index = timVeTheoMa(danhSach, *soLuong, maVe);
    if (index == -1) {
        printf("Khong tim thay ma ve %d de thuc hien huy!\n", maVe);
        return 0;
    }
    
    for (int i = index; i < *soLuong - 1; i++) {
        danhSach[i] = danhSach[i + 1];
    }
    (*soLuong)--;
    printf("Da xoa vinh vien ve ma %d khoi he thong.\n", maVe);
    return 1;
}

int main() {
    VeSuKien danhSachVe[MAX_VE];
    int soLuongVe = 0;

    printf("===================================================================\n");
    printf("  DEMO MODULE QUAN LY & SOAT VE - LIVE CONCERT VIBE 2025 (TICKETBOX)\n");
    printf("===================================================================\n");

    printf("\n--- Khoi tao danh sach gom 3 ve ban dau ---\n");
    VeSuKien v1 = {1001, "Live Concert VIBE 2025", "VIP", 2500000.0f, 1, 0};
    VeSuKien v2 = {1002, "Live Concert VIBE 2025", "GA", 1200000.0f, 1, 0};
    VeSuKien v3 = {1003, "Live Concert VIBE 2025", "Zone A", 1800000.0f, 0, 0};
    
    phatHanhVe(danhSachVe, &soLuongVe, v1);
    phatHanhVe(danhSachVe, &soLuongVe, v2);
    phatHanhVe(danhSachVe, &soLuongVe, v3);

    printf("\n--- Hien thi danh sach va gia thanh toan thuc te ---\n");
    hienThiDanhSach(danhSachVe, soLuongVe);

    printf("\n--- Phat hanh them 1 ve moi (Ma: 1004) ---\n");
    VeSuKien v4 = {1004, "Live Concert VIBE 2025", "VIP", 2500000.0f, 0, 0};
    phatHanhVe(danhSachVe, &soLuongVe, v4);
    hienThiDanhSach(danhSachVe, soLuongVe);

    printf("\n--- Check-in hop le cho ma ve 1001 ---\n");
    checkInVe(danhSachVe, soLuongVe, 1001);

    printf("\n--- Thu nghiem quet lai ma ve 1001 (Duplicate QR Scan) ---\n");
    checkInVe(danhSachVe, soLuongVe, 1001);

    printf("\n--- Thuc hien huy ve 1002 khoi he thong ---\n");
    huyVe(danhSachVe, &soLuongVe, 1002);
    hienThiDanhSach(danhSachVe, soLuongVe);

    printf("\n--- Thu nghiem quet ma ve khong ton tai (Ma: 9999) ---\n");
    checkInVe(danhSachVe, soLuongVe, 9999);

    printf("\n--- Hien thi tong ket danh sach ve sau tat ca thao tac ---\n");
    hienThiDanhSach(danhSachVe, soLuongVe);

    return 0;
}
