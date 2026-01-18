#include "logger.h"

int main() {
    // Khởi tạo logger mức INFO, ghi ra file "app.log"
    if (logger_init(LOG_INFO, "app.log") != 0) {
        return 1;
    }

    log_msg(LOG_INFO, "Application started. Version %d.%d", 1, 0);
    log_msg(LOG_WARNING, "This is a warning message.");
    
    // Log này sẽ bị bỏ qua vì LOG_DEBUG > LOG_INFO
    log_msg(LOG_DEBUG, "This debug info won't appear yet.");

    // Thay đổi mức lọc tại runtime
    printf("\n--- Changing log level to DEBUG ---\n");
    logger_set_level(LOG_DEBUG);
    
    log_msg(LOG_DEBUG, "Now you can see this debug message!");
    log_msg(LOG_ERROR, "Database connection failed! Code: %d", 500);

    logger_shutdown();
    return 0;
}