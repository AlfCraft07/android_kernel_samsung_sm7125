#!/bin/sh

build_kernel_dtb() {
    echo "-----------------------------------------------"
    echo "Beginning kernel and dtb compilation..."
    echo "-----------------------------------------------"

    export ARCH=arm64
    mkdir out

    export PATH=$(pwd)/llvm-aosp/bin:$PATH

    BUILD_VAR="-j$(nproc --all) ARCH=arm64 O=out LLVM=1"

    make $BUILD_VAR vendor/atoll-sec-perf_defconfig vendor/samsung/$DEVICE_NAME.config all
}

build_dtbo() {
    echo "-----------------------------------------------"
    echo "Building dtbo.img..."
    echo "-----------------------------------------------"
    DTBO_FILES=$(find $(pwd)/out/arch/arm64/boot/dts/samsung/ -name atoll-sec-"$DEVICE_NAME"-eur-overlay-*.dtbo)
    $(pwd)/tools/mkdtimg create $(pwd)/out/dtbo.img --page_size=4096 ${DTBO_FILES}

    mv $(pwd)/out/dtbo.img dtbo.img
}

build_boot() {
    echo "-----------------------------------------------"
    echo "Building boot.img..."
    echo "-----------------------------------------------"
    MAGISKBOOT="$(pwd)/magiskboot"
    OUT_KERNEL="$(pwd)/out/arch/arm64/boot/Image"
    DTB_OUT="$(pwd)/out/arch/arm64/boot/dts/qcom/atoll-ab-idp.dtb"
    MONTH="$(date +%Y-%m)"

    wget -O stock_boot.img https://raw.githubusercontent.com/frstprjkt/boot_samsung_sm7125/refs/heads/main/"$DEVICE_NAME"-boot.img
    $MAGISKBOOT unpack -h stock_boot.img
    sed -i "s|^os_patch_level=.*|os_patch_level=$MONTH|" header
    cp $OUT_KERNEL Image
    cp $DTB_OUT dtb
    $MAGISKBOOT repack stock_boot.img boot.img
}

build_kernel_dtb
build_dtbo
build_boot
