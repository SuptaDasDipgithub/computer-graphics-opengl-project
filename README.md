# 🎨 Computer Graphics (OpenGL) Project
This project demonstrates **Computer Graphics concepts** using **C++ and OpenGL**.  
It visually represents 2D/3D scenes and rendering techniques, implemented as part of an academic course in **Computer Graphics**.

---
## 🚀 Features
- 🧱 2D/3D shape rendering using OpenGL primitives  
- 🌆 Scene modeling (e.g., buildings, urban environments, objects)  
- 🎥 Camera control and transformations  
- 💡 Basic lighting and shading  
- 🖱️ Interactive view controls (if enabled)
---
## 🧩 Project Structure
computer-graphics-opengl-project-main/
│
├── main.cpp # Main OpenGL source code
├── main.o # Compiled object file
├── test.cbp # Code::Blocks project file
├── test.depend # Dependency list for Code::Blocks
├── test.layout # IDE layout file
│
├── bin/
│ └── Debug/test.exe # Compiled executable (debug build)
│
├── obj/
│ └── Debug/main.o # Object file
│
└── demo/
└── urban area.jpg # Example rendered output / texture

---
## ⚙️ Setup & Installation
### 🧰 Requirements
- **C++ Compiler** (GCC, Clang, or MSVC)
- **OpenGL** (>= 3.0)
- **GLUT / freeGLUT** libraries
- **Code::Blocks IDE** *(optional but recommended)*
.
### 💻 Build Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/YOUR_USERNAME/computer-graphics-opengl-project.git
   cd computer-graphics-opengl-project-main

2. Open the project in Code::Blocks: File → Open → test.cbp

3. Configure your compiler to include: -lglut -lGLU -lGL

4. Build and run:
Press F9 in Code::Blocks, or Use terminal: g++ main.cpp -o graphics_project -lglut -lGLU -lGL./graphics_project

# 🧠 Concepts Demonstrated
- OpenGL Coordinate Systems
- Polygon Rendering
- Transformations (Translate, Rotate, Scale)
- Scene Composition
- Viewport & Projection Matrix Control

# 📚 Tools & Technologies
Language: C++
Graphics API: OpenGL
IDE: Code::Blocks
Platform: Windows / Linux

# 📜 License
This project is created for academic purposes under the Computer Graphics course. You may use or modify it with proper attribution.

# 🏫 Academic Context
Developed as a final project in Computer Graphics, demonstrating:
1. OpenGL-based visual rendering
2. Geometric transformation principles
3. Scene creation and rendering pipeline understanding
