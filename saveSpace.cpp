//#include "saveSpace.hpp"



/*#include <cerrno>
#include <ncursesw/ncurses.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <elf.h>
#include <cstring>


// ─────────────────────────────────────────────
// ZONE PERSISTANTE
// ─────────────────────────────────────────────
extern "C" {

// 128 Ko = 131072 octets
__attribute__((section(".save,\"aw\",@progbits")))
__attribute__((used))
uint8_t g_save_area[131072] = {0};

}

// ─────────────────────────────────────────────
// ELF I/O
// ─────────────────────────────────────────────
static off_t g_save_offset = -1;
static constexpr size_t SAVE_SIZE = 131072;

static void resolve_save_offset()
{
    int fd = open("/proc/self/exe", O_RDONLY);
    if (fd < 0) return;

    Elf64_Ehdr eh;
    if (pread(fd, &eh, sizeof(eh), 0) != sizeof(eh)) {
        close(fd);
        return;
    }

    Elf64_Shdr sh;
    Elf64_Shdr shstr;

    pread(fd, &shstr, sizeof(shstr),
          eh.e_shoff + eh.e_shentsize * eh.e_shstrndx);

    char name[64];

    for (int i = 0; i < eh.e_shnum; ++i) {
        pread(fd, &sh, sizeof(sh),
              eh.e_shoff + i * eh.e_shentsize);

        pread(fd, name, sizeof(name) - 1,
              shstr.sh_offset + sh.sh_name);
        name[sizeof(name) - 1] = '\0';

        if (strcmp(name, ".save") == 0) {
            g_save_offset = sh.sh_offset;
            break;
        }
    }

    close(fd);
}

void save_load()
{
    if (g_save_offset < 0)
        resolve_save_offset();
    if (g_save_offset < 0)
        return;

    int fd = open("/proc/self/exe", O_RDONLY);
    if (fd < 0) return;

    pread(fd, g_save_area, SAVE_SIZE, g_save_offset);
    close(fd);
}

void save_flush()
{
    if (g_save_offset < 0)
        resolve_save_offset();
    if (g_save_offset < 0)
        return;

    int fd = open("/proc/self/exe", O_RDWR);
    ssize_t w = pwrite(fd, g_save_area, 1, g_save_offset);
    mvprintw(1, 0, "pwrite=%ld errno=%d (%s)",
             w, errno, strerror(errno));

    uint8_t check = 0;
    pread(fd, &check, 1, g_save_offset);
    mvprintw(2, 0, "readback=%u", check);


    close(fd);
}*/
