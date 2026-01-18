#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

// 8 cấp độ log theo tiêu chuẩn syslog
typedef enum {
    LOG_EMERGENCY = 0, // Hệ thống không thể sử dụng
    LOG_ALERT,         // Cần hành động ngay lập tức
    LOG_CRITICAL,      // Tình trạng nguy kịch
    LOG_ERROR,         // Lỗi thực thi
    LOG_WARNING,       // Cảnh báo
    LOG_NOTICE,        // Thông báo bình thường nhưng đáng chú ý
    LOG_INFO,          // Thông tin hỗ trợ
    LOG_DEBUG          // Thông tin chi tiết để gỡ lỗi
} LogLevel;

// Khởi tạo và giải phóng logger
int logger_init(LogLevel level, const char *filename);
void logger_shutdown(void);

// Thay đổi mức lọc log tại runtime
void logger_set_level(LogLevel level);

// Hàm cốt lõi (không gọi trực tiếp, dùng macro bên dưới)
void logger_log(LogLevel level, const char *file, int line, const char *fmt, ...);

// Macro tiện lợi để tự động chèn tên file và dòng
#define log_msg(level, fmt, ...) \
    logger_log(level, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif