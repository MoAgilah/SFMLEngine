# EngineSFMLBackend

A modern C++ backend implementation that demonstrates interface-driven architecture, backend encapsulation and modular system integration.

EngineSFMLBackend provides the concrete SFML implementation of the abstractions defined by EngineInterface. Rather than exposing SFML directly throughout an application, the project encapsulates rendering, input, resources, audio and window management behind stable interface contracts, allowing higher-level systems to remain independent of the underlying multimedia framework.

The project focuses on software engineering rather than graphics features, demonstrating how a third-party framework can be integrated into a reusable backend while maintaining clean architecture, extensibility and long-term maintainability.

---

## The Engineering Problem

While EngineInterface defines stable abstractions for engine systems, applications still require concrete implementations that interact with platform and graphics libraries. Directly exposing SFML throughout an application would introduce framework dependencies into higher-level code, increasing coupling and reducing flexibility.

EngineSFMLBackend addresses this challenge by implementing the EngineInterface contracts using SFML while containing all framework-specific functionality within the backend. Applications communicate exclusively through abstract interfaces, allowing backend technologies to be replaced without affecting engine or application logic.

---

## Framework Architecture

<p align="center">
  <img width="447" height="558" alt="sfml-engine-diagram" src="https://github.com/user-attachments/assets/a8979395-f40e-42f7-aa99-36ae3a946fa5" width="600"/>
</p>

The backend is organised into distinct implementation layers that mirror the abstractions defined by EngineInterface. Interface contracts are implemented through dedicated SFML components, while backend services remain modular and isolated from higher-level engine systems. This separation provides a reusable implementation that can evolve independently of the interface layer.

---

## Architecture Goals

The project was designed to demonstrate:

- Backend implementation
- Interface-driven architecture
- Backend abstraction
- Dependency inversion
- Modular backend design
- Layered architecture
- Reusable engine services

Although demonstrated using SFML, these engineering principles are transferable to alternative rendering APIs, multimedia frameworks, simulation software and other modular C++ applications.

---

## Key Features

- Complete SFML implementation of EngineInterface
- Encapsulated rendering, input, audio and resource systems
- Clear separation between interface contracts and backend implementation
- Modular backend services organised by responsibility
- Git submodule integration with EngineInterface
- Reusable architecture designed for extension and future backend replacement

---

## Technologies & Engineering Practices

### Development

- C++20
- SFML 3
- Visual Studio 2022
- Git
- Git Submodules

### Engineering Practices

- Backend Implementation
- Interface-Driven Architecture
- Dependency Inversion
- Backend Abstraction
- Modular Architecture
- Layered Architecture
- RAII
- Resource Encapsulation

---

## Architecture Highlights

- Concrete implementation of EngineInterface contracts
- Backend encapsulation of SFML functionality
- Modular subsystem organisation
- Reusable backend implementation
- Clean separation between interfaces and framework code

---

## Engineering Outcome

EngineSFMLBackend demonstrates how a modern C++ backend can integrate a third-party multimedia framework without compromising architectural separation.

By implementing the contracts defined by EngineInterface, the backend provides rendering, input, resources and platform services through stable abstractions while isolating SFML from higher-level engine systems. This approach improves maintainability, supports future backend replacement and provides a reusable implementation that can be shared across multiple projects.

---
