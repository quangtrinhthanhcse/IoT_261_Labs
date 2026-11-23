# LAB 4 — Web Server cấu hình ESP32-S3 (Nhóm 08)

## 1. Cấu trúc thư mục
- `esp32_webserver/`: Project PlatformIO cho YoloUNO (ESP32-S3), đã hoàn thiện **Bài 0 (Phần A–D)**:
  - AP Wi-Fi mặc định: `ESP32-G08` / mật khẩu `12345678` (`http://192.168.4.1`)
  - LED1: `GPIO48`, LED2: `GPIO41`, nút `BOOT`: `GPIO0`
  - Đã áp dụng đủ 4 điểm `FIX` trong `mainserver.cpp` và hoàn thiện `handleToggle()`
  - Dùng `sensor_task` giả lập để mọi thành viên đều có thể build và test độc lập

## 2. Phân công nhóm & Tên nhánh Git
Mỗi thành viên tách nhánh từ `main` trước khi làm:
```bash
git checkout main
git pull origin main
git checkout -b <ten-nhanh>
```

| Thành viên | Bài tập | Nhánh đề xuất | File / Hàm phụ trách chính |
| :--- | :--- | :--- | :--- |
| Thành viên 1 | Bài 0 (nền tảng) + Bài 1 (Trung bình trượt & Mutex) | `lab4/ex1-moving-avg` | `include/sensor_avg.h`, `src/sensor_avg.cpp`, `handleSensors()` |
| Thành viên 2 | Bài 2 (Ngưỡng nhiệt độ JS) | `lab4/ex2-temp-ui` | `mainPage()` (khối `T_LIMIT` và hiển thị `#temp`) |
| Thành viên 3 | Bài 3 (Mức độ ẩm & Hysteresis 1%) | `lab4/ex3-hum-level` | `humLevel()`, trường `"hum_level"` trong `/sensors`, `#hum` trong `mainPage()` |
| Thành viên 4 *(Xung phong)* | Bài 4 (Giữ AP `WIFI_AP_STA`) + Bài 5 (CoreIOT) | `lab4/ex4-ap-sta`, `lab4/ex5-coreiot` | `settingsPage()`, `handleConnect()`, `connectToWiFi()`, `main_server_task()`, `internet_task()` |

> **Lưu ý khi merge Bài 2 & Bài 3:** Cả hai bài đều cập nhật hàm `setInterval` trong `mainPage()` (`src/mainserver.cpp`), vì vậy Thành viên 2 chỉ sửa khối xử lý `#temp`, còn Thành viên 3 chỉ sửa khối xử lý `#hum` để dễ gộp vào `main`.

## 3. Hợp đồng hàm dùng chung (để Bài 5 ghép với Bài 1 & Bài 3)
- **Bài 1 (`sensor_avg.h`):** `bool getAverage(float *t_avg, float *h_avg);` (trả về `false` nếu `buf_count == 0`).
- **Bài 3 (`mainserver.h`):** `const char *humLevel(float h);` (trả về `"ok"`, `"dry"`, `"humid"`, hoặc `"danger"`).

## 4. Lưu ý bảo mật & Nộp bài
- **Không** commit mật khẩu Wi-Fi thật hoặc CoreIOT Access Token lên GitHub (nếu dùng file riêng hãy lưu vào `include/secrets.h` đã được ignore).
- **Không** commit thư mục `.pio/` (đã được chặn bởi `.gitignore` ở gốc repo).
