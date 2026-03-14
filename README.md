
![EngineLogo](https://github.com/Mathys-Hymon/ClutterEngine/blob/18f664656290dbc14758a925802a724a73ab9c85/engineLogoLight.png)


![C++20](https://img.shields.io/badge/C++-20-blue.svg?style=flat&logo=c%2B%2B)
![CMake](https://img.shields.io/badge/CMake-3.20+-success.svg?style=flat&logo=cmake)
![License](https://img.shields.io/badge/License-MIT-green.svg)

**Clutter Engine** is an educational, tooling-first, ECS-based game engine shaped for Nintendo 3DS homebrew development. Inspired by modern workflows, it features a clear separation between the runtime core and a dedicated PC-based editor.

## ✨ Features

* **Data-Driven Architecture:** Powered by [`EnTT`](https://github.com/skypjack/entt) for maximum performance and cache-friendly Entity Component System (ECS) management.
* **Native C++ Reflection & Serialization:** A custom-built reflection system (`clt::meta::Reflector`) that automatically serializes any component, nested struct, or standard container (`std::vector`, `std::unordered_map`) into human-readable JSON files using `nlohmann/json`.
* **Strict Editor/Runtime Separation:** 

  * `ClutterCore` (`clt::`): The lightweight engine runtime.
  * `ClutterEditor` (`editor::`): A comprehensive ImGui-based toolchain.
* **Modern Graphics Pipeline:** Built with Vulkan/OpenGL and GLFW (Currently PC-first, serving as an emulator/editor for the 3DS target).
* **Smart Asset Management:** (WIP) Lazy-loading asset system with Handle/Registry architecture for optimal RAM usage on constrained hardware.

## 🗺️ Roadmap & Milestones

Clutter Engine is under active development. Here is the path forward to achieving a complete, production-ready 3DS toolchain:

### 📍 Milestone 1: Editor Foundations (Current)
- [x] Core ECS architecture with `EnTT`.
- [x] Custom Reflection & Serialization system (`nlohmann/json`).
- [ ] ImGui Editor integration (`editor::`).
- [ ] Auto-generated UI (Inspector) based on C++ reflection data.
- [ ] Scene Hierarchy panel and basic entity manipulation.

### 📍 Milestone 2: Asset Pipeline & Basic Rendering
- [ ] Abstract Renderer API (OpenGL initially, with Vulkan/3DS abstraction in mind).
- [ ] Basic Real-time Lighting (Directional & Point lights, Forward Rendering).
- [ ] Smart `AssetManager` with Lazy-Loading and memory caching.
- [ ] Offline Asset Cooking (e.g., converting `.ttf` to Bitmap Atlases via the Editor).
- [ ] Multi-threaded asynchronous asset loading.

### 📍 Milestone 3: Advanced Tooling & Baked Illumination
- [ ] Offline Lightmapper (Baked Lighting): Pre-computing light bounces into lightmap textures for maximum 3DS runtime performance.
- [ ] Visual HUD/UI Editor (Unreal UMG / Unity Canvas style) for rapid interface building.
- [ ] 2D and 3D Physics engine integration (e.g., Box2D / JoltPhysics).
- [ ] Audio engine abstraction (BGM, SFX, spatialization).

### 📍 Milestone 4: The "Play-in-Editor" (PIE) Experience
- [ ] Dual-Screen Framebuffer rendering (Top: 400x240, Bottom: 320x240).
- [ ] Editor tools to simulate 3DS hardware (Gyroscope gimbals, Touch screen inputs).
- [ ] Play/Pause/Step simulation states.

### 📍 Milestone 5: Nintendo 3DS Native Deployment
- [ ] Build system integration with `devkitARM` and `libctru`.
- [ ] Native 3DS rendering backend (PICA200 / citro3d).
- [ ] **Hardware Abstraction Layer (HAL):** Clean C++ wrappers for 3DS specific features (`PlaySound()`, Camera, Gyro, Mic, etc.).
- [ ] **Network API:** Wrappers for local wireless play and online sessions.

## 🚀 Getting Started

### Prerequisites
* **C++20 Compiler** (GCC 13+ / MinGW-w64 recommended)
* **CMake 3.20+**
* **Vulkan SDK** (1.4+)

### Cloning the Repository
Since this project may use submodules in the future, it's recommended to clone recursively:
```bash
git clone [https://github.com/Mathys-Hymon/ClutterEngine.git](https://github.com/Mathys-Hymon/ClutterEngine.git)
cd ClutterEngine

### Building (Windows / MinGW)
The project uses CMake. You can open it directly in IDEs like **CLion** or **Visual Studio**, or build it via the command line:

```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build . --target ClutterEditor -j 14
```

## 🏗️ Architecture & Namespaces

The engine strictly enforces domain boundaries to keep the codebase clean and portable:

| Module | Namespace | Description |
| :--- | :--- | :--- |
| **ClutterCore** | `clt::` | The core engine library. Contains `Level`, `Actor`, Math, and rendering logic. |
| **Meta / Utils** | `clt::meta::` | Deep engine tools like the `Serializer` and `Reflector`. |
| **ClutterEditor**| `editor::` | The PC toolchain. Contains ImGui panels, `EditorLayer`, and dev tools. |

## 📚 Third-Party Libraries
A huge thanks to the open-source community. Clutter Engine stands on the shoulders of:
* **EnTT** (ECS)
* **nlohmann/json** (Serialization)
* **Dear ImGui** (Editor UI)
* **stb_image** (Texture loading)
* **GLFW & Vulkan** (Windowing & Graphics)

## 📄 License
This project is open-source and available under the **MIT License**. Feel free to learn from it, fork it, and use it in your own projects!
