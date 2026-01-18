#include "logger.h"
#include <stdarg.h>
#include <time.h>
#include <string.h>

// Trạng thái nội bộ của module (Encapsulation)
static LogLevel current_max_level = LOG_INFO;
static FILE *log_file = NULL;

// Tên các cấp độ log để in ra chuỗi
static const char *level_strings[] = {
    "EMERGENCY", "ALERT", "CRITICAL", "ERROR", 
    "WARNING", "NOTICE", "INFO", "DEBUG"
};

int logger_init(LogLevel level, const char *filename) {
    current_max_level = level;
    if (filename != NULL) {
        log_file = fopen(filename, "a"); // Mở file ở chế độ append
        if (log_file == NULL) {
            perror("Failed to open log file");
            return -1;
        }
    }
    return 0;
}

void logger_set_level(LogLevel level) {
    current_max_level = level;
}

void logger_shutdown(void) {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}

// Hàm hỗ trợ lấy timestamp
static void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

void logger_log(LogLevel level, const char *file, int line, const char *fmt, ...) {
    // 1. Lọc theo cấp độ
    if (level > current_max_level) {
        return;
    }

    char timestamp[20];
    get_timestamp(timestamp, sizeof(timestamp));

    // 2. Chuẩn bị danh sách đối số thay đổi (stdarg.h)
    va_list args;

    // 3. Ghi ra Console (stdout hoặc stderr)
    FILE *out = (level <= LOG_ERROR) ? stderr : stdout;
    
    fprintf(out, "[%s] [%s] [%s:%d] - ", timestamp, level_strings[level], file, line);
    va_start(args, fmt);
    vfprintf(out, fmt, args);
    va_end(args);
    fprintf(out, "\n");
    fflush(out);

    // 4. Ghi ra File (nếu có cấu hình)
    if (log_file != NULL) {
        fprintf(log_file, "[%s] [%s] [%s:%d] - ", timestamp, level_strings[level], file, line);
        va_start(args, fmt);
        vfprintf(log_file, fmt, args);
        va_end(args);
        fprintf(log_file, "\n");
        fflush(log_file);
    }
}