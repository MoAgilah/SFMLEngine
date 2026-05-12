# SFMLEngine

A lightweight, modular **C++ 2D game engine core** designed around clean separation between engine logic and rendering backends. The first implementation uses **SFML**, with the architecture structured to support future backend expansion.

The project focuses on scalable architecture, reusable systems, backend abstraction, and maintainable gameplay frameworks.

> **Status:** Work in progress — interfaces and systems are evolving as the engine ecosystem matures.

---

## 🧩 Overview

SFMLEngine defines the structure, interfaces, and backend connectors needed to write gameplay systems independently from rendering or platform APIs.

The goal is to allow game logic to communicate with generic engine interfaces rather than directly depending on SFML-specific classes. This improves maintainability, portability, and long-term extensibility.

---

## ⚙️ Key Features

- Modular engine systems
- Backend abstraction architecture
- SFML graphics and input backend
- Interface-based engine design
- Scene and state management
- Entity and gameplay systems
- Audio support
- Collision handling framework
- Expandable engine structure
- Reusable gameplay framework

---

## 🧱 Architecture

The engine separates platform-specific backend implementations from gameplay-facing systems through interfaces and abstraction layers.

Gameplay logic uses the `EngineInterface` layer, while backend-specific functionality is implemented separately inside the SFML backend.

```text
SFMLEngine/
├── EngineInterface/       → Core abstract interfaces
├── EngineSFMLBackEnd/     → SFML implementation of the interfaces
├── SFMLEngine.sln         → Visual Studio solution
├── Directory.Build.props  → Shared build settings
└── .gitmodules            → Submodule configuration
```

This structure allows the same gameplay systems to be reused across multiple backends with reduced code duplication.

---

## 🛠 Technologies

- C++
- SFML
- Visual Studio
- CMake
- Game engine architecture
- Backend abstraction

---

## 🚀 Getting Started

### Clone with Submodules

```bash
git clone https://github.com/MoAgilah/SFMLEngine.git
cd SFMLEngine
git submodule update --init --recursive
```

### Build

1. Open `SFMLEngine.sln` in Visual Studio.
2. Select **Debug** or **Release**.
3. Build the solution.

---

## 🔗 Example Projects

SFMLEngine is used or referenced across related projects:

| Project | Purpose |
|---------|---------|
| [Pong](https://github.com/MoAgilah/Pong) | Minimal gameplay example using the engine |
| [AI-Game-Controller](https://github.com/MoAgilah/AI-Game-Controller) | Original AI/gameplay prototype that inspired the architecture |
| [SuperMarioWorldClone](https://github.com/MoAgilah/SuperMarioWorldClone) | Ongoing rebuild using the engine for modularity and scalability |

---

## 🔭 Future Work

- Complete SFML backend coverage
- Add alternative rendering backends
- Improve ECS implementation
- Add physics integration
- Improve resource management
- Add editor or debugging tools
- Expand multi-platform support

---
