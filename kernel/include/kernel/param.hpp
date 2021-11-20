// some general settings.
namespace config {
constexpr auto NUM_OF_PROC = 64;
constexpr auto KERNEL_STACK_SIZE = 4096;
constexpr auto NUM_OF_CPU = 8;
constexpr auto NUM_OF_FILE_PER_PROC = 16;
constexpr auto NUM_OF_FILE_PER_SYS = 100;
constexpr auto MAXNUM_OF_ACTIVE_INODE = 50;
constexpr auto MAX_MAJOR_DEVICE_NUM = 10;
constexpr auto ROOTDEV_ID = 1;
constexpr auto MAX_EXEC_ARGS = 32;
constexpr auto MAXNUM_OF_BLOCKS_OP_CAN_WRITES = 10;
constexpr auto LOG_SIZE = MAXNUM_OF_BLOCKS_OP_CAN_WRITES * 3;
constexpr auto BUFFER_NUM = MAXNUM_OF_BLOCKS_OP_CAN_WRITES * 3;
constexpr auto FS_SIZE_IN_BLOCKS = 1000; // size of disk block cache.
} // namespace config
