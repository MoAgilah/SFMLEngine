# SFMLEngine

A lightweight, backend-agnostic C++ game engine core designed around clean separation between **engine logic** and **rendering backends** — with the first implementation built using **SFML**.

This repository provides the **shared engine architecture** used across:
- 🎮 [**Pong**](https://github.com/MoAgilah/Pong) — a minimal, practical example showcasing engine usage  
- 🧠 [**AI-Game-Controller**](https://github.com/MoAgilah/AI-Game-Controller) — the experimental origin project that inspired this engine  
- 🍄 [**SuperMarioWorldClone**](https://github.com/MoAgilah/SuperMarioWorldClone) — the ongoing rebuild and next step, expanding AI integration and gameplay complexity using this engine

> **Status:** Work in progress — interfaces and systems are evolving as the ecosystem matures.

---

## 🧩 Overview

**SFMLEngine** defines the structure, interfaces, and backend connectors that let you write gameplay systems independent of rendering or platform APIs.  
The goal is to **write once**, then **plug in any backend** (currently SFML, with SDL/DirectX/Vulkan support planned).

### Key Principles
- **Backend-agnostic:** Engine logic talks to interfaces, not implementations.
- **Interface segregation:** Each system (graphics, input, audio, etc.) remains modular.
- **Code reuse:** The same game logic can be reused across multiple rendering backends.
- **Ease of extension:** Designed to plug in new backends without code duplication.

---

## 📁 Repository Structure
```
SFMLEngine/
├── EngineInterface/ # Core abstract interfaces (Git submodule)
├── EngineSFMLBackEnd/ # SFML implementation of the interfaces
├── SFMLEngine.sln # Visual Studio solution (for Windows builds)
├── Directory.Build.props # Shared build settings
└── .gitmodules # Submodule configuration
```

## ⚙️ Getting Started

### 1. Clone with submodules
```
git clone https://github.com/MoAgilah/SFMLEngine.git
cd SFMLEngine
git submodule update --init --recursive
```

### 2. Build

#### 🧰 Using Visual Studio
Simply open `SFMLEngine.sln` and build your desired configuration (**Debug** or **Release**).

### 3. Link in your project

To use **SFMLEngine**:

1. Add it as a **submodule** or dependency in your project.  
2. Include the **EngineInterface** headers.  
3. Link against the **EngineSFMLBackEnd** library (or another backend once available).  
4. Instantiate your engine via the backend’s **factory method** and use only the **interface layer** in your gameplay code.

## 🚀 Example Projects

| Project | Purpose | Description |
|----------|----------|-------------|
| [**Pong**](https://github.com/MoAgilah/Pong) | Demonstration | Simple gameplay showcase built on **SFMLEngine**. |
| [**AI-Game-Controller**](https://github.com/MoAgilah/AI-Game-Controller) | Prototype | Original project where the engine architecture was first conceptualized. |
| [**SuperMarioWorldClone**](https://github.com/MoAgilah/SuperMarioWorldClone) | Next Phase | Rebuild of the AI-Game-Controller project using **SFMLEngine** for modularity and scalability. |

## 🏗️ Roadmap

- [ ] Complete SFML backend coverage (rendering, input, audio)  
- [ ] Add example scenes and test harness  
- [ ] Introduce component/entity system layer  
- [ ] Add alternative backends (SDL, Vulkan, DirectX)  
- [ ] Integrate AI controller utilities  
- [ ] Create documentation site and wiki  




