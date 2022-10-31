# 42_RayTracer


<img width="1340" alt="Screen Shot 2022-10-27 at 3 51 45 PM" src="https://user-images.githubusercontent.com/89991397/198308503-ec15fbd8-a7f4-4d02-9611-3e1b50020dc7.png">

## Introduction
During this project we built a basic raytracer in C, where we awere able to render a scene with several objects such as a plane, sphere or cylinder with lights and shadows. We used the [MLX42 library](https://github.com/codam-coding-college/MLX42) in order to render each pixel to the screen. We used the [unity unit tester](http://www.throwtheswitch.org/unity) in order to test the parsed data from a .rt file. Concurrency is applied in the form of threading, where 7 threads are used to increase the running time on average of 300% by dividing the computations per pixel. For the computations basic geometry using linear algebra is applied to shoot rays from a window to the objects which are displayed.


## Downloading the Repository
Download the git repo's using the following commands:

```
git clone https://gitlab.com/stormq4/42_raytracer.git
cd 42_RayTracer
```

## Running the program
MLX42 is supported by GLFW. In order to download the GLFW library run the following commands in your command line. 

```
brew update
brew install glfw
```

Compile the minrRT executable bij running:
```
make bonus
```

And execute a map by running a file in the rt_files folder in the command line as an argument of the .rt folder.
```
./miniRT rt_files/(can_be_anything).rt
``` 
<img width="1345" alt="Screen Shot 2022-10-27 at 3 53 43 PM" src="https://user-images.githubusercontent.com/89991397/198308551-d358c52a-ab52-4ce7-9988-7ceb5f2b009b.png">

## Colaborators
This project was created by [pderksen98](https://gitlab.com/pderksen98) && [me](https://gitlab.com/stormq4).

## Some Cool Generated Scenes

<img width="1334" alt="Screen Shot 2022-10-27 at 3 52 00 PM" src="https://user-images.githubusercontent.com/89991397/198308598-e7d7db15-8f7d-430e-bd9b-13599ec59a12.png">

<img width="1346" alt="Screen Shot 2022-10-27 at 3 52 17 PM" src="https://user-images.githubusercontent.com/89991397/198308274-3ea92fec-b256-4548-974f-ae32ea1c0c45.png">
