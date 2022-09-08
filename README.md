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

## Calculating and rendering a 3D sphere on a 2D screen
### Rendering 3D image onto a 2D screen
![passing_a_3D_ray_into_a_2D_screen](https://user-images.githubusercontent.com/55924723/189185343-19952480-7c28-43da-bf0a-25b45f959eed.png)
### Vector equation of a sphere
![finding_the_intersection_point](https://user-images.githubusercontent.com/55924723/189186868-1c30fff5-5757-46b2-a3b7-60cb65fced72.png)

### Simplifying the equation
![finding_the_equation_of_circle](https://user-images.githubusercontent.com/55924723/189185800-f64068ce-a826-482e-9177-9286fe9eea20.png)

### Implemented sphere from the maths and rendered into the scene.
![Screenshot 2022-02-08 164131](https://user-images.githubusercontent.com/55924723/155990839-2a4d0b2f-f883-4fcb-b38f-c7ad2d098bda.png)

## Calculating the shadows and shininess in relation to a source light
### Using dot product to get the angle between the light source and a point on the sphere
![shiningness_maths](https://user-images.githubusercontent.com/55924723/189185440-426b5e98-6a10-48fa-9033-e9d8426b91e0.png)
### Implementation of the maths.
![Screenshot 2022-02-08 193018](https://user-images.githubusercontent.com/55924723/155990845-476fea27-174e-4cec-809c-cbb33fcd20af.png)

## Transforming objects using translation, rotations and scaling matrices.

### The different matrices that are used to translate, rotate and scale unit sphere centred from the origin.
![combined_transformations](https://user-images.githubusercontent.com/55924723/189185605-6e8f699a-ec74-4bdd-ae5b-af16da5ed61d.png)
### Implemented the maths. The three objects are derived from unit radius spheres centred at the origin
![Screenshot 2022-02-10 105544](https://user-images.githubusercontent.com/55924723/155990850-bd1a68a5-2a13-4801-9d47-e96bb0fd9683.png)




## Implementing a plane
### Plane vector
![plane_vectors](https://user-images.githubusercontent.com/55924723/189185672-0bf5e534-91d6-4629-9e5a-942a1a89cdcb.png)
### Equation for finding point of intersection with a plane
![finding_equation_for_the_intersection](https://user-images.githubusercontent.com/55924723/189185733-e2e303ad-09c4-4e23-9dbe-abce791c2228.png)

### Implementation
![Screenshot 2022-02-10 133942](https://user-images.githubusercontent.com/55924723/155990868-cd59f34f-237a-472a-9b8a-04c3afd030bb.png)

## Implemented shadowing on the plane
![Screenshot 2022-02-17 141328](https://user-images.githubusercontent.com/55924723/155990883-ab5e0408-e0a0-46d0-8447-4bdf88c48bf9.png)
## Made correction to the shadowing to make it realistic
![Screenshot 2022-02-17 143054](https://user-images.githubusercontent.com/55924723/155990895-8fd9114c-c870-47a8-ae7c-31506974d9f3.png)

## Introduced different sources of lights placed at different positions and having different colors.
![Screenshot 2022-02-17 174635](https://user-images.githubusercontent.com/55924723/155990902-a510d385-a8c4-4307-9c53-907df90f47f1.png)

## Calculated and introduced different materials having different specular, shiness and reflectivity values
### Material diffusion vectors and the point of intersections
![material_diffusion_calculation](https://user-images.githubusercontent.com/55924723/189187534-969879f1-0b8e-404c-bd76-4630f32d414e.png)
### Specular vectors and intersection equations
![specular_mathematics](https://user-images.githubusercontent.com/55924723/189187573-6217a5ac-c8f1-4b86-ac6d-92254e6f1ad8.png)

### Reflection vectors and the intersection equations
![reflectivity_mathematics](https://user-images.githubusercontent.com/55924723/189187605-24e71943-dec6-480f-8cf0-8187215bc051.png)

### implementation
![Screenshot 2022-02-27 180440](https://user-images.githubusercontent.com/55924723/155990908-8ad1c0ff-c24d-496b-b829-b5d3f6acf95f.png)
![different_reflexitivity](https://user-images.githubusercontent.com/55924723/184780442-7a37f754-ce13-40b7-927b-b45341aebeee.png)


## Introducing Cylinders and cones
![Cylinder_and_cones](https://user-images.githubusercontent.com/55924723/184780631-8469010e-1965-4e9d-adfc-396eba6e6b41.png)


