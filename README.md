# Ray-Tracing-
An application that implements ray tracing from scratch using mathematics and linear algebra to render object of different shapes,materials, shininess , colors, and reflectivity in 3D scene.

## How the application works.
The application first places different object in the a 3D plane. The light sources and camera are  placed at specific position whereas the other objects and planes are initially placed at the origin then later transformed and  translated using matrix operations.

Different objects and their reflexitivity,shininess and colours are all modelled using linear algebra and mathematics.

## Running the code
- Download the SDL2  from https://www.libsdl.org/download-2.0.php,
- Clone the project and replace the SDL2PATH variable in the makefile with the absolute path of where the SLD2 folder was extracted,
- using CMake, run command 'make'

THe following are screenshots of  the different stages of development.

## The 2D rendering
![Screenshot 2022-02-08 161321](https://user-images.githubusercontent.com/55924723/155990815-c1d3a631-a896-459d-b2ed-21f12e87b3ec.png)

## Rendering 3D object to a 2D screen
![Screenshot 2022-02-08 164131](https://user-images.githubusercontent.com/55924723/155990839-2a4d0b2f-f883-4fcb-b38f-c7ad2d098bda.png)

## Calculating the shadows and shininess in relation to a source light
![Screenshot 2022-02-08 193018](https://user-images.githubusercontent.com/55924723/155990845-476fea27-174e-4cec-809c-cbb33fcd20af.png)

## Transforming objects using translation, rotations and scaling matrices. (The three objects are derived from unit radius spheres centred at the origin).
![Screenshot 2022-02-10 105544](https://user-images.githubusercontent.com/55924723/155990850-bd1a68a5-2a13-4801-9d47-e96bb0fd9683.png)

## Implementing a plane
![Screenshot 2022-02-10 133942](https://user-images.githubusercontent.com/55924723/155990868-cd59f34f-237a-472a-9b8a-04c3afd030bb.png)

## implemented shadowing on the plane
![Screenshot 2022-02-17 141328](https://user-images.githubusercontent.com/55924723/155990883-ab5e0408-e0a0-46d0-8447-4bdf88c48bf9.png)

## Made correction to the shadowing to make it realistic
![Screenshot 2022-02-17 143054](https://user-images.githubusercontent.com/55924723/155990895-8fd9114c-c870-47a8-ae7c-31506974d9f3.png)

## Introduced different sources of lights placed at different positions and having different colors.
![Screenshot 2022-02-17 174635](https://user-images.githubusercontent.com/55924723/155990902-a510d385-a8c4-4307-9c53-907df90f47f1.png)

## Introduced different materials having different specular, shiness and reflectivity values
![Screenshot 2022-02-27 180440](https://user-images.githubusercontent.com/55924723/155990908-8ad1c0ff-c24d-496b-b829-b5d3f6acf95f.png)
![different_reflexitivity](https://user-images.githubusercontent.com/55924723/184780442-7a37f754-ce13-40b7-927b-b45341aebeee.png)

## Introducing Cylinders and cones
![Cylinder_and_cones](https://user-images.githubusercontent.com/55924723/184780631-8469010e-1965-4e9d-adfc-396eba6e6b41.png)


