# Cub3D

Cub3D is the last project in 42 School that require us to code in C. This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. This project allow us to explore the world of ray-casting and create a ray-caster from scratch.

## Table of contents
- [Cub3D](#cub3d)
  - [Table of contents](#table-of-contents)
  - [Team Members](#team-members)
  - [Project Requirements](#project-requirements)
  - [High-level overview](#high-level-overview)
    - [Initialization](#initialization)
    - [Parsing](#parsing)
    - [Raycasting](#raycasting)
      - [How many rays do we need to cast????](#how-many-rays-do-we-need-to-cast)
      - [How to cast a ray????](#how-to-cast-a-ray)
    - [Rendering](#rendering)
  - [Resources](#resources)
  - [Conclusion](#conclusion)

## Team Members

Our team is composed of 2 members:

1. [Wang Xue Rui](https://github.com/wangxuerui2003)
2. [Ricky Wong](https://github.com/Ricky0625)

The actual time spent on this project is around 2 weeks.

## Project Requirements

For this project, we managed to complete both the mandatory part and bonus part with some extra features. Please read the subject file for more information.

Link to the subject file: [Subject](https://cdn.intra.42.fr/pdf/pdf/88183/en.subject.pdf)

To summarize, our program should be able to (including bonus):

- Move POV with WASD, rotate POV with left and right arrow keys or mouse
- Render different textures for different walls
- Set different colors for floor and ceiling
- Accept only maps file that are ended with this file extension: `.cub`
- Accept only maps that are surrounded by walls
- Identify invalid maps/textures format and exit the program with an error message
- Have some simple animation
- A minimap system
- A door that can be opened and closed
- Wall collisions system

Below are some are the extra features that we have added:

- A simple HUD, which show some information about the player and the raycasting environment
- Able to "look up & down" with up and down arrow keys
- Able to increase/decrease FOV
- Toggle fisheye effect

> Its' not something impressive but it makes the program fun :D

## High-level overview

From a high-level standpoint, our program can be divided into 4 parts:

1. **Initialization** - This is where we initialize some of the variables and structs that we need for the program to run.
2. **Parsing** - This is where we parse the map file and validate if the map follows the rules.
3. **Raycasting** - This is where we do raycasting. Basically the core of the program. The data of this part will be used in next phase.
4. **Rendering** - This is where we render the world based on the data we get from the previous phase.

If you are interested in the details of each phase, we welcome you to continue reading. :D

> Disclaimer: The explanation will still be explained in a high-level manner. But we will try our best to include more details so that you can understand the program better.

### Initialization

For this part, we will initialize our mlx instances, the canvas (images, in the case of mlx), the raycasting environment, the render options and etc. These value will be used in the phases after this.

### Parsing

Before we continue to explain the parsing phase, we would like to list down the rules for the map file, the textures, and the map content.

1. Map file
   
   - The map file only will get passed in as an argument if it **ends with** the `.cub` file extension. Yeap, so `text.cub.cub` is a valid map file because it ends with `.cub`. :D
   - The map file should contain all the required information, which are the **elements** (textures) and the **map content** (basically the rendered world in a 2D format). The order of the information is crucial. It must be in the following order:
     - Elements
     - Map content
    - You can have spaces in between Elements and Map content.
  
2. Textures

    - These are the required textures for the program to run.
      - North texture (NO)
      - South texture (SO)
      - East texture (EA)
      - West texture (WE)
      - Ceiling color (C)
      - Floor color (F)
    - When you specify the textures, you should **strictly** follow the format below:
      - Textures: `NO ./path/to/texture`. Specify the identifier then the path.
      - Colors: `C 255,255,255`. Specify the identifier then the RGB value.
    - There's one optional textures, which is the door texture (D). It's completely optional so even if you don't provide it, the program will still run. For door, you need to follow the **format for textures**.
    - Again, it's **STRICTLY** required to the format here. Otherwise, you will see an error message when you are trying to run the program.
    - Each element can be seperated by a new line.
  
3. Map content

    - The map content should be surrounded by walls. The shape of the map can be anything as long as it's surrounded by walls.
    - The map must be composed of only 7 possible characters:
      - 0: Empty space
      - 1: Wall
      - N/S/E/W: Player's starting position and orientation
      - D: The location of the door (optional)
    - You only can have one player
    - You can have multiple doors (optional)
    - There's should not be any extra spaces or lines in between the map content. Otherwise, you will see an error message when you are trying to run the program.

So these are the rules for the map file, the textures, and the map content. Now, let's move on to the parsing phase. The parsing phase is basically the phase where we parse the map file and validate if the map follows the rules. If the map file is valid, we will store the data in a struct called `t_map`. This struct will be used in the next phase.

Besides this, when we are validating our map file, we will also do some initialization for the player and doors. If we encounter any of them, we add them to our main struct `t_cub`. This struct basically stores everything we need for the program to run.

### Raycasting

Now, the fun part begins. This is where we do raycasting. If we were to explain it in a simple terms, this is what we do in this phase:

    For each **column** of the screen, we **cast a ray** to see **where and what this ray hits**. We **store the data of the ray** and continue the process until we reach the last column of the screen.

Is this simple enough? Hahaha. If you are still confused, let's break it down into smaller chunks.

#### How many rays do we need to cast????

First off, how do we know how many rays do we need to cast? Well, this is actually quite simple. It's the width of the screen. So, if the screen is 800px wide, we need to cast 800 rays. If the screen is 1920px wide, we need to cast 1920 rays. So, the number of rays we need to cast is the width of the screen.

#### How to cast a ray????

Before we continue, we have to admit, we lied. We actually didn't just cast one ray for each column. We actually cast **two** rays and pick one. Haha.

This part is actually done by using an algorithm called DDA. OK, What? DDA? Disco Duck Adventure? Dinner Dessert Appetizer? Alright alright, it's actually called **Digital Differential Analyzer**.

We will use this algorithm to know the intersection point of the ray. OK, but like how? Well, I think it's better you go watch this video first which explains how and DDA is used in raycasting.

[Super Fast Ray Casting in Tiled Worlds using DDA - javidx9](https://youtu.be/NbSee-XM7WA)

Ok... I guess you know how it works now right? So, we will use DDA to find the intersection point of the ray. In the video, it actually "cast" a ray both horizontally and vertically simultaneously. But we don't actually do it that way. Instead, we cast two ray, one will seek for intersection on a horizontal axis, and another will seek for intersection on a vertical axis.

When both of the found their intersection point, we calculate the distance between the player and the intersection point. Then we compare both ray (horizontal and vertical) and choose the one that's closer to the player. This ray will then store into an array of rays and ready to be used in the next phase.

To check whether we should stop the whole DDA process is by using our collision system. Once it found a wall or a closed door, the DDA algorithm will stop.

Also, during this, we will also check if along the ray, is there a door? We don't care the state of the door. When we found one, we get the data of the door, and store it into our ray data as well. This data will then be used to open/close door. To open/close door, it must be within the `DOOR FOV` and a ray distance that is less than `100`.

Once this phrase is completed, we now have an array of rays, which its size is the width of the window.

These are the data that we collect for each ray:

1. The intersection point
2. The angle of the ray
3. The distance between the player and the intersection point
4. The orientation of the ray, where it landed on (horizontal or vertical axis)
5. The info of the door (if there's any)

### Rendering

Once we have all the data we need, we can now render the world. The data we collected in the previous phase not only can be used to render the world, but also can be used to render the minimap, we just need to scale it down.

It's the similar process like raycasting, we will loop through each column of the screen and render the world column by column. We will draw each column one by one. Unlike other peers, which they draw the whole world in steps (draw ceiling and floor first then the walls), we draw the whole world in one go. We think this is a better approach because it's easier to manage and it's more efficient. Meaning that we don't need to loop through the whole screen multiple times.

We have a function called `draw_slice`, which is responsible to draw each of the column in one go. The order is as below:

1. Draw ceiling
2. Draw the textures
3. Draw floor

To draw ceiling and floor is easy, we just need a function that draw lines and can take in a color. For the textures, we need to do some calculation to get the correct texture to draw. We will explain this in the next section.

To get the correct texture, we need to do something called, **texture mapping**. This is the process where we map the texture to the wall, extract the correct texture column and copy it to the screen. We need to perform some calculation to get the texture offset, calculate the scale factor so that we can repeat/skip some of the texture pixel. Once we have these, we calculate where should we put the pixel on the canvas. We will then copy the pixel from the texture to the canvas. Repeat this process until we loop through all the rays.

And here we go, our world is rendered. :D

## Resources

The most recommended resource for this project by our peers is the tutorial by [Lode](https://lodev.org/cgtutor/raycasting.html). It's a well written resource but there too much information to digest. We personally don't think it's a good resource for beginners because it might be too overwhelming.

So, we actually use another tutorial to guide us through the project. I think this resource is underrated. This is the resouce we are using: [Ray-casting tutorial by F. Permadi](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/). It seperate the tutorial into bite-size chunks and explain the concept in a simple way. Highly recommended.

## Conclusion

Overall, this is a fun project to work on. We have learned a lot from this project. When we just started the core program, this project seems impossible to complete. It's so rewarding to see that we can actually complete this project. This just proves that we can do anything if we put enough effort into it. Also, to proves that our hard work on the previous projects are not wasted.

Lastly, we would like to thank all the people who have helped us in this project. We really appreciate it. Thank you! I hope you enjoy reading this README file. :D
