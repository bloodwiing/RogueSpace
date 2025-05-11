![LogoTemp2](https://github.com/user-attachments/assets/27fcf399-284e-4304-abc9-fef4371bd0a8)

A 1st year Vilnius University Computer Science Course project.

C++ 3D Game Engine using the OpenGL graphics driver with a spaceship combat demo game.

## Video

https://github.com/user-attachments/assets/b25806e1-fc39-4a1a-b5e0-657296a8244f

## Technicals

The game engine uses node based with a hybrid entity component system. Nodes have completely independent trees and have respective names.

The name of the game engine is **JAGE** (Just Another Game Engine).

3D Nodes are called Actors. Each actor may have more children as actors. Children will be affected by any transformations of all of its parents up to the root of the scene, which includes translation, rotation, scale.

<!-- ![image](https://github.com/user-attachments/assets/10521fd1-37c1-4af8-bdcd-3e6b9c0e32d9) -->
<img alt="3D Node Inheritence" src="https://github.com/user-attachments/assets/10521fd1-37c1-4af8-bdcd-3e6b9c0e32d9" width="600">

All nodes shown in the graphic, except Ship Actor, are JAGE base nodes, usable for every project. Ship Actor is specific to Trailblazer.

<br>

Similarly, 2D Nodes are called Frames. And as Actors, they can have Frames as children. Frames also have an Anchor system, where Frames can be customised how they scale when the parent size changes (such as in the case of a screen resize).

<!-- ![image](https://github.com/user-attachments/assets/c8fb114d-bbb7-4632-b7d9-e17d46ee4928) -->
<img alt="2D Node Inheritence" src="https://github.com/user-attachments/assets/c8fb114d-bbb7-4632-b7d9-e17d46ee4928" width="800">

Most nodes shown in this graphic are part of the JAGE base node types, but Enemy Indicator Frame, Score Frame and Progress Bar frames are special to Trailblazer.

## Features

Implemented features of the game engine:

* Asynchronous threaded asset loading with LOD priority;
* Specialised collection for Actors, made to made to be very fast to add or remove nodes;
* Support for fully responsive UI.

## Room for improvement

Despite the features of the game engine, some other features, that would be considered essential, had not been implemented:

* Proper shading had only been tested, but was not implemented, there is no collection of lights to reference and no way to create lights in the JAGE base;
* JAGE has no audio API;
* Scenes, Actor and Frame trees could be serialised to be loaded from files;
* Instanced Models, optimise drawing the same object over many points;
* Nodes inheritence versus Scripts should be made clearer.

## Building

```sh
cmake  -S . -B output
cmake --build output --target Build
```

## Libraries
* **[Glad](https://glad.dav1d.de/)** `0.1.36` for OpenGL `3.3`<br>
OpenGL loader
* **[GLFW](https://www.glfw.org/)** `3.3.8`<br>
OpenGL Window and Input tools
* **[stb](https://github.com/nothings/stb)** `5736b15`<br>
  Single-file libraries for C/C++
  * [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)<br>
    Single-file header for image-related tasks
* **[GLM](https://github.com/g-truc/glm)** `0.9.9.8`<br>
  Mathematics library for OpenGL applications
* **[m_json](https://github.com/nlohmann/m_json)** `3.11.2` <br>
  JSON for Modern C++
