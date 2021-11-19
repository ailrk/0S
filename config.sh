SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc

export PREFIX=/usr
export EXEC_PREFX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 -g'
export CPPFLAGS=''

# choose system root for the cross compiler
export SYSROOT="${pwd}/sysroot"
export CC="$CC --sysroot=$SYSROOT"

# handle when -elf gcc target doesn't have a system include dir
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
    exprt CC="$CC -issytem=$INCLUDEDIR"
fi
