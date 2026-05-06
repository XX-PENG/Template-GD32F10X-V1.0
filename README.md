# Template-GD32F10X-V1.0

兆易创新 GD32F10X 系列 MCU 的 VSCode + GCC + CMake 开发模板

## 📋 项目简介

本项目提供了一个基于 **GNU Arm Embedded** 工具链和 **CMake** 构建系统的 GD32F10X 开发模板，支持在 macOS、Linux 和 Windows 平台上进行嵌入式开发。

### 主要特性

- ✅ VS Code 集成开发环境支持
- ✅ 使用 GNU Arm Embedded Toolchain (arm-none-eabi-gcc)
- ✅ CMake 构建系统，支持 Ninja 和 Make 生成器
- ✅ 集成 CMSIS、GD32 标准外设库和板级支持文件
- ✅ 集成 FreeRTOS 实时操作系统
- ✅ 支持 Debug 和 Release 两种构建模式
- ✅ 支持 J-Link 调试
- ✅ 自动生成 HEX 和 BIN 文件

---

## 🛠️ 环境要求

### 必需软件

1. **GNU Arm Embedded Toolchain**
   - 下载地址：[ARM Developer](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
   - 或通过 Homebrew 安装（macOS）：
     ```bash
     brew install --cask gcc-arm-embedded
     ```

2. **CMake** (版本 >= 3.22)
   - 下载地址：[CMake Official](https://cmake.org/download/)
   - 或通过 Homebrew 安装（macOS）：
     ```bash
     brew install cmake
     ```

3. **Ninja** 或 **Make**
   - Ninja（推荐，构建速度更快）：
     ```bash
     brew install ninja
     ```
   - 或使用系统自带的 Make（macOS 需安装 Xcode Command Line Tools）：
     ```bash
     xcode-select --install
     ```
     
4. **VS Code** 及扩展：
    - 下载地址：[Visual Studio Code](https://code.visualstudio.com/)
    - Cortex-Debug 扩展（在 VS Code 中搜索安装）
    - C/C++ Extension Pack（在 VS Code 中搜索安装）

5. **SEGGER J-Link 驱动和软件包**
   - 下载地址：[SEGGER J-Link](https://www.segger.com/downloads/jlink)
   - macOS 安装后会包含 JLinkGDBServer 和 J-Link 驱动。
   - 或通过 Homebrew 安装（macOS）：
     ```bash
     brew install segger-jlink
     ```

### 可选软件

1. **VS Code** 及扩展：
  - Serial Monitor 扩展（在 VS Code 中搜索安装）

2. **git** 可在 VS Code 中进行版本控制，建议安装 git
   - 下载地址：[Git Official](https://git-scm.com/)
   - 或通过 Homebrew 安装（macOS）：
     ```bash
     brew install git
     ```
   - git 配置：
     ```bash
     git config --global user.name "YourName"
     git config --global user.email "your.email@example.com"
     ```

---

## 📦 项目结构

```
Template-GD32F10X-V1.0/
├── .vscode/              # VS Code 配置文件
│       └── launch.json   # 调试配置
├── Core/                 # 核心代码
│   ├── Inc/              # 头文件
│   │   ├── FreeRTOSConfig.h      # FreeRTOS 配置
│   │   └── systick.h
│   └── Src/              # 源文件
│       ├── main.c        # 主程序入口
│       ├── freertos.c    # FreeRTOS 初始化与任务创建
│       ├── gd32f10x_it.c
│       └── systick.c
├── Drivers/              # 驱动库
│   ├── CMSIS/            # ARM CMSIS 核心库
│   ├── GD32F10x_standard_peripheral/
│   ├── GD32F10x_usbd_library/
│   └── GD32F10x_usbfs_library/
├── jlink/                # 调试辅助文件
│   ├── GD32F10x_MD.svd   # Cortex-Debug 使用的 SVD 文件
│   └── svd/              # 备用/分类存放的 SVD 文件
├── cmake/                # CMake 配置文件
│   ├── gd32/             # GD32 子模块
│   └── gcc-arm-none-eabi.cmake  # 工具链配置
├── Middlewares/          # 中间件
│   └── Third_Party/
│       └── FreeRTOS/     # FreeRTOS Kernel 源码
├── examples/             # 官方示例代码
├── CMakeLists.txt        # CMake 主配置文件
├── CMakePresets.json     # CMake 预设配置
├── GD32F103C8_FLASH.ld   # 链接脚本（指定 Flash/RAM 布局）
└── startup_gd32f10x_md.s # GNU 启动文件
```

## 🔗 链接脚本说明

`GD32F103C8_FLASH.ld` 是本项目当前使用的链接脚本，实际链接时由 `cmake/gcc-arm-none-eabi.cmake` 的 `-T "${CMAKE_SOURCE_DIR}/GD32F103C8_FLASH.ld"` 参数指定。

当前脚本中指定的内存布局是：

- FLASH `0x08000000` 起始，长度 `64K`
- RAM `0x20000000` 起始，长度 `20K`（栈顶 `_estack = 0x20005000`）
- 程序入口使用 `Reset_Handler`

如果你的实际 GD32F103 器件内存大小与此不同，需要根据芯片规格调整这个文件。

---

## ⏱️ FreeRTOS 支持说明

本工程已集成 `FreeRTOS`，`Middlewares/Third_Party/FreeRTOS/` 通过 STM32CubeMX 生成

- `Core/Src/freertos.c` 包含 RTOS 初始化函数 `FREERTOS_Init()`。
- `Core/Inc/FreeRTOSConfig.h` 用于配置 FreeRTOS 内核参数，如任务堆栈、时钟节拍、调度选项等。
- `Middlewares/Third_Party/FreeRTOS/` 包含 FreeRTOS 内核实现、CMSIS-RTOS2 适配层和 ARM_CM3 可移植层。
- 默认构建会自动包含 FreeRTOS 内核，无需额外手动添加源文件。
- `Core/Src/systick.c` 中的 `delay_1ms()` 在调度器启动后会自动切换为 `vTaskDelay()`，确保系统时钟节拍正确配置。

---

## 🚀 快速开始

### 1. 克隆项目

```bash
git clone <repository-url>
cd Template-GD32F10X-V1.0
```

### 2. 配置芯片与外设

当前模板默认面向 `GD32F103C8T6` 中密度器件，并包含最小外设集合：

- `Core/Src/main.c` 中的示例主循环
- `Core/Src/systick.c` 中的 SysTick 配置
- `startup_gd32f10x_md.s` 启动文件
- `GD32F103C8_FLASH.ld` 链接脚本

如果你要切换到其它 GD32F10x 型号，至少需要同步修改宏定义、启动文件和链接脚本。

### 3. 配置调试器

本项目已默认支持 J-Link 调试。建议按以下步骤配置：
1. 将目标板连接到 J-Link，使用 SWD 进行调试。
2. 在 `.vscode/launch.json` 中确认配置项：
  - `device`：与目标芯片型号一致，例如 `GD32F103C8T6`
   - `interface`：通常设置为 `swd`
   - `executable`：指向编译生成的 ELF 文件，例如 `${workspaceFolder}/build/Debug/Template-GD32F10X-V1.0.elf`
  - `svdFile`：当前默认指向 `${workspaceFolder}/jlink/GD32F10x_MD.svd`
3. 启动 VS Code 调试时，Cortex-Debug 会自动使用 J-Link GDB Server 连接目标。

补充说明：
- 仓库已经附带 `jlink/GD32F10x_MD.svd`，可直接用于 VS Code 的寄存器视图。
- 截至目前，未发现 GigaDevice 在 GD32F103 官方产品页公开提供 `.svd` 下载条目；本仓库中的 SVD 文件应视为工程内置调试辅助文件。
- 如果你切换到其它 GD32F10x 型号，除修改 `device` 外，也应核对启动文件、链接脚本以及 SVD 是否仍然匹配。


### 4. 构建项目

#### 使用 CMake Presets（推荐）

```bash
# 配置 Debug 模式
cmake --preset=Debug

# 构建项目
cmake --build build/Debug

# 或配置 Release 模式
cmake --preset=Release
cmake --build build/Release
```

#### 手动配置

```bash
# Debug 模式
cmake -DCMAKE_BUILD_TYPE=Debug -B build/Debug -G Ninja
cmake --build build/Debug

# Release 模式
cmake -DCMAKE_BUILD_TYPE=Release -B build/Release -G Ninja
cmake --build build/Release
```

> 如果遇到 CMake 缓存错误或源目录不匹配，建议先删除旧的构建目录再重新配置：
>
> ```bash
> rm -rf build/Debug
> cmake --preset=Debug
> ```

构建成功后，会在 `build/<BuildType>/` 目录下生成：
- `${CMAKE_PROJECT_NAME}.elf` 对应的 ELF 文件
- `${CMAKE_PROJECT_NAME}.hex` 对应的烧录镜像
- `${CMAKE_PROJECT_NAME}.bin` 对应的裸二进制文件
- `${CMAKE_PROJECT_NAME}.map` 对应的链接映射文件

### 5. 配置与启动调试

1. 确保 J-Link 驱动已正确安装，目标板连接到 J-Link，使用 SWD 调试。
2. 检查 `.vscode/launch.json` 配置项（如 `device`、`interface`、`executable`、`svdFile`）。
3. 常用快捷键
- `F5` - 启动调试
- `Shift+F5` - 停止调试
- `F9` - 切换断点
- `F10` - 单步跳过
- `F11` - 单步进入

---

### 常见问题

**问题 1**: 调试时连接失败或超时
**解决**: 确认 J-Link 固件和 SWD 连接是否正常，若必要可降低调试接口频率。

**问题 2**: 构建时找不到头文件或源文件
**解决**: 确认 `CMakeLists.txt` 与 `cmake/gd32/CMakeLists.txt` 中正确包含了相关目录和文件。

**问题 3**: 调试时没有寄存器视图或外设名称显示不完整
**解决**: 确认 `.vscode/launch.json` 中的 `svdFile` 指向现有文件。当前工程默认使用 `jlink/GD32F10x_MD.svd`。如果切换到其它芯片型号，可能需要替换为匹配的 SVD 文件。

---


## 📝 开发指南

### 添加新源文件

在 `CMakeLists.txt` 中添加你的源文件：

```cmake
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    Hardware/Src/my_driver.c    # 添加你的文件
)
```

### 添加头文件路径

```cmake
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/My/New/Path    # 添加你的路径
)
```

### 添加宏定义

```cmake
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    USE_MY_FEATURE=1
    DEBUG_MODE=1
)
```

---

## 📚 参考资源

- [GD32F10x 固件库](https://www.gd32mcu.com/)
- [GigaDevice 官网](https://www.gigadevice.com/)
- [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)
- [CMake 官方文档](https://cmake.org/documentation/)
- [Cortex-Debug 插件](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)
- [Community GD32 Cores](https://github.com/CommunityGD32Cores/platform-gd32)

---

## 📄 许可证

本项目中的驱动程序库遵循 GigaDevice 官方许可协议。详见各源码文件开头的版权声明。

---

## 🤝 贡献

欢迎提交 Issue 和 Pull Request！

---

## 📮 联系方式

如有问题，请通过 GitHub Issues 反馈。
