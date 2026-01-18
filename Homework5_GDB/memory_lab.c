#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Tái hiện lỗi Stack Overflow bằng đệ quy vô hạn.
 * @param depth: Độ sâu hiện tại của lời gọi hàm.
 */
void trigger_stack_overflow(int depth) {
    // In ra độ sâu để quan sát quá trình tiêu thụ stack
    if (depth % 1000 == 0) {
        printf("Current stack depth: %d\n", depth);
    }
    
    // Mảng cục bộ lớn để đẩy nhanh quá trình tràn stack
    char buffer[1024]; 
    buffer[0] = 'a'; // Tránh trình biên dịch tối ưu hóa bỏ qua buffer

    // Gọi đệ quy vô hạn
    trigger_stack_overflow(depth + 1);
}

/**
 * Tái hiện lỗi Memory Leak và dẫn đến Out of Memory (OOM).
 */
void trigger_memory_leak_and_oom() {
    long count = 0;
    size_t block_size = 1024; // 1KB mỗi lần cấp phát

    printf("Starting memory leak loop...\n");
    
    while (1) {
        // Cấp phát nhưng không bao giờ giải phóng (free)
        void *ptr = malloc(block_size);
        
        // Kiểm tra nếu malloc thất bại (Out of Memory)
        if (ptr == NULL) {
            printf("\n[!] Out of Memory! Malloc returned NULL at iteration: %ld\n", count);
            return; // Thoát an toàn khi hết bộ nhớ
        }

        // Ghi dữ liệu để đảm bảo trang bộ nhớ thực sự được cấp phát
        memset(ptr, 0, block_size);
        
        count++;
        if (count % 10000 == 0) {
            printf("Allocated: %ld KB\r", count);
            fflush(stdout);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <stack_overflow | memory_leak | out_of_memory>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "stack_overflow") == 0) {
        printf("Triggering Stack Overflow...\n");
        trigger_stack_overflow(1);
    } 
    else if (strcmp(argv[1], "memory_leak") == 0 || strcmp(argv[1], "out_of_memory") == 0) {
        // Cả hai trường hợp này chung một logic: Leak liên tục dẫn đến OOM
        trigger_memory_leak_and_oom();
    } 
    else {
        printf("Unknown argument: %s\n", argv[1]);
        return 1;
    }

    return 0;
}