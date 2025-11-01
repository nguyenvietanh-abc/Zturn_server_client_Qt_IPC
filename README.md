# Zturn_server_client_Qt_IPC  
Hệ thống được xây dựng trên bo mạch Zturn Board V2 (Zynq-7000) bằng PetaLinux Tools dựa trên Yocto Project, sử dụng tệp .xsa sẵn có để tạo project, config kernel, build image, patch driver, device tree và tạo boot file.  
Sau khi hoàn tất hệ thống nhúng, triển khai chương trình C++ được phát triển để mô phỏng cơ chế truyền dữ liệu dạng server–client đa kết nối (multi-client) thông qua giao thức TCP/IP trên kết nối Ethernet. Trong mô hình này, bo mạch nhúng đóng vai trò server, cung cấp các thông tin gồm góc phương vị (range angle), góc hướng (direction angle), nhiệt độ và độ ẩm cho client. Dữ liệu được sinh ngẫu nhiên trong giới hạn trên–dưới định sẵn bằng hàm tạo dữ liệu giả lập. Phía client sẽ gửi yêu cầu đến server với tần số 600Hz, và mỗi lần yêu cầu, server phản hồi lại một bộ giá trị thông tin tương ứng. Hệ thống đảm bảo khả năng phản hồi liên tục và chính xác với tần số cao, phản ánh hoạt động thời gian thực của ứng dụng nhúng. Tiếp theo, chương trình mở rộng và triển khai thành ứng dụng Qt, ứng dụng cơ chế giao tiếp liên tiến trình (IPC – Inter-Process Communication) để quản lý trao đổi dữ liệu giữa các tiến trình trong cùng hệ thống, giúp tối ưu hiệu năng, tăng tính linh hoạt và khả năng mở rộng cho việc phát triển các ứng dụng nhúng phức tạp hơn dựa trên nền tảng Zynq–7000.  

Quy trình triển khai:  

1. Create Petalinux Project (tạo skeleton base FPGA-disgned)  
2. System Configuration (Configure Kernel, RootFS, Device Tree)  
   2.1. Kích hoạt driver  
   2.2. Tùy chỉnh device tree (các node phần cứng tương ứng PL/PS)  
   2.3. Add libs (Qt libs).  
3. System Build Process (Build System Image)  
   -> Yocto thực hiện Bitbake để compile Kernel, U-Boot, rootfs, device tree  
   >> Tạo các file:  
   >> BOOT.BIN (chứa FSBL, bitstream, U-Boot)  
   >> image.ub (kernel + device tree + rootfs)  
   >> rootfs.tar.gz  
4. Boot Image Packaging (Create Boot Files & Package)  
   $ petalinux-package --boot --fsbl images/linux/zynq_fsbl.elf \  
                  --u-boot images/linux/u-boot.elf \  
                  --fpga images/linux/system.bit  
   >> SD Card << BOOT.BIN && image.ub && boot.scr  
5. SDK toolchain Export (Generate & Build SDK)  
   $ petalinux-build --sdk  
   $ petalinux-package --sdk  
   >> sdk.sh (toolchain + sysroot)  
   >> Create Cross-compilation SDK chứa compiler arm-linux-gnuabihf-g++), headers, libs để build Qt/C++ on host.  
6. SDK Installation & Environment Setup (Extract SDK & Setup Environment)  
   $ ./sdk.sh  
   $ source /opt/petalinux/2024.1/environment-setup-cortexa9t2hf-neon-xilinx-linux-gnueabi  
   >> Config biến môi trường cho cross-compilation  
   >> Cho phép Qt/makefile build ứng dụng nhúng để chyaj trên board  
7. Qt Cross-Compilation (Build Qt for Embedded)  
   $ ./configure -prefix /usr/local/qt5 \  
            -device linux-arm-gnueabi-g++ \  
            -device-option CROSS_COMPILE=arm-linux-gnueabihf- \  
            -sysroot=$SDKTARGETSYSROOT \  
            -opensource -confirm-license \  
            -release -no-opengl -nomake examples -nomake tests  
   $ make -j8  
   $ make install  
   >> Compile Qt dựa trên kiến trúc ARM của Zynq, link với sysroot và toolchain từ SDK.  
8. Deployment && Execution (Run on Target)  
   Using FileZilla để upload file "Deploy" + libs lên folder Qt_libs trên SD_Card (trực tiếp)  
   (có thể mount với sd_card -> umount)  
  $ ssh root@192.168.1.3  
  $ cd ~Qt_libs  
  $ ./deploy #running file deploy  

Build the system (Zturn Board V2, Zynq 7000) with petalinux Tools based on Yocto using available xsa files to create projects, configure kernel, build images, patch drivers, device trees and create boot files. Then, a program was written to implement server-client data transmission (multi-client) using TCP/IP and C++ to simulate the embedded board acting as a server providing information about range angle, direction angle, temperature, humidity to the client. The data is generated using a random data retrieval function with upper and lower bounds. The client side sends requests to the server to get the above information at a frequency of 600Hz, with each request from the client the server returns a value of the information. Then it was expanded and deployed into a Qt program using inter-process communications (IPC).
