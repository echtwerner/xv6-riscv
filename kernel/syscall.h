// System call names are derived automatically from SYS_* defines to minimize changes compared to upstream.
// Usage:
// 1. Default: Name = lowercase(DEFINE_NAME without "SYS_")  e.g. SYS_fork -> "fork"
// 2. With sys_ prefix: Add // sys_prefix: 1 after the define  e.g. SYS_sbrk -> "sys_sbrk"
//    Only add the comment where sys_ prefix is needed - most syscalls use default naming
// This approach keeps the header close to original upstream while allowing exceptions via simple flags
//
// System call numbers and syscall_name  - optional // sys_prefix: 1
#define SYS_fork 1
#define SYS_exit 2
#define SYS_wait 3
#define SYS_pipe 4
#define SYS_read 5
#define SYS_kill 6
#define SYS_exec 7
#define SYS_fstat 8
#define SYS_chdir 9
#define SYS_dup 10
#define SYS_getpid 11
#define SYS_sbrk 12 // sys_prefix: 1
#define SYS_pause 13
#define SYS_uptime 14
#define SYS_open 15
#define SYS_write 16
#define SYS_mknod 17
#define SYS_unlink 18
#define SYS_link 19
#define SYS_mkdir 20
#define SYS_close 21
#define SYS_freepg 22