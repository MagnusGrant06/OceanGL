## OceanGL
OceanGL is a project I have been working on and off since ~July, primarily to improve my modern C++ knowledge as well as OpenGL / graphics programming skills. It is an ocean simulation, but not in the traditional sense, where instead of just simulating the water, I want to simulate a vibrant ocean full of life.

### Techniques Used
This project is heavily work in progress, meaning there is a foundation of a very basic engine, with a renderer, a scene, objects, materials shaders, lights and more to allow me to learn how the backend of a game engine works as well as allowing my codebase to be extendable. On the C++ side, I'm trying to use modern features that are used in real codebases, such as proper memory management using smart pointers and move semantics, adhering to the rule of 0/5/10, lambdas and std::functions for custom shader data, as well as use of modern data structures for hash tables and inheritance. I plan to keep using features I learn about as I progress, like concepts, ranges/views, and constexpr. On the graphics side I'm following learnopengl.com loosely to improve my OpenGL knowledge, and have so far implemented full model loading for .obj files, cameras, shaders, point lights and directional lights, and an object hierarchy allowing for dynamic drawing and updating of models and shaders. I plan to transfer shader work I did on my fluid simulation project to create similar water based shading effects, as I created a water simulation using the Godot game engine, using its native GDShader language, which is similar to OpenGL's GLSL.

### Resources
[Learn OpenGL](https://learnopengl.com/Lighting/Multiple-lights) \
[C++ Reference](https://cppreference.com)
