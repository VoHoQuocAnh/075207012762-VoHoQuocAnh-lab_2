#  HỆ THỐNG QUẢN LÝ XE BUS & ĐO HIỆU NĂNG THUẬT TOÁN SẮP XẾP

##  Thông tin sinh viên
* **Họ và tên:** Võ Hồ Quốc Anh
* **Mã số sinh viên:** 075207012762
##  Mô tả dự án
Chương trình C++ thực hiện quản lý danh sách xe bus (`licensePlate`, `driverName`, `start`, `dest`, `num`)

1. **Quản lý dữ liệu Xe Bus:**
   - Đọc dữ liệu từ file `Data1.txt` ($n = 20$) và `Data2.txt` ($n = 1000$).
   - Kiểm tra và chuẩn hóa định dạng biển số xe bus (định dạng chuẩn: `29B-123.45`).
   - Tìm kiếm xe bus theo nơi xuất phát nhập từ bàn phím.
   - Đếm số lượng xe bus có dưới 30 chỗ ngồi.
   - Xuất dữ liệu sau khi sắp xếp ra file `SortResult.txt`.

2. **Cài đặt 8 thuật toán sắp xếp theo Tên tài xế:**
   - **Đơn giản:** Interchange Sort, Selection Sort, Insertion Sort, Bubble Sort.
   - **Nâng cao:** Quick Sort, Heap Sort, Shell Sort, Merge Sort.

3. **Đo thực nghiệm hiệu năng (Benchmark):**
   - Đo thời gian thực thi của 8 thuật toán sắp xếp trên bộ dữ liệu $n = 1000$ (`Data2.txt`) sử dụng thư viện `<chrono>`.
   - Lưu báo cáo và nhận xét đánh giá hiệu năng vào file `075207012762_VoHoQuocAnh_runtime.docx`.
## Cấu trúc các file trong dự án
| `075207012762_VoHoQuocAnh_code.cpp` | Mã nguồn C++ chính chứa toàn bộ chương trình, các thuật toán và menu điều khiển |
| `075207012762_VoHoQuocAnh_runtime.docx` | File báo cáo kết quả đo thời gian thực nghiệm và nhận xét chi tiết |
| `Data1.txt` | Tập dữ liệu mẫu kích thước nhỏ ($n = 20$) |
| `Data2.txt` | Tập dữ liệu sinh ngẫu nhiên kích thước lớn ($n = 1000$) |
| `SortResult.txt` | File lưu danh sách xe bus sau khi đã được sắp xếp |
| `README.md` | Tài liệu hướng dẫn sử dụng và thông tin bài nộp |
##  Hướng dẫn biên dịch và chạy chương trình

### Yêu cầu môi trường
* Trình biên dịch C++ hỗ trợ C++11 trở lên (g++, Clang, hoặc MSVC).

### Các bước thực hiện trong Terminal / Git Bash:

1. **Biên dịch mã nguồn:**
   ```bash
   g++ -std=c++11 075207012762_VoHoQuocAnh_code.cpp -o main
