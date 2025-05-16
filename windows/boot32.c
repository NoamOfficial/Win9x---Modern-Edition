// boot32.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define EXPORT __attribute__((visibility("default")))

// Simulate low-level memory pointers (adjust these to your AMS hook macros later)
void* kernel_memory = NULL;
char env_vars[1024] = {0};

// Simulated console render (text mode)
EXPORT int Boot32_RenderLogo(const char* logoFile) {
    FILE* file = fopen(logoFile, "r");
    if (!file) {
        printf("[boot32] Failed to load logo: %s\n", logoFile);
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    return 0;
}

// Initialize system (RAMDisk, memory map, etc.)
EXPORT int Boot32_Startup(void) {
    printf("[boot32] Starting boot system...\n");
    // Pretend to init AMS here
    // hook AMS interrupts, set reserved regions, etc.
    return 0;
}

// Load kernel file into memory
EXPORT int Boot32_LoadKernel(const char* kernelPath) {
    printf("[boot32] Loading kernel: %s\n", kernelPath);

    FILE* file = fopen(kernelPath, "rb");
    if (!file) {
        printf("[boot32] Failed to load kernel\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    kernel_memory = malloc(size);
    if (!kernel_memory) {
        printf("[boot32] Memory allocation failed\n");
        fclose(file);
        return -1;
    }

    fread(kernel_memory, 1, size, file);
    fclose(file);

    printf("[boot32] Kernel loaded (%ld bytes)\n", size);
    return 0;
}

// Setup environment variables
EXPORT void Boot32_SetupEnv(void) {
    strcpy(env_vars, "BOOT=TRUE;PATH=C:\\UltimateOS\\System32;");
    printf("[boot32] Environment initialized: %s\n", env_vars);
}

// Handoff to kernel
EXPORT void Boot32_HandOff(void) {
    printf("[boot32] Handing off to kernel...\n");

    if (kernel_memory) {
        void (*kernel_entry)(void) = (void (*)(void))kernel_memory;
        kernel_entry();  // 🧠 this is where the magic starts
    } else {
        printf("[boot32] No kernel loaded to execute!\n");
    }
}
